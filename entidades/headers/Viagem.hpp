#ifndef VIAGEM_HPP_INCLUDED
#define VIAGEM_HPP_INCLUDED

#include "../dominios/Codigo.hpp"
#include "../dominios/Nome.hpp"
#include "../dominios/Avaliacao.hpp"

class Viagem {
private:
    Codigo codigo;
    Nome nome;
    Avaliacao avaliacao;
public:
    void setCodigo(const std::string& val);
    void setNome(const std::string& val);
    void setAvaliacao(int val);

    std::string getCodigo() const;
    std::string getNome() const;
    int getAvaliacao() const;
};

#endif // VIAGEM_HPP_INCLUDED
