#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <cassert>

#ifndef MATRIX_H
#define MATRIX_H
 
enum Matrix_order
{
    Cols
}; 

class Matrix
{
public:

    // Constructors

    Matrix(int m, int n, double val, std::string s = "none");
    Matrix(const Matrix& a);
    Matrix(Matrix&& a);
    
    // Destructors

    ~Matrix();
    
    // Public methods

    std::string get_name() const;
    int get_rows() const;
    int get_cols() const; 
    Matrix& diagonalize();
    
    // Operators

    const double& operator()(int m, int n) const;
    double& operator()(int m, int n);
    Matrix operator+(const Matrix& a) const;
    Matrix operator-(const Matrix& a) const;
    Matrix operator*(const Matrix& a) const;

    friend std::ostream& operator<< (std::ostream& os, const Matrix& A);

private:
    Matrix_order _order;
    int _rows;
    int _cols;
    std::unique_ptr<double[]> _vals; 
    std::string _name;

    // Private methods
    
    //int index(int m, int n) const;
};

#endif
