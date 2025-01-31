// Duracao.hpp
#ifndef DURACAO_HPP_INCLUDED
#define DURACAO_HPP_INCLUDED

#include "Dominio.hpp"

class Duracao : public Dominio<int> {
protected:
    void validar(const int& val) override;
public:
    Duracao() = default;
    ~Duracao() = default;
};

#endif // DURACAO_HPP_INCLUDED
