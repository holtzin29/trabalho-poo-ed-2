#ifndef MAGOTERRA_HPP
#define MAGOTERRA_HPP
#include "../mago.hpp"

class MagoTerra : public Mago {
    public:
        MagoTerra(std::string nome);
        void inicializarMagias() override;
};
#endif