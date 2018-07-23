#include "gui.h"
//For Replace Function
#include "math.h"
#include "iostream"
#include "string"
#include <locale.h>
#include "fstream"
//For regExp
#include <QRegExp>

using namespace std;

GUI::GUI(QWidget *parent): QDialog(parent)
{
}

GUI::GUI(QString GuiFile, QString MainPath){
    SetMainpath(MainPath);
    SetGuiDataPath(MainPath);
    CreatGuiThroughCsvFile(GuiFile);

    //this->hide();
}

GUI::~GUI()
{

}

void GUI::CreatGuiThroughCsvFile(const QString &fileName){

    for(int i=0 ; i<500 ; i++){
        GuiLabel[i] = NULL;
        GuiLineEdit[i] = NULL;
        GuiPushButton[i] = NULL;
        GuiPushButtonBatFile[i] = NULL;
        GuiComboBox[i] = NULL;
        GuiComboxCsv[i] = NULL;
        GuiRadioButton[i] = NULL;
        GuiCheckBox[i] = NULL;
        GuiSpacerItem[i] = NULL;
        GuiTableWidget[i] = NULL;
        GuiTableWidgetHeaderCsv[i] = NULL;
        GuiTableWidgetDataCsv[i] = NULL;
        GuiUserDefined[i] = NULL;
        GuiGroup[i] = NULL;
        GuiGroup_E[i] = NULL;
        GuiGridLayout[i] = NULL;

        GuiTextEdit[i]=NULL;
        GuiTextEditDataFile[i]=NULL;

        GuiTab[i]=NULL;
        GuiTabChildWidget[i]=NULL;

        GuiHBoxLayout[i]=NULL;
        GuiVBoxLayout[i]=NULL;
    }


    mainLayout = new QGridLayout(this);
    mainLayout->setMargin(15);

    GuiCsv=new CsvFileParse;
    GuiCsv->parseCSV(fileName);

    int temp_Row,temp_column,temp_H_Size,temp_V_Size,temp_H_Start,temp_H_End;
    QString temp_str,temp_text;
    QStringList Tempstringlist;
    QString strTemp12;


    GuiFlag = GuiCsv->sheet.data[1][11];

    //int CountUserDefined = 0;
    //QString SStrA[100];

    QSizePolicy Qpolicy;
    int temp_flag,temp_child,temp_Expand;
    QString temp_parent;

    GuiCheckFunctionData.clear();
    for(int i=0;i<GuiCsv->sheet.data.size();i++){

        temp_str = GuiCsv->sheet.data[i][1];
        temp_H_Start = GuiCsv->sheet.data[i][12].toInt();
        temp_H_End = GuiCsv->sheet.data[i][13].toInt();
        temp_flag = GuiCsv->sheet.data[i][8].toInt();
        temp_child = GuiCsv->sheet.data[i][9].toInt();
        temp_parent = GuiCsv->sheet.data[i][10];
        temp_H_Size = GuiCsv->sheet.data[i][5].toInt();
        temp_V_Size = GuiCsv->sheet.data[i][6].toInt();
        temp_Row = GuiCsv->sheet.data[i][3].toInt();
        temp_column = GuiCsv->sheet.data[i][4].toInt();
        temp_Expand = GuiCsv->sheet.data[i][15].toInt();

        strTemp12 = GuiCsv->sheet.data[i][12];

        switch(temp_Expand){
            case 0:
                Qpolicy.setHorizontalPolicy(QSizePolicy::Expanding);
                Qpolicy.setVerticalPolicy(QSizePolicy::Maximum);
                break;
            case 1:
                Qpolicy.setHorizontalPolicy(QSizePolicy::Maximum);
                Qpolicy.setVerticalPolicy(QSizePolicy::Expanding);
                break;
            case 2:
                Qpolicy.setHorizontalPolicy(QSizePolicy::Expanding);
                Qpolicy.setVerticalPolicy(QSizePolicy::Expanding);
                break;
        }

        if(temp_str == "QGridLayout"){
            GuiGridLayout[temp_flag] = new QGridLayout;
            for(int j = temp_H_Start;j <= temp_H_End;j++){
                GUILayoutFunc(GuiGridLayout[temp_flag],j);
            }
        }
        else if(temp_str == "QGridLayout_M"){
            GuiGridLayout[temp_flag] = new QGridLayout;
            for(int j = temp_H_Start;j <= temp_H_End;j++){
                GUILayoutFunc(GuiGridLayout[temp_flag],j);
            }
            //GuiGridLayout[temp_flag]->set
            mainLayout->addLayout(GuiGridLayout[temp_flag],temp_Row,temp_column,temp_H_Size,temp_V_Size);
        }
        else if(temp_str == "QHBoxLayout"){
            GuiHBoxLayout[temp_flag] = new QHBoxLayout;     //QLayout   QHBoxLayout
            for(int j = temp_H_Start;j <= temp_H_End;j++){
                GUILayoutFunc(GuiHBoxLayout[temp_flag],j);
            }
        }
        else if(temp_str == "QHBoxLayout_M"){
            GuiHBoxLayout[temp_flag] = new QHBoxLayout; //QLayout   QHBoxLayout
            for(int j = temp_H_Start;j <= temp_H_End;j++){
                GUILayoutFunc(GuiHBoxLayout[temp_flag],j);
            }
            mainLayout->addLayout(GuiHBoxLayout[temp_flag],temp_Row,temp_column,temp_H_Size,temp_V_Size);
        }
        else if(temp_str == "QVBoxLayout"){
            GuiVBoxLayout[temp_flag] = new QVBoxLayout;     //QLayout   QHBoxLayout
            for(int j = temp_H_Start;j <= temp_H_End;j++){
                GUILayoutFunc(GuiVBoxLayout[temp_flag],j);
            }
        }
        else if(temp_str == "QVBoxLayout_M"){
            GuiVBoxLayout[temp_flag] = new QVBoxLayout; //QLayout   QHBoxLayout
            for(int j = temp_H_Start;j <= temp_H_End;j++){
                GUILayoutFunc(GuiVBoxLayout[temp_flag],j);
            }
            mainLayout->addLayout(GuiVBoxLayout[temp_flag],temp_Row,temp_column,temp_H_Size,temp_V_Size);
        }
        else if((temp_str == "QGroupBox")&&(temp_parent !="Sub")){
            GuiGroup[temp_flag] = new QGroupBox;
            GuiGroup[temp_flag]->setSizePolicy(Qpolicy);

            GuiGroup[temp_flag]->setTitle(GuiCsv->sheet.data[i][2]);
            GuiGroup[temp_flag]->setLayout(GuiGridLayout[temp_child]);
            mainLayout->addWidget(GuiGroup[temp_flag],temp_Row,temp_column,temp_H_Size,temp_V_Size);
        }
        else if((temp_str == "QGroupBox_E")){
            GuiGroup_E[temp_flag] = new GroupBoxExtend(("Advanced Setting"), this, GroupBoxExtend::STATE_NORMAL);
            GuiGroup_E[temp_flag]->setSizePolicy(Qpolicy);

            GuiGroup_E[temp_flag]->setTitle(GuiCsv->sheet.data[i][2]);
            GuiGroup_E[temp_flag]->setLayout(GuiGridLayout[temp_child]);

            for(int j = temp_H_Start;j <= temp_H_End;j++){
                GUILayoutFunc(GuiGroup_E[temp_flag],j);
            }

            mainLayout->addWidget(GuiGroup_E[temp_flag],temp_Row,temp_column,temp_H_Size,temp_V_Size);
        }
        else if((temp_str == "QTabWidget")&&(temp_parent !="Sub")){
            if(GuiTab[temp_flag]==NULL){
                GuiTab[temp_flag] = new QTabWidget;
            }
            GuiTab[temp_flag]->setSizePolicy(Qpolicy);

            GuiTabChildWidget[temp_child] = new QWidget();
            GuiTabChildWidget[temp_child]->setLayout(GuiGridLayout[temp_child]);

            GuiTab[temp_flag]->addTab(GuiTabChildWidget[temp_child],QIcon(m_path + "/" + strTemp12), GuiCsv->sheet.data[i][2]);
            mainLayout->addWidget(GuiTab[temp_flag],temp_Row,temp_column,temp_H_Size,temp_V_Size);
        }
        else if(temp_str == "UserDefined"){
            GuiUserDefined[temp_H_Start] = new QString("UserDefined" + QString::number(temp_H_Start,10));
        }

        //Add data into GuiCheckFunctionData
        CreatCheckFunctionData(i);
    }

    GuiPreFunction();
}

