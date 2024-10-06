# 多様体上の最適化理論のための実験用コード

## 概要

本プログラムは多様体上の最適化理論のための実験用コードです．    
以下の問題を計算するための実装が含まれています．

```
Minimize x^TAx
Subject to x in S^{n-1}
```

## 使い方

Dockerfile を使って Docker コンテナを作成し，コンテナ上で以下を実行すると
サンプルコードが実行できます．

```
# cmake -S . -B build
# cd build
# make
# ./maniopt
```
