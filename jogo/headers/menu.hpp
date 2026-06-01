#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using namespace std;
using namespace sf;

class Menu {
private:
    int itemSelecionado;
    Font fonte;
    vector<Text> opcoes;

public:
    Menu(float largura, float altura);

    void desenhar(RenderWindow& janela);

    void moverCima();

    void moverBaixo();

    int getPressionado();
};

#endif