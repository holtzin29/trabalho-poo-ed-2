#ifndef MAGIAS_AR_HPP
#define MAGIAS_AR_HPP

#include "../magia.hpp"
#include "../entidade.hpp"
using namespace std;

class RajadaDeVento : public Magia {
    public:
        RajadaDeVento();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        string getDescricao() const override;
};

class CorrenteDeAr : public Magia {
    public:
        CorrenteDeAr();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        string getDescricao() const override;
};

class Tornado : public Magia {
    public:
        Tornado();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        string getDescricao() const override;
};

class OlhoDoFuracão : public Magia {
    public:
        OlhoDoFuracão();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        string getDescricao() const override;
};

class TempestadeArcana : public Magia {
    public:
        TempestadeArcana();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        string getDescricao() const override;
};

#endif