#include "matrix.hpp"

int main()
{
    std::cout << "Construct matrix A ..." << std::endl;
    Matrix A(4, 4, 2, "A");
    std::cout << A;
    std::cout << std::endl;

    std::cout << "Move A to C ..." << std::endl;
    Matrix C(std::move(A)); // Move semantica, C++11 feature
    // Now A not exist... 
    std::cout << std::endl;

    std::cout << "Universe construction for B ..." << std::endl;
    Matrix B{2, 2, 10, "B"}; // Universe constructor, C++11 feature
    std::cout << B;
    std::cout << std::endl;

    std::cout << "Construct X and Y ..." << std::endl;
    Matrix X(2, 2, 1, "X"), Y(2, 2, 2, "Y");
    std::cout << X << Y;
    std::cout << "Multiple: Z = X * Y ..." << std::endl;
    Matrix Z(X*Y);
    std::cout << X << Y << Z;
    std::cout << std::endl;
    
    return 0;
}
