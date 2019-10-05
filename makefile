HOST_COMP = g++-8
DEVICE_COMP = nvcc
ARCH = sm_60
FLAGS = -std=c++14 -O0

cpu:
	$(CC) $(FLAGS) -o pde matrix.cpp run.cpp

gpu:
	$(GPU_COMP) $(FLAGS) -arch=$(ARCH) -o pde --compiler-bindir $(HOST_COMP) matrix.cpp matrix.cu run.cpp