#ifndef MANIOPT_RETRUCTION_H_
#define MANIOPT_RETRUCTION_H_

#include "maniopt/vector.h"

/** @brief 多様体上の最適化のための名前空間． */
namespace maniopt {

/**
 * @brief レトラクションを管理するクラス．
 */
class Retruction {
public:
  /**
   * レトラクションを計算して返す．
   *
   * @param[in] x ベクトル
   * @param[in] t ステップ幅
   * @param[in] eta 勾配
   * @return レトラクションによる多様体上の点
   */
  virtual Vector Compute(const Vector& x, double t, const Vector& eta) const = 0;
};

/**
 * 正規化して返す．
 *
 * @param[in] v ベクトル
 * @return 正規化したベクトル
 */
Vector Normalize(const Vector& v);

/**
 * @brief 射影によるレトラクション．
 */
class ProjRetruction : public Retruction {
public:
  /**
   * レトラクションを計算して返す．
   *
   * @param[in] x ベクトル
   * @param[in] t ステップ幅
   * @param[in] eta 勾配
   * @return レトラクションによる多様体上の点
   */
  Vector Compute(const Vector& x, double t, const Vector& eta) const override;
};

} // namespace maniopt

#endif // MANIOPT_RETRUCTION_H_
