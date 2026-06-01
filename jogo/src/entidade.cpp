#include <iostream>
#include "posicao.hpp"
#include "entidade.hpp"

using namespace std;

Entidade::Entidade(string nome, int vidaMax, int nivel)
    : nome(nome), vidaMaxima(vidaMax), vida(vidaMax), nivel(nivel), vivo(true) {}

void Entidade::setVida(int v)
{
    vida = v;
    if (vida <= 0)
    {
        vida = 0;
        vivo = false;
    }
    if (vida > vidaMaxima)
        vida = vidaMaxima;
}

int Entidade::getVida() {
     return vida;
 }
int Entidade::getVidaMaxima(){ 
    return vidaMaxima;
 }
int Entidade::getNivel(){ 
    return nivel; 
}
bool Entidade::estaVivo() {
     return vivo;
     }
string Entidade::getNome() { 
    return nome; 
}
Posicao &Entidade::getPosicao() {
     return pos;
     }
Atributos &Entidade::getAtributos() { 
    return atributos; 
}

void Entidade::setVidaMaxima(int v) {
    vidaMaxima = v;
}

void Entidade::subirNivel()
{
    nivel++;
    vidaMaxima += 10;
    vida = vidaMaxima; // cura ao subir de nível
}
