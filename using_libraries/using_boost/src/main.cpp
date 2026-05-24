// src/main.cpp
// SPDX-License-Identifier: Apache-2.0
// Copyright 2026 Magpiny

#include <boost/math/constants/constants.hpp>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/interpolators/pchip.hpp>
#include <boost/math/statistics/univariate_statistics.hpp>

#include <print> // C++23
#include <vector>

int main() {
  // Constants
  using boost::math::constants::pi;
  std::println("pi = {:.15f}", pi<double>());

  // Statistics
  std::vector<double> data = {98.2, 97.8, 99.1, 98.5, 97.9,
                              98.8, 99.3, 98.1, 97.6, 99.0};

  namespace stats = boost::math::statistics;
  std::println("mean   = {:.4f}", stats::mean(data));
  std::println("stddev = {:.4f}", std::sqrt(stats::variance(data)));

  // PCHIP interpolation — smooth curves for Chartra
  std::vector<double> t = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> y = {100.0, 102.5, 101.8, 104.2, 103.7, 106.1};

  auto spline = boost::math::interpolators::pchip(std::move(t), std::move(y));

  std::println("\nInterpolated values:");
  for (double x = 0.0; x <= 5.0; x += 0.5) {
    std::println("  t={:.1f}  y={:.4f}", x, spline(x));
  }

  return 0;
}
