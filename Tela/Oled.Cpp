#include "./Oled.hpp"

Tela::Tela(){
    Tela::Tela(SCREEN_WIDTH,SCREEN_HEIGHT);
}

Tela::Tela(int largura, int altura){
    static led  display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    this->led = &led;
    if(!this->led->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    this->led->setTextSize(1);
    this->led-> setTextColor(BRANCO);
    this->led->fillScreen(PRETO);
    this->led->display();
    this->altura = altura;
    this->largura = largura;
}