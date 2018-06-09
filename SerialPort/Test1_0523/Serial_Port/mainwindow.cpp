#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //查找可用的串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->PortBox->addItem(serial.portName());
            serial.close();
        }
    }
    //设置波特率下拉菜单默认显示第7个，19600
    ui->BaudBox->setCurrentIndex(4);
    //关闭发送按钮使能
    ui->sendButton->setEnabled((false));
    qDebug()<<tr("界面设定成功");
    this->setWindowTitle("慢阻肺健康小助手");
    //ui->centralWidget->setMaximumSize(600,500);//限定大小
    //ui->centralWidget->setMinimumSize(600,500);//限定大小

}

MainWindow::~MainWindow()
{
    delete ui;
}

int Bytes_to_int(char high, char low)
{
    char d = (char)((high<<8)|(0x00FF & low));
    return (int)((d << 16) >> 16);
}
//清空接收串口
void MainWindow::on_clearButton_clicked()
{
    ui->RecvEdit->clear();
}
//发送数据
void MainWindow::on_sendButton_clicked()
{
    serial->write(ui->TransEdit->toPlainText().toLatin1());
}


//读取接收到的数据
void MainWindow::Read_Data()
{
    QByteArray buf;                //字节数组
    uint8_t length = 0;length = length;
    unsigned char FEV1_temp[2],FEV6_temp[2],FVC_temp[2],PEF_temp[2];
    unsigned char SPO2_temp[2],PR_temp[2],ETCO2_temp[2],Insp_CO2_temp[2],Res_Rate_temp[2];
    uint16_t FEV1=0,FEV6=0,FVC=0,PEF=0;
    uint16_t SPO2=0,PR=0,ETCO2=0,Insp_CO2=0,Res_Rate=0;
    buf = serial->readAll();
    if(!buf.isEmpty())
    {
        QString str = ui->RecvEdit->toPlainText();//获取多行文本的数据
        str += tr(buf);            //
        ui->RecvEdit->clear();
        ui->RecvEdit->append(str); //在文本接收末端接收str数据
    }
    length = buf.size();
    qDebug()<<" the length is"<<length<<" "<<buf<<"\n";
    if(buf[0]==0xff && buf[1]==0xfe)
    {
        FEV1_temp[0] = buf[2];FEV1_temp[1] = buf[3];
        FEV1 = Bytes_to_int(FEV1_temp[0],FEV1_temp[1]);
        FEV6_temp[0] = buf[4];FEV6_temp[1] = buf[5];
        FEV6 = Bytes_to_int(FEV6_temp[0],FEV6_temp[1]);
        FVC_temp[0]  = buf[6];FVC_temp[1]  = buf[7];
        FVC = Bytes_to_int(FVC_temp[0],FVC_temp[1]);
        PEF_temp[0]  = buf[8];PEF_temp[1]  = buf[9];
        PEF = Bytes_to_int(PEF_temp[0],PEF_temp[1]);
        SPO2_temp[0] = buf[10];SPO2_temp[1] = buf[11];
        SPO2 = Bytes_to_int(SPO2_temp[0], SPO2_temp[1]);
        PR_temp[0]   = buf[12];PR_temp[1] = buf[13];
        PR   = Bytes_to_int(PR_temp[0], PR_temp[1]);
        ETCO2_temp[0]  = buf[14];ETCO2_temp[1]  = buf[15];
        ETCO2 = Bytes_to_int(ETCO2_temp[0],ETCO2_temp[1]);
        Insp_CO2_temp[0] = buf[16];Insp_CO2_temp[1]  = buf[17];
        Insp_CO2 = Bytes_to_int(Insp_CO2_temp[0],Insp_CO2_temp[1]);
        Res_Rate_temp[0]  = buf[18];Res_Rate_temp[1]  = buf[19];
        Res_Rate = Bytes_to_int(Res_Rate_temp[0],Res_Rate_temp[1]);
        qDebug()<<"FEV1 "<<FEV1<<"FEV6 "<<FEV6<<"FEV6 "<<FVC<<"FVC "<<PEF<<"PEF "<<"\n";
        qDebug()<<"SPO2 "<<SPO2<<"PR "<<PR<<"ETCO2 "<<ETCO2<<"Inso_CO2 "<<Insp_CO2<<"Res_Rate "<<Res_Rate<<"\n";
    }
    buf.clear();
}

