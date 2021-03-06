#include <gtest/gtest.h>

#include <ATen/ATen.h>

using namespace at;
void TestSimpleCase(Type& T) {
  auto a = randn({2, 3, 4, 5}, T);
  ASSERT_TRUE(a.prod(-4).equal(a.prod(0)));
  ASSERT_TRUE(a.prod(3).equal(a.prod(-1)));
}

void TestExpressionSpecification(Type& T) {
  auto a = randn({2, 3, 4, 5}, T);
  ASSERT_TRUE(a.unsqueeze(-5).equal(a.unsqueeze(0)));
  ASSERT_TRUE(a.unsqueeze(4).equal(a.unsqueeze(-1)));

  // can unsqueeze scalar
  auto b = randn(1, T);
  b.unsafeGetTensorImpl()->maybe_zero_dim(true);
  ASSERT_TRUE(b.unsqueeze(0).equal(b.unsqueeze(-1)));
}

void TestEmptyTensor(Type& T) {
  auto a = randn(0, T);
  ASSERT_TRUE(a.prod(0).equal(at::ones({}, T)));
}

void TestScalarVs1Dim1Size(Type& T) {
  auto a = randn(1, T);
  ASSERT_TRUE(a.prod(0).equal(a.prod(-1)));
  a.unsafeGetTensorImpl()->maybe_zero_dim(true);
  ASSERT_EQ(a.dim(), 0);
  ASSERT_TRUE(a.prod(0).equal(a.prod(-1)));
}

TEST(TestWrapdim, TestWrapdim) {
  manual_seed(123);
  Type& T = CPU(kFloat);

  TestSimpleCase(T);
  TestEmptyTensor(T);
  TestScalarVs1Dim1Size(T);
  TestExpressionSpecification(T);
}
