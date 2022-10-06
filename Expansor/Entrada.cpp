#include "./Entrada.hpp"

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