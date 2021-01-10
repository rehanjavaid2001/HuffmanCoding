#Rehan Javaid, rj3dxu, 11/12/2020, Makefile (encoder/decoder)

CXX = clang++
CXXFLAGS = -o
all: encoder decoder

encoder: huffmanenc.cpp heap.cpp
	$(CXX) $(CXXFLAGS) encoder huffmanenc.cpp heap.cpp

decoder: huffmandec.cpp
	$(CXX) $(CXXFLAGS) decoder huffmandec.cpp

