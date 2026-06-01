#ifndef MAGOAR_HPP
#define MAGOAR_HPP
#include "../mago.hpp"

class MagoAr : public Mago {
    public:
        MagoAr(std::string nome);
        void inicializarMagias() override;
};
#endif