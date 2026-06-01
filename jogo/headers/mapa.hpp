#ifndef MAPA_HPP
#define MAPA_HPP

#include <SFML/Graphics.hpp>
#include <vector>

enum TileType {
    TILE_GRASS,
    TILE_FOREST,
    TILE_WATER,
    TILE_MOUNTAIN,
    TILE_STONE,
    TILE_LAVA,
    TILE_SAND
};

class Mapa {
private:
    static const int LARGURA = 20;
    static const int ALTURA = 15;
    static const int TAMANHO_TILE = 32;
    
    std::vector<std::vector<TileType>> tiles;
    int fase;
    
    void gerarFase1();
    void gerarFase2();
    void gerarFase3();
    void gerarFase4();
    
public:
    Mapa(int fase = 1);
    
    void desenhar(sf::RenderWindow& janela);
    TileType getTile(int x, int y) const;
    
    int getLargura() const { return LARGURA; }
    int getAltura() const { return ALTURA; }
    int getTamTile() const { return TAMANHO_TILE; }
    int getFase() const { return fase; }
    
    sf::Vector2f getPixelPosition(int gridX, int gridY) const;
    
private:
    void desenharTile(sf::RenderWindow& janela, int x, int y, TileType tipo);
    sf::Color getCorTile(TileType tipo) const;
};

#endif
