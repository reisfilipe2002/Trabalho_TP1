// Codigo.cpp
#include "Codigo.hpp"
#include <cctype>

// Implementação do método validar para Codigo
void Codigo::validar(const std::string& val) {
    if(val.length() != 6) {
        throw std::invalid_argument("Codigo deve ter exatamente 6 caracteres.");
    }
    for(char c : val) {
        if(!std::isalnum(c)) {
            throw std::invalid_argument("Codigo deve conter apenas letras ou digitos.");
        }
    }
}
