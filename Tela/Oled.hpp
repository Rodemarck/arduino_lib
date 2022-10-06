#ifndef OLED_H
#define OLED_H

#include "./../import.h"

#define SCREEN_WIDTH    128     // OLED display width, in pixels
#define SCREEN_HEIGHT   64      // OLED display height, in pixels
#define OLED_RESET      4       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS  0x3C    ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define PRETO SSD1306_BLACK
#define BRANCO SSD1306_WHITE  

class Tela{
public:
    Adafruit_SSD1306* led;
    int largura;
    int altura;
    Tela();
    Tela(int largura, int altura);
};


#endif