void GUI::GUILayoutFunc(QGridLayout *layoutObj,int num1){
    QString str = GuiCsv->sheet.data[num1][1];
    int Row = GuiCsv->sheet.data[num1][3].toInt();
    int column = GuiCsv->sheet.data[num1][4].toInt();
    int H_Size = GuiCsv->sheet.data[num1][5].toInt();
    int V_Size = GuiCsv->sheet.data[num1][6].toInt();
    int Para1 = GuiCsv->sheet.data[num1][12].toInt();
    int flag = GuiCsv->sheet.data[num1][8].toInt();
    QString str_10 = GuiCsv->sheet.data[num1][10];

    CreatSingleWidget(num1);

    if(str == "Qlabel"){
        layoutObj->addWidget(GuiLabel[Para1],Row,column,H_Size,V_Size);
    }
    else if(str == "QLineEdit"){
        layoutObj->addWidget(GuiLineEdit[Para1],Row,column,H_Size,V_Size);
    }
    else if(str == "QPushButton"){
        layoutObj->addWidget(GuiPushButton[Para1],Row,column,H_Size,V_Size);
    }
    else if(str == "QComboBox"){
        layoutObj->addWidget(GuiComboBox[Para1],Row,column,H_Size,V_Size);
    }
    else if(str == "QRadioButton"){
        layoutObj->addWidget(GuiRadioButton[Para1],Row,column,H_Size,V_Size);
    }
    else if(str == "QCheckBox"){
        layoutObj->addWidget(GuiCheckBox[Para1],Row,column,H_Size,V_Size);
    }
    else if(str == "QSpacerItem"){
        layoutObj->addItem(GuiSpacerItem[Para1],Row,column);
    }
    else if(str == "QTableWidget"){
        layoutObj->addWidget(GuiTableWidget[Para1],Row,column,H_Size,V_Size);
    }
    else if((str == "QGroupBox")&&(str_10 =="Sub")){
        layoutObj->addWidget(GuiGroup[flag],Row,column,H_Size,V_Size);
    }
    else if(str == "QHBoxLayout"){
        layoutObj->addLayout(GuiHBoxLayout[flag],Row,column,H_Size,V_Size);
    }
    else if(str == "GuiVBoxLayout"){
        layoutObj->addLayout(GuiVBoxLayout[flag],Row,column,H_Size,V_Size);
    }
    else if(str == "QGridLayout"){
        layoutObj->addLayout(GuiGridLayout[flag],Row,column,H_Size,V_Size);
    }
    else if(str == "QTextEdit"){
        layoutObj->addWidget(GuiTextEdit[Para1],Row,column,H_Size,V_Size);
    }
    else if((str == "QTabWidget")&&(str_10 =="Sub")){
        layoutObj->addWidget(GuiTab[flag],Row,column,H_Size,V_Size);
    }
    else{

    }

}

void GUI::GUILayoutFunc(QLayout *layoutObj, int num1)
{
    QString str = GuiCsv->sheet.data[num1][1];
    int Para1 = GuiCsv->sheet.data[num1][12].toInt();
    int flag = GuiCsv->sheet.data[num1][8].toInt();
    QString str_10 = GuiCsv->sheet.data[num1][10];

    CreatSingleWidget(num1);

    if(str == "Qlabel"){
        layoutObj->addWidget(GuiLabel[Para1]);
    }
    else if(str == "QLineEdit"){
        layoutObj->addWidget(GuiLineEdit[Para1]);
    }
    else if(str == "QPushButton"){
        layoutObj->addWidget(GuiPushButton[Para1]);
    }
    else if(str == "QComboBox"){
        layoutObj->addWidget(GuiComboBox[Para1]);
    }
    else if(str == "QRadioButton"){
        layoutObj->addWidget(GuiRadioButton[Para1]);
    }
    else if(str == "QCheckBox"){
        layoutObj->addWidget(GuiCheckBox[Para1]);
    }
    else if(str == "QSpacerItem"){
        //layoutObj->addStretch();
        layoutObj->addItem(GuiSpacerItem[Para1]);
    }
    else if(str == "QTableWidget"){
        layoutObj->addWidget(GuiTableWidget[Para1]);
    }
    else if((str == "QGroupBox")&&(str_10 =="Sub")){
        layoutObj->addWidget(GuiGroup[flag]);
    }
    else if(str == "QHBoxLayout"){
        //layoutObj->addLayout(GuiHBoxLayout[flag]);
        //layoutObj->addChildLayout(GuiHBoxLayout[flag]);
    }
    else if(str == "GuiVBoxLayout"){
        //layoutObj->addLayout(GuiVBoxLayout[flag]);
        //layoutObj->addChildLayout(GuiVBoxLayout[flag]);
    }
    else if(str == "QTextEdit"){
        layoutObj->addWidget(GuiTextEdit[Para1]);
    }
    else if((str == "QTabWidget")&&(str_10 =="Sub")){
        layoutObj->addWidget(GuiTab[flag]);
    }
    else{

    }
}

