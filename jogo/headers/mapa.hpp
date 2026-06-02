#ifndef MAPA_HPP
#define MAPA_HPP

#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

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
    static const int X_OFFSET = 363;
    static const int Y_OFFSET = 120;
    
    vector<vector<TileType>> tiles;
    int fase;
    
    void gerarFase1();
    void gerarFase2();
    void gerarFase3();
    void gerarFase4();
    
public:
    Mapa(int fase = 1);
    
    void desenhar(RenderWindow& janela);
    TileType getTile(int x, int y) const;
    
    int getLargura() const { return LARGURA; }
    int getAltura() const { return ALTURA; }
    int getTamTile() const { return TAMANHO_TILE; }
    int getFase() const { return fase; }
    
    Vector2f getPixelPosition(int gridX, int gridY) const;
    
private:
    void desenharTile(RenderWindow& janela, int x, int y, TileType tipo);
    Color getCorTile(TileType tipo) const;
};

#endif
