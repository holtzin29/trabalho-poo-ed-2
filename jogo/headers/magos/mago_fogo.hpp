#ifndef MAGOFOGO_HPP
#define MAGOFOGO_HPP
#include "../mago.hpp"
using namespace std;

class MagoFogo : public Mago {
    public:
        MagoFogo(string nome);
        void inicializarMagias() override;
};
#endif
