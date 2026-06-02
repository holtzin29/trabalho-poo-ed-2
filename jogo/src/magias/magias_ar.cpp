#include "../headers/magias/magias_ar.hpp"
#include <iostream>
using namespace std;

// --- RajadaDeVento ---
RajadaDeVento::RajadaDeVento() : Magia("Rajada de Vento", 8, 18) {}

void RajadaDeVento::lancar(Entidade* lancador, Entidade* alvo) {
    alvo->receberDano(danoBase);
    cout << lancador->getNome() << " dispara uma Rajada de Vento! Dano: " << danoBase << "\n";
}

string RajadaDeVento::getDescricao() const {
    return "Ataque rapido. Dano: " + to_string(danoBase);
}

// --- CorrenteDeAr ---
CorrenteDeAr::CorrenteDeAr() : Magia("Corrente de Ar", 18, 0) {}

void CorrenteDeAr::lancar(Entidade* lancador, Entidade* alvo) {
    lancador->getAtributos().setAgilidade(lancador->getAtributos().getAgilidade() + 3);
    cout << lancador->getNome() << " usa Corrente de Ar! +3 Agilidade\n";
}

string CorrenteDeAr::getDescricao() const {
    return "Aumenta agilidade em 3 permanentemente.";
}

// --- Tornado ---
Tornado::Tornado() : Magia("Tornado", 30, 45) {}

void Tornado::lancar(Entidade* lancador, Entidade* alvo) {
    // dano duplo em rajada
    alvo->receberDano(danoBase);
    alvo->receberDano(danoBase / 2);
    cout << lancador->getNome() << " invoca um Tornado! Dano duplo: "
              << danoBase << " + " << danoBase / 2 << "\n";
}

string Tornado::getDescricao() const {
    return "Rajada dupla: " + to_string(danoBase) + " + " + to_string(danoBase / 2);
}

// --- OlhoDoFuracão ---
OlhoDoFuracão::OlhoDoFuracão() : Magia("Olho do Furacao", 45, 50) {}

void OlhoDoFuracão::lancar(Entidade* lancador, Entidade* alvo) {
    alvo->receberDano(danoBase);
    // também cura levemente o lancador
    lancador->setVida(lancador->getVida() + 15);
    cout << lancador->getNome() << " entra no Olho do Furacao! Dano: "
              << danoBase << " | +15 HP\n";
}

string OlhoDoFuracão::getDescricao() const {
    return "Dano alto + recupera 15 HP.";
}

// --- TempestadeArcana ---
TempestadeArcana::TempestadeArcana() : Magia("Tempestade Arcana", 70, 90) {}

void TempestadeArcana::lancar(Entidade* lancador, Entidade* alvo) {
    alvo->receberDano(danoBase);
    cout << " " << lancador->getNome()
              << " desencadeia a TEMPESTADE ARCANA sobre "
              << alvo->getNome() << "! Dano: " << danoBase << "\n";
}

string TempestadeArcana::getDescricao() const {
    return "Poder maximo do ar. Dano devastador.";
}