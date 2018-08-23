#include "ccenterwidget.h"

//Tab Widget
#include "Demo_MsgNotify/demo_msgnotify.h"
#include "drawprogressbar/drawprogressbar.h"
#include "NavListView/navlistview.h"
//qtpropertybrowser
#include "qtpropertybrowser.h"
#include "qtbuttonpropertybrowser.h"
#include "qteditorfactory.h"
#include "qtgroupboxpropertybrowser.h"
#include "qtpropertybrowserutils_p.h"
#include "qtpropertymanager.h"
#include "qttreepropertybrowser.h"
#include "qtvariantproperty.h"



//tab Json
#include "tab/json/cgeneratejson.h"

//tab thirft
//#include "tab/thirft/cmanegeservice.h"


CCenterWidget::CCenterWidget(QString GuiFile, QString MainPath): GUI(GuiFile,MainPath)
{
    GuiPreFunction();
    InitialConnection();
}

CCenterWidget::~CCenterWidget()
{

}

void CCenterWidget::GuiPreFunction()
{
    this->mainLayout->setColumnStretch(0,2);
    this->mainLayout->setColumnStretch(1,1);
    if(this->GuiGridLayout[1]!=NULL){
        this->GuiGridLayout[1]->setRowStretch(0,1);
        this->GuiGridLayout[1]->setRowStretch(1,20);
    }
    if(this->GuiGridLayout[4]!=NULL){
        this->GuiGridLayout[4]->setRowStretch(0,2);
        this->GuiGridLayout[4]->setRowStretch(1,1);
    }
    for(int i=0;i<500;i++){
        if(this->GuiPushButton[i]!=NULL){
            this->GuiPushButton[i]->setObjectName(QString("GuiPushButton%1").arg(i));
        }
    }

    //Intial tab widget
}

void CCenterWidget::InitialWindow()
{

}

void CCenterWidget::Downloadstlye()
{

}

void CCenterWidget::ReadGuiDataFile()
{
    ReadGuiPara(GetGuiDataPath() + "/" + GetGuiDataFile());
}

void CCenterWidget::WriteGuiDataFile()
{
    WriteGuiPara(GetGuiDataPath() + "/" + GetGuiDataFile());
}

void CCenterWidget::InitialConnection()
{
    //tab Widget
    if(this->GuiPushButton[10]!=NULL){
        QObject::connect(GuiPushButton[10], SIGNAL(clicked()),this,SLOT(ClickedButton_10()));
    }
    if(this->GuiPushButton[11]!=NULL){
        QObject::connect(GuiPushButton[11], SIGNAL(clicked()),this,SLOT(ClickedButton_11()));
    }
    if(this->GuiPushButton[12]!=NULL){
        QObject::connect(GuiPushButton[12], SIGNAL(clicked()),this,SLOT(ClickedButton_12()));
    }
    if(this->GuiPushButton[13]!=NULL){
        QObject::connect(GuiPushButton[13], SIGNAL(clicked()),this,SLOT(ClickedButton_13()));
    }


    //Json tab
    if(this->GuiPushButton[101]!=NULL){
        QObject::connect(GuiPushButton[101], SIGNAL(clicked()),this,SLOT(ClickedButton_101()));
    }
    if(this->GuiPushButton[102]!=NULL){
        QObject::connect(GuiPushButton[102], SIGNAL(clicked()),this,SLOT(ClickedButton_102()));
    }


    //thirft tab
    if(this->GuiPushButton[201]!=NULL){
        QObject::connect(GuiPushButton[201], SIGNAL(clicked()),this,SLOT(ClickedButton_ThirftClient_201()));
    }
    if(this->GuiPushButton[202]!=NULL){
        QObject::connect(GuiPushButton[202], SIGNAL(clicked()),this,SLOT(ClickedButton_ThirftServer_202()));
    }

}

void CCenterWidget::UpdateUserDefinedPara(bool flag)
{

}


void CCenterWidget::ShowMessage(const string &strMess)
{
    if(GuiTextEdit[1]!=NULL){
        GuiTextEdit[1]->setText(QString::fromStdString(strMess));
    }
}

void CCenterWidget::ClickedButton_10()
{
    Demo_MsgNotify* Demo_MsgNotify_obj = new Demo_MsgNotify(this->GetMainpath(),"News","You win 800 million dollars.",0);
    Demo_MsgNotify_obj->setCycleNum(3);
    Demo_MsgNotify_obj->ShowMessages();
}

