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
#ifndef NOTIFYMANAGER_H
#define NOTIFYMANAGER_H

#include <QObject>
#include <QQueue>

#include "notify.h"
//#include "./lqformwidget_global.h"

//class LQFORMWIDGETSHARED_EXPORT NotifyManager : public QObject   //it is for dll
class NotifyManager : public QObject
{
    Q_OBJECT
public:
    explicit NotifyManager( QObject *parent = 0);

    void notify(const QString &title, const QString &body,
                const QString &icon, const QString url);
    void setMaxCount(int count);
    void setDisplayTime(int ms);
    void setCycleNum(const int & value);

private:
    class NotifyData {
    public:
        NotifyData(const QString &icon, const QString &title,
                   const QString &body, const QString url):
            icon(icon),
            title(title),
            body(body),
            url(url)
        {
        }

        QString icon;
        QString title;
        QString body;
        QString url;
    };

    void rearrange();
    void showNext();

    QQueue<NotifyData> dataQueue;
    QList<Notify*> notifyList;
    int maxCount;
    int displayTime;
    int m_cycleNum;
};

#endif // NOTIFYMANAGER_H
