#include "controladorasapresentacao.h"

//--------------------------------------------------------------------------------------------
// Implementaçőes dos métodos das classes controladoras da camada de apresentaçăo.


//--------------------------------------------------------------------------------------------
// Implementaçőes dos métodos da classe controladora apresentaçăo controle.

void CntrApresentacaoControle::executar() {

    // Mensagens a serem apresentadas na tela inicial.
    char texto1[]="Selecione um dos serviços:";
    char texto2[]="a - Acessar sistema.";
    char texto3[]="b - Cadastrar usuário.";
    char texto5[]="d - Encerrar execução do sistema.";

    // Mensagens a serem apresentadas na tela de seleção de serviço.
    char texto6[]="Selecione um dos serviços:";
    char texto7[]="a - Selecionar serviços de viajante.";
    char texto8[]="b - Selecionar serviços relacionados a viagem.";
    char texto9[]="c - Encerrar sessão.";

    char texto10[]="Falha na autenticação. Digite algo para continuar.";  // Mensagem a ser apresentada.

    Conta conta("defaultCodigo", "defaultSenha");  // Define a variável conta com valores padrão.
    int campo;  // Campo de entrada.
    int linha, coluna;  // Dados sobre tamanho da tela.

    getmaxyx(stdscr, linha, coluna);  // Armazena quantidade de linhas e colunas.

    bool apresentar = true;  // Controle de laço.

    while (apresentar) {
        // Apresenta tela inicial.
        clear();  // Limpa janela.
        mvprintw(linha/4, coluna/4, "%s", texto1);
        mvprintw(linha/4 + 2, coluna/4, "%s", texto2);
        mvprintw(linha/4 + 4, coluna/4, "%s", texto3);
        mvprintw(linha/4 + 8, coluna/4, "%s", texto5);

        noecho();
        campo = getch();  // Leitura do campo de entrada e conversão de ASCII.
        echo();

        switch (campo) {
            case 'a':
                if (cntrApresentacaoAutenticacao->autenticar(conta)) {  // Solicita autenticação.
                    bool autenticado = true;  // Controle de laço interno.
                    while (autenticado) {
                        // Apresenta tela de seleção de serviço.
                        clear();
                        mvprintw(linha/4, coluna/4, "%s", texto6);
                        mvprintw(linha/4 + 2, coluna/4, "%s", texto7);
                        mvprintw(linha/4 + 4, coluna/4, "%s", texto8);
                        mvprintw(linha/4 + 6, coluna/4, "%s", texto9);

                        noecho();
                        campo = getch();
                        echo();

                        switch (campo) {
                            case 'a': cntrApresentacaoViajante->executar(conta); break;
                            case 'b': cntrApresentacaoViagem->executar(conta); break;
                            case 'c': autenticado = false; break;
                        }
                    }
                } else {
                    clear();
                    mvprintw(linha/4, coluna/4, "%s", texto10);
                    noecho();
                    getch();
                    echo();
                }
                break;

            case 'b': cntrApresentacaoViajante->cadastrar(); break;
            case 'd': apresentar = false; break;
        }
    }
}

//--------------------------------------------------------------------------------------------
// Implementaçőes dos métodos da classe controladora apresentaçăo autenticaçăo.

bool CntrApresentacaoAutenticacao::autenticar(Conta &conta) {

    // Mensagens a serem apresentadas na tela de autenticação.
    char texto1[] = "Digite a Conta: ";
    char texto2[] = "Digite a senha: ";
    char texto3[] = "Dado em formato incorreto. Digite algo.";

    // Campos de entrada.
    char campo1[80];
    char campo2[80];

    int linha, coluna; // Dados sobre tamanho da tela.

    getmaxyx(stdscr, linha, coluna); // Armazena quantidade de linhas e colunas.
    
    Senha senha(""); // Instancia a classe Senha com um valor padrão.

    echo(); // Habilita eco.

    while (true) {
        // Apresenta tela de autenticação.
        clear();
        mvprintw(linha/4, coluna/4, "%s", texto1);
        getstr(campo1);
        mvprintw(linha/4 + 2, coluna/4, "%s", texto2);
        getstr(campo2);

        try {
            conta.setCodigo(campo1);
            conta.setSenha(campo2);
            break;
        }
        catch (std::invalid_argument &exp) {
            mvprintw(linha/4 + 4, coluna/4, "%s", texto3);
            noecho();
            getch();
            echo();
        }
    }

    Codigo codigo(conta.getCodigo());
    senha.setValor(conta.getSenha());
    return cntr->autenticar(codigo, senha); // Solicita serviço de autenticação.
}

//--------------------------------------------------------------------------------------------
// Implementaçőes dos métodos da classe controladora apresentaçăo viajante.


