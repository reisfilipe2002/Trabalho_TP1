#include "Destino.hpp"


void Destino::setCodigo(const std::string& val) {
    codigo.setValor(val);
}

void Destino::setNome(const std::string& val) {
    nome.setValor(val);
}

void Destino::setDataInicio(const std::string& val) {
    dataInicio.setValor(val);
}

void Destino::setDataTermino(const std::string& val) {
    dataTermino.setValor(val);
}

void Destino::setAvaliacao(int val) {
    avaliacao.setValor(val);
}

std::string Destino::getCodigo() const {
    return codigo.getValor();
}

std::string Destino::getNome() const {
    return nome.getValor();
}

std::string Destino::getDataInicio() const {
    return dataInicio.getValor();
}

std::string Destino::getDataTermino() const {
    return dataTermino.getValor();
}

int Destino::getAvaliacao() const {
    return avaliacao.getValor();
}

