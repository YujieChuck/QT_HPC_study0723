/****************************************************************************
**
** Year    		: 2018/07/05
** User  		: YujieChuck
** E-Mail  		: caeunion@163.com
** Description	: 本控件来自网络，本人收藏而来。
**                具体出处如下：
**                https://github.com/kevinlq/LQFramKit
**                非常感谢############   kevinlq   ############的分享
**                该类实现标题栏定制化
** If you have any questions , please contact me
**
****************************************************************************/
#ifndef NOTIFY_H
#define NOTIFY_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>

class Notify : public QWidget
{
    Q_OBJECT
public:
    explicit Notify(int displayTime, QWidget *parent = 0);

    void setIcon(const QString &value);

    void setTitle(const QString &value);

    void setBody(const QString &value);

    void setUrl(const QString &value);

    void showGriant();

    //Edit By Yujie in 05/07/2018
    void setCycleNum(int & value);

Q_SIGNALS:
    void disappeared();

private:

    int displayTime;

    QString icon;
    QString title;
    QString body;
    QString url;

    QLabel *backgroundLabel;
    QLabel *iconLabel;
    QLabel *titleLabel;
    QLabel *bodyLabel;

    QPushButton *closeBtn;

    void hideGriant();

    void mousePressEvent(QMouseEvent *event);

    //Edit By Yujie in 05/07/2018
    int m_Cycle;
    int m_CycleCount;
};

#endif // NOTIFY_H