void GUI::GUILayoutFunc(GroupBoxExtend *GroupBoxEObj, int num1)
{
    QString str = GuiCsv->sheet.data[num1][1];
    int Para1 = GuiCsv->sheet.data[num1][12].toInt();
    int flag = GuiCsv->sheet.data[num1][8].toInt();
    QString str_10 = GuiCsv->sheet.data[num1][10];

    if(str == "Qlabel"){
        GroupBoxEObj->addWidget(GuiLabel[Para1]);
    }
    else if(str == "QLineEdit"){
        GroupBoxEObj->addWidget(GuiLineEdit[Para1]);
    }
    else if(str == "QPushButton"){
        GroupBoxEObj->addWidget(GuiPushButton[Para1]);
    }
    else if(str == "QComboBox"){
        GroupBoxEObj->addWidget(GuiComboBox[Para1]);
    }
    else if(str == "QRadioButton"){
        GroupBoxEObj->addWidget(GuiRadioButton[Para1]);
    }
    else if(str == "QCheckBox"){
        GroupBoxEObj->addWidget(GuiCheckBox[Para1]);
    }
    else if(str == "QTableWidget"){
        GroupBoxEObj->addWidget(GuiTableWidget[Para1]);
    }
    else if((str == "QGroupBox")&&(str_10 =="Sub")){
        GroupBoxEObj->addWidget(GuiGroup[flag]);
    }
    else if(str == "QTextEdit"){
        GroupBoxEObj->addWidget(GuiTextEdit[Para1]);
    }
    else if((str == "QTabWidget")&&(str_10 =="Sub")){
        GroupBoxEObj->addWidget(GuiTab[flag]);
    }
    else{

    }

}

