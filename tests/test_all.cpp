#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>

#include "AbstractClass.cpp"
#include "ConcreteClassX.cpp"
#include "ConcreteClassY.cpp"

class MockAbstract : public AbstractClass {
public:
  MOCK_METHOD(void, primitiveOperationA, (), (const, override));
  MOCK_METHOD(void, primitiveOperationB, (), (const, override));
};
using ::testing::AtLeast;

TEST (Abstract, Mock) {
  MockAbstract ma;
  EXPECT_CALL(ma, primitiveOperationA()).Times(AtLeast(1));
  ma.primitiveOperationA();
  EXPECT_CALL(ma, primitiveOperationB()).Times(AtLeast(1));
  ma.primitiveOperationB();
}

TEST (Concrete_class_X, test_cout) {
  ConcreteClassX mx;
  testing::internal::CaptureStdout();
  mx.primitiveOperationA();
  mx.primitiveOperationB();
  const std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "PrimitiveOperationA implementation from X\nPrimitiveOperationB implementation from X\n");
}

TEST (Concrete_class_Y, test_cout) {
  ConcreteClassY my;
  testing::internal::CaptureStdout();
  my.primitiveOperationA();
  my.primitiveOperationB();
  const std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "PrimitiveOperationA implementation from Y\nPrimitiveOperationB implementation from Y\n");
}
