// #include <iostream>
// #include <string>

// #include "CommonUtility/Loger.h"
// #include "DomainModel/TaskFactory.h"
// #include "Poco/Task.h"
// #include "Poco/TaskManager.h"
// #include "Poco/TaskNotification.h"
// #include "crow.h"
// #include "gflags\gflags.h"

// DEFINE_bool(log_debug, true, "log debug");

// using namespace RM;
// using namespace std;
// using namespace crow;
// using namespace gflags;

// int main(int argc, char** argv) {
//   gflags::ParseCommandLineFlags(&argc, &argv, true);

//   Loger::Init("core.log");
//   Loger::Trace(
//       "Log Trace write information in console window when log_debug equal "
//       "true");
//   Loger::Error("Log Error write information in log file..");
//   Loger::Trace("web api server start...");

//   SimpleApp app;
//   Poco::TaskManager pocoTM;

//   CROW_ROUTE(app, "/api/v1.0").methods("POST"_method)([&](const request& req) {
//     try {
//       Loger::Trace("##################asyncronize call start");
//       string params = req.body;
//       std::shared_ptr<BaseTask> taskPtr = TaskFactory::CreateTask(params);
//       pocoTM.start(taskPtr.get());
//       Loger::Trace("###################asyncronize call end");
//       return response(201);
//     } catch (std::exception& ex) {
//       Loger::Error(ex.what());
//       return crow::response{ex.what()};
//     }
//   });

//   app.bindaddr("127.0.0.1");
//   app.port(8011).multithreaded().run();
//   pocoTM.joinAll();
// }

#include <iostream>
#include <string>
#include "nlohmann/json.hpp"
#include "drogon/drogon.h"
#include "Poco/Task.h"
#include "Poco/TaskManager.h"
#include "Poco/TaskNotification.h"

using namespace drogon;
using namespace std;

int main(int argc, char **argv)
{
    LOG_INFO << "config file is web.json";
    app().loadConfigFile("./web.json").run();
    return 0;
}