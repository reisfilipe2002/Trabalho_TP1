#ifndef DOMINIOS_H_INCLUDED
#define DOMINIOS_H_INCLUDED

#include <string>
#include <stdexcept>

using namespace std;

///
/// Padrão para representação de código.
///
/// Regras de formato:
///
/// - Seis caracteres;
/// - Cada caractere pode ser letra (A-Z ou a-z) ou dígito (0-9).
///
class Codigo {
private:
    static const int TAMANHO = 6;
    string valor;
    void validar(string);

public:
    Codigo();
    string getValor() const;
    void setValor(const string);
};

inline string Codigo::getValor() const {
    return valor;
}

///
/// Padrão para representação de data.
///
/// Regras de formato:
///
/// - Formato DD-MM-AA;
/// - DD: 00 a 31;
/// - MM: 01 a 12;
/// - AA: 00 a 99;
/// - Considerar anos bissextos.
///
class Data {
private:
    string valor;
    void validar(string);

public:
    Data();
    string getValor() const;
    void setValor(const string);
};

inline string Data::getValor() const {
    return valor;
}

///
/// Padrão para representação de dinheiro.
///
/// Regras de formato:
///
/// - Valor entre 0,00 a 200.000,00.
///
class Dinheiro {
private:
    double valor;
    void validar(double);

public:
    Dinheiro();
    double getValor() const;
    void setValor(const double);
};

inline double Dinheiro::getValor() const {
    return valor;
}

///
/// Padrão para representação de duração.
///
/// Regras de formato:
///
/// - Valor entre 0 a 360.
///
class Duracao {
private:
    int valor;
    void validar(int);

public:
    Duracao();
    int getValor() const;
    void setValor(const int);
};

inline int Duracao::getValor() const {
    return valor;
}

///
/// Padrão para representação de horário.
///
/// Regras de formato:
///
/// - Formato HH:MM;
/// - HH: 00 a 23;
/// - MM: 00 a 59.
///
class Horario {
private:
    string valor;
    void validar(string);

public:
    Horario();
    string getValor() const;
    void setValor(const string);
};

inline string Horario::getValor() const {
    return valor;
}

///
/// Padrão para representação de nome.
///
/// Regras de formato:
///
/// - Texto com até 30 caracteres.
///
class Nome {
private:
    static const int MAX_CARACTERES = 30;
    string valor;
    void validar(string);

public:
    Nome();
    string getValor() const;
    void setValor(const string);
};

inline string Nome::getValor() const {
    return valor;
}




class Avaliacao {
private:
    int valor;                          // Valor da avaliação (0-5)
    void validar(int valor) {
        if (valor < 0 || valor > 5) {
            throw std::invalid_argument("Avaliacao fora do intervalo [0..5].");
        }
    }

public:
    Avaliacao() : valor(0) {}          
    
    void setValor(int valor) {
        validar(valor);
        this->valor = valor;
    }
    
    int getValor() const {
        return valor;
    }
};

///
/// Padrão para representação de senha.
///
/// Regras de formato:
///
/// - Cinco dígitos (0-9);
/// - Não há dígito duplicado;
/// - Os cinco dígitos não podem estar em ordem crescente;
/// - Os cinco dígitos não podem estar em ordem decrescente.
///
class Senha {
private:
    static const int TAMANHO = 5;
    string valor;
    void validar(string);

public:
    Senha();
    string getValor() const;
    void setValor(const string);
};

inline string Senha::getValor() const {
    return valor;
}

#endif // DOMINIOS_H_INCLUDED