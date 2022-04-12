#include <Arduino.h>

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
    void escreve(int p, bool val);
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
    int i = 0;
    for(;i < ci_n; i++)
        this->dados[i] = 0;
}
void Saida::escreve(int p, bool val){
    int c = p / 8;
    int k = p % 8;
    if(val)
        bitSet(this->dados[c],p);
    else
        bitClear(this->dados[c],p);
}
void Saida::atualiza(){
    digitalWrite(this->latch_p, LOW);
    var i = ci_n - 1;
    for(; i >=0; i--)
        shiftOut(this->data_p, this->clock_p, LSBFIRST, this->dados[i]);
    digitalWrite(this->latch_p, HIGH);
}
Saida* Saida::GetInstance(){
    return singleton_;
}

class Entrada{

}