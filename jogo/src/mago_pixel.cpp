#include "../headers/mago_pixel.hpp"

MagoPixel::MagoPixel(int x, int y, TipoMago tipo, const std::string& n)
    : PersonagemPixel(x, y, tipo, false), nivel(1) {
    nome = n;
}

void MagoPixel::desenhar(sf::RenderWindow& janela, int tamanhoTile) {
    sf::Vector2f pos = getPixelPos();
    sf::Color cor = getCorElemento();
    sf::Color corEscura(cor.r / 2, cor.g / 2, cor.b / 2);
    
    // Cabeça (círculo)
    sf::CircleShape cabeca(6);
    cabeca.setPosition(pos.x + 10, pos.y + 2);
    cabeca.setFillColor(sf::Color(255, 220, 177));
    janela.draw(cabeca);
    
    // Chapéu pontudo (triângulo)
    sf::ConvexShape chapeu(3);
    chapeu.setPoint(0, sf::Vector2f(16, 0));
    chapeu.setPoint(1, sf::Vector2f(8, 10));
    chapeu.setPoint(2, sf::Vector2f(24, 10));
    chapeu.setPosition(pos.x, pos.y);
    chapeu.setFillColor(cor);
    janela.draw(chapeu);
    
    // Corpo (retângulo)
    sf::RectangleShape corpo(sf::Vector2f(12, 14));
    corpo.setPosition(pos.x + 10, pos.y + 14);
    corpo.setFillColor(cor);
    janela.draw(corpo);
    
    // Braço esquerdo
    sf::RectangleShape bracoE(sf::Vector2f(4, 12));
    bracoE.setPosition(pos.x + 6, pos.y + 15);
    bracoE.setFillColor(sf::Color(255, 220, 177));
    janela.draw(bracoE);
    
    // Braço direito (levantado segurando varinha)
    sf::RectangleShape bracoD(sf::Vector2f(4, 14));
    bracoD.setPosition(pos.x + 24, pos.y + 13);
    bracoD.setFillColor(sf::Color(255, 220, 177));
    janela.draw(bracoD);
    
    // Varinha
    sf::RectangleShape varinha(sf::Vector2f(2, 10));
    varinha.setPosition(pos.x + 26, pos.y + 8);
    varinha.setFillColor(sf::Color(210, 180, 140));
    janela.draw(varinha);
    
    // Ponta da varinha (brilho)
    sf::CircleShape pontaVarinha(3);
    pontaVarinha.setPosition(pos.x + 24, pos.y + 6);
    pontaVarinha.setFillColor(cor);
    janela.draw(pontaVarinha);
    
    // Perna esquerda
    sf::RectangleShape pernaE(sf::Vector2f(4, 10));
    pernaE.setPosition(pos.x + 12, pos.y + 28);
    pernaE.setFillColor(sf::Color(100, 100, 100));
    janela.draw(pernaE);
    
    // Perna direita
    sf::RectangleShape pernaD(sf::Vector2f(4, 10));
    pernaD.setPosition(pos.x + 18, pos.y + 28);
    pernaD.setFillColor(sf::Color(100, 100, 100));
    janela.draw(pernaD);
}
