#include "matrix.hpp"

// Constructors and desctructor (for Host and Device)

 Matrix::Matrix(int m, int n, double val, std::string s) : _order(Matrix_order::Cols), _rows(m), _cols(n), _vals(m*n), _dev_vals(m, n), _name(s) 
{
    assert(_rows > 0 && _cols > 0);
    
    for(int in = 0; in < _cols; ++in)
        for(int im = 0; im < _rows; ++im)
            (*this)(im, in) = val;

    std::cout << "Constructor for " << _name << std::endl;
}

Matrix::Matrix(const Matrix& a) : _order(a._order), _rows(a._rows), _cols(a._cols), _vals(a._vals), _dev_vals(a._dev_vals), _name("copy of " + a._name) 
{
    std::cout << "Copy Constructor for " << _name << std::endl;
}

Matrix::Matrix(Matrix&& a) : _order(a._order), _rows(a._rows), _cols(a._cols), _vals(std::move(a._vals)), _dev_vals(std::move(a._dev_vals)), _name("moved " + a._name) 
{
    std::cout << "Move Constructor for " << _name << std::endl;
}

Matrix::~Matrix()
{
    std::cout << "Destructor for " << _name << std::endl;
}

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

    for(int m = 0; m < A._rows; ++m)
    {
        for(int n = 0; n < A._cols; ++n)
            os << A(m, n) << " ";

        os << std::endl;
    }

    return os;
}

// Device methods

void Matrix::load_to_device() const
{
    _dev_vals = _vals;
}

void Matrix::load_from_device()
{
    _vals = _dev_vals;
}

Matrix Matrix::device_plus(const Matrix& a) const
{
    Matrix b(_rows, _cols, 0, this->_name + "(device)+" + a._name);

    thrust::plus<double> op;
    thrust::transform(_dev_vals.begin(), _dev_vals.end(), a._dev_vals.begin(), b._dev_vals.begin(), op);
}

Matrix Matrix::device_minus(const Matrix& a) const
{
    Matrix b(_rows, _cols, 0, this->_name + "(device)-" + a._name);

    thrust::minus<double> op;
    thrust::transform(_dev_vals.begin(), _dev_vals.end(), a._dev_vals.begin(), b._dev_vals.begin(), op);
}