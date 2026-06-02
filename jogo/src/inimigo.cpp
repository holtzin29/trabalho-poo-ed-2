#include "../headers/inimigo.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

Inimigo::Inimigo(string nome, int vidaMax, int dano,
                 int defesa, int xp, TipoInimigo tipo)
    : Entidade(nome, vidaMax),
      danoBase(dano), defesa(defesa), xpRecompensa(xp),
      tipo(tipo), congelado(false), turnosQueimando(0), danoQueimadura(0) {}

void Inimigo::atacar(Entidade* alvo) {
    if (congelado) {
        cout << nome << " esta congelado e nao pode atacar!\n";
        congelado = false;
        return;
    }
    alvo->receberDano(danoBase);
    cout << nome << " ataca " << alvo->getNome()
              << "! Dano: " << danoBase << "\n";
}

void Inimigo::receberDano(int dano) {
    int danoFinal = max(1, dano - defesa);
    setVida(vida - danoFinal);
    cout << nome << " recebe " << danoFinal << " de dano"
              << (defesa > 0 ? " (defesa: -" + to_string(defesa) + ")" : "")
              << ". HP: " << vida << "/" << vidaMaxima << "\n";
}

void Inimigo::exibirStatus() const {
    cout << "[ " << nome << " ] HP: "
              << vida << "/" << vidaMaxima << "\n";
}

void Inimigo::aplicarCongelamento() {
    congelado = true;
    cout << nome << " foi congelado!\n";
}

void Inimigo::aplicarQueimadura(int dano, int turnos) {
    danoQueimadura = dano;
    turnosQueimando = turnos;
    cout << nome << " esta em chamas por " << turnos << " turnos!\n";
}

void Inimigo::processarEfeitos() {
    if (turnosQueimando > 0) {
        setVida(vida - danoQueimadura);
        turnosQueimando--;
        cout << nome << " sofre " << danoQueimadura
                  << " de queimadura! Turnos restantes: "
                  << turnosQueimando << "\n";
    }
}

int Inimigo::getXpRecompensa() const { return xpRecompensa; }
TipoInimigo Inimigo::getTipo()  const { return tipo; }
bool Inimigo::estaCongelado()   const { return congelado; }