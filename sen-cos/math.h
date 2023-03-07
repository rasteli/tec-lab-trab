#include <cmath>

namespace math {
  int factorial(int n) {
    if (n <= 1) return 1;

    return n * factorial(n - 1);
  }
  
  double deg2rad(double deg) {
    return M_PI * deg / 180;
  }

  double cos(double theta, int n) {
    double sum = 0;

    for (int i = 0; i < n; i++) {
      sum += pow(-1, i) * pow(theta, 2 * i) / factorial(2 * i);
    }

    return sum;
  }

  double sin(double theta, int n) {
    double sum = 0;

    for (int i = 0; i < n; i++) {
      sum += pow(-1, i) * pow(theta, 2 * i + 1) / factorial(2 * i + 1);
    }

    return sum;
  }
}
