#include "../headers/jogo.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;
using namespace sf;

// ─── construtor ───────────────────────────────────────────────────────────────
Jogo::Jogo()
    : janela(VideoMode(1366, 768), "Mago Arcano",
             Style::Titlebar | Style::Close),
      estado(MENU_PRINCIPAL),
      rodada(1), xpTotal(0),
      magiaSelecionada(0), turnoJogador(true),
      temporizadorInimigo(0.f), tempoMovimento(0.f), tipoSelecionado(0), faseAtual(1)
{
    janela.setFramerateLimit(60);
    if (!fonte.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"))
        if (!fonte.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf"))
            cerr << "Fonte não encontrada, usando padrão\n";
}

// ─── loop principal ────────────────────────────────────────────────────────────
void Jogo::rodar() {
    Clock relogio;
    while (janela.isOpen()) {
        float dt = relogio.restart().asSeconds();
        Event evento;

        while (janela.pollEvent(evento)) {
            if (evento.type == Event::Closed)
                janela.close();

            // ── MENU PRINCIPAL ──
            if (estado == MENU_PRINCIPAL) {
                if (evento.type == Event::KeyPressed)
                    estado = SELECAO_TIPO;
            }

            // ── SELEÇÃO DE TIPO ──
            else if (estado == SELECAO_TIPO) {
                if (evento.type == Event::KeyPressed) {
                    if (evento.key.code == Keyboard::Left)
                        tipoSelecionado = (tipoSelecionado + 3) % 4;
                    if (evento.key.code == Keyboard::Right)
                        tipoSelecionado = (tipoSelecionado + 1) % 4;
                    if (evento.key.code == Keyboard::Return)
                        estado = SELECAO_NOME;
                }
            }

            // ── SELEÇÃO DE NOME ──
            else if (estado == SELECAO_NOME) {
                if (evento.type == Event::TextEntered) {
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
                if (evento.type == Event::KeyPressed) {
                    int tam = jogador->getSkillTree().getTamanho();
                    if (evento.key.code == Keyboard::Up)
                        magiaSelecionada = (magiaSelecionada + tam - 1) % tam;
                    if (evento.key.code == Keyboard::Down)
                        magiaSelecionada = (magiaSelecionada + 1) % tam;
                    if (evento.key.code == Keyboard::Return) {
                        usarMagia(magiaSelecionada);
                    }
                    if (evento.key.code == Keyboard::T)
                        estado = SKILL_TREE;
                }
            }

            // ── SKILL TREE ──
            else if (estado == SKILL_TREE) {
                if (evento.type == Event::KeyPressed) {
                    int tam = jogador->getSkillTree().getTamanho();
                    if (evento.key.code == Keyboard::Up)
                        magiaSelecionada = (magiaSelecionada + tam - 1) % tam;
                    if (evento.key.code == Keyboard::Down)
                        magiaSelecionada = (magiaSelecionada + 1) % tam;
                    if (evento.key.code == Keyboard::Return)
                        jogador->desbloquearHabilidade(magiaSelecionada);
                    if (evento.key.code == Keyboard::Escape)
                        estado = COMBATE;
                }
            }

            // ── GAME OVER / VITORIA ──
            else if (estado == GAME_OVER || estado == VITORIA) {
                if (evento.type == Event::KeyPressed &&
                    evento.key.code == Keyboard::Return) {
                    delete jogador;
                    delete inimigo;
                    nomeTemp.clear();
                    rodada = 1; xpTotal = 0;
                    magiaSelecionada = 0;
                    turnoJogador = true;
                    logCombate.clear();
                    estado = MENU_PRINCIPAL;
                }
            }
        }

        // movimento do jogador no mapa
        if (estado == COMBATE) {
            atualizarMovimento(dt);
        }

        // turno do inimigo com delay
        if (estado == COMBATE && !turnoJogador) {
            temporizadorInimigo -= dt;
            if (temporizadorInimigo <= 0.f) {
                turnoInimigo();
            }
        }

        // renderização
        janela.clear(Color(15, 12, 25));
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
Color Jogo::corElemento() const {
    switch (tipoSelecionado) {
        case 0: return Color(255, 80,  30);   // fogo
        case 1: return Color(30,  160, 255);  // agua
        case 2: return Color(140, 100, 40);   // terra
        case 3: return Color(180, 240, 255);  // ar
        default: return Color::White;
    }
}

string Jogo::nomeElemento() const {
    switch (tipoSelecionado) {
        case 0: return "FOGO";  case 1: return "AGUA";
        case 2: return "TERRA"; case 3: return "AR";
        default: return "";
    }
}

string Jogo::emojiBoss() const {
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
void Jogo::criarJogador(int tipo, const string& nome) {
    switch (tipo) {
        case 0: jogador = new MagoFogo(nome);  break;
        case 1: jogador = new MagoAgua(nome);  break;
        case 2: jogador = new MagoTerra(nome); break;
        case 3: jogador = new MagoAr(nome);    break;
    }
    
    // Cria pixel art do jogador
    TipoMago tipos[] = {FOGO, AGUA, TERRA, AR};
    jogadorPixel = new MagoPixel(5, 7, tipos[tipo], nome);
}

void Jogo::iniciarRodada() {
    // Determina a fase baseado na rodada
    faseAtual = min(rodada, 4);
    
    // Cria o mapa da fase
    mapa = new Mapa(faseAtual);
    
    // escala de inimigos por rodada
    TipoInimigo tipos[] = {GOBLIN, ESQUELETO, GOLEM, DRAGAO};
    TipoInimigo tipo = tipos[min(rodada - 1, 3)];
    inimigo = 
        FabricaInimigos::criar(tipo, jogador->getNivel());
    
    // Cria pixel art do inimigo
    TipoInimigoPixel tiposPixel[] = {GOBLIN_PIX, SKELETON_PIX, GOLEM_PIX, DRAGON_PIX};
    TipoMago elementoInimigo = static_cast<TipoMago>(rand() % 4);
    inimigoPixel = new InimigoPixel(14, 7, elementoInimigo, 
                                   tiposPixel[min(rodada - 1, 3)]);
    
    turnoJogador = true;
    magiaSelecionada = 0;
    adicionarLog("-- Rodada " + to_string(rodada) +
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
    ostringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    jogador->usarMagia(indice, inimigo);
    cout.rdbuf(old);
    adicionarLog(buffer.str());

    // efeitos especiais por magia
    string nomeMagia = m->getNome();
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

    ostringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    inimigo->atacar(jogador);
    cout.rdbuf(old);
    adicionarLog(buffer.str());

    jogador->regenerarMana();
    verificarFimCombate();
    if (estado == COMBATE)
        turnoJogador = true;
}

void Jogo::atualizarMovimento(float dt) {
    if (!jogadorPixel || !mapa) return;

    tempoMovimento -= dt;
    if (tempoMovimento > 0.f) return;

    int dx = 0;
    int dy = 0;
    if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
        dx = -1;
    else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
        dx = 1;
    else if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
        dy = -1;
    else if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
        dy = 1;

    if (dx == 0 && dy == 0) return;

    int novaX = jogadorPixel->getGridX() + dx;
    int novaY = jogadorPixel->getGridY() + dy;
    if (novaX < 0 || novaX >= mapa->getLargura() ||
        novaY < 0 || novaY >= mapa->getAltura())
        return;

    TileType destino = mapa->getTile(novaX, novaY);
    if (destino == TILE_WATER || destino == TILE_MOUNTAIN ||
        destino == TILE_LAVA) {
        adicionarLog("Caminho bloqueado.");
        return;
    }

    if (inimigoPixel && inimigoPixel->getGridX() == novaX &&
        inimigoPixel->getGridY() == novaY) {
        adicionarLog("Inimigo bloqueia o caminho.");
        return;
    }

    jogadorPixel->setPosicao(novaX, novaY);
    tempoMovimento = 0.10f;
}

void Jogo::verificarFimCombate() {
    if (!inimigo->estaVivo()) {
        int xp = inimigo->getXpRecompensa();
        adicionarLog(inimigo->getNome() + " derrotado! +" + to_string(xp) + " XP");
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
        adicionarLog("LEVEL UP! Nivel " + to_string(jogador->getNivel()) +
                     " | +2 pontos de habilidade!");
    }
}

void Jogo::adicionarLog(const string& msg) {
    if (msg.empty()) return;
    // quebra mensagens longas
    istringstream stream(msg);
    string linha;
    while (getline(stream, linha)) {
        if (!linha.empty())
            logCombate.push_back(linha);
    }
    // mantém só as últimas 6 linhas
    while (logCombate.size() > 6)
        logCombate.erase(logCombate.begin());
}

// ─── desenho ──────────────────────────────────────────────────────────────────
void Jogo::desenharBarraHP(float x, float y, float largura,
                            int hp, int hpMax, Color cor) {
    RectangleShape fundo({largura, 14.f});
    fundo.setPosition(x, y);
    fundo.setFillColor(Color(50, 20, 20));
    janela.draw(fundo);

    float pct = max(0.f, (float)hp / hpMax);
    RectangleShape barra({largura * pct, 14.f});
    barra.setPosition(x, y);
    barra.setFillColor(cor);
    janela.draw(barra);

    Text txt;
    txt.setFont(fonte);
    txt.setCharacterSize(11);
    txt.setFillColor(Color::White);
    txt.setString(to_string(hp) + "/" + to_string(hpMax));
    txt.setPosition(x + largura / 2 - 20, y);
    janela.draw(txt);
}

void Jogo::desenharBarraMP(float x, float y, float largura, int mp, int mpMax) {
    RectangleShape fundo({largura, 14.f});
    fundo.setPosition(x, y);
    fundo.setFillColor(Color(20, 20, 60));
    janela.draw(fundo);

    float pct = max(0.f, (float)mp / mpMax);
    RectangleShape barra({largura * pct, 14.f});
    barra.setPosition(x, y);
    barra.setFillColor(Color(80, 100, 255));
    janela.draw(barra);

    Text txt;
    txt.setFont(fonte);
    txt.setCharacterSize(11);
    txt.setFillColor(Color::White);
    txt.setString(to_string(mp) + "/" + to_string(mpMax));
    txt.setPosition(x + largura / 2 - 20, y);
    janela.draw(txt);
}

// helper para texto simples
static Text makeText(const Font& f, const string& s,
                          unsigned sz, Color c, float x, float y) {
    Text t;
    t.setFont(f);
    t.setString(s);
    t.setCharacterSize(sz);
    t.setFillColor(c);
    t.setPosition(x, y);
    return t;
}

static Text makeTextClamped(const Font& f, const string& s,
                                  unsigned sz, Color c,
                                  float x, float y, float maxWidth) {
    Text t = makeText(f, s, sz, c, x, y);
    if (t.getLocalBounds().width <= maxWidth)
        return t;

    string truncated = s;
    while (!truncated.empty()) {
        truncated.pop_back();
        t.setString(truncated + "...");
        if (t.getLocalBounds().width <= maxWidth)
            break;
    }
    return t;
}

static Text centerText(const Font& f, const string& s,
                             unsigned sz, Color c, float centerX, float y) {
    Text t = makeText(f, s, sz, c, 0.f, y);
    FloatRect bounds = t.getLocalBounds();
    t.setPosition(centerX - bounds.width / 2.f,
                  y - bounds.top);
    return t;
}

void Jogo::desenharMenu() {
    janela.draw(centerText(fonte, "MAGO ARCANO", 60,
                Color(220, 180, 60), 683.f, 160));
    janela.draw(centerText(fonte, "Um jogo de magia elementar", 20,
                Color(160, 140, 200), 683.f, 250));
    janela.draw(centerText(fonte, "Pressione qualquer tecla para comecar", 24,
                Color(200, 200, 255), 683.f, 380));
    janela.draw(centerText(fonte, "Use setas e ENTER para escolher", 16,
                Color(140, 140, 180), 683.f, 500));
}

void Jogo::desenharSelecaoTipo() {
    janela.draw(centerText(fonte, "Escolha seu elemento:", 32,
                Color(220, 200, 255), 683.f, 80));

    struct Info { string nome; string desc; Color cor; };
    Info infos[4] = {
        {"FOGO",  "Alto dano\nAtaques explosivos",    Color(255, 80,  30)},
        {"AGUA",  "Cura e controle\nDano sustentado", Color(30,  160, 255)},
        {"TERRA", "Alta defesa\nDano pesado",          Color(160, 120, 40)},
        {"AR",    "Velocidade\nRajadas multiplas",     Color(180, 240, 255)},
    };

    float baseX = 243.f;
    float baseY = 170.f;
    for (int i = 0; i < 4; i++) {
        float x = baseX + i * 220.f;
        float y = baseY;
        bool sel = (i == tipoSelecionado);

        RectangleShape caixa({160.f, 220.f});
        caixa.setPosition(x, y);
        caixa.setFillColor(sel
            ? Color(infos[i].cor.r/4, infos[i].cor.g/4, infos[i].cor.b/4, 200)
            : Color(30, 25, 45, 180));
        caixa.setOutlineThickness(sel ? 3.f : 1.f);
        caixa.setOutlineColor(sel ? infos[i].cor : Color(60, 50, 80));
        janela.draw(caixa);

        string simbolo[] = {"  ^v^", "  ~~~", "  ###", "  >>>"};
        janela.draw(makeText(fonte, simbolo[i], 28, infos[i].cor, x + 20, y + 20));
        janela.draw(makeText(fonte, infos[i].nome, 20,
                    sel ? infos[i].cor : Color(200,200,200), x + 20, y + 80));

        istringstream ss(infos[i].desc);
        string linha; int ly = 0;
        while (getline(ss, linha)) {
            janela.draw(makeText(fonte, linha, 13,
                        Color(160,160,160), x + 10, y + 110 + ly * 20));
            ly++;
        }
    }

    janela.draw(centerText(fonte, "< use as setas e ENTER para confirmar >", 16,
                Color(160, 140, 200), 683.f, 430));
}

void Jogo::desenharSelecaoNome() {
    Color cor = corElemento();
    janela.draw(centerText(fonte, "Mago de " + nomeElemento(), 34, cor, 683.f, 120));
    janela.draw(centerText(fonte, "Digite seu nome:", 24,
                Color(200,200,255), 683.f, 200));

    RectangleShape caixa({380.f, 48.f});
    caixa.setPosition(683.f - 190.f, 240.f);
    caixa.setFillColor(Color(30, 25, 45));
    caixa.setOutlineThickness(2.f);
    caixa.setOutlineColor(cor);
    janela.draw(caixa);

    janela.draw(makeText(fonte, nomeTemp + "_", 24,
                Color::White, 683.f - 180.f, 252));
    janela.draw(centerText(fonte, "ENTER para confirmar", 16,
                Color(140,120,180), 683.f, 320));
}

void Jogo::desenharHUD() {
    if (!jogador || !inimigo) return;
    Color cor = corElemento();

    RectangleShape painelJogador({420.f, 100.f});
    painelJogador.setPosition(40.f, 20.f);
    painelJogador.setFillColor(Color(20, 16, 35, 220));
    painelJogador.setOutlineThickness(2.f);
    painelJogador.setOutlineColor(cor);
    janela.draw(painelJogador);

    janela.draw(makeText(fonte, jogador->getNome() + " [Nv." +
                to_string(jogador->getNivel()) + "]",
                18, cor, 52, 24));
    janela.draw(makeText(fonte, "HP", 13, Color(255,100,100), 52, 46));
    desenharBarraHP(92, 46, 300, jogador->getVida(),
                    jogador->getVidaMaxima(), Color(200,50,50));
    janela.draw(makeText(fonte, "MP", 13, Color(100,100,255), 52, 68));
    desenharBarraMP(92, 68, 300, jogador->getMana(), jogador->getManaMaxima());
    janela.draw(makeText(fonte,
                "For: " + to_string(jogador->getAtributos().getForca()) +
                "  Agi: " + to_string(jogador->getAtributos().getAgilidade()),
                13, Color(160,160,200), 52, 90));

    RectangleShape painelInfo({360.f, 100.f});
    painelInfo.setPosition(503.f, 20.f);
    painelInfo.setFillColor(Color(18, 16, 28, 220));
    painelInfo.setOutlineThickness(2.f);
    painelInfo.setOutlineColor(Color(180, 180, 100));
    janela.draw(painelInfo);

    janela.draw(centerText(fonte, "Rodada " + to_string(rodada) + "/4", 22,
                Color(220,180,100), 683.f, 36));
    janela.draw(centerText(fonte, "XP Total: " + to_string(xpTotal), 18,
                Color(200,200,160), 683.f, 64));
    janela.draw(centerText(fonte, nomeElemento(), 18,
                cor, 683.f, 88));

    RectangleShape painelInimigo({420.f, 100.f});
    painelInimigo.setPosition(906.f, 20.f);
    painelInimigo.setFillColor(Color(35, 16, 16, 220));
    painelInimigo.setOutlineThickness(2.f);
    painelInimigo.setOutlineColor(Color(200,100,100));
    janela.draw(painelInimigo);

    janela.draw(makeText(fonte, emojiBoss() + " " + inimigo->getNome(),
                18, Color(255,120,120), 918, 24));
    janela.draw(makeText(fonte, "HP", 13, Color(255,100,100), 918, 46));
    desenharBarraHP(958, 46, 300, inimigo->getVida(),
                    inimigo->getVidaMaxima(), Color(200,50,50));
}

void Jogo::desenharLog() {
    RectangleShape painel({516.f, 150.f});
    painel.setPosition(790.f, 600.f);
    painel.setFillColor(Color(10, 8, 20, 230));
    painel.setOutlineThickness(2.f);
    painel.setOutlineColor(Color(60, 50, 80));
    janela.draw(painel);

    janela.draw(makeText(fonte, "Eventos de combate:", 16,
                Color(200,200,255), 800, 608));

    for (int i = 0; i < (int)logCombate.size(); i++) {
        float alpha = 160.f + (float)i / max(1, (int)logCombate.size()) * 95.f;
        janela.draw(makeText(fonte, logCombate[i], 13,
                    Color(200, 190, 220, (uint8_t)alpha),
                    800, 630 + i * 18));
    }
}

void Jogo::desenharCombate() {
    mapa->desenhar(janela);

    if (jogadorPixel) {
        jogadorPixel->desenhar(janela, 32);
    }
    if (inimigoPixel) {
        inimigoPixel->desenhar(janela, 32);
    }

    desenharHUD();

    SkillTree& st = jogador->getSkillTree();
    float painelAltura = 90.f + st.getTamanho() * 52.f;
    if (painelAltura < 220.f) painelAltura = 220.f;

    RectangleShape painelMagias({300.f, painelAltura});
    painelMagias.setPosition(1030.f, 140.f);
    painelMagias.setFillColor(Color(18, 14, 30, 220));
    painelMagias.setOutlineThickness(2.f);
    painelMagias.setOutlineColor(corElemento());
    janela.draw(painelMagias);

    float textoMax = 280.f;
    float textoX = 1040.f;

    janela.draw(makeTextClamped(fonte, "MAGIAS DISPONIVEIS", 18,
                corElemento(), textoX, 148, textoMax));

    for (int i = 0; i < st.getTamanho(); i++) {
        Magia* m = st.getMagia(i);
        bool selecionado = (i == magiaSelecionada);
        bool desbloqueado = m->estaDesbloqueada();

        Color cor = desbloqueado
            ? (selecionado ? Color::Yellow : Color(200,200,200))
            : Color(140, 130, 150);

        string prefixo = selecionado ? "> " : "  ";
        string lock    = desbloqueado ? "" : " [L]";
        string custo   = "MP:" + to_string(m->getCustoMana());
        float baseY = 178 + i * 52;

        janela.draw(makeTextClamped(fonte, prefixo + m->getNome() + lock,
                    14, cor, textoX, baseY, textoMax));
        janela.draw(makeTextClamped(fonte, m->getDescricao() + "  " + custo,
                    12, Color(180,170,190), textoX, baseY + 18, textoMax));
    }

    float instrucoesY = 178 + st.getTamanho() * 52.f;
    janela.draw(makeTextClamped(fonte,
        turnoJogador ? "WASD mover  SETAS selecionar  ENTER usar  T skill"
                     : "Inimigo atacando...",
        14, Color(180,180,210), textoX, instrucoesY, textoMax));

    desenharLog();
}

void Jogo::desenharSkillTree() {
    Color cor = corElemento();
    janela.draw(makeText(fonte, "SKILL TREE - " + nomeElemento(),
                28, cor, 260, 20));
    janela.draw(makeText(fonte,
                "Pontos: " + to_string(
                    jogador->getSkillTree().getPontosDisponiveis()),
                20, Color(220,180,60), 340, 60));

    SkillTree& st = jogador->getSkillTree();
    for (int i = 0; i < st.getTamanho(); i++) {
        Magia* m = st.getMagia(i);
        bool selecionado = (i == magiaSelecionada);
        bool desbloqueado = m->estaDesbloqueada();

        RectangleShape caixa({700.f, 60.f});
        caixa.setPosition(100, 110 + i * 72);
        caixa.setFillColor(desbloqueado
            ? Color(20, 40, 20, 200)
            : Color(30, 25, 45, 200));
        caixa.setOutlineThickness(selecionado ? 2.f : 1.f);
        caixa.setOutlineColor(selecionado ? Color::Yellow
            : (desbloqueado ? Color(60,120,60) : Color(60,50,80)));
        janela.draw(caixa);

        string status = desbloqueado ? "[OK] " : "[bloq] ";
        Color corNome  = desbloqueado ? Color(100,220,100)
                                          : Color(180,160,200);
        janela.draw(makeText(fonte, status + m->getNome(),
                    18, corNome, 116, 118 + i * 72));
        janela.draw(makeText(fonte,
                    m->getDescricao() + "  | MP: " +
                    to_string(m->getCustoMana()),
                    14, Color(140,130,160), 116, 142 + i * 72));
    }

    janela.draw(makeText(fonte,
                "Setas: navegar  ENTER: desbloquear  ESC: voltar",
                14, Color(140,130,160), 240, 490));
}

void Jogo::desenharGameOver() {
    janela.draw(makeText(fonte, "GAME OVER", 56,
                Color(220, 50, 50), 280, 180));
    janela.draw(makeText(fonte,
                jogador ? jogador->getNome() + " foi derrotado..." : "Derrota...",
                22, Color(180,140,140), 310, 280));
    janela.draw(makeText(fonte, "ENTER para recomecar", 20,
                Color(160,130,160), 320, 400));
}

void Jogo::desenharVitoria() {
    janela.draw(makeText(fonte, "VITORIA!", 56,
                Color(220,180,60), 300, 160));
    janela.draw(makeText(fonte,
                jogador ? jogador->getNome() + " dominou os 4 elementos!" : "",
                22, Color(200,220,160), 240, 270));
    janela.draw(makeText(fonte,
                "XP Total: " + to_string(xpTotal),
                20, Color(180,200,160), 360, 340));
    janela.draw(makeText(fonte, "ENTER para recomecar", 20,
                Color(160,160,180), 320, 440));
}