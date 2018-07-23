#ifndef CSVFILEPARSE_H
#define CSVFILEPARSE_H

//#include "csvread.h"
//using namespace LX;

#include <QString>
#include <QStringList>


namespace LX
{
    class Sheet
    {
        enum FieldType{STRING, INT, DOUBLE, BOOL};
    public:
        Sheet(){}
        Sheet(Sheet& rhs);
        Sheet &operator =(Sheet &rhs);
    public:
        QString name;
        QList<QStringList> data;
        QList<FieldType> fieldTypes;
    };
}

class CsvFileParse{

    public:
        CsvFileParse(){}
        CsvFileParse(CsvFileParse& rhs);
        CsvFileParse &operator =(CsvFileParse &rhs);

    public:
        LX::Sheet sheet;
        void parseCSV(const QString &fileName);
        QStringList splitCSVLine(const QString &lineStr);

    public:
        bool generateCSV(const QString &fileName);
        QString joinCSVStrs(const QStringList &strList);

};

#endif // CSVFILEPARSE_H
