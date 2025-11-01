#include <TFT_eSPI.h>

class ChatUI {
  TFT_eSPI* _tft;
  int y = 40;
public:
  void begin(TFT_eSPI* tft) {
    _tft = tft;
    _tft->fillScreen(TFT_BLACK);
    _tft->setTextColor(TFT_WHITE);
    _tft->setTextSize(2);
  }

  void addMessage(String who, String text) {
    _tft->setCursor(10, y);
    if (who == "Bạn") _tft->setTextColor(TFT_CYAN);
    else _tft->setTextColor(TFT_YELLOW);
    _tft->println(who + ": " + text);
    y += 30;
    if (y > 220) {
      _tft->fillScreen(TFT_BLACK);
      y = 40;
    }
  }
};

ChatUI chatUI;