void GUI::CreatSingleWidget(int intWidgetNum)
{
    QString str = GuiCsv->sheet.data[intWidgetNum][1];
    int Row = GuiCsv->sheet.data[intWidgetNum][3].toInt();
    int column = GuiCsv->sheet.data[intWidgetNum][4].toInt();
    int H_Size = GuiCsv->sheet.data[intWidgetNum][5].toInt();
    int V_Size = GuiCsv->sheet.data[intWidgetNum][6].toInt();
    int Para1 = GuiCsv->sheet.data[intWidgetNum][12].toInt();
    int Para2 = GuiCsv->sheet.data[intWidgetNum][13].toInt();
    //int Para3 = GuiCsv->sheet.data[intWidgetNum][14].toInt();
    int flag = GuiCsv->sheet.data[intWidgetNum][8].toInt();
    int child = GuiCsv->sheet.data[intWidgetNum][9].toInt();
    int Expand = GuiCsv->sheet.data[intWidgetNum][15].toInt();
    QStringList header;

    QSizePolicy Qpolicy;
    switch(Expand){
        case 0:
            Qpolicy.setHorizontalPolicy(QSizePolicy::Expanding);
            Qpolicy.setVerticalPolicy(QSizePolicy::Maximum);
            break;
        case 1:
            Qpolicy.setHorizontalPolicy(QSizePolicy::Maximum);
            Qpolicy.setVerticalPolicy(QSizePolicy::Expanding);
            break;
        case 2:
            Qpolicy.setHorizontalPolicy(QSizePolicy::Expanding);
            Qpolicy.setVerticalPolicy(QSizePolicy::Expanding);
            break;
    }


    QString str_7 = GuiCsv->sheet.data[intWidgetNum][7];
    QString str_8 = GuiCsv->sheet.data[intWidgetNum][8];
    QString str_9 = GuiCsv->sheet.data[intWidgetNum][9];
    QString str_10 = GuiCsv->sheet.data[intWidgetNum][10];
    QString str_12 = GuiCsv->sheet.data[intWidgetNum][12];
    QString str_14 = GuiCsv->sheet.data[intWidgetNum][14];

    QFile file(m_path + "/" + str_10);
    QFile file_14(m_path + "/" + str_14);

    if(str == "Qlabel"){
        GuiLabel[Para1] = new QLabel;
        GuiLabel[Para1]->setText(GuiCsv->sheet.data[intWidgetNum][2]);

        if(str_7 == "Picture"){
            if (file.exists()){
                GuiLabel[Para1]->setSizeIncrement(100,100);
                GuiLabel[Para1]->setPixmap(QPixmap(m_path + "/" + str_10));
                GuiLabel[Para1]->setScaledContents(true);    //而ui->label->setScaledContents(true);为设置QLabel自动缩放，既：显示图像大小自动调整为Qlabel大小。
                GuiLabel[Para1]->resize(6,6);
                //GuiLabel[Para1]->setSizePolicy(Qpolicy);
                GuiLabel[Para1]->show();
            }
            else{
                GuiLabel[Para1]->setText("There is no picture which is " + m_path + "/" + str_10);
            }
        }

        if(str_8 == "AlignRight"){
            if(str_9 == "AlignVCenter"){
               GuiLabel[Para1]->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
            }
            else if(str_9 == "AlignTop"){
                GuiLabel[Para1]->setAlignment(Qt::AlignRight|Qt::AlignTop);
            }
            else if(str_9 == "AlignBaseline"){
                GuiLabel[Para1]->setAlignment(Qt::AlignRight|Qt::AlignBaseline);
            }
            else if(str_9 == "AlignBottom"){
                GuiLabel[Para1]->setAlignment(Qt::AlignRight|Qt::AlignBottom);
            }
 }
        else if(str_8 == "AlignLeft"){
            if(str_9 == "AlignVCenter"){
                GuiLabel[Para1]->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            }
            else if(str_9 == "AlignTop"){
                GuiLabel[Para1]->setAlignment(Qt::AlignLeft|Qt::AlignTop);
            }
            else if(str_9 == "AlignBaseline"){
                GuiLabel[Para1]->setAlignment(Qt::AlignLeft|Qt::AlignBaseline);
            }
            else if(str_9 == "AlignBottom"){
                GuiLabel[Para1]->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
            }
        }
        else if(str_8 == "AlignHCenter"){
            if(str_9 == "AlignVCenter"){
                GuiLabel[Para1]->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }
            else if(str_9 == "AlignTop"){
                GuiLabel[Para1]->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
            }
            else if(str_9 == "AlignBaseline"){
                GuiLabel[Para1]->setAlignment(Qt::AlignHCenter|Qt::AlignBaseline);
            }
            else if(str_9 == "AlignBottom"){
                GuiLabel[Para1]->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
            }
        }
        else if(str_8 == "AlignJustify"){
            if(str_9 == "AlignVCenter"){
                GuiLabel[Para1]->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
            }
            else if(str_9 == "AlignTop"){
                GuiLabel[Para1]->setAlignment(Qt::AlignJustify|Qt::AlignTop);
            }
            else if(str_9 == "AlignBaseline"){
                GuiLabel[Para1]->setAlignment(Qt::AlignJustify|Qt::AlignBaseline);
            }
            else if(str_9 == "AlignBottom"){
                GuiLabel[Para1]->setAlignment(Qt::AlignJustify|Qt::AlignBottom);
            }
        }
        //GuiLabel[Para1]->setSizePolicy(Qpolicy);
    }
    else if(str == "QLineEdit"){
        GuiLineEdit[Para1] = new QLineEdit;
       // GuiLineEdit[Para1]->setSizePolicy(Qpolicy);
    }
    else if(str == "QPushButton"){
        GuiPushButton[Para1] = new QPushButton;
        GuiPushButton[Para1]->setText(GuiCsv->sheet.data[intWidgetNum][2]);
        if (file.exists()){
            GuiPushButton[Para1]->setIcon(QIcon(m_path + "/" + str_10));
            //QString aa="border-image:url("+m_path + "/" + str_10+");";//border-image:url(D:/QT_study/Cplus_study/QT_HPC_study/QT_HPC_study/ConfigurationFolder\images\blue_open.png);
//            GuiPushButton[Para1]->setStyleSheet("border-image: url("+m_path + "/" + str_10+");");
//        GuiPushButton[Para1]->setFocusPolicy(Qt::StrongFocus);
        }

        //GuiPushButton[Para1]->setSizePolicy(Qpolicy);
        GuiPushButtonBatFile[Para1] = new QString(m_path + "/" + str_8);
    }
    else if(str == "QComboBox"){
        GuiComboBox[Para1] =new QComboBox;
        GuiComboxCsv[Para1] = new CsvFileParse;
        if (file.exists()){
            GuiComboxCsv[Para1]->parseCSV(m_path + "/" + str_10);
            for(int i=0;i<GuiComboxCsv[Para1]->sheet.data.size();i++){
                GuiComboBox[Para1]->addItem(GuiComboxCsv[Para1]->sheet.data[i][0]);
            }
        }
        else{
            GuiComboBox[Para1]->addItem("There is no initialization file which is " + m_path + "/" + str_10);
        }

        //GuiComboBox[Para1]->setSizePolicy(Qpolicy);
    }
    else if(str == "QRadioButton"){
        GuiRadioButton[Para1] =new QRadioButton;
        GuiRadioButton[Para1]->setText(GuiCsv->sheet.data[intWidgetNum][2]);
        //GuiRadioButton[Para1]->setSizePolicy(Qpolicy);
    }
    else if(str == "QCheckBox"){
        GuiCheckBox[Para1] =new QCheckBox;
        GuiCheckBox[Para1]->setText(GuiCsv->sheet.data[intWidgetNum][2]);
        //GuiCheckBox[Para1]->setSizePolicy(Qpolicy);
    }
    else if(str == "QSpacerItem"){
        //QSpacerItem *spacerItem1 = new QSpacerItem(20,20,QSizePolicy::Minimum,QSizePolicy::Expanding);
        GuiSpacerItem[Para1] = new QSpacerItem(H_Size*20,V_Size*20,QSizePolicy::Minimum,QSizePolicy::Expanding);
    }
    else if(str == "QTableWidget"){
        GuiTableWidget[Para1] =new QTableWidget;
        //GuiTableWidget[Para1]->setSizePolicy(Qpolicy);
        if (file.exists()){
            GuiTableWidgetHeaderCsv[Para1] = new CsvFileParse;
            GuiTableWidgetHeaderCsv[Para1]->parseCSV(m_path + "/" + str_10);
            GuiTableWidget[Para1]->setRowCount(Para2);
            GuiTableWidget[Para1]->setColumnCount(GuiTableWidgetHeaderCsv[Para1]->sheet.data[child].size());
            header = GuiTableWidgetHeaderCsv[Para1]->sheet.data[child];
            GuiTableWidget[Para1]->setHorizontalHeaderLabels(header);
//            GuiTableWidget[Para1]->horizontalHeader()
//            GuiTableWidget[Para1]->horizontalHeader()->setStretchLastSection(true);
        }
        if(file_14.exists()){
            GuiTableWidgetDataCsv[Para1] = new CsvFileParse;
//            GuiTableWidgetDataCsv[Para1]->parseCSV(m_path + "/" + str_14);
            GuiTableWidgetDataCsv[Para1]->parseCSV(Gui_DataPath + "/" + str_14);
            UpdataTableFromQList(GuiTableWidget[Para1],GuiTableWidgetDataCsv[Para1]->sheet.data,0,0);
        }
    }
    else if((str == "QGroupBox")&&(str_10 =="Sub")){
        GuiGroup[flag] = new QGroupBox;
        GuiGroup[flag]->setTitle(GuiCsv->sheet.data[intWidgetNum][2]);
        GuiGroup[flag]->setLayout(GuiGridLayout[child]);
        GuiGroup[flag]->setSizePolicy(Qpolicy);
    }
    else if(str == "QHBoxLayout"){

    }
    else if(str == "GuiVBoxLayout"){

    }
    else if(str == "QTextEdit"){
        GuiTextEdit[Para1] = new QTextEdit;

        if(str_8 == "AlignRight"){
            if(str_9 == "AlignVCenter"){
               GuiTextEdit[Para1]->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
            }
            else if(str_9 == "AlignTop"){
                GuiTextEdit[Para1]->setAlignment(Qt::AlignRight|Qt::AlignTop);
            }
            else if(str_9 == "AlignBaseline"){
                GuiTextEdit[Para1]->setAlignment(Qt::AlignRight|Qt::AlignBaseline);
            }
            else if(str_9 == "AlignBottom"){
                GuiTextEdit[Para1]->setAlignment(Qt::AlignRight|Qt::AlignBottom);
            }
 }
        else if(str_8 == "AlignLeft"){
            if(str_9 == "AlignVCenter"){
                GuiTextEdit[Para1]->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            }
            else if(str_9 == "AlignTop"){
                GuiTextEdit[Para1]->setAlignment(Qt::AlignLeft|Qt::AlignTop);
            }
            else if(str_9 == "AlignBaseline"){
                GuiTextEdit[Para1]->setAlignment(Qt::AlignLeft|Qt::AlignBaseline);
            }
            else if(str_9 == "AlignBottom"){
                GuiTextEdit[Para1]->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
            }
        }
        else if(str_8 == "AlignHCenter"){
            if(str_9 == "AlignVCenter"){
                GuiTextEdit[Para1]->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }
            else if(str_9 == "AlignTop"){
                GuiTextEdit[Para1]->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
            }
            else if(str_9 == "AlignBaseline"){
                GuiTextEdit[Para1]->setAlignment(Qt::AlignHCenter|Qt::AlignBaseline);
            }
            else if(str_9 == "AlignBottom"){
                GuiTextEdit[Para1]->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
            }
        }
        else if(str_8 == "AlignJustify"){
            if(str_9 == "AlignVCenter"){
                GuiTextEdit[Para1]->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
            }
            else if(str_9 == "AlignTop"){
                GuiTextEdit[Para1]->setAlignment(Qt::AlignJustify|Qt::AlignTop);
            }
            else if(str_9 == "AlignBaseline"){
                GuiTextEdit[Para1]->setAlignment(Qt::AlignJustify|Qt::AlignBaseline);
            }
            else if(str_9 == "AlignBottom"){
                GuiTextEdit[Para1]->setAlignment(Qt::AlignJustify|Qt::AlignBottom);
            }
        }

        if (file.exists()){
            GuiTextEditDataFile[Para1]= new QString(m_path + "/" + str_10);
        }
    }
    else if((str == "QTabWidget")&&(str_10 =="Sub")){
        if(GuiTab[flag]==NULL){
            GuiTab[flag] = new QTabWidget;
        }
        GuiTab[flag]->setSizePolicy(Qpolicy);

        GuiTabChildWidget[child] = new QWidget();
        GuiTabChildWidget[child]->setLayout(GuiGridLayout[child]);

        GuiTab[flag]->addTab(GuiTabChildWidget[child],QIcon(m_path + "/" + str_12), GuiCsv->sheet.data[intWidgetNum][2]);
    }
    else{

    }
}


