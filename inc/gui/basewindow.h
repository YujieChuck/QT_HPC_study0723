/****************************************************************************
**
** Year    		: 2018/07/02
** User  		: YujieChuck
** E-Mail  		: caeunion@163.com
** Description	: 本控件来自与网络，本人收藏而来。
**                具体出处如下：
**                https://blog.csdn.net/GoForwardToStep/article/details/53494800
**                非常感谢############   前行中的小猪   ############的分享
**                该类实现标题栏定制化
** If you have any questions , please contact me
**
****************************************************************************/
#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QWidget>
#include <QDialog>
#include "inc/gui/mytitlebar.h"
#include <QMainWindow>

class BaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    BaseWindow(QWidget *parent = 0);
    ~BaseWindow();

private:
    void initTitleBar();

private slots:
    void onButtonMinClicked();
    void onButtonRestoreClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();

public:
    MyTitleBar* m_titleBar;

};

#endif // BASEWINDOW_H
