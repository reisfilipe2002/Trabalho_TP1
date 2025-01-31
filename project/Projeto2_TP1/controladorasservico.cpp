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
    comandoSQL = "INSERT INTO contas (codigo, senha) VALUES (";
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

    if (listaResultado.empty())
        throw EErroPersistencia("Lista de resultados vazia.");

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
// Classe ComandoListarViagemAll

ComandoListarViagensAll::ComandoListarViagensAll() {
    comandoSQL = "SELECT * FROM viagens";
}

std::vector<Viagem> ComandoListarViagensAll::getResultado() {
    std::vector<Viagem> viagens;
    ElementoResultado resultado;

    if (listaResultado.empty())
        throw EErroPersistencia("Lista de resultados vazia.");

    while (!listaResultado.empty()) {
        Viagem viagem;

        resultado = listaResultado.back();
        listaResultado.pop_back();
        viagem.setCodigo(std::string(resultado.getValorColuna()));

        resultado = listaResultado.back();
        listaResultado.pop_back();
        viagem.setNome(std::string(resultado.getValorColuna()));

        resultado = listaResultado.back();
        listaResultado.pop_back();
        viagem.setAvaliacao(std::stoi(resultado.getValorColuna()));

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
    comandoSQL += "SET nome = '" + destino.getNome() + "', ";
    comandoSQL += "WHERE codigo = '" + destino.getCodigo() + "' ";
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
    comandoSQL += "SET nome = '" + atividade.getNome() + "', ";
    comandoSQL += "preco = '" + std::to_string(atividade.getPreco()) + "' ";
    comandoSQL += "WHERE codigo = '" + atividade.getCodigo() + "' ";
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

ComandoAdicionarHospedagem::ComandoAdicionarHospedagem(const Codigo &codigoDestino, const Hospedagem &hospedagem) {
    comandoSQL = "INSERT INTO hospedagens (codigo, nome, diaria, codigo_destino, codigo_viagem) VALUES (";
    comandoSQL += "'" + hospedagem.getCodigo() + "', ";
    comandoSQL += "'" + hospedagem.getNome() + "', ";
    comandoSQL += "'" + std::to_string(hospedagem.getDiaria()) + "', ";
    comandoSQL += "'" + codigoDestino.getValor() + "', ";
}

//--------------------------------------------------------------------------------------------
// Classe ComandoExcluirHospedagem

ComandoExcluirHospedagem::ComandoExcluirHospedagem(const Codigo &codigoDestino, const Codigo &codigoHospedagem) {
    comandoSQL = "DELETE FROM hospedagens WHERE codigo = '";
    comandoSQL += codigoHospedagem.getValor();
    comandoSQL += "' AND codigo_destino = '";
    comandoSQL += codigoDestino.getValor();
    comandoSQL += "'";
}


//--------------------------------------------------------------------------------------------
// Classe ComandoEditarHospedagem

ComandoEditarHospedagem::ComandoEditarHospedagem(const Codigo &codigoDestino, const Hospedagem &hospedagem) {
    comandoSQL = "UPDATE hospedagens ";
    comandoSQL += "SET nome = '" + hospedagem.getNome() + "', ";
    comandoSQL += "preco = '" + std::to_string(hospedagem.getDiaria()) + "', ";
    comandoSQL += "avaliacao = '" + std::to_string(hospedagem.getAvaliacao()) + "' ";
    comandoSQL += "WHERE codigo = '" + hospedagem.getCodigo() + "' ";
    comandoSQL += "AND codigo_destino = '" + codigoDestino.getValor() + "'";
}

//--------------------------------------------------------------------------------------------
// Classe ComandoConsultarHospedagem

ComandoConsultarHospedagem::ComandoConsultarHospedagem(const Codigo &codigoHospedagem, const Codigo &codigoDestino) {
    comandoSQL = "SELECT * FROM hospedagens WHERE codigo = '";
    comandoSQL += codigoHospedagem.getValor();
    comandoSQL += "'";
}

bool ComandoConsultarHospedagem::getResultado(Hospedagem *hospedagem) {
    ElementoResultado resultado;
    if (listaResultado.empty())
        return false;

    // Supondo que a ordem das colunas seja: codigo, nome, preco, avaliacao, codigo_destino
    resultado = listaResultado.back();
    listaResultado.pop_back();
    hospedagem->setCodigo(std::string(resultado.getValorColuna()));

    resultado = listaResultado.back();
    listaResultado.pop_back();
    hospedagem->setNome(std::string(resultado.getValorColuna()));

    resultado = listaResultado.back();
    listaResultado.pop_back();
    hospedagem->setDiaria(std::stod(resultado.getValorColuna()));

    resultado = listaResultado.back();
    listaResultado.pop_back();
    hospedagem->setAvaliacao(std::stoi(resultado.getValorColuna()));

    return true;
}

//--------------------------------------------------------------------------------------------
// Classe ComandoListarHospedagens

ComandoConsultarHospedagem::ComandoConsultarHospedagem(const Codigo &codigoDestino, const Codigo &codigoHospedagem) {
    comandoSQL = "SELECT * FROM hospedagens WHERE codigo_destino = '";
    comandoSQL += codigoDestino.getValor();
    comandoSQL += "' AND codigo = '";
    comandoSQL += codigoHospedagem.getValor();
    comandoSQL += "'";
}

bool ComandoConsultarHospedagem::getResultado(Hospedagem *hospedagem) {
    bool hospedagens;
    ElementoResultado resultado;
    if (listaResultado.empty())
        return false;
    while (!listaResultado.empty()) {
        Hospedagem hospedagem;

        resultado = listaResultado.back();
        listaResultado.pop_back();
        hospedagem.setCodigo(std::string(resultado.getValorColuna()));

        resultado = listaResultado.back();
        listaResultado.pop_back();
        hospedagem.setNome(std::string(resultado.getValorColuna()));

        resultado = listaResultado.back();
        listaResultado.pop_back();
        hospedagem.setDiaria(std::stod(resultado.getValorColuna()));

        resultado = listaResultado.back();
        listaResultado.pop_back();
        hospedagem.setAvaliacao(std::stoi(resultado.getValorColuna()));
    }

    return hospedagens;
}

//--------------------------------------------------------------------------------------------


bool checarUsuarioCadastrado(Codigo codigo){
    // Todo serviço que precisa de usuário cadastrado precisa chegar primeiro se o usuário está cadastrado.
    // Isso evita usuário descadastrado continuando a executar serviços.

    ComandoContarEntidade comandoContarUsuario("usuarios", "codigo", codigo.getValor());
    comandoContarUsuario.executar();

    if (comandoContarUsuario.getResultado() == 0)
        return false;

    return true;
}

bool CntrServicoAutenticacao::autenticar(const Codigo &codigo, const Senha &senha){

    ComandoLerSenha comandoLerSenha(codigo);

    try {
        comandoLerSenha.executar();

        string senhaRecuperada;

        senhaRecuperada = comandoLerSenha.getResultado();

        if (senhaRecuperada == senha.getValor())
            return true;

        return false;
    }
    catch(EErroPersistencia &exp) {
        return false;
    }
}
bool CntrServicoPessoal::cadastrarUsuario(Usuario usuario){

    ComandoCadastrarUsuario comandoCadastrar(usuario);

    try{
        comandoCadastrar.executar();
        return true;
    }
    catch(EErroPersistencia &exp) {
        return false;
    }
}

Codigo CntrServicoViagens::gerarCodigo(){

    int digitoChar;
    string digitoAleatorio;
    string stringCodigoAleatorio = "";
    Codigo codigoAleatorio;

    for (int i = 0; i < 5; i++)
    {
        digitoChar = rand() % 2;

        if (digitoChar)
            digitoAleatorio = 'A' + rand()%26;
        else
            digitoAleatorio = to_string(rand() % 10);

        stringCodigoAleatorio += digitoAleatorio;
    }

    codigoAleatorio.setValor(stringCodigoAleatorio);

    return codigoAleatorio;
}

Codigo CntrServicoViagens::gerarCodigoValido(string entidade){

    Codigo codigoAleatorio;
    bool codigoValidoEncontrado = false;

    while (!codigoValidoEncontrado){
        codigoAleatorio = gerarCodigo();

        if (codigoValido(entidade, codigoAleatorio))
            codigoValidoEncontrado = true;
    }

    return codigoAleatorio;
}
int CntrServicoViagens::compararDatas(Data dataUm, Data dataDois)
{
    // Checar se a dataDois é maior ou igual à dataUm.

    char delim = '-';
	int posicaoPrimeiroDelim = 2;
	int posicaoSegundoDelim = 5;

	int diaUm, mesUm, anoUm;
	int diaDois, mesDois, anoDois;

    diaUm = stoi(dataUm.getValor().substr(0, 2));
	mesUm = stoi(dataUm.getValor().substr(posicaoPrimeiroDelim + 1, 2));
	anoUm = stoi(dataUm.getValor().substr(posicaoSegundoDelim + 1, 2));

    diaDois = stoi(dataDois.getValor().substr(0, 2));
	mesDois = stoi(dataDois.getValor().substr(posicaoPrimeiroDelim + 1, 2));
	anoDois = stoi(dataDois.getValor().substr(posicaoSegundoDelim + 1, 2));

    switch (compararUnidadesData(anoUm, anoDois)){
        case 3:
            return 3;
        case 1:
            return 1;
        case 2:
            switch (compararUnidadesData(mesUm, mesDois)){
                case 3:
                    return 3;
                case 1:
                    return 1;
                case 2:
                    return compararUnidadesData(diaUm, diaDois);
            }
    }
}

bool CntrServicoViagens::checarIntervaloDatas(Data primeiroDataUm, Data primeiroDataDois, Data segundoDataUm, Data segundoDataDois)
{
    // Considerando o primeiro como a data à qual a segunda precisa se ajustar.
    // Assim, segundoDataUm precisa ser maior ou igual a primeiroDataUm.
    // E segundoDataDois precisa ser menor ou igual a primeiroDataDois.

    if (compararDatas(primeiroDataUm, segundoDataUm) == 1)
        return false;

    if (compararDatas(primeiroDataDois, segundoDataDois) == 3)
        return false;

    return true;
}

double CntrServicoViagens::dinheiroParaDouble(Dinheiro dinheiro)
{
    string valor;
    valor = dinheiro.getValor();

	while (valor.find(".") != string::npos)
		valor.replace(valor.find("."), 1, "");

	while (valor.find(",") != string::npos)
		valor.replace(valor.find(","), 1, ".");

    // Conversăo do valor em formato certo para double.
	return stod(valor);
}