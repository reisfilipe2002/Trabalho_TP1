#include "controladorasservico.h"

list<ElementoResultado> ComandoSQL::listaResultado;

//---------------------------------------------------------------------------
//Classe ErroPersistencia.

EErroPersistencia::EErroPersistencia(string mensagem){
        this->mensagem = mensagem;
}

string EErroPersistencia::what() {
        return mensagem;
}

//---------------------------------------------------------------------------
//Classe ElementoResultado.

void ElementoResultado::setNomeColuna(const string& nomeColuna) {
        this->nomeColuna = nomeColuna;
}

void ElementoResultado::setValorColuna(const string& valorColuna){
        this->valorColuna = valorColuna;
}

//---------------------------------------------------------------------------
//Classe ComandoSQL.

void ComandoSQL::conectar() {
      rc = sqlite3_open(nomeBancoDados, &bd);
      if( rc != SQLITE_OK )
        throw EErroPersistencia("Erro na conexao ao banco de dados");
}

void ComandoSQL::desconectar() {
      rc =  sqlite3_close(bd);
      if( rc != SQLITE_OK )
        throw EErroPersistencia("Erro na desconexao ao banco de dados");
}

void ComandoSQL::executar() {
        conectar();
        rc = sqlite3_exec(bd, comandoSQL.c_str(), callback, 0, &mensagem);
        if(rc != SQLITE_OK){
                sqlite3_free(mensagem);
                desconectar();
                throw EErroPersistencia("Erro na execucao do comando SQL");
        }
        desconectar();
}

int ComandoSQL::callback(void *NotUsed, int argc, char **valorColuna, char **nomeColuna){
      NotUsed=0;
      ElementoResultado elemento;
      int i;
      for(i=0; i<argc; i++){
        elemento.setNomeColuna(nomeColuna[i]);
        elemento.setValorColuna(valorColuna[i] ? valorColuna[i]: "NULL");
        listaResultado.push_front(elemento);
      }
      return 0;
}

//---------------------------------------------------------------------------
//Classe ComandoLerSenha.

ComandoLerSenha::ComandoLerSenha(const Codigo &codigoConta) {
    comandoSQL = "SELECT senha FROM contas WHERE codigo = '";
    comandoSQL += codigoConta.getValor();
    comandoSQL += "'";
}

std::string ComandoLerSenha::getResultado() {
    ElementoResultado resultado;
    std::string senha;

    if (listaResultado.empty())
        throw EErroPersistencia("Lista de resultados vazia.");
    
    resultado = listaResultado.back();
    listaResultado.pop_back();
    senha = resultado.getValorColuna();

    return senha;
}


//---------------------------------------------------------------------------
//Classe ComandoCadastrarConta.

ComandoCadastrarConta::ComandoCadastrarConta(const Conta &conta) {
    comandoSQL = "INSERT INTO contas (codigo, nome, email, senha) VALUES (";
    comandoSQL += "'" + conta.getCodigo() + "', ";
    comandoSQL += "'" + conta.getSenha() + "')";
}

//---------------------------------------------------------------------------
//Classe ComandoDescadastrarUsuario.

ComandoDescadastrarConta::ComandoDescadastrarConta(const Codigo &codigoConta) {
    comandoSQL = "DELETE FROM contas WHERE codigo = '";
    comandoSQL += codigoConta.getValor();
    comandoSQL += "'";
}

//---------------------------------------------------------------------------
//Classe ComandoEditarUsuario.

ComandoEditarConta::ComandoEditarConta(const Conta &conta) {
    comandoSQL = "UPDATE contas ";
    comandoSQL += "SET senha = '" + conta.getSenha();
    comandoSQL += "' WHERE codigo = '" + conta.getCodigo() + "'";
}

//---------------------------------------------------------------------------
bool ComandoConsultarConta::getResultado(Conta *conta) {
    ElementoResultado resultado;
    if (listaResultado.empty())
        return false;

    // Supondo que a ordem das colunas seja: codigo,senha
    resultado = listaResultado.back();
    listaResultado.pop_back();
    conta->setCodigo(std::string(resultado.getValorColuna()));

    resultado = listaResultado.back();
    listaResultado.pop_back();
    conta->setSenha(std::string(resultado.getValorColuna()));

    return true;
}

