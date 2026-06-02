#ifndef MAGIAS_TERRA_HPP
#define MAGIAS_TERRA_HPP

#include "../magia.hpp"
#include "../entidade.hpp"
using namespace std;

class Pedrada : public Magia {
    public:
        Pedrada();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        string getDescricao() const override;
};

class ChuvaDeRochas : public Magia {
    public:
        ChuvaDeRochas();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        string getDescricao() const override;
};

class Terremoto : public Magia {
    public:
        Terremoto();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        string getDescricao() const override;
};

class MuralhaDeRocha : public Magia {
    public:
        MuralhaDeRocha();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        string getDescricao() const override;
};

class ColapsoDaTerra : public Magia {
    public:
        ColapsoDaTerra();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        string getDescricao() const override;
};

#endif