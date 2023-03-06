#include <list>
#include <string>
#include "installment.h"

struct Client {
  std::string name;
  std::string address;
  std::string cpf;
  std::string birthDate;

  float loan = 0;
  std::string loanDate;

  std::list<Installment> installments;
};
