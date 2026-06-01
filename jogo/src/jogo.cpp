#include "../headers/jogo.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

// ─── construtor ───────────────────────────────────────────────────────────────
Jogo::Jogo()
    : janela(sf::VideoMode(900, 600), "Mago Arcano",
             sf::Style::Titlebar | sf::Style::Close),
      estado(MENU_PRINCIPAL),
      rodada(1), xpTotal(0),
      magiaSelecionada(0), turnoJogador(true),
      temporizadorInimigo(0.f), tipoSelecionado(0), faseAtual(1)
{
    janela.setFramerateLimit(60);
    if (!fonte.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"))
        if (!fonte.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf"))
            std::cerr << "Fonte não encontrada, usando padrão\n";
}

// ─── loop principal ────────────────────────────────────────────────────────────
void Jogo::rodar() {
    sf::Clock relogio;
    while (janela.isOpen()) {
        float dt = relogio.restart().asSeconds();
        sf::Event evento;

        while (janela.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                janela.close();

            // ── MENU PRINCIPAL ──
            if (estado == MENU_PRINCIPAL) {
                if (evento.type == sf::Event::KeyPressed &&
                    evento.key.code == sf::Keyboard::Return)
                    estado = SELECAO_TIPO;
            }

            // ── SELEÇÃO DE TIPO ──
            else if (estado == SELECAO_TIPO) {
                if (evento.type == sf::Event::KeyPressed) {
                    if (evento.key.code == sf::Keyboard::Left)
                        tipoSelecionado = (tipoSelecionado + 3) % 4;
                    if (evento.key.code == sf::Keyboard::Right)
                        tipoSelecionado = (tipoSelecionado + 1) % 4;
                    if (evento.key.code == sf::Keyboard::Return)
                        estado = SELECAO_NOME;
                }
            }

            // ── SELEÇÃO DE NOME ──
            else if (estado == SELECAO_NOME) {
                if (evento.type == sf::Event::TextEntered) {
                    if (evento.text.unicode == '\b') {
                        if (!nomeTemp.empty()) nomeTemp.pop_back();
                    } else if (evento.text.unicode == '\r') {
                        if (!nomeTemp.empty()) {
                            criarJogador(tipoSelecionado, nomeTemp);
                            iniciarRodada();
                            estado = COMBATE;
                        }
                    } else if (evento.text.unicode < 128 && nomeTemp.size() < 16) {
                        nomeTemp += static_cast<char>(evento.text.unicode);
                    }
                }
            }

            // ── COMBATE ──
            else if (estado == COMBATE && turnoJogador) {
                if (evento.type == sf::Event::KeyPressed) {
                    int tam = jogador->getSkillTree().getTamanho();
                    if (evento.key.code == sf::Keyboard::Up)
                        magiaSelecionada = (magiaSelecionada + tam - 1) % tam;
                    if (evento.key.code == sf::Keyboard::Down)
                        magiaSelecionada = (magiaSelecionada + 1) % tam;
                    if (evento.key.code == sf::Keyboard::Return) {
                        usarMagia(magiaSelecionada);
                    }
                    if (evento.key.code == sf::Keyboard::T)
                        estado = SKILL_TREE;
                }
            }

            // ── SKILL TREE ──
            else if (estado == SKILL_TREE) {
                if (evento.type == sf::Event::KeyPressed) {
                    int tam = jogador->getSkillTree().getTamanho();
                    if (evento.key.code == sf::Keyboard::Up)
                        magiaSelecionada = (magiaSelecionada + tam - 1) % tam;
                    if (evento.key.code == sf::Keyboard::Down)
                        magiaSelecionada = (magiaSelecionada + 1) % tam;
                    if (evento.key.code == sf::Keyboard::Return)
                        jogador->desbloquearHabilidade(magiaSelecionada);
                    if (evento.key.code == sf::Keyboard::Escape)
                        estado = COMBATE;
                }
            }

            // ── GAME OVER / VITORIA ──
            else if (estado == GAME_OVER || estado == VITORIA) {
                if (evento.type == sf::Event::KeyPressed &&
                    evento.key.code == sf::Keyboard::Return) {
                    jogador.reset();
                    inimigo.reset();
                    nomeTemp.clear();
                    rodada = 1; xpTotal = 0;
                    magiaSelecionada = 0;
                    turnoJogador = true;
                    logCombate.clear();
                    estado = MENU_PRINCIPAL;
                }
            }
        }

        // turno do inimigo com delay
        if (estado == COMBATE && !turnoJogador) {
            temporizadorInimigo -= dt;
            if (temporizadorInimigo <= 0.f) {
                turnoInimigo();
            }
        }

        // renderização
        janela.clear(sf::Color(15, 12, 25));
        switch (estado) {
            case MENU_PRINCIPAL:  desenharMenu();        break;
            case SELECAO_TIPO:    desenharSelecaoTipo(); break;
            case SELECAO_NOME:    desenharSelecaoNome(); break;
            case COMBATE:         desenharCombate();     break;
            case SKILL_TREE:      desenharSkillTree();   break;
            case GAME_OVER:       desenharGameOver();    break;
            case VITORIA:         desenharVitoria();     break;
        }
        janela.display();
    }
}

// ─── helpers de cor / nome ────────────────────────────────────────────────────
sf::Color Jogo::corElemento() const {
    switch (tipoSelecionado) {
        case 0: return sf::Color(255, 80,  30);   // fogo
        case 1: return sf::Color(30,  160, 255);  // agua
        case 2: return sf::Color(140, 100, 40);   // terra
        case 3: return sf::Color(180, 240, 255);  // ar
        default: return sf::Color::White;
    }
}

std::string Jogo::nomeElemento() const {
    switch (tipoSelecionado) {
        case 0: return "FOGO";  case 1: return "AGUA";
        case 2: return "TERRA"; case 3: return "AR";
        default: return "";
    }
}

std::string Jogo::emojiBoss() const {
    if (!inimigo) return "";
    switch (inimigo->getTipo()) {
        case GOBLIN:    return "[Goblin]";
        case ESQUELETO: return "[Esqueleto]";
        case GOLEM:     return "[Golem]";
        case DRAGAO:    return "[Dragao]";
        default:        return "[?]";
    }
}

// ─── lógica ───────────────────────────────────────────────────────────────────
void Jogo::criarJogador(int tipo, const std::string& nome) {
    switch (tipo) {
        case 0: jogador = std::make_unique<MagoFogo>(nome);  break;
        case 1: jogador = std::make_unique<MagoAgua>(nome);  break;
        case 2: jogador = std::make_unique<MagoTerra>(nome); break;
        case 3: jogador = std::make_unique<MagoAr>(nome);    break;
    }
    
    // Cria pixel art do jogador
    TipoMago tipos[] = {FOGO, AGUA, TERRA, AR};
    jogadorPixel = std::make_unique<MagoPixel>(5, 7, tipos[tipo], nome);
}

void Jogo::iniciarRodada() {
    // Determina a fase baseado na rodada
    faseAtual = std::min(rodada, 4);
    
    // Cria o mapa da fase
    mapa = std::make_unique<Mapa>(faseAtual);
    
    // escala de inimigos por rodada
    TipoInimigo tipos[] = {GOBLIN, ESQUELETO, GOLEM, DRAGAO};
    TipoInimigo tipo = tipos[std::min(rodada - 1, 3)];
    inimigo = std::unique_ptr<Inimigo>(
        FabricaInimigos::criar(tipo, jogador->getNivel()));
    
    // Cria pixel art do inimigo
    TipoInimigoPixel tiposPixel[] = {GOBLIN_PIX, SKELETON_PIX, GOLEM_PIX, DRAGON_PIX};
    TipoMago elementoInimigo = static_cast<TipoMago>(rand() % 4);
    inimigoPixel = std::make_unique<InimigoPixel>(14, 7, elementoInimigo, 
                                                   tiposPixel[std::min(rodada - 1, 3)]);
    
    turnoJogador = true;
    magiaSelecionada = 0;
    adicionarLog("-- Rodada " + std::to_string(rodada) +
                 ": " + inimigo->getNome() + " aparece! --");
}

void Jogo::usarMagia(int indice) {
    if (!turnoJogador) return;
    Magia* m = jogador->getSkillTree().getMagia(indice);
    if (!m) return;
    if (!m->estaDesbloqueada()) {
        adicionarLog("Magia bloqueada! Use T para abrir a Skill Tree.");
        return;
    }

    // redireciona cout para capturar a mensagem da magia
    std::ostringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    jogador->usarMagia(indice, inimigo.get());
    std::cout.rdbuf(old);
    adicionarLog(buffer.str());

    // efeitos especiais por magia
    std::string nomeMagia = m->getNome();
    if (nomeMagia == "Onda Gelada")
        inimigo->aplicarCongelamento();
    if (nomeMagia == "Queimadura")
        inimigo->aplicarQueimadura(8, 3);

    verificarFimCombate();
    if (estado == COMBATE) {
        turnoJogador = false;
        temporizadorInimigo = 1.2f;
    }
}

void Jogo::turnoInimigo() {
    inimigo->processarEfeitos();

    std::ostringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    inimigo->atacar(jogador.get());
    std::cout.rdbuf(old);
    adicionarLog(buffer.str());

    jogador->regenerarMana();
    verificarFimCombate();
    if (estado == COMBATE)
        turnoJogador = true;
}

void Jogo::verificarFimCombate() {
    if (!inimigo->estaVivo()) {
        int xp = inimigo->getXpRecompensa();
        adicionarLog(inimigo->getNome() + " derrotado! +" + std::to_string(xp) + " XP");
        processarXP(xp);

        if (rodada >= 4) {
            estado = VITORIA;
        } else {
            rodada++;
            iniciarRodada();
        }
    }
    if (!jogador->estaVivo())
        estado = GAME_OVER;
}

void Jogo::processarXP(int xp) {
    xpTotal += xp;
    int xpParaSubir = jogador->getNivel() * 100;
    if (xpTotal >= xpParaSubir) {
        xpTotal -= xpParaSubir;
        jogador->subirNivel();
        jogador->ganharPontosHabilidade(2);
        adicionarLog("LEVEL UP! Nivel " + std::to_string(jogador->getNivel()) +
                     " | +2 pontos de habilidade!");
    }
}

void Jogo::adicionarLog(const std::string& msg) {
    if (msg.empty()) return;
    // quebra mensagens longas
    std::istringstream stream(msg);
    std::string linha;
    while (std::getline(stream, linha)) {
        if (!linha.empty())
            logCombate.push_back(linha);
    }
    // mantém só as últimas 6 linhas
    while (logCombate.size() > 6)
        logCombate.erase(logCombate.begin());
}

// ─── desenho ──────────────────────────────────────────────────────────────────
void Jogo::desenharBarraHP(float x, float y, float largura,
                            int hp, int hpMax, sf::Color cor) {
    sf::RectangleShape fundo({largura, 14.f});
    fundo.setPosition(x, y);
    fundo.setFillColor(sf::Color(50, 20, 20));
    janela.draw(fundo);

    float pct = std::max(0.f, (float)hp / hpMax);
    sf::RectangleShape barra({largura * pct, 14.f});
    barra.setPosition(x, y);
    barra.setFillColor(cor);
    janela.draw(barra);

    sf::Text txt;
    txt.setFont(fonte);
    txt.setCharacterSize(11);
    txt.setFillColor(sf::Color::White);
    txt.setString(std::to_string(hp) + "/" + std::to_string(hpMax));
    txt.setPosition(x + largura / 2 - 20, y);
    janela.draw(txt);
}

void Jogo::desenharBarraMP(float x, float y, float largura, int mp, int mpMax) {
    sf::RectangleShape fundo({largura, 14.f});
    fundo.setPosition(x, y);
    fundo.setFillColor(sf::Color(20, 20, 60));
    janela.draw(fundo);

    float pct = std::max(0.f, (float)mp / mpMax);
    sf::RectangleShape barra({largura * pct, 14.f});
    barra.setPosition(x, y);
    barra.setFillColor(sf::Color(80, 100, 255));
    janela.draw(barra);

    sf::Text txt;
    txt.setFont(fonte);
    txt.setCharacterSize(11);
    txt.setFillColor(sf::Color::White);
    txt.setString(std::to_string(mp) + "/" + std::to_string(mpMax));
    txt.setPosition(x + largura / 2 - 20, y);
    janela.draw(txt);
}

// helper para texto simples
static sf::Text makeText(const sf::Font& f, const std::string& s,
                          unsigned sz, sf::Color c, float x, float y) {
    sf::Text t;
    t.setFont(f);
    t.setString(s);
    t.setCharacterSize(sz);
    t.setFillColor(c);
    t.setPosition(x, y);
    return t;
}

void Jogo::desenharMenu() {
    janela.draw(makeText(fonte, "MAGO ARCANO", 52,
                sf::Color(220, 180, 60), 240, 140));
    janela.draw(makeText(fonte, "Um jogo de magia elementar", 18,
                sf::Color(160, 140, 200), 290, 210));
    janela.draw(makeText(fonte, "Pressione ENTER para comecar", 22,
                sf::Color(200, 200, 255), 270, 340));
    janela.draw(makeText(fonte, "Use setas + ENTER para navegar", 14,
                sf::Color(100, 100, 140), 300, 520));
}

void Jogo::desenharSelecaoTipo() {
    janela.draw(makeText(fonte, "Escolha seu elemento:", 28,
                sf::Color(220, 200, 255), 290, 60));

    struct Info { std::string nome; std::string desc; sf::Color cor; };
    Info infos[4] = {
        {"FOGO",  "Alto dano\nAtaques explosivos",    sf::Color(255, 80,  30)},
        {"AGUA",  "Cura e controle\nDano sustentado", sf::Color(30,  160, 255)},
        {"TERRA", "Alta defesa\nDano pesado",          sf::Color(160, 120, 40)},
        {"AR",    "Velocidade\nRajadas multiplas",     sf::Color(180, 240, 255)},
    };

    for (int i = 0; i < 4; i++) {
        float x = 60.f + i * 200.f;
        float y = 160.f;
        bool sel = (i == tipoSelecionado);

        sf::RectangleShape caixa({160.f, 200.f});
        caixa.setPosition(x, y);
        caixa.setFillColor(sel
            ? sf::Color(infos[i].cor.r/4, infos[i].cor.g/4, infos[i].cor.b/4, 200)
            : sf::Color(30, 25, 45, 180));
        caixa.setOutlineThickness(sel ? 3.f : 1.f);
        caixa.setOutlineColor(sel ? infos[i].cor : sf::Color(60, 50, 80));
        janela.draw(caixa);

        // símbolo grande
        std::string simbolo[] = {"  ^v^", "  ~~~", "  ###", "  >>>"};
        janela.draw(makeText(fonte, simbolo[i], 28, infos[i].cor, x + 20, y + 20));
        janela.draw(makeText(fonte, infos[i].nome, 20,
                    sel ? infos[i].cor : sf::Color(200,200,200), x + 20, y + 80));

        // descrição linha a linha
        std::istringstream ss(infos[i].desc);
        std::string linha; int ly = 0;
        while (std::getline(ss, linha)) {
            janela.draw(makeText(fonte, linha, 13,
                        sf::Color(160,160,160), x + 10, y + 110 + ly * 20));
            ly++;
        }
    }

    janela.draw(makeText(fonte, "< setas >  ENTER para confirmar", 16,
                sf::Color(160, 140, 200), 300, 420));
}

void Jogo::desenharSelecaoNome() {
    sf::Color cor = corElemento();
    janela.draw(makeText(fonte, "Mago de " + nomeElemento(), 30, cor, 320, 120));
    janela.draw(makeText(fonte, "Digite seu nome:", 22,
                sf::Color(200,200,255), 320, 220));

    // caixa de texto
    sf::RectangleShape caixa({300.f, 44.f});
    caixa.setPosition(300, 270);
    caixa.setFillColor(sf::Color(30, 25, 45));
    caixa.setOutlineThickness(2.f);
    caixa.setOutlineColor(cor);
    janela.draw(caixa);

    janela.draw(makeText(fonte, nomeTemp + "_", 24,
                sf::Color::White, 312, 278));
    janela.draw(makeText(fonte, "ENTER para confirmar", 16,
                sf::Color(140,120,180), 330, 360));
}

void Jogo::desenharHUD() {
    if (!jogador) return;
    sf::Color cor = corElemento();

    // painel jogador (esquerda)
    sf::RectangleShape painelJ({280.f, 110.f});
    painelJ.setPosition(10, 10);
    painelJ.setFillColor(sf::Color(20, 16, 35, 220));
    painelJ.setOutlineThickness(1.f);
    painelJ.setOutlineColor(cor);
    janela.draw(painelJ);

    janela.draw(makeText(fonte, jogador->getNome() + " [Nv." +
                std::to_string(jogador->getNivel()) + "]",
                16, cor, 18, 14));
    janela.draw(makeText(fonte, "HP", 13, sf::Color(255,100,100), 18, 36));
    desenharBarraHP(45, 36, 220, jogador->getVida(),
                    jogador->getVidaMaxima(), sf::Color(200,50,50));
    janela.draw(makeText(fonte, "MP", 13, sf::Color(100,100,255), 18, 58));
    desenharBarraMP(45, 58, 220, jogador->getMana(), jogador->getManaMaxima());

    janela.draw(makeText(fonte,
                "For: " + std::to_string(jogador->getAtributos().getForca()) +
                "  Agi: " + std::to_string(jogador->getAtributos().getAgilidade()),
                13, sf::Color(160,160,200), 18, 82));
    janela.draw(makeText(fonte,
                "XP: " + std::to_string(xpTotal) + "/" +
                std::to_string(jogador->getNivel() * 100),
                13, sf::Color(220,180,60), 18, 100));

    // painel inimigo (direita)
    if (!inimigo) return;
    sf::RectangleShape painelI({280.f, 80.f});
    painelI.setPosition(610, 10);
    painelI.setFillColor(sf::Color(35, 16, 16, 220));
    painelI.setOutlineThickness(1.f);
    painelI.setOutlineColor(sf::Color(180,50,50));
    janela.draw(painelI);

    janela.draw(makeText(fonte, emojiBoss() + " " + inimigo->getNome(),
                16, sf::Color(255,120,80), 618, 14));
    janela.draw(makeText(fonte, "HP", 13, sf::Color(255,100,100), 618, 36));
    desenharBarraHP(645, 36, 220, inimigo->getVida(),
                    inimigo->getVidaMaxima(), sf::Color(200,50,50));

    // rodada
    janela.draw(makeText(fonte, "Rodada " + std::to_string(rodada) + "/4",
                18, sf::Color(200,180,100), 390, 20));
}

void Jogo::desenharLog() {
    sf::RectangleShape painel({880.f, 120.f});
    painel.setPosition(10, 470);
    painel.setFillColor(sf::Color(10, 8, 20, 230));
    painel.setOutlineThickness(1.f);
    painel.setOutlineColor(sf::Color(60, 50, 80));
    janela.draw(painel);

    for (int i = 0; i < (int)logCombate.size(); i++) {
        float alpha = 120.f + (float)i / logCombate.size() * 135.f;
        janela.draw(makeText(fonte, logCombate[i], 13,
                    sf::Color(200, 190, 220, (uint8_t)alpha),
                    18, 476 + i * 18));
    }
}

void Jogo::desenharCombate() {
    // Desenha o mapa
    mapa->desenhar(janela);
    
    // Desenha o jogador pixel
    if (jogadorPixel) {
        jogadorPixel->desenhar(janela, 32);
    }
    
    // Desenha o inimigo pixel
    if (inimigoPixel) {
        inimigoPixel->desenhar(janela, 32);
    }
    
    // HUD de combate (fixo na tela)
    // Painel de informações do jogador (esquerda)
    sf::RectangleShape painelJogador({280.f, 120.f});
    painelJogador.setPosition(10, 480);
    painelJogador.setFillColor(sf::Color(18, 14, 30, 210));
    painelJogador.setOutlineThickness(2.f);
    painelJogador.setOutlineColor(corElemento());
    janela.draw(painelJogador);
    
    janela.draw(makeText(fonte, nomeElemento() + ": " + jogador->getNome(), 14, 
                        corElemento(), 20, 485));
    janela.draw(makeText(fonte, "Niv: " + std::to_string(jogador->getNivel()),
                        12, sf::Color(200,200,200), 20, 505));
    
    desenharBarraHP(20, 520, 120, jogador->getVida(), jogador->getVidaMaxima(), corElemento());
    desenharBarraMP(160, 520, 120, jogador->getMana(), jogador->getManaMaxima());
    
    janela.draw(makeText(fonte, "Nivel: " + std::to_string(jogador->getNivel()),
                        11, sf::Color(100,200,100), 20, 560));
    
    // Painel de inimigo (direita)
    sf::RectangleShape painelInimigo({280.f, 120.f});
    painelInimigo.setPosition(610, 480);
    painelInimigo.setFillColor(sf::Color(30, 14, 14, 210));
    painelInimigo.setOutlineThickness(2.f);
    painelInimigo.setOutlineColor(sf::Color(200, 100, 100));
    janela.draw(painelInimigo);
    
    if (inimigo) {
        janela.draw(makeText(fonte, inimigo->getNome() + " " + emojiBoss(),
                            14, sf::Color(255, 100, 100), 620, 485));
        janela.draw(makeText(fonte, "Rod: " + std::to_string(rodada),
                            12, sf::Color(200,200,200), 620, 505));
        
        desenharBarraHP(620, 520, 120, inimigo->getVida(), inimigo->getVidaMaxima(),
                       sf::Color(255, 100, 100));
        janela.draw(makeText(fonte, "XP: " + std::to_string(inimigo->getXpRecompensa()),
                            11, sf::Color(100,200,100), 620, 560));
    }

    // Painel de magias (centro-inferior)
    sf::RectangleShape painelMagias({300.f, 200.f});
    painelMagias.setPosition(300, 420);
    painelMagias.setFillColor(sf::Color(18, 14, 30, 210));
    painelMagias.setOutlineThickness(1.f);
    painelMagias.setOutlineColor(corElemento());
    janela.draw(painelMagias);

    janela.draw(makeText(fonte, "MAGIAS", 13, corElemento(), 310, 425));

    SkillTree& st = jogador->getSkillTree();
    for (int i = 0; i < st.getTamanho(); i++) {
        Magia* m = st.getMagia(i);
        bool selecionado = (i == magiaSelecionada);
        bool desbloqueado = m->estaDesbloqueada();

        sf::Color cor = desbloqueado
            ? (selecionado ? sf::Color::Yellow : sf::Color(200,200,200))
            : sf::Color(80, 70, 100);

        std::string prefixo = selecionado ? "> " : "  ";
        std::string lock    = desbloqueado ? "" : " [L]";
        std::string custo   = "MP:" + std::to_string(m->getCustoMana());

        janela.draw(makeText(fonte, prefixo + m->getNome() + lock,
                    11, cor, 315, 445 + i * 42));
        janela.draw(makeText(fonte, m->getDescricao().substr(0,30) + "  " + custo,
                    9, sf::Color(140,130,160), 325, 458 + i * 42));
    }

    // Instruções
    janela.draw(makeText(fonte,
        turnoJogador ? "Setas: selecionar  ENTER: usar  T: skills"
                     : "Inimigo atacando...",
        11, sf::Color(140,130,160), 315, 595));

    desenharLog();
}

void Jogo::desenharSkillTree() {
    sf::Color cor = corElemento();
    janela.draw(makeText(fonte, "SKILL TREE - " + nomeElemento(),
                28, cor, 260, 20));
    janela.draw(makeText(fonte,
                "Pontos: " + std::to_string(
                    jogador->getSkillTree().getPontosDisponiveis()),
                20, sf::Color(220,180,60), 340, 60));

    SkillTree& st = jogador->getSkillTree();
    for (int i = 0; i < st.getTamanho(); i++) {
        Magia* m = st.getMagia(i);
        bool selecionado = (i == magiaSelecionada);
        bool desbloqueado = m->estaDesbloqueada();

        sf::RectangleShape caixa({700.f, 60.f});
        caixa.setPosition(100, 110 + i * 72);
        caixa.setFillColor(desbloqueado
            ? sf::Color(20, 40, 20, 200)
            : sf::Color(30, 25, 45, 200));
        caixa.setOutlineThickness(selecionado ? 2.f : 1.f);
        caixa.setOutlineColor(selecionado ? sf::Color::Yellow
            : (desbloqueado ? sf::Color(60,120,60) : sf::Color(60,50,80)));
        janela.draw(caixa);

        std::string status = desbloqueado ? "[OK] " : "[bloq] ";
        sf::Color corNome  = desbloqueado ? sf::Color(100,220,100)
                                          : sf::Color(180,160,200);
        janela.draw(makeText(fonte, status + m->getNome(),
                    18, corNome, 116, 118 + i * 72));
        janela.draw(makeText(fonte,
                    m->getDescricao() + "  | MP: " +
                    std::to_string(m->getCustoMana()),
                    14, sf::Color(140,130,160), 116, 142 + i * 72));
    }

    janela.draw(makeText(fonte,
                "Setas: navegar  ENTER: desbloquear  ESC: voltar",
                14, sf::Color(140,130,160), 240, 490));
}

void Jogo::desenharGameOver() {
    janela.draw(makeText(fonte, "GAME OVER", 56,
                sf::Color(220, 50, 50), 280, 180));
    janela.draw(makeText(fonte,
                jogador ? jogador->getNome() + " foi derrotado..." : "Derrota...",
                22, sf::Color(180,140,140), 310, 280));
    janela.draw(makeText(fonte, "ENTER para recomecar", 20,
                sf::Color(160,130,160), 320, 400));
}

void Jogo::desenharVitoria() {
    janela.draw(makeText(fonte, "VITORIA!", 56,
                sf::Color(220,180,60), 300, 160));
    janela.draw(makeText(fonte,
                jogador ? jogador->getNome() + " dominou os 4 elementos!" : "",
                22, sf::Color(200,220,160), 240, 270));
    janela.draw(makeText(fonte,
                "XP Total: " + std::to_string(xpTotal),
                20, sf::Color(180,200,160), 360, 340));
    janela.draw(makeText(fonte, "ENTER para recomecar", 20,
                sf::Color(160,160,180), 320, 440));
}