#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>

#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/transform.h>
#include <thrust/functional.h>

enum Matrix_order
{
    Cols
}; 

class Matrix
{
public:
    // Constructors and desctructor (for Host and Device)
    Matrix(int m, int n, double val, std::string s = "none");
    Matrix(const Matrix& a);
    Matrix(Matrix&& a);
    ~Matrix();
    
    // Host methods
    std::string get_name() const;
    int get_rows() const;
    int get_cols() const; 
    Matrix& diagonalize();

    // Host operators
    const double& operator()(int m, int n) const;
    double& operator()(int m, int n);
    Matrix operator+(const Matrix& a) const;
    Matrix operator-(const Matrix& a) const;
    Matrix operator*(const Matrix& a) const;
    friend std::ostream& operator<< (std::ostream& os, const Matrix& A);

    // Device methods
    void load_to_device() const;
    void load_from_device();
    Matrix device_plus(const Matrix& a) const;
    Matrix device_minus(const Matrix& a) const;
    Matrix device_multiply(const Matrix& a) const;

private:
    // Members
    Matrix_order _order;
    int _rows;
    int _cols;
    std::string _name;
    thrust::host_vector<double>  _vals;
    // Device
    mutable thrust::device_vector<double> _dev_vals;

    // Methods    
    //int index(int m, int n) const;
};

#endif
