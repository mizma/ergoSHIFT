# 1 "d:\\work\\flatbox\\firmwares_atmega32u4\\LUFA\\LUFAHybridFightstick\\LUFAHybridFightstick.ino"
# 2 "d:\\work\\flatbox\\firmwares_atmega32u4\\LUFA\\LUFAHybridFightstick\\LUFAHybridFightstick.ino" 2
# 3 "d:\\work\\flatbox\\firmwares_atmega32u4\\LUFA\\LUFAHybridFightstick\\LUFAHybridFightstick.ino" 2
# 4 "d:\\work\\flatbox\\firmwares_atmega32u4\\LUFA\\LUFAHybridFightstick\\LUFAHybridFightstick.ino" 2

# 6 "d:\\work\\flatbox\\firmwares_atmega32u4\\LUFA\\LUFAHybridFightstick\\LUFAHybridFightstick.ino" 2
# 7 "d:\\work\\flatbox\\firmwares_atmega32u4\\LUFA\\LUFAHybridFightstick\\LUFAHybridFightstick.ino" 2
# 8 "d:\\work\\flatbox\\firmwares_atmega32u4\\LUFA\\LUFAHybridFightstick\\LUFAHybridFightstick.ino" 2


# 9 "d:\\work\\flatbox\\firmwares_atmega32u4\\LUFA\\LUFAHybridFightstick\\LUFAHybridFightstick.ino"
/* in case you want to disable one type of gamepad */
//#define DISABLE_NSWITCH
//#define DISABLE_XINPUT



/* PINOUT (follows Nintendo naming (X=up, B=down)) */
# 34 "d:\\work\\flatbox\\firmwares_atmega32u4\\LUFA\\LUFAHybridFightstick\\LUFAHybridFightstick.ino"
/* Buttons declarations */

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
  NEUTRAL, // LEFT/UP + DOWN/RIGHT = NEUTRAL
  NEGATIVE, // LEFT/UP beats DOWN/RIGHT
  POSITIVE, // DOWN/RIGHT beats LEFT/UP
  LAST_INPUT, //Last input has priority; not a valid state if being used for initial_input
} Socd_t;
Socd_t x_socd_type = NEUTRAL; // controls left/right and up/down resolution type
Socd_t y_socd_type = NEGATIVE;
Socd_t x_initial_input, y_initial_input = NEUTRAL;

typedef enum {
  CVERT_NORMAL, // Middle input is DOWN (Hitbox style)
  CVERT_INVERT // Middle input is UP (for normal arcade style)
} CardVert_t;
CardVert_t cvert;

/* mode selectors */
bool xinput;
bool modeChanged;

