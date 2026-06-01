#ifndef MAGOAGUA_HPP
#define MAGOAGUA_HPP
#include "../mago.hpp"

class MagoAgua : public Mago {
    public:
        MagoAgua(std::string nome);
        void inicializarMagias() override;
};
#endif