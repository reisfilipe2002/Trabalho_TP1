#ifndef CONTROLADORASSERVICO_H_INCLUDED
#define CONTROLADORASSERVICO_H_INCLUDED

#include "dominios.h"
#include "entidades.h"
#include "interfaces.h"

#include <list>
#include <string>
#include <stdio.h>
#include <iostream>

#include "sqlite3.h"

//--------------------------------------------------------------------------------------------
// Classe de exceção para erros de persistência em banco de dados.

class EErroPersistencia {
private:
    std::string mensagem;
public:
    EErroPersistencia(std::string mensagem) : mensagem(mensagem) {}
    std::string what() {
        return mensagem;
    }
};

//--------------------------------------------------------------------------------------------
// Classe ElementoResultado para armazenar os resultados de uma consulta SQL.

class ElementoResultado {
private:
    std::string nomeColuna;
    std::string valorColuna;
public:
    void setNomeColuna(const std::string &nomeColuna) {
        this->nomeColuna = nomeColuna;
    }
    std::string getNomeColuna() const {
        return nomeColuna;
    }
    void setValorColuna(const std::string &valorColuna) {
        this->valorColuna = valorColuna;
    }
    std::string getValorColuna() const {
        return valorColuna;
    }
};

//--------------------------------------------------------------------------------------------
// Classe ComandoSQL: responsável por abrir/fechar conexão e executar um comando SQL.
// Usa callback estático para salvar resultados em listaResultado.

class ComandoSQL {
private:
    const char *nomeBancoDados;
    sqlite3 *bd;
    char *mensagem;
    int rc;

    void conectar();
    void desconectar();
    static int callback(void *, int, char **, char **);

protected:
    static std::list<ElementoResultado> listaResultado;
    std::string comandoSQL;

public:
    // Ajuste o nome do arquivo .db conforme desejado.
    ComandoSQL() {
        nomeBancoDados = "viagem_db.db";
    }
    void executar();
};

//--------------------------------------------------------------------------------------------
// Exemplo de classes Comando para operações específicas no banco de dados.
// Você pode criar quantas forem necessárias: cada comando encapsula 1 operação SQL distinta.
//--------------------------------------------------------------------------------------------

// (1) Conta / Autenticação
class ComandoCadastrarConta : public ComandoSQL {
public:
    // Recebe objeto Conta e gera comando SQL de INSERT no banco.
    ComandoCadastrarConta(const Conta &conta);
};

class ComandoDescadastrarConta : public ComandoSQL {
public:
    // Recebe Codigo da conta e gera comando SQL de DELETE.
    ComandoDescadastrarConta(const Codigo &codigoConta);
};

class ComandoEditarConta : public ComandoSQL {
public:
    // Recebe objeto Conta (com os novos dados) e gera comando SQL de UPDATE.
    ComandoEditarConta(const Conta &conta);
};

class ComandoConsultarConta : public ComandoSQL {
public:
    // Recebe Codigo e gera SELECT para buscar a conta correspondente.
    ComandoConsultarConta(const Codigo &codigoConta);

    // Depois de executar, use este método para extrair o resultado da listaResultado.
    bool getResultado(Conta *conta);
};

class ComandoLerSenha : public ComandoSQL {
public:
    // Exemplo de comando que retorna a senha, para fins de autenticação.
    ComandoLerSenha(const Codigo &codigoConta);
    std::string getResultado();
};

// (2) Viagem
class ComandoCriarViagem : public ComandoSQL {
public:
    // Recebe objeto Viagem e o codigo do Viajante (Conta), gera INSERT.
    ComandoCriarViagem(const Viagem &viagem, const Codigo &codigoViajante);
};

class ComandoExcluirViagem : public ComandoSQL {
public:
    ComandoExcluirViagem(const Codigo &codigoViagem, const Codigo &codigoViajante);
};

class ComandoEditarViagem : public ComandoSQL {
public:
    ComandoEditarViagem(const Viagem &viagem, const Codigo &codigoViajante);
};

class ComandoConsultarViagem : public ComandoSQL {
public:
    ComandoConsultarViagem(const Codigo &codigoViagem);
    bool getResultado(Viagem *viagem);
};

class ComandoListarViagens : public ComandoSQL {
public:
    // Gera SELECT para todas as viagens de um viajante específico.
    ComandoListarViagens(const Codigo &codigoViajante);
    std::vector<Viagem> getResultado();
};

class ComandoListarViagensAll : public ComandoSQL {
public:
    // Gera SELECT para todas as viagens de todos os viajantes.
    ComandoListarViagensAll();
    std::vector<Viagem> getResultado();
};

// (3) Destino (como parte de uma viagem)
class ComandoAdicionarDestino : public ComandoSQL {
public:
    ComandoAdicionarDestino(const Codigo &codigoViagem, const Destino &destino);
};

