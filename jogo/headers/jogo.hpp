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
using namespace std;
using namespace sf;

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
    RenderWindow janela;
    Font fonte;
    EstadoJogo estado;

    // jogador
    Mago *jogador;
    MagoPixel *jogadorPixel;
    string nomeTemp;

    // inimigo atual
    Inimigo *inimigo;
    InimigoPixel * inimigoPixel;
    int rodada;
    int xpTotal;

    // mapa
    Mapa * mapa;
    int faseAtual;

    // combate
    int magiaSelecionada;
    vector<string> logCombate;
    bool turnoJogador;
    float temporizadorInimigo; // delay antes do inimigo agir
    float tempoMovimento;      // tempo entre movimentos contínuos

    // seleção de tipo
    int tipoSelecionado; // 0-3

    // cores por elemento
    Color corElemento() const;
    string nomeElemento() const;
    string emojiBoss() const;

    // desenho de cada estado
    void desenharMenu();
    void desenharSelecaoTipo();
    void desenharSelecaoNome();
    void desenharCombate();
    void desenharSkillTree();
    void desenharGameOver();
    void desenharVitoria();

    // helpers de desenho
    void desenharBarraHP(float x, float y, float largura, int hp, int hpMax, Color cor);
    void desenharBarraMP(float x, float y, float largura, int mp, int mpMax);
    void desenharHUD();
    void desenharLog();
    void adicionarLog(const string& msg);

    // lógica
    void criarJogador(int tipo, const string& nome);
    void iniciarRodada();
    void usarMagia(int indice);
    void turnoInimigo();
    void verificarFimCombate();
    void processarXP(int xp);
    void atualizarMovimento(float dt);

public:
    Jogo();
    void rodar();
};

#endif