void CCenterWidget::ClickedButton_11()
{
    QDialog* dialg = new QDialog();
    dialg->setWindowTitle("DrawProgress Bar Test");
    DrawProgressBar *Dpb = new DrawProgressBar(dialg);
    dialg->setMinimumSize(800,600);
    dialg->show();
    Dpb->setValue (1);

    QTime t;
    t.start();
    while(t.elapsed()<=9000){
        QCoreApplication::processEvents();
        for(int i=0;i<4;i++){
            if(t.elapsed()>2000*(i+1)){
                Dpb->setValue (i+2);
            }
        }
    }
}

void CCenterWidget::ClickedButton_12()
{
    QDialog* dialg = new QDialog();
    dialg->setWindowTitle("DrawProgress Bar Test");
    NavListView *listView2 = new NavListView(dialg);
    dialg->setMinimumSize(800,600);
    dialg->show();

    listView2->setIcoColorBg(false);
    listView2->setColorLine(QColor(32, 53, 74));
    listView2->setColorBg(QColor(52, 73, 94), QColor(24, 189, 155), QColor(24, 189, 155, 150));
    listView2->setColorText(QColor(254, 255, 255), QColor(252, 252, 252), QColor(0, 0, 0));

    listView2->setInfoVisible(false);

    listView2->setLineVisible(false);
    listView2->setIcoStyle(NavListView::IcoStyle_Triangle);

    listView2->readData(GetMainpath() + "/ConfigurationFolder/images/LQRes/image/config/config.xml");

    listView2->setMinimumHeight(800);
    //listView2->readData("D:/QT_study/Cplus_study/QT_HPC_study/QT_HPC_study/ConfigurationFolder/images/LQRes/image/config/config.xml");
}

