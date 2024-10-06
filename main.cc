#include "maniopt/matrix.h"
#include "maniopt/vector.h"
#include "maniopt/search_step_size.h"
#include "maniopt/retruction.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

#include <cblas.h>

/** @brief 多様体上の最適化のための名前空間． */
namespace maniopt {

/**
 * @brief 各反復の情報を管理する構造体．
 */
struct Params {
  /** 探索方向 */
  Vector eta;

  /** 仮の更新位置 */
  Vector tentative;

  /** レトラクションで確定した更新位置 */
  Vector next;
};

/**
 * @brief 反復した結果を管理する構造体．
 */
struct Result {
  /** 初期値 */
  Vector init;

  /** 各反復での情報 */
  std::vector<Params> progress;
};

/**
 * 勾配を計算して返す．
 *
 * 目的関数が x^Tax で多様体が S^{n-1} であるとする．
 *
 * @param[in] a 係数行列
 * @param[in] x 近似解
 */
Vector ComputeEta(const Matrix& a, const Vector& x) {
  auto ax = a * x;
  auto xtax = Dot(x, ax);

  // ax = -xtax*x + ax
  constexpr int kIncx = 1;
  constexpr int kIncy = 1;
  ::cblas_daxpy(x.size(), -xtax, x.data(), kIncx, ax.data(), kIncy);
  auto eta = -2.0 * ax;
  return eta;
}

/**
 * 以下の最適化問題の反復結果を返す．
 *     Minimize x^Tax
 *     Subject to x in S^{n-1}
 *
 * 128回反復した結果を返す．
 *
 * @param[in] a 係数行列
 * @param[in,out] x 初期値を入力して更新する
 * @param[in] search_step_size ステップ幅探索
 * @param[in] retruction レトラクション
 * @return 反復結果
 */
Result Optimize(const Matrix& a, Vector& x,
    const SearchStepSize& search_step_size = ConstantStepSize(0.2),
    const Retruction& retruction = ProjRetruction()) {
  constexpr int kMaxK = 128;
  Result result;
  result.init = x;
  for (int k = 0; k < kMaxK; k++) {
    Params params;
    auto eta = ComputeEta(a, x);
    auto t = search_step_size.Compute(a, x);
    params.eta = eta;
    params.tentative = x + t * eta;

    x = retruction.Compute(x, t, eta);
    params.next = x;
    result.progress.emplace_back(params);
  }

  return result;
}

/**
 * 反復結果を出力ストリームに出力する．
 *
 * @param[in] result 反復結果
 * @param[in,out] out 出力ストリーム
 * @return 出力ストリームへの参照
 */
std::ostream& Print(const Result& result, std::ostream& out = std::cout) {
  out << std::setprecision(16);
  out << "init: " << result.init << "\n";
  for (int k = 0, n = result.progress.size(); k < n; k++) {
    const auto& params = result.progress[k];
    out << "k: " << k;
    out << ", eta: " << params.eta;
    out << ", x + t*eta: " << params.tentative;
    out << ", next: " << params.next;
    out << "\n";
  }
  return out;
}

} // namespace maniopt

/**
 * 実験用メインメソッド．
 *
 * @return 終了コード
 */
int main() {
  maniopt::Matrix a({5, 2, 2, 3}, 2);
  maniopt::Vector x({1.0 / std::sqrt(2.0), 1.0 / std::sqrt(2.0)});
  auto result = maniopt::Optimize(a, x,
      maniopt::ConstantStepSize(0.2),
      maniopt::ProjRetruction()
  );

  maniopt::Print(result);

  return 0;
}
