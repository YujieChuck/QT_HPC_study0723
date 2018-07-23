/****************************************************************************
**
** Year    		: 2018/07/02
** Author  		: YujieChuck
** E-Mail  		: caeunion@163.com
** Description	: 该类由我本人创建，用于界面框架的测试；
** If you have any questions , please contact me
****************************************************************************/

#ifndef QT_HPC_STUDY_QDIALOG_H
#define QT_HPC_STUDY_QDIALOG_H

#include <inc/gui/gui.h>
#include <inc/unity/caeglobalfunction.h>
#include "ccenterwidget.h"
#include "inc/gui/mytitlebar.h"
#include <QDialog>
//#include "inc/gui/basewindow.h"
//#include <QMainWindow>

class QT_HPC_study_QDialog : public QDialog,public caeglobalFunction
{
    Q_OBJECT

public:
    QT_HPC_study_QDialog(QWidget *parent = 0);
    ~QT_HPC_study_QDialog();

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

public:
    void createMenuBar();
    void createToolBar();
    void createStatusBar();

private slots:
    void onButtonMinClicked();
    void onButtonRestoreClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();


private:
    void resizeEvent(QResizeEvent *event);

private:
    QGridLayout* m_MainGridLayout;

    QString M_MainPath;
    QString Gui_MainPath;
    CCenterWidget* CCenterWidget_Obj;


    MyTitleBar* m_titleBar;
    QMenuBar* m_menuBar;
    QToolBar *fileToolBar;
};

#endif // QT_HPC_STUDY_QDIALOG_H
