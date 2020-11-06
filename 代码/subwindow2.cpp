#include "subwindow2.h"
#include "ui_subwindow2.h"

subWindow2::subWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::subWindow2)
{
    ui->setupUi(this);
}

subWindow2::~subWindow2()
{
    delete ui;
}
