#ifndef MAGIA_HPP
#define MAGIA_HPP
#include <string>
#include <iostream>
using namespace std;

class Magia {
    protected:
        string nome;
        int custoMana;
        int danoBase;
        bool desbloqueada;

    public:
        Magia(string nome, int custoMana, int danoBase);
        virtual ~Magia() {}

        // virtual puro -> cada elemento implementa o efeito diferente
        virtual void lancar(class Entidade* lancador, class Entidade* alvo) = 0;
        virtual string getDescricao() const = 0;

        string getNome() const;
        int getCustoMana() const;
        int getDanoBase() const;
        bool estaDesbloqueada() const;
        void desbloquear();
};

#endif