#include "caeglobalfunction.h"

QString caeglobalFunction::stringtoQS(const string &s){
     return QString(QString::fromLocal8Bit(s.c_str()));
}

string caeglobalFunction::QStostring(const QString &s){
     return string((const char *)s.toLocal8Bit());
}

// 需包含locale、string头文件、使用setlocale函数。
std::wstring caeglobalFunction::StringToWstring(const std::string str)
{// string转wstring
    unsigned len = str.size() * 2;// 预留字节数
    setlocale(LC_CTYPE, "");     //必须调用此函数
    wchar_t *p = new wchar_t[len];// 申请一段内存存放转换后的字符串
    mbstowcs(p,str.c_str(),len);// 转换
    std::wstring str1(p);
    delete[] p;// 释放申请的内存
    return str1;
}

std::string caeglobalFunction::WstringToString(const std::wstring str)
{// wstring转string
    unsigned len = str.size() * 4;
    setlocale(LC_CTYPE, "");
    char *p = new char[len];
    wcstombs(p,str.c_str(),len);
    std::string str1(p);
    delete[] p;
    return str1;
}

bool caeglobalFunction::StringReplaceStr(const char *filePath, string OldStr, string ReplaceStr)
{
    string Newfile[5000];
    int i = 0, pos, count, len;
    len = (int)OldStr.length();
    ifstream inFile;
    inFile.open(filePath);

    if (!inFile.is_open())
    {
        return false;
    }

    for (string str; getline(inFile, str); i++)
    {
        if (str.substr(0, len) == OldStr)
        {
            len = (int)str.length();
        }
        pos = (int)str.find(OldStr);
        if (pos >= 0)
        {
            str.replace(pos, len, ReplaceStr);
        }
        if (i>4999)
        {
            return false;
        }
        else
            Newfile[i] = str;
    }
    count = i;
    inFile.close();
    //写入文件
    ofstream outFile;
    outFile.open(filePath);
    if (!outFile.is_open())
    {
        return false;
    }
    for (i = 0; i <= count; i++)
    {
        outFile << Newfile[i] << endl;
    }
    outFile.close();
    return true;
}

