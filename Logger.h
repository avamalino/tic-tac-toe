#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

#include "imgui/imgui.h"

enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warning,
    Error
};

struct LogEntry {
    LogLevel level;
    std::string message;
    std::chrono::system_clock::time_point timestamp;
};

class Logger {
    public:
        static void Init(const std::string& filename);
        static void Shutdown();

        static void Log(LogLevel level, const std::string& message);
        static void Clear();
        static void CopyAllToClipboard();

        static void Trace(const std::string& message);
        static void Debug(const std::string& message);
        static void Info(const std::string& message);
        static void Warning(const std::string& message);
        static void Error(const std::string& message);

        static void DrawImGui();
        static void DrawFileConsole();
        static void SetConsoleLevel(LogLevel level);

    private:
        static std::vector<LogEntry> sEntries;
        static std::ofstream sFile;
        static LogLevel sConsoleLevel;
};