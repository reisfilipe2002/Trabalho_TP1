// TUEntidade.cpp
#include "TUEntidade.hpp"
#include <iostream>

// Definição das constantes estáticas
const std::string TUEntidade::VALOR_CODIGO_VALIDO = "ABC123";
const std::string TUEntidade::VALOR_CODIGO_INVALIDO = "AB@123";
const std::string TUEntidade::VALOR_DATA_VALIDO = "29-02-20"; // Ano bissexto
const std::string TUEntidade::VALOR_DATA_INVALIDO = "31-04-21"; // Abril tem 30 dias
const double TUEntidade::VALOR_DINHEIRO_VALIDO = 199999.99;
const double TUEntidade::VALOR_DINHEIRO_INVALIDO = 250000.00;
const std::string TUEntidade::VALOR_HORARIO_VALIDO = "23:59";
const std::string TUEntidade::VALOR_HORARIO_INVALIDO = "24:00";
const std::string TUEntidade::VALOR_NOME_VALIDO = "Joao da Silva";
const std::string TUEntidade::VALOR_NOME_INVALIDO = "Este é um nome extremamente longo que excede trinta caracteres";
const std::string TUEntidade::VALOR_SENHA_VALIDO = "13579";
const std::string TUEntidade::VALOR_SENHA_INVALIDO = "12345"; // Ordem crescente

// Implementação do método setUp
void TUEntidade::setUp(){
    entidade = new Entidade();
    estado = SUCESSO;
}

// Implementação do método tearDown
void TUEntidade::tearDown(){
    delete entidade;
}