void MainWindow::on_openButton_clicked()
{
    long FEV1_ct=0,FVC_ct=0,FEV1_FVC_ct=0,PEF_ct=0,FEF25_ct=0,FEF50_ct=0,FEF75_ct=0;
    if(ui->openButton->text()==tr("打开串口"))
    {
        serial = new QSerialPort;
        serial->setPortName(ui->PortBox->currentText());
        serial->open(QIODevice::ReadWrite);
        serial->setBaudRate(ui->BaudBox->currentText().toInt());
        switch(ui->BitNumBox->currentIndex())
        {
            case 8:serial->setDataBits(QSerialPort::Data8);break;       
            default:break;
        }
        switch(ui->ParityBox->currentIndex())
        {
            case 0:serial->setParity(QSerialPort::NoParity);break;
            default:break;
        }
        switch(ui->StopBox->currentIndex())
        {
            case 1:serial->setStopBits(QSerialPort::OneStop);break;
            case 2:serial->setStopBits(QSerialPort::TwoStop);break;
        }
        serial->setFlowControl(QSerialPort::NoFlowControl);
        //关闭设置菜单使能
        ui->PortBox->setEnabled(false);
        ui->BaudBox->setEnabled(false);
        ui->BitNumBox->setEnabled(false);
        ui->ParityBox->setEnabled(false);
        ui->StopBox->setEnabled(false);
        ui->openButton->setText(tr("关闭串口"));
        ui->sendButton->setEnabled(true);
        //连接信号槽
        QObject::connect(serial,&QSerialPort::readyRead,this, &MainWindow::Read_Data);
        uint16_t g_age,g_height,g_weight;
        g_age = ui->AgeEdit->text().toInt();
        g_height = ui->HeightEdit->text().toInt();
        g_weight = ui->WeightEdit->text().toInt();
        qDebug()<<g_age<<" "<<g_height<<" "<<g_weight;
        QString g_male;qint8 g_male_value;
        g_male   = ui->MaleBox_2->currentText();
        qDebug()<<g_male;
        g_male_value = (g_male=="男" ? 1:0);
        //给出预计值公式
        FEV1_ct  = (-1.653 + g_male_value*0.564 + (-0.022)*g_age + 0.033*g_height)*1000;
        FVC_ct   = (-3.091 + g_male_value*0.702 + (-0.020)*g_age + 0.044*g_height)*1000;
        FEV1_FVC_ct = (99.121+ (-0.138)*g_age + (-0.147)*g_weight);
        PEF_ct   = (-0.287 + g_male_value*2.249 + (-0.026)*g_age + 0.039*g_height + 0.026*g_weight)*1000;
        FEF25_ct = (-0.338 + g_male_value*1.784 + (-0.018)*g_age + 0.043*g_height)*1000;
        FEF50_ct = (0.836 + g_male_value*0.572 + (-0.027)*g_age + 0.025*g_height)*1000;
        FEF75_ct = (-1.542 + g_male_value*0.135 + (-0.029)*g_age + 0.027*g_height)*1000;
        ui->FEV1_Edit->text()= FEV1_ct;ui->FVC_Edit->text()=FVC_ct;ui->FEV1_FVC_Edit->text() = FEV1_FVC_ct;
        qDebug()<<FEV1_ct;
        QString str = QString::number(FEV1_ct,10);ui->FEV1_Edit->setText(str);
        str = QString::number(FVC_ct,10);ui->FVC_Edit->setText(str);
        str = QString::number(FEV1_FVC_ct,10);ui->FEV1_FVC_Edit->setText(str);
        str = QString::number(PEF_ct,10);ui->PEF_Edit->setText(str);
        str = QString::number(FEF25_ct,10);ui->FEF25_Edit->setText(str);
        str = QString::number(FEF50_ct,10);ui->FEF50_Edit->setText(str);
        str = QString::number(FEF75_ct,10);ui->FEF75_Edit->setText(str);


        qDebug()<<g_male_value<<FEV1_ct<<FEV1_FVC_ct;
    }
    else
    {
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();
        //恢复使能
        ui->PortBox->setEnabled(true);
        ui->BaudBox->setEnabled(true);
        ui->BitNumBox->setEnabled(true);
        ui->ParityBox->setEnabled(true);
        ui->StopBox->setEnabled(true);
        ui->openButton->setText(tr("打开串口"));
        ui->sendButton->setEnabled(false);
    }
}
