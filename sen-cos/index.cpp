#include <iostream>
#include <cmath>

#include "math.h"

int main() {
  double deg;

  std::cout << "Digite um valor de ângulo em graus (x): ";
  std::cin >> deg;

  double theta = math::deg2rad(deg);

  std::cout << "\nCalculando usando funções próprias..." << '\n';
  
  double sin3 = math::sin(theta, 3);
  double cos3 = math::cos(theta, 3);

  std::cout << "\nPara 3 termos:" << '\n'
            << "sen(x) = " << sin3 << '\n'
            << "cos(x) = " << cos3 << '\n';

  double sin40 = math::sin(theta, 40);
  double cos40 = math::cos(theta, 40);

  std::cout << "\nPara 40 termos:" << '\n'
            << "sen(x) = " << sin40 << '\n'
            << "cos(x) = " << cos40 << '\n';

  std::cout <<"\nCalculando usando cmath..." << '\n';

  double sin_c = sin(theta);
  double cos_c = cos(theta);

  std::cout << "\nsen(x) = " << sin_c << '\n'
            << "cos(x) = " << cos_c << '\n';
  
  std::cout << "\nDiferença entre 3 termos e cmath:" << '\n';

  double sin3Difference = fabs(sin_c - sin3);
  double cos3Difference = fabs(cos_c - cos3);

  std::cout << "sin: " << sin3Difference << '\n'
            << "cos: " << cos3Difference << '\n';
  
  return 0;
}
