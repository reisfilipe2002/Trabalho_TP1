#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

#include "dominios.h"
#include "entidades.h"
#include <vector>
#include <stdexcept>

//-----------------------------------------------------------------------------
// Declarações "forward" para evitar dependências circulares, caso necessário.
//-----------------------------------------------------------------------------
class IServicoAutenticacao;
class IServicoViajante;
class IServicoViagem;

//-----------------------------------------------------------------------------
// Declarações das interfaces da camada de apresentação.
// A ideia é que cada interface de apresentação interaja com o usuário
// (por meio de console, interface gráfica, etc.) e utilize os serviços
// para efetivamente manipular os dados.
//-----------------------------------------------------------------------------

/// Interface para apresentação/autenticação de contas.
class IApresentacaoAutenticacao {
public:
    /// Realiza o fluxo de autenticação (solicita código, senha, etc.).
    /// Retorna true se o usuário foi autenticado com sucesso.
    virtual bool autenticar(Conta &conta) = 0;

    /// Permite “injetar” a implementação concreta do serviço de autenticação.
    virtual void setCntrServicoAutenticacao(IServicoAutenticacao*) = 0;

    virtual ~IApresentacaoAutenticacao() {}
};

/// Interface para apresentação das funções relacionadas ao Viajante (usuário).
class IApresentacaoViajante {
public:
    /// Executa o fluxo principal do viajante (ex.: menu principal).
    virtual void executar(const Conta &conta) = 0;

    /// Fluxo de cadastro de nova conta.
    virtual void cadastrar() = 0;

    /// Associa a este controlador de apresentação o serviço de Viajante.
    virtual void setCntrServicoViajante(IServicoViajante*) = 0;

    virtual ~IApresentacaoViajante() {}
};

/// Interface para apresentação das funções relacionadas a Viagens,
/// Destinos, Atividades e Hospedagens.
class IApresentacaoViagem {
public:
    /// Executa o fluxo principal para manipular as viagens de um viajante.
    virtual void executar(const Conta &conta) = 0;

    /// Permite injetar o serviço de Viagem para que a apresentação
    /// possa consultar/criar/editar/excluir dados.
    virtual void setCntrServicoViagem(IServicoViagem*) = 0;

    virtual ~IApresentacaoViagem() {}
};

//-----------------------------------------------------------------------------
// Declarações das interfaces da camada de serviço.
// Aqui ficam as operações de CRUD e consultas específicas, 
// de fato manipulando as entidades e persistindo-as (ou simulando a persistência).
//-----------------------------------------------------------------------------

/// Serviço responsável pela autenticação.
class IServicoAutenticacao {
public:
    /// Autentica uma conta com base em seu código e senha.
    /// Retorna true se a combinação for válida.
    virtual bool autenticar(const Codigo &codigo, const Senha &senha) = 0;

    virtual ~IServicoAutenticacao() {}
};

/// Serviço responsável por operações relativas ao Viajante (usuário).
class IServicoViajante {
public:
    /// Cria uma nova conta no sistema.
    virtual bool cadastrarConta(const Conta &conta) = 0;

    /// Exclui (descadastra) uma conta a partir do código.
    virtual bool excluirConta(const Codigo &codigo) = 0;

    /// Altera dados (por exemplo, senha) de uma conta existente.
    virtual bool editarConta(const Conta &conta) = 0;

    /// Retorna uma cópia de conta, se existir.
    virtual bool consultarConta(const Codigo &codigo, Conta *conta) = 0;

    virtual ~IServicoViajante() {}
};

/// Serviço responsável por operações relacionadas a Viagens, Destinos,
/// Atividades e Hospedagens.
class IServicoViagem {
public:
    // ---------------------------
    // Operações sobre Viagem
    // ---------------------------
    virtual bool criarViagem(const Viagem &viagem, const Codigo &codigoViajante) = 0;
    virtual bool excluirViagem(const Codigo &codigoViagem, const Codigo &codigoViajante) = 0;
    virtual bool editarViagem(const Viagem &viagem, const Codigo &codigoViajante) = 0;
    virtual bool consultarViagem(const Codigo &codigoViagem, Viagem *viagem) = 0;
    virtual std::vector<Viagem> listarViagens(const Codigo &codigoViajante) = 0;

    // ---------------------------
    // Operações sobre Destino
    // ---------------------------
    virtual bool adicionarDestino(const Codigo &codigoViagem, const Destino &destino) = 0;
    virtual bool excluirDestino(const Codigo &codigoViagem, const Codigo &codigoDestino) = 0;
    virtual bool editarDestino(const Codigo &codigoViagem, const Destino &destino) = 0;
    virtual bool consultarDestino(const Codigo &codigoViagem, const Codigo &codigoDestino, Destino *destino) = 0;

    // ---------------------------
    // Operações sobre Atividade
    // ---------------------------
    virtual bool adicionarAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Atividade &atividade) = 0;
    virtual bool excluirAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Codigo &codigoAtividade) = 0;
    virtual bool editarAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Atividade &atividade) = 0;

    // ---------------------------
    // Operações sobre Hospedagem
    // ---------------------------
    virtual bool adicionarHospedagem(const Codigo &codigoViagem, const Codigo &codigoDestino, const Hospedagem &hospedagem) = 0;
    virtual bool excluirHospedagem(const Codigo &codigoViagem, const Codigo &codigoDestino, const Codigo &codigoHospedagem) = 0;
    virtual bool editarHospedagem(const Codigo &codigoViagem, const Codigo &codigoDestino, const Hospedagem &hospedagem) = 0;

    virtual ~IServicoViagem() {}
};

#endif // INTERFACES_H_INCLUDED