void GUI::DataFlagSave(){
    QString DataType,flag,descrip,WidgetType,WigetFlagNum,WigetValue;
    QStringList SingleArrary;

    for(int i=0;i<GuiCsv->sheet.data.size();i++){
        DataType = GuiCsv->sheet.data[i][7];
        flag = GuiCsv->sheet.data[i][8];
        descrip = GuiCsv->sheet.data[i][14];
        WidgetType = GuiCsv->sheet.data[i][1];
        WigetFlagNum = GuiCsv->sheet.data[i][12];
        WigetValue = "Null";

//        if((str == "QLineEdit")||(str == "QComboBox")||(str == "QRadioButton")||(str == "QCheckBox")){
        SingleArrary.clear();
        SingleArrary.append(DataType);
        SingleArrary.append(flag);
        SingleArrary.append(descrip);
        SingleArrary.append(WigetValue);
        SingleArrary.append(WidgetType);
        SingleArrary.append(WigetFlagNum);
        GuiFunctionData.append(SingleArrary);
//        }
    }

//    WriteGUIData = new CsvFileWrite;
//    WriteGUIData->sheet.data = GuiFunctionData;
//    WriteGUIData->generateCSV(m_path + "\\ConfigurationFolder\\GUIParaconfigfile.csv");
}

void GUI::ReadGuiPara(const QString &fileName){
    CsvFileParse ReadCsvobj;
    ReadCsvobj.parseCSV(fileName);
    UpdataGuiPara(ReadCsvobj.sheet.data);

    UpdateUserDefinedPara(true);
}

