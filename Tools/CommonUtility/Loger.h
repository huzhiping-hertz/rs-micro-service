#ifndef RSLOGER_H
#define RSLOGER_H

#include <iostream>
#include <string.h>
#include "spdlog/spdlog.h"
#include "fmt/format.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace RS
{

using namespace std;
#define __FILENAME__ (strrchr(__FILE__, _PATH_SPLITER_) ? strrchr(__FILE__, _PATH_SPLITER_) + 1 : __FILE__)
#define LOG_INFO (RS::Loger(__FILENAME__,__LINE__))
    class Loger
    {
    public:
        Loger(string fname,int line):m_fname(fname),m_line(line) {}
        Loger():m_fname(""),m_line(0) {}
    public:
        template<typename T>
        Loger& operator<<(const T& msg)
        {
            auto loger = spdlog::get("rslog");
            if (loger != nullptr)
            {
                SPDLOG_LOGGER_INFO(loger, fmt::format("[source {0}:{1}] {2}",this->m_fname,this->m_line,msg));
            }
            else
            {
                SPDLOG_INFO(msg);
            }
            return *this;
        }

    public:
        static void InitLog(string logfile);
    private:
        string m_fname;
        int m_line;
    };
}

#endif