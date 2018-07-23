#include "csvfileparse.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>


void CsvFileParse::parseCSV(const QString &fileName)
{
//    LX::Sheet sheet;

    int nameStartIndex = fileName.lastIndexOf('/') + 1;
    if(nameStartIndex < 1)
    {
        nameStartIndex = fileName.lastIndexOf('\\') + 1;
    }
    int nameEndIndex = fileName.lastIndexOf('.');
    sheet.name = fileName.mid(nameStartIndex, nameEndIndex - nameStartIndex);

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        sheet.data.clear();
        return;
        //return sheet;
    }

    QTextStream inStream(&file);

    for( QString lineStr; !inStream.atEnd(); )
    {
        lineStr = inStream.readLine();
        if(lineStr.isEmpty())
        {
            continue;
        }

        sheet.data.append(splitCSVLine(lineStr));
    }
    file.close();

    return;
}

QStringList CsvFileParse::splitCSVLine(const QString &lineStr)
{
    QStringList strList;
    QString str;

    int length = lineStr.length();
    int quoteCount = 0;
    int repeatQuoteCount = 0;

    for(int i = 0; i < length; ++i)
    {
        if(lineStr[i] != '\"')
        {
            repeatQuoteCount = 0;
            if(lineStr[i] != ',')
            {
                str.append(lineStr[i]);
            }
            else
            {
                if(quoteCount % 2)
                {
                    str.append(',');
                }
                else
                {
                    strList.append(str);
                    quoteCount = 0;
                    str.clear();
                }
            }
        }
        else
        {
            ++quoteCount;
            ++repeatQuoteCount;
            if(repeatQuoteCount == 4)
            {
                str.append('\"');
                repeatQuoteCount = 0;
                quoteCount -= 4;
            }
        }
    }
    strList.append(str);

    return qMove(strList);
}


bool CsvFileParse::generateCSV(const QString &fileName)
{
    QFile file(fileName);

    //Determine if the folder is present
    int FindPos1 = fileName.lastIndexOf("/");
    int FindPos2 = fileName.lastIndexOf("\\");
    int FindReal;
    FindReal = FindPos2;
    if(FindPos1>FindPos2){
        FindReal = FindPos1;
    }
    QString FilePath = fileName.left(FindReal);
    QDir dir(FilePath);
    if(!dir.exists()){
        bool ok = dir.mkpath(FilePath);//创建多级目录
        if(!ok){  //Add Message
            QMessageBox::information(NULL, "Create folder according to date", "Failed to generate folder which is "+FilePath+".", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return false;
        }
    }

    bool openOk = file.open(QIODevice::WriteOnly);
    if(!openOk)
    {
        QMessageBox::information(NULL, "Failed to write to the CSV file", "Failed to write to the CSV file which is "+fileName+".", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return false;
    }
    QTextStream outStream(&file);

    int strCount = sheet.data.count();
    for(int i = 0; i < strCount; ++i)
    {
        outStream << joinCSVStrs(sheet.data.at(i));
        outStream << "\r\n";   //\r\n for windows
    }
    file.close();

    return true;
}


QString CsvFileParse::joinCSVStrs(const QStringList &strList)
{
    QString lineStr;

    int strCount = strList.count();
    int lastStrIndex = strCount - 1;

    for(int k = 0; k < strCount; ++k)
    {
        QString tarStr;
        bool commaFlag = false;

        const QString& oriStr = strList.at(k);
        int length = oriStr.length();
        for(int i = 0; i < length; ++i)
        {
            if(oriStr[i] == ',')
            {
                tarStr.append(oriStr[i]);
                commaFlag = true;
            }
            else if(oriStr[i] == '\"')
            {
                tarStr.append("\"\"\"\"");
            }
            else
            {
                tarStr.append(oriStr[i]);
            }
        }
        if(commaFlag)
        {
            tarStr.push_front('\"');
            tarStr.push_back('\"');
        }
        if(k != lastStrIndex)
        {
            tarStr.append(',');
        }

        lineStr.append(tarStr);
    }

    return qMove(lineStr);
}

