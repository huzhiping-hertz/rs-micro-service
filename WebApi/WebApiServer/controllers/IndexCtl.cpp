#include "IndexCtl.h"

void IndexCtl::GetInformation(const HttpRequestPtr &req,std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto para=req->getParameters();
    HttpViewData data;
    data.insert("title","RM WebApi Information");
    auto resp=HttpResponse::newHttpViewResponse("IndexView.csp",data);
    callback(resp);
}
