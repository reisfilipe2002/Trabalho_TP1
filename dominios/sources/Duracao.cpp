// Duracao.cpp
#include "Duracao.hpp"

// Implementação do método validar para Duracao
void Duracao::validar(const int& val) {
    if(val <= 0 || val >= 360) {
        throw std::invalid_argument("Duracao deve estar entre 0 e 360.");
    }
}
