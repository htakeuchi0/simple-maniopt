#ifndef MAINOPT_MATRIX_H_
#define MAINOPT_MATRIX_H_

#include <vector>
#include "maniopt/vector.h"

/** @brief 多様体上の最適化のための名前空間． */
namespace maniopt {

/**
 * @brief 行列を管理するクラス．
 */
class Matrix {
public:
  Matrix();
  Matrix(std::size_t col, std::size_t row);
  Matrix(const std::vector<double>& vec, std::size_t size);
  ~Matrix() = default;
  Matrix(const Matrix& rhs) = default;
  Matrix(Matrix&& rhs) = default;
  Matrix& operator=(const Matrix& rhs) = default;
  Matrix& operator=(Matrix&& rhs) = default;
  void SetSize(std::size_t col, std::size_t row);
  double *data() noexcept;
  const double *data() const noexcept;
  std::size_t Col() const noexcept;
  std::size_t Row() const noexcept;
  std::size_t size() const noexcept;

private:
  std::vector<double> raw_;
  std::size_t col_;
  std::size_t row_;
};

const Matrix operator*(const Matrix& lhs, const Matrix& rhs);

const Vector operator*(const Matrix& lhs, const Vector& rhs);

} // namespace maniopt

#endif // MAINOPT_MATRIX_H_
