#include "Conta.hpp"

void Conta::setCodigo(const std::string& val) {
    codigo.setValor(val);
}

void Conta::setSenha(const std::string& val) {
    senha.setValor(val);
}

std::string Conta::getCodigo() const {
    return codigo.getValor();
}

std::string Conta::getSenha() const {
    return senha.getValor();
}
