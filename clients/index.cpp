#include <iostream>
#include <unordered_map>
#include <list>
#include <functional>

#include "entities/client.h"
#include "entities/operations.h"

// Exibe o menu e retorna a opção escolhida.
int getMenuOption() {
  int option;

  std::cout << '\n';

  std::cout << "[1] - Cadastrar novo cliente" << '\n'
            << "[2] - Visualizar informações de um cliente" << '\n'
            << "[3] - Editar informações de um cliente" << '\n'
            << "[4] - Cadastrar parcela paga" << '\n'
            << "[5] - Cadastrar novo empréstimo" << '\n'
            << "[6] - Excluir cliente" << '\n'
            << "[7] - Sair" << '\n';

  std::cin >> option;

  return option;
}

int main() {
  int option;
  Operations op;
  std::list<Client> clients;

  // Hash Map que associa cada opção do menu a uma função da struct 'Operations'.
  // Isso foi feito para evitar o uso de um switch statement com vários casos ou vários if statements
  // para a execução da função desejada.
  std::unordered_map<int, std::function<void(Operations*)>> operations = {
    {1, std::bind(&Operations::registerNewClient, &op, std::ref(clients))},
    {2, std::bind(&Operations::viewClientInfo, &op, std::ref(clients))},
    {3, std::bind(&Operations::editClientInfo, &op, std::ref(clients))},
    {4, std::bind(&Operations::registerPaidInstallment, &op, std::ref(clients))},
    {5, std::bind(&Operations::registerNewLoan, &op, std::ref(clients))},
    {6, std::bind(&Operations::eraseClient, &op, std::ref(clients))},
    {7, &Operations::exit}
  };
    
  while (option != 7) {
    option = getMenuOption();

    if (option < 1 || option > 7) {
      std::cout << "Opção inválida!" << '\n';
    } else {
      // Executa a função associada à opção escolhida.
      // É necessário passar a referência da struct 'Operations' como parâmetro,
      // devido ao tipo da função ser 'void(Operations*)'.
      operations[option](&op);
    }
  }
    
  return 0;
}