//--------------------------------------------------------------------------------------------
// Classe ComandoCriarViagem

ComandoCriarViagem::ComandoCriarViagem(const Viagem &viagem, const Codigo &codigoViajante) {
    comandoSQL = "INSERT INTO viagens (codigo, nome, codigo_viajante) VALUES (";
    comandoSQL += "'" + viagem.getCodigo() + "', ";
    comandoSQL += "'" + viagem.getNome() + "', ";
    comandoSQL += "'" + codigoViajante.getValor() + "')";
}

//--------------------------------------------------------------------------------------------
// Classe ComandoExcluirViagem

ComandoExcluirViagem::ComandoExcluirViagem(const Codigo &codigoViagem, const Codigo &codigoViajante) {
    comandoSQL = "DELETE FROM viagens WHERE codigo = '";
    comandoSQL += codigoViagem.getValor();
    comandoSQL += "' AND codigo_viajante = '";
    comandoSQL += codigoViajante.getValor();
    comandoSQL += "'";
}

//--------------------------------------------------------------------------------------------
// Classe ComandoEditarViagem

ComandoEditarViagem::ComandoEditarViagem(const Viagem &viagem, const Codigo &codigoViajante) {
    comandoSQL = "UPDATE viagens ";
    comandoSQL += "SET nome = '" + viagem.getNome() + "' ";
    comandoSQL += "WHERE codigo = '" + viagem.getCodigo() + "' ";
    comandoSQL += "AND codigo_viajante = '" + codigoViajante.getValor() + "'";
}

//--------------------------------------------------------------------------------------------
// Classe ComandoConsultarViagem

ComandoConsultarViagem::ComandoConsultarViagem(const Codigo &codigoViagem) {
    comandoSQL = "SELECT * FROM viagens WHERE codigo = '";
    comandoSQL += codigoViagem.getValor();
    comandoSQL += "'";
}

bool ComandoConsultarViagem::getResultado(Viagem *viagem) {
    ElementoResultado resultado;
    if (listaResultado.empty())
        return false;

    // Supondo que a ordem das colunas seja: codigo, nome, codigo_viajante
    resultado = listaResultado.back();
    listaResultado.pop_back();
    viagem->setCodigo(std::string(resultado.getValorColuna()));

    resultado = listaResultado.back();
    listaResultado.pop_back();
    viagem->setNome(std::string(resultado.getValorColuna()));

    return true;
}

//--------------------------------------------------------------------------------------------
// Classe ComandoListarViagens

ComandoListarViagens::ComandoListarViagens(const Codigo &codigoViajante) {
    comandoSQL = "SELECT * FROM viagens WHERE codigo_viajante = '";
    comandoSQL += codigoViajante.getValor();
    comandoSQL += "'";
}

std::vector<Viagem> ComandoListarViagens::getResultado() {
    std::vector<Viagem> viagens;
    ElementoResultado resultado;

    while (!listaResultado.empty()) {
        Viagem viagem;

        resultado = listaResultado.back();
        listaResultado.pop_back();
        viagem.setCodigo(std::string(resultado.getValorColuna()));

        resultado = listaResultado.back();
        listaResultado.pop_back();
        viagem.setNome(std::string(resultado.getValorColuna()));

        viagens.push_back(viagem);
    }

    return viagens;
}

//--------------------------------------------------------------------------------------------
// Classe ComandoAdicionarDestino

ComandoAdicionarDestino::ComandoAdicionarDestino(const Codigo &codigoViagem, const Destino &destino) {
    comandoSQL = "INSERT INTO destinos (codigo, nome, custo, codigo_viagem) VALUES (";
    comandoSQL += "'" + destino.getCodigo() + "', ";
    comandoSQL += "'" + destino.getNome() + "', ";
    comandoSQL += "'" + destino.getDataInicio() + "', ";
    comandoSQL += "'" + destino.getDataTermino() + "', ";
    comandoSQL += "'" + codigoViagem.getValor() + "')";
}

//--------------------------------------------------------------------------------------------
// Classe ComandoExcluirDestino

