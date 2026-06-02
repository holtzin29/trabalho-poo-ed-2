#include "../headers/magos/mago_terra.hpp"
#include "../headers/magias/magias_terra.hpp"
using namespace std;

MagoTerra::MagoTerra(string nome)
    : Mago(nome, 110, 90, 3, TERRA) {
    inicializarMagias();
}

void MagoTerra::inicializarMagias() {
    Magia* m0 = new Pedrada(); m0->desbloquear();
    skillTree.adicionarMagia(m0,                  0);
    skillTree.adicionarMagia(new ChuvaDeRochas(),   1);
    skillTree.adicionarMagia(new Terremoto(),       1);
    skillTree.adicionarMagia(new MuralhaDeRocha(),  2);
    skillTree.adicionarMagia(new ColapsoDaTerra(),  3);
}