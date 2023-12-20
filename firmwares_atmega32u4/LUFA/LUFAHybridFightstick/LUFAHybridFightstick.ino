#include "LUFAConfig.h"
#include <LUFA.h>
#include "XS_HID.h"
#define BOUNCE_WITH_PROMPT_DETECTION
#include <Bounce2.h>
#include <EEPROM.h>
#include <inttypes.h>

/* in case you want to disable one type of gamepad */
//#define DISABLE_NSWITCH
//#define DISABLE_XINPUT

#define SOCD_CONFIG

/* PINOUT (follows Nintendo naming (X=up, B=down)) */
#define PIN_UP    7
#define PIN_DOWN  4
#define PIN_LEFT  3
#define PIN_RIGHT 5
#define PIN_A     MISO         //XBOX B
#define PIN_B     10           //XBOX A  
#define PIN_X     15           //XBOX Y
#define PIN_Y     MOSI         //XBOX X     
#define PIN_L     21           //XBOX LB
#define PIN_R     20           //XBOX RB
#define PIN_ZL    8            //XBOX LT
#define PIN_ZR    19           //XBOX RT
#define PIN_LS    6            //XBOX LS (left analog click)
#define PIN_RS    9            //XBOX RS (right analog click)
#define PIN_PLUS  2            //XBOX START
#define PIN_MINUS 18           //XBOX BACK
#define PIN_HOME  1

/* Buttons declarations */
#define MILLIDEBOUNCE 1 //Debounce time in milliseconds
unsigned long startAndSelTime = 0;
unsigned long currTime = 0;

byte internalButtonStatus[4];

Bounce joystickUP = Bounce();
Bounce joystickDOWN = Bounce();
Bounce joystickLEFT = Bounce();
Bounce joystickRIGHT = Bounce();
Bounce buttonA = Bounce();
Bounce buttonB = Bounce();
Bounce buttonX = Bounce();
Bounce buttonY = Bounce();
Bounce buttonL = Bounce();
Bounce buttonR = Bounce();
Bounce buttonZL = Bounce();
Bounce buttonZR = Bounce();
Bounce buttonLS = Bounce();
Bounce buttonRS = Bounce();
Bounce buttonPLUS = Bounce();
Bounce buttonMINUS = Bounce();
Bounce buttonHOME = Bounce();

/* MODE DECLARATIONS */
typedef enum {
  RIGHT_ANALOG_MODE,
  ANALOG_MODE,
  DIGITAL,
} State_t;
State_t state;

typedef enum {
  NEUTRAL,    // LEFT/UP + DOWN/RIGHT = NEUTRAL
  NEGATIVE,   // LEFT/UP beats DOWN/RIGHT
  POSITIVE,   // DOWN/RIGHT beats LEFT/UP
  LAST_INPUT, //Last input has priority; not a valid state if being used for initial_input
} Socd_t;
Socd_t x_socd_type = NEUTRAL; // controls left/right and up/down resolution type
Socd_t y_socd_type = NEGATIVE;
Socd_t x_initial_input, y_initial_input = NEUTRAL;

typedef enum {
  CVERT_NORMAL,     // Middle input is DOWN (Hitbox style)
  CVERT_INVERT        // Middle input is UP (for normal arcade style)
} CardVert_t;
CardVert_t cvert;

/* mode selectors */
bool xinput;
bool modeChanged;

void checkModeChange() {
  if (buttonStatus[BUTTONSTART] && buttonStatus[BUTTONSELECT])
  {
    if ( !modeChanged )
    {
      State_t last_state;

      last_state = state; 

      if (internalButtonStatus[BUTTONLEFT])
        state = ANALOG_MODE;
      else if (internalButtonStatus[BUTTONRIGHT])
        state = RIGHT_ANALOG_MODE;
      else if (internalButtonStatus[BUTTONUP])
        state = DIGITAL;

      if (last_state != state) EEPROM.put(0, state);
      modeChanged = true;
    }
    else
    {
      modeChanged = false;
    }
  }
}

