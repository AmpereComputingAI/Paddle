#!/bin/bash
mkdir build || true
cd build
rm -Rf *
cmake .. -DPY_VERSION=3.8 -DWITH_ARM=ON \
  	                  -DWITH_TESTING=OFF \
			  -DCMAKE_BUILD_TYPE=Release \
			  -DON_INFER=ON \
			  -DWITH_XBYAK=OFF \
			  -DWITH_CPU=OFF \
			  -DWITH_NCCL=OFF \
			  -DWITH_RCCL=OFF \
			  -DWITH_MKLDNN=ON \
			  -DWITH_MKL=OFF \
			  -DWITH_ONEMKL=OFF
make TARGET=ARMV8 -j32
make install
cd python
python setup.py install
