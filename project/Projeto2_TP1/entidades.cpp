#include "entidades.h"

// =========== Atividade =================================
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

// =========== Conta =================================
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

// =========== Destino =================================
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

void Destino::adicionarAtividade(const Atividade& atividade) {
    if (!validarDataAtividade(atividade.getData())) {
        throw std::invalid_argument("Data da atividade fora do intervalo do destino.");
    }
    atividades.push_back(atividade);
}

void Destino::adicionarHospedagem(const Hospedagem& hospedagem) {
    hospedagens.push_back(hospedagem);
}

std::vector<Atividade> Destino::getAtividades() const {
    return atividades;
}

std::vector<Hospedagem> Destino::getHospedagens() const {
    return hospedagens;
}

bool Destino::validarDataAtividade(const std::string& dataAtividade) const {
    return dataAtividade >= dataInicio.getValor() && dataAtividade <= dataTermino.getValor();
}

// =========== Viagem =================================
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

void Viagem::adicionarDestino(const Destino& destino) {
    destinos.push_back(destino);
}

std::vector<Destino> Viagem::getDestinos() const {
    return destinos;
}

// =========== Hospedagem =================================
void Hospedagem::setCodigo(const std::string& val) {
    codigo.setValor(val);
}

void Hospedagem::setNome(const std::string& val) {
    nome.setValor(val);
}

void Hospedagem::setDiaria(double val) {
    diaria.setValor(val);
}

void Hospedagem::setAvaliacao(int val) {
    avaliacao.setValor(val);
}

std::string Hospedagem::getCodigo() const {
    return codigo.getValor();
}

std::string Hospedagem::getNome() const {
    return nome.getValor();
}

double Hospedagem::getDiaria() const {
    return diaria.getValor();
}

int Hospedagem::getAvaliacao() const {
    return avaliacao.getValor();
}

// =========== Viajante =================================
Conta Viajante::getConta() const {
    return conta;
}

void Viajante::adicionarViagem(const Viagem& viagem) {
    viagens.push_back(viagem);
}

std::vector<Viagem> Viajante::getViagens() const {
    return viagens;
}