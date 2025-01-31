// Avaliacao.hpp
#ifndef AVALIACAO_HPP_INCLUDED
#define AVALIACAO_HPP_INCLUDED

#include <stdexcept>
#include <string>
#include "Dominio.hpp"

class Avaliacao : public Dominio<int> {
protected:
    void validar(const int& val) override;
public:
    Avaliacao() = default;
    ~Avaliacao() = default;
};

#endif // AVALIACAO_HPP_INCLUDED