void setupPins() {
  if (cvert == CVERT_INVERT) {
    // Inverted Up/Down input
    joystickUP.attach(PIN_DOWN, INPUT_PULLUP);
    joystickDOWN.attach(PIN_UP, INPUT_PULLUP);
  } else { // CVERT_NORMAL (Default)
    joystickUP.attach(PIN_UP, INPUT_PULLUP);
    joystickDOWN.attach(PIN_DOWN, INPUT_PULLUP);
  }
  joystickLEFT.attach(PIN_LEFT, INPUT_PULLUP);
  joystickRIGHT.attach(PIN_RIGHT, INPUT_PULLUP);
  buttonA.attach(PIN_A, INPUT_PULLUP);     // XBOX B
  buttonB.attach(PIN_B, INPUT_PULLUP);     // XBOX A
  buttonX.attach(PIN_X, INPUT_PULLUP);     // XBOX Y
  buttonY.attach(PIN_Y, INPUT_PULLUP);    // XBOX X
  buttonL.attach(PIN_L, INPUT_PULLUP);    // XBOX LB
  buttonR.attach(PIN_R, INPUT_PULLUP);     // XBOX RB
  buttonZL.attach(PIN_ZL, INPUT_PULLUP);    // XBOX LT
  buttonZR.attach(PIN_ZR, INPUT_PULLUP);    // XBOX RT
  buttonLS.attach(PIN_LS, INPUT_PULLUP);       // XBOX LS
  buttonRS.attach(PIN_RS, INPUT_PULLUP);       // XBOX RS
  buttonPLUS.attach(PIN_PLUS, INPUT_PULLUP);   // XBOX START
  buttonMINUS.attach(PIN_MINUS, INPUT_PULLUP); // XBOX BACK
  buttonHOME.attach(PIN_HOME, INPUT_PULLUP);

  joystickUP.interval(MILLIDEBOUNCE);
  joystickDOWN.interval(MILLIDEBOUNCE);
  joystickLEFT.interval(MILLIDEBOUNCE);
  joystickRIGHT.interval(MILLIDEBOUNCE);
  buttonA.interval(MILLIDEBOUNCE);
  buttonB.interval(MILLIDEBOUNCE);
  buttonX.interval(MILLIDEBOUNCE);
  buttonY.interval(MILLIDEBOUNCE);
  buttonL.interval(MILLIDEBOUNCE);
  buttonR.interval(MILLIDEBOUNCE);
  buttonZL.interval(MILLIDEBOUNCE);
  buttonZR.interval(MILLIDEBOUNCE);
  buttonLS.interval(MILLIDEBOUNCE);
  buttonRS.interval(MILLIDEBOUNCE);
  buttonPLUS.interval(MILLIDEBOUNCE);
  buttonMINUS.interval(MILLIDEBOUNCE);
  buttonHOME.interval(MILLIDEBOUNCE);
}

