#include "../headers/magias/magias_agua.hpp"
#include <iostream>

// --- JatoDeAgua ---
JatoDeAgua::JatoDeAgua() : Magia("Jato de Água", 10, 20) {}

void JatoDeAgua::lancar(Entidade* lancador, Entidade* alvo) {
    alvo->receberDano(danoBase);
    int cura = static_cast<int>(danoBase * 0.3f);
    lancador->setVida(lancador->getVida() + cura);
    std::cout << lancador->getNome() << " dispara Jato de Água! Dano: "
              << danoBase << " | Cura: " << cura << "\n";
}

std::string JatoDeAgua::getDescricao() const {
    return "Dano + cura 30% do dano causado.";
}

// --- OndaGelada ---
OndaGelada::OndaGelada() : Magia("Onda Gelada", 20, 25) {}

void OndaGelada::lancar(Entidade* lancador, Entidade* alvo) {
    alvo->receberDano(danoBase);
    // efeito de congelar é tratado no loop de combate via flag no Inimigo
    std::cout << lancador->getNome() << " lança Onda Gelada! "
              << alvo->getNome() << " está congelado por 1 turno!\n";
}

std::string OndaGelada::getDescricao() const {
    return "Dano + congela o inimigo por 1 turno.";
}

// --- CuraAgua ---
CuraAgua::CuraAgua() : Magia("Cura das Águas", 30, 0) {}

void CuraAgua::lancar(Entidade* lancador, Entidade* alvo) {
    int cura = 50;
    lancador->setVida(lancador->getVida() + cura);
    std::cout << lancador->getNome() << " usa Cura das Águas! +"
              << cura << " HP\n";
}

std::string CuraAgua::getDescricao() const {
    return "Recupera 50 HP instantaneamente.";
}

// --- MareAlta ---
MareAlta::MareAlta() : Magia("Maré Alta", 45, 55) {}

void MareAlta::lancar(Entidade* lancador, Entidade* alvo) {
    alvo->receberDano(danoBase);
    int cura = static_cast<int>(danoBase * 0.5f);
    lancador->setVida(lancador->getVida() + cura);
    std::cout << lancador->getNome() << " invoca a Maré Alta! Dano: "
              << danoBase << " | Cura: " << cura << "\n";
}

std::string MareAlta::getDescricao() const {
    return "Dano alto + cura 50% do dano.";
}

// --- Tsunami ---
Tsunami::Tsunami() : Magia("Tsunami", 70, 95) {}

void Tsunami::lancar(Entidade* lancador, Entidade* alvo) {
    alvo->receberDano(danoBase);
    std::cout << "🌊 " << lancador->getNome()
              << " desencadeia um TSUNAMI sobre "
              << alvo->getNome() << "! Dano: " << danoBase << "\n";
}

std::string Tsunami::getDescricao() const {
    return "Poder máximo da água. Dano devastador.";
}