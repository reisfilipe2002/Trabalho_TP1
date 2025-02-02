#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

#include "dominios.h"
#include "entidades.h"
#include <vector>
#include <stdexcept>

// Forward declarations for service interfaces.
class IServicoAutenticacao;
class IServicoViajante;
class IServicoViagem;

//*****************************************************************************
// Presentation Interfaces
//*****************************************************************************

/// Interface for account authentication presentation.
class IApresentacaoAutenticacao {
public:
    /// Performs the authentication flow using a Conta.
    virtual bool autenticar(Conta &conta) = 0;

    /// Injects the concrete authentication service.
    virtual void setCntrServicoAutenticacao(IServicoAutenticacao*) = 0;

    virtual ~IApresentacaoAutenticacao() {}
};

/// Interface for traveler (viajante) presentation.
class IApresentacaoViajante {
public:
    /// Executes the main traveler flow (for example, showing a menu).
    virtual void executar(const Conta &conta) = 0;

    /// Executes the registration flow.
    virtual void cadastrar() = 0;

    /// Injects the traveler service.
    virtual void setCntrServicoViajante(IServicoViajante*) = 0;

    /// Injects the viagem service (if needed).
    virtual void setCntrServicoViagem(IServicoViagem*) = 0;

    virtual ~IApresentacaoViajante() {}
};

/// Interface for travel (viagem) presentation.
class IApresentacaoViagem {
public:
    /// Executes the main travel flow.
    virtual void executar(const Conta &conta) = 0;

    /// Injects the travel service.
    virtual void setCntrServicoViagem(IServicoViagem*) = 0;

    virtual ~IApresentacaoViagem() {}
};

//*****************************************************************************
// Service Interfaces
//*****************************************************************************

/// Service interface for authentication.
class IServicoAutenticacao {
public:
    /// Authenticates an account based on its Codigo and Senha.
    virtual bool autenticar(const Codigo &codigo, const Senha &senha) = 0;
    virtual ~IServicoAutenticacao() {}
};

/// Service interface for traveler (conta) operations.
class IServicoViajante {
public:
    virtual bool cadastrarConta(const Conta &conta) = 0;
    virtual bool excluirConta(const Codigo &codigo) = 0;
    virtual bool editarConta(const Conta &conta) = 0;
    virtual bool consultarConta(const Codigo &codigo, Conta *conta) = 0;
    virtual ~IServicoViajante() {}
};

/// Service interface for travel (viagem) operations.
class IServicoViagem {
public:
    virtual Codigo gerarCodigo() = 0;
    virtual Codigo gerarCodigoValido(std::string entidade) = 0;
    virtual bool checarIntervaloDatas(Data primeiroDataUm, Data primeiroDataDois,
                                      Data segundoDataUm, Data segundoDataDois) = 0;
    virtual double dinheiroParaDouble(Dinheiro dinheiro) = 0;
    virtual bool codigoValido(std::string entidade, Codigo codigo) = 0;
    virtual bool criarViagem(const Viagem &viagem, const Codigo &codigoViajante) = 0;
    virtual bool excluirViagem(const Codigo &codigoViagem, const Codigo &codigoViajante) = 0;
    virtual bool editarViagem(const Viagem &viagem, const Codigo &codigoViajante) = 0;
    virtual bool consultarViagem(const Codigo &codigoViagem, Viagem *viagem) = 0;
    virtual std::vector<Viagem> listarViagens(const Codigo &codigoViajante) = 0;
    virtual bool adicionarDestino(const Codigo &codigoViagem, const Destino &destino) = 0;
    virtual bool excluirDestino(const Codigo &codigoViagem, const Codigo &codigoDestino) = 0;
    virtual bool editarDestino(const Codigo &codigoViagem, const Destino &destino) = 0;
    virtual bool consultarDestino(const Codigo &codigoViagem, const Codigo &codigoDestino, Destino *destino) = 0;
    virtual bool adicionarAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Atividade &atividade) = 0;
    virtual bool excluirAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Codigo &codigoAtividade) = 0;
    virtual bool editarAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Atividade &atividade) = 0;
    virtual std::vector<Atividade> listarAtividades(const Codigo &codigoViagem, const Codigo &codigoDestino) = 0;
    virtual bool adicionarHospedagem(const Codigo &codigoViagem, const Codigo &codigoDestino, const Hospedagem &hospedagem) = 0;
    virtual bool excluirHospedagem(const Codigo &codigoViagem, const Codigo &codigoDestino, const Codigo &codigoHospedagem) = 0;
    virtual bool editarHospedagem(const Codigo &codigoViagem, const Codigo &codigoDestino, const Hospedagem &hospedagem) = 0;
    virtual std::vector<Hospedagem> listarHospedagens(const Codigo &codigoViagem, const Codigo &codigoDestino) = 0;
    virtual ~IServicoViagem() {}
};

#endif // INTERFACES_H_INCLUDED
