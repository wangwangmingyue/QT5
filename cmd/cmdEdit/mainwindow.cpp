#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>           //启动一个进程
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMaximumSize(400,200);
    this->setMinimumSize(400,200);
    this->setWindowTitle("命令行");
    QObject::connect(ui->cmdLineEdit,SIGNAL(returnPressed()),this,SLOT(on_submitButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submitButton_clicked()
/* QProcess *myProcess = new QProcess(parent);
   myProcess->start(program, arguments);
*/
{
   QProcess *process = new QProcess;
   QString startProgram = ui->cmdLineEdit->text();
   process->start(startProgram.trimmed());//清除空格
   //返回了回车键
   MainWindow::connect(ui->cmdLineEdit,SIGNAL(returnPressed()),this,SLOT(on_submitButton_clicked()));
   ui->cmdLineEdit->clear();
   //this->close();
}