void GUI::WriteGuiPara(const QString &fileName){
    UpdateUserDefinedPara(false);

    QString DataType,flag,descrip,WidgetType,WigetFlagNum,WigetValue,Guiflag_fuzhu;
    int WigetValueInt,WigetFlagNumInt;

    QList<QStringList> GuiFunctionDataFuzhu;
    GuiFunctionDataFuzhu.clear();
    WriteGUIData = new CsvFileWrite;
    QStringList SingleArrary;
    for(int i=0;i<GuiFunctionData.size();i++){
        DataType = GuiFunctionData[i][0];
        flag = GuiFunctionData[i][1];
        descrip = GuiFunctionData[i][2];
        WigetValue = GuiFunctionData[i][3];
        WidgetType = GuiFunctionData[i][4];
        WigetFlagNum = GuiFunctionData[i][5];
        Guiflag_fuzhu = GuiFunctionData[i][6];

        WigetFlagNumInt = WigetFlagNum.toInt();
        if(WidgetType == "QLineEdit"){
            if(GuiLineEdit[WigetFlagNumInt]!=NULL) WigetValue = GuiLineEdit[WigetFlagNumInt]->text();
        }
        else if(WidgetType == "QComboBox"){
            if(GuiComboBox[WigetFlagNumInt]!=NULL){
                WigetValueInt = GuiComboBox[WigetFlagNumInt]->currentIndex();
                WigetValue = QString::number(WigetValueInt);}
        }
        else if(GuiRadioButton[WigetFlagNumInt]!=NULL&&WidgetType == "QRadioButton"){
            if(GuiRadioButton[WigetFlagNumInt]->isChecked()){
                WigetValue = "1";
            }
            else{
                WigetValue = "0";
            }
        }
        else if(GuiCheckBox[WigetFlagNumInt]!=NULL&&WidgetType == "QCheckBox"){
            if(GuiCheckBox[WigetFlagNumInt]->checkState() == Qt::Checked){
                WigetValue = "1";
            }
            else{
                WigetValue = "0";
            }
        }
        else if(GuiUserDefined[WigetFlagNumInt]!=NULL&&WidgetType == "UserDefined"){
            WigetValue = *GuiUserDefined[WigetFlagNumInt];
        }
        else if(GuiGroup[WigetFlagNumInt]!=NULL&&WidgetType == "QGroupBox"){
            if(GuiGroup[WigetFlagNumInt]->isCheckable()){
                if(GuiGroup[WigetFlagNumInt]->isChecked()){
                    WigetValue = "1";
                }
                else{
                    WigetValue = "0";
                }
            }
        }
        else if(GuiGroup_E[WigetFlagNumInt]!=NULL&&WidgetType == "QGroupBox_E"){
            if(GuiGroup_E[WigetFlagNumInt]->isCheckable()){
                if(GuiGroup_E[WigetFlagNumInt]->isChecked()){
                    WigetValue = "1";
                }
                else{
                    WigetValue = "0";
                }
            }
        }
        else if(GuiTableWidget[WigetFlagNumInt]!=NULL&&WidgetType == "QTableWidget"){
            if(GuiTableWidgetDataCsv[WigetFlagNumInt]!=NULL){
                GuiTableWidgetDataCsv[WigetFlagNumInt]->sheet.data.clear();
                GuiTableWidgetDataCsv[WigetFlagNumInt]->sheet.data = GetTableData(GuiTableWidget[WigetFlagNumInt]);
                GuiTableWidgetDataCsv[WigetFlagNumInt]->generateCSV(Gui_DataPath + "/" +descrip);
            }
        }
        else if((GuiTextEdit[WigetFlagNumInt]!=NULL)&&(WidgetType == "QTextEdit")){
            if(GuiTextEdit[WigetFlagNumInt]!=NULL){
                UpdataTextEditData(*GuiTextEdit[WigetFlagNumInt],*GuiTextEditDataFile[WigetFlagNumInt],EWrite);
            }
        }

        SingleArrary.clear();
        SingleArrary.append(DataType);
        SingleArrary.append(flag);
        SingleArrary.append(descrip);
        SingleArrary.append(WigetValue);
        SingleArrary.append(WidgetType);
        SingleArrary.append(WigetFlagNum);
        SingleArrary.append(Guiflag_fuzhu);
        GuiFunctionDataFuzhu.append(SingleArrary);
    }
    GuiFunctionData = GuiFunctionDataFuzhu;

    WriteGUIData->sheet.data = GuiFunctionDataFuzhu;
    WriteGUIData->generateCSV(fileName);

    UpdateUserDefinedPara(true);
}

void GUI::UpdataGuiPara(QList<QStringList> TwoA){
    GuiFunctionData.clear();

    QString DataType,flag,descrip,WidgetType,WigetFlagNum,WigetValue,Guiflag_fuzhu;
    int WigetValueInt,WigetFlagNumInt;

    QStringList SingleArrary;
    for(int i=0;i<TwoA.size();i++){
        DataType = TwoA[i][0];
        flag = TwoA[i][1];
        descrip = TwoA[i][2];
        WigetValue = TwoA[i][3];
        WidgetType = TwoA[i][4];
        WigetFlagNum = TwoA[i][5];
        Guiflag_fuzhu = TwoA[i][6];

        WigetValueInt = WigetValue.toInt();
        WigetFlagNumInt = WigetFlagNum.toInt();

        if(Guiflag_fuzhu ==GuiCsv->sheet.data[1][11]){
            if((GuiLineEdit[WigetFlagNumInt]!=NULL)&&(WidgetType == "QLineEdit")){
                GuiLineEdit[WigetFlagNumInt]->setText(WigetValue);
            }
            else if((GuiComboBox[WigetFlagNumInt]!=NULL)&&(WidgetType == "QComboBox")){
                GuiComboBox[WigetFlagNumInt]->setCurrentIndex(WigetValueInt);
            }
            else if((GuiRadioButton[WigetFlagNumInt]!=NULL)&&(WidgetType == "QRadioButton")){
                if(WigetValueInt ==0){
                    GuiRadioButton[WigetFlagNumInt]->setChecked(false);
                }
                else{
                    GuiRadioButton[WigetFlagNumInt]->setChecked(true);
                }
            }
            else if((GuiCheckBox[WigetFlagNumInt]!=NULL)&&(WidgetType == "QCheckBox")){
                if(WigetValueInt ==0){
                    GuiCheckBox[WigetFlagNumInt]->setCheckState(Qt::Unchecked);
                }
                else{
                    GuiCheckBox[WigetFlagNumInt]->setCheckState(Qt::Checked);
                }
            }
            else if((GuiUserDefined[WigetFlagNumInt]!=NULL)&&(WidgetType == "UserDefined")){
                *GuiUserDefined[WigetFlagNumInt] = WigetValue;
            }
            else if((GuiGroup[WigetFlagNumInt]!=NULL)&&(WidgetType == "QGroupBox")){
                if(GuiGroup[WigetFlagNumInt]->isCheckable()){
                    if(WigetValueInt ==0){
                        GuiGroup[WigetFlagNumInt]->setChecked(false);
                    }
                    else{
                        GuiGroup[WigetFlagNumInt]->setChecked(true);
                    }
                }
            }
            else if((GuiGroup_E[WigetFlagNumInt]!=NULL)&&(WidgetType == "QGroupBox_E")){
                if(GuiGroup_E[WigetFlagNumInt]->isCheckable()){
                    if(WigetValueInt ==0){
                        GuiGroup_E[WigetFlagNumInt]->setChecked(false);
                        GuiGroup_E[WigetFlagNumInt]->UpdateState(false);
                    }
                    else{
                        GuiGroup_E[WigetFlagNumInt]->setChecked(true);
                        GuiGroup_E[WigetFlagNumInt]->UpdateState(true);
                    }
                }
            }
            else if((GuiTableWidget[WigetFlagNumInt]!=NULL)&&(WidgetType == "QTableWidget")){
                if(GuiTableWidgetDataCsv[WigetFlagNumInt]!=NULL){
                    GuiTableWidgetDataCsv[WigetFlagNumInt]->sheet.data.clear();
                    GuiTableWidgetDataCsv[WigetFlagNumInt]->parseCSV(Gui_DataPath + "/" + descrip);
                    UpdataTableFromQList(GuiTableWidget[WigetFlagNumInt],GuiTableWidgetDataCsv[WigetFlagNumInt]->sheet.data,0,0);
                }
            }
            else if((GuiTextEdit[WigetFlagNumInt]!=NULL)&&(WidgetType == "QTextEdit")){
                if(GuiTextEdit[WigetFlagNumInt]!=NULL){
                    UpdataTextEditData(*GuiTextEdit[WigetFlagNumInt],*GuiTextEditDataFile[WigetFlagNumInt],ERead);
                }
            }

            SingleArrary.clear();
            SingleArrary.append(DataType);
            SingleArrary.append(flag);
            SingleArrary.append(descrip);
            SingleArrary.append(WigetValue);
            SingleArrary.append(WidgetType);
            SingleArrary.append(WigetFlagNum);
            SingleArrary.append(Guiflag_fuzhu);
            GuiFunctionData.append(SingleArrary);
        }
    }
    //Check whether the data is integrated
    QString tempWidgetType,tempWigetFlagNum;
    bool flagexist;
    for(int i=0;i<GuiCheckFunctionData.size();i++){
        flagexist=false;
        tempWidgetType = GuiCheckFunctionData[i][4];
        tempWigetFlagNum = GuiCheckFunctionData[i][5];

        for(int j=0;j<GuiFunctionData.size();j++){
            WidgetType = GuiFunctionData[j][4];
            WigetFlagNum = GuiFunctionData[j][5];
            if(WidgetType==tempWidgetType){
                if(WigetFlagNum==tempWigetFlagNum){
                    flagexist=true;
                    break;
                }
            }
        }

        if(!flagexist){
            SingleArrary.clear();
            SingleArrary.append(GuiCheckFunctionData[i][0]);
            SingleArrary.append(GuiCheckFunctionData[i][1]);
            SingleArrary.append(GuiCheckFunctionData[i][2]);
            SingleArrary.append(GuiCheckFunctionData[i][3]);
            SingleArrary.append(GuiCheckFunctionData[i][4]);
            SingleArrary.append(GuiCheckFunctionData[i][5]);
            SingleArrary.append(GuiCheckFunctionData[i][6]);
            GuiFunctionData.append(SingleArrary);
        }
    }

    UpdateUserDefinedPara(true);
}


