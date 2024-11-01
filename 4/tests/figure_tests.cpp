#include <gtest/gtest.h>
#include "../include/trapezoid.h"
#include "../include/rhombus.h"
#include "../include/pentagon.h"
#include "../include/array.h"
#include <sstream>

// Тесты для Trapezoid
TEST(TrapezoidTest, CenterCalculation) {
    Trapezoid<double> trapezoid;
    std::stringstream ss("0 0 4 0 3 2 1 2");  // Трапеция с основаниями 4 и 2
    ss >> trapezoid;
    
    auto center = trapezoid.getCenter();
    EXPECT_NEAR(center.x(), 2.0, 0.0001);
    EXPECT_NEAR(center.y(), 1.0, 0.0001);
}

TEST(TrapezoidTest, AreaCalculation) {
    Trapezoid<double> trapezoid;
    std::stringstream ss("0 0 4 0 3 2 1 2");
    ss >> trapezoid;
    
    double area = static_cast<double>(trapezoid);
    EXPECT_NEAR(area, 6.0, 0.0001);
}

TEST(TrapezoidTest, Equality) {
    Trapezoid<double> t1, t2;
    std::stringstream ss1("0 0 4 0 3 2 1 2");
    std::stringstream ss2("0 0 4 0 3 2 1 2");
    ss1 >> t1;
    ss2 >> t2;
    
    EXPECT_TRUE(t1 == t2);
}

// Тесты для Rhombus
TEST(RhombusTest, CenterCalculation) {
    Rhombus<double> rhombus;
    std::stringstream ss("0 0 2 2 0 4 -2 2");  // Ромб с диагоналями 4 и 4
    ss >> rhombus;
    
    auto center = rhombus.getCenter();
    EXPECT_NEAR(center.x(), 0.0, 0.0001);
    EXPECT_NEAR(center.y(), 2.0, 0.0001);
}

TEST(RhombusTest, AreaCalculation) {
    Rhombus<double> rhombus;
    std::stringstream ss("0 0 2 2 0 4 -2 2");
    ss >> rhombus;
    
    double area = static_cast<double>(rhombus);
    EXPECT_NEAR(area, 8.0, 0.0001);
}

TEST(RhombusTest, Equality) {
    Rhombus<double> r1, r2;
    std::stringstream ss1("0 0 2 2 0 4 -2 2");
    std::stringstream ss2("0 0 2 2 0 4 -2 2");
    ss1 >> r1;
    ss2 >> r2;
    
    EXPECT_TRUE(r1 == r2);
}

// Тесты для Pentagon
TEST(PentagonTest, CenterCalculation) {
    Pentagon<double> pentagon;
    std::stringstream ss("0 0 2 0 3 2 1 3 -1 2");
    ss >> pentagon;
    
    auto center = pentagon.getCenter();
    EXPECT_NEAR(center.x(), 1.0, 0.0001);
    EXPECT_NEAR(center.y(), 1.4, 0.0001);
}

TEST(PentagonTest, AreaCalculation) {
    Pentagon<double> pentagon;
    std::stringstream ss("0 0 2 0 3 2 1 3 -1 2");
    ss >> pentagon;
    
    double area = static_cast<double>(pentagon);
    EXPECT_NEAR(area, 8.0, 0.0001);
}

TEST(PentagonTest, Equality) {
    Pentagon<double> p1, p2;
    std::stringstream ss1("0 0 2 0 3 2 1 3 -1 2");
    std::stringstream ss2("0 0 2 0 3 2 1 3 -1 2");
    ss1 >> p1;
    ss2 >> p2;
    
    EXPECT_TRUE(p1 == p2);
}

// Тесты для операций копирования и перемещения (как в оригинальном файле)
TEST(OperationsTest, CopyAssignmentTrapezoid) {
    Trapezoid<double> t1;
    std::stringstream ss("0 0 4 0 3 2 1 2");
    ss >> t1;
    
    Trapezoid<double> t2;
    t2 = t1;
    EXPECT_TRUE(t1 == t2);
}

TEST(OperationsTest, MoveAssignmentTrapezoid) {
    Trapezoid<double> t1;
    std::stringstream ss("0 0 4 0 3 2 1 2");
    ss >> t1;
    
    Trapezoid<double> t2;
    t2 = std::move(t1);
    
    Trapezoid<double> expected;
    std::stringstream ss2("0 0 4 0 3 2 1 2");
    ss2 >> expected;
    EXPECT_TRUE(t2 == expected);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 