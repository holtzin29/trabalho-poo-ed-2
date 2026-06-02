#ifndef MAGOTERRA_HPP
#define MAGOTERRA_HPP
#include "../mago.hpp"
using namespace std;

class MagoTerra : public Mago {
    public:
        MagoTerra(string nome);
        void inicializarMagias() override;
};
#endif