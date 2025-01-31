// TUEntidade.hpp
#ifndef TU_ENTIDADE_HPP_INCLUDED
#define TU_ENTIDADE_HPP_INCLUDED

#include "Entidade.hpp"

class TUEntidade {
private:
    // Constantes para Avaliacao
    const static int VALOR_AVALIACAO_VALIDO = 5;
    const static int VALOR_AVALIACAO_INVALIDO = 6;

    // Constantes para Codigo
    const static std::string VALOR_CODIGO_VALIDO;
    const static std::string VALOR_CODIGO_INVALIDO;

    // Constantes para Data
    const static std::string VALOR_DATA_VALIDO;
    const static std::string VALOR_DATA_INVALIDO;

    // Constantes para Dinheiro
    const static double VALOR_DINHEIRO_VALIDO;
    const static double VALOR_DINHEIRO_INVALIDO;

    // Constantes para Duracao
    const static int VALOR_DURACAO_VALIDO = 180;
    const static int VALOR_DURACAO_INVALIDO = 400;

    // Constantes para Horario
    const static std::string VALOR_HORARIO_VALIDO;
    const static std::string VALOR_HORARIO_INVALIDO;

    // Constantes para Nome
    const static std::string VALOR_NOME_VALIDO;
    const static std::string VALOR_NOME_INVALIDO;

    // Constantes para Senha
    const static std::string VALOR_SENHA_VALIDO;
    const static std::string VALOR_SENHA_INVALIDO;

    Entidade* entidade; // Unidade em teste
    int estado;         // Estado do teste

    void setUp();       // Inicializa a unidade em teste
    void tearDown();    // Destroi a unidade em teste
    void testarCenario(); // Cenário de teste

public:
    const static int SUCESSO = 0; // Indica sucesso
    const static int FALHA = -1;  // Indica falha
    int run();                     // Executa os testes
};

#endif // TU_ENTIDADE_HPP_INCLUDED
