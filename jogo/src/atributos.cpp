#include "../headers/atributos.hpp"
using namespace std;
// Define static member variable
int Atributos::totalCriados = 0;

// da pra fazer construtores assim tambem ao inves do this->
Atributos::Atributos() : forca(5), agilidade(10), regeneracao(1) {
    Atributos::totalCriados += 1;
}

Atributos::Atributos(int f, int v, int r) : forca(f), agilidade(v), regeneracao(r) {
    Atributos::totalCriados += 1;
}

int Atributos::getForca() {
    return forca;
}

int Atributos::getAgilidade() {
    return agilidade;
}

int Atributos::getRegeneracao() {
    return regeneracao;
}

void Atributos::setForca(int f) {
    forca = f;
}

void Atributos::setAgilidade(int v) {
    agilidade = v;
}

void Atributos::setRegen(int r) {
    regeneracao = r;
}