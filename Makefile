# 指定编译器
CXX = g++
CXXFLAGS = -std=c++17 -fPIC -Wall
LDFLAGS = -shared

# 动态库目标名称
TARGET = libUserInterface.so

# 源文件路径
SRC = code/UserInterface.cpp code/StorageLayer.cpp code/MemoryIndexLayer.cpp \
      code/ReadWriteBuffer.cpp 

# 包含头文件路径
INCLUDE = -I./code

# 生成动态库目标
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(INCLUDE) -o $(TARGET) $(LDFLAGS)

# 清理生成文件
clean:
	rm -f $(TARGET)
