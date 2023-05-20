#include "LteCtl.h"
#include "DomainModel/LteDemodulation.h"

void LteCtl::GetFreqAnalysis(const HttpRequestPtr &req,std::function<void (const HttpResponsePtr &)> &&callback)
{
    LteDemodulation ltedemod;
    string params=ltedemod.getParams();

    Json::Value paramObj;
    JSONCPP_STRING err;
    const auto rawJsonLength = static_cast<int>(params.length());
    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(params.c_str(), params.c_str() + rawJsonLength, &paramObj,&err)) {
        paramObj["error"]="params template parse error";
    }

    auto resp = HttpResponse::newHttpJsonResponse(paramObj);
    callback(resp);

}

void LteCtl::FreqAnalysis(const HttpRequestPtr &req,std::function<void (const HttpResponsePtr &)> &&callback)
{
    
    auto paramObj = req->getJsonObject();

    Json::StreamWriterBuilder builder;
    const std::string paramStr= Json::writeString(builder, *paramObj);

    LteDemodulation ltedemod;
    string rs=ltedemod.run(paramStr);


    Json::Value rsObj;
    rsObj["result"] = rs;
    auto resp = HttpResponse::newHttpJsonResponse(rsObj);
    callback(resp);

}
