#ifndef MANIOPT_SEARCH_STEP_SIZE_H_
#define MANIOPT_SEARCH_STEP_SIZE_H_

/** @brief 多様体上の最適化のための名前空間． */
namespace maniopt {

/**
 * @brief ステップ幅探索ロジックを管理するクラス．
 */
class SearchStepSize {
public:
  /**
   * ステップ幅を計算して返す．
   *
   * @param[in] a 係数行列
   * @param[in] x 近似解
   * @return レトラクションによる多様体上の点
   * @return ステップ幅
   */
  virtual double Compute(const Matrix& a, const Vector& x) const = 0;
};

/**
 * @brief 固定値によるステップ幅の決定ロジック．
 */
class ConstantStepSize : public SearchStepSize {
public:
  ConstantStepSize() : t_{0} {}
  ConstantStepSize(double t) : t_{t} {}

  /**
   * ステップ幅を計算して返す．
   *
   * @param[in] a 係数行列
   * @param[in] x 近似解
   * @return ステップ幅
   */
  double Compute(const Matrix& a, const Vector& x) const override { return t_; }

private:
  /** 固定するステップ幅 */
  double t_;
};

} // namespace maniopt

#endif // MANIOPT_SEARCH_STEP_SIZE_H_
