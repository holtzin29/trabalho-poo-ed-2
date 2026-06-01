// mago.hpp
#ifndef MAGO_HPP
#define MAGO_HPP
#include "personagem.hpp"

enum TipoMago { FOGO, AGUA, TERRA, AR };

class Mago : public Personagem {
    protected:
        int mana;
        int manaMaxima;
        TipoMago tipo;

    public:
        Mago(std::string nome, int vidaMax, int manaMax, int velocidade, TipoMago tipo);

        // ainda abstrato: cada subclasse popula a skilltree com suas magias
        virtual void inicializarMagias() = 0;

        // implementados aqui, válidos pra todos os magos
        void atacar(Entidade* alvo) override;       // ataca com 1ª magia desbloqueada
        void usarMagia(int indice, Entidade* alvo); // usa magia específica
        void receberDano(int dano) override;
        void exibirStatus() const override;
        void regenerarMana();

        int getMana() const;
        int getManaMaxima() const;
        TipoMago getTipo() const;

    protected:
        bool gastarMana(int custo);
};

#endif