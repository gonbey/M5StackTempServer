# M5StackTempServer
温度計サーバー

## 仕様
### 機材
コントローラとしてM5Stackを利用する。
センサーとしてDHT11を使用する。
仕様:<https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf>

コントローラはhttpサーバーを起動、センサーの値を取得しレスポンスとして値を返す。

### ソフトウェア
#### ライブラリ
実装簡略化のためArduinoおよび下記ライブラリを用いる
####Arduino library for DHT11, DHT22
https://github.com/adafruit/DHT-sensor-library
####Arduino WiFi library
https://www.arduino.cc/en/Reference/WiFi  

#### 仕様
WiFiに接続する  
以下を繰り返す  
  http接続を待ち受ける  
  リクエストが来たら  
    温度センサの値を取得する  
    レスポンスを返す  

## メモ
### その他ハードウェア仕様
#### DHT11
##### できること
20-90%の湿度測定　誤差+-5%  
0-50度の温度測定  誤差+-2度  

##### ピン
1. VDD(3-5.5V)  
1. DATA(バス、電源投入後1秒間はデータを送信しない。)  
1. OPEN  
1. GND(100μFのパスコンを準備しておく)  
OPENは使用しない。  

バスはVDDでプルアップする。  
##### 通信  
シリアル方式  
フォーマットは  
1. 相対湿度整数(8bit)  
1. 相対湿度浮動小数(8bit)  
1. 温度整数(8bit)  
1. 温度浮動小数(8bit)  
1. チェックサム(8bit、上記4フォーマットの加算した数の後ろ8bit)  

開始、コントローラからスタートビットを送る(最低18μS)  
コントローラ側をハイインピーダンスにする(20-40μS)  
センサーが開始信号を送る(LOW80μS->HIGH80μS)  
データ送信(各ビットはLOW50μS->HIGH(26-28μSで0, 70μSで1、8bit分繰り返し)  
センサーが終了信号を送る(50μS)  
終了、コントローラはハイインピーダンスのまま次の転送に備える。  

#M5Stack仕様  
ESP32-D0WDQ6ベース <https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf>  
入力電圧2.2-3.6V、推奨3.3V
最大32割り込みベクタ設定可能
520KB分データと命令かける

メモリマップドIO？
GPIOメモリ範囲は0x3FF4_4000 0x3FF4_4FFF 4 KB

デジタルIO可能  
GPIOはM5Stack直結  
今回センサー接続は5番を利用(プルアップ、デジタルIO以外の機能と共有されてるため注意する)  
