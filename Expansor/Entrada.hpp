#ifndef ENTRADA_H  
#define ENTRADA_H

#include <Arduino.h>
#include "./funcExpansor.h"

class Entrada{
protected:
    Entrada(uint8_t ci_n, uint8_t latch_p, uint8_t data_p, uint8_t clock_p, uint8_t enable_p, void (func*)(uint8_t*,uint8_t));
    static Entrada* singleton_ = nullptr;
    void (func*)(uint8_t*,uint8_t);
    uint8_t ci_n;
    uint8_t latch_p;
    uint8_t data_p;
    uint8_t clock_p;
    uint8_t enable_p;
    uint8_t* dados;
    static Entrada *GetInstance();
public:
    Entrada(Entrada &other) = delete;
    void operator=(const Entrada &) = delete;
    void begin(uint8_t ci_n, uint8_t latch_p, uint8_t data_p, uint8_t clock_p, uint8_t enable_p, void (func*)(uint8_t*,uint8_t));
    bool atualiza();
    void verifica(bool check);
    void verifica();
    bool valor(uint8_t p);
};

#endif
