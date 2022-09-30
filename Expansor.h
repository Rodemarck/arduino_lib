#ifndef EXPANSOR_H  
#define EXPANSOR_H

#include <Arduino.h>
#define bitClear(a,b) a&=~(1<<b)
#define bitSet(a,b) a|=(1<<b)
#define bitVal(a,b) !!(a & (1<< b))
#define setBit(a,b,c) {bool var_10001=bitVal(a,b);if(var_10001!=c) (c) ? bitSet(a,b); : bitClear(a,b);}
#define DELAY_PULSE 5

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
Saida* Saida::Saida(uint8_t ci_n, uint8_t latch_p, uint8_t data_p, uint8_t clock_p){
    pinMode(latch_p,OUTPUT);
    pinMode(data_p,OUTPUT);
    pinMode(clock_p,OUTPUT);
    this->ci_n = ci_n;
    this->latch_p = latch_p;
    this->data_p = data_p;
    this->clock_p = clock_p;
    this->dados = (uint8_t*) malloc(ci_n * sizeof(uint8_t));
    for(uint8_t i = 0;i < ci_n; i++)
        this->dados[i] = 0;
    this->atualiza();
}
void Saida::escreve(uint8_t p, bool val){
    uint8_t c = p / 8;
    uint8_t k = p % 8;
    Saida* t = Saida::GetInstance();
    setBit(t->dados[c],k,val);
    t->atualiza();
}
bool Saida::valor(uint8_t p){
    uint8_t c = p / 8;
    uint8_t k = p % 8;
    return !!(Saida::GetInstance()->dados[c] & (1 << k));
}
void Saida::atualiza(){
    Saida* t = Saida::GetInstance();
    digitalWrite(t->latch_p, LOW);
    uint8_t i = ci_n - 1;
    for(; i >=0; i--)
        shiftOut(t->data_p, t->clock_p, LSBFIRST, t->dados[i]);
    digitalWrite(t->latch_p, HIGH);
}
Saida* Saida::GetInstance(){
    return Saida::singleton_;
}
void Saida::begin(uint8_t ci_n, uint8_t latch_p, uint8_t data_p, uint8_t clock_p){
    if(Saida::singleton_ != nullptr){
        free(Saida::singleton_->dados);
        free(Saida::singleton_);
    }
    Saida::singleton_ = new Saida::Saida(ci_n, latch_p, data_p, clock_p));
}

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
}
Entrada* Entrada::Entrada(uint8_t ci_n, uint8_t latch_p, uint8_t data_p, uint8_t clock_p, uint8_t enable_p,void (func*)(uint8_t*,uint8_t)){
    pinMode(latch_p,OUTPUT);
    pinMode(data_p,INPUT);
    pinMode(clock_p,OUTPUT);
    pinMode(enable_p,OUTPUT);
    this->ci_n = ci_n;
    this->enable_p = enable_p;
    this->latch_p = latch_p;
    this->data_p = data_p;
    this->clock_p = clock_p;
    this->dados = (uint8_t*) malloc(ci_n * sizeof(uint8_t));
    for(uint8_t i = 0;i < ci_n; i++)
        this->dados[i] = 0;
    this->atualiza();
}
void Entrada::verifica(bool check){
    if(!check) return;
    Entrada::GetInstance()->func(e->dados,e->ci_n);
}
void Entrada::verifica(){
    Entrada::verifica(Entrada::atualiza());
}
bool Entrada::valor(uint8_t p){
    uint8_t c = p / 8;
    uint8_t k = p % 8;
    return !!(Entrada::GetInstance()->dados[c] & (1 << k));
}

bool Entrada::atualiza(){
    Entrada* e = Entrada::GetInstance();
    digitalWrite(e->enable_p,HIGH);
    digitalWrite(e->latch_p,LOW);
    delayMicroseconds(DELAY_PULSE);
    digitalWrite(e->latch_p,HIGH);
    digitalWrite(e->enable_p,LOW);
    uint8_t val;
    bool aux;
    bool mud = false;
    for(uint8_t c = e->ci_n-1; c>=0; c--){
        val = 0
        for(uint8_t k = 7; k>=0; k--){
            aux = digitalRead(e->data_p);
            setBit(val,k,aux);
            digitalWrite(e->clock_p,LOW);
            delayMicroseconds(DELAY_PULSE);
            digitalWrite(e->clock_p,HIGH);
        }
        if(e->dados[c] != val) {
            e->dados[c] = val;
            mud = true;
        }
    }
    return mud;
}

#endif