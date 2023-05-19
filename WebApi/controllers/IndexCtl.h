#pragma once

#include <drogon/HttpController.h>

using namespace drogon;
class IndexCtl:public drogon::HttpController<IndexCtl>
{
public:

    METHOD_LIST_BEGIN
    ADD_METHOD_TO(IndexCtl::GetInformation,"/",Get);
    METHOD_LIST_END

    void GetInformation(const HttpRequestPtr &req,std::function<void (const HttpResponsePtr &)> &&callback);

};