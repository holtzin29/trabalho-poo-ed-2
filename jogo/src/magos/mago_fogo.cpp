// magofogo.cpp
#include "../headers/magos/mago_fogo.hpp"
#include "../headers/magias/magias_fogo.hpp"
using namespace std;

MagoFogo::MagoFogo(string nome)
    : Mago(nome, 80, 120, 5, FOGO) {
    inicializarMagias();
}

void MagoFogo::inicializarMagias() {
    // custo 0 = já desbloqueada, os outros precisam de pontos
    Magia* m0 = new BolaDeFogo();    m0->desbloquear();
    skillTree.adicionarMagia(m0, 0);
    skillTree.adicionarMagia(new Queimadura(),       1);
    skillTree.adicionarMagia(new ExplosaoFogo(),     1);
    skillTree.adicionarMagia(new Inferno(),          2);
    skillTree.adicionarMagia(new ApocalipseDeFogo(), 3);
}