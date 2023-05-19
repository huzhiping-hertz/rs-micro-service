#include "BaseTask.h"
using namespace RM;

BaseTask::BaseTask(string params,string taskName) :m_params(params), Task(taskName)
{
	
}
BaseTask::~BaseTask()
{
}


void BaseTask::runTask()
{

}

void BaseTask::cancel()
{
	Poco::Task::cancel();
}

string BaseTask::getParams()
{
	json paramObj;
	paramObj["version"]="v1.0";
	return paramObj.dump();
}