void setup() {

  bool updateCVert = false;
  modeChanged = false;
  EEPROM.get(0, state);
  EEPROM.get(2, xinput);
#ifdef SOCD_CONFIG
  EEPROM.get(4, x_socd_type);
  EEPROM.get(6, y_socd_type);
#endif

  // setup cardinal middle button settings
  EEPROM.get(8, cvert);

  if (cvert != CVERT_NORMAL && cvert != CVERT_INVERT) {
    // Initialize to Hitbox style if EEPROM is not initialized
    cvert = CVERT_NORMAL;
    updateCVert = true;
  }

  if (digitalRead(PIN_UP) == LOW) {
    // set to standard arcade style setup
    if  (cvert != CVERT_INVERT) {
      cvert = CVERT_INVERT;
      updateCVert = true;
    }
  }
  if (digitalRead(PIN_DOWN) == LOW) {
    // set to standard Hitbox style setup
    if  (cvert != CVERT_NORMAL) {
      cvert = CVERT_NORMAL;
      updateCVert = true;
    }
  }

  if (updateCVert) {
    EEPROM.put(8, cvert);
  }

  setupPins();
  delay(500);

#ifdef DISABLE_NSWITCH
#warning "NSWITCH mode is disabled, will act only as an XInput controller"
  /* force Xinput */
  xinput = true;
#else
#ifdef DISABLE_XINPUT
#warning "XINPUT mode is disabled, will act only as a Nintendo switch controller"
  /* force nswitch */
  xinput = false;
#else
  /* set xinput mode according to held button */
  // if select is held on boot, NSWitch mode
  bool xinput_current = xinput;
  int value = digitalRead(PIN_MINUS);
  if (value == LOW)
  {
    xinput = false;
  }
  // if start is held on boot, XInput mode
  else {
    value = digitalRead(PIN_PLUS);
    if (value == LOW)
    {
      xinput = true;
    }
  }
  if (xinput_current != xinput) {
    // Update if changed
    EEPROM.put(2, xinput);
  }
#endif
#endif

  // TODO: add setting for inverting Up/Down

#ifdef SOCD_CONFIG
  // Configure SOCD cleaning type at startup.
  {
    Socd_t y_socd_type_current = y_socd_type;
    Socd_t x_socd_type_current = x_socd_type;

    if (digitalRead(PIN_HOME) == LOW) {
      // If HOME is pressed, change to all Neutral SOCD setup
      y_socd_type = NEUTRAL;
      x_socd_type = NEUTRAL;
    }
    if (digitalRead(PIN_LS) == LOW) {
      // If LS is pressed, change to Gafro style SOCD setup
      y_socd_type = NEGATIVE;
      x_socd_type = LAST_INPUT;
    }
    if (digitalRead(PIN_RS) == LOW) {
      // If RS is pressed, change to Hitbox style SOCD setup
      y_socd_type = NEGATIVE;
      x_socd_type = NEUTRAL;
    }

    // Update if any changes are made
    if (x_socd_type_current != x_socd_type) EEPROM.put(4, x_socd_type);
    if (y_socd_type_current != y_socd_type) EEPROM.put(6, y_socd_type);
  }
#endif

  SetupHardware(xinput);
  GlobalInterruptEnable();
}


void loop() {
  currTime = millis();
  buttonRead();
  checkModeChange();
  convert_dpad();
  send_pad_state();
}

