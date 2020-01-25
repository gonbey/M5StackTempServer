# M5StackTempServer
温度計サーバー

## 要件
温湿度値をローカルネットワークから閲覧できるようこと

## 仕様
### 機材
コントローラとしてM5Stackを利用する。
センサーとしてDHT11を使用する。

コントローラはhttpサーバーを起動、センサーの値を取得しレスポンスとして値を返す。

### ソフトウェア
実装簡略化のためArduinoおよび下記ライブラリを用いる
####Arduino library for DHT11, DHT22
https://github.com/adafruit/DHT-sensor-library

DHT11のピン配置は下記の通り
*VDD
*DATA
*OPEN
*GND
