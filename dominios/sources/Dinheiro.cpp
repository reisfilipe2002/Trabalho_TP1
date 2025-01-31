// Dinheiro.cpp
#include "Dinheiro.hpp"

// Implementação do método validar para Dinheiro
void Dinheiro::validar(const double& val) {
    if(val <= 0.00 || val >= 200000.00) {
        throw std::invalid_argument("Dinheiro deve estar entre 0.00 e 200000.00.");
    }
}
