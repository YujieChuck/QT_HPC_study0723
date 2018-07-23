/****************************************************************************
**
** Year    		: 2018/07/02
** Author  		: YujieChuck
** E-Mail  		: caeunion@163.com
** Description	: 该类由我本人创建，用于界面框架的测试；
** If you have any questions , please contact me
****************************************************************************/

/*******************************************************************************
Copyright(C):
FileName:qt_hpc_study.h
Description:用于调试功能代码
Author:yujie.li
Date:2018/06/22
Others:
Histroy:
*******************************************************************************/
#ifndef QT_HPC_STUDY_H
#define QT_HPC_STUDY_H

#include <inc/gui/gui.h>
#include <inc/unity/caeglobalfunction.h>
//#include <QMainWindow>
#include "ccenterwidget.h"
#include "inc/gui/mytitlebar.h"

class QT_HPC_study :public QMainWindow ,public caeglobalFunction
{
    Q_OBJECT

public:
    QT_HPC_study(QWidget *parent = 0);
    ~QT_HPC_study();

protected:
    /*****************************************************************************
    * @函数名称 : GuiPreFunction
    * @功能描述 : 初始化界面后，用于定制界面显示。例如Qlabel中文字的显示颜色，Qtable的显示效果等
    * @author : yujie.li
    * @date : 2018/06/24
    * @version : ver 1.0
    * @inparam :
    * @outparam :
    *****************************************************************************/
    void GuiPreFunction();                   //virtual function
    /*****************************************************************************
    * @函数名称 : InitialWindow
    * @功能描述 : 初始化界面的标题栏，并设置icon
    * @author : yujie.li
    * @date : 2018/06/29
    * @version : ver 1.0
    * @inparam :
    * @outparam :
    *****************************************************************************/
    void InitialWindow();
    /*****************************************************************************
    * @函数名称 : Downloadstlye
    * @功能描述 : 设置所有Widget的样式
    * @author : yujie.li
    * @date : 2018/06/29
    * @version : ver 1.0
    * @inparam :
    * @outparam :
    *****************************************************************************/
    void Downloadstlye();
    /*****************************************************************************
    * @函数名称 : ReadGuiDataFile
    * @功能描述 : 将配置文件中记录的数据刷入界面中
    * @author : yujie.li
    * @date : 2018/06/24
    * @version : ver 1.0
    * @inparam :
    * @outparam :
    *****************************************************************************/
    void ReadGuiDataFile();
    /*****************************************************************************
    * @函数名称 : WriteGuiDataFile
    * @功能描述 : 将当前界面所有信息写入配置文件中
    * @author : yujie.li
    * @date : 2018/06/24
    * @version : ver 1.0
    * @inparam :
    * @outparam :
    *****************************************************************************/
    void WriteGuiDataFile();
    /*****************************************************************************
    * @函数名称 : InitialConnection
    * @功能描述 : 定义该界面所有信号与槽
    * @author : yujie.li
    * @date : 2018/06/24
    * @version : ver 1.0
    * @inparam :
    * @outparam :
    *****************************************************************************/
    void InitialConnection();
    /*****************************************************************************
    * @函数名称 : UpdateUserDefinedPara
    * @功能描述 : 用于将界面中某Widget与定义的变量进行映射
    * @author : yujie.li
    * @date : 2018/06/24
    * @version : ver 1.0
    * @inparam :
    * @outparam :
    *****************************************************************************/
    void UpdateUserDefinedPara(bool flag);   //virtual function

    void SplitGUIWindow();

private:
    void createMenuBar();
    void createToolBar();
    void createStatusBar();

private:


private slots:
    void onButtonMinClicked();
    void onButtonRestoreClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();


private:
    void resizeEvent(QResizeEvent *event);

private:
    QString M_MainPath;
    QString Gui_MainPath;

    QMenuBar* m_menuBar;
    CCenterWidget* CCenterWidget_Obj;

    MyTitleBar* m_titleBar;
};

#endif // QT_HPC_STUDY_H
