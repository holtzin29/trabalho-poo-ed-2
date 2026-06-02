// personagem.hpp
#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP
#include "entidade.hpp"
#include "skilltree.hpp"
using namespace std;
class Personagem : public Entidade {
    protected:
        int velocidade;
        int pontosHabilidade;
        SkillTree skillTree;  // associação: Personagem TEM UMA SkillTree

    public:
        Personagem(string nome, int vidaMax, int velocidade);

        // ainda abstrato — Mago vai implementar
        virtual void atacar(Entidade* alvo) = 0;
        virtual void receberDano(int dano) override;
        virtual void exibirStatus() const = 0;

        void ganharPontosHabilidade(int pontos);
        bool desbloquearHabilidade(int indice);
        SkillTree& getSkillTree();
        int getVelocidade() const;
};

#endif