void CCenterWidget::ClickedButton_13()
{
    ////////*********************object*********************////////
    /// help detail _QDialog
    ///http://docs.huihoo.com/qt/solutions/4/qtpropertybrowser/
    ///
    ///
    QDialog* _QDialog = new QDialog();


    QWidget* _QWidget = new QWidget();
    QtTreePropertyBrowser* m_TreeWidget = new QtTreePropertyBrowser(_QWidget);
    QtVariantPropertyManager* m_pVarManager;
    m_pVarManager =new QtVariantPropertyManager(m_TreeWidget);
    QtVariantProperty *item =m_pVarManager->addProperty(QVariant::Int, QStringLiteral("Int Data:"));
    item->setValue(101);
    m_TreeWidget->addProperty(item);
    m_property_dic[item] =QStringLiteral("Int Data:");

    item =m_pVarManager->addProperty(QVariant::Bool, QStringLiteral("Bool Data:"));
    item->setValue(true);
    m_TreeWidget->addProperty(item);
    m_property_dic[item] =QStringLiteral("Bool Data:");

    item =m_pVarManager->addProperty(QVariant::Double, QStringLiteral("Float Data:"));
    item->setValue(3.1415926);
    //If want to know more details ,you could look follow web site
    //http://docs.huihoo.com/qt/solutions/4/qtpropertybrowser/qtvariantpropertymanager.html#attributeType
    item->setAttribute("decimals",5);
    item->setAttribute("minimum",1.0);
    item->setAttribute("maximum",5.0);
    item->setAttribute("singleStep",0.5);
    //item->setWhatsThis("Info");
//    item->setEnabled(false);    //For control whether it could be edited
//    item->setModified(false);
//    item->setStatusTip("Info");
    item->setToolTip("Info");   //For control the value tip
    m_TreeWidget->addProperty(item);
    m_property_dic[item] =QStringLiteral("Float Data:");
    QtVariantProperty* item02 =m_pVarManager->addProperty(QVariant::Double, QStringLiteral("Float Data02:"));
    item->addSubProperty(item02);   //For control the sub property



    QtVariantProperty *item03 = m_pVarManager->addProperty(QtVariantPropertyManager::enumTypeId(), QStringLiteral("direction:"));
    QStringList enumNames;
    enumNames << "Up" << "Right" << "Down" << "Left";
    //QMap<int, QIcon> enumIcons;
    QtIconMap enumIcons;
    //QtVariantPropertyManager::iconMapTypeId()
    enumIcons[0] = QIcon(":/demo/images/up.png");
    enumIcons[1] = QIcon("D:/QT_study/Cplus_study/QT_HPC_study/QT_HPC_study/ConfigurationFolder/images/blue_right.png");
    enumIcons[2] = QIcon(":/demo/images/down.png");
    enumIcons[3] = QIcon(":/demo/images/left.png");
    //item03->setAttribute();
    item03->setAttribute("enumNames",enumNames);
    m_pVarManager->setAttribute(item03,"enumIcons",enumIcons[1]);
    //item03->setAttribute("enumIcons",enumIcons);
    item03->setValue(2);
    m_TreeWidget->addProperty(item03);



    item =m_pVarManager->addProperty(QVariant::String, QStringLiteral("String Data:"));
    m_TreeWidget->addProperty(item);
    item->setValue(QStringLiteral("Yujie.Li"));
    QGridLayout* m_QGridLayout = new QGridLayout(_QDialog);
    m_property_dic[item] =QStringLiteral("String Data:");

    m_QGridLayout->addWidget(_QWidget,0,0,1,1);
    ////////*********************object*********************////////


    ////////*********************object*********************////////
    QWidget* _QWidget02 = new QWidget();
    QtTreePropertyBrowser* m_TreeWidget02 = new QtTreePropertyBrowser(_QWidget02);
    QtVariantPropertyManager* m_pVarManager02;
    m_pVarManager02 =new QtVariantPropertyManager(m_TreeWidget02);
    QtProperty *groupItem = m_pVarManager02->addProperty(QtVariantPropertyManager::groupTypeId(),QStringLiteral("Group1"));
    item =m_pVarManager02->addProperty(QVariant::Int, QStringLiteral("Int Data:"));
    item->setValue(101);
    groupItem->addSubProperty(item);
    item =m_pVarManager02->addProperty(QVariant::Bool, QStringLiteral("Bool Data:"));
    item->setValue(true);
    groupItem->addSubProperty(item);
    item =m_pVarManager02->addProperty(QVariant::Double, QStringLiteral("Float Data:"));
    item->setValue(3.1415926);
    groupItem->addSubProperty(item);
    item =m_pVarManager02->addProperty(QVariant::String, QStringLiteral("String Data:"));
    groupItem->addSubProperty(item);
    item->setValue(QStringLiteral("Yujie.Li"));
    m_TreeWidget02->addProperty(groupItem);

    m_QGridLayout->addWidget(_QWidget02,0,1,1,1);
    ////////*********************object*********************////////


    ////////*********************object*********************////////
    //For Modify Value
    QtVariantEditorFactory* m_pVarFactory = new QtVariantEditorFactory(m_TreeWidget);
    m_TreeWidget->setFactoryForManager(m_pVarManager,m_pVarFactory);

    QtVariantEditorFactory* m_pVarFactory02 = new QtVariantEditorFactory(m_TreeWidget02);
    m_TreeWidget02->setFactoryForManager(m_pVarManager02,m_pVarFactory02);

    //For Get value changed   //void valueChanged ( QtProperty * property, const QVariant & value )
    connect(m_pVarManager,&QtVariantPropertyManager::valueChanged,this,&CCenterWidget::variantPropertyValueChanged);
    ////////*********************object*********************////////



    _QDialog->show();
    _QDialog->setMinimumSize(600,600);


}

void CCenterWidget::variantPropertyValueChanged(QtProperty *property, const QVariant &value)
{
    QString s =m_property_dic[property];
    qDebug()<<s<<":"<<value;
}

void CCenterWidget::ClickedButton_101()
{
    CGenerateJson G_J;
    JSON::Object::Ptr J_O_P;
    string jsonString = "{ \"name\" : \"Yujie\",\"address\" : \"ShangHai\"}";
    G_J.ParseJson(jsonString,J_O_P);
    Dynamic::Var ret = J_O_P->get("name");
    if ( !ret.isEmpty() )
    {
        qDebug() << QString::fromStdString(ret.toString());
        ShowMessage("\"name\" :"+ret.toString());
    }
}

void CCenterWidget::ClickedButton_102()
{
    string strTemp;
    CGenerateJson G_J;
    G_J.testSetArrayElement(strTemp);

    qDebug() << QString::fromStdString(strTemp);
    ShowMessage(strTemp);
}

void CCenterWidget::ClickedButton_ThirftClient_201()
{

}

void CCenterWidget::ClickedButton_ThirftServer_202()
{
//    CManegeService _CManegeService;
//    _CManegeService.startService();

}





