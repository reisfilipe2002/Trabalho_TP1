#include "Viagem.hpp"

void Viagem::setCodigo(const std::string& val) {
    codigo.setValor(val);
}

void Viagem::setNome(const std::string& val) {
    nome.setValor(val);
}

void Viagem::setAvaliacao(int val) {
    avaliacao.setValor(val);
}

std::string Viagem::getCodigo() const {
    return codigo.getValor();
}

std::string Viagem::getNome() const {
    return nome.getValor();
}

int Viagem::getAvaliacao() const {
    return avaliacao.getValor();
}
