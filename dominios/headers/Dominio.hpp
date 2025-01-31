// Dominio.hpp
#ifndef DOMINIO_HPP_INCLUDED
#define DOMINIO_HPP_INCLUDED

#include <stdexcept>

template <typename Tipo>
class Dominio {
protected:
    Tipo valor; // Atributo para armazenar valor.
    virtual void validar(const Tipo&) = 0; // Método abstrato de validação.
public:
    void setValor(const Tipo& val); // Método para atribuir valor.
    Tipo getValor() const; // Método para recuperar valor.
};

template <typename Tipo>
void Dominio<Tipo>::setValor(const Tipo& val) {
    validar(val); // Lança exceção se inválido
    valor = val;
}

template <typename Tipo>
Tipo Dominio<Tipo>::getValor() const {
    return valor;
}

#endif // DOMINIO_HPP_INCLUDED


