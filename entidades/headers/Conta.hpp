#ifndef CONTA_HPP_INCLUDED
#define CONTA_HPP_INCLUDED

#include "../dominios/Codigo.hpp"
#include "../dominios/Senha.hpp"

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

#endif // CONTA_HPP_INCLUDED