class ComandoExcluirDestino : public ComandoSQL {
public:
    ComandoExcluirDestino(const Codigo &codigoViagem, const Codigo &codigoDestino);
};

class ComandoEditarDestino : public ComandoSQL {
public:
    ComandoEditarDestino(const Codigo &codigoViagem, const Destino &destino);
};

class ComandoConsultarDestino : public ComandoSQL {
public:
    ComandoConsultarDestino(const Codigo &codigoViagem, const Codigo &codigoDestino);
    bool getResultado(Destino *destino);
};


// (4) Atividade
class ComandoAdicionarAtividade : public ComandoSQL {
public:
    ComandoAdicionarAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Atividade &atividade);

};

class ComandoExcluirAtividade : public ComandoSQL {
public:
    ComandoExcluirAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Codigo &codigoAtividade);
}; 

class ComandoEditarAtividade : public ComandoSQL {
public:
    ComandoEditarAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Atividade &atividade);
};

class ComandoConsultarAtividade : public ComandoSQL {
public:
    ComandoConsultarAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Codigo &codigoAtividade);
    bool getResultado(Atividade *atividade);
};



// (5) Hospedagem
class ComandoAdicionarHospedagem : public ComandoSQL {
public:
    ComandoAdicionarHospedagem( const Codigo &codigoDestino, const Hospedagem &hospedagem);
};

class ComandoExcluirHospedagem : public ComandoSQL {
public:
    ComandoExcluirHospedagem( const Codigo &codigoDestino, const Codigo &codigoHospedagem);
};

class ComandoEditarHospedagem : public ComandoSQL {
public:
    ComandoEditarHospedagem( const Codigo &codigoDestino, const Hospedagem &hospedagem);
};

class ComandoConsultarHospedagem : public ComandoSQL {
public:
    ComandoConsultarHospedagem( const Codigo &codigoDestino, const Codigo &codigoHospedagem);
    bool getResultado(Hospedagem *hospedagem);
};


//--------------------------------------------------------------------------------------------
// Exemplo de função auxiliar que você pode querer ter para verificar se uma Conta existe, etc.
bool checarContaCadastrada(const Codigo &codigoConta);



//--------------------------------------------------------------------------------------------
// Classes controladoras da camada de serviço propriamente ditas, que implementam as interfaces.
// Elas usam os comandos acima para acessar o banco de dados via ComandoSQL.
//--------------------------------------------------------------------------------------------

class CntrServicoAutenticacao : public IServicoAutenticacao {
public:
    bool autenticar(const Codigo &codigo, const Senha &senha) override;
};

class CntrServicoViajante : public IServicoViajante {
public:
    bool cadastrarConta(const Conta &conta) override;
    bool excluirConta(const Codigo &codigo) override;
    bool editarConta(const Conta &conta) override;
    bool consultarConta(const Codigo &codigo, Conta *conta) override;
};

class CntrServicoViagem : public IServicoViagem {
public:
    // Viagem
    bool criarViagem(const Viagem &viagem, const Codigo &codigoViajante) override;
    bool excluirViagem(const Codigo &codigoViagem, const Codigo &codigoViajante) override;
    bool editarViagem(const Viagem &viagem, const Codigo &codigoViajante) override;
    bool consultarViagem(const Codigo &codigoViagem, Viagem *viagem) override;
    std::vector<Viagem> listarViagens(const Codigo &codigoViajante) override;

    // Destino
    bool adicionarDestino(const Codigo &codigoViagem, const Destino &destino) override;
    bool excluirDestino(const Codigo &codigoViagem, const Codigo &codigoDestino) override;
    bool editarDestino(const Codigo &codigoViagem, const Destino &destino) override;
    bool consultarDestino(const Codigo &codigoViagem, const Codigo &codigoDestino, Destino *destino) override;

    // Atividade
    bool adicionarAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Atividade &atividade) override;
    bool excluirAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Codigo &codigoAtividade) override;
    bool editarAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Atividade &atividade) override;

    // Hospedagem
    bool adicionarHospedagem(const Codigo &codigoViagem, const Codigo &codigoDestino, const Hospedagem &hospedagem) override;
    bool excluirHospedagem(const Codigo &codigoViagem, const Codigo &codigoDestino, const Codigo &codigoHospedagem) override;
    bool editarHospedagem(const Codigo &codigoViagem, const Codigo &codigoDestino, const Hospedagem &hospedagem) override;

    double consultarCustoViagem(const Codigo &codigoViagem);

    double dinheiroParaDouble(const Dinheiro &dinheiro);

private:        
    std::vector<Destino> listarDestinos(const Codigo &codigoViagem);
    std::vector<Atividade> listarAtividades(const Codigo &codigoViagem, const Codigo &codigoDestino);
    std::vector<Hospedagem> listarHospedagens(const Codigo &codigoViagem, const Codigo &codigoDestino);
};


#endif // CONTROLADORASSERVICO_H_INCLUDED
