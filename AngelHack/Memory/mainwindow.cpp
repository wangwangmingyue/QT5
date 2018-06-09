#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_map_display_clicked()
{
    QImage *ppm = new QImage("D:\\ProgramData\\Qt\\AngelHack\\Memory\\photos\\Chinesemap1.bmp");
    ui->label_2->setPixmap(QPixmap::fromImage(*ppm));
    ui->Walking_cityEdit->setText("9");ui->Walking_miles->setText("5000");
    ui->TheEasternCity->setText("北京");ui->TheWesternCity->setText("西宁");
    ui->TheNorthCity->setText("北京");ui->TheSouthCity->setText("深圳");
    ui->TheLongTimeCity->setText("北京");
    ui->Walking_Province->setText("9");
    //ui->label_2->setGeometry(100,100,40,40);
}


void MainWindow::on_map_trace_clicked()
{
    ui->Walking_Edit2->setText("9");ui->Keywords2->setText("开心、壮观");
    ui->Place_Edit2->setText("北京");ui->Partner->setText("Xiaoma");
    ui->Pre_details2->setText("北京是中华人民共和国的首都、直辖市、国家中心城市、超大城市、国际大都市，全国政治中心、文化中心、国际交往中心、科技创新中心，是中国共产党中央委员会、中华人民共和国中央人民政府、全国人民代表大会、中国人民政治协商会议全国委员会、中华人民共和国中央军事委员会所在地，也是中部战区司令部驻地");
}

void MainWindow::on_Reading_shugui_clicked()
{
    QImage *ppmm = new QImage("D:\\ProgramData\\Qt\\AngelHack\\Memory\\photos\\shugui.jpg");
    ui->label_6->setPixmap(QPixmap::fromImage(*ppmm));
    //ui->
    ui->Reading_keywords->setText("文学");
    ui->Reading_bookname_Edit->setText("平凡的世界");
    ui->Reading_Author->setText("路遥");
    ui->Reading_Pages->setText("1040000");
    ui->Read_beizhu->setText("这是一部全景式地表现中国当代城乡社会生活的长篇小说");
    //ui->label_2->setGeometry(100,100,40,40);
}

void MainWindow::on_Reading_cancel_clicked()
{
    QImage *ppmm = new QImage("D:\\ProgramData\\Qt\\AngelHack\\Memory\\photos\\shugui.jpg");
    ui->label_6->setPixmap(QPixmap::fromImage(*ppmm));
    QString str = ui->BookChoose->currentText();
    if(str=="平凡的世界")
    {
       qDebug()<<"平凡的世界";
       ui->Reading_author2->setText("路遥");
       ui->Reading_background->setText("该书以中国70年代中期到80年代中期十年间为背景，通过复杂的矛盾纠葛，以孙少安和孙少平两兄弟为中心，刻画了当时社会各阶层众多普通人的形象；劳动与爱情、挫折与追求、痛苦与欢乐、日常生活与巨大社会冲突纷繁地交织在一起，深刻地展示了普通人在大时代历史进程中所走过的艰难曲折的道路。");


       ui->Reading_pages2->setText("1040000");
       ui->Reading_detail2->setText("少安最终没和润叶在一起，不喜欢爱情悲剧。--2016.05.02");

    }
}

void MainWindow::on_pushButton_12_clicked()
{
    QString str = ui->Pre_choose->currentText();
    if(str=="AngelHack")
    {
    qDebug()<<"success";
    QImage *ppmm = new QImage("D:\\ProgramData\\Qt\\AngelHack\\Memory\\photos\\AngelHack.jpg");
    ui->Prepare_photos_2->setPixmap(QPixmap::fromImage(*ppmm));
    QImage *ppmm2 = new QImage("D:\\ProgramData\\Qt\\AngelHack\\Memory\\photos\\Angel_Hack2.jpg");
    ui->label_4->setPixmap(QPixmap::fromImage(*ppmm2));
    ui->textBrowser_2->setText("外国人很多的一次编程比赛，英语得到了提高，哈哈哈");
    //ui->Prepare_photos->setGeometry(100,100,40,40);
    }
}
