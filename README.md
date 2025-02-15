# LightLogger日志库特性说明及使用文档

## ✨ 核心特性

- **日志级别**
  - 支持：`DEBUG`、`INFO`、`WARN`、`ERROR`、`FATAL` 五个级别
  - 级别比较：使用整数比较（级别越高数值越大）
  - 级别过滤：支持设置全局日志级别

- **输出格式**
  - 📍 自动记录文件名和行号
  - 🎨 终端颜色支持（类Unix系统，使用ANSI转义码）
  - ✍️ printf风格格式化输出
  - 输出目标：标准错误输出(`std::cerr`)

- **工程特性**
  - 🔒 线程安全：通过互斥锁(`mutex`)实现
  - 📦 header-only：单头文件实现，无需编译

## 🚀 使用示例
- 直接将logger.hpp复制到你的include目录里
```cpp
#include "logger.hpp"
int main() {
    Logger::setLevel(INFO);  // 设置全局日志级别

    LOG_DEBUG("This debug message won't show");
    LOG_INFO("Program started");
    LOG_WARN("Memory usage: %d%%", 85);
    LOG_ERROR("File not found: %s", "data.txt");
    LOG_FATAL("Critical system failure!");

    return 0;
}
```

## 🖥️ 输出效果（终端带颜色）
[INFO] example.cpp:8 - Program started

[WARN] example.cpp:9 - Memory usage: 85%

[ERROR] example.cpp:10 - File not found: data.txt

[FATAL] example.cpp:11 - Critical system failure!

## ⚠️ 注意事项

- **平台兼容性**
  - 颜色支持依赖终端ANSI转义码（Linux/macOS默认支持）
  - Windows系统需要额外处理颜色显示（当前版本未实现）

- **使用规范**
  - 格式化字符串遵循C标准库printf规范
  - 日志级别比较使用整数比较机制
  - 所有日志通过std::cerr输出

- **性能建议**
  - 生产环境建议关闭DEBUG级别日志
  - 高频日志场景注意格式化字符串性能