ComandoExcluirDestino::ComandoExcluirDestino(const Codigo &codigoViagem, const Codigo &codigoDestino) {
    comandoSQL = "DELETE FROM destinos WHERE codigo = '";
    comandoSQL += codigoDestino.getValor();
    comandoSQL += "' AND codigo_viagem = '";
    comandoSQL += codigoViagem.getValor();
    comandoSQL += "'";
}

//--------------------------------------------------------------------------------------------
// Classe ComandoEditarDestino

ComandoEditarDestino::ComandoEditarDestino(const Codigo &codigoViagem, const Destino &destino) {
    comandoSQL = "UPDATE destinos ";
    comandoSQL += "SET nome = '" + destino.getNome().getValor() + "', ";
    comandoSQL += "custo = '" + std::to_string(destino.getCusto()) + "' ";
    comandoSQL += "WHERE codigo = '" + destino.getCodigo().getValor() + "' ";
    comandoSQL += "AND codigo_viagem = '" + codigoViagem.getValor() + "'";
}

//--------------------------------------------------------------------------------------------
// Classe ComandoConsultarDestino

ComandoConsultarDestino::ComandoConsultarDestino(const Codigo &codigoViagem, const Codigo &codigoDestino) {
    comandoSQL = "SELECT * FROM destinos WHERE codigo = '";
    comandoSQL += codigoDestino.getValor();
    comandoSQL += "' AND codigo_viagem = '";
    comandoSQL += codigoViagem.getValor();
    comandoSQL += "'";
}

bool ComandoConsultarDestino::getResultado(Destino *destino) {
    ElementoResultado resultado;
    if (listaResultado.empty())
        return false;

    // Supondo que a ordem das colunas seja: codigo, nome, custo
    resultado = listaResultado.back();
    listaResultado.pop_back();
    destino->setCodigo(std::string(resultado.getValorColuna()));

    resultado = listaResultado.back();
    listaResultado.pop_back();
    destino->setNome(std::string(resultado.getValorColuna()));


    return true;
}

//--------------------------------------------------------------------------------------------
// Classe ComandoAdicionarAtividade

ComandoAdicionarAtividade::ComandoAdicionarAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Atividade &atividade) {
    comandoSQL = "INSERT INTO atividades (codigo, nome, custo, codigo_destino, codigo_viagem) VALUES (";
    comandoSQL += "'" + atividade.getCodigo() + "', ";
    comandoSQL += "'" + atividade.getNome() + "', ";
    comandoSQL += "'" + std::to_string(atividade.getPreco()) + "', ";
    comandoSQL += "'" + codigoDestino.getValor() + "', ";
    comandoSQL += "'" + codigoViagem.getValor() + "')";
}

//--------------------------------------------------------------------------------------------
// Classe ComandoExcluirAtividade

ComandoExcluirAtividade::ComandoExcluirAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Codigo &codigoAtividade) {
    comandoSQL = "DELETE FROM atividades WHERE codigo = '";
    comandoSQL += codigoAtividade.getValor();
    comandoSQL += "' AND codigo_destino = '";
    comandoSQL += codigoDestino.getValor();
    comandoSQL += "' AND codigo_viagem = '";
    comandoSQL += codigoViagem.getValor();
    comandoSQL += "'";
}

//--------------------------------------------------------------------------------------------
// Classe ComandoEditarAtividade

ComandoEditarAtividade::ComandoEditarAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Atividade &atividade) {
    comandoSQL = "UPDATE atividades ";
    comandoSQL += "SET nome = '" + atividade.getNome().getValor() + "', ";
    comandoSQL += "custo = '" + std::to_string(atividade.getCusto()) + "' ";
    comandoSQL += "WHERE codigo = '" + atividade.getCodigo().getValor() + "' ";
    comandoSQL += "AND codigo_destino = '" + codigoDestino.getValor() + "' ";
    comandoSQL += "AND codigo_viagem = '" + codigoViagem.getValor() + "'";
}

//--------------------------------------------------------------------------------------------
// Classe ComandoConsultarAtividade

ComandoConsultarAtividade::ComandoConsultarAtividade(const Codigo &codigoViagem, const Codigo &codigoDestino, const Codigo &codigoAtividade) {
    comandoSQL = "SELECT * FROM atividades WHERE codigo = '";
    comandoSQL += codigoAtividade.getValor();
    comandoSQL += "' AND codigo_destino = '";
    comandoSQL += codigoDestino.getValor();
    comandoSQL += "' AND codigo_viagem = '";
    comandoSQL += codigoViagem.getValor();
    comandoSQL += "'";
}

