// Senha.cpp
#include "Senha.hpp"
#include <cctype>
#include <algorithm>

// Implementação do método validar para Senha
void Senha::validar(const std::string& val) {
    if(val.length() != 5) {
        throw std::invalid_argument("Senha deve ter exatamente 5 digitos.");
    }
    // Verifica se todos são dígitos
    for(char c : val) {
        if(!std::isdigit(c)) {
            throw std::invalid_argument("Senha deve conter apenas digitos.");
        }
    }
    // Verifica duplicação
    std::string copia = val;
    std::sort(copia.begin(), copia.end());
    for(size_t i = 1; i < copia.length(); ++i) {
        if(copia[i] == copia[i-1]) {
            throw std::invalid_argument("Senha nao pode conter digitos duplicados.");
        }
    }
    // Verifica ordem crescente ou decrescente
    bool crescente = true, decrescente = true;
    for(size_t i = 0; i < val.length() - 1; ++i) {
        if(val[i] + 1 != val[i + 1]) {
            crescente = false;
        }
        if(val[i] - 1 != val[i + 1]) {
            decrescente = false;
        }
    }
    if(crescente || decrescente) {
        throw std::invalid_argument("Senha nao pode estar em ordem crescente ou decrescente.");
    }
}
