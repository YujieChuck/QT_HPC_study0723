/****************************************************************************
**
** Year    		: 2018/07/02
** Author  		: YujieChuck
** E-Mail  		: caeunion@163.com
** Description	: 该类由我本人创建，运用类似MVP的模式，将界面、界面文件、界面数据进行了分离
**                该类实现解析csv文件，生成QT界面上的控件
** If you have any questions , please contact me
****************************************************************************/

/*******************************************************************************
Copyright(C):
FileName:gui.h
Description:用于基于csv文件生成界面的基类
Author:yujie.li
Date:2018/06/22
Others:
Histroy:
*******************************************************************************/
#ifndef GUI_H
#define GUI_H

#include <QDialog>
#include <QMainWindow>

//添加的头文件如下：
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <Qtgui>
#include <QRadioButton>
#include <QGroupBox>
#include <QTableView>
#include <QCheckBox>
#include <QComboBox>
#include <QSpacerItem>
#include <QTableWidget>
#include <QTextEdit>
#include <QPlainTextEdit>

#include <QFile>
#include "inc/gui/groupboxextend.h"

#include "inc/gui/basewindow.h"
#include "inc/gui/csvfileparse.h"
#include "inc/gui/csvfilewrite.h"
//#include <caeglobalfunction.h>
#include <vector>

#include "basewindow.h"


enum ETextOper{
    EWrite = 0,
    ERead
};

class GUI : public QDialog
{
    Q_OBJECT

public:
    GUI(QWidget *parent = 0);
    GUI(QString GuiFile,QString MainPath);
    ~GUI();
public:
    void CreatGuiThroughCsvFile(const QString &fileName);

protected:
    void GUILayoutFunc(QGridLayout *layoutObj, int num1);
    void GUILayoutFunc(QLayout *layoutObj,int num1);
    void GUILayoutFunc(GroupBoxExtend *GroupBoxEObj, int num1);
    void CreatSingleWidget(int intWidgetNum);

public:
    QGridLayout *mainLayout;
private:
    QString m_path;
    QString GuiFile;
    QString GuiFlag;
    QString Gui_DataPath,Gui_DataFile;
    CsvFileParse* GuiCsv;

public:
    /*****************************************************************************
    * @函数名称 : SetMainpath
    * @功能描述 : 用于设置生成界面文件的存放路径，（界面所有Widget的数值与显示分离）
    * @author : yujie.li
    * @date : 2018/06/25
    * @version : ver 1.0
    * @inparam :
    * @outparam :
    *****************************************************************************/
    void SetMainpath(const QString &fileName);

    /*****************************************************************************
    * @函数名称 : GetMainpath
    * @功能描述 : 获取生成界面文件的存放路径
    * @author : yujie.li
    * @date : 2018/06/25
    * @version : ver 1.0
    * @inparam :
    * @outparam :
    *****************************************************************************/
    QString GetMainpath();

    /*****************************************************************************
    * @函数名称 : SetGuiFile
    * @功能描述 : 用于设置生成界面文件的文件名，这里必须为CSV文件
    * @author : yujie.li
    * @date : 2018/06/25
    * @version : ver 1.0
    * @inparam :
    * @outparam :
    *****************************************************************************/
    void SetGuiFile(const QString &fileName);

    /*****************************************************************************
    * @函数名称 : GetGuiFile
    * @功能描述 :获取生成界面文件的文件名
    * @author : yujie.li
    * @date : 2018/06/25
    * @version : ver 1.0
    * @inparam :
    * @outparam :
    *****************************************************************************/
    QString GetGuiFile();

    /*****************************************************************************
    * @函数名称 : SetGuiDataPath
    * @功能描述 : 用于设置界面中所有Widget对应的数值存放路径，（界面所有Widget的数值与显示分离）
    * @author : yujie.li
    * @date : 2018/06/24
    * @version : ver 1.0
    * @inparam :
    * @outparam :
    *****************************************************************************/
    void SetGuiDataPath(const QString &qstrPath);

    /*****************************************************************************
    * @函数名称 : GetGuiDataPath
    * @功能描述 : 获取界面中所有Widget对应的数值存放路径
    * @author : yujie.li
    * @date : 2018/06/24
    * @version : ver 1.0
    * @inparam :
    * @outparam :
    *****************************************************************************/
    QString GetGuiDataPath();

