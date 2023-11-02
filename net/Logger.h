#pragma once
//{{{  includes
#include <string>
#include <mutex>
#include <thread>

#include <fstream>
#include <cstring>
#include <iostream>
#include <sstream>
//}}}

namespace xop {
  enum Priority { LOG_DEBUG, LOG_STATE, LOG_INFO, LOG_WARNING, LOG_ERROR, };

  class Logger {
  public:
    static Logger& Instance();

    Logger &operator = (const Logger&) = delete;
    Logger (const Logger&) = delete;
    ~Logger();

    void Init (char* pathname = nullptr);
    void Exit();

    void Log (Priority priority, const char* __file, const char* __func, int __line, const char* fmt, ...);
    void Log2 (Priority priority, const char* fmt, ...);

  private:
    void Write (std::string buf);
    Logger();

    std::mutex mutex_;
    std::ofstream ofs_;
    };
  }

#ifdef _DEBUG
  #define logDebug(fmt, ...) xop::Logger::Instance().Log (xop::LOG_DEBUG, __FILE__, __FUNCTION__,__LINE__, fmt, ##__VA_ARGS__)
#else
  #define logDebug(fmt, ...)
#endif

#define logInfo(fmt, ...) xop::Logger::Instance().Log2 (xop::LOG_INFO, fmt, ##__VA_ARGS__)
#define logError(fmt, ...) xop::Logger::Instance().Log (xop::LOG_ERROR, __FILE__, __FUNCTION__,__LINE__, fmt, ##__VA_ARGS__)
