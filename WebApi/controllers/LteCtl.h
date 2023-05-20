#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class LteCtl:public drogon::HttpController<LteCtl>
{
public:

    METHOD_LIST_BEGIN
    ADD_METHOD_TO(LteCtl::FreqAnalysis,"/api/lte/analysis",Post);
    ADD_METHOD_TO(LteCtl::GetFreqAnalysis,"/api/lte/analysis",Get);
    METHOD_LIST_END

    void FreqAnalysis(const HttpRequestPtr &req,std::function<void (const HttpResponsePtr &)> &&callback);
    void GetFreqAnalysis(const HttpRequestPtr &req,std::function<void (const HttpResponsePtr &)> &&callback);
};