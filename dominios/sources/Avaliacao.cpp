// Avaliacao.cpp
#include "Avaliacao.hpp"

// Implementação do método validar para Avaliacao
void Avaliacao::validar(const int& val) {
    if (val < 0 || val > 5) {
        throw std::invalid_argument("Avaliacao deve ser um valor entre 0 e 5.");
    }
}
