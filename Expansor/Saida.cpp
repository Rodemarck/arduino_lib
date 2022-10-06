#include "./Saida.hpp"

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