void convert_dpad() {
  byte cleanButtonStatus[4] = {0};
  // Prevent SOCD inputs (left+right or up+down) from making it to the logic below.
  clean_all_socd(internalButtonStatus, cleanButtonStatus, x_socd_type, y_socd_type);

  switch (state)
  {
    case DIGITAL:
      buttonStatus[AXISLX] = 128;
      buttonStatus[AXISLY] = 128;
      buttonStatus[AXISRX] = 128;
      buttonStatus[AXISRY] = 128;
      buttonStatus[BUTTONUP] = cleanButtonStatus[BUTTONUP];
      buttonStatus[BUTTONDOWN] = cleanButtonStatus[BUTTONDOWN];
      buttonStatus[BUTTONLEFT] = cleanButtonStatus[BUTTONLEFT];
      buttonStatus[BUTTONRIGHT] = cleanButtonStatus[BUTTONRIGHT];
      break;

    case RIGHT_ANALOG_MODE:
      buttonStatus[AXISLX] = 128;
      buttonStatus[AXISLY] = 128;
      buttonStatus[BUTTONUP] = 0;
      buttonStatus[BUTTONDOWN] = 0;
      buttonStatus[BUTTONLEFT] = 0;
      buttonStatus[BUTTONRIGHT] = 0;

      if ((cleanButtonStatus[BUTTONUP]) && (cleanButtonStatus[BUTTONRIGHT])) {
        buttonStatus[AXISRY] = 0;
        buttonStatus[AXISRX] = 255;
      }
      else if ((cleanButtonStatus[BUTTONUP]) && (cleanButtonStatus[BUTTONLEFT])) {
        buttonStatus[AXISRY] = 0;
        buttonStatus[AXISRX] = 0;
      }
      else if ((cleanButtonStatus[BUTTONDOWN]) && (cleanButtonStatus[BUTTONRIGHT])) {
        buttonStatus[AXISRY] = 255;
        buttonStatus[AXISRX] = 255;
      }
      else if ((cleanButtonStatus[BUTTONDOWN]) && (cleanButtonStatus[BUTTONLEFT])) {
        buttonStatus[AXISRY] = 255;
        buttonStatus[AXISRX] = 0;
      }
      else if (cleanButtonStatus[BUTTONUP]) {
        buttonStatus[AXISRY] = 0;
        buttonStatus[AXISRX] = 128;
      }
      else if (cleanButtonStatus[BUTTONDOWN]) {
        buttonStatus[AXISRY] = 255;
        buttonStatus[AXISRX] = 128;
      }
      else if (cleanButtonStatus[BUTTONLEFT]) {
        buttonStatus[AXISRX] = 0;
        buttonStatus[AXISRY] = 128;
      }
      else if (cleanButtonStatus[BUTTONRIGHT]) {
        buttonStatus[AXISRX] = 255;
        buttonStatus[AXISRY] = 128;
      }
      else {
        buttonStatus[AXISRX] = 128;
        buttonStatus[AXISRY] = 128;
      }

      break;

    case ANALOG_MODE:
    /* fallthrough */
    default:
      buttonStatus[AXISRX] = 128;
      buttonStatus[AXISRY] = 128;
      buttonStatus[BUTTONUP] = 0;
      buttonStatus[BUTTONDOWN] = 0;
      buttonStatus[BUTTONLEFT] = 0;
      buttonStatus[BUTTONRIGHT] = 0;

      if ((cleanButtonStatus[BUTTONUP]) && (cleanButtonStatus[BUTTONRIGHT])) {
        buttonStatus[AXISLY] = 0;
        buttonStatus[AXISLX] = 255;
      }
      else if ((cleanButtonStatus[BUTTONDOWN]) && (cleanButtonStatus[BUTTONRIGHT])) {
        buttonStatus[AXISLY] = 255;
        buttonStatus[AXISLX] = 255;
      }
      else if ((cleanButtonStatus[BUTTONDOWN]) && (cleanButtonStatus[BUTTONLEFT])) {
        buttonStatus[AXISLY] = 255;
        buttonStatus[AXISLX] = 0;
      }
      else if ((cleanButtonStatus[BUTTONUP]) && (cleanButtonStatus[BUTTONLEFT])) {
        buttonStatus[AXISLY] = 0;
        buttonStatus[AXISLX] = 0;
      }
      else if (cleanButtonStatus[BUTTONUP]) {
        buttonStatus[AXISLY] = 0;
        buttonStatus[AXISLX] = 128;
      }
      else if (cleanButtonStatus[BUTTONDOWN]) {
        buttonStatus[AXISLY] = 255;
        buttonStatus[AXISLX] = 128;
      }
      else if (cleanButtonStatus[BUTTONLEFT]) {
        buttonStatus[AXISLX] = 0;
        buttonStatus[AXISLY] = 128;
      }
      else if (cleanButtonStatus[BUTTONRIGHT]) {
        buttonStatus[AXISLX] = 255;
        buttonStatus[AXISLY] = 128;
      }
      else {
        buttonStatus[AXISLX] = 128;
        buttonStatus[AXISLY] = 128;
      }

      break;


  }
}

