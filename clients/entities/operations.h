#include <string>
#include <list>

// Imprime todos os clientes cadastrados, cada qual seguido de um número indexador
// e retorna o número selecionado.
int getClientOption(std::list<Client> clients) {
  int option;
  
  for (int i = 0; i < clients.size(); i++) {
    auto it = std::next(clients.begin(), i);
    Client client = *it;

    std::cout << i + 1 << " - " << client.name << '\n';
  }

  std::cin >> option;

  return option;
}

// Com exceção de 'exit()', todas as funções de 'Operations' recebem como parâmetro
// uma referência para a lista de clientes, assim permitindo que as alterações feitas
// dentro das funções sejam refletidas fora delas.
struct Operations {
  void registerNewClient(std::list<Client> &clients) {
    std::cout << "\nCadastrando novo cliente..." << '\n';
    
    Client client;

    std::cout << "Nome: ";
    std::getline(std::cin >> std::ws, client.name);

    std::cout << "Endereço: ";
    std::getline(std::cin, client.address);

    std::cout << "CPF: ";
    std::cin >> client.cpf;

    std::cout << "Data de nascimento: ";
    std::cin >> client.birthDate;
    
    clients.push_back(client);

    std::cout << "\nCliente " << client.name << " cadastrado com sucesso!" << '\n';
  };

  void viewClientInfo(std::list<Client> &clients) {
    if (clients.size() == 0) {
      std::cout << "\nNão há clientes cadastrados!" << '\n';
      return;
    }
    
    std::cout << "\nDe qual cliente deseja visualizar informações?" << '\n';

    int clientOption = getClientOption(clients);

    // Percorre a lista de clientes até achar o cliente selecionado.
    // O ponteiro 'it' aponta para o elemento da lista que está na posição 'clientOption - 1'.
    // Também presente nas próximas funções.
    auto it = std::next(clients.begin(), clientOption - 1);
    Client client = *it;

    std::cout << "\nVisualizando informações de " << client.name << "..." << '\n';

    std::cout << "Nome: " << client.name << '\n'
              << "Endereço: " << client.address << '\n'
              << "CPF: " << client.cpf << '\n'
              << "Data de nascimento: " << client.birthDate << '\n';

    // Verifica se o cliente possui um empréstimo vigente.
    if (client.loan > 0) {
      std::cout << "Valor do empréstimo: " << client.loan << '\n'
                << "Data do empréstimo: " << client.loanDate << '\n';

      std::cout << "Parcelas: " << '\n';
      std::cout << '\n';

      // Imprime as informações de cada parcela do empréstimo.
      for (auto installment : client.installments) {
        std::cout << "Valor: " << installment.value << '\n'
                  << "Vencimento: " << installment.dueDate << '\n'
                  << "Pagamento: " << installment.paymentDate << '\n'
                  << "Paga: " << (installment.isPaid ? "Sim" : "Não") << '\n';

        std::cout << '\n';
      }
    }
  };

  void editClientInfo(std::list<Client> &clients) {
    if (clients.size() == 0) {
      std::cout << "\nNão há clientes cadastrados!" << '\n';
      return;
    }

    std::cout << "\nDe qual cliente deseja alterar informações?" << '\n';

    int infoOption;
    int clientOption = getClientOption(clients);

    auto it = std::next(clients.begin(), clientOption - 1);
    Client client = *it;

    std::cout << "\nQual informação deseja alterar?" << '\n';
    std::cout << "[1] - NOME" << '\n'
              << "[2] - ENDEREÇO" << '\n'
              << "[3] - CPF" << '\n'
              << "[4] - DATA DE NASCIMENTO" << '\n';

    std::cin >> infoOption;

    std::cout << "Novo valor: ";

    // TODO: Refactor this switch statement to use a hash map instead (if possible).
    switch(infoOption) {
      case 1:
        std::getline(std::cin >> std::ws, client.name);
        break;
      case 2:
        std::getline(std::cin, client.address);
        break;
      case 3:
        std::cin >> client.cpf;
        break;
      case 4:
        std::cin >> client.birthDate;
        break;
      case 5:
        std::cin >> client.loan;
        break;
      case 6:
        std::cin >> client.loanDate;
        break;
      default:
        std::cout << "Opção inválida!" << '\n';
        return;
    }

    // Atualiza o cliente na lista.
    // Isso é feito atribuindo o valor de 'client' para o elemento apontado pelo ponteiro 'it'.
    // Assim refletindo as alterações para fora do escopo da função.
    // Também presente nas próximas funções.
    *it = client;
  };

