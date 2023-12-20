## LUFA Switch/XInput ハイブリッドアケコンファームウェア

このファームウェアは[CrazyRedMachine](https://github.com/CrazyRedMachine)様による
[LUFAHybridFightstick](https://github.com/CrazyRedMachine/LUFAHybridFightstick)のergoSHIFT向け改造版になります。

## 謝辞 

このファームは[CrazyRedMachine](https://github.com/CrazyRedMachine)様による
[LUFAHybridFightstick](https://github.com/CrazyRedMachine/LUFAHybridFightstick)のフォークで、
[fluffymadness' ATMega32U4-Switch-Fightstick](https://github.com/fluffymadness/ATMega32U4-Switch-Fightstick)
と [bootsector's XInputPadMicro](https://github.com/bootsector/XInputPadMicro)をベースに作成されています。

このフォークではergoSHIFTに対応するため、以下の修正を入れています。

* ergoSHIFT の配線に合わせたキーマップの修正
* アナログスティック対応コードの削除
* 設定関連（SOCDクリーナー設定等）のボタンを他のergoSHIFTと合わせるためマッピング変更
    * SOCDクリーナー設定は起動時のみに変更し、プリセットの選択のみとしました
      （全ニュートラル、Hitbox風、ガフロコン風）
    * 追加で上下キーの反転機能を追加。格ゲー以外のゲームでの利用向け。

## 機能

### ゲームパッドモード設定

起動時（USB接続時もしくはリセットボタン短押し時）に ”Select” を押したまま起動することで
ニンテンドースイッチコントローラーとして動作します。

起動時（USB接続時もしくはリセットボタン短押し時）に ”Start” を押したまま起動することで
XInputコントローラーとして動作します。

ゲームパッドモードは保持されるため、コントローラーの切断時でも保持されます。起動時に何も押さなければ
以前設定したモードで動作します。

### 方向キー設定

方向キーのモードは動作中に動的に切り替えが可能です。START+SELECT+(←／↑／→) のキーコンボで設定できます。

* ↑： 十字キーとして動作
* ←： 疑似左アナログスティックとして動作（十字キーを左アナログスティックとしてマッピング）
* →： 疑似右アナログスティックとして動作（十字キーを右アナログスティックとしてマッピング）

方向キーモード設定も電源オフでも保持されます。

以下にある上限反転をしている場合は上下反転された状態での↑を利用してください。

### アナログ入力サポート機能

ergoSHIFTにはアナログ入力がないため機能削除しました。

### ホームボタンシミュレート機能

ergoSHIFTにはHomeボタンがあるため機能削除しました。

### SOCD クリーナー設定

* 起動時にHOME(PS)押下＝全ニュートラル
* 起動時にR3(RS)押下＝ヒットボックス風SOCDクリーナー（↑＋↓＝↑、←＋→＝ニュートラル）
    * 一部公式大会等でも許可されたモードです（大会毎にルールが違う可能性があるためルール確認のこと）
* 起動時にL3(LS)押下＝ガフロコン風SOCDクリーナー（↑＋↓＝↑、←＋→＝後勝ち）
    * 一部公式大会等では禁止されているモードです。

起動時設定なので、USB接続時か、リセットボタンを使うことで設定可能です。

### 上下入力反転設定

ergoSHIFTはHitbox風コントローラーのため、上下キーのレイアウトが少々変わっているため、格ゲー以外では
利用しづらい為、格ゲー以外で利用するときのために上下反転する機能を追加しました。

* 起動時に上ボタン（十字キーの親指のボタン）を押下＝上下反転
* 起動時に下ボタン（十字キーの真ん中のボタン）を押下＝反転解除

## ファームウェアビルド手順

1. [Arduino IDE](https://www.arduino.cc/en/software)をダウンロードしてインストールしてください。
2. Arduino IDE内のライブラリ管理メニューからBounce2ライブラリをインストールしてください。
3. ファイル→環境設定から追加のボードマネージャURLに
   `https://github.com/CrazyRedMachine/Arduino-Lufa/raw/master/package_arduino-lufa_index.json` を追加。
4. ツール→ボード→ボードマネージャからLUFA AVR Boardをインストール
5. ツール→ボード以下で Arduino Leonardo (LUFA) を選択
    * Pro-MicroはArduino Leonardoの互換ボードなのでこちらで動作します
6. マイコンボードに書き込みで書き込み出来ます。
    * 初回の書き込みは特に何もしなくても上記設定をして付属の.inoを書き込めば書き込めますが2度め以降は
      書き込み出来ません。これはHIDモードで動作するファームはArduino IDEからのリセット要求に対応できない
      ためです。2回め以降の書き込みを行う場合は Arduino IDE で書き込みボタンを押してからログで
      PORTS {} / {} => {} といったような内容が出力され始めた段階でリセットボタンを押下（Pro-Micro Qwiic
      の場合はリセットボタンをダブルクリック）することで書き込みが出来ます。
    * 上記ログを表示するためには Arduino IDE の環境設定で「より詳細な情報を表示する」にチェックを入れると
      出ます
    * タイミングが難しい場合は以下に記載している .hex ファイルを取り出して QMK Toolbox で書き込みする方法も
      あります。

### ファームの書き込み方法

USB HID対応のファームをAVRボードに書き込みすると、Arduino IDEから書き込み時の自動リセットを受け付けなくなります。
一度ファームを書き込んだ後は書き込み処理時に手動でリセット（ergoSHIFTではSW_RST1）を押す必要があります。
Sparkfun Qwiic Pro Micro 5Vを使った場合はリセットをダブルクリックすることで書き込みモードに入れることが出来ます。

Arduino IDEでは自分で書き込みのタイミングを制御出来ないため、2回目以降はVSCodeのArduinoプラグインを使って
コンパイルだけ行い、.hex ファイルを取り出して [QMK Toolbox](https://github.com/qmk/qmk_toolbox)を利用して
書き込む方法がおすすめです。
VSCodeは[こちら](https://azure.microsoft.com/ja-jp/products/visual-studio-code/)からダウンロードできます。
インストールが終わったらプラグインからArduinoを検索しマイクロソフト製のArduinoプラグインをインストール。
Arduino IDEで上記の設定が一通り終わった後にこのフォルダをVSCodeで開くことでVSCodeからのコンパイルが可能です。
.inoファイルを開いてVSCodeのコマンドパレットから Arduino: Verify を選択するとコンパイルされ、buildフォルダに
.hexファイルが生成されます。

.hexファイルは[QMK Toolbox](https://github.com/qmk/qmk_toolbox)を使って書き込みが出来ます

1. QMK Toolboxを起動したら、右上のOPENから上記で作成した.hexファイルを選択してください。
2. 右上のドロップダウンから ATMega32u4を選択してください
3. Pro Micro のリセットボタンを押し（Qwiic Pro Micro USB-Cの場合はリセットをダブルクリックし）、QMK Toolbox
   のログ上に黄色の文字で"Caterina device connected (usbser): ~~~"と出たら右上のFlashボタンを押下すると
   書き込みが開始されます。書き込み完了後に自動でボードがリセットされ新しいファームで立ち上がります。

こちらの方法は追加のソフトのセットアップが必要ですが、コンパイルと書き込みを分けて行えるため、リセットのタイミング
が図りやすいため失敗し辛い為おすすめです（ただし初回書き込みはArduino IDEでないとうまくいかない事があったため、
新品のPro Microを書き込む場合はArduino IDEで行う事をおすすめします）

## ピン配置

.ino ファイルで設定可能です。

こちらのリポジトリ内のファイルではすでに ergoSHIFT 向けに設定済みです。

```C
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
```

## 寄付

もしこのプロジェクトが参考担った場合はベースとなったプロジェクトにいって寄付すると大本のプロジェクトの
人たちが喜びます。
