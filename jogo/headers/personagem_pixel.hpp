#ifndef PERSONAGEM_PIXEL_HPP
#define PERSONAGEM_PIXEL_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "mago.hpp"
using namespace std;
using namespace sf;

class PersonagemPixel {
protected:
    int gridX, gridY;
    TipoMago tipo;
    string nome;
    bool eInimigo;
    
public:
    PersonagemPixel(int x, int y, TipoMago t, bool inimigo = false);
    virtual ~PersonagemPixel() = default;
    
    virtual void desenhar(RenderWindow& janela, int tamanhoTile) = 0;
    
    void setPosicao(int x, int y) { gridX = x; gridY = y; }
    int getGridX() const { return gridX; }
    int getGridY() const { return gridY; }
    TipoMago getTipo() const { return tipo; }
    bool isInimigo() const { return eInimigo; }
    string getNome() const { return nome; }
    
    static const int MAP_OFFSET_X = 363;
    static const int MAP_OFFSET_Y = 120;

    Vector2f getPixelPos() const {
        return Vector2f(gridX * 32 + MAP_OFFSET_X,
                        gridY * 32 + MAP_OFFSET_Y);
    }
    
protected:
    Color getCorElemento() const;
    void desenharPixelRetangulo(RenderWindow& janela, int px, int py, int w, int h, Color cor, int tamanhoTile);
    void desenharPixelCirculo(RenderWindow& janela, int cx, int cy, int r, Color cor, int tamanhoTile);
};

#endif
