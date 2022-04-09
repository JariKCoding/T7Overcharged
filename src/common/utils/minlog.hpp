#pragma once
#include <fstream>
#include <filesystem>
#include <iostream>

#ifndef MINLOG_OUT_FILE
#define MINLOG_OUT_FILE "MinLog.log"
#endif

#ifndef MINLOG_OUT_DIR
#define MINLOG_OUT_DIR  "logs"
#endif

class MinLog
{
private:
    std::ofstream OutputStream;
    bool _isOpen = false;

public:
    static MinLog& Instance()
    {
        static MinLog _instance = MinLog(MINLOG_OUT_FILE, MINLOG_OUT_DIR);
        return _instance;
    }

    MinLog() { }

    MinLog(const char* filename, const char* dir = "")
    {
        Open(filename, dir);
    }

    void Open(const char* filename, const char* dir = "")
    {
        if (_isOpen) return;
        std::filesystem::path const directory = std::filesystem::current_path() / dir;
        std::filesystem::create_directories(directory);
        MinLog::OutputStream = std::ofstream(directory / filename);
        _isOpen = true;
    }

    void Write(const char* value)
    {
        MinLog::OutputStream << value;
        std::cout << value;
    }

    void WriteLine(const char* value)
    {
        MinLog::OutputStream << value << std::endl;
        std::cout << value << std::endl;
    }

    void WriteDebug(const char* value)
    {
#ifdef DEBUG
        MinLog::OutputStream << value << std::endl;
        std::cout << value << std::endl;
#endif
    }
};
