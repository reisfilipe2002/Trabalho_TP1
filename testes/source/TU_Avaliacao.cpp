// TU_Avaliacao.cpp
#include "TU_Avaliacao.hpp"
#include <iostream>

// Implementação do método setUp
void TU_Avaliacao::setUp(){
    dominio = new Avaliacao();
    estado = SUCESSO;
}

// Implementação do método tearDown
void TU_Avaliacao::tearDown(){
    delete dominio;
}

// Implementação do teste com valor válido
void TU_Avaliacao::testarCenarioValorValido(){
    try{
        dominio->setValor(VALOR_VALIDO);
        if (dominio->getValor() != VALOR_VALIDO)
            estado = FALHA;
    }
    catch(std::invalid_argument &excecao){
        estado = FALHA;
    }
}

// Implementação do teste com valor inválido
void TU_Avaliacao::testarCenarioValorInvalido(){
    try{
        dominio->setValor(VALOR_INVALIDO);
        estado = FALHA; // Se não lançar exceção, o teste falha
    }
    catch(std::invalid_argument &excecao){
        // Se a exceção for lançada, o teste é bem-sucedido
    }
}

// Implementação do método run
int TU_Avaliacao::run(){
    setUp();
    testarCenarioValorValido();
    testarCenarioValorInvalido();
    tearDown();
    return estado;
}
