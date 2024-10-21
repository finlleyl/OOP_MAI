#include <gtest/gtest.h>
#include "rectangle.h"
#include "square.h"
#include "trapezoid.h"
#include "figurearray.h"
#include "point.h"
#include "concepts.h"

TEST(SquareTest, AreaCalculation) {
    Point<int> p1(0, 0);
    Point<int> p2(2, 2);
    Square<int> square(p1, p2);

    double area = static_cast<double>(square);

    EXPECT_DOUBLE_EQ(area, 4.0);
}

TEST(SquareTest, CenterCalculation) {
    Point<double> p1(1.0, 1.0);
    Point<double> p2(3.0, 3.0);
    Square<double> square(p1, p2);

    auto center = square.Center();

    EXPECT_EQ(center, std::make_pair(2.0, 2.0));
}

TEST(SquareTest, EqualityOperator) {
    Point<int> p1(0, 0);
    Point<int> p2(2, 2);
    Square<int> square1(p1, p2);
    Square<int> square2(p1, p2);

    EXPECT_TRUE(square1 == square2);
}

TEST(SquareTest, CloneMethod) {
    Point<double> p1(0.0, 0.0);
    Point<double> p2(2.0, 2.0);
    Square<double> square(p1, p2);

    std::unique_ptr<Figure<double>> clonedSquare(square.Clone());

    EXPECT_TRUE(square == *clonedSquare);
}

TEST(RectangleTest, AreaCalculation) {
    Point<double> p1(0.0, 0.0);
    Point<double> p2(5.0, 3.0);
    Rectangle<double> rect(p1, p2);

    double area = static_cast<double>(rect);

    EXPECT_DOUBLE_EQ(area, 15.0);
}

TEST(RectangleTest, CenterCalculation) {
    Point<int> p1(1, 1);
    Point<int> p2(5, 5);
    Rectangle<int> rect(p1, p2);

    auto center = rect.Center();

    EXPECT_EQ(center, std::make_pair(3, 3));
}

TEST(RectangleTest, EqualityOperator) {
    Point<double> p1(0.0, 0.0);
    Point<double> p2(4.0, 3.0);
    Rectangle<double> rect1(p1, p2);
    Rectangle<double> rect2(p1, p2);

    EXPECT_TRUE(rect1 == rect2);
}

TEST(RectangleTest, CloneMethod) {
    Point<int> p1(0, 0);
    Point<int> p2(4, 3);
    Rectangle<int> rect(p1, p2);

    std::unique_ptr<Figure<int>> clonedRect(rect.Clone());

    EXPECT_TRUE(rect == *clonedRect);
}

TEST(TrapezoidTest, AreaCalculation) {
    Point<int> p1(0, 0);
    Point<int> p2(6, 0);
    Point<int> p3(5, 3);
    Point<int> p4(1, 3);
    Trapezoid<int> trapezoid(p1, p2, p3, p4);

    double area = static_cast<double>(trapezoid);

    EXPECT_DOUBLE_EQ(area, 15.0);
}

TEST(TrapezoidTest, CenterCalculation) {
    Point<double> p1(1.0, 1.0);
    Point<double> p2(5.0, 1.0);
    Point<double> p3(4.0, 3.0);
    Point<double> p4(2.0, 3.0);
    Trapezoid<double> trapezoid(p1, p2, p3, p4);

    auto center = trapezoid.Center();

    EXPECT_EQ(center, std::make_pair(3.0, 2.0));
}

TEST(TrapezoidTest, EqualityOperator) {
    Point<int> p1(0, 0);
    Point<int> p2(4, 0);
    Point<int> p3(3, 2);
    Point<int> p4(1, 2);
    Trapezoid<int> trapezoid1(p1, p2, p3, p4);
    Trapezoid<int> trapezoid2(p1, p2, p3, p4);

    EXPECT_TRUE(trapezoid1 == trapezoid2);
}

TEST(TrapezoidTest, CloneMethod) {
    Point<double> p1(0.0, 0.0);
    Point<double> p2(4.0, 0.0);
    Point<double> p3(3.0, 2.0);
    Point<double> p4(1.0, 2.0);
    Trapezoid<double> trapezoid(p1, p2, p3, p4);

    std::unique_ptr<Figure<double>> clonedTrapezoid(trapezoid.Clone());

    EXPECT_TRUE(trapezoid == *clonedTrapezoid);
}

TEST(FigureArrayTest, AddAndSize) {
    FigureArray<double> figures;
    auto square = std::make_shared<Square<double>>(Point<double>(0.0, 0.0), Point<double>(2.0, 2.0));
    auto rect = std::make_shared<Rectangle<double>>(Point<double>(0.0, 0.0), Point<double>(4.0, 3.0));

    figures.add(square);
    figures.add(rect);

    EXPECT_EQ(figures.size(), 2);
}

TEST(FigureArrayTest, RemoveFigure) {
    FigureArray<int> figures;
    auto square = std::make_shared<Square<int>>(Point<int>(0, 0), Point<int>(2, 2));
    auto rect = std::make_shared<Rectangle<int>>(Point<int>(0, 0), Point<int>(4, 3));
    figures.add(square);
    figures.add(rect);

    figures.remove(0);

    EXPECT_TRUE(*figures[0] == *rect);
}

TEST(FigureArrayTest, TotalAreaCalculation) {
    FigureArray<double> figures;
    auto square = std::make_shared<Square<double>>(Point<double>(0.0, 0.0), Point<double>(2.0, 2.0)); // Area = 4
    auto rect = std::make_shared<Rectangle<double>>(Point<double>(0.0, 0.0), Point<double>(4.0, 3.0)); // Area = 12
    figures.add(square);
    figures.add(rect);

    double totalArea = figures.totalArea();

    EXPECT_DOUBLE_EQ(totalArea, 16.0);
}

TEST(FigureArrayTest, OperatorAccess) {
    FigureArray<int> figures;
    auto trapezoid = std::make_shared<Trapezoid<int>>(
        Point<int>(0, 0), Point<int>(4, 0), Point<int>(3, 2), Point<int>(1, 2));
    figures.add(trapezoid);

    auto retrievedFigure = figures[0];

    EXPECT_TRUE(*retrievedFigure == *trapezoid);
}

TEST(FigureArrayTest, OutOfRangeAccess) {
    FigureArray<double> figures;

    EXPECT_THROW(figures[0], std::out_of_range);
}

TEST(FigureArrayTest, RemoveOutOfRange) {
    FigureArray<int> figures;
    auto square = std::make_shared<Square<int>>(Point<int>(0, 0), Point<int>(2, 2));
    figures.add(square);

    EXPECT_THROW(figures.remove(1), std::out_of_range);
}