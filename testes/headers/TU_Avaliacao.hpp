// TU_Avaliacao.hpp
#ifndef TU_AVALIACAO_HPP_INCLUDED
#define TU_AVALIACAO_HPP_INCLUDED

#include "Avaliacao.hpp"

class TU_Avaliacao {
private:
    const static int VALOR_VALIDO = 5;        // Valor válido para Avaliacao
    const static int VALOR_INVALIDO = 6;      // Valor inválido para Avaliacao
    Avaliacao* dominio;                       // Unidade em teste
    int estado;                                // Estado do teste

    void setUp();                              // Inicializa a unidade em teste
    void tearDown();                           // Destroi a unidade em teste
    void testarCenarioValorValido();           // Teste com valor válido
    void testarCenarioValorInvalido();         // Teste com valor inválido
public:
    const static int SUCESSO = 0;              // Indica sucesso
    const static int FALHA = -1;               // Indica falha
    int run();                                  // Executa os testes
};

#endif // TU_AVALIACAO_HPP_INCLUDED