    /*****************************************************************************
    * @函数名称 : SetGuiDataFile
    * @功能描述 : 用于设置界面中所有Widget对应的数值存放的文件，这里必须为CSV文件，（界面所有Widget的数值与显示分离）
    * @author : yujie.li
    * @date : 2018/06/24
    * @version : ver 1.0
    * @inparam :
    * @outparam :
    *****************************************************************************/
    void SetGuiDataFile(const QString &qstrGuiDataFile);

    /*****************************************************************************
    * @函数名称 : GetGuiDataFile
    * @功能描述 : 获取设置界面中所有Widget对应的数值存放的文件
    * @author : yujie.li
    * @date : 2018/06/25
    * @version : ver 1.0
    * @inparam :
    * @outparam :
    *****************************************************************************/
    QString GetGuiDataFile();



    QLabel *GuiLabel[500];
    QLineEdit *GuiLineEdit[500];
    QPushButton *GuiPushButton[500];
    QString *GuiPushButtonBatFile[500];
    QComboBox *GuiComboBox[500];
    CsvFileParse *GuiComboxCsv[500];
    QRadioButton *GuiRadioButton[500];
    QCheckBox *GuiCheckBox[500];
    QSpacerItem *GuiSpacerItem[500];
    QTableWidget *GuiTableWidget[500];
    CsvFileParse *GuiTableWidgetHeaderCsv[500];
    CsvFileParse *GuiTableWidgetDataCsv[500];
    QString *GuiUserDefined[500];
    QTextEdit *GuiTextEdit[500];
    QString *GuiTextEditDataFile[500];
    QTabWidget* GuiTab[500];
    QWidget* GuiTabChildWidget[500];


    QGroupBox *GuiGroup[500];
    GroupBoxExtend *GuiGroup_E[500];
    QGridLayout *GuiGridLayout[500];
    QLayout *GuiHBoxLayout[500];
    QLayout *GuiVBoxLayout[500];



    void DataFlagSave();
    QList<QStringList> GuiFunctionData;

    //read and write csv files in order to update GUI
    CsvFileWrite* WriteGUIData;
    void ReadGuiPara(const QString &fileName);
    void WriteGuiPara(const QString &fileName);
    void UpdataGuiPara(QList<QStringList> TwoA);

    //update Gui data and transfer data to model
    void SetGuiDatatoObject(QList<QStringList> *DataTransfer);
    virtual void SetRestGuiDatatoObject(QList<QStringList> *DataTransfer);

    void GetGuiDataFromObject(QList<QStringList> *DataTransfer);
    virtual void GetRestGuiDataFromObject(QList<QStringList> *DataTransfer);

    //Add orther initial function
    virtual void GuiPreFunction();
    virtual void UpdateUserDefinedPara(bool flag);
    virtual void SetConfigPath(QString Path);
    virtual QString GetConfigPath();
    virtual void ReadConfigFile();
    virtual void WriteConfigFile();

    //Upate table and Get cuurent table data
    void UpdataTableFromQList(QTableWidget *Tableobj, QList<QStringList> Data, int RowStart, int ColumStart);
    QList<QStringList> GetTableData(QTableWidget *Tableobj);
    void DeleSelectedInTable(QTableWidget *Tableobj, int RowStart, int ColumStart, int RowNum, int ColumNum);

private:

    /*****************************************************************************
    * @函数名称 : CreatCheckFunctionData
    * @功能描述 : 用于check配置文件中是否有遗漏的组件信息未存储，若存在，则自动添加上
    * @author : yujie.li
    * @date : 2018/06/22
    * @version : ver 1.0
    * @inparam : 组件编号：num1
    * @outparam :
    *****************************************************************************/
    void CreatCheckFunctionData(int num1);

    /*****************************************************************************
    * @函数名称 : UpdataTextEditData
    * @功能描述 : 根据文本文件中的数据，更新控件TextEdit中的值
    * @author : yujie.li
    * @date : 2018/07/07
    * @version : ver 1.0
    * @inparam : 组件编号：num1
    * @outparam :
    *****************************************************************************/
    void UpdataTextEditData(QTextEdit &TextEditObj,const QString & strFile,int intFlag);



private:
    QList<QStringList> GuiCheckFunctionData;
};

#endif // GUI_H
