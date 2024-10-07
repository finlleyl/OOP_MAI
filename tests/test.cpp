#include <gtest/gtest.h>
#include "rectangle.h"
#include "square.h"
#include "trapezoid.h"
#include "figurearray.h"

TEST(RectangleTest, Creation) {
    Rectangle rect(0, 0, 4, 3);

    EXPECT_EQ(rect.Center(), std::make_pair(2.0, 1.5));
    EXPECT_DOUBLE_EQ(static_cast<double>(rect), 12.0);
}

TEST(RectangleTest, Equality) {
    Rectangle rect1(0, 0, 4, 3);
    Rectangle rect2(0, 0, 4, 3);
    Rectangle rect3(1, 1, 5, 4);

    EXPECT_TRUE(rect1 == rect2);
    EXPECT_FALSE(rect1 == rect3);
}

TEST(SquareTest, Creation) {
    Square square(1, 1, 3, 3);

    EXPECT_EQ(square.Center(), std::make_pair(2.0, 2.0));
    EXPECT_DOUBLE_EQ(static_cast<double>(square), 4.0);
}

TEST(SquareTest, InvalidCreation) {
    EXPECT_THROW(Square square(0, 0, 4, 3), std::invalid_argument);
}

TEST(SquareTest, Equality) {
    Square square1(1, 1, 3, 3);
    Square square2(1, 1, 3, 3);
    Square square3(0, 0, 2, 2);

    EXPECT_TRUE(square1 == square2);
    EXPECT_FALSE(square1 == square3);
}

TEST(TrapezoidTest, Creation) {
    Trapezoid trapezoid(1, 1, 4, 7, 8, 7, 11, 1);

    EXPECT_EQ(trapezoid.Center(), std::make_pair(6.0, 4.0));
    EXPECT_DOUBLE_EQ(static_cast<double>(trapezoid), 42.0);
}

TEST(TrapezoidTest, InvalidCreation) {
    EXPECT_THROW(Trapezoid trapezoid(0, 0, 4, 0, 3, 3, 1, 3), std::invalid_argument);
}

TEST(TrapezoidTest, Equality) {
    Trapezoid trap1(1, 1, 4, 7, 8, 7, 11, 1);
    Trapezoid trap2(1, 1, 4, 7, 8, 7, 11, 1);
    Trapezoid trap3(1, 1, 4, 6, 8, 6, 11, 1);

    EXPECT_TRUE(trap1 == trap2);
    EXPECT_FALSE(trap1 == trap3);
}

TEST(FigureArrayTest, AddAndGetFigures) {
    FigureArray figures;
    Rectangle* rect = new Rectangle(0, 0, 4, 3);
    Square* square = new Square(1, 1, 3, 3);
    Trapezoid* trapezoid = new Trapezoid(1, 1, 4, 7, 8, 7, 11, 1);

    figures.Add(rect);
    figures.Add(square);
    figures.Add(trapezoid);

    EXPECT_EQ(figures.Size(), 3);
    EXPECT_EQ(figures.Get(0), rect);
    EXPECT_EQ(figures.Get(1), square);
    EXPECT_EQ(figures.Get(2), trapezoid);
}

TEST(FigureArrayTest, RemoveFigure) {
    FigureArray figures;
    figures.Add(new Rectangle(0, 0, 4, 3));
    figures.Add(new Square(1, 1, 3, 3));
    figures.Add(new Trapezoid(1, 1, 4, 7, 8, 7, 11, 1));

    figures.Remove(1);

    EXPECT_EQ(figures.Size(), 2);
    EXPECT_THROW(figures.Get(2), std::out_of_range);
}

TEST(FigureArrayTest, TotalArea) {
    FigureArray figures;
    figures.Add(new Rectangle(0, 0, 4, 3)); // Area = 12
    figures.Add(new Square(1, 1, 3, 3));    // Area = 4
    figures.Add(new Trapezoid(1, 1, 4, 7, 8, 7, 11, 1)); // Area = 8

    double totalArea = figures.TotalArea();

    EXPECT_DOUBLE_EQ(totalArea, 58.0);
}

TEST(FigureArrayTest, CloneFigures) {
    Rectangle rect(0, 0, 4, 3);
    Square square(1, 1, 3, 3);
    Trapezoid trapezoid(1, 1, 4, 7, 8, 7, 11, 1);

    Figure* rectClone = rect.Clone();
    Figure* squareClone = square.Clone();
    Figure* trapezoidClone = trapezoid.Clone();

    EXPECT_TRUE(rect == *rectClone);
    EXPECT_TRUE(square == *squareClone);
    EXPECT_TRUE(trapezoid == *trapezoidClone);

    delete rectClone;
    delete squareClone;
    delete trapezoidClone;
}

TEST(OperatorOverloadingTest, OutputStream) {
    Rectangle rect(0, 0, 4, 3);
    Square square(1, 1, 3, 3);
    Trapezoid trapezoid(1, 1, 4, 7, 8, 7, 11, 1);

    std::stringstream rectStream;
    std::stringstream squareStream;
    std::stringstream trapezoidStream;

    rectStream << rect;
    squareStream << square;
    trapezoidStream << trapezoid;

    EXPECT_NE(rectStream.str(), "");
    EXPECT_NE(squareStream.str(), "");
    EXPECT_NE(trapezoidStream.str(), "");
}

TEST(OperatorOverloadingTest, InputStream) {
    std::stringstream rectInput("0 0 4 3");
    std::stringstream squareInput("1 1 3 3");
    std::stringstream trapezoidInput("1 1 4 7 8 7 11 1");

    Rectangle rect(0, 0, 0, 0);
    Square square(0, 0, 0, 0);
    Trapezoid trapezoid(1, 1, 4, 7, 8, 7, 11, 1);

    rectInput >> rect;
    squareInput >> square;
    trapezoidInput >> trapezoid;

    EXPECT_EQ(rect.Center(), std::make_pair(2.0, 1.5));
    EXPECT_EQ(square.Center(), std::make_pair(2.0, 2.0));
    EXPECT_EQ(trapezoid.Center(), std::make_pair(6.0, 4.0));
}

TEST(FigureArrayTest, OutOfRangeAccess) {
    FigureArray figures;
    figures.Add(new Rectangle(0, 0, 4, 3));

    EXPECT_THROW(figures.Get(1), std::out_of_range);
    EXPECT_THROW(figures.Remove(1), std::out_of_range);
}

