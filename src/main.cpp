#include <iostream>
#include "FigureArray.h"
#include "rectangle.h"
#include "square.h"
#include "trapezoid.h"

int main() {
    FigureArray figures;

    try {
        Rectangle rect(0, 0, 4, 3);
        std::cout << "Adding a rectangle:\n";
        std::cout << rect << std::endl;
        figures.Add(rect.Clone());

        Square square(1, 1, 3, 3);
        std::cout << "Adding a square:\n";
        std::cout << square << std::endl;
        figures.Add(square.Clone());

        Trapezoid trapezoid(0, 0, 4, 0, 3, 2, 1, 2);
        std::cout << "Adding a trapezoid:\n";
        std::cout << trapezoid << std::endl;
        figures.Add(trapezoid.Clone());
    } catch (const std::exception& e) {
        std::cout << "Error creating figure: " << e.what() << std::endl;
    }

    std::cout << "\n=== List of all figures ===\n";
    for (size_t i = 0; i < figures.Size(); ++i) {
        Figure* fig = figures.Get(i);
        std::cout << "Figure #" << i + 1 << ":\n";
        std::cout << *fig << std::endl;
        auto center = fig->Center();
        std::cout << "Center: (" << center.first << ", " << center.second << ")\n";
        std::cout << "Area: " << static_cast<double>(*fig) << std::endl;
    }

    double totalArea = figures.TotalArea();
    std::cout << "\nTotal area of all figures: " << totalArea << std::endl;

    std::cout << "\nRemoving the second figure (Square)...\n";
    try {
        figures.Remove(1);
    } catch (const std::exception& e) {
        std::cout << "Error removing figure: " << e.what() << std::endl;
    }

    std::cout << "\n=== List of figures after removal ===\n";
    for (size_t i = 0; i < figures.Size(); ++i) {
        Figure* fig = figures.Get(i);
        std::cout << "Figure #" << i + 1 << ":\n";
        std::cout << *fig << std::endl;
        auto center = fig->Center();
        std::cout << "Center: (" << center.first << ", " << center.second << ")\n";
        std::cout << "Area: " << static_cast<double>(*fig) << std::endl;
    }

    totalArea = figures.TotalArea();
    std::cout << "\nTotal area after removal: " << totalArea << std::endl;

    return 0;
}
