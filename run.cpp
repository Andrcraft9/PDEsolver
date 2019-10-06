#include "matrix.hpp"
#include <chrono>

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

    const int size_mat = 256;
    clock_t time_start, time_end;
    cout << "Matmul A and B:" << endl;
    Matrix devA(size_mat, size_mat, 2, "A");
    devA.load_to_device();
    cout << devA << endl;
    Matrix devB(size_mat, size_mat, 2, "B");
    devB.load_to_device();
    cout << devB << endl;
    
    time_start = clock();
    Matrix devC1(devA*devB);
    time_end = clock();
    cout << "cpu version: " << (time_end - time_start) / (double) CLOCKS_PER_SEC << endl;
    cout << devC1 << endl;

    time_start = clock();
    Matrix devC2(devA.device_multiply(devB));
    time_end = clock();
    cout << "gpu version: " << (time_end - time_start) / (double) CLOCKS_PER_SEC << endl;
    devC2.load_from_device();
    cout << devC2 << endl;
    
    return 0;
}
