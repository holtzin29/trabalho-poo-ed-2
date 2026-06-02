#include "../headers/personagem_pixel.hpp"
using namespace std;
using namespace sf;

PersonagemPixel::PersonagemPixel(int x, int y, TipoMago t, bool inimigo)
    : gridX(x), gridY(y), tipo(t), eInimigo(inimigo) {}

Color PersonagemPixel::getCorElemento() const {
    switch(tipo) {
        case AGUA:  return Color(100, 180, 255);
        case FOGO:  return Color(255, 100, 0);
        case AR:    return Color(200, 200, 255);
        case TERRA: return Color(139, 90, 43);
        default:    return Color::White;
    }
}

void PersonagemPixel::desenharPixelRetangulo(RenderWindow& janela, int px, int py, int w, int h, Color cor, int tamanhoTile) {
    Vector2f pixelPos = getPixelPos();
    RectangleShape pixel(Vector2f(w * 2, h * 2));
    pixel.setPosition(pixelPos.x + px * 2, pixelPos.y + py * 2);
    pixel.setFillColor(cor);
    janela.draw(pixel);
}

void PersonagemPixel::desenharPixelCirculo(RenderWindow& janela, int cx, int cy, int r, Color cor, int tamanhoTile) {
    Vector2f pixelPos = getPixelPos();
    CircleShape circulo(r);
    circulo.setPosition(pixelPos.x + cx * 2, pixelPos.y + cy * 2);
    circulo.setFillColor(cor);
    janela.draw(circulo);
}