  void registerPaidInstallment(std::list<Client> &clients) {
    if (clients.size() == 0) {
      std::cout << "\nNão há clientes cadastrados!" << '\n';
      return;
    }
    
    std::cout << "\nPara qual cliente deseja registrar um pagamento?" << '\n';

    int clientOption = getClientOption(clients);

    auto it = std::next(clients.begin(), clientOption - 1);
    Client client = *it;

    if (client.loan == 0) {
      std::cout << "\nEste cliente não possui empréstimos!" << '\n';
      return;
    }

    std::cout << "\nQual parcela deseja pagar?" << '\n';

    // Imprime a data de vencimento de cada parcela do cliente
    // seguida de um número indexador para seleção de uma determinada parcela.
    for (int i = 0; i < client.installments.size(); i++) {
      // Percorre a lista de parcelas do cliente até achar a parcela selecionada.    
      auto inst_it = std::next(client.installments.begin(), i);
      Installment installment = *inst_it;

      std::cout << i + 1 << " - " << installment.dueDate << '\n';
    }

    int installmentOption;
    std::cin >> installmentOption;

    // Novamente percorre a lista de parcelas para achar a selecionada.    
    auto inst_it = std::next(client.installments.begin(), installmentOption - 1);
    Installment installment = *inst_it;

    if (installment.isPaid) {
      std::cout << "\nEsta parcela já foi paga!" << '\n';
      return;
    }

    std::cout << "\nRegistrando pagamento para " << client.name << "..." << '\n';

    std::cout << "Data do pagamento: ";
    std::cin >> installment.paymentDate;

    installment.isPaid = true;

    // Atribui o valor de 'installment' para o elemento apontado pelo ponteiro 'inst_it'.
    *inst_it = installment;
    *it = client;

    // Verifica se todas as parcelas foram pagas.
    for (auto installment : client.installments) {
      if (!installment.isPaid) return;
    }

    // Caso todas as parcelas tenham sido pagas, o empréstimo é zerado
    // para que um novo possa ser feito.
    client.loan = 0;
    client.loanDate = "";
    client.installments.clear();

    // Novamente atualiza o cliente na lista com as novas informações sobre empréstimo.
    *it = client;

    std::cout << "\nEmpréstimo de " << client.name << " pago!" << '\n';
  };

  void registerNewLoan(std::list<Client> &clients) {
    if (clients.size() == 0) {
      std::cout << "\nNão há clientes cadastrados!" << '\n';
      return;
    }

    std::cout << "\nPara qual cliente deseja registrar um novo empréstimo?" << '\n';

    int installments;
    int clientOption = getClientOption(clients);
    
    auto it = std::next(clients.begin(), clientOption - 1);
    Client client = *it;

    if (client.loan > 0) {
      std::cout << "\nEste cliente já possui um empréstimo em aberto!" << '\n';
      return;
    }

    std::cout << "\nRegistrando novo empréstimo para " << client.name << "..." << '\n';

    std::cout << "Valor do empréstimo: ";
    std::cin >> client.loan;

    std::cout << "Data do empréstimo: ";
    std::cin >> client.loanDate;

    std::cout << "Em quantas parcelas deseja pagar? (máximo 12)" << '\n';
    std::cin >> installments;

    if (installments > 12 || installments < 1) {
      std::cout << "Número de parcelas inválido!" << '\n';
      return;
    }

    // Considerando a data de pagamento do empréstimo no formato dd/mm/aaaa, o código abaixo
    // separa o dia, o mês e o ano localizados em relação à primeira e à segunda barras (/)
    // e atribui cada valor a uma variável diferente do tipo string.
    std::size_t firstSlash = client.loanDate.find('/');
    std::size_t secondSlash = client.loanDate.find('/', firstSlash + 1);
    std::string paymentDay = client.loanDate.substr(0, firstSlash);
    std::string paymentMonth = client.loanDate.substr(firstSlash + 1, secondSlash - firstSlash - 1);
    std::string paymentYear = client.loanDate.substr(secondSlash + 1);

    for (int i = 0; i < installments; i++) {
      Installment installment;

      // Converte as strings para inteiros.
      int paymentYearInt = std::stoi(paymentYear);
      int paymentMonthInt = std::stoi(paymentMonth);
      
      // Verifica se o mês de vencimento excede 12. Se sim, o ano é incrementado em 1
      // e o mês é decrementado em 12, para que esteja entre 1 e 12.
      if (paymentMonthInt + i + 1 > 12) {
        paymentMonthInt = (paymentMonthInt + i + 1) - 12;
        paymentYearInt = std::stoi(paymentYear) + 1;
      } else {
        // Caso contrário, o mês é incrementado em 1.
        paymentMonthInt += i + 1;
      }

      installment.isPaid = false; // A parcela sempre é registrada como não paga.
      installment.value = client.loan / installments;
      // Imprime a data de vencimento no formato dd/mm/aaaa,
      // sendo o mês e o ano convertidos para string.
      installment.dueDate = paymentDay + '/' +  std::to_string(paymentMonthInt)  + '/' + std::to_string(paymentYearInt);
    
      client.installments.push_back(installment);
    }

    *it = client;
  };

  void eraseClient(std::list<Client> &clients) {
    if (clients.size() == 0) {
      std::cout << "\nNão há clientes cadastrados!" << '\n';
      return;
    }
    
    std::cout << "\nQual cliente deseja excluir?" << '\n';

    int clientOption = getClientOption(clients);
    auto it = std::next(clients.begin(), clientOption - 1);

    clients.erase(it);

    std::cout << "\nCliente excluído com sucesso!" << '\n';
  };

  void exit() {
    std::cout << "Saindo..." << '\n';
  };
};
