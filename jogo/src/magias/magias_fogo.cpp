#include "../headers/magias/magias_fogo.hpp"
#include <iostream>
#include <algorithm>

// --- BolaDeFogo ---
BolaDeFogo::BolaDeFogo() : Magia("Bola de Fogo", 10, 25) {}

void BolaDeFogo::lancar(Entidade* lancador, Entidade* alvo) {
    alvo->receberDano(danoBase);
    std::cout << lancador->getNome() << " lança Bola de Fogo em "
              << alvo->getNome() << "! Dano: " << danoBase << "\n";
}

std::string BolaDeFogo::getDescricao() const {
    return "Projétil de fogo. Dano: " + std::to_string(danoBase);
}

// --- Queimadura ---
Queimadura::Queimadura() : Magia("Queimadura", 15, 10), turnosRestantes(3) {}

void Queimadura::lancar(Entidade* lancador, Entidade* alvo) {
    // aplica dano imediato + sinaliza efeito de turno (controlado pelo loop de jogo)
    turnosRestantes = 3;
    alvo->receberDano(danoBase);
    std::cout << lancador->getNome() << " aplica Queimadura em "
              << alvo->getNome() << "! Dano: " << danoBase
              << " por " << turnosRestantes << " turnos.\n";
}

std::string Queimadura::getDescricao() const {
    return "Dano ao longo do tempo por 3 turnos.";
}

int Queimadura::getTurnosRestantes() const { return turnosRestantes; }

// --- ExplosaoFogo ---
ExplosaoFogo::ExplosaoFogo() : Magia("Explosão de Fogo", 25, 40) {}

void ExplosaoFogo::lancar(Entidade* lancador, Entidade* alvo) {
    int dano = static_cast<int>(danoBase * 1.5f);
    alvo->receberDano(dano);
    std::cout << lancador->getNome() << " causa uma Explosão de Fogo! Dano: " << dano << "\n";
}

std::string ExplosaoFogo::getDescricao() const {
    return "Explosão em área. Dano: " + std::to_string(static_cast<int>(danoBase * 1.5f));
}

// --- Inferno ---
Inferno::Inferno() : Magia("Inferno", 40, 60) {}

void Inferno::lancar(Entidade* lancador, Entidade* alvo) {
    alvo->receberDano(danoBase);
    // cura o lancador em 20% do dano causado
    int cura = static_cast<int>(danoBase * 0.2f);
    lancador->setVida(lancador->getVida() + cura);
    std::cout << lancador->getNome() << " invoca o Inferno! Dano: " << danoBase
              << " | Cura: " << cura << "\n";
}

std::string Inferno::getDescricao() const {
    return "Dano alto + recupera 20% do dano como vida.";
}

// --- ApocalipseDeFogo ---
ApocalipseDeFogo::ApocalipseDeFogo() : Magia("Apocalipse de Fogo", 70, 100) {}

void ApocalipseDeFogo::lancar(Entidade* lancador, Entidade* alvo) {
    alvo->receberDano(danoBase);
    std::cout << "🔥 " << lancador->getNome()
              << " desencadeia o APOCALIPSE DE FOGO sobre "
              << alvo->getNome() << "! Dano: " << danoBase << "\n";
}

std::string ApocalipseDeFogo::getDescricao() const {
    return "Poder máximo do fogo. Dano devastador.";
}