#include "../headers/inimigo_pixel.hpp"
using namespace std;
using namespace sf;

InimigoPixel::InimigoPixel(int x, int y, TipoMago tipo, TipoInimigoPixel inimigo)
    : PersonagemPixel(x, y, tipo, true), tipoInimigo(inimigo) {}

void InimigoPixel::desenhar(RenderWindow& janela, int tamanhoTile) {
    Vector2f pos = getPixelPos();
    
    switch(tipoInimigo) {
        case GOBLIN_PIX:
            desenharGoblin(janela, pos);
            break;
        case SKELETON_PIX:
            desenharSkeleton(janela, pos);
            break;
        case SPIDER_PIX:
            desenharSpider(janela, pos);
            break;
        case GOLEM_PIX:
            desenharGolem(janela, pos);
            break;
        case DRAGON_PIX:
            desenharDragon(janela, pos);
            break;
    }
}

void InimigoPixel::desenharGoblin(RenderWindow& janela, const Vector2f& pos) {
    Color corGoblin(100, 200, 100);
    
    // Cabeça
    RectangleShape cabeca(Vector2f(10, 10));
    cabeca.setPosition(pos.x + 11, pos.y + 3);
    cabeca.setFillColor(corGoblin);
    janela.draw(cabeca);
    
    // Olhos
    CircleShape olhoE(2);
    olhoE.setPosition(pos.x + 13, pos.y + 5);
    olhoE.setFillColor(Color::Black);
    janela.draw(olhoE);
    
    CircleShape olhoD(2);
    olhoD.setPosition(pos.x + 17, pos.y + 5);
    olhoD.setFillColor(Color::Black);
    janela.draw(olhoD);
    
    // Corpo
    RectangleShape corpo(Vector2f(12, 14));
    corpo.setPosition(pos.x + 10, pos.y + 14);
    corpo.setFillColor(corGoblin);
    janela.draw(corpo);
    
    // Braço esquerdo
    RectangleShape bracoE(Vector2f(6, 12));
    bracoE.setPosition(pos.x + 4, pos.y + 16);
    bracoE.setFillColor(corGoblin);
    janela.draw(bracoE);
    
    // Braço direito
    RectangleShape bracoD(Vector2f(6, 12));
    bracoD.setPosition(pos.x + 24, pos.y + 16);
    bracoD.setFillColor(corGoblin);
    janela.draw(bracoD);
    
    // Perna esquerda
    RectangleShape pernaE(Vector2f(4, 10));
    pernaE.setPosition(pos.x + 12, pos.y + 28);
    pernaE.setFillColor(Color(50, 100, 50));
    janela.draw(pernaE);
    
    // Perna direita
    RectangleShape pernaD(Vector2f(4, 10));
    pernaD.setPosition(pos.x + 18, pos.y + 28);
    pernaD.setFillColor(Color(50, 100, 50));
    janela.draw(pernaD);
}

void InimigoPixel::desenharSkeleton(RenderWindow& janela, const Vector2f& pos) {
    Color corOsso(220, 220, 220);
    Color corBuraco(50, 50, 50);
    
    // Crânio
    RectangleShape cranio(Vector2f(12, 12));
    cranio.setPosition(pos.x + 10, pos.y + 2);
    cranio.setFillColor(corOsso);
    janela.draw(cranio);
    
    // Olhos vazios
    RectangleShape olhoE(Vector2f(3, 3));
    olhoE.setPosition(pos.x + 12, pos.y + 5);
    olhoE.setFillColor(corBuraco);
    janela.draw(olhoE);
    
    RectangleShape olhoD(Vector2f(3, 3));
    olhoD.setPosition(pos.x + 17, pos.y + 5);
    olhoD.setFillColor(corBuraco);
    janela.draw(olhoD);
    
    // Coluna vertebral
    RectangleShape coluna(Vector2f(4, 16));
    coluna.setPosition(pos.x + 14, pos.y + 14);
    coluna.setFillColor(corOsso);
    janela.draw(coluna);
    
    // Braço esquerdo
    RectangleShape bracoE(Vector2f(3, 14));
    bracoE.setPosition(pos.x + 6, pos.y + 16);
    bracoE.setFillColor(corOsso);
    janela.draw(bracoE);
    
    // Braço direito
    RectangleShape bracoD(Vector2f(3, 14));
    bracoD.setPosition(pos.x + 25, pos.y + 16);
    bracoD.setFillColor(corOsso);
    janela.draw(bracoD);
    
    // Perna esquerda
    RectangleShape pernaE(Vector2f(3, 12));
    pernaE.setPosition(pos.x + 12, pos.y + 28);
    pernaE.setFillColor(corOsso);
    janela.draw(pernaE);
    
    // Perna direita
    RectangleShape pernaD(Vector2f(3, 12));
    pernaD.setPosition(pos.x + 19, pos.y + 28);
    pernaD.setFillColor(corOsso);
    janela.draw(pernaD);
}

