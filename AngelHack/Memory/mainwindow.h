#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //void on_pushButton_3_clicked();

    //void on_pushButton_5_clicked();

    //void on_pushButton_4_clicked();

    void on_map_display_clicked();

    void on_map_trace_clicked();

    void on_Reading_shugui_clicked();

    void on_Reading_cancel_clicked();

    void on_Preparing_confirm_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
