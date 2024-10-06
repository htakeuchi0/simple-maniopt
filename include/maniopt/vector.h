#ifndef MANIOPT_VECTOR_H_
#define MANIOPT_VECTOR_H_

#include <vector>
#include <ostream>

/** @brief 多様体上の最適化のための名前空間． */
namespace maniopt {

/**
 * @brief ベクトルを管理するクラス．
 */
class Vector {
public:
  Vector();
  Vector(std::size_t size);
  Vector(const std::vector<double>& vec);
  ~Vector() = default;
  Vector(const Vector& rhs) = default;
  Vector(Vector&& rhs) = default;
  Vector& operator=(const Vector& rhs) = default;
  Vector& operator=(Vector&& rhs) = default;
  void SetSize(std::size_t size);
  double *data() noexcept;
  const double *data() const noexcept;
  std::size_t size() const noexcept;
  auto begin();
  auto end();
  auto begin() const;
  auto end() const;
  auto cbegin() const;
  auto cend() const;

private:
  std::vector<double> raw_;
};

const Vector operator*(const Vector& lhs, double rhs);

const Vector operator*(double lhs, const Vector& rhs);

const Vector operator+(const Vector& lhs, const Vector& rhs);

const double Dot(const Vector& lhs, const Vector& rhs);

std::ostream& operator<<(std::ostream& lhs, const Vector& rhs);

} // namespace maniopt

#endif // MANIOPT_VECTOR_H_
