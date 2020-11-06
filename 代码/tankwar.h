#pragma once
#ifndef TANKWAR_H
#define TANKWAR_H
#include <QPainter>
#define up 1
#define down 2

class Bullet
{
    int pos_x;//子弹当前横坐标
    int pos_y;//子弹当前纵坐标
    int pre_x;//子弹之前横坐标
    int pre_y;//子弹之前前纵坐标
    int sleep_time;//子弹移动的间隔时间
    int dir;//子弹移动方向
    int type;//子弹种类
    int master;//子弹所属的坦克
    int hurt_id;//子弹命中目标id
public:
    Bullet();//构造函数
    bool move();//控制子弹的移动
    void delete_bullet();//子弹在地图上消失
    friend class Tank;
    friend class subWindow;
};

class Tank
{
protected:
    int type;//种类,1轻型坦克,2装甲车,3反坦克炮，4重型坦克
    int dir;//移动方向
    int pre_dir;//之前的移动方向
    int life;//生命值
    int atk;//攻击力
    int move_sleep_time;//移动速度
    int bullet_sleep_time;//子弹速度
    int pos_x;//横坐标
    int pos_y;//纵坐标
    int id;//坦克id
    Bullet* bullets;//射出的子弹
public:
    Tank();
    Tank(int t, int x, int y, int i);//构造函数
    ~Tank()//析构函数
    {
        delete bullets;
    }
    void basic_move();//控制坦克的移动
    void shoot();//射出子弹
    void delete_tank();//使坦克在地图上消失

    friend class subWindow;
};

class Map
{
    static int *map;//存储地图数据
public:
    Map();//地图的初始化
    friend class subWindow;
    friend class Tank;
    friend class Player;
    friend class Enemy;
    friend class Bullet;

};


class Enemy :public Tank
{
public:
    Enemy(int t, int x, int y,int i) :Tank(t, x, y,i)//构造函数
    {
        dir = down;
        pre_dir = dir;
        switch (t)
        {
        case 1:
            life = 1;
            atk = 1;
            move_sleep_time = 300;
            bullet_sleep_time = 80;
            break;
        case 2:
            life = 2;
            atk = 1;
            move_sleep_time = 200;
            bullet_sleep_time = 50;
            break;
        case 3:
            life = 2;
            atk = 2;
            move_sleep_time = 300;
            bullet_sleep_time = 50;
            break;
        case 4:
            life = 3;
            atk = 2;
            move_sleep_time = 300;
            bullet_sleep_time = 80;
            break;
        }
    }
    void move();//根据一定策略控制敌方坦克的移动
    friend class Bullet;
    friend class Control;
};

class Player :public Tank
{
public:
    Player(int t,int x, int y,int i) :Tank(t, x, y,i)//构造函数
    {
        dir = up;
        pre_dir = dir;
        life = 10;
        atk = 1;
        move_sleep_time = 300;
        bullet_sleep_time = 80;
    }
    void move();//根据玩家的键盘输入控制玩家坦克的移动
    friend class Bullet;
};

#endif // TANKWAR_H
