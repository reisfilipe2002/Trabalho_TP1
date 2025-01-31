#include "Atividade.hpp"

void Atividade::setCodigo(const std::string& val) {
    codigo.setValor(val);
}

void Atividade::setNome(const std::string& val) {
    nome.setValor(val);
}

void Atividade::setData(const std::string& val) {
    data.setValor(val);
}

void Atividade::setHorario(const std::string& val) {
    horario.setValor(val);
}

void Atividade::setDuracao(int val) {
    duracao.setValor(val);
}

void Atividade::setPreco(double val) {
    preco.setValor(val);
}

void Atividade::setAvaliacao(int val) {
    avaliacao.setValor(val);
}

std::string Atividade::getCodigo() const {
    return codigo.getValor();
}

std::string Atividade::getNome() const {
    return nome.getValor();
}

std::string Atividade::getData() const {
    return data.getValor();
}

std::string Atividade::getHorario() const {
    return horario.getValor();
}

int Atividade::getDuracao() const {
    return duracao.getValor();
}

double Atividade::getPreco() const {
    return preco.getValor();
}

int Atividade::getAvaliacao() const {
    return avaliacao.getValor();
}
