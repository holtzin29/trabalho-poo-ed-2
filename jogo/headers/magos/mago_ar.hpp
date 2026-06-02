#ifndef MAGOAR_HPP
#define MAGOAR_HPP
#include "../mago.hpp"
using namespace std;

class MagoAr : public Mago {
    public:
        MagoAr(string nome);
        void inicializarMagias() override;
};
#endif