// Implementação do método testarCenario
void TUEntidade::testarCenario(){
    // Testar Avaliacao com valor válido
    try{
        entidade->setAvaliacao(VALOR_AVALIACAO_VALIDO);
        if(entidade->getAvaliacao() != VALOR_AVALIACAO_VALIDO){
            std::cout << "Falha: Avaliacao com valor válido não foi atribuída corretamente." << std::endl;
            estado = FALHA;
        }
    }
    catch(std::invalid_argument &excecao){
        std::cout << "Falha: Excecao inesperada ao definir Avaliacao com valor válido: " << excecao.what() << std::endl;
        estado = FALHA;
    }

    // Testar Avaliacao com valor inválido
    try{
        entidade->setAvaliacao(VALOR_AVALIACAO_INVALIDO);
        std::cout << "Falha: Avaliacao permitiu valor inválido sem lançar exceção." << std::endl;
        estado = FALHA; // Deve lançar exceção
    }
    catch(std::invalid_argument &excecao){
        // Exceção esperada, teste bem-sucedido
    }

    // Testar Codigo com valor válido
    try{
        entidade->setCodigo(VALOR_CODIGO_VALIDO);
        if(entidade->getCodigo() != VALOR_CODIGO_VALIDO){
            std::cout << "Falha: Codigo com valor válido não foi atribuído corretamente." << std::endl;
            estado = FALHA;
        }
    }
    catch(std::invalid_argument &excecao){
        std::cout << "Falha: Excecao inesperada ao definir Codigo com valor válido: " << excecao.what() << std::endl;
        estado = FALHA;
    }

    // Testar Codigo com valor inválido
    try{
        entidade->setCodigo(VALOR_CODIGO_INVALIDO);
        std::cout << "Falha: Codigo permitiu valor inválido sem lançar exceção." << std::endl;
        estado = FALHA; // Deve lançar exceção
    }
    catch(std::invalid_argument &excecao){
        // Exceção esperada, teste bem-sucedido
    }

    // Testar Data com valor válido
    try{
        entidade->setData(VALOR_DATA_VALIDO);
        if(entidade->getData() != VALOR_DATA_VALIDO){
            std::cout << "Falha: Data com valor válido não foi atribuída corretamente." << std::endl;
            estado = FALHA;
        }
    }
    catch(std::invalid_argument &excecao){
        std::cout << "Falha: Excecao inesperada ao definir Data com valor válido: " << excecao.what() << std::endl;
        estado = FALHA;
    }

    // Testar Data com valor inválido
    try{
        entidade->setData(VALOR_DATA_INVALIDO);
        std::cout << "Falha: Data permitiu valor inválido sem lançar exceção." << std::endl;
        estado = FALHA; // Deve lançar exceção
    }
    catch(std::invalid_argument &excecao){
        // Exceção esperada, teste bem-sucedido
    }

    // Testar Dinheiro com valor válido
    try{
        entidade->setDinheiro(VALOR_DINHEIRO_VALIDO);
        if(entidade->getDinheiro() != VALOR_DINHEIRO_VALIDO){
            std::cout << "Falha: Dinheiro com valor válido não foi atribuído corretamente." << std::endl;
            estado = FALHA;
        }
    }
    catch(std::invalid_argument &excecao){
        std::cout << "Falha: Excecao inesperada ao definir Dinheiro com valor válido: " << excecao.what() << std::endl;
        estado = FALHA;
    }

    // Testar Dinheiro com valor inválido
    try{
        entidade->setDinheiro(VALOR_DINHEIRO_INVALIDO);
        std::cout << "Falha: Dinheiro permitiu valor inválido sem lançar exceção." << std::endl;
        estado = FALHA; // Deve lançar exceção
    }
    catch(std::invalid_argument &excecao){
        // Exceção esperada, teste bem-sucedido
    }

    // Testar Duracao com valor válido
    try{
        entidade->setDuracao(VALOR_DURACAO_VALIDO);
        if(entidade->getDuracao() != VALOR_DURACAO_VALIDO){
            std::cout << "Falha: Duracao com valor válido não foi atribuída corretamente." << std::endl;
            estado = FALHA;
        }
    }
    catch(std::invalid_argument &excecao){
        std::cout << "Falha: Excecao inesperada ao definir Duracao com valor válido: " << excecao.what() << std::endl;
        estado = FALHA;
    }

    // Testar Duracao com valor inválido
    try{
        entidade->setDuracao(VALOR_DURACAO_INVALIDO);
        std::cout << "Falha: Duracao permitiu valor inválido sem lançar exceção." << std::endl;
        estado = FALHA; // Deve lançar exceção
    }
    catch(std::invalid_argument &excecao){
        // Exceção esperada, teste bem-sucedido
    }

    // Testar Horario com valor válido
    try{
        entidade->setHorario(VALOR_HORARIO_VALIDO);
        if(entidade->getHorario() != VALOR_HORARIO_VALIDO){
            std::cout << "Falha: Horario com valor válido não foi atribuído corretamente." << std::endl;
            estado = FALHA;
        }
    }
    catch(std::invalid_argument &excecao){
        std::cout << "Falha: Excecao inesperada ao definir Horario com valor válido: " << excecao.what() << std::endl;
        estado = FALHA;
    }

    // Testar Horario com valor inválido
    try{
        entidade->setHorario(VALOR_HORARIO_INVALIDO);
        std::cout << "Falha: Horario permitiu valor inválido sem lançar exceção." << std::endl;
        estado = FALHA; // Deve lançar exceção
    }
    catch(std::invalid_argument &excecao){
        // Exceção esperada, teste bem-sucedido
    }

    // Testar Nome com valor válido
    try{
        entidade->setNome(VALOR_NOME_VALIDO);
        if(entidade->getNome() != VALOR_NOME_VALIDO){
            std::cout << "Falha: Nome com valor válido não foi atribuído corretamente." << std::endl;
            estado = FALHA;
        }
    }
    catch(std::invalid_argument &excecao){
        std::cout << "Falha: Excecao inesperada ao definir Nome com valor válido: " << excecao.what() << std::endl;
        estado = FALHA;
    }

    // Testar Nome com valor inválido
    try{
        entidade->setNome(VALOR_NOME_INVALIDO);
        std::cout << "Falha: Nome permitiu valor inválido sem lançar exceção." << std::endl;
        estado = FALHA; // Deve lançar exceção
    }
    catch(std::invalid_argument &excecao){
        // Exceção esperada, teste bem-sucedido
    }

    // Testar Senha com valor válido
    try{
        entidade->setSenha(VALOR_SENHA_VALIDO);
        if(entidade->getSenha() != VALOR_SENHA_VALIDO){
            std::cout << "Falha: Senha com valor válido não foi atribuída corretamente." << std::endl;
            estado = FALHA;
        }
    }
    catch(std::invalid_argument &excecao){
        std::cout << "Falha: Excecao inesperada ao definir Senha com valor válido: " << excecao.what() << std::endl;
        estado = FALHA;
    }

    // Testar Senha com valor inválido
    try{
        entidade->setSenha(VALOR_SENHA_INVALIDO);
        std::cout << "Falha: Senha permitiu valor inválido sem lançar exceção." << std::endl;
        estado = FALHA; // Deve lançar exceção
    }
    catch(std::invalid_argument &excecao){
        // Exceção esperada, teste bem-sucedido
    }
}

// Implementação do método run
int TUEntidade::run(){
    setUp();
    testarCenario();
    tearDown();
    return estado;
}
