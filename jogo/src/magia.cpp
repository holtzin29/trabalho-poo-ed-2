#include "../headers/magia.hpp"
using namespace std;

Magia::Magia(string nome, int custoMana, int danoBase)
    : nome(nome), custoMana(custoMana), danoBase(danoBase), desbloqueada(false) {}

string Magia::getNome()          const { return nome; }
int         Magia::getCustoMana()     const { return custoMana; }
int         Magia::getDanoBase()      const { return danoBase; }
bool        Magia::estaDesbloqueada() const { return desbloqueada; }
void        Magia::desbloquear()            { desbloqueada = true; }