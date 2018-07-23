#ifndef DEMO_MSGNOTIFY_H
#define DEMO_MSGNOTIFY_H

#include <QWidget>
class NotifyManager;


class Demo_MsgNotify : public QWidget
{
    Q_OBJECT

public:
    explicit Demo_MsgNotify(const QString &strMainPath = "",const QString &strTitle = "",const QString &msg = "",QWidget *parent = 0);
    ~Demo_MsgNotify();

public:
    void ShowMessages();
    void Downloadstlye();
    void setCycleNum(const int & value);

private slots:


private:
    NotifyManager *m_mang;
    QString m_msg;
    QString m_MainPath;
    QString m_Title;
};

#endif // DEMO_MSGNOTIFY_H
