こちらのファームはArduino Pro Micro 等のATMega32u4ベースの制御基盤で利用するためのファームになります。

Flatbox-ACR [rev1.1](../hardware-rev1.1) に利用できます。

## [オリジナル](https://github.com/jfedor2/flatbox/blob/master/firmware-atmega32u4)からの変化点

* SOCDクリーナー設定機能の追加（ヒットボックスモード、ガフロコンモード、全ニュートラルモード対応）
    * 接続時／リセット時にR3を押すとHitbox風SOCDクリーナーになります
    * 接続時／リセット時にL3を押すとガフロコン風SOCDクリーナーになります
    * 接続時／リセット時にPSを押すと全ニュートラルモードになります。
    * 設定はEEPROMに保存され電源を切っても保持されます。
* 上下反転モード機能の追加（格ゲー以外のゲーム用）
    * 接続時／リセット時にDOWNキーを押すとヒットボックス風のレイアウトになります
    * 接続時／リセット時にUPキーを押すと上下キー反転になります。
    * 設定はEEPROMに保存され電源を切っても保持されます。

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
一度ファームを書き込んだ後は書き込み処理時に手動でリセット（Flatbox ACRではSW_RST1）を押す必要があります。
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
