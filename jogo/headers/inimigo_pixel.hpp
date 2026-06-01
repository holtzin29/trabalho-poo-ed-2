#ifndef INIMIGO_PIXEL_HPP
#define INIMIGO_PIXEL_HPP

#include "personagem_pixel.hpp"

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
    
    void desenhar(sf::RenderWindow& janela, int tamanhoTile) override;
    
private:
    void desenharGoblin(sf::RenderWindow& janela, const sf::Vector2f& pos);
    void desenharSkeleton(sf::RenderWindow& janela, const sf::Vector2f& pos);
    void desenharSpider(sf::RenderWindow& janela, const sf::Vector2f& pos);
    void desenharGolem(sf::RenderWindow& janela, const sf::Vector2f& pos);
    void desenharDragon(sf::RenderWindow& janela, const sf::Vector2f& pos);
};

#endif