void GUI::SetMainpath(const QString &fileName){
    m_path = fileName;
}

QString GUI::GetMainpath(){
    return m_path;
}

void GUI::SetGuiFile(const QString &fileName){
    GuiFile = fileName;
}

QString GUI::GetGuiFile(){
    return GuiFile;
}

void GUI::SetGuiDataPath(const QString &qstrPath)
{
    Gui_DataPath = qstrPath;
}

QString GUI::GetGuiDataPath()
{
    return Gui_DataPath;
}

void GUI::SetGuiDataFile(const QString &qstrGuiDataFile)
{
    Gui_DataFile = qstrGuiDataFile;
}

QString GUI::GetGuiDataFile()
{
    return Gui_DataFile;
}

//void GUI::SetGuiFlag(const QString &fileName){
//    GuiFlag = fileName;
//}

//QString GUI::GetGuiFlag(){
//    return GuiFlag;
//}

//update Gui data and transfer data to model
void GUI::SetGuiDatatoObject(QList<QStringList>* DataTransfer){
    UpdateUserDefinedPara(true);

    QString DataType,flag,descrip,WidgetType,WigetFlagNum,WigetValue,Guiflag_fuzhu;
    int WigetValueInt,WigetFlagNumInt;

    QList<QStringList> GuiFunctionDataFuzhu;
    GuiFunctionDataFuzhu.clear();
    QStringList SingleArrary;
    for(int i=0;i<GuiFunctionData.size();i++){
        DataType = GuiFunctionData[i][0];
        flag = GuiFunctionData[i][1];
        descrip = GuiFunctionData[i][2];
        WigetValue = GuiFunctionData[i][3];
        WidgetType = GuiFunctionData[i][4];
        WigetFlagNum = GuiFunctionData[i][5];
        Guiflag_fuzhu = GuiFunctionData[i][6];

        WigetFlagNumInt = WigetFlagNum.toInt();
        if(GuiLineEdit[WigetFlagNumInt]!=NULL&&WidgetType == "QLineEdit"){
            WigetValue = GuiLineEdit[WigetFlagNumInt]->text();
        }
        else if(GuiComboBox[WigetFlagNumInt]!=NULL&&WidgetType == "QComboBox"){
            WigetValueInt = GuiComboBox[WigetFlagNumInt]->currentIndex();
            WigetValue = QString::number(WigetValueInt);
        }
        else if(GuiRadioButton[WigetFlagNumInt]!=NULL&&WidgetType == "QRadioButton"){
            if(GuiRadioButton[WigetFlagNumInt]->isChecked()){
                WigetValue = "1";
            }
            else{
                WigetValue = "0";
            }
        }
        else if(GuiCheckBox[WigetFlagNumInt]!=NULL&&WidgetType == "QCheckBox"){
            if(GuiCheckBox[WigetFlagNumInt]->checkState() == Qt::Checked){
                WigetValue = "1";
            }
            else{
                WigetValue = "0";
            }
        }
        else if((GuiUserDefined[WigetFlagNumInt]!=NULL)&&(WidgetType == "UserDefined")){
            *GuiUserDefined[WigetFlagNumInt] = WigetValue;
        }
        else if(GuiGroup[WigetFlagNumInt]!=NULL&&WidgetType == "QGroupBox"){
            if(GuiGroup[WigetFlagNumInt]->isCheckable()){
                if(GuiGroup[WigetFlagNumInt]->isChecked()){
                    WigetValue = "1";
                }
                else{
                    WigetValue = "0";
                }
            }
        }

        SingleArrary.clear();
        SingleArrary.append(DataType);
        SingleArrary.append(flag);
        SingleArrary.append(descrip);
        SingleArrary.append(WigetValue);
        SingleArrary.append(WidgetType);
        SingleArrary.append(WigetFlagNum);
        SingleArrary.append(Guiflag_fuzhu);
        GuiFunctionDataFuzhu.append(SingleArrary);

        DataTransfer->append(SingleArrary);
    }
    GuiFunctionData = GuiFunctionDataFuzhu;

    SetRestGuiDatatoObject(DataTransfer);
}

void GUI::SetRestGuiDatatoObject(QList<QStringList> *DataTransfer){

}

void GUI::GetGuiDataFromObject(QList<QStringList>* DataTransfer){
    UpdataGuiPara(*DataTransfer);
    GetRestGuiDataFromObject(DataTransfer);
}

