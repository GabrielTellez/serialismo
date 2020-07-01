SOURCE=serial-matrix.cpp
TARGET=serial-matrix
CPP= g++
$(TARGET): $(SOURCE)
	$(CPP) $(SOURCE) -o $(TARGET)

