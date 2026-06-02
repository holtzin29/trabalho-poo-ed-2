#include "../headers/magias/magias_terra.hpp"
#include <iostream>
using namespace std;

// --- Pedrada ---
Pedrada::Pedrada() : Magia("Pedrada", 8, 22) {}

void Pedrada::lancar(Entidade* lancador, Entidade* alvo) {
    alvo->receberDano(danoBase);
    cout << lancador->getNome() << " arremessa uma Pedrada! Dano: " << danoBase << "\n";
}

string Pedrada::getDescricao() const {
    return "Ataque basico de terra. Dano: " + to_string(danoBase);
}

// --- ChuvaDeRochas ---
ChuvaDeRochas::ChuvaDeRochas() : Magia("Chuva de Rochas", 20, 35) {}

void ChuvaDeRochas::lancar(Entidade* lancador, Entidade* alvo) {
    // ignora 50% da redução de dano do alvo
    int dano = static_cast<int>(danoBase * 1.5f);
    alvo->receberDano(dano);
    cout << lancador->getNome() << " invoca Chuva de Rochas! Dano perfurante: " << dano << "\n";
}

string ChuvaDeRochas::getDescricao() const {
    return "Perfura defesas. Dano: " + to_string(static_cast<int>(danoBase * 1.5f));
}

// --- Terremoto ---
Terremoto::Terremoto() : Magia("Terremoto", 35, 55) {}

void Terremoto::lancar(Entidade* lancador, Entidade* alvo) {
    alvo->receberDano(danoBase);
    cout << lancador->getNome() << " provoca um Terremoto! Dano: " << danoBase << "\n";
}

string Terremoto::getDescricao() const {
    return "Abala o chao. Dano pesado: " + to_string(danoBase);
}

// --- MuralhaDeRocha ---
MuralhaDeRocha::MuralhaDeRocha() : Magia("Muralha de Rocha", 40, 0) {}

void MuralhaDeRocha::lancar(Entidade* lancador, Entidade* alvo) {
    // aumenta vidaMaxima temporariamente (loop de combate controla duração)
    int bonus = 40;
    lancador->setVidaMaxima(lancador->getVidaMaxima() + bonus);
    lancador->setVida(lancador->getVida() + bonus);
    cout << lancador->getNome() << " ergue uma Muralha de Rocha! +"
              << bonus << " HP maximo\n";
}

string MuralhaDeRocha::getDescricao() const {
    return "Aumenta HP maximo em 40 temporariamente.";
}

// --- ColapsoDaTerra ---
ColapsoDaTerra::ColapsoDaTerra() : Magia("Colapso da Terra", 70, 90) {}

void ColapsoDaTerra::lancar(Entidade* lancador, Entidade* alvo) {
    alvo->receberDano(danoBase);
    cout << "  " << lancador->getNome()
              << " causa o COLAPSO DA TERRA sob "
              << alvo->getNome() << "! Dano: " << danoBase << "\n";
}

string ColapsoDaTerra::getDescricao() const {
    return "Poder máximo da terra. Dano devastador.";
}