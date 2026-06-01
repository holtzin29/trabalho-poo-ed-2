#include "../headers/posicao.hpp"
#include <iostream>

Posicao::Posicao() : x(0), y(0) {

}
Posicao::Posicao(int x, int y) : x(x), y(y) {
    
}
void Posicao::setPos(int a, int b) {
    this->x = a;
    this->y = b;
}

int Posicao::getX() {
    return x;
}

int Posicao::getY() {
    return y;
}

