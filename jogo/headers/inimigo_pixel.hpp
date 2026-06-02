#ifndef INIMIGO_PIXEL_HPP
#define INIMIGO_PIXEL_HPP

#include "personagem_pixel.hpp"
using namespace std;
using namespace sf;

enum TipoInimigoPixel {
    GOBLIN_PIX,
    SKELETON_PIX,
    SPIDER_PIX,
    GOLEM_PIX,
    DRAGON_PIX
};

class InimigoPixel : public PersonagemPixel {
private:
    TipoInimigoPixel tipoInimigo;
    
public:
    InimigoPixel(int x, int y, TipoMago tipo, TipoInimigoPixel inimigo);
    
    void desenhar(RenderWindow& janela, int tamanhoTile) override;
    
private:
    void desenharGoblin(RenderWindow& janela, const Vector2f& pos);
    void desenharSkeleton(RenderWindow& janela, const Vector2f& pos);
    void desenharSpider(RenderWindow& janela, const Vector2f& pos);
    void desenharGolem(RenderWindow& janela, const Vector2f& pos);
    void desenharDragon(RenderWindow& janela, const Vector2f& pos);
};

#endif
