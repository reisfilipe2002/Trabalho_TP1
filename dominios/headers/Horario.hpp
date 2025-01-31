// Horario.hpp
#ifndef HORARIO_HPP_INCLUDED
#define HORARIO_HPP_INCLUDED

#include "Dominio.hpp"
#include <string>

class Horario : public Dominio<std::string> {
protected:
    void validar(const std::string& val) override;
};

#endif // HORARIO_HPP_INCLUDED
