#include <iostream>
#include "Avaliacao.cpp"
#include "Codigo.cpp"
#include "Data.cpp"
#include "Dinheiro.cpp"
#include "Duracao.cpp"
#include "Horario.cpp"
#include "Nome.cpp"
#include "Senha.cpp"

using namespace std;

int main() {
    Nome *ptr;
    ptr = new Nome();

    
    if (ptr->setNome("João da Silva Pereira")) {
        cout << "Nome=" << ptr->getNome() << endl;
    } else {
        cout << "Nome inválido" << endl;
    }

  
    if (ptr->setNome("João da Silva Pereira Borges Neto Primo")) {
        cout << "Nome=" << ptr->getNome() << endl;
    } else {
        cout << "Nome inválido" << endl;
    }

    delete ptr;

    return 0;
}






