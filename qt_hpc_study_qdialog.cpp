#include "qt_hpc_study_qdialog.h"
//#include <QRect>

QT_HPC_study_QDialog::QT_HPC_study_QDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

    QDir DDir;
    QString qstrCurrentPath = DDir.currentPath();
    QString qstrMainPathFile = "ConfigurationFolder/StudyGUIMainPath.csv";
    QString qstrJudgeFile = "ConfigurationFolder/GUIData/TestOutputHeader.csv";
    QString qstrGuiFile = "ConfigurationFolder/StudyGUI.csv";
    Gui_MainPath = InitializationProgram(qstrCurrentPath,qstrMainPathFile,"QT HPC Study",qstrJudgeFile);

    CCenterWidget_Obj = new CCenterWidget(Gui_MainPath+"/"+qstrGuiFile,Gui_MainPath);
    CCenterWidget_Obj->SetGuiDataPath(Gui_MainPath);
    CCenterWidget_Obj->SetGuiDataFile("ConfigurationFolder/GUIData/StudyGUIData.csv");

    GuiPreFunction();
    InitialConnection();

    ReadGuiDataFile();

    //#########################Intial window#########################//
    Downloadstlye();
    InitialWindow();

    //m_MainGridLayout->addWidget(CCenterWidget_Obj,0,0,1,1);

    m_MainGridLayout = new QGridLayout(this);
    m_MainGridLayout->addWidget(CCenterWidget_Obj,0,0,1,1);
    //m_MainGridLayout->setMargin(36);
    //m_MainGridLayout->setContentsMargins(0,30+36,0,0);

//    m_MainGridLayout = new QVBoxLayout(this);
//    m_MainGridLayout->addWidget(CCenterWidget_Obj);
//    m_MainGridLayout->setMargin(36);


    //this->setWindowState(Qt::WindowMaximized);
}

QT_HPC_study_QDialog::~QT_HPC_study_QDialog()
{


}

void QT_HPC_study_QDialog::GuiPreFunction()
{

}

void QT_HPC_study_QDialog::InitialWindow()
{
    //******************************For Title******************************//
    m_titleBar = new MyTitleBar(this);
    m_titleBar->move(0, 0);

    connect(m_titleBar, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
    connect(m_titleBar, SIGNAL(signalButtonRestoreClicked()), this, SLOT(onButtonRestoreClicked()));
    connect(m_titleBar, SIGNAL(signalButtonMaxClicked()), this, SLOT(onButtonMaxClicked()));
    connect(m_titleBar, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));
    // 设置标题栏跑马灯效果，可以不设置;
    m_titleBar->setTitleRoll();
    m_titleBar->setTitleIcon(Gui_MainPath + "/ConfigurationFolder/images/Logo.png");
    m_titleBar->setTitleContent(QStringLiteral("    HPC Study based Qdialog v1.0  "));
    //m_titleBar->setButtonType(MIN_MAX_BUTTON);
    //m_titleBar->setTitleWidth(this->width());
    m_titleBar->setTitleWidth(650);
    m_titleBar->setBackgroundColor(0,0,20);
    //******************************For Title******************************//

     createMenuBar();
     createToolBar();

    //The follow code could update the image of pushbutton. So it shows that the css file could not load image normally.
//    m_titleBar->m_pButtonMin->setStyleSheet("border-image:url(D:/QT_study/Cplus_study/QT_HPC_study/QT_HPC_study/ConfigurationFolder/images/QSS/TitleQss/min.png) 0 81 0 0 ;");




}

void QT_HPC_study_QDialog::Downloadstlye()
{
    //加载样式表
    QFile file(Gui_MainPath + "/ConfigurationFolder/images/QSS/WidgetQss.css");
    QFile TitleCssfile(Gui_MainPath + "/ConfigurationFolder/images/QSS/TitleQss.css");
    if (file.open(QFile::ReadOnly)&&TitleCssfile.open(QFile::ReadOnly)){
        QString styleSheet = qApp->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        styleSheet += QLatin1String(TitleCssfile.readAll());
        QString paletteColor = styleSheet.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(styleSheet);   //qApp
        file.close();
    }
}

void QT_HPC_study_QDialog::ReadGuiDataFile()
{
    //ReadGuiPara(GetGuiDataPath() + "/" + GetGuiDataFile());
}

void QT_HPC_study_QDialog::WriteGuiDataFile()
{
    //WriteGuiPara(GetGuiDataPath() + "/" + GetGuiDataFile());
}

