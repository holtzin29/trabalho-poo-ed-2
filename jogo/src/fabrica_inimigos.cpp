#include "../headers/fabrica_inimigos.hpp"

int FabricaInimigos::totalCriado = 0;

Inimigo* FabricaInimigos::criar(TipoInimigo tipo, int nivelJogador) {
    totalCriado++;
    int escala = nivelJogador;

    switch (tipo) {
        case GOBLIN:
            return new Inimigo("Goblin",
                /*vida*/  30 + escala * 5,
                /*dano*/  8  + escala * 2,
                /*def*/   2,
                /*xp*/    20 + escala * 5,
                GOBLIN);

        case ESQUELETO:
            return new Inimigo("Esqueleto",
                50  + escala * 5,
                12  + escala * 2,
                5,
                35  + escala * 5,
                ESQUELETO);

        case GOLEM:
            return new Inimigo("Golem de Pedra",
                100 + escala * 10,
                18  + escala * 3,
                12,
                60  + escala * 10,
                GOLEM);

        case DRAGAO:
            return new Inimigo("Dragão Ancião",
                200 + escala * 20,
                30  + escala * 5,
                20,
                150 + escala * 20,
                DRAGAO);

        default:
            return new Inimigo("Inimigo", 30, 8, 0, 10, GOBLIN);
    }
}

int FabricaInimigos::getTotalCriados() { return totalCriado; }