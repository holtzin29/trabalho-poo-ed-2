#include "../headers/mapa.hpp"
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace sf;

Mapa::Mapa(int f) : fase(f) {
    tiles.resize(ALTURA, vector<TileType>(LARGURA));
    
    switch(fase) {
        case 1: gerarFase1(); break;
        case 2: gerarFase2(); break;
        case 3: gerarFase3(); break;
        case 4: gerarFase4(); break;
        default: gerarFase1();
    }
}

void Mapa::gerarFase1() {
    // Floresta - gramado com árvores espalhadas
    for (int y = 0; y < ALTURA; y++) {
        for (int x = 0; x < LARGURA; x++) {
            int rand = (x * 73 + y * 97) % 100;
            if (rand < 70) tiles[y][x] = TILE_GRASS;
            else if (rand < 95) tiles[y][x] = TILE_FOREST;
            else tiles[y][x] = TILE_WATER;
        }
    }
    // Garante um caminho
    for (int y = 6; y < 9; y++) {
        for (int x = 0; x < LARGURA; x++) {
            tiles[y][x] = TILE_GRASS;
        }
    }
}

void Mapa::gerarFase2() {
    // Deserto com água
    for (int y = 0; y < ALTURA; y++) {
        for (int x = 0; x < LARGURA; x++) {
            int rand = (x * 83 + y * 107) % 100;
            if (rand < 60) tiles[y][x] = TILE_SAND;
            else if (rand < 80) tiles[y][x] = TILE_GRASS;
            else if (rand < 90) tiles[y][x] = TILE_WATER;
            else tiles[y][x] = TILE_STONE;
        }
    }
    // Garante um caminho
    for (int y = 6; y < 9; y++) {
        for (int x = 0; x < LARGURA; x++) {
            tiles[y][x] = TILE_SAND;
        }
    }
}

void Mapa::gerarFase3() {
    // Montanha com pedras
    for (int y = 0; y < ALTURA; y++) {
        for (int x = 0; x < LARGURA; x++) {
            int rand = (x * 113 + y * 127) % 100;
            int altura = (x + y) % 10;
            
            if (altura > 6) tiles[y][x] = TILE_MOUNTAIN;
            else if (rand < 50) tiles[y][x] = TILE_STONE;
            else if (rand < 75) tiles[y][x] = TILE_GRASS;
            else tiles[y][x] = TILE_WATER;
        }
    }
    // Caminho zigzag
    for (int i = 0; i < ALTURA; i++) {
        int x = (i * 2) % LARGURA;
        tiles[i][x] = TILE_GRASS;
        if (x > 0) tiles[i][x-1] = TILE_GRASS;
    }
}

void Mapa::gerarFase4() {
    // Vulcão com lava
    for (int y = 0; y < ALTURA; y++) {
        for (int x = 0; x < LARGURA; x++) {
            int rand = (x * 131 + y * 137) % 100;
            int distCenter = abs(x - 10) + abs(y - 7);
            
            if (distCenter < 3) tiles[y][x] = TILE_LAVA;
            else if (distCenter < 6) tiles[y][x] = TILE_STONE;
            else if (rand < 70) tiles[y][x] = TILE_STONE;
            else if (rand < 90) tiles[y][x] = TILE_GRASS;
            else tiles[y][x] = TILE_LAVA;
        }
    }
    // Caminho em espiral
    for (int i = 0; i < LARGURA; i++) {
        tiles[7][i] = TILE_GRASS;
    }
}

TileType Mapa::getTile(int x, int y) const {
    if (x < 0 || x >= LARGURA || y < 0 || y >= ALTURA) {
        return TILE_WATER;
    }
    return tiles[y][x];
}

Vector2f Mapa::getPixelPosition(int gridX, int gridY) const {
    return Vector2f(gridX * TAMANHO_TILE + X_OFFSET,
                    gridY * TAMANHO_TILE + Y_OFFSET);
}

Color Mapa::getCorTile(TileType tipo) const {
    switch(tipo) {
        case TILE_GRASS:    return Color(34, 139, 34);      // Verde escuro
        case TILE_FOREST:   return Color(0, 100, 0);        // Verde muito escuro
        case TILE_WATER:    return Color(30, 144, 255);     // Azul
        case TILE_MOUNTAIN: return Color(128, 128, 128);    // Cinza
        case TILE_STONE:    return Color(169, 169, 169);    // Cinza claro
        case TILE_LAVA:     return Color(255, 69, 0);       // Laranja vermelho
        case TILE_SAND:     return Color(210, 180, 140);    // Areia
        default:            return Color(100, 100, 100);
    }
}

void Mapa::desenharTile(RenderWindow& janela, int x, int y, TileType tipo) {
    float pixelX = x * TAMANHO_TILE + X_OFFSET;
    float pixelY = y * TAMANHO_TILE + Y_OFFSET;
    
    // Desenha o tile base
    RectangleShape tile(Vector2f(TAMANHO_TILE - 1, TAMANHO_TILE - 1));
    tile.setPosition(pixelX, pixelY);
    tile.setFillColor(getCorTile(tipo));
    janela.draw(tile);
    
    // Desenha efeitos visuais para certos tiles
    if (tipo == TILE_FOREST) {
        // Desenha árvore simples
        RectangleShape trunk(Vector2f(4, 8));
        trunk.setPosition(pixelX + 14, pixelY + 16);
        trunk.setFillColor(Color(139, 69, 19));
        janela.draw(trunk);
        
        // Copa da árvore
        CircleShape copa(6);
        copa.setPosition(pixelX + 10, pixelY + 8);
        copa.setFillColor(Color(0, 100, 0));
        janela.draw(copa);
    }
    else if (tipo == TILE_LAVA) {
        // Efeito de lava com padrão
        RectangleShape lavaGlint(Vector2f(6, 6));
        lavaGlint.setPosition(pixelX + 8, pixelY + 8);
        lavaGlint.setFillColor(Color(255, 200, 0));
        janela.draw(lavaGlint);
        
        lavaGlint.setPosition(pixelX + 20, pixelY + 20);
        janela.draw(lavaGlint);
    }
    else if (tipo == TILE_MOUNTAIN) {
        // Pico da montanha
        ConvexShape pico(3);
        pico.setPoint(0, Vector2f(16, 4));
        pico.setPoint(1, Vector2f(4, 28));
        pico.setPoint(2, Vector2f(28, 28));
        pico.setPosition(pixelX, pixelY);
        pico.setFillColor(Color(192, 192, 192));
        janela.draw(pico);
    }
    else if (tipo == TILE_WATER) {
        // Onda da água
        RectangleShape onda(Vector2f(8, 2));
        onda.setPosition(pixelX + 4, pixelY + 14);
        onda.setFillColor(Color(100, 200, 255));
        janela.draw(onda);
        
        onda.setPosition(pixelX + 18, pixelY + 20);
        janela.draw(onda);
    }
}

void Mapa::desenhar(RenderWindow& janela) {
    for (int y = 0; y < ALTURA; y++) {
        for (int x = 0; x < LARGURA; x++) {
            desenharTile(janela, x, y, tiles[y][x]);
        }
    }
}
