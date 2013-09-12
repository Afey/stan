#include <gtest/gtest.h>
#include <stan/math/functions/ho.hpp>

TEST(StanMathFunctionsHo, Var) {
  std::vector<double> t(100);
  Eigen::Matrix<double,Eigen::Dynamic,1> x0(2);
  stan::agrad::var gamma;

  
  double dt = 0.1;
  for (int i = 0; i < 100; i++)
    t[i] = i*dt + dt;

  x0(0) = 1.0;
  x0(1) = 0.0;

  gamma = 0.15;

  Eigen::Matrix<stan::agrad::var,Eigen::Dynamic,Eigen::Dynamic> 
    xhat = stan::math::ho<stan::agrad::var>(t, x0, gamma);

  EXPECT_NEAR(0.995029, xhat(0,0).val(), 1e-6);
  EXPECT_NEAR(-0.0990884, xhat(0,1).val(), 1e-6);

  EXPECT_NEAR(-0.421907, xhat(99,0).val(), 1e-6);
  EXPECT_NEAR(0.246407, xhat(99,1).val(), 1e-6);
}

TEST(StanMathFunctionsHo, Double) {
  std::vector<double> t(100);
  Eigen::Matrix<double,Eigen::Dynamic,1> x0(2);
  double gamma;

  
  double dt = 0.1;
  for (int i = 0; i < 100; i++)
    t[i] = i*dt + dt;

  x0(0) = 1.0;
  x0(1) = 0.0;

  gamma = 0.15;

  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> 
    xhat = stan::math::ho<double>(t, x0, gamma);

  EXPECT_NEAR(0.995029, xhat(0,0), 1e-6);
  EXPECT_NEAR(-0.0990884, xhat(0,1), 1e-6);

  EXPECT_NEAR(-0.421907, xhat(99,0), 1e-6);
  EXPECT_NEAR(0.246407, xhat(99,1), 1e-6);
}
