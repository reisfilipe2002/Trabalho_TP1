#ifndef ENTIDADES_H_INCLUDED
#define ENTIDADES_H_INCLUDED

#include "dominios.h"
#include <vector>
#include <stdexcept>

class Atividade {
private:
    Codigo codigo;
    Nome nome;
    Data data;
    Horario horario;
    Duracao duracao;
    Dinheiro preco;
    Avaliacao avaliacao;

public:
    void setCodigo(const std::string& val);
    void setNome(const std::string& val);
    void setData(const std::string& val);
    void setHorario(const std::string& val);
    void setDuracao(int val);
    void setPreco(double val);
    void setAvaliacao(int val);

    std::string getCodigo() const;
    std::string getNome() const;
    std::string getData() const;
    std::string getHorario() const;
    int getDuracao() const;
    double getPreco() const;
    int getAvaliacao() const;
};

class Conta {
private:
    Codigo codigo;
    Senha senha;

public:
    void setCodigo(const std::string& val);
    void setSenha(const std::string& val);

    std::string getCodigo() const;
    std::string getSenha() const;
};

class Destino {
private:
    Codigo codigo;
    Nome nome;
    Data dataInicio;
    Data dataTermino;
    Avaliacao avaliacao;
    std::vector<Atividade> atividades;
    std::vector<Hospedagem> hospedagens;

public:
    void setCodigo(const std::string& val);
    void setNome(const std::string& val);
    void setDataInicio(const std::string& val);
    void setDataTermino(const std::string& val);
    void setAvaliacao(int val);

    std::string getCodigo() const;
    std::string getNome() const;
    std::string getDataInicio() const;
    std::string getDataTermino() const;
    int getAvaliacao() const;

    void adicionarAtividade(const Atividade& atividade);
    void adicionarHospedagem(const Hospedagem& hospedagem);
    std::vector<Atividade> getAtividades() const;
    std::vector<Hospedagem> getHospedagens() const;

    bool validarDataAtividade(const std::string& dataAtividade) const;
};

class Viagem {
private:
    Codigo codigo;
    Nome nome;
    Avaliacao avaliacao;
    std::vector<Destino> destinos;

public:
    void setCodigo(const std::string& val);
    void setNome(const std::string& val);
    void setAvaliacao(int val);

    std::string getCodigo() const;
    std::string getNome() const;
    int getAvaliacao() const;

    void adicionarDestino(const Destino& destino);
    std::vector<Destino> getDestinos() const;
};

class Hospedagem {
private:
    Codigo codigo;
    Nome nome;
    Dinheiro diaria;
    Avaliacao avaliacao;

public:
    void setCodigo(const std::string& val);
    void setNome(const std::string& val);
    void setDiaria(double val);
    void setAvaliacao(int val);

    std::string getCodigo() const;
    std::string getNome() const;
    double getDiaria() const;
    int getAvaliacao() const;
};

class Viajante {
private:
    Conta conta;
    std::vector<Viagem> viagens;

public:
    void setConta(const Conta& conta);


    Conta getConta() const;

    void adicionarViagem(const Viagem& viagem);
    std::vector<Viagem> getViagens() const;
};

#endif // ENTIDADES_H_INCLUDED