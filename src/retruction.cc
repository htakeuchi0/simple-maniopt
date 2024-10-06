#include <cblas.h>
#include "maniopt/retruction.h"

namespace maniopt {

Vector Normalize(const Vector& v) {
  constexpr int kIncx = 1;
  constexpr int kIncy = 1;
  double size = ::cblas_dnrm2(v.size(), v.data(), kIncx);
  Vector result{v.size()};
  ::cblas_daxpy(v.size(), 1.0 / size, v.data(), kIncx, result.data(), kIncy);
  return result;
}

Vector ProjRetruction::Compute(const Vector& x, double t, const Vector& eta) const {
  Vector result{x};
  constexpr int kIncx = 1;
  constexpr int kIncy = 1;
  ::cblas_daxpy(eta.size(), t, eta.data(), kIncx, result.data(), kIncy);
  result = Normalize(result);
  return result;
}

} // namespace maniopt