//CAE模板用到的相关函数
QString caeglobalFunction::CreatTimeFolder(QString StrPath,QString PreFix)
{
    //获得当前时间
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy_MM_dd_hh_mm_ss");
    //qDebug()<<current_date<<"Practice";
    QString FolderName = PreFix + current_date;
    QString m_path = StrPath + "\\" + FolderName;

    QDir dir(m_path);
    if(!dir.exists()){
        bool ok = dir.mkpath(m_path);//创建多级目录
        if(!ok){  //Add Message
            QMessageBox::information(NULL, "Create folder according to date", "Failed to generate folder which is "+m_path+".", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return "Failed to generate folder which is "+m_path+".";
        }
    }
    return m_path;
}


//To replace file's CString from OldStr to ReplaceStr
bool caeglobalFunction::ReplaceFolderFile(QString FilePath, QString OldStr, QString ReplaceStr)
{
    string OldStr_s = QStostring(OldStr);
    string ReplaceStr_s = QStostring(ReplaceStr);
    //**********修改指定路径FilePath下文件file的字符串**********
    std::string PszFile_S = QStostring(FilePath);
    const char *pszFile = PszFile_S.c_str();
    bool fu_temp = StringReplaceStr(pszFile, OldStr_s, ReplaceStr_s);
    return fu_temp;
}

//To Run a Program
QString caeglobalFunction::RunAnsysProgram(QString ProgramPath, QString WorkPath, QString AnsysProgramName,bool Waitflag){
    //调用ANSYS_AIM程序
    LPCTSTR WorkPath_L;
    STARTUPINFO StartupInfo2;
    PROCESS_INFORMATION ProcessInfo2;
    memset(&StartupInfo2, 0, sizeof(STARTUPINFO));//分配内存
    StartupInfo2.cb = sizeof(STARTUPINFO);//初始化
    StartupInfo2.dwFlags = STARTF_USESHOWWINDOW;
    StartupInfo2.wShowWindow = SW_HIDE;
    //1定义程序工作路径（也即子进程的工作路径）
    //const char *buf;
    //LPCTSTR *p = (LPCTSTR *)buf;
    string buf = QStostring(WorkPath);    //QString 转 const char *
    WorkPath_L = (LPCTSTR)WorkPath.utf16();
    //&&&&&&&&&&&&QString转LPWSTR
    //LPWSTR ProgramPath_L = (LPWSTR)(LPCWSTR)ProgramPath;
    LPWSTR ProgramPath_L =(LPWSTR)ProgramPath.utf16();
    //2不同电脑上的Ansys启动路径不一样，要修改
//    QWidget* MessageBox_temp;
//    MessageBox_temp = new QWidget;
    QString outInfo;
    if (!::CreateProcess(NULL, ProgramPath_L,
        NULL,
        NULL,
        false,
        0,
        NULL,
        WorkPath_L,
        &StartupInfo2,
        &ProcessInfo2)){
        outInfo = AnsysProgramName + " program failed to run. ";
        //QMessageBox::information(NULL, "Program call status", outInfo, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        QMessageBox::information(NULL, "Program call status", outInfo, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//        MessageBox_temp->activateWindow();
        //AfxMessageBox(outInfo, MB_ICONERROR);
        return outInfo;
        GetLastError();
    }
    else{
        //等待，直到创建的ANSYS进程运行完毕。
        if(Waitflag){
            outInfo = AnsysProgramName + " program is running, Please wait.";
            ::WaitForSingleObject(ProcessInfo2.hProcess, INFINITE);
        }
        QMessageBox::information(NULL, "Program call status", outInfo, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//        MessageBox_temp->activateWindow();
//        MessageBox_temp->setWindowFlags(Qt::WindowStaysOnTopHint);
        return outInfo;
    }
}

//Get disk free space
quint64 caeglobalFunction::GetDiskFreeSpace(QString driver)
{
    if(PathAndFileExists(driver,1)){
        LPCWSTR lpcwstrDriver=(LPCWSTR)driver.utf16();
        ULARGE_INTEGER liFreeBytesAvailable, liTotalBytes, liTotalFreeBytes;
        if(!GetDiskFreeSpaceEx( lpcwstrDriver, &liFreeBytesAvailable, &liTotalBytes, &liTotalFreeBytes) ) {
            QString Info_S = "ERROR: Call to GetDiskFreeSpaceEx() failed.";
            QMessageBox::warning(NULL, "Get Disk Free Space", Info_S, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return 0;
        }
        QString Info_S = "ERROR: Call to GetDiskFreeSpaceEx() failed.";
        //QMessageBox::warning(NULL, "Get Disk Free Space", Info_S, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return (quint64) liTotalFreeBytes.QuadPart/1024/1024/1024;
    }
    else{
        int freeeeeeee = 0;
        return (quint64) freeeeeeee;
    }


}

//Browse file and return  file selected
QString caeglobalFunction::BrowseFile(QString Filter, QString DefaultDir,QString FirstMessage, QString FailMessage)
{
    QString FileSelected;
    //bool isOpen=true;     //是否打开(否则为保存)
    if (FirstMessage != ""){
        QMessageBox::information(NULL, "Dialog", FirstMessage, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

    //QString CreoModelS= QFileDialog::getOpenFileName(this,"open file dialog","/","C++(*.cpp)::C files(*.c)");
    //QString QFileDialog::getOpenFileName(QWidget *parent = Q_NULLPTR, const QString &caption = QString(), const QString &dir = QString(), const QString &filter = QString(), QString *selectedFilter = Q_NULLPTR, Options options = Options())
    QString CreoModelS= QFileDialog::getOpenFileName(NULL,"Open file dialog",DefaultDir,Filter);

    //未选择文件的处理
    if(CreoModelS==""){
        return FailMessage;
    }
    return CreoModelS;
}


//Browse file and return  folder selected
QString caeglobalFunction::BrowseFolder(QString TitleInfo,QString NoticeInfo,QString DefaultDir)
{
    QString strFolderPath = QFileDialog::getExistingDirectory(NULL, TitleInfo+NoticeInfo,
                                                     DefaultDir,
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    return strFolderPath;
}

//Get the correct path through the v150 file
QString caeglobalFunction::GetAnsysAimPath(QString PathV162){
    QString AnsysAimPath,AnsysAimPath32,AnsysAimPathReal;
    //Ansys_ver = PathV162.Right(3);          //截取右边3个字符
    AnsysAimPath = PathV162 + "/Framework/bin/Win64/runwb2.exe";

    if(!QFile::exists(AnsysAimPath)){
        QMessageBox::information(NULL, "Don't find the installation location of ANSYS Workbench", "There is no file which is "+AnsysAimPath+".", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return "There is no file which is "+AnsysAimPath+".";
    }

    return AnsysAimPath;
}

//Get the correct path through the v150 file
QString caeglobalFunction::GetAnsysAPDLPath(QString PathVer){
    QString AnsysAPDLPath,AnsysAimPath32,AnsysAimPathReal,APDL_ver;
    APDL_ver = PathVer.right(3);          //截取右边3个字符
    AnsysAPDLPath = PathVer + "/ansys/bin/winx64/ANSYS" + APDL_ver + ".exe";

    if(!QFile::exists(AnsysAPDLPath)){
        QMessageBox::information(NULL, "Don't find the installation location of ANSYS APDL", "There is no file which is "+AnsysAPDLPath+".", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return "There is no file which is "+AnsysAPDLPath+".";
    }

    return AnsysAPDLPath;
}


QList<QStringList> caeglobalFunction::ReadConfigFile(const QString &fileName){
    CsvFileParse* ReadConfigCsvObj=new CsvFileParse;
    ReadConfigCsvObj->parseCSV(fileName);

    QList<QStringList> Q_data;
    Q_data = ReadConfigCsvObj->sheet.data;
    return Q_data;
}

QList<QStringList> caeglobalFunction::ReadCSVFile(const QString &fileName)
{
    CsvFileParse* ReadConfigCsvObj=new CsvFileParse;
    ReadConfigCsvObj->parseCSV(fileName);

    QList<QStringList> Q_data;
    Q_data = ReadConfigCsvObj->sheet.data;
    return Q_data;

}

void caeglobalFunction::WriteConfigFile(const QString &fileName,QList<QStringList> ConfigData){
    CsvFileWrite* WriteCeshi=new CsvFileWrite;
    WriteCeshi->sheet.data = ConfigData;
    WriteCeshi->generateCSV(fileName);
}

void caeglobalFunction::WriteCSVFile(const QString &fileName, QList<QStringList> ConfigData)
{
    CsvFileWrite* WriteCeshi=new CsvFileWrite;
    WriteCeshi->sheet.data = ConfigData;
    WriteCeshi->generateCSV(fileName);

}


//Rename creo model if its name begins with number.
QString caeglobalFunction::JudgeAndRenameCreoModel(const QString &fileName){
    QString ReturnName;

    int FindPos1 = fileName.lastIndexOf("/");
    int FindPos2 = fileName.lastIndexOf("\\");
    int FindReal;
    FindReal = FindPos2;
    if(FindPos1>FindPos2){
        FindReal = FindPos1;
    }
    QString FilePath = fileName.left(FindReal);

    int FindPoint = fileName.indexOf(".");
    QString OnlyFileName = fileName.mid(FindReal+1,FindPoint-FindReal-1);

    QString Lastext = fileName.right(fileName.size()-FindPoint);


    //Rename creo model if its name begins with number.
    QString FirstAtName = OnlyFileName.left(1);
    double temp = FirstAtName.toDouble();
    if(temp>0.0){
        bool isOk = QFile::rename(fileName, FilePath + "/" + "ASM" + OnlyFileName + Lastext);
        if (!isOk){
            QMessageBox::warning(NULL, "Warning", "Rename creo model failed!!");
            return "Rename creo model failed!!";
        }
        else{
            ReturnName = FilePath + "/" + "ASM" + OnlyFileName + Lastext;
        }
    }
    else{
        ReturnName = fileName;
    }
    return ReturnName;
}

bool caeglobalFunction::PathMatchCheck(const QString &fileName){
    bool temp_Flag = true;
    QRegExp rxSpace,rxMidGan;
    rxSpace.setPattern(QString("^[A-Za-z]:([^\\s]*)?$"));
    rxMidGan.setPattern(QString("^[A-Za-z]:([^\-]*)?$"));

    if(!rxSpace.exactMatch(fileName)){
        temp_Flag = false;
        QMessageBox::warning(NULL, "This Path is wrong", "Please make sure that "+ fileName + " does not contain spaces!!");
    }
    if(!rxMidGan.exactMatch(fileName)){
        temp_Flag = false;
        QMessageBox::warning(NULL, "This Path is wrong", "Please make sure that "+ fileName + " does not contain \"-\"!!");
    }
    return temp_Flag;
}

//数据转置，针对二维的列表
QList<QStringList> caeglobalFunction::TransposeData(QList<QStringList> oldData){

    QList<QStringList> newData;
    QStringList templist;
    //qDebug<<oldData[0].size();
    for(int i=0;i<oldData[0].size();i++)
    {
        for(int j = 0; j < oldData.size(); j++)
        {
            templist.append(oldData[j][i]);

        }
        newData.append(templist);
        templist.clear();
    }
    return newData;
}

bool caeglobalFunction::QStringisexistinQStringList(QString name, QStringList list)
{
    bool isexist=false;
    for (int i=0;i<list.size();i++)
    {
        if(name==list.at(i))
        {
            isexist=true;
        }
    }
    return isexist;
}

bool caeglobalFunction::PathAndFileExists(QString PathFile,int flag){
    if(PathFile !=""){
        QDir dir(PathFile);
        QFile file(PathFile);
        switch(flag){
        case 1:
            if(dir.exists()){
                return true;
            }
            else{
                return false;
            }
            break;
        case 2:
            if (file.exists()){
                return true;
            }
            else{
                return false;
            }
            break;
        }
    }
    else{
        return false;
    }

}

bool caeglobalFunction::CreatSpecifiedFile(QString FileName){
    QFile file(FileName);
    bool openOk = file.open(QIODevice::WriteOnly);
    if(!openOk)
    {
        QMessageBox::information(NULL, "Creat file", "Creat file which is"+ FileName+" unsuccessfully.", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return false;
    }
    else{
        file.close();
        return true;
    }
}

QString caeglobalFunction::CreatSpecificFolder(QString DirPath, QString DirName)
{

    QString m_path = DirPath + "/" + DirName;

    QDir dir(m_path);
    if(!dir.exists()){
        bool ok = dir.mkpath(m_path);//创建多级目录
        if(!ok){  //Add Message
            QMessageBox::information(NULL, "Create folder", "Failed to generate folder which is "+m_path+".", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return "Failed to generate folder which is "+m_path+".";
        }
    }
    return m_path;
}

bool caeglobalFunction::DeleteSpecificFolder(QString dirName)
{
//    QDir dir(folderDir);
//    QFileInfoList fileList;
//    QFileInfo curFile;
//    if(!dir.exists())  {return false;}//文件不存，则返回false
//    fileList=dir.entryInfoList(QDir::Dirs|QDir::Files
//                               |QDir::Readable|QDir::Writable
//                               |QDir::Hidden|QDir::NoDotAndDotDot
//                               ,QDir::Name);
//    while(fileList.size()>0)//跳出条件
//    {
//        int infoNum=fileList.size();
//        for(int i=infoNum-1;i>=0;i--)
//        {
//            curFile=fileList[i];
//            if(curFile.isFile())//如果是文件，删除文件
//            {
//                QFile fileTemp(curFile.filePath());
//                fileTemp.remove();
//                fileList.removeAt(i);
//            }
//            if(curFile.isDir())//如果是文件夹
//            {
//                QDir dirTemp(curFile.filePath());
//                QFileInfoList fileList1=dirTemp.entryInfoList(QDir::Dirs|QDir::Files
//                                                              |QDir::Readable|QDir::Writable
//                                                              |QDir::Hidden|QDir::NoDotAndDotDot
//                                                              ,QDir::Name);
//                if(fileList1.size()==0)//下层没有文件或文件夹
//                {
//                    dirTemp.rmdir(".");
//                    fileList.removeAt(i);
//                }
//                else//下层有文件夹或文件
//                {
//                    for(int j=0;j<fileList1.size();j++)
//                    {
//                        if(!(fileList.contains(fileList1[j])))
//                            fileList.append(fileList1[j]);
//                    }
//                }
//            }
//        }
//    }
//   return true;



   QDir directory(dirName);
    if (!directory.exists())
    {
        return true;
    }


    QString srcPath = QDir::toNativeSeparators(dirName);
    if (!srcPath.endsWith(QDir::separator()))
        srcPath += QDir::separator();


    QStringList fileNames = directory.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
    bool error = false;
    for (QStringList::size_type i=0; i != fileNames.size(); ++i)
    {
        QString filePath = srcPath + fileNames.at(i);
        QFileInfo fileInfo(filePath);
        if (fileInfo.isFile() || fileInfo.isSymLink())
        {
            QFile::setPermissions(filePath, QFile::WriteOwner);
            if (!QFile::remove(filePath))
            {
                qDebug() << "remove file" << filePath << " faild!";
                error = true;
            }
        }
        else if (fileInfo.isDir())
        {
            if (!DeleteSpecificFolder(filePath))
            {
                error = true;
            }
        }
    }


    if (!directory.rmdir(QDir::toNativeSeparators(directory.path())))
    {
        qDebug() << "remove dir" << directory.path() << " faild!";
        error = true;
    }
    return !error;

   //头文件包含
//   #include <QDir>
//   #include <QFileInfo>
//   #include <QString>
//   #include <QList>
//   #include <QFileInfo>
//   #include <QFile>

}
//初始化程序
QString caeglobalFunction::InitializationProgram(QString m_configfolder, QString m_def,QString Program_def,QString JudgeFile){
    QDir dir;
    QString CurrentPath = dir.currentPath();
    QString m_MainPath;
    //Read Configuration File information
    QStringList SingleList;
    SingleList.clear();
    CsvFileWrite* Writecsvobj=new CsvFileWrite;
    CsvFileParse* ReadCsvobj = new CsvFileParse;

    if(!PathAndFileExists(m_configfolder +"\\"+ m_def,2)){
        SingleList.append(CurrentPath);
        Writecsvobj->sheet.data.clear();
        Writecsvobj->sheet.data.append(SingleList);
        Writecsvobj->generateCSV(m_configfolder +"\\"+ m_def);

        m_MainPath = CurrentPath;
    }
    else{
        ReadCsvobj->parseCSV(m_configfolder +"\\"+ m_def);
        if(ReadCsvobj->sheet.data.size()>0){
            QString Flagstr;
            Flagstr = ReadCsvobj->sheet.data[0][0];
            if(!PathAndFileExists(Flagstr,1)){
                m_MainPath = CurrentPath;
            }
            else{
                m_MainPath = Flagstr;
            }
        }
        else{
            SingleList.append(CurrentPath);
            Writecsvobj->sheet.data.clear();
            Writecsvobj->sheet.data.append(SingleList);
            Writecsvobj->generateCSV(m_configfolder +"\\"+ m_def);

            m_MainPath = CurrentPath;
        }

    }

    if(!PathAndFileExists(m_MainPath + "/" + JudgeFile,2)){
        //BrowseFolder(QString TitleInfo,QString NoticeInfo,QString DefaultDir)
        QString message = "Please select the installation directory of the This Program.This directory format is as follows:***\\"+Program_def;
        for(int i=1;i<3;i++){
            m_MainPath= BrowseFolder("",message,m_MainPath);
            if(PathAndFileExists(m_MainPath + "/" + JudgeFile,2)){
                i=99999999;
            }
        }
    }

    SingleList.clear();
    SingleList.append(m_MainPath);
    Writecsvobj->sheet.data.clear();
    Writecsvobj->sheet.data.append(SingleList);
    Writecsvobj->generateCSV(m_MainPath +"\\"+ m_def);
    Writecsvobj->generateCSV(m_configfolder +"\\"+ m_def);

    return m_MainPath;
}





std::wstring caeglobalFunction::s2ws(const std::string& s){
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    wstring r(buf);
    delete[] buf;
    return r.c_str();
}

LPCWSTR caeglobalFunction::QStringToLPCWSTR(QString orig){
    std::string Openstr_s = QStostring(orig);        //QString 转 string
    std::wstring Openstr_ws = s2ws(Openstr_s);  // Temporary buffer is required
    LPCWSTR Openstr_w = Openstr_ws.c_str();
    return Openstr_w;
//    return (LPCWSTR)Openstr_ws.c_str();
}

bool caeglobalFunction::CopyPathOrFiletoDenspath(QString source ,QString Target, bool coverFileIfExist){
    //Determine the source object is a file or folder
    int Flagint = source.lastIndexOf('.');
    if(Flagint >=0){
        //拷贝文件：
        //if the path of target don't exist,it will creat folder
        //Determine if the folder is present
        int FindPos1 = source.lastIndexOf("/");
        int FindPos2 = source.lastIndexOf("\\");
        int FindReal;
        FindReal = FindPos2;
        if(FindPos1>FindPos2){
            FindReal = FindPos1;
        }
        QString FilePath = source.left(FindReal);
        QDir dir(FilePath);
        bool ok;
        if(!dir.exists()){
            ok = dir.mkpath(FilePath);//创建多级目录
            if(!ok){  //Add Message
                QMessageBox::information(NULL, "Failed to copy file", "Failed to find source file which is "+source+".", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                return false;
            }
        }

        FindPos1 = Target.lastIndexOf("/");
        FindPos2 = Target.lastIndexOf("\\");
        FindReal;
        FindReal = FindPos2;
        if(FindPos1>FindPos2){
            FindReal = FindPos1;
        }
        FilePath = Target.left(FindReal);
        QDir dir2(FilePath);
        if(!dir2.exists()){
            ok = dir2.mkpath(FilePath);//创建多级目录
            if(!ok){  //Add Message
                QMessageBox::information(NULL, "Failed to copy file", "Fail to find target file which is "+Target+".", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                return false;
            }
        }

        //Do module
        Target.replace("\\","/");
        if (source == Target){
            return true;
        }
        if (!QFile::exists(source)){
            return false;
        }
        QDir *createfile     = new QDir;
        bool exist = createfile->exists(Target);
        if (exist){
            if(coverFileIfExist){
                createfile->remove(Target);
            }
        }//end if

        if(!QFile::copy(source, Target))
        {
            return false;
        }
        return true;
    }
    else{
        //拷贝文件夹：
        QDir sourceDir(source);
        QDir targetDir(Target);

        if(!sourceDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
            if(!targetDir.mkdir(targetDir.absolutePath())){
                QMessageBox::information(NULL, "Failed to copy folder", "Failed to find source folder which is "+source+".", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                return false;}
        }
        if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
            if(!targetDir.mkdir(targetDir.absolutePath())){
                QMessageBox::information(NULL, "Failed to copy folder", "Failed to find target folder which is "+Target+".", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                return false;}
        }

        QFileInfoList fileInfoList = sourceDir.entryInfoList();
        foreach(QFileInfo fileInfo, fileInfoList){
            if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
                continue;

            if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
                if(!CopyPathOrFiletoDenspath(fileInfo.filePath(),
                    targetDir.filePath(fileInfo.fileName()),
                    coverFileIfExist))
                    return false;
            }
            else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
                if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                    targetDir.remove(fileInfo.fileName());
                }

                /// 进行文件copy
                if(!QFile::copy(fileInfo.filePath(),
                    targetDir.filePath(fileInfo.fileName()))){
                        return false;
                }
            }
        }
        return true;

    }
}

void caeglobalFunction::OpenPathOrFile(QString str){
//    LPCWSTR Open_L = QStringToLPCWSTR("OPEN");
//    LPCWSTR Target_L = QStringToLPCWSTR(str);
    std::string Openstr_s = QStostring("OPEN");        //QString 转 string
    std::wstring Openstr_ws = s2ws(Openstr_s);  // Temporary buffer is required
    LPCWSTR Openstr_w = Openstr_ws.c_str();

    std::string Openstr_s2 = QStostring(str);        //QString 转 string
    std::wstring Openstr_ws2 = s2ws(Openstr_s2);  // Temporary buffer is required
    LPCWSTR Openstr_w2 = Openstr_ws2.c_str();
    ShellExecute(NULL, Openstr_w,Openstr_w2, NULL, NULL, SW_SHOW);
}

bool caeglobalFunction::CopyDirFiletoSpecifiedcDir(QString origDir,QString destDir,QStringList filters){

    QDir dir(destDir);
    if(!dir.exists()){
        bool ok = dir.mkpath(destDir);//创建多级目录
        if(!ok){  //Add Message
            QMessageBox::information(NULL, "Create folder according to date", "Failed to generate folder which is "+destDir+".", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return false;
        }
    }

    QDir con_dir(origDir);
    //QStringList filters;//过滤需要的文件
    //filters << "*.csv";
    con_dir.setNameFilters(filters);
    //QStringList file_list=con_dir.entryList();//获取指定路径下的所有文件及文件夹
    //QString ProjectConfig=ProjectPath+"/Configure";
    QFileInfoList file_list=con_dir.entryInfoList();//获取指定路径下的所有文件及文件夹
    for(int i=0;i<file_list.size();i++){
       QFile file(file_list[i].absoluteFilePath()) ;
       QString copyfileName=destDir+"/"+file_list[i].fileName();
       QFile exist_file(copyfileName);
       if(exist_file.exists())
       {
           exist_file.remove();
       }
       file.copy(copyfileName);
     }
    return true;
}
