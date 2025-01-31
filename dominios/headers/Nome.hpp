// Nome.hpp
#ifndef NOME_HPP_INCLUDED
#define NOME_HPP_INCLUDED

#include "Dominio.hpp"
#include <string>

class Nome : public Dominio<std::string> {
protected:
    void validar(const std::string& val) override;
};

#endif // NOME_HPP_INCLUDED
