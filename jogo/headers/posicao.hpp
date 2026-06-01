#ifndef POSICAO_HPP
#define POSICAO_HPP

#define POSICAO_INICIAL_X
#define POSICAO_INICIAL_Y
#include <iostream>
#include <tuple>
using namespace std;
class Posicao {
    private:
    int x;
    int y;
    
    public:
    Posicao();
    Posicao(int a, int b);
    void setPos(int x, int y);
    int getX();
    int getY();
};

#endif