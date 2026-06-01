#ifndef MAGO_PIXEL_HPP
#define MAGO_PIXEL_HPP

#include "personagem_pixel.hpp"

class MagoPixel : public PersonagemPixel {
private:
    int nivel;
    
public:
    MagoPixel(int x, int y, TipoMago tipo, const std::string& n);
    
    void desenhar(sf::RenderWindow& janela, int tamanhoTile) override;
};

#endif
