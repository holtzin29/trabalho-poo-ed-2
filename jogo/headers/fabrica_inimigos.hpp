#ifndef FABRICA_INIMIGOS_HPP
#define FABRICA_INIMIGOS_HPP
#include "inimigo.hpp"

class FabricaInimigos {
    private:
        static int totalCriado;
    public:
        // cria inimigo escalado pelo nível do jogador
        static Inimigo* criar(TipoInimigo tipo, int nivelJogador);
        static int getTotalCriados();
};

#endif