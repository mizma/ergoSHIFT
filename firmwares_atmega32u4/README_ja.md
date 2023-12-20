# ATMEGA32U4 マイコン用ファームウェア

現在 ATMEGA32U4マイコン製 AVRボード（5Vバージョン）用のファームウェアは２種類あります（3.3V版は非対応）。
どちらのファームもSOCDクリーナーや上下ボタン反転機能は同様に動きます。

以下対応機能表になります。

Firmware            | [DINPUT](DINPUT)      | [LUFA](LUFA)          |
------------------- | :-------------------: | :-------------------: |
DInput              | **YES**               | NO                    |
XInput              | NO                    | **YES**               |
PS3                 | **YES**               | NO                    |
Switch              | NO                    | **YES**               |
SOCD                | Hitbox,Gafro,NEUTRAL  | Hitbox,Gafro,NEUTRAL  |
Vertical Inversion  | **YES**               | **YES**               |
DPAD emulation      | **YES**               | **YES**               |
Fake Left Stick     | NO                    | **YES**               |
Fake Right Stick    | NO                    | **YES**               |

## 各種設定 

以下の表に各ファームウェアが対応する設定機能と操作方法を示します。
設定はすべて電源オフしても保持されます。

| ファーム          |                       | DINPUT                | LUFA                  |
| :---------------- | :-------------------: | :---------------:     | :-------------------: |
| 上下反転          | 標準                  | ↓ + リセット          | ↓ + リセット          |
|                   | 上下反転              | ↑ + リセット          | ↑ + リセット          |
| SOCDクリーナー    | Hitboxモード          | R3(RS) + リセット     | R3(RS) + リセット     |
|                   | ガフロコンモード      | L3(LS) + リセット     | L3(LS) + リセット     |
|                   | 全ニュートラル        | PS(HOME) + リセット   | PS(HOME) + リセット   |
| 入力モード変更    | Xinput                | 非対応                | "Start" + リセット    |
|                   | Switch                | 非対応                | "Select" + リセット   |
|                   | DInput/PS3            | デフォルト            | 非対応                |
| 方向入力モード    | 十字キー              | デフォルト            | UP+START+SELECT       |
|                   | 左アナログスティック  | 非対応                | LEFT+START+SELECT     |
|                   | 右アナログスティック  | 非対応                | RIGHT+START+SELECT    |

リセットキーを使った設定は対応したキーを押したままリセットキーを一回短押しして、コントローラーが
再接続するまで待ってください。接続完了時に押されていたキーを判定して設定変更が行われるので、対応キーを
離すのが早すぎると設定されない場合があります。

キーコンボの[カンニングペーパー](Flatbox-ACR_Hotkey_Cheatsheet.pdf)を作ったので覚えるのが面倒な場合は
こちらを印刷して裏側等に挟み込んでご利用ください（印刷サイズ：B5）

## [DINPUT](./DINPUT/)

こちらのファームはオリジナルのFlatboxのファーム(Dinput)をベースにしたものになります。
シンプルなファームでPS3まで対応しているためPC(DInput)とPS3を利用する場合はこちらをご利用ください。

## [LUFA](./LUFA/)

こちらは[CrazyRedMachine](https://github.com/CrazyRedMachine)様作成の
[LUFAHybridFightstick](https://github.com/CrazyRedMachine/LUFAHybridFightstick)をベースにFlatbox ACR用にカスタマイズ
したファームになります。Xinputとニンテンドースイッチに対応しています（XinputはPCのみ対応。XBoxには認証チップ
が必要なため非対応になります）。

スイッチモードとXInputモードはキーコンボで設定切り替え可能です（上記表参照）。
また、疑似アナログスティック入力に対応しています。

PCで利用する際にDInput非対応のソフトを利用する場合やニンテンドースイッチで利用する場合にこちらをお使いください。
