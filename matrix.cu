#include "matrix.hpp"

#define BLOCK_SIZE 16

// Device methods

// CUDA Kernel matvec
__host__ __device__ int iDivUp(int a, int b)
{ 
    return ((a % b) != 0) ? (a / b + 1) : (a / b);
}

__forceinline__ __device__ int dev_index(int m, int n, int rows, int cols) { return m + n*rows;}
{
    return 
}

__global__ void dev_matmul(double* a, double* b, double* c, int rows, int cols)
{
    int m = blockDim.x*blockIdx.x + threadIdx.x;
    int n = blockDim.y*blockIdx.y + threadIdx.y;
    int k = dev_index(m, n, rows, cols);

    double s = 0;
    for(int i = 0; i < rows; ++i)
    {
            int ka = dev_index(m, i, rows, cols);
            int kb = dev_index(i, n, rows, cols);
            s = s + a[ka] * b[kb];
    }

    c[k] = s;
}

Matrix Matrix::device_multiply(const Matrix& a) const
{
    Matrix b(_rows, _cols, 0, this->_name + "(device)*" + a._name);

    const double *raw_ptr_this = thrust::raw_pointer_cast(this->_dev_vals.data());
    const double *raw_ptr_a = thrust::raw_pointer_cast(a._dev_vals.data());
    double *raw_ptr_b = thrust::raw_pointer_cast(b._dev_vals.data());

    dim3 DimBlock(BLOCK_SIZE, BLOCK_SIZE);
    dim3 DimGrid(iDivUp(_rows, BLOCK_SIZE), iDivUp(_cols, BLOCK_SIZE));
    dev_matmul<<<DimBlock, DimGrid>>>(raw_ptr_this, raw_ptr_a, raw_ptr_b, _rows, _cols);
    
    //thrust::plus<double> op;
    //thrust::transform(_dev_vals.begin(), _dev_vals.end(), a._dev_vals.begin(), b._dev_vals.begin(), op);
}