void GUI::GetRestGuiDataFromObject(QList<QStringList> *DataTransfer){

}

void GUI::GuiPreFunction(){
//    if(GuiGroup[0]!=NULL) GuiGroup[0]->setCheckable(true);
//    if(GuiGroup[1]!=NULL) GuiGroup[1]->setCheckable(true);
//    if(GuiGroup[2]!=NULL) GuiGroup[2]->setCheckable(true);
//    if(GuiGroup[3]!=NULL) GuiGroup[3]->setCheckable(true);
}

void GUI::UpdateUserDefinedPara(bool flag){

}

void GUI::SetConfigPath(QString Path)
{

}

QString GUI::GetConfigPath()
{
    return "";
}

void GUI::ReadConfigFile()
{

}

void GUI::WriteConfigFile()
{

}


void GUI::UpdataTableFromQList(QTableWidget *Tableobj, QList<QStringList> Data, int RowStart, int ColumStart)
{
    if(Tableobj!=NULL){
        int TableRowNum = Tableobj->rowCount();
        int TableColumNum = Tableobj->columnCount();

        //if the row number of tabel is small than clipdata
        if(TableRowNum<(RowStart + Data.size())){
            Tableobj->setRowCount(RowStart + Data.size());
        }

        for(int i=0;i<Data.size();i++){
             for(int j=0;j<Data[0].size();j++)
             {
                if(ColumStart+j<TableColumNum)
                {
                   Tableobj->setItem(RowStart+i,ColumStart+j,new QTableWidgetItem(Data[i][j]));
                }
             }
        }

    }
}

QList<QStringList> GUI::GetTableData(QTableWidget *Tableobj){
    QList<QStringList> TableData;
    QStringList temp_SingleA;
    TableData.clear();
    if(Tableobj!=NULL){
        int TableRowNum = Tableobj->rowCount();
        int TableColumNum = Tableobj->columnCount();

        //Get the number of row which used
        bool temp_Flag = true;
        QString Temp_str;
        QRegExp rxSpace;
        int RealRowNum=0;
        rxSpace.setPattern(QString("^[\\s]+$"));
        for(int i=0;i<TableRowNum;i++){
            if(Tableobj->item(i,0)!=NULL){
                Temp_str=Tableobj->item(i,0)->text();
                if((!Temp_str.isEmpty())&&(!rxSpace.exactMatch(Temp_str))){
                    RealRowNum++;
                }
            }
        }

        //Output useful data
        for(int i=0;i<RealRowNum;i++){
             temp_SingleA.clear();
             for(int j=0;j<TableColumNum;j++){
                 if(Tableobj->item(i,j)!=NULL){
                     temp_SingleA.append(Tableobj->item(i,j)->text());
                 }
                 else{
                     temp_SingleA.append("  ");
                 }
             }
             TableData.append(temp_SingleA);
        }
//        if(RealRowNum){

//        }

        return TableData;
    }
    return TableData;
}

void GUI::DeleSelectedInTable(QTableWidget *Tableobj, int RowStart, int ColumStart, int RowNum, int ColumNum)
{
    if(Tableobj!=NULL){
        int RowSum,ColumSum;

        //Delete Row
        for(int i=RowStart;i<RowStart + RowNum;i++){
            RowSum = Tableobj->rowCount();
            if(RowSum>1){
                Tableobj->removeRow(RowStart);
            }
        }

        //Delete Colum
        for(int i=ColumStart;i<ColumStart + ColumNum;i++){
            ColumSum = Tableobj->colorCount();
            if(ColumSum>1){
                Tableobj->removeColumn(ColumStart);
            }
        }
    }
}

void GUI::CreatCheckFunctionData(int num1)
{
//    GuiCheckFunctionData.clear();
    QStringList TempstrList;
    QStringList SingleArrary;
    TempstrList.clear();
    SingleArrary.clear();
    for(int i=0;i<17;i++){
        TempstrList.append(GuiCsv->sheet.data[num1][i]);
    }
    QString str = TempstrList[1];

    SingleArrary.append(TempstrList[7]);
    SingleArrary.append(TempstrList[8]);
    SingleArrary.append(TempstrList[14]);
    SingleArrary.append("Value");
    SingleArrary.append(TempstrList[1]);
    SingleArrary.append(TempstrList[12]);
    SingleArrary.append(TempstrList[11]);
    //special control
    if(str == "Qlabel"){
        SingleArrary[0] = TempstrList[15];
        SingleArrary[1] = TempstrList[14];
        SingleArrary[2] = TempstrList[16];
    }
//    else if(str == "QLineEdit"){

//    }
//    else if(str == "QPushButton"){

//    }
//    else if(str == "QComboBox"){

//    }
//    else if(str == "QRadioButton"){

//    }
//    else if(str == "QCheckBox"){

//    }
//    else if(str == "QSpacerItem"){

//    }
    else if(str == "QTableWidget"){
        SingleArrary[1] = TempstrList[16];
    }
    else if(str == "QGroupBox"){
        SingleArrary[1] = TempstrList[16];
        SingleArrary[5] = TempstrList[8];
    }
    else if(str == "QHBoxLayout"){
        SingleArrary[5] = TempstrList[8];
    }
    else if(str == "QHBoxLayout_M"){
        SingleArrary[5] = TempstrList[8];
    }
    else if(str == "QGridLayout"){
        SingleArrary[5] = TempstrList[8];
    }
    else if(str == "QGroupBox_E"){
        SingleArrary[5] = TempstrList[8];
    }
    else{   //

    }
    GuiCheckFunctionData.append(SingleArrary);
}

void GUI::UpdataTextEditData(QTextEdit &TextEditObj, const QString &strFile, int intFlag)
{
    if(intFlag == EWrite){
        QFile file(strFile);
        if (!file.open(QFile::WriteOnly | QFile::Text))     //
        {
            //Print log

            QMessageBox::information(this, "Error Message", "Please Select a Text File!");
            return;
        }
        QTextStream out(&file);                 //分行写入文件
        out << TextEditObj.toPlainText();
        file.close();
    }
    else{
        QFile file(strFile);
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            //Print log

             QMessageBox::warning(this, tr("Application"),
                                     tr("Cannot read file %1:\n%2.")
                                  .arg(strFile)
                                     .arg(file.errorString()));
             return;
        }
        QTextStream in(&file);
        TextEditObj.setText(in.readAll());
        file.close();
    }
}
