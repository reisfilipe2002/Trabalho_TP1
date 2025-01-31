// Data.hpp
#ifndef DATA_HPP_INCLUDED
#define DATA_HPP_INCLUDED

#include <string>
#include "Dominio.hpp"

class Data : public Dominio<std::string> {
protected:
    void validar(const std::string& val) override;
private:
    bool isBissexto(int ano);
};

#endif // DATA_HPP_INCLUDED
