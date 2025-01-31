// Data.cpp
#include "Data.hpp"
#include <regex>
#include <sstream>

// Implementação do método isBissexto
bool Data::isBissexto(int ano) {
    if (ano % 4 != 0) return false;
    if (ano % 100 != 0) return true;
    if (ano % 400 != 0) return false;
    return true;
}

// Implementação do método validar para Data
void Data::validar(const std::string& val) {
    // Formato DD-MM-AA
    std::regex formato(R"((\d{2})-(\d{2})-(\d{2}))");
    std::smatch matches;
    if(!std::regex_match(val, matches, formato)) {
        throw std::invalid_argument("Data deve estar no formato DD-MM-AA.");
    }
    int dia = std::stoi(matches[1]);
    int mes = std::stoi(matches[2]);
    int ano = std::stoi(matches[3]);

    if(mes < 1 || mes > 12) {
        throw std::invalid_argument("Mes deve ser entre 01 e 12.");
    }

    int diasNoMes;
    switch(mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            diasNoMes = 31;
            break;
        case 4: case 6: case 9: case 11:
            diasNoMes = 30;
            break;
        case 2:
            diasNoMes = isBissexto(2000 + ano) ? 29 : 28; // Considerando anos entre 2000 e 2099
            break;
        default:
            diasNoMes = 31;
    }

    if(dia < 1 || dia > diasNoMes) {
        throw std::invalid_argument("Dia invalido para o mes especificado.");
    }
}
