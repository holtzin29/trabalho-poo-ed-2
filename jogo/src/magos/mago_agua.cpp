#include "../headers/magos/mago_agua.hpp"
#include "../headers/magias/magias_agua.hpp"

MagoAgua::MagoAgua(std::string nome)
    : Mago(nome, 90, 100, 4, AGUA) {
    inicializarMagias();
}

void MagoAgua::inicializarMagias() {
    Magia* m0 = new JatoDeAgua(); m0->desbloquear();
    skillTree.adicionarMagia(m0,              0);
    skillTree.adicionarMagia(new OndaGelada(),  1);
    skillTree.adicionarMagia(new CuraAgua(),    1);
    skillTree.adicionarMagia(new MareAlta(),    2);
    skillTree.adicionarMagia(new Tsunami(),     3);
}