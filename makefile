HOST_COMP = g++-6
DEVICE_COMP = nvcc
ARCH = sm_60
FLAGS = -std=c++14

gpu:
	$(DEVICE_COMP) $(FLAGS) -arch=$(ARCH) -o pde --compiler-bindir $(HOST_COMP) matrix.cu matrix.cpp matrix_matmul.cu run.cpp