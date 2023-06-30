#include "Loger.h"
#include <stdlib.h>
#include <thread>
#include <stdio.h>
#include <vector>

using namespace RS;

void Loger::InitLog(string logfile)
{
    std::vector<spdlog::sink_ptr> sinks;
    auto max_size = 1048576 * 5;
    auto max_files = 3;


    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);
    console_sink->set_pattern("[%Y-%m-%d %H:%M:%S %e] [thread %t] %v");
    sinks.push_back(console_sink);
    
    if (logfile.compare("") != 0)
    {
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/" + logfile, max_size, max_files);
        file_sink->set_level(spdlog::level::debug);
        file_sink->set_pattern("[%Y-%m-%d %H:%M:%S %e] [thread %t] %v");
        sinks.push_back(file_sink);
    }

    auto combined_logger = std::make_shared<spdlog::logger>("rslog", begin(sinks), end(sinks));
    combined_logger->set_level(spdlog::level::trace);
    spdlog::register_logger(combined_logger);
}