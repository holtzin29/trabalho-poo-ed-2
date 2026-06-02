#include "../headers/mago_pixel.hpp"
using namespace std;
using namespace sf;

MagoPixel::MagoPixel(int x, int y, TipoMago tipo, const string& n)
    : PersonagemPixel(x, y, tipo, false), nivel(1) {
    nome = n;
}

void MagoPixel::desenhar(RenderWindow& janela, int tamanhoTile) {
    Vector2f pos = getPixelPos();
    Color cor = getCorElemento();
    Color corEscura(cor.r / 2, cor.g / 2, cor.b / 2);
    
    // Cabeça (círculo)
    CircleShape cabeca(6);
    cabeca.setPosition(pos.x + 10, pos.y + 2);
    cabeca.setFillColor(Color(255, 220, 177));
    janela.draw(cabeca);
    
    // Chapéu pontudo (triângulo)
    ConvexShape chapeu(3);
    chapeu.setPoint(0, Vector2f(16, 0));
    chapeu.setPoint(1, Vector2f(8, 10));
    chapeu.setPoint(2, Vector2f(24, 10));
    chapeu.setPosition(pos.x, pos.y);
    chapeu.setFillColor(cor);
    janela.draw(chapeu);
    
    // Corpo (retângulo)
    RectangleShape corpo(Vector2f(12, 14));
    corpo.setPosition(pos.x + 10, pos.y + 14);
    corpo.setFillColor(cor);
    janela.draw(corpo);
    
    // Braço esquerdo
    RectangleShape bracoE(Vector2f(4, 12));
    bracoE.setPosition(pos.x + 6, pos.y + 15);
    bracoE.setFillColor(Color(255, 220, 177));
    janela.draw(bracoE);
    
    // Braço direito (levantado segurando varinha)
    RectangleShape bracoD(Vector2f(4, 14));
    bracoD.setPosition(pos.x + 24, pos.y + 13);
    bracoD.setFillColor(Color(255, 220, 177));
    janela.draw(bracoD);
    
    // Varinha
    RectangleShape varinha(Vector2f(2, 10));
    varinha.setPosition(pos.x + 26, pos.y + 8);
    varinha.setFillColor(Color(210, 180, 140));
    janela.draw(varinha);
    
    // Ponta da varinha (brilho)
    CircleShape pontaVarinha(3);
    pontaVarinha.setPosition(pos.x + 24, pos.y + 6);
    pontaVarinha.setFillColor(cor);
    janela.draw(pontaVarinha);
    
    // Perna esquerda
    RectangleShape pernaE(Vector2f(4, 10));
    pernaE.setPosition(pos.x + 12, pos.y + 28);
    pernaE.setFillColor(Color(100, 100, 100));
    janela.draw(pernaE);
    
    // Perna direita
    RectangleShape pernaD(Vector2f(4, 10));
    pernaD.setPosition(pos.x + 18, pos.y + 28);
    pernaD.setFillColor(Color(100, 100, 100));
    janela.draw(pernaD);
}
