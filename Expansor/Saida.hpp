#ifndef SAIDA_H  
#define SAIDA_H

#include <Arduino.h>
#include "./funcExpansor.h"

class Saida{
protected:
    Saida(uint8_t ci_n, uint8_t latch_p, uint8_t data_p, uint8_t clock_p);
    static Saida* singleton_ = nullptr;
    uint8_t ci_n;
    uint8_t latch_p;
    uint8_t data_p;
    uint8_t clock_p;
    uint8_t* dados;
    static Saida *GetInstance();
public:
    Saida(Saida &other) = delete;
    void operator=(const Saida &) = delete;
    void begin(uint8_t ci_n, uint8_t latch_p, uint8_t data_p, uint8_t clock_p);
    void atualiza();
    void escreve(uint8_t p, bool val);
    bool valor(uint8_t p);
};

#endif
