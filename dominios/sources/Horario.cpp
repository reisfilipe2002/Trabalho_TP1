// Horario.cpp
#include "Horario.hpp"
#include <regex>
#include <cctype>

// Implementação do método validar para Horario
void Horario::validar(const std::string& val) {
    // Formato HH:MM
    std::regex formato(R"((\d{2}):(\d{2}))");
    std::smatch matches;
    if(!std::regex_match(val, matches, formato)) {
        throw std::invalid_argument("Horario deve estar no formato HH:MM.");
    }
    int hora = std::stoi(matches[1]);
    int minuto = std::stoi(matches[2]);

    if(hora < 0 || hora > 23) {
        throw std::invalid_argument("Hora deve estar entre 00 e 23.");
    }
    if(minuto < 0 || minuto > 59) {
        throw std::invalid_argument("Minuto deve estar entre 00 e 59.");
    }
}
