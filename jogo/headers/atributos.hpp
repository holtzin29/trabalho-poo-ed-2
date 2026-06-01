#ifndef ATRIBUTOS_HPP
#define ATRIBUTOS_HPP

// TODO -> definir forca e agilidade base (todo personagem começa com isso no nivel 1)
#define ATRIBUTOS_BASE_FORCA 
#define ATRIBUTOS_BASE_AGILIDADE 

class Atributos {
    private:
    int forca;
    int agilidade;
    int regeneracao; 

    static int totalCriados; // contadr
    public:
    Atributos();
    Atributos(int forc, int ag, int regen);

    public:
    int getForca();
    int getAgilidade();
    int getRegeneracao();

    void setForca(int f);
    void setAgilidade(int v);
    void setRegen(int r);
};
#endif