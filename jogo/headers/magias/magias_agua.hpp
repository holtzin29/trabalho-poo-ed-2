#ifndef MAGIAS_AGUA_HPP
#define MAGIAS_AGUA_HPP
#include "../magia.hpp"
#include "../entidade.hpp"

class JatoDeAgua : public Magia {
    public:
        JatoDeAgua();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        std::string getDescricao() const override;
};

class OndaGelada : public Magia {
    public:
        OndaGelada();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        std::string getDescricao() const override;
};

class CuraAgua : public Magia {
    public:
        CuraAgua();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        std::string getDescricao() const override;
};

class MareAlta : public Magia {
    public:
        MareAlta();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        std::string getDescricao() const override;
};

class Tsunami : public Magia {
    public:
        Tsunami();
        void lancar(Entidade* lancador, Entidade* alvo) override;
        std::string getDescricao() const override;
};

#endif