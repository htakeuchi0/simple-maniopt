#include "maniopt/matrix.h"
#include <cblas.h>

namespace maniopt {

Matrix::Matrix() : col_{0}, row_{0} {}

Matrix::Matrix(std::size_t col, std::size_t row) {
  SetSize(col, row);
}

Matrix::Matrix(const std::vector<double>& vec, std::size_t size) : raw_{vec}, row_{size}, col_{size} {}

void Matrix::SetSize(std::size_t col, std::size_t row) {
  col_ = col;
  row_ = row;
  raw_.resize(col * row);
}

double *Matrix::data() noexcept { return raw_.data(); }

const double *Matrix::data() const noexcept { return raw_.data(); }

std::size_t Matrix::Col() const noexcept { return col_; }

std::size_t Matrix::Row() const noexcept { return row_; }

std::size_t Matrix::size() const noexcept { return raw_.size(); }

const Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
  Matrix c{lhs.Row(), rhs.Col()};
  constexpr double kAlpha = 1.0;
  constexpr double kBeta = 0.0;
  ::cblas_dgemm(
      ::CblasColMajor,
      ::CblasNoTrans,
      ::CblasNoTrans,
      lhs.Row(),
      rhs.Col(),
      lhs.Col(),
      kAlpha,
      lhs.data(),
      lhs.Row(),
      rhs.data(),
      rhs.Row(),
      kBeta,
      c.data(),
      c.Row());
  return c;
}

const Vector operator*(const Matrix& lhs, const Vector& rhs) {
  Vector y{lhs.Row()};
  constexpr double kAlpha = 1.0;
  constexpr double kBeta = 0;
  constexpr int kIncx = 1;
  constexpr int kIncy = 1;
  ::cblas_dgemv(
      ::CblasColMajor,
      ::CblasNoTrans,
      lhs.Row(),
      lhs.Col(),
      kAlpha,
      lhs.data(),
      lhs.Row(),
      rhs.data(),
      kIncx,
      kBeta,
      y.data(),
      kIncy);
  return y;
}

} // namespace maniopt

