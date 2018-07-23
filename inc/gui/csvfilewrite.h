#ifndef CSVFILEWRITE_H
#define CSVFILEWRITE_H

#include <QString>
#include <QStringList>


namespace LW
{
    class Sheet2
    {
        enum FieldType{STRING, INT, DOUBLE, BOOL};
    public:
        Sheet2(){}
        Sheet2(Sheet2& rhs);
        Sheet2 &operator =(Sheet2 &rhs);
    public:
        QString name;
        QList<QStringList> data;
        QList<FieldType> fieldTypes;
    };
}

class CsvFileWrite{

    public:
        CsvFileWrite(){}
        CsvFileWrite(CsvFileWrite& rhs);
        CsvFileWrite &operator =(CsvFileWrite &rhs);

    public:
        LW::Sheet2 sheet;
    public:
        bool generateCSV(const QString &fileName);
        QString joinCSVStrs(const QStringList &strList);

};

#endif // CSVFILEPARSE_H

