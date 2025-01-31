#ifndef DESTINO_HPP_INCLUDED
#define DESTINO_HPP_INCLUDED

#include "../dominios/Codigo.hpp"
#include "../dominios/Nome.hpp"
#include "../dominios/Data.hpp"
#include "../dominios/Avaliacao.hpp"

class Destino {
private:
    Codigo codigo;
    Nome nome;
    Data dataInicio;
    Data dataTermino;
    Avaliacao avaliacao;
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
};

#endif // DESTINO_HPP_INCLUDED