void QT_HPC_study_QDialog::InitialConnection()
{
//    if(GuiRadioButton[1]!=NULL) QObject::connect(GuiRadioButton[1], SIGNAL(clicked()),this,SLOT(Clicked_RadioRaceFlag()));
//    if(GuiRadioButton[2]!=NULL) QObject::connect(GuiRadioButton[2], SIGNAL(clicked()),this,SLOT(Clicked_RadioRaceFlag()));
//    createActions();
}

void QT_HPC_study_QDialog::UpdateUserDefinedPara(bool flag)
{
    //Initial the value of UserDefined
//    QString Temp_str;
//    if(flag){
//        if(GuiLineEdit[1]!=NULL) CreoModelFile = GuiLineEdit[1]->text();
//        if(GuiLineEdit[2]!=NULL) ScriptFile = GuiLineEdit[2]->text();
//        if(GuiLineEdit[3]!=NULL) Gui_WorkPath = GuiLineEdit[3]->text();
//    }
//    else{
//        if(GuiLineEdit[1]!=NULL) GuiLineEdit[1]->setText(CreoModelFile);
//        if(GuiLineEdit[2]!=NULL) GuiLineEdit[2]->setText(ScriptFile);
//        if(GuiLineEdit[3]!=NULL) GuiLineEdit[3]->setText(Gui_WorkPath);
    //    }
}

void QT_HPC_study_QDialog::createMenuBar()
{
    m_menuBar = new QMenuBar(this);
    QAction *action = new QAction(tr("action1"),this);
    QMenu* menu = m_menuBar->addMenu(tr("&File"));
    menu->addAction(action);
    action = new QAction(tr("action1"),this);
    menu = m_menuBar->addMenu(tr("&Edit"));
    menu->addAction(action);
    action = new QAction(tr("action1"),this);
    menu = m_menuBar->addMenu(tr("&Debug"));
    menu->addAction(action);
    action = new QAction(tr("action1"),this);
    menu = m_menuBar->addMenu(tr("&View"));
    menu->addAction(action);
    action = new QAction(tr("action1"),this);
    menu = m_menuBar->addMenu(tr("&Window"));
    menu->addAction(action);
    action = new QAction(tr("action1"),this);
    menu = m_menuBar->addMenu(tr("&Tools"));
    menu->addAction(action);
    action = new QAction(tr("action1"),this);
    menu = m_menuBar->addMenu(tr("&Help"));
    menu->addAction(action);
}

void QT_HPC_study_QDialog::createToolBar()
{
    //QToolBar *fileToolBar;
    QToolBar *editToolBar;

    fileToolBar = new QToolBar(this);
    editToolBar = new QToolBar(this);

    QAction *cut;
    cut = new QAction(tr("cut"),this);

    //fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(cut);

    cut = new QAction(tr("Copy"),this);
    fileToolBar->addAction(cut);
    //editToolBar = addToolBar(tr("Edit"));
    //editToolBar->addAction(cut);
//    editToolBar->addAction(cut);
//    editToolBar->addAction(cut);
    //fileToolBar->setContentsMargins(0,m_menuBar->height()+1,0,0);


//    fileToolBar->move(0,m_titleBar->height());
}

void QT_HPC_study_QDialog::onButtonMinClicked()
{
    if (Qt::Tool == (windowFlags() & Qt::Tool))
    {
        hide();    //设置了Qt::Tool 如果调用showMinimized()则窗口就销毁了？？？
    }
    else
    {
        showMinimized();
    }
}

void QT_HPC_study_QDialog::onButtonRestoreClicked()
{
    QPoint windowPos;
    QSize windowSize;
    m_titleBar->getRestoreInfo(windowPos, windowSize);
    this->setGeometry(QRect(windowPos, windowSize));
}

void QT_HPC_study_QDialog::onButtonMaxClicked()
{
    m_titleBar->saveRestoreInfo(this->pos(), QSize(this->width(), this->height()));
    QRect desktopRect = QApplication::desktop()->availableGeometry();
    QRect FactRect = QRect(desktopRect.x() - 3, desktopRect.y() - 3, desktopRect.width() + 6, desktopRect.height() + 6);
    setGeometry(FactRect);
}

void QT_HPC_study_QDialog::onButtonCloseClicked()
{
    close();
}

void QT_HPC_study_QDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    int mHeight = this->height();
    int mWidth = this->width();
    m_menuBar->setFixedWidth(mWidth);

    //Modify the postion of m_menuBar
    m_menuBar->move(0,m_titleBar->height());
    fileToolBar->move(0,m_titleBar->height()+m_menuBar->height());
    //m_menuBar->setContentsMargins(0,m_titleBar->height()+5,0,0);
    this->setContentsMargins(0,m_menuBar->height()+1,0,0);
}

