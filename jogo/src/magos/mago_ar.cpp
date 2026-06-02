#include "../headers/magos/mago_ar.hpp"
#include "../headers/magias/magias_ar.hpp"
using namespace std;

MagoAr::MagoAr(string nome)
    : Mago(nome, 75, 110, 7, AR) {
    inicializarMagias();
}

void MagoAr::inicializarMagias() {
    Magia* m0 = new RajadaDeVento(); m0->desbloquear();
    skillTree.adicionarMagia(m0,                  0);
    skillTree.adicionarMagia(new CorrenteDeAr(),    1);
    skillTree.adicionarMagia(new Tornado(),         1);
    skillTree.adicionarMagia(new OlhoDoFuracão(),   2);
    skillTree.adicionarMagia(new TempestadeArcana(), 3);
}