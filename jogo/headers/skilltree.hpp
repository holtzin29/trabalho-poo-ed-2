// skilltree.hpp
#ifndef SKILLTREE_HPP
#define SKILLTREE_HPP
#include <vector>
#include "magia.hpp"

using namespace std;

class SkillTree {
    private:
        vector<Magia*> magias;   // polimorfismo: ponteiros pra base
        vector<int> custosPontos; // custo de cada magia em pontos
        int pontosDisponiveis;

        static int totalDesbloqueios; // static: conta globalmente

    public:
        SkillTree();
        ~SkillTree();

        void adicionarMagia(Magia* magia, int custo);
        bool desbloquearMagia(int indice);
        void exibirArvore() const;

        Magia* getMagia(int indice);
        int getTamanho() const;
        int getPontosDisponiveis() const;
        void adicionarPontos(int pontos);

        static int getTotalDesbloqueios();
};

#endif