// Codigo.hpp
#ifndef CODIGO_HPP_INCLUDED
#define CODIGO_HPP_INCLUDED

#include <string>
#include "Dominio.hpp"

class Codigo : public Dominio<std::string> {
protected:
    void validar(const std::string& val) override;
public:
    Codigo() = default;
    ~Codigo() = default;
};

#endif // CODIGO_HPP_INCLUDED
