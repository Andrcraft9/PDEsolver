#include "matrix.hpp"

void separate()
{
    std::cout << "|------------------------------|" << std::endl;
    std::cout << std::endl;
}

int main()
{
    using namespace std;

    cout << "Construct matrix A:" << endl;
    Matrix A(4, 4, 2, "A");
    cout << A << endl;

    separate();

    cout << "Move A to C, show C:" << endl;
    Matrix C(move(A)); // Move semantica, C++11 feature
    // Now A is not exist!
    cout << C << endl;
    
    separate();

    cout << "Universe construction for B:" << endl;
    Matrix B{2, 2, 10, "B"}; // Universe constructor, C++11 feature
    cout << B << endl;

    separate();

    cout << "Construct X and Y:" << endl;
    Matrix X(2, 2, 1, "X"), Y(2, 2, 2, "Y");
    cout << X << Y;
    cout << "Multiple: Z = X * Y, show Z:" << endl;
    Matrix Z(X*Y);
    cout << Z << endl;

    separate();
    
    return 0;
}
