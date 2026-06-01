#include "../headers/personagem_pixel.hpp"

PersonagemPixel::PersonagemPixel(int x, int y, TipoMago t, bool inimigo)
    : gridX(x), gridY(y), tipo(t), eInimigo(inimigo) {}

sf::Color PersonagemPixel::getCorElemento() const {
    switch(tipo) {
        case AGUA:  return sf::Color(100, 180, 255);
        case FOGO:  return sf::Color(255, 100, 0);
        case AR:    return sf::Color(200, 200, 255);
        case TERRA: return sf::Color(139, 90, 43);
        default:    return sf::Color::White;
    }
}

void PersonagemPixel::desenharPixelRetangulo(sf::RenderWindow& janela, int px, int py, int w, int h, sf::Color cor, int tamanhoTile) {
    sf::Vector2f pixelPos = getPixelPos();
    sf::RectangleShape pixel(sf::Vector2f(w * 2, h * 2));
    pixel.setPosition(pixelPos.x + px * 2, pixelPos.y + py * 2);
    pixel.setFillColor(cor);
    janela.draw(pixel);
}

void PersonagemPixel::desenharPixelCirculo(sf::RenderWindow& janela, int cx, int cy, int r, sf::Color cor, int tamanhoTile) {
    sf::Vector2f pixelPos = getPixelPos();
    sf::CircleShape circulo(r);
    circulo.setPosition(pixelPos.x + cx * 2, pixelPos.y + cy * 2);
    circulo.setFillColor(cor);
    janela.draw(circulo);
}
