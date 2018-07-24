#ifndef CGENERATEJSON_H
#define CGENERATEJSON_H

#include <QWidget>
#include<iostream>
#include <stdint.h>
#include <sstream>

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/JSONException.h"
#include "Poco/StreamCopier.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Query.h"
#include "Poco/JSON/PrintHandler.h"

using namespace Poco::Dynamic;
using namespace Poco;
using namespace Poco::JSON;
using std::string;



class CGenerateJson : public QWidget
{
    Q_OBJECT
public:
    explicit CGenerateJson(QWidget *parent = 0);

public:
    int ParseJson(const std::string &jsonFile, JSON::Object::Ptr &jsonObj);

    int testSetArrayElement(std::string &strJson);


signals:

public slots:
};

#endif // CGENERATEJSON_H
