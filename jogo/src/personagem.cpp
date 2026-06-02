// personagem.cpp
#include "../headers/personagem.hpp"
#include <iostream>
using namespace std;

Personagem::Personagem(string nome, int vidaMax, int velocidade)
    : Entidade(nome, vidaMax), velocidade(velocidade), pontosHabilidade(0) {}

void Personagem::receberDano(int dano) {
    setVida(vida - dano);
}

void Personagem::ganharPontosHabilidade(int pontos) {
    pontosHabilidade += pontos;
    skillTree.adicionarPontos(pontos);
}

bool Personagem::desbloquearHabilidade(int indice) {
    return skillTree.desbloquearMagia(indice);
}

SkillTree& Personagem::getSkillTree() { return skillTree; }
int Personagem::getVelocidade() const  { return velocidade; }