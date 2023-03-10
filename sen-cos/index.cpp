#include <iostream>
#include <cmath>

#include "math.h"

void calculateAndPrintOwnResults(double theta, int n, double sin_c, double cos_c) {
  auto sin = math::sin(theta, n);
  auto cos = math::cos(theta, n);

  std::cout << "\nPara "<< n << " termos:" << '\n'
            << "sen(x) = " << sin << '\n'
            << "cos(x) = " << cos << '\n';

  std::cout << "\nDiferença entre " << n << " termos e cmath:" << '\n';

  double sinDifference = fabs((double)(sin_c - sin));
  double cosDifference = fabs((double)(cos_c - cos));

  double sinDiffPercentage = (1 - (double)(sin / sin_c)) * 100;
  double cosDiffPercentage = (1 - (double)(cos / cos_c)) * 100;

  std::cout << "(abs) sin: " << sinDifference << " | (%) sin: " << sinDiffPercentage << "%" << '\n'
            << "(abs) cos: " << cosDifference << " | (%) cos: " << cosDiffPercentage << "%" << '\n';
}

int main() {
  double deg;

  std::cout << "Digite um valor de ângulo em graus (x): ";
  std::cin >> deg;

  double theta = math::deg2rad(deg);

  std::cout << "\nCalculando usando cmath..." << '\n';

  double sin_c = sin(theta);
  double cos_c = cos(theta);

  std::cout << "\nsen(x) = " << sin_c << '\n'
            << "cos(x) = " << cos_c << '\n';

  std::cout << "\nCalculando usando funções próprias..." << '\n';
  
  calculateAndPrintOwnResults(theta, 3, sin_c, cos_c);
  calculateAndPrintOwnResults(theta, 40, sin_c, cos_c);
  
  return 0;
}
