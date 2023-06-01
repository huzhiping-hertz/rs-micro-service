#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include "trantor/utils/Logger.h"
#include "trantor/utils/AsyncFileLogger.h"

namespace RS
{
    using namespace std;

    class Loger
    {
    private:
        Loger() {}

    private:
        static trantor::AsyncFileLogger fileLoger;
    public:
        static void InitLog(string logfile);
    };
}

#endif