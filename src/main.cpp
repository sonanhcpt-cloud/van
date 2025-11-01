#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "chat_ui.h"
#include "voice_stt.h"
#include "voice_tts.h"

TFT_eSPI tft = TFT_eSPI();

const char* ssid = "WIFI_TEN";
const char* password = "WIFI_MATKHAU";

// Bạn thay bằng key của mình
const String GOOGLE_TTS_KEY = "YOUR_GOOGLE_API_KEY";
const String STT_ENDPOINT = "https://speech.googleapis.com/v1/speech:recognize?key=" + GOOGLE_TTS_KEY;
const String TTS_ENDPOINT = "https://texttospeech.googleapis.com/v1/text:synthesize?key=" + GOOGLE_TTS_KEY;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  tft.println("Dang ket noi Wi-Fi...");

  while (WiFi.status() != WL_CONNECTED) delay(500);

  tft.fillScreen(TFT_BLACK);
  tft.println("Xin chao! Tro ly XiaoZhi VN");
  delay(1000);
  chatUI.begin(&tft);
}

void loop() {
  String userSpeech = recognizeSpeech(STT_ENDPOINT);
  if (userSpeech.length() > 0) {
    chatUI.addMessage("Bạn", userSpeech);
    String reply = "Xin chào, tôi là XiaoZhi!"; // sau này có thể thay bằng AI trả lời
    chatUI.addMessage("XiaoZhi", reply);
    speakText(reply, TTS_ENDPOINT);
  }
}