bool ComandoConsultarAtividade::getResultado(Atividade *atividade) {
    ElementoResultado resultado;
    if (listaResultado.empty())
        return false;

    // Supondo que a ordem das colunas seja: codigo, nome, custo
    resultado = listaResultado.back();
    listaResultado.pop_back();
    atividade->setCodigo(std::string(resultado.getValorColuna()));

    resultado = listaResultado.back();
    listaResultado.pop_back();
    atividade->setNome(std::string(resultado.getValorColuna()));

    resultado = listaResultado.back();
    listaResultado.pop_back();
    atividade->setPreco(std::stod(resultado.getValorColuna()));

    return true;
}

//--------------------------------------------------------------------------------------------
// Classe ComandoAdicionarHospedagem

ComandoAdicionarHospedagem::ComandoAdicionarHospedagem(const Codigo &codigoViagem, const Codigo &codigoDestino, const Hospedagem &hospedagem) {
    comandoSQL = "INSERT INTO hospedagens (codigo, nome, custo, codigo_destino, codigo_viagem) VALUES (";
    comandoSQL += "'" + hospedagem.getCodigo().getValor() + "', ";
    comandoSQL += "'" + hospedagem.getNome().getValor() + "', ";
    comandoSQL += "'" + std::to_string(hospedagem.getCusto()) + "', ";
    comandoSQL += "'" + codigoDestino.getValor() + "', ";
    comandoSQL += "'" + codigoViagem.getValor() + "')";
}

//--------------------------------------------------------------------------------------------
// Classe ComandoExcluirHospedagem

ComandoExcluirHospedagem::ComandoExcluirHospedagem(const Codigo &codigoViagem, const Codigo &codigoDestino, const Codigo &codigoHospedagem) {
    comandoSQL = "DELETE FROM hospedagens WHERE codigo = '";
    comandoSQL += codigoHospedagem.getValor();
    comandoSQL += "' AND codigo_destino = '";
    comandoSQL += codigoDestino.getValor();
    comandoSQL += "' AND codigo_viagem = '";
    comandoSQL += codigoViagem.getValor();
    comandoSQL += "'";
}

//--------------------------------------------------------------------------------------------
// Classe ComandoEditarHospedagem

ComandoEditarHospedagem::ComandoEditarHospedagem(const Codigo &codigoViagem, const Codigo &codigoDestino, const Hospedagem &hospedagem) {
    comandoSQL = "UPDATE hospedagens ";
    comandoSQL += "SET nome = '" + hospedagem.getNome().getValor() + "', ";
    comandoSQL += "custo = '" + std::to_string(hospedagem.getCusto()) + "' ";
    comandoSQL += "WHERE codigo = '" + hospedagem.getCodigo().getValor() + "' ";
    comandoSQL += "AND codigo_destino = '" + codigoDestino.getValor() + "' ";
    comandoSQL += "AND codigo_viagem = '" + codigoViagem.getValor() + "'";
}

//--------------------------------------------------------------------------------------------
// Classe ComandoConsultarHospedagem

ComandoConsultarHospedagem::ComandoConsultarHospedagem(const Codigo &codigoViagem, const Codigo &codigoDestino, const Codigo &codigoHospedagem) {
    comandoSQL = "SELECT * FROM hospedagens WHERE codigo = '";
    comandoSQL += codigoHospedagem.getValor();
    comandoSQL += "' AND codigo_destino = '";
    comandoSQL += codigoDestino.getValor();
    comandoSQL += "' AND codigo_viagem = '";
    comandoSQL += codigoViagem.getValor();
    comandoSQL += "'";
}

bool ComandoConsultarHospedagem::getResultado(Hospedagem *hospedagem) {
    ElementoResultado resultado;
    if (listaResultado.empty())
        return false;

    // Supondo que a ordem das colunas seja: codigo, nome, custo
    resultado = listaResultado.back();
    listaResultado.pop_back();
    hospedagem->setCodigo(Codigo(resultado.getValorColuna()));

    resultado 