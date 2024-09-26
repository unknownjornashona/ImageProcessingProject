# 安装指南

该安装指南将指导您在本地环境中设置和配置视频监控与情报分析系统。

## 前提条件

在开始之前，请确保您的系统上安装了以下软件和工具：

- **C++编译器**：支持 C++11 或更高版本（如 GCC、Clang 或 MSVC）。
- **CMake**：用于项目构建工具。建议版本为 3.10 及以上。
- **OpenCV**：计算机视觉库，建议版本为 4.5 及以上。

## 安装步骤

### 1. 安装 C++ 编译器

如果您的系统尚未安装 C++ 编译器，请根据您所使用的操作系统进行安装：

- **Ubuntu / Debian**:

  ```bash
  sudo apt update
  sudo apt install build-essential
  ```

- **Fedora**:

  ```bash
  sudo dnf install gcc-c++ cmake
  ```

- **Windows**:

  请安装 [Visual Studio](https://visualstudio.microsoft.com/) 或 [MinGW](http://mingw.org/)。

### 2. 安装 CMake

- **Ubuntu / Debian**:

  ```bash
  sudo apt install cmake
  ```

- **Fedora**:

  ```bash
  sudo dnf install cmake
  ```

- **Windows**:

  下载 CMake 安装包并按照安装向导进行安装：[CMake 下载页面](https://cmake.org/download/)

### 3. 安装 OpenCV

- **Ubuntu / Debian**:

  ```bash
  sudo apt install libopencv-dev
  ```

- **Fedora**:

  ```bash
  sudo dnf install opencv-devel
  ```

- **Windows**:

  1. 下载 OpenCV 的预编译版本：[OpenCV 下载页面](https://opencv.org/releases/)
  2. 将 OpenCV 的安装路径添加到系统环境变量中。

### 4. 克隆项目

使用 Git 克隆本项目的代码库：

```bash
git clone https://github.com/yourusername/video-monitoring.git
cd video-monitoring
```

### 5. 创建构建目录

在项目根目录下创建一个 `build` 目录：

```bash
mkdir build
cd build
```

### 6. 配置项目

使用 CMake 配置项目：

```bash
cmake ..
```

如果您在步骤中遇到任何问题（例如无法找到 OpenCV），请确保 CMake 找到了正确的库路径，并检查是否在 `CMakeLists.txt` 中正确指定了 OpenCV 的路径。

### 7. 编译项目

运行以下命令编译项目：

```bash
make
```

### 8. 运行程序

在构建完成后，您可以运行程序：

```bash
./ImageProcessing ./captured_images 10
```

- `./captured_images` 是存储捕获图像和报告的目录，您可以自由更改为其他路径。
- `10` 是指需要捕获的图像帧数，可以根据实际需求进行调整。

## 许可证

该项目采用 MIT 许可证，详见 [LICENSE](LICENSE) 文件。

## 联系

如有问题或需要进一步的技术支持，请联系：

- 电子邮件: your-email@example.com
```

### 说明

- **前提条件**：列出了安装项目之前必须满足的条件。
- **安装步骤**：提供了详细的步骤，包括各种操作系统的特定说明，确保用户可以顺利安装。
- **克隆项目到运行程序**：逐步引导用户从获取源代码到运行项目的全过程。
- **许可证与联系方式**：提供必要的法律信息和联系信息，方便用户获取支持。