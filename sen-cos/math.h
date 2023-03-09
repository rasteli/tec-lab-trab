#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

namespace mp = boost::multiprecision;

namespace math {
  using boost_int = mp::cpp_int;
  using boost_float = mp::cpp_dec_float_100;

  boost_int factorial(int n) {
    if (n <= 1) return 1;

    return n * factorial(n - 1);
  }
  
  double deg2rad(double deg) {
    return M_PI * deg / 180;
  }

  boost_float cos(double theta, int n) {
    boost_float sum = 0;

    for (int i = 0; i < n; i++) {
      boost_float dividend = pow(-1, i) * pow(theta, 2 * i);

      sum += dividend / boost_float(factorial(2 * i));
    }

    return sum;
  }

  boost_float sin(double theta, int n) {
    boost_float sum = 0;

    for (int i = 0; i < n; i++) {
      boost_float dividend = pow(-1, i) * pow(theta, 2 * i + 1);
      
      sum += dividend / boost_float(factorial(2 * i + 1));
    }

    return sum;
  }
}
