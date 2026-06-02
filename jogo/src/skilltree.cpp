// skilltree.cpp
#include "../headers/skilltree.hpp"
#include <iostream>
using namespace std;

int SkillTree::totalDesbloqueios = 0;

SkillTree::SkillTree() : pontosDisponiveis(0) {}

SkillTree::~SkillTree() {
    for (Magia* m : magias) delete m;
}

void SkillTree::adicionarMagia(Magia* magia, int custo) {
    magias.push_back(magia);
    custosPontos.push_back(custo);
}

bool SkillTree::desbloquearMagia(int indice) {
    if (indice < 0 || indice >= (int)magias.size()) return false;
    if (magias[indice]->estaDesbloqueada()) return false;
    if (pontosDisponiveis < custosPontos[indice]) return false;

    pontosDisponiveis -= custosPontos[indice];
    magias[indice]->desbloquear();
    totalDesbloqueios++;
    return true;
}

void SkillTree::exibirArvore() const {
    for (int i = 0; i < (int)magias.size(); i++) {
        string status = magias[i]->estaDesbloqueada() ? "[OK]" : "[" + to_string(custosPontos[i]) + "pt]";
        cout << i+1 << ". " << status << " " << magias[i]->getNome()
                  << " - " << magias[i]->getDescricao() << "\n";
    }
    cout << "Pontos disponíveis: " << pontosDisponiveis << "\n";
}

Magia* SkillTree::getMagia(int indice) {
    if (indice < 0 || indice >= (int)magias.size()) return nullptr;
    return magias[indice];
}

int SkillTree::getTamanho()           const { return magias.size(); }
int SkillTree::getPontosDisponiveis() const { return pontosDisponiveis; }
void SkillTree::adicionarPontos(int p)      { pontosDisponiveis += p; }
int SkillTree::getTotalDesbloqueios()       { return totalDesbloqueios; }