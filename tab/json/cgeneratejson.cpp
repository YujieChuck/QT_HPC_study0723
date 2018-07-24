#include "cgeneratejson.h"
#include "Poco/File.h"
#include "Poco/Logger.h"
#include "Poco/FileStream.h"



CGenerateJson::CGenerateJson(QWidget *parent) : QWidget(parent)
{

}

int CGenerateJson::ParseJson(const std::string& jsonFile, JSON::Object::Ptr &jsonObj)
{
    int parserStatus=0;
    //此处判断是否是json还是其中的内容对象
    Poco::File jf(jsonFile);
    std::string jsonStr;
    size_t preIndex=jsonFile.find_first_of("{");
    size_t rearIndex=jsonFile.find_last_of("}");

    if (preIndex!=-1&&rearIndex!=-1)
    {
        jsonStr=jsonFile;
    }else
    {
        if (!jf.exists()){
            Poco::Logger::get("TraceLog").error("Cannot find the json.");
            parserStatus=-201;
//            exit(-1);
        }
        Poco::FileInputStream fis(jsonFile);
        std::ostringstream ostr;
        StreamCopier::copyStream(fis, ostr);
        jsonStr= ostr.str();
    }

    Poco::JSON::Parser sparser;
    Poco::Dynamic::Var result;
    try
    {
        result = sparser.parse(jsonStr);
    }
    catch (Poco::JSON::JSONException* jsone)
    {
        Poco::Logger::get("TraceLog").fatal(jsone->displayText());
//        exit(-1);
    }
    catch (Poco::Exception& e)
    {
        Poco::Logger::get("TraceLog").fatal(e.displayText());
        parserStatus=-203;
//        exit(-1);
    }

    if (result.type() == typeid(Poco::JSON::Object::Ptr))
    {
        jsonObj = result.extract<Poco::JSON::Object::Ptr>();
    }
    else
    {
        Poco::Logger::get("TraceLog").fatal("Error json format.");
        parserStatus=-202;
//        exit(-1);
    }

    return parserStatus;
}

int CGenerateJson::testSetArrayElement(std::string &strJson)
{
    std::string json = "[]";
    Parser parser;
    Var result = parser.parse(json);
    Poco::JSON::Array::Ptr array = result.extract<Poco::JSON::Array::Ptr>();

    Poco::Dynamic::Array dynArray = *array;
    assert(dynArray.size() == 0);

    // array[0] = 7
    array->set(0, 7);
    assert(array->size() == 1);
    assert(array->getElement<int>(0) == 7);

    dynArray = *array;
    assert(dynArray.size() == 1);
    assert(dynArray[0] == 7);

    // array[2] = "foo"
    array->set(2, std::string("foo"));
    assert(array->size() == 3);
    assert(array->getElement<int>(0) == 7);
    assert(array->isNull(1));
    assert(array->getElement<std::string>(2) == "foo");

    dynArray = *array;
    assert(dynArray.size() == 3);
    assert(dynArray[0] == 7);
    assert(dynArray[1].isEmpty());
    assert(dynArray[2] == "foo");

    // array[1] = 13
    array->set(1, 13);
    assert(array->size() == 3);
    assert(array->getElement<int>(0) == 7);
    assert(array->getElement<int>(1) == 13);
    assert(array->getElement<std::string>(2) == "foo");


    //Json object to string
    JSON::Object jsnObj;
    jsnObj.set("ArrayData",array);
    std::stringstream  jsnString;
    jsnObj.stringify(jsnString, 3);
    strJson = jsnString.str();

//#ifdef POCO_ENABLE_CPP11

//    dynArray = std::move(*array);
//    assert(dynArray.size() == 3);
//    assert(dynArray[0] == 7);
//    assert(dynArray[1] == 13);
//    assert(dynArray[2] == "foo");

//#endif // POCO_ENABLE_CPP11

//    dynArray.clear();
//    assert(dynArray.size() == 0);
    return 0;
}
