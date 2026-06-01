#ifndef PERSONAGEM_PIXEL_HPP
#define PERSONAGEM_PIXEL_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "mago.hpp"

class PersonagemPixel {
protected:
    int gridX, gridY;
    TipoMago tipo;
    std::string nome;
    bool eInimigo;
    
public:
    PersonagemPixel(int x, int y, TipoMago t, bool inimigo = false);
    virtual ~PersonagemPixel() = default;
    
    virtual void desenhar(sf::RenderWindow& janela, int tamanhoTile) = 0;
    
    void setPosicao(int x, int y) { gridX = x; gridY = y; }
    int getGridX() const { return gridX; }
    int getGridY() const { return gridY; }
    TipoMago getTipo() const { return tipo; }
    bool isInimigo() const { return eInimigo; }
    std::string getNome() const { return nome; }
    
    sf::Vector2f getPixelPos() const {
        return sf::Vector2f(gridX * 32 + 100, gridY * 32 + 50);
    }
    
protected:
    sf::Color getCorElemento() const;
    void desenharPixelRetangulo(sf::RenderWindow& janela, int px, int py, int w, int h, sf::Color cor, int tamanhoTile);
    void desenharPixelCirculo(sf::RenderWindow& janela, int cx, int cy, int r, sf::Color cor, int tamanhoTile);
};

#endif
