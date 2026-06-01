#ifndef MAGOFOGO_HPP
#define MAGOFOGO_HPP
#include "../mago.hpp"

class MagoFogo : public Mago {
    public:
        MagoFogo(std::string nome);
        void inicializarMagias() override;
};
#endif
