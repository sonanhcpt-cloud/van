#include <HTTPClient.h>
#include <ArduinoJson.h>

void speakText(String text, String endpoint) {
  HTTPClient http;
  http.begin(endpoint);
  http.addHeader("Content-Type", "application/json");

  String body = "{\"input\":{\"text\":\"" + text + "\"},"
                "\"voice\":{\"languageCode\":\"vi-VN\",\"name\":\"vi-VN-Wavenet-F\"},"
                "\"audioConfig\":{\"audioEncoding\":\"MP3\"}}";

  int httpCode = http.POST(body);
  if (httpCode == 200) {
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, http.getString());
    String audioContent = doc["audioContent"];
    // phát file audioContent (MP3 base64) -> phần này cần thêm decoder (sau này mình hướng dẫn)
  }
  http.end();
}
