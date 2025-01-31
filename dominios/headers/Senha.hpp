// Senha.hpp
#ifndef SENHA_HPP_INCLUDED
#define SENHA_HPP_INCLUDED

#include "Dominio.hpp"
#include <string>

class Senha : public Dominio<std::string> {
protected:
    void validar(const std::string& val) override;
};

#endif // SENHA_HPP_INCLUDED
