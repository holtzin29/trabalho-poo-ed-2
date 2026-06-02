#ifndef MAGO_PIXEL_HPP
#define MAGO_PIXEL_HPP

#include "personagem_pixel.hpp"
using namespace std;
using namespace sf;

class MagoPixel : public PersonagemPixel {
private:
    int nivel;
    
public:
    MagoPixel(int x, int y, TipoMago tipo, const string& n);
    
    void desenhar(RenderWindow& janela, int tamanhoTile) override;
};

#endif
