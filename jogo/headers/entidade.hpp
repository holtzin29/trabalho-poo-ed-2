
#ifndef ENTIDADE_HPP
#define ENTIDADE_HPP
#include <iostream>
#include "posicao.hpp"
#include "atributos.hpp"

#define NIVEL_BASE 1

using namespace std;

// classe totalmente abstrata para tambem usarmos para os inimigos

class Entidade
{
protected: // protected pois vamos herdar essa classe
    Posicao pos;
    Atributos atributos;
    int vida; // vida atual
    int vidaMaxima;
    int nivel;
    bool vivo;
    string nome;

public:
    Entidade(string nome, int vidaMax, int nivel = 1);
    virtual ~Entidade() {}

    virtual void atacar(Entidade *alvo) = 0;
    virtual void receberDano(int dano) = 0;
    virtual void exibirStatus() const = 0;

    // mago e inimigo vao sobrescrever os acima
    void setVida(int v);
    int getVida();
    int getVidaMaxima();
    int getNivel();
    bool estaVivo();
    string getNome();
    Posicao &getPosicao();
    Atributos &getAtributos();
    void setVidaMaxima(int v);
    void subirNivel();
};
#endif