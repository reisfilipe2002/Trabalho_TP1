#ifndef CONTROLADORASAPRESENTACAO_H_INCLUDED
#define CONTROLADORASAPRESENTACAO_H_INCLUDED

#include <iostream>
#include <string>
#include "curses.h"
#include "dominios.h"
#include "entidades.h"
#include "interfaces.h"
#include <list>

//*****************************************************************************
// Controladores de Apresentação
//*****************************************************************************

/// Controlador principal de apresentação.
class CntrApresentacaoControle {
private:
    IApresentacaoAutenticacao *cntrApresentacaoAutenticacao = nullptr;
    IApresentacaoViajante *cntrApresentacaoViajante = nullptr;
    IApresentacaoViagem *cntrApresentacaoViagem = nullptr;

public:
    void executar();
    void setCntrApresentacaoAutenticacao(IApresentacaoAutenticacao*);
    void setCntrIApresentacaoViajante(IApresentacaoViajante*);
    void setCntrIApresentacaoViagem(IApresentacaoViagem*);
};

// Métodos de configuração
inline void CntrApresentacaoControle::setCntrApresentacaoAutenticacao(IApresentacaoAutenticacao *cntr){
    cntrApresentacaoAutenticacao = cntr;
}

inline void CntrApresentacaoControle::setCntrIApresentacaoViajante(IApresentacaoViajante *cntr){
    cntrApresentacaoViajante = cntr;
}

inline void CntrApresentacaoControle::setCntrIApresentacaoViagem(IApresentacaoViagem *cntr){
    cntrApresentacaoViagem = cntr;
}

// Implementação do método executar()
inline void CntrApresentacaoControle::executar(){
    if (!cntrApresentacaoAutenticacao || !cntrApresentacaoViajante || !cntrApresentacaoViagem) {
        std::cout << "Erro: Um ou mais controladores não foram configurados corretamente.\n";
        return;
    }

    std::string codigo, senha;
    Conta conta(codigo, senha);

    // Solicitar credenciais ao usuário antes da autenticação
    std::cout << "Digite o código da conta: ";
    std::cin >> codigo;
    conta.setCodigo(codigo);

    std::cout << "Digite a senha: ";
    std::cin >> senha;
    conta.setSenha(senha);

    // Chama autenticação
    if (cntrApresentacaoAutenticacao->autenticar(conta)) {
        std::cout << "Autenticação bem-sucedida!\n";
        cntrApresentacaoViajante->executar(conta);
        cntrApresentacaoViagem->executar(conta);
    } else {
        std::cout << "Falha na autenticação. Tente novamente.\n";
    }
}

//------------------------------------------------------------------------------
/// Controlador de apresentação para autenticação.
class CntrApresentacaoAutenticacao : public IApresentacaoAutenticacao {
private:
    IServicoAutenticacao *cntr = nullptr;

public:
    bool autenticar(Conta &conta) override;
    void setCntrServicoAutenticacao(IServicoAutenticacao*) override;
};

// Define o serviço de autenticação
inline void CntrApresentacaoAutenticacao::setCntrServicoAutenticacao(IServicoAutenticacao *cntr){
    this->cntr = cntr;
}

// Implementação do método autenticar()
inline bool CntrApresentacaoAutenticacao::autenticar(Conta &conta){
    if (!cntr) {
        std::cout << "Erro: Serviço de autenticação não configurado.\n";
        return false;
    }

    // Converte std::string para Código e Senha antes de chamar a autenticação
    Codigo codigo(conta.getCodigo());
    Senha senha(conta.getSenha());

    return cntr->autenticar(codigo, senha);
}

//------------------------------------------------------------------------------
/// Controlador de apresentação para viajante.
class CntrApresentacaoViajante : public IApresentacaoViajante {
private:
    IServicoViajante *cntrServicoViajante = nullptr;
    IServicoViagem *cntrServicoViagem = nullptr;

    void editar(const Conta &conta) {
        std::cout << "Editando conta do viajante.\n";
    }

    void descadastrar(const Conta &conta) {
        std::cout << "Descadastrando conta do viajante.\n";
    }

public:
    void executar(const Conta &conta) override;
    void cadastrar() override;
    void setCntrServicoViajante(IServicoViajante *) override;
    void setCntrServicoViagem(IServicoViagem*) override;
};

// Define os serviços
inline void CntrApresentacaoViajante::setCntrServicoViajante(IServicoViajante *cntr){
    cntrServicoViajante = cntr;
}

inline void CntrApresentacaoViajante::setCntrServicoViagem(IServicoViagem *cntr){
    cntrServicoViagem = cntr;
}

// Implementação do método executar()
inline void CntrApresentacaoViajante::executar(const Conta &conta){
    std::cout << "Executando apresentação do viajante.\n";
    cadastrar();
}

// Implementação do método cadastrar()
inline void CntrApresentacaoViajante::cadastrar(){
    std::cout << "Cadastrando novo viajante...\n";
    if (cntrServicoViajante)
        std::cout << "Serviço de viajante chamado.\n";
    else
        std::cout << "Erro: Serviço de viajante não configurado.\n";
}

//------------------------------------------------------------------------------
/// Controlador de apresentação para viagem.
class CntrApresentacaoViagem : public IApresentacaoViagem {
private:
    IServicoViagem *cntr = nullptr;

    void cadastrarViagem(const Conta &conta){
        std::cout << "Cadastrando nova viagem...\n";
        if (cntr)
            std::cout << "Serviço de viagem configurado.\n";
        else
            std::cout << "Erro: Serviço de viagem não configurado.\n";
    }

public:
    void executar(const Conta &conta) override;
    void setCntrServicoViagem(IServicoViagem*) override;
};

// Define o serviço de viagem
inline void CntrApresentacaoViagem::setCntrServicoViagem(IServicoViagem *cntr){
    this->cntr = cntr;
}

// Implementação do método executar()
inline void CntrApresentacaoViagem::executar(const Conta &conta){
    std::cout << "Executando apresentação da viagem.\n";
    cadastrarViagem(conta);
}

#endif // CONTROLADORASAPRESENTACAO_H_INCLUDED