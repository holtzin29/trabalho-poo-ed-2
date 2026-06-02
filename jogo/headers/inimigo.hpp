#ifndef INIMIGO_HPP
#define INIMIGO_HPP
#include "entidade.hpp"
#include <string>
using namespace std;

enum TipoInimigo { 
    GOBLIN, ESQUELETO, GOLEM, DRAGAO 
};

class Inimigo : public Entidade {
    protected:
        int danoBase;
        int defesa;
        int xpRecompensa;
        TipoInimigo tipo;
        bool congelado;         // efeito Onda Gelada
        int turnosQueimando;    // efeito Queimadura
        int danoQueimadura;

    public:
        Inimigo(string nome, int vidaMax, int dano,
                int defesa, int xp, TipoInimigo tipo);

        // sobrescrita dos virtuais puros de Entidade
        void atacar(Entidade* alvo) override;
        void receberDano(int dano) override;
        void exibirStatus() const override;

        // efeitos de status
        void aplicarCongelamento();
        void aplicarQueimadura(int dano, int turnos);
        void processarEfeitos(); // chamado a cada turno

        int getXpRecompensa() const;
        TipoInimigo getTipo() const;
        bool estaCongelado() const;
};

#endif