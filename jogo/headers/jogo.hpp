#ifndef JOGO_HPP
#define JOGO_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <string>
#include <vector>
#include "mago.hpp"
#include "magos/mago_fogo.hpp"
#include "magos/mago_agua.hpp"
#include "magos/mago_terra.hpp"
#include "magos/mago_ar.hpp"
#include "inimigo.hpp"
#include "fabrica_inimigos.hpp"
#include "mapa.hpp"
#include "mago_pixel.hpp"
#include "inimigo_pixel.hpp"

enum EstadoJogo {
    MENU_PRINCIPAL,
    SELECAO_TIPO,
    SELECAO_NOME,
    COMBATE,
    SKILL_TREE,
    GAME_OVER,
    VITORIA
};

class Jogo {
private:
    sf::RenderWindow janela;
    sf::Font fonte;
    EstadoJogo estado;

    // jogador
    std::unique_ptr<Mago> jogador;
    std::unique_ptr<MagoPixel> jogadorPixel;
    std::string nomeTemp;

    // inimigo atual
    std::unique_ptr<Inimigo> inimigo;
    std::unique_ptr<InimigoPixel> inimigoPixel;
    int rodada;
    int xpTotal;

    // mapa
    std::unique_ptr<Mapa> mapa;
    int faseAtual;

    // combate
    int magiaSelecionada;
    std::vector<std::string> logCombate;
    bool turnoJogador;
    float temporizadorInimigo; // delay antes do inimigo agir

    // seleção de tipo
    int tipoSelecionado; // 0-3

    // cores por elemento
    sf::Color corElemento() const;
    std::string nomeElemento() const;
    std::string emojiBoss() const;

    // desenho de cada estado
    void desenharMenu();
    void desenharSelecaoTipo();
    void desenharSelecaoNome();
    void desenharCombate();
    void desenharSkillTree();
    void desenharGameOver();
    void desenharVitoria();

    // helpers de desenho
    void desenharBarraHP(float x, float y, float largura, int hp, int hpMax, sf::Color cor);
    void desenharBarraMP(float x, float y, float largura, int mp, int mpMax);
    void desenharHUD();
    void desenharLog();
    void adicionarLog(const std::string& msg);

    // lógica
    void criarJogador(int tipo, const std::string& nome);
    void iniciarRodada();
    void usarMagia(int indice);
    void turnoInimigo();
    void verificarFimCombate();
    void processarXP(int xp);

public:
    Jogo();
    void rodar();
};

#endif