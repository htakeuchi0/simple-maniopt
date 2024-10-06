#include "maniopt/vector.h"
#include <cblas.h>

namespace maniopt {

Vector::Vector() {}

Vector::Vector(std::size_t size) {
  SetSize(size);
}

Vector::Vector(const std::vector<double>& vec) : raw_{vec} {}

void Vector::SetSize(std::size_t size) {
  raw_.resize(size);
}

double *Vector::data() noexcept { return raw_.data(); }

const double *Vector::data() const noexcept { return raw_.data(); }

std::size_t Vector::size() const noexcept { return raw_.size(); }

auto Vector::begin() { return raw_.begin(); }

auto Vector::end() { return raw_.end(); }

auto Vector::begin() const { return raw_.begin(); }

auto Vector::end() const { return raw_.end(); }

auto Vector::cbegin() const { return raw_.cbegin(); }

auto Vector::cend() const { return raw_.cend(); }

const Vector operator*(const Vector& lhs, double rhs) {
  constexpr int kIncx = 1;
  constexpr int kIncy = 1;
  Vector y{lhs.size()};
  ::cblas_daxpy(lhs.size(), rhs, lhs.data(), kIncx, y.data(), kIncy);
  return y;
}

const Vector operator*(double lhs, const Vector& rhs) {
  return rhs * lhs;
}

const Vector operator+(const Vector& lhs, const Vector& rhs) {
  Vector added{rhs};
  constexpr double kAlpha = 1.0;
  constexpr int kIncx = 1;
  constexpr int kIncy = 1;
  ::cblas_daxpy(lhs.size(), kAlpha, lhs.data(), kIncx, added.data(), kIncy);
  return added; 
}

const double Dot(const Vector& lhs, const Vector& rhs) {
  constexpr int kIncx = 1;
  constexpr int kIncy = 1;
  double dot = ::cblas_ddot(lhs.size(), lhs.data(), kIncx, rhs.data(), kIncy);
  return dot;
}

std::ostream& operator<<(std::ostream& lhs, const Vector& rhs) {
  lhs << "[ ";
  for (auto&& entry : rhs) {
    lhs << entry << ", ";
  }
  lhs << "]";
  return lhs;
}

} // namespace maniopt
