#include "demo_msgnotify.h"
#include <QDir>

#include "msgNotify/notifymanager.h"

Demo_MsgNotify::Demo_MsgNotify(const QString &strMainPath,const QString &strTitle,const QString &msg,QWidget *parent)
    :QWidget(parent)
{
    //this->setWindowTitle(title);
    //Downloadstlye();
    m_mang = new NotifyManager(this);
    m_msg = msg;
    m_Title = strTitle;
    m_MainPath = strMainPath;

//    this->on_pushButton_clicked();
//    this->on_pushButton_clicked();
//    this->on_pushButton_clicked();
//    this->on_pushButton_clicked();
//    this->on_pushButton_clicked();
//    this->on_pushButton_clicked();

}

Demo_MsgNotify::~Demo_MsgNotify()
{
}

void Demo_MsgNotify::Downloadstlye()
{
//    QDir DDir;
//    //加载样式表
//    QFile file(m_MainPath+"/ConfigurationFolder/images/LQRes/message.css");
//    if (file.open(QFile::ReadOnly)){
//        QString styleSheet = this->styleSheet();
//        styleSheet += QLatin1String(file.readAll());
//        QString paletteColor = styleSheet.mid(20, 7);
//        this->setPalette(QPalette(QColor(paletteColor)));
//        this->setStyleSheet(styleSheet);   //qApp
//        file.close();
//    }
}

void Demo_MsgNotify::setCycleNum(const int &value)
{
    m_mang->setCycleNum(value);
}

void Demo_MsgNotify::ShowMessages()
{
    m_mang->notify(m_Title,m_msg,
                   m_MainPath+"/ConfigurationFolder/images/LQRes/image/message.png",
                   "https://test.com");
}
