#include "DHT.h"
#include <WiFi.h>

const char* ssid     = "セキュリティのため消しました";
const char* password = "セキュリティのため消しました";

WiFiServer server(80);
DHT dht(5, DHT11);
void setup()
{
  // 温度センサ
  dht.begin();
  // シリアル通信
  Serial.begin(115200);
  // WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // サーバー
  server.begin();
}

int value = 0;

void loop() {
  // WiFi接続待ち受け
  WiFiClient client = server.available();   // listen for incoming clients
  if (client) {                             // if you get a client,
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        // HTTPリクエスト
        if (c == '\n') {                    // if the byte is a newline character
          if (currentLine.length() == 0) {
            // 温湿度取得
            float r[2]; // 湿度, 温度
            get(r);
            // レスポンスヘッダ
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // レスポンスボディ
            char buf[1000];
            sprintf(buf, (const char*)F("<html lang=\"ja\"><body><h1>DHT11Test</h1><p>TEMP:%f</p><p>RHUM:%f</p></body>"), r[1], r[0]);
            client.print(buf);
            // レスポンス終了
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
  // WiFi終了
    client.stop();
  }
}

void get(float *r) {
  // DHT11の測定値正確性のため2秒待ちが必要
  delay(2000);
  // 
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // 有効値？
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    r[0] = 0.0;
    r[1] = 0.0;
    return;
  }
  r[0] = h;
  r[1] = t;

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%"));
  Serial.print(F("Templature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  return;
}
