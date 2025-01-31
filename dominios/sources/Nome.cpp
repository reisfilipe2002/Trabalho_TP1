// Nome.cpp
#include "Nome.hpp"
#include <cctype>

// Implementação do método validar para Nome
void Nome::validar(const std::string& val) {
    if(val.length() > 30) {
        throw std::invalid_argument("Nome deve ter ate 30 caracteres.");
    }
    // Verifica se contém apenas letras e espaços
    for(char c : val) {
        if(!std::isalpha(c) && c != ' ') {
            throw std::invalid_argument("Nome deve conter apenas letras e espacos.");
        }
    }
}
