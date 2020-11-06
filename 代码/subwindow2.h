#ifndef SUBWINDOW2_H
#define SUBWINDOW2_H

#include <QMainWindow>

namespace Ui {
class subWindow2;
}

class subWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit subWindow2(QWidget *parent = nullptr);
    ~subWindow2();

private:
    Ui::subWindow2 *ui;
};

#endif // SUBWINDOW2_H
