// Dinheiro.hpp
#ifndef DINHEIRO_HPP_INCLUDED
#define DINHEIRO_HPP_INCLUDED

#include "Dominio.hpp"

class Dinheiro : public Dominio<double> {
protected:
    void validar(const double& val) override;
public:
    Dinheiro() = default;
    ~Dinheiro() = default;
};

#endif // DINHEIRO_HPP_INCLUDED
