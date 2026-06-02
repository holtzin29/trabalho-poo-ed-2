#ifndef MAGOAGUA_HPP
#define MAGOAGUA_HPP
#include "../mago.hpp"
using namespace std;

class MagoAgua : public Mago {
    public:
        MagoAgua(string nome);
        void inicializarMagias() override;
};
#endif