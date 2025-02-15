# LightLogger
轻量级的header-only日志库

特性说明：

    日志级别：支持DEBUG、INFO、WARN、ERROR、FATAL五个级别
    颜色输出：不同级别对应不同终端颜色（支持类Unix系统终端）
    位置信息：自动记录文件名和行号
    格式化输出：支持printf风格格式化
    线程安全：使用mutex保证多线程安全
    级别过滤：可设置全局日志级别
    header-only：单头文件实现，无需编译

使用示例：

#include "logger.hpp" //直接将logger.hpp复制到你的include目录里
int main() {
    Logger::setLevel(INFO);  // 设置日志级别
    LOG_DEBUG("This debug message won't show");
    LOG_INFO("Program started");
    LOG_WARN("Memory usage: %d%%", 85);
    LOG_ERROR("File not found: %s", "data.txt");
    LOG_FATAL("Critical system failure!");
    return 0;
}

输出效果（终端中显示颜色）：

[INFO] example.cpp:8 - Program started

[WARN] example.cpp:9 - Memory usage: 85%

[ERROR] example.cpp:10 - File not found: data.txt

[FATAL] example.cpp:11 - Critical system failure!

注意事项：

    颜色支持需要终端支持ANSI转义码（大多数Linux/macOS终端默认支持）
    Windows系统需要额外处理才能显示颜色（本实现未包含）
    日志级别比较使用整数比较，级别越高数值越大
    使用标准错误输出(std::cerr)进行日志记录
    格式化字符串遵循C标准库printf规范



