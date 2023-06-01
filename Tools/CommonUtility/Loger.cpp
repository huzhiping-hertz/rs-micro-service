#include "Loger.h"
#include <stdlib.h>
#include <thread>
#include <stdio.h>
using namespace RS;

trantor::AsyncFileLogger Loger::fileLoger;

void Loger::InitLog(string logfile)
{
    fileLoger.setFileName(logfile);
    fileLoger.startLogging();

    trantor::Logger::setOutputFunction(
        [&](const char *msg, const uint64_t len)
        {
            fileLoger.output(msg, len);
            printf("%.*s",(int)len,msg);
        },
        [&]()
        { fileLoger.flush(); });

    fileLoger.setFileSizeLimit(1000000);
}