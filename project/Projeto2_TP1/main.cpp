#include <iostream>
#include "curses.h"
#include "dominios.h"
#include "interfaces.h"
#include "controladorasapresentacao.h"
#include "controladorasservico.h"

using namespace std;

int main()
{
    // Criando uma conta fictícia
 // Supondo que exista um construtor padrão

    // Instanciando os controladores de apresentação e passando a conta
    CntrApresentacaoControle *cntrApresentacaoControle = new CntrApresentacaoControle();
    IApresentacaoAutenticacao *cntrApresentacaoAutenticacao = new CntrApresentacaoAutenticacao();
    IApresentacaoViagem *cntrApresentacaoViagem = new CntrApresentacaoViagem();
    IApresentacaoViajante *cntrApresentacaoViajante = new CntrApresentacaoViajante();

    // Instanciando os controladores de serviço
    IServicoAutenticacao *cntrServicoAutenticacao = new CntrServicoAutenticacao();
    IServicoViajante *cntrServicoViajante = new CntrServicoViajante();
    IServicoViagem *cntrServicoViagem = new CntrServicoViagem();

    // Ligando controladores de apresentação aos controladores de serviço
    cntrApresentacaoControle->setCntrApresentacaoAutenticacao(cntrApresentacaoAutenticacao);
    cntrApresentacaoControle->setCntrIApresentacaoViajante(cntrApresentacaoViajante);
    cntrApresentacaoControle->setCntrIApresentacaoViagem(cntrApresentacaoViagem);

    cntrApresentacaoAutenticacao->setCntrServicoAutenticacao(cntrServicoAutenticacao);
    cntrApresentacaoViajante->setCntrServicoViajante(cntrServicoViajante);
    cntrApresentacaoViajante->setCntrServicoViagem(cntrServicoViagem);

    // Iniciando interface curses
    initscr();         
    cntrApresentacaoControle->executar();
    endwin();          

    return 0;
}
