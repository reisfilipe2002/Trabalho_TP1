#ifndef ATIVIDADE_HPP_INCLUDED
#define ATIVIDADE_HPP_INCLUDED

#include "../dominios/Codigo.hpp"
#include "../dominios/Nome.hpp"
#include "../dominios/Data.hpp"
#include "../dominios/Horario.hpp"
#include "../dominios/Duracao.hpp"
#include "../dominios/Dinheiro.hpp"
#include "../dominios/Avaliacao.hpp"

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

#endif // ATIVIDADE_HPP_INCLUDED

