#ifndef MAGIAS_FOGO_HPP
#define MAGIAS_FOGO_HPP

#include "../magia.hpp"
#include "../entidade.hpp"
using namespace std;

class BolaDeFogo : public Magia {
    public:
        BolaDeFogo();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        string getDescricao() const override;
};

class Queimadura : public Magia {
    private:
        int turnosRestantes;
    public:
        Queimadura();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        string getDescricao() const override;
        int getTurnosRestantes() const;
};

class ExplosaoFogo : public Magia {
    public:
        ExplosaoFogo();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        string getDescricao() const override;
};

class Inferno : public Magia {
    public:
        Inferno();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        string getDescricao() const override;
};

class ApocalipseDeFogo : public Magia {
    public:
        ApocalipseDeFogo();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        string getDescricao() const override;
};

#endif