void buttonRead()
{
  // for SOCD cleaning to work properly we need directions to update
  // on any change instead of on fall
  joystickUP.update(); joystickDOWN.update(); joystickLEFT.update(); joystickRIGHT.update();
  if (joystickUP.changed() || joystickDOWN.changed() || joystickLEFT.changed() || joystickRIGHT.changed())
  {
    internalButtonStatus[BUTTONUP] = !joystickUP.read();
    internalButtonStatus[BUTTONDOWN] = !joystickDOWN.read();
    internalButtonStatus[BUTTONLEFT] = !joystickLEFT.read();
    internalButtonStatus[BUTTONRIGHT] = !joystickRIGHT.read();
  }
  if (buttonA.update()) {
    buttonStatus[BUTTONA] = buttonA.fell();
  }
  if (buttonB.update()) {
    buttonStatus[BUTTONB] = buttonB.fell();
  }
  if (buttonX.update()) {
    buttonStatus[BUTTONX] = buttonX.fell();
  }
  if (buttonY.update()) {
    buttonStatus[BUTTONY] = buttonY.fell();
  }
  if (buttonL.update()) {
    buttonStatus[BUTTONLB] = buttonL.fell();
  }
  if (buttonR.update()) {
    buttonStatus[BUTTONRB] = buttonR.fell();
  }
  if (buttonZL.update()) {
    buttonStatus[BUTTONLT] = buttonZL.fell();
  }
  if (buttonZR.update()) {
    buttonStatus[BUTTONRT] = buttonZR.fell();
  }
  if (buttonLS.update()) {
    buttonStatus[BUTTONL3] = buttonLS.fell();
  }
  if (buttonRS.update()) {
    buttonStatus[BUTTONR3] = buttonRS.fell();
  }
  if (buttonPLUS.update()) {
    buttonStatus[BUTTONSTART] = buttonPLUS.fell();
  }
  if (buttonMINUS.update()) {
    buttonStatus[BUTTONSELECT] = buttonMINUS.fell();
  }
  if (buttonHOME.update()) {
    buttonStatus[BUTTONHOME] = buttonHOME.fell();
  }
}


void clean_all_socd(byte *internalButtonStatus, byte *cleanButtonStatus, Socd_t x_socd_type, Socd_t y_socd_type)
{
  clean_socd(internalButtonStatus[BUTTONLEFT], &cleanButtonStatus[BUTTONLEFT], internalButtonStatus[BUTTONRIGHT], &cleanButtonStatus[BUTTONRIGHT], x_socd_type, &x_initial_input);
  clean_socd(internalButtonStatus[BUTTONUP], &cleanButtonStatus[BUTTONUP], internalButtonStatus[BUTTONDOWN], &cleanButtonStatus[BUTTONDOWN], y_socd_type, &y_initial_input);
}
/**
   Cleans the given (possible) simultaneous opposite cardinal direction inputs according to the preferences provided.

   @note Given two simultaneous opposite cardinal direction inputs, clean_socd will
   make sure that both are not actually sent. The method used to resolve this conflict
   is determined by input_priority. The x (LEFT/RIGHT) and y (UP/DOWN) axes can be
   handled with the same logic as long as the negative and positive inputs are correctly
   arranged, so pointers are used to make the same function handle both.

   @param[in] negative_in The LEFT/UP input variable.
   @param[out] negative_out The LEFT/UP resulting value.
   @param[in] positive_in  The DOWN/RIGHT input variable.
   @param[out] positive_out  The DOWN/RIGHT resulting value.
   @param[in] input_priority Determines the SOCD resolution method used. @see Socd_t for how each resolution method works.
   @param[in,out] initial_input If input_priority = LAST_INPUT and SOCD cleaning is needed, this is used to determine
    which input was made last. If only one input is made, this variable is set to that input, even if input_priority != LAST_INPUT.
*/
void clean_socd(byte negative_in, byte *negative_out, byte positive_in, byte *positive_out, Socd_t input_priority, Socd_t *initial_input)
{
  if (negative_in && positive_in) // SOCD that needs to be resolved
  {
    switch (input_priority)
    {
      case NEUTRAL:
        *negative_out = *positive_out = false;
        break;
      case NEGATIVE:
        *negative_out = true;
        *positive_out = false;
        break;
      case POSITIVE:
        *negative_out = false;
        *positive_out = true;
        break;
      case LAST_INPUT:
        // Check which input was made first to figure out which input was made last, which wins.
        switch (*initial_input)
        {
          case NEGATIVE:
            *negative_out = false;
            *positive_out = true;
            break;
          case POSITIVE:
            *negative_out = true;
            *positive_out = false;
            break;
          // This is a fallback case for when there hasn't been an input since starting up.
          case NEUTRAL:
            *negative_out = *positive_out = false;
            break;
        }
    }
  }
  else // no SOCD to resolve, which means our current input (if any) can be output as is, but also should be remembered as the initial input.
  {
    *positive_out = positive_in;
    *negative_out = negative_in;
    if (negative_in && !positive_in)
      *initial_input = NEGATIVE;
    if (positive_in && !negative_in)
      *initial_input = POSITIVE;
  }
}
