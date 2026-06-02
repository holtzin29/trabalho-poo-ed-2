#include "../headers/magias/magias_fogo.hpp"
#include <iostream>
#include <algorithm>
using namespace std;
// --- BolaDeFogo ---
BolaDeFogo::BolaDeFogo() : Magia("Bola de Fogo", 10, 25) {}

void BolaDeFogo::lancar(Entidade* lancador, Entidade* alvo) {
    alvo->receberDano(danoBase);
    cout << lancador->getNome() << " lança Bola de Fogo em "
              << alvo->getNome() << "! Dano: " << danoBase << "\n";
}

string BolaDeFogo::getDescricao() const {
    return "Projetil de fogo. Dano: " + to_string(danoBase);
}

// --- Queimadura ---
Queimadura::Queimadura() : Magia("Queimadura", 15, 10), turnosRestantes(3) {}

void Queimadura::lancar(Entidade* lancador, Entidade* alvo) {
    // aplica dano imediato + sinaliza efeito de turno (controlado pelo loop de jogo)
    turnosRestantes = 3;
    alvo->receberDano(danoBase);
    cout << lancador->getNome() << " aplica Queimadura em "
              << alvo->getNome() << "! Dano: " << danoBase
              << " por " << turnosRestantes << " turnos.\n";
}

string Queimadura::getDescricao() const {
    return "Dano ao longo do tempo por 3 turnos.";
}

int Queimadura::getTurnosRestantes() const { return turnosRestantes; }

// --- ExplosaoFogo ---
ExplosaoFogo::ExplosaoFogo() : Magia("Explosao de Fogo", 25, 40) {}

void ExplosaoFogo::lancar(Entidade* lancador, Entidade* alvo) {
    int dano = static_cast<int>(danoBase * 1.5f);
    alvo->receberDano(dano);
    cout << lancador->getNome() << " causa uma Explosao de Fogo! Dano: " << dano << "\n";
}

string ExplosaoFogo::getDescricao() const {
    return "Explosao em area. Dano: " + to_string(static_cast<int>(danoBase * 1.5f));
}

// --- Inferno ---
Inferno::Inferno() : Magia("Inferno", 40, 60) {}

void Inferno::lancar(Entidade* lancador, Entidade* alvo) {
    alvo->receberDano(danoBase);
    // cura o lancador em 20% do dano causado
    int cura = static_cast<int>(danoBase * 0.2f);
    lancador->setVida(lancador->getVida() + cura);
    cout << lancador->getNome() << " invoca o Inferno! Dano: " << danoBase
              << " | Cura: " << cura << "\n";
}

string Inferno::getDescricao() const {
    return "Dano alto + recupera 20% do dano como vida.";
}

// --- ApocalipseDeFogo ---
ApocalipseDeFogo::ApocalipseDeFogo() : Magia("Apocalipse de Fogo", 70, 100) {}

void ApocalipseDeFogo::lancar(Entidade* lancador, Entidade* alvo) {
    alvo->receberDano(danoBase);
    cout << " " << lancador->getNome()
              << " desencadeia o APOCALIPSE DE FOGO sobre "
              << alvo->getNome() << "! Dano: " << danoBase << "\n";
}

string ApocalipseDeFogo::getDescricao() const {
    return "Poder maximo do fogo. Dano devastador.";
}