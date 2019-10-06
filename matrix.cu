#include "matrix.hpp"

// Constructors and desctructor (for Host and Device)

 Matrix::Matrix(int m, int n, double val, std::string s) : _order(Matrix_order::Cols), _rows(m), _cols(n), _name(s), _vals(m*n), _dev_vals(m*n)
{
    assert(_rows > 0 && _cols > 0);
    
    for(int in = 0; in < _cols; ++in)
        for(int im = 0; im < _rows; ++im)
            (*this)(im, in) = val;

    std::cout << "Constructor for " << _name << std::endl;
}

Matrix::Matrix(const Matrix& a) : _order(a._order), _rows(a._rows), _cols(a._cols), _name("copy of " + a._name), _vals(a._vals), _dev_vals(a._dev_vals)
{
    std::cout << "Copy Constructor for " << _name << std::endl;
}

Matrix::Matrix(Matrix&& a) : _order(a._order), _rows(a._rows), _cols(a._cols), _name("moved " + a._name), _vals(std::move(a._vals)), _dev_vals(std::move(a._dev_vals))
{
    std::cout << "Move Constructor for " << _name << std::endl;
}

Matrix::~Matrix()
{
    std::cout << "Destructor for " << _name << std::endl;
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

    return b;
}

Matrix Matrix::device_minus(const Matrix& a) const
{
    Matrix b(_rows, _cols, 0, this->_name + "(device)-" + a._name);

    thrust::minus<double> op;
    thrust::transform(_dev_vals.begin(), _dev_vals.end(), a._dev_vals.begin(), b._dev_vals.begin(), op);

    return b;
}