void InimigoPixel::desenharSpider(RenderWindow& janela, const Vector2f& pos) {
    Color corAranha(80, 20, 120);
    
    // Corpo principal
    CircleShape corpo(8);
    corpo.setPosition(pos.x + 8, pos.y + 10);
    corpo.setFillColor(corAranha);
    janela.draw(corpo);
    
    // Cabeça
    CircleShape cabeca(5);
    cabeca.setPosition(pos.x + 13, pos.y + 4);
    cabeca.setFillColor(corAranha);
    janela.draw(cabeca);
    
    // Olhos
    CircleShape olhoE(2);
    olhoE.setPosition(pos.x + 14, pos.y + 6);
    olhoE.setFillColor(Color::Red);
    janela.draw(olhoE);
    
    CircleShape olhoD(2);
    olhoD.setPosition(pos.x + 17, pos.y + 6);
    olhoD.setFillColor(Color::Red);
    janela.draw(olhoD);
    
    // Pata dianteira esquerda
    RectangleShape pataEE(Vector2f(2, 12));
    pataEE.setPosition(pos.x + 4, pos.y + 12);
    pataEE.setFillColor(corAranha);
    janela.draw(pataEE);
    
    RectangleShape pataED(Vector2f(2, 14));
    pataED.setPosition(pos.x + 2, pos.y + 10);
    pataED.setFillColor(corAranha);
    janela.draw(pataED);
    
    // Pata traseira esquerda
    RectangleShape pataTEE(Vector2f(2, 12));
    pataTEE.setPosition(pos.x + 4, pos.y + 22);
    pataTEE.setFillColor(corAranha);
    janela.draw(pataTEE);
    
    RectangleShape pataTED(Vector2f(2, 14));
    pataTED.setPosition(pos.x + 2, pos.y + 20);
    pataTED.setFillColor(corAranha);
    janela.draw(pataTED);
    
    // Pata dianteira direita
    RectangleShape pataDE(Vector2f(2, 12));
    pataDE.setPosition(pos.x + 28, pos.y + 12);
    pataDE.setFillColor(corAranha);
    janela.draw(pataDE);
    
    RectangleShape pataDED(Vector2f(2, 14));
    pataDED.setPosition(pos.x + 30, pos.y + 10);
    pataDED.setFillColor(corAranha);
    janela.draw(pataDED);
    
    // Pata traseira direita
    RectangleShape pataTDE(Vector2f(2, 12));
    pataTDE.setPosition(pos.x + 28, pos.y + 22);
    pataTDE.setFillColor(corAranha);
    janela.draw(pataTDE);
    
    RectangleShape pataTDED(Vector2f(2, 14));
    pataTDED.setPosition(pos.x + 30, pos.y + 20);
    pataTDED.setFillColor(corAranha);
    janela.draw(pataTDED);
}

void InimigoPixel::desenharGolem(RenderWindow& janela, const Vector2f& pos) {
    Color corGolem(160, 160, 160);
    Color corPedra(200, 200, 200);
    
    // Cabeça (quadrada)
    RectangleShape cabeca(Vector2f(14, 14));
    cabeca.setPosition(pos.x + 9, pos.y + 0);
    cabeca.setFillColor(corGolem);
    janela.draw(cabeca);
    
    // Olhos brilhantes
    RectangleShape olhoE(Vector2f(4, 4));
    olhoE.setPosition(pos.x + 11, pos.y + 5);
    olhoE.setFillColor(Color::Yellow);
    janela.draw(olhoE);
    
    RectangleShape olhoD(Vector2f(4, 4));
    olhoD.setPosition(pos.x + 17, pos.y + 5);
    olhoD.setFillColor(Color::Yellow);
    janela.draw(olhoD);
    
    // Corpo (maior, robusto)
    RectangleShape corpo(Vector2f(18, 16));
    corpo.setPosition(pos.x + 7, pos.y + 14);
    corpo.setFillColor(corGolem);
    janela.draw(corpo);
    
    // Detalhe no corpo
    RectangleShape detalhe(Vector2f(4, 4));
    detalhe.setPosition(pos.x + 11, pos.y + 18);
    detalhe.setFillColor(corPedra);
    janela.draw(detalhe);
    
    detalhe.setPosition(pos.x + 17, pos.y + 18);
    janela.draw(detalhe);
    
    // Braço esquerdo (grosso)
    RectangleShape bracoE(Vector2f(6, 16));
    bracoE.setPosition(pos.x + 2, pos.y + 14);
    bracoE.setFillColor(corGolem);
    janela.draw(bracoE);
    
    // Braço direito (grosso)
    RectangleShape bracoD(Vector2f(6, 16));
    bracoD.setPosition(pos.x + 26, pos.y + 14);
    bracoD.setFillColor(corGolem);
    janela.draw(bracoD);
    
    // Perna esquerda
    RectangleShape pernaE(Vector2f(6, 12));
    pernaE.setPosition(pos.x + 10, pos.y + 28);
    pernaE.setFillColor(Color(140, 140, 140));
    janela.draw(pernaE);
    
    // Perna direita
    RectangleShape pernaD(Vector2f(6, 12));
    pernaD.setPosition(pos.x + 18, pos.y + 28);
    pernaD.setFillColor(Color(140, 140, 140));
    janela.draw(pernaD);
}

void InimigoPixel::desenharDragon(RenderWindow& janela, const Vector2f& pos) {
    Color corDragao(255, 150, 0);
    Color corAsas(255, 200, 100);
    
    // Cabeça
    RectangleShape cabeca(Vector2f(14, 12));
    cabeca.setPosition(pos.x + 9, pos.y + 2);
    cabeca.setFillColor(corDragao);
    janela.draw(cabeca);
    
    // Chifres
    ConvexShape chifreE(3);
    chifreE.setPoint(0, Vector2f(11, 2));
    chifreE.setPoint(1, Vector2f(8, 0));
    chifreE.setPoint(2, Vector2f(10, 6));
    chifreE.setPosition(pos.x, pos.y);
    chifreE.setFillColor(Color(200, 150, 0));
    janela.draw(chifreE);
    
    ConvexShape chifreD(3);
    chifreD.setPoint(0, Vector2f(21, 2));
    chifreD.setPoint(1, Vector2f(24, 0));
    chifreD.setPoint(2, Vector2f(22, 6));
    chifreD.setPosition(pos.x, pos.y);
    chifreD.setFillColor(Color(200, 150, 0));
    janela.draw(chifreD);
    
    // Olhos
    CircleShape olhoE(2);
    olhoE.setPosition(pos.x + 11, pos.y + 4);
    olhoE.setFillColor(Color::Black);
    janela.draw(olhoE);
    
    CircleShape olhoD(2);
    olhoD.setPosition(pos.x + 19, pos.y + 4);
    olhoD.setFillColor(Color::Black);
    janela.draw(olhoD);
    
    // Corpo
    RectangleShape corpo(Vector2f(16, 14));
    corpo.setPosition(pos.x + 8, pos.y + 14);
    corpo.setFillColor(corDragao);
    janela.draw(corpo);
    
    // Asas (esquerda)
    ConvexShape asaE(4);
    asaE.setPoint(0, Vector2f(0, 18));
    asaE.setPoint(1, Vector2f(-8, 12));
    asaE.setPoint(2, Vector2f(-10, 22));
    asaE.setPoint(3, Vector2f(0, 24));
    asaE.setPosition(pos.x + 8, pos.y);
    asaE.setFillColor(corAsas);
    janela.draw(asaE);
    
    // Asas (direita)
    ConvexShape asaD(4);
    asaD.setPoint(0, Vector2f(0, 18));
    asaD.setPoint(1, Vector2f(8, 12));
    asaD.setPoint(2, Vector2f(10, 22));
    asaD.setPoint(3, Vector2f(0, 24));
    asaD.setPosition(pos.x + 24, pos.y);
    asaD.setFillColor(corAsas);
    janela.draw(asaD);
    
    // Cauda
    RectangleShape cauda(Vector2f(8, 4));
    cauda.setPosition(pos.x + 22, pos.y + 20);
    cauda.setFillColor(corDragao);
    janela.draw(cauda);
}
