#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPainter>

#include "tankwar.h"

#include <QTimer>
namespace Ui {
class subWindow;
}

class subWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit subWindow(QWidget *parent = nullptr);
    ~subWindow();

    void paintEvent(QPaintEvent *event);
    QPainter painter;
    void init();//初始化
    void gameover();

private slots:
    void on_returnclick_clicked();
    void tank_move_slow();
    void tank_move_fast();
    void bullet_move_slow();
    void bullet_move_fast();
    void bullet_move(int speed);
    void keyPressEvent(QKeyEvent *ev);
    void showgrades();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void sendsignal();
private:
    Ui::subWindow *ui;
    QString brick_pic=":/pic/brick.jpg";
    QString forest_pic=":/pic/forest.jpg";
    QString sea_pic=":/pic/sea2.jpg";
    QString steel_pic=":/pic/brick2.png";
    QString black_pic=":/pic/black.png";
    QString star_pic=":/pic/star.png";
    QString tank1up_pic=":/pic/tank2up.png";
    QPixmap brick;
    QPixmap sea;
    QPixmap forest;
    QPixmap steel;
    QPixmap black;
    QPixmap star;
    QPixmap tank1_up;
    QPixmap tank1_dn;
    QPixmap tank1_right;
    QPixmap tank1_left;
    QPixmap tank2_up;
    QPixmap tank2_dn;
    QPixmap tank2_left;
    QPixmap tank2_right;
    QPixmap tank3_up;
    QPixmap tank3_dn;
    QPixmap tank3_right;
    QPixmap tank3_left;
    QPixmap tank4_up;
    QPixmap tank4_dn;
    QPixmap tank4_right;
    QPixmap tank4_left;
    QPixmap tank5_up;
    QPixmap tank5_dn;
    QPixmap tank5_right;
    QPixmap tank5_left;
    QPixmap tank6_up;
    QPixmap tank6_dn;
    QPixmap tank6_right;
    QPixmap tank6_left;
    QPixmap bullet;
    QPixmap win_pic;
    QPixmap gameover_pic;
    QPixmap clock_pic;
    QPixmap bomb_pic;
    QPixmap tank_pic;
    Map m;
    Tank t;
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;
    QTimer *timer4;
    QTimer *timer5;

    Enemy* enemies[3];//地图上现有的敌方坦克
    Player* players[2];//玩家坦克
    int enemies_num;//剩余的敌方坦克数量
    int new_num;//新构造的敌方坦克数量
    int players_num;//目前存活的玩家数量
    int score;//玩家1得分
    int score_2;//玩家2得分
    int mode;//1单人模式,2双人模式
    int kill[4];//玩家1击杀敌方坦克情况
    int kill_2[4];//玩家2击杀敌方坦克情况
    int tools[5][2];//道具坐标
    int tools_exist[5];//道具存在情况
    bool startflag;
    bool endflag;
    bool gradesflag;
    bool winflag;
};

#endif // SUBWINDOW_H
