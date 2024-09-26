cmake_minimum_required(VERSION 3.10)
project(ImageProcessingProject)

# 查找 OpenCV
find_package(OpenCV REQUIRED)

# 包含头文件
include_directories(${OpenCV_INCLUDE_DIRS} include)

# 源文件
set(SOURCES
    src/main.cpp
    src/ImageProcessor.cpp
    src/VideoCapture.cpp
)

# 创建可执行文件
add_executable(ImageProcessing ${SOURCES})

# 链接 OpenCV 库
target_link_libraries(ImageProcessing ${OpenCV_LIBS})
