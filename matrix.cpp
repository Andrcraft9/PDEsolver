#include "matrix.hpp"

// Host methods

std::string Matrix::get_name() const
{
    return _name;
}

int Matrix::get_rows() const 
{
    return _rows;
}

int Matrix::get_cols() const 
{
    return _cols;
}

Matrix& Matrix::diagonalize()
{
    for(int in = 0; in < _cols; ++in)
        for(int im = 0; im < _rows; ++im)
            if (in != im) (*this)(im, in) = 0.0;

    return *this;
}

// Host operators

const double& Matrix::operator()(int m, int n) const
{
    return _vals[m + n*_rows];
}

double& Matrix::operator()(int m, int n)
{
    return _vals[m + n*_rows];
}

Matrix Matrix::operator+(const Matrix& a) const
{
    assert(_cols == a._cols && _rows == a._rows);

    Matrix b(_rows, _cols, 0, this->_name + "+" + a._name);

    for(int in = 0; in < _cols; ++in)
        for(int im = 0; im < _rows; ++im)
            b(im, in) = (*this)(im, in) + a(im, in);

    return b;
}

Matrix Matrix::operator-(const Matrix& a) const
{
    assert(_cols == a._cols && _rows == a._rows);

    Matrix b(_rows, _cols, 0, this->_name + "-" + a._name); 

    for(int in = 0; in < _cols; ++in)
        for(int im = 0; im < _rows; ++im)
            b(im, in) = (*this)(im, in) - a(im, in);

    return b;
}

Matrix Matrix::operator*(const Matrix& a) const
{
    assert(_cols == a._cols && _rows == a._rows);

    Matrix b(_rows, _cols, 0, this->_name + "*" + a._name); 

    for(int in = 0; in < _cols; ++in)
    {
        for(int im = 0; im < _rows; ++im)
        {
            double s = 0;
            for(int k = 0; k < _rows; ++k)
                 s = s + (*this)(im, k) * a(k, in);

            b(im, in) = s;
        }
    }

    return b;
}

//int Matrix::index(int m, int n) const
//{
//    return m + n*_rows;
//}

std::ostream& operator<< (std::ostream& os, const Matrix& A) 
{
    os << "Matrix name is: " << A._name << std::endl;
    
    const int lim_size = 16;

    if (A._rows < lim_size && A._cols < lim_size)
        for(int m = 0; m < A._rows; ++m)
        {
            for(int n = 0; n < A._cols; ++n)
                os << A(m, n) << " ";

            os << std::endl;
        }
    else
    {
        for(int m = 0; m < lim_size; ++m)
        {
            for(int n = 0; n < lim_size; ++n)
                os << A(m, n) << " ";

            os << "..." << std::endl;
        }
        os << "..." << std::endl;
    }

    return os;
}