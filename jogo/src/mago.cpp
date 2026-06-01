// mago.cpp
#include "../headers/mago.hpp"
#include <iostream>

Mago::Mago(std::string nome, int vidaMax, int manaMax, int velocidade, TipoMago tipo)
    : Personagem(nome, vidaMax, velocidade), mana(manaMax), manaMaxima(manaMax), tipo(tipo) {}

void Mago::atacar(Entidade* alvo) {
    // ataca com a primeira magia desbloqueada disponível
    for (int i = 0; i < skillTree.getTamanho(); i++) {
        Magia* m = skillTree.getMagia(i);
        if (m->estaDesbloqueada() && gastarMana(m->getCustoMana())) {
            m->lancar(this, alvo);
            return;
        }
    }
    std::cout << nome << " não tem mana suficiente!\n";
}

void Mago::usarMagia(int indice, Entidade* alvo) {
    Magia* m = skillTree.getMagia(indice);
    if (!m) { std::cout << "Magia inválida.\n"; return; }
    if (!m->estaDesbloqueada()) { std::cout << "Magia bloqueada.\n"; return; }
    if (!gastarMana(m->getCustoMana())) { std::cout << "Mana insuficiente.\n"; return; }
    m->lancar(this, alvo);
}

void Mago::receberDano(int dano) {
    // agilidade reduz dano em 10% por ponto acima de 5
    int reducao = (atributos.getAgilidade() - 5) * 2;
    int danoFinal = std::max(1, dano - reducao);
    setVida(vida - danoFinal);
}

void Mago::exibirStatus() const {
    std::cout << "[ " << nome << " ] "
              << "HP: " << vida << "/" << vidaMaxima << " "
              << "MP: " << mana << "/" << manaMaxima << " "
              << "Nv: " << nivel << "\n";
}

void Mago::regenerarMana() {
    mana = std::min(manaMaxima, mana + atributos.getRegeneracao());
}

bool Mago::gastarMana(int custo) {
    if (mana < custo) return false;
    mana -= custo;
    return true;
}

int Mago::getMana()        const { return mana; }
int Mago::getManaMaxima()  const { return manaMaxima; }
TipoMago Mago::getTipo()   const { return tipo; }