#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "subwindow.h"
#include "subwindow2.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*set size*/
    setMinimumSize(1500, 900); setMaximumSize(1500, 900);

    /*set background*/
    QPixmap pixmap = QPixmap(":/pic/cover.png").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );

    /*set title*/
    this->setWindowTitle("Tank Battle");
    this->setWindowIcon(QIcon(":/pic/cover.png"));
    //this->setWindowIcon(QIcon(":/pic/icon.jpg"));
    /*set icon*/
    ui->pushButton->setStyleSheet("QPushButton{border-image:url(:/pic/start5.png);}" //正常
                                   "QPushButton:hover{border-image:url(:/pic/start6.png);}" //鼠标悬浮
                                  );
    ui->pushButton->setFixedSize(QSize(200,100));//icon size
    ui->pushButton_2->setFixedSize(QSize(200,100));//icon size
    ui->pushButton_2->setStyleSheet("QPushButton{border-image:url(:/pic/EXIT.png);}" //正常
                                   "QPushButton:hover{border-image:url(:/pic/exit2.png);}" //鼠标悬浮
                                  );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setText("hello");
    this->close();
    subWindow *s=new subWindow(this);
    s->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    exit(0);
}