void checkModeChange() {
  if (buttonStatus[12] && buttonStatus[13])
  {
    if ( !modeChanged )
    {
      State_t last_state;

      last_state = state;

      if (internalButtonStatus[2])
        state = ANALOG_MODE;
      else if (internalButtonStatus[3])
        state = RIGHT_ANALOG_MODE;
      else if (internalButtonStatus[0])
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
    joystickUP.attach(7, 0x2);
    joystickDOWN.attach(9, 0x2);
  } else { // CVERT_NORMAL (Default)
    joystickUP.attach(9, 0x2);
    joystickDOWN.attach(7, 0x2);
  }
  joystickLEFT.attach(6, 0x2);
  joystickRIGHT.attach(8, 0x2);
  buttonA.attach(MISO /*XBOX B*/, 0x2); // XBOX B
  buttonB.attach(10 /*XBOX A  */, 0x2); // XBOX A
  buttonX.attach(15 /*XBOX Y*/, 0x2); // XBOX Y
  buttonY.attach(MOSI /*XBOX X     */, 0x2); // XBOX X
  buttonL.attach(21 /*XBOX LB*/, 0x2); // XBOX LB
  buttonR.attach(19 /*XBOX RB*/, 0x2); // XBOX RB
  buttonZL.attach(20 /*XBOX LT*/, 0x2); // XBOX LT
  buttonZR.attach(18 /*XBOX RT*/, 0x2); // XBOX RT
  buttonLS.attach(5 /*XBOX LS (left analog click)*/, 0x2); // XBOX LS
  buttonRS.attach(3 /*XBOX RS (right analog click)*/, 0x2); // XBOX RS
  buttonPLUS.attach(1 /*XBOX START*/, 0x2); // XBOX START
  buttonMINUS.attach(2 /*XBOX BACK*/, 0x2); // XBOX BACK
  buttonHOME.attach(0, 0x2);

  joystickUP.interval(1 /*Debounce time in milliseconds*/);
  joystickDOWN.interval(1 /*Debounce time in milliseconds*/);
  joystickLEFT.interval(1 /*Debounce time in milliseconds*/);
  joystickRIGHT.interval(1 /*Debounce time in milliseconds*/);
  buttonA.interval(1 /*Debounce time in milliseconds*/);
  buttonB.interval(1 /*Debounce time in milliseconds*/);
  buttonX.interval(1 /*Debounce time in milliseconds*/);
  buttonY.interval(1 /*Debounce time in milliseconds*/);
  buttonL.interval(1 /*Debounce time in milliseconds*/);
  buttonR.interval(1 /*Debounce time in milliseconds*/);
  buttonZL.interval(1 /*Debounce time in milliseconds*/);
  buttonZR.interval(1 /*Debounce time in milliseconds*/);
  buttonLS.interval(1 /*Debounce time in milliseconds*/);
  buttonRS.interval(1 /*Debounce time in milliseconds*/);
  buttonPLUS.interval(1 /*Debounce time in milliseconds*/);
  buttonMINUS.interval(1 /*Debounce time in milliseconds*/);
  buttonHOME.interval(1 /*Debounce time in milliseconds*/);
}

void setup() {

  bool updateCVert = false;
  modeChanged = false;
  EEPROM.get(0, state);
  EEPROM.get(2, xinput);

  EEPROM.get(4, x_socd_type);
  EEPROM.get(6, y_socd_type);


  // setup cardinal middle button settings
  EEPROM.get(8, cvert);

  if (cvert != CVERT_NORMAL && cvert != CVERT_INVERT) {
    // Initialize to Hitbox style if EEPROM is not initialized
    cvert = CVERT_NORMAL;
    updateCVert = true;
  }

  if (digitalRead(9) == 0x0) {
    // set to standard arcade style setup
    if (cvert != CVERT_INVERT) {
      cvert = CVERT_INVERT;
      updateCVert = true;
    }
  }
  if (digitalRead(7) == 0x0) {
    // set to standard Hitbox style setup
    if (cvert != CVERT_NORMAL) {
      cvert = CVERT_NORMAL;
      updateCVert = true;
    }
  }

  if (updateCVert) {
    EEPROM.put(8, cvert);
  }

  setupPins();
  delay(500);
# 209 "d:\\work\\flatbox\\firmwares_atmega32u4\\LUFA\\LUFAHybridFightstick\\LUFAHybridFightstick.ino"
  /* set xinput mode according to held button */
  // if select is held on boot, NSWitch mode
  bool xinput_current = xinput;
  int value = digitalRead(2 /*XBOX BACK*/);
  if (value == 0x0)
  {
    xinput = false;
  }
  // if start is held on boot, XInput mode
  else {
    value = digitalRead(1 /*XBOX START*/);
    if (value == 0x0)
    {
      xinput = true;
    }
  }
  if (xinput_current != xinput) {
    // Update if changed
    EEPROM.put(2, xinput);
  }



  // TODO: add setting for inverting Up/Down


  // Configure SOCD cleaning type at startup.
  {
    Socd_t y_socd_type_current = y_socd_type;
    Socd_t x_socd_type_current = x_socd_type;

    if (digitalRead(0) == 0x0) {
      // If HOME is pressed, change to all Neutral SOCD setup
      y_socd_type = NEUTRAL;
      x_socd_type = NEUTRAL;
    }
    if (digitalRead(5 /*XBOX LS (left analog click)*/) == 0x0) {
      // If LS is pressed, change to Gafro style SOCD setup
      y_socd_type = NEGATIVE;
      x_socd_type = LAST_INPUT;
    }
    if (digitalRead(3 /*XBOX RS (right analog click)*/) == 0x0) {
      // If RS is pressed, change to Hitbox style SOCD setup
      y_socd_type = NEGATIVE;
      x_socd_type = NEUTRAL;
    }

    // Update if any changes are made
    if (x_socd_type_current != x_socd_type) EEPROM.put(4, x_socd_type);
    if (y_socd_type_current != y_socd_type) EEPROM.put(6, y_socd_type);
  }


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
      buttonStatus[14] = 128;
      buttonStatus[15] = 128;
      buttonStatus[16] = 128;
      buttonStatus[17] = 128;
      buttonStatus[0] = cleanButtonStatus[0];
      buttonStatus[1] = cleanButtonStatus[1];
      buttonStatus[2] = cleanButtonStatus[2];
      buttonStatus[3] = cleanButtonStatus[3];
      break;

    case RIGHT_ANALOG_MODE:
      buttonStatus[14] = 128;
      buttonStatus[15] = 128;
      buttonStatus[0] = 0;
      buttonStatus[1] = 0;
      buttonStatus[2] = 0;
      buttonStatus[3] = 0;

      if ((cleanButtonStatus[0]) && (cleanButtonStatus[3])) {
        buttonStatus[17] = 0;
        buttonStatus[16] = 255;
      }
      else if ((cleanButtonStatus[0]) && (cleanButtonStatus[2])) {
        buttonStatus[17] = 0;
        buttonStatus[16] = 0;
      }
      else if ((cleanButtonStatus[1]) && (cleanButtonStatus[3])) {
        buttonStatus[17] = 255;
        buttonStatus[16] = 255;
      }
      else if ((cleanButtonStatus[1]) && (cleanButtonStatus[2])) {
        buttonStatus[17] = 255;
        buttonStatus[16] = 0;
      }
      else if (cleanButtonStatus[0]) {
        buttonStatus[17] = 0;
        buttonStatus[16] = 128;
      }
      else if (cleanButtonStatus[1]) {
        buttonStatus[17] = 255;
        buttonStatus[16] = 128;
      }
      else if (cleanButtonStatus[2]) {
        buttonStatus[16] = 0;
        buttonStatus[17] = 128;
      }
      else if (cleanButtonStatus[3]) {
        buttonStatus[16] = 255;
        buttonStatus[17] = 128;
      }
      else {
        buttonStatus[16] = 128;
        buttonStatus[17] = 128;
      }

      break;

    case ANALOG_MODE:
    /* fallthrough */
    default:
      buttonStatus[16] = 128;
      buttonStatus[17] = 128;
      buttonStatus[0] = 0;
      buttonStatus[1] = 0;
      buttonStatus[2] = 0;
      buttonStatus[3] = 0;

      if ((cleanButtonStatus[0]) && (cleanButtonStatus[3])) {
        buttonStatus[15] = 0;
        buttonStatus[14] = 255;
      }
      else if ((cleanButtonStatus[1]) && (cleanButtonStatus[3])) {
        buttonStatus[15] = 255;
        buttonStatus[14] = 255;
      }
      else if ((cleanButtonStatus[1]) && (cleanButtonStatus[2])) {
        buttonStatus[15] = 255;
        buttonStatus[14] = 0;
      }
      else if ((cleanButtonStatus[0]) && (cleanButtonStatus[2])) {
        buttonStatus[15] = 0;
        buttonStatus[14] = 0;
      }
      else if (cleanButtonStatus[0]) {
        buttonStatus[15] = 0;
        buttonStatus[14] = 128;
      }
      else if (cleanButtonStatus[1]) {
        buttonStatus[15] = 255;
        buttonStatus[14] = 128;
      }
      else if (cleanButtonStatus[2]) {
        buttonStatus[14] = 0;
        buttonStatus[15] = 128;
      }
      else if (cleanButtonStatus[3]) {
        buttonStatus[14] = 255;
        buttonStatus[15] = 128;
      }
      else {
        buttonStatus[14] = 128;
        buttonStatus[15] = 128;
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
    internalButtonStatus[0] = !joystickUP.read();
    internalButtonStatus[1] = !joystickDOWN.read();
    internalButtonStatus[2] = !joystickLEFT.read();
    internalButtonStatus[3] = !joystickRIGHT.read();
  }
  if (buttonA.update()) {
    buttonStatus[4] = buttonA.fell();
  }
  if (buttonB.update()) {
    buttonStatus[5] = buttonB.fell();
  }
  if (buttonX.update()) {
    buttonStatus[6] = buttonX.fell();
  }
  if (buttonY.update()) {
    buttonStatus[7] = buttonY.fell();
  }
  if (buttonL.update()) {
    buttonStatus[8] = buttonL.fell();
  }
  if (buttonR.update()) {
    buttonStatus[9] = buttonR.fell();
  }
  if (buttonZL.update()) {
    buttonStatus[10] = buttonZL.fell();
  }
  if (buttonZR.update()) {
    buttonStatus[11] = buttonZR.fell();
  }
  if (buttonLS.update()) {
    buttonStatus[18] = buttonLS.fell();
  }
  if (buttonRS.update()) {
    buttonStatus[19] = buttonRS.fell();
  }
  if (buttonPLUS.update()) {
    buttonStatus[12] = buttonPLUS.fell();
  }
  if (buttonMINUS.update()) {
    buttonStatus[13] = buttonMINUS.fell();
  }
  if (buttonHOME.update()) {
    buttonStatus[20] = buttonHOME.fell();
  }
}


void clean_all_socd(byte *internalButtonStatus, byte *cleanButtonStatus, Socd_t x_socd_type, Socd_t y_socd_type)
{
  clean_socd(internalButtonStatus[2], &cleanButtonStatus[2], internalButtonStatus[3], &cleanButtonStatus[3], x_socd_type, &x_initial_input);
  clean_socd(internalButtonStatus[0], &cleanButtonStatus[0], internalButtonStatus[1], &cleanButtonStatus[1], y_socd_type, &y_initial_input);
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
# 469 "d:\\work\\flatbox\\firmwares_atmega32u4\\LUFA\\LUFAHybridFightstick\\LUFAHybridFightstick.ino"
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
