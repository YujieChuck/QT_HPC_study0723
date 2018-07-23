/****************************************************************************
**
** Year    		: 2018/07/02
** Author  		: YujieChuck
** E-Mail  		: caeunion@163.com
** Description	: 该类由我本人创建，该类的作用是封装一些界面中常用的功能；
**                该类封装了界面重用操作
** If you have any questions , please contact me
****************************************************************************/

#ifndef CAEGLOBALFUNCTION_H
#define CAEGLOBALFUNCTION_H
//#pragma once

#include <QDateTime>
#include <QTime>
#include <QDate>
#include <QString>
#include <qDebug>
#include <QDir>
#include <QMessageBox>
//For Create Process
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
//#include <QtCore/QCoreApplication>
//#include <QtCore/QProcess>
//#include <QtCore/QStringList>

//For Browse File
#include <QApplication>
#include <QFileDialog>

#include <stdlib.h>

//For Replace Function
#include "math.h"
#include "iostream"
#include "string"
#include <locale.h>
#include "fstream"

//Configuration file function
#include <QStringList>
#include <QList>
#include <QString>
#include "inc/gui/csvfileparse.h"
#include "inc/gui/csvfilewrite.h"

//For regExp
#include <QRegExp>

using namespace std;

class caeglobalFunction
{
public:
    caeglobalFunction(){}

    QString stringtoQS(const string &s);
    string QStostring(const QString &s);

// 需包含locale、string头文件、使用setlocale函数。
    std::wstring StringToWstring(const std::string str);
    std::string WstringToString(const std::wstring str);

    bool StringReplaceStr(const char *filePath, string OldStr, string ReplaceStr);
//CAE模板用到的相关函数
    QString CreatTimeFolder(QString StrPath,QString PreFix);

//Creat Specified File
    bool CreatSpecifiedFile(QString FileName);
    QString CreatSpecificFolder(QString DirPath, QString DirName);
    //Delete specified path
    bool DeleteSpecificFolder(QString dirName);

//To replace file's CString from OldStr to ReplaceStr
    bool ReplaceFolderFile(QString FilePath, QString OldStr, QString ReplaceStr);
//To Run a Program
    QString RunAnsysProgram(QString ProgramPath, QString WorkPath, QString AnsysProgramName,bool Waitflag);

//Get disk free space
    quint64 GetDiskFreeSpace(QString driver);

//Browse file and return  file selected
    QString BrowseFile(QString Filter, QString DefaultDir,QString FirstMessage, QString FailMessage);

//Browse file and return  folder selected
    QString BrowseFolder(QString TitleInfo,QString NoticeInfo,QString DefaultDir);

//Get the correct path through the v150 file
    QString GetAnsysAimPath(QString PathV162);

//Get the correct path through the v150 file
    QString GetAnsysAPDLPath(QString PathVer);


    QList<QStringList> ReadConfigFile(const QString &fileName);

    QList<QStringList> ReadCSVFile(const QString &fileName);

    void WriteConfigFile(const QString &fileName,QList<QStringList> ConfigData);

    void WriteCSVFile(const QString &fileName,QList<QStringList> ConfigData);

//Rename creo model if its name begins with number.
    QString JudgeAndRenameCreoModel(const QString &fileName);

    bool PathMatchCheck(const QString &fileName);

//数据转置，针对只有一行的列表
    QList<QStringList> TransposeData(QList<QStringList> oldData);

//判断字符串是否链表里面
    bool QStringisexistinQStringList(QString name,QStringList list);

//Judge whether path or file exist
    bool PathAndFileExists(QString PathFile, int flag);


//Copy file or foler function
    std::wstring s2ws(const std::string& s);
    //LPCWSTR caeglobalFunction::QStringToLPCWSTR(QString orig);
    LPCWSTR QStringToLPCWSTR(QString orig);
    bool CopyPathOrFiletoDenspath(QString source ,QString Target, bool coverFileIfExist);
    void OpenPathOrFile(QString str);



//Initial program and Get MainPath
    QString InitializationProgram(QString m_configfolder, QString m_def, QString Program_def, QString JudgeFile);
    bool CopyDirFiletoSpecifiedcDir(QString origDir,QString destDir,QStringList filters);
};

#endif // CAEGLOBALFUNCTION_H
