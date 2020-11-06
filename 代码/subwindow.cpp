#include "subwindow.h"
#include "ui_subwindow.h"
#include "mainwindow.h"
#include "Windows.h"
#include "QKeyEvent"
#include "parameters.h"
subWindow::subWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::subWindow)
{
    ui->setupUi(this);
    //labels=new QLabel[LENGTH*WIDTH];
    this->grabKeyboard();
    //set size
    setMinimumSize(1500, 900); setMaximumSize(1500, 900);
    //set background
    QPalette  palette (this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette( palette );
    /*set title*/
    this->setWindowTitle("Tank Battle");
    this->setWindowIcon(QIcon(":/pic/icon.jpg"));
    //set icons
    ui->pushButton->setStyleSheet("QPushButton{border-image:url(:/pic/1player.png);}" //正常
                                   "QPushButton:hover{border-image:url(:/pic/1playerline.png);}" //鼠标悬浮
                                  );
    ui->pushButton->setFixedSize(QSize(400,100));//icon size
    ui->pushButton_2->setStyleSheet("QPushButton{border-image:url(:/pic/2player.png);}" //正常
                                   "QPushButton:hover{border-image:url(:/pic/2playerline.png);}" //鼠标悬浮
                                  );
    ui->pushButton_2->setFixedSize(QSize(400,100));//icon size
    ui->returnclick->setFixedSize(QSize(200,50));//icon size
    ui->returnclick->setStyleSheet("QPushButton{border-image:url(:/pic/return.png);}" //正常
                                   "QPushButton:hover{border-image:url(:/pic/returnline.png);}" //鼠标悬浮
                                  );

    //load pics
    brick.load(brick_pic);
    sea.load(sea_pic);
    forest.load(forest_pic);
    steel.load(steel_pic);
    black.load(black_pic);
    star.load(star_pic);
    tank1_up.load(":/pic/tank1up.png");
    tank1_dn.load(":/pic/tank1dn.png");
    tank1_left.load(":/pic/tank1left.png");
    tank1_right.load(":/pic/tank1right.png");
    tank2_up.load(":/pic/tank2up.png");
    tank2_dn.load(":/pic/tank2dn.png");
    tank2_left.load(":/pic/tank2left.png");
    tank2_right.load(":/pic/tank2right.png");
    tank3_up.load(":/pic/tank3up.png");
    tank3_dn.load(":/pic/tank3dn.png");
    tank3_left.load(":/pic/tank3left.png");
    tank3_right.load(":/pic/tank3right.png");
    tank4_up.load(":/pic/tank4up.png");
    tank4_dn.load(":/pic/tank4dn.png");
    tank4_left.load(":/pic/tank4left.png");
    tank4_right.load(":/pic/tank4right.png");
    tank5_up.load(":/pic/tank5up.png");
    tank5_dn.load(":/pic/tank5dn.png");
    tank5_left.load(":/pic/tank5left.png");
    tank5_right.load(":/pic/tank5right.png");
    tank6_up.load(":/pic/tank6up.png");
    tank6_dn.load(":/pic/tank6dn.png");
    tank6_left.load(":/pic/tank6left.png");
    tank6_right.load(":/pic/tank6right.png");

    tank_pic.load(":/pic/test.png");
    bomb_pic.load(":/pic/bomb.jpg");
    bullet.load(":/pic/bullet.png");
    gameover_pic.load(":/pic/win.png");
    gameover_pic.load(":/pic/gameover.png");

    startflag=0;
    endflag=0;
    gradesflag=0;
    winflag=0;

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    timer3 = new QTimer(this);
    timer4 = new QTimer(this);

    timer1->start(TANK_SLOW);
    timer2->start(TANK_FAST);
    timer3->start(BULLET_SLOW);
    timer4->start(BULLET_FAST);

    connect(timer1,&QTimer::timeout,this,&subWindow::tank_move_slow);
    connect(timer2,&QTimer::timeout,this,&subWindow::tank_move_fast);
    connect(timer3,&QTimer::timeout,this,&subWindow::bullet_move_slow);
    connect(timer4,&QTimer::timeout,this,&subWindow::bullet_move_fast);
    connect(timer1,&QTimer::timeout,this,&subWindow::showgrades);

    //connect(timer1,&QTimer::timeout,this,&subWindow::keyPressEvent);
    init();
}

subWindow::~subWindow()
{
    delete ui;
}

void subWindow::init()
{
    for (int i = 0; i < 4; i++)
    {
        kill[i] = 0;
        kill_2[i] = 0;
    }
    for (int i = 0; i < 5; i++)
        tools_exist[i] = 0;
    //clock
    tools[0][0] = 30;
    tools[0][1] = 24;
    //tank
    tools[1][0] = 15;
    tools[1][1] = 20;
    //bomb
    tools[2][0] = 26;
    tools[2][1] = 16;

    enemies_num = 10;
    players_num = 1;
    new_num = 0;
    score = 0;
    score_2 = 0;
    gradesflag=0;
    Enemy *e1 = new Enemy(1, 4, 2, 10);
    Enemy *e2 = new Enemy(1, 18, 2, 11);
    Enemy *e3 = new Enemy(1, 32, 2, 12);
    Player *p1 = new Player(0,15, WIDTH-2, 20);
    Player *p2 = new Player(-1,27, WIDTH-2, 21);
    enemies[0] = e1;
    enemies[1] = e2;
    enemies[2] = e3;
    players[0] = p1;
    if(mode==2)
        players[1]=p2;
    else
        players[1] = NULL;
}

void subWindow::on_returnclick_clicked()
{
    endflag=0;
    init();
    Map m;
    startflag=0;
    ui->pushButton->show();
    ui->pushButton_2->show();
    init();
}

void subWindow::tank_move_slow()
{
    for(int i=0;i<3;i++)
    {
        if(enemies[i]!=NULL&&enemies[i]->move_sleep_time==TANK_SLOW)
        {
            enemies[i]->move();
        }
    }
    for(int i=0;i<2;i++)
    {
        if(players[i]!=NULL)
            players[i]->move();

    }
    update();
}
void subWindow::tank_move_fast()
{
    for(int i=0;i<3;i++)
    {
        if(enemies[i]!=NULL&&enemies[i]->move_sleep_time==TANK_FAST)
        {
            enemies[i]->move();
        }
    }
    update();
}

void subWindow::bullet_move(int speed)
{
    for (int i = 0; i < 3; i++)
    {
        if (enemies[i] != NULL)
        {
            if (enemies[i]->bullet_sleep_time==speed)
            {
                if (enemies[i]->bullets != NULL && !enemies[i]->bullets->move())
                {
                    int pos = enemies[i]->bullets->hurt_id;
                    if (pos >= 20 && pos < 30)//player tank
                    {
                        players[pos - 20]->life--;
                        if (players[pos - 20]->life <= 0)
                        {
                            players[pos - 20]->delete_tank();
                            delete players[pos - 20];
                            players[pos - 20] = NULL;
                            players_num--;
                            if (players_num == 0)
                            {
                                if(!endflag)
                                {
                                    for(int k=0;k<4;k++)
                                        score += 100 * (k + 1)*kill[k];
                                    for(int k=0;k<4;k++)
                                        score_2 += 100 * (k + 1)*kill_2[k];
                                }

                                endflag=1;
                                winflag=0;
                            }
                        }
                        else
                        {
                            players[pos - 20]->delete_tank();
                            players[pos - 20]->pos_x = 15 + (pos - 20) * 10;
                            players[pos - 20]->pos_y = 27;
                            players[pos-20]->pre_dir=up;
                        }
                    }
                    else if (pos >= 30 && pos < 40)//enemy bullet
                    {
                        delete enemies[pos - 30]->bullets;
                        enemies[pos - 30]->bullets = NULL;
                    }
                    else if (pos >= 40 && pos < 50)//player bullet
                    {
                        delete players[pos - 40]->bullets;
                        players[pos - 40]->bullets = NULL;
                    }
                    delete enemies[i]->bullets;
                    enemies[i]->bullets = NULL;
                }
            }
        }
        else
        {
            int pos = 0;
            switch (i)
            {
            case 0:
                pos = 4; break;
            case 1:
                pos = 18; break;
            case 2:
                pos = 32; break;
            }
            if (new_num == 6)
            {
                Enemy *e = new Enemy(4, pos, 2, 10 + i);
                enemies[i] = e;
            }
            else if (new_num >= 4 && new_num <= 5)
            {
                Enemy *e = new Enemy(2, pos, 2, 10 + i);
                enemies[i] = e;
            }
            else if (new_num >= 2 && new_num <= 3)
            {
                Enemy *e = new Enemy(3, pos, 2, 10 + i);
                enemies[i] = e;
            }
            else if (new_num >= 0 && new_num <= 1)
            {
                Enemy *e = new Enemy(2, pos, 2, 10 + i);
                enemies[i] = e;
            }
            new_num++;
        }
    }
    for (int i = 0; i < 2; i++)
    {
        if (players[i] != NULL)
        {
            for (int k = 0; k < 3; k++)
            {
                if (tools_exist[k] == 1&&
                        (players[i]->pos_x-2<=tools[k][0]&&players[i]->pos_x+2>=tools[k][0])&&
                         (players[i]->pos_y-2 <= tools[k][1]&&players[i]->pos_y+2>=tools[k][1]))
                {
                    switch (k)
                    {
                    case 0://clock
                        //clock++;
                        break;
                    case 1://tank
                        players[i]->life++;
                        break;
                    case 2://bomb
                        for (int j = 0; j < 3; j++)
                        {
                            if (i == 0)
                                kill[enemies[j]->type - 1]++;
                            else
                                kill_2[enemies[j]->type - 1]++;
                            if (enemies[j]->bullets != NULL)
                                enemies[j]->bullets->delete_bullet();
                            enemies[j]->delete_tank();
                            delete enemies[j];
                            enemies[j] = NULL;
                            enemies_num--;
                        }
                        break;
                    }
                    tools_exist[k] = 2;
                }
            }

            if (players[i]->bullet_sleep_time==speed)
            {
                if (players[i]->bullets != NULL && !players[i]->bullets->move())
                {

                    int pos = players[i]->bullets->hurt_id;
                    if (pos >= 10 && pos < 20)//enemy tanks
                    {
                        if (enemies[pos - 10]->life <= 1)
                        {
                            if(i==0)
                                kill[enemies[pos - 10]->type - 1]++;
                            else
                                kill_2[enemies[pos - 10]->type - 1]++;
                            if(enemies[pos - 10]->bullets!=NULL)
                                enemies[pos - 10]->bullets->delete_bullet();
                            delete enemies[pos - 10]->bullets;
                            enemies[pos - 10]->bullets=NULL;
                            enemies[pos - 10]->delete_tank();
                            delete enemies[pos - 10];
                            enemies[pos - 10] = NULL;
                            enemies_num--;
                        }
                        else
                            enemies[pos - 10]->life--;
                    }
                    else if(pos>=30&&pos<40)//enemy bullet
                    {
                        delete enemies[pos - 30]->bullets;
                        enemies[pos - 30]->bullets = NULL;
                    }
                    else if (pos >= 40 && pos < 50)//player bullet
                    {
                        delete players[pos - 40]->bullets;
                        players[pos - 40]->bullets = NULL;
                    }
                    delete players[i]->bullets;
                    players[i]->bullets = NULL;
                }
            }
        }
    }
    switch (enemies_num)
    {
    case 9:
        if(tools_exist[1]==0)
            tools_exist[1] = 1;
        break;
    case 4:
        if (tools_exist[1] == 0)
            tools_exist[1] = 1;
        break;
    case 7:
        if (tools_exist[2] == 0)
            tools_exist[2] = 1;
        break;
    }
    for (int i = 0; i < 3; i++)
    {
        if (tools_exist[i] == 1)
        {
            switch (i)
            {
            case 0:
                ;//print_symbol("时钟", 7, tools[i][0], tools[i][1]);
                break;
            case 1:
                Map::map[LENGTH*tools[i][1]+tools[i][0]]=TOOL_TANK;break;
            case 2:
                Map::map[LENGTH*tools[i][1]+tools[i][0]]=TOOL_BOMB;break;
            }
        }
        else
            if(Map::map[LENGTH*tools[i][1]+tools[i][0]]>=60)
            Map::map[LENGTH*tools[i][1]+tools[i][0]]=0;
    }
    if (Map::map[LENGTH*(WIDTH - 3) + LENGTH / 2-1] == 0||
            Map::map[LENGTH*(WIDTH - 3) + LENGTH / 2-1] == 0||
            Map::map[LENGTH*(WIDTH - 3) + LENGTH / 2] == 0||
            Map::map[LENGTH*(WIDTH - 2) + LENGTH / 2] == 0)
    {
        if(!endflag)
        {
            for(int k=0;k<4;k++)
                score += 100*(k+1)*kill[k];
            for(int k=0;k<4;k++)
                score_2 += 100 * (k + 1)*kill_2[k];
        }
        endflag=1;

    }
    if(enemies_num==0)
    {
        if(!endflag)
        {
            for(int k=0;k<4;k++)
                score += 100 * (k + 1)*kill[k];
            for(int k=0;k<4;k++)
                score_2 += 100 * (k + 1)*kill_2[k];
        }
        endflag=1;
        winflag=1;
    }
    update();
}
void subWindow::bullet_move_fast()
{
    bullet_move(BULLET_FAST);
}
void subWindow::bullet_move_slow()
{
    bullet_move(BULLET_SLOW);
}
void subWindow::paintEvent(QPaintEvent *event)
{
    painter.begin(this);
    if(startflag&&!endflag)
    {
        for(int i=0;i<WIDTH;i++)
        {
            for(int j=0;j<LENGTH;j++)
            {
                if(Map::map[i*LENGTH+j]>=30&&Map::map[i*LENGTH+j]<50)
                {
                    painter.drawPixmap(SIZE*j, SIZE*i, 30, 30,bullet);
                }
                switch(Map::map[i*LENGTH+j])
                {
                case EMPTY:
                    painter.drawPixmap(SIZE*j, SIZE*i, 30, 30,black);break;
                case STAR:
                    if(j==LENGTH/2-1&&i==WIDTH-3)
                        painter.drawPixmap(SIZE*j, SIZE*i, 60, 60,star);
                    break;
                case BRICK_WALL:
                    painter.drawPixmap(SIZE*j, SIZE*i, 30, 30,brick);break;
                case STEEL_WALL:
                    painter.drawPixmap(SIZE*j, SIZE*i, 30, 30,steel);break;
                case FOREST:
                    painter.drawPixmap(SIZE*j, SIZE*i, 30, 30,forest);break;
                case SEA:
                    painter.drawPixmap(SIZE*j, SIZE*i, 30, 30,sea);break;
                case TANK1_UP:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank1_up);break;
                case TANK1_DN:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank1_dn);break;
                case TANK1_LEFT:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank1_left);break;
                case TANK1_RIGHT:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank1_right);break;
                case TANK2_UP:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank2_up);break;
                case TANK2_DN:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank2_dn);break;
                case TANK2_LEFT:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank2_left);break;
                case TANK2_RIGHT:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank2_right);break;
                case TANK3_UP:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank3_up);break;
                case TANK3_DN:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank3_dn);break;
                case TANK3_LEFT:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank3_left);break;
                case TANK3_RIGHT:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank3_right);break;
                case TANK4_UP:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank4_up);break;
                case TANK4_DN:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank4_dn);break;
                case TANK4_LEFT:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank4_left);break;
                case TANK4_RIGHT:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank4_right);break;
                case TANK5_UP:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank5_up);break;
                case TANK5_DN:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank5_dn);break;
                case TANK5_LEFT:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank5_left);break;
                case TANK5_RIGHT:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank5_right);break;
                case TANK6_UP:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank6_up);break;
                case TANK6_DN:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank6_dn);break;
                case TANK6_LEFT:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank6_left);break;
                case TANK6_RIGHT:
                    painter.drawPixmap(SIZE*(j-1), SIZE*(i-1), 90, 90,tank6_right);break;
                case BULLET1:
                    painter.drawPixmap(SIZE*j, SIZE*i, 30, 30,bullet);break;
                case TOOL_TANK:
                    painter.drawPixmap(SIZE*j, SIZE*i, 30, 30,tank_pic);break;
                case TOOL_BOMB:
                    painter.drawPixmap(SIZE*j, SIZE*i, 30, 30,bomb_pic);break;
                }

            }
        }

        QFont ft;
        ft.setPointSize(15);
        painter.setFont(ft);
        painter.setPen(Qt::white);
        painter.drawText(1300,100,tr("Enemies"));
        painter.drawText(1330,150,QString::number(enemies_num));
        painter.drawText(1300,250,tr("Player 1"));
        painter.drawText(1330,300,tr("HP:"));
        painter.setPen(Qt::red);
        painter.drawText(1380,300,QString::number(players[0]->life));
        painter.setPen(Qt::white);
        painter.setPen(Qt::blue);
        painter.drawText(1280,350,tr("W"));
        painter.drawText(1250,400,tr("A S D 移动坦克"));
        painter.drawText(1270,450,tr("J射击"));
        if (mode == 2)
        {
            painter.setPen(Qt::white);
            painter.drawText(1300,550,tr("Player 2"));
            painter.drawText(1330,600,tr("HP:"));
            painter.setPen(Qt::red);
            painter.drawText(1380,600,QString::number(players[1]->life));
            painter.setPen(Qt::white);
            painter.setPen(Qt::blue);
            painter.drawText(1280,650,tr("up"));
            painter.drawText(1210,700,tr("left dn right 移动坦克"));
            painter.drawText(1300,750,tr("space射击"));
        }
    }
    else if(endflag)
    {
        QFont ft;
        ft.setPointSize(20);
        painter.setFont(ft);
        painter.setPen(Qt::white);
        painter.drawText(100,100,tr("Player 1:"));
        painter.drawPixmap(150, 150, 60, 60,tank1_up);
        painter.drawPixmap(150, 250, 60, 60,tank2_up);
        painter.drawPixmap(150, 350, 60, 60,tank3_up);
        painter.drawPixmap(150, 450, 60, 60,tank4_up);
        for (int i = 0; i < 4; i++)
        {
            painter.drawText(250,200+100*i,tr("*"));
            painter.drawText(300,200+100*i,QString::number(kill[i]));
            painter.drawText(350,200+100*i,tr("="));
            painter.drawText(400,200+100*i,QString::number(100 * (i + 1)*kill[i]));
        }
        painter.drawText(100,600,tr("Final Score:"));
        painter.drawText(350,600,QString::number(score));

        if(mode==2)
        {
            painter.drawText(800,100,tr("Player 2:"));
            painter.drawPixmap(850, 150, 60, 60,tank1_up);
            painter.drawPixmap(850, 250, 60, 60,tank2_up);
            painter.drawPixmap(850, 350, 60, 60,tank3_up);
            painter.drawPixmap(850, 450, 60, 60,tank4_up);
            for (int i = 0; i < 4; i++)
            {
                painter.drawText(950,200+100*i,tr("*"));
                painter.drawText(1000,200+100*i,QString::number(kill_2[i]));
                painter.drawText(1050,200+100*i,tr("="));
                painter.drawText(1100,200+100*i,QString::number(100 * (i + 1)*kill_2[i]));
            }
            painter.drawText(800,600,tr("Final Score:"));
            painter.drawText(1050,600,QString::number(score_2));
        }
        if(winflag)
            painter.drawPixmap(600, 700, 60, 60,tank2_up);
        else
            painter.drawPixmap(500, 700,400, 100,gameover_pic);
    }
    else
    {
        ui->returnclick->hide();
    }
    painter.end();
}
void subWindow::showgrades()
{
    if(endflag)
        gradesflag=1;
}

void subWindow::gameover()
{
    endflag=1;
}
void subWindow::keyPressEvent(QKeyEvent *event)
{
    if(players[0]!=NULL)
    {
            switch(event->key())
            {
            case Qt::Key_S:
                players[0]->dir=down;break;
            case Qt::Key_W:
                players[0]->dir=up;break;
            case Qt::Key_A:
                players[0]->dir=left;break;
            case Qt::Key_D:
                players[0]->dir=right;break;
            case Qt::Key_J:
                players[0]->shoot();break;
            }
            update();
    }
    if(players[1]!=NULL)
    {
            switch(event->key())
            {
            case Qt::Key_Down:
                players[1]->dir=down;break;
            case Qt::Key_Up:
                players[1]->dir=up;break;
            case Qt::Key_Left:
                players[1]->dir=left;break;
            case Qt::Key_Right:
                players[1]->dir=right;break;
            case Qt::Key_Space:
                players[1]->shoot();break;
            }
            update();
    }

}

void subWindow::on_pushButton_clicked()
{

    mode=1;
    Map m;
    init();
    startflag=1;
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->returnclick->show();
}

void subWindow::on_pushButton_2_clicked()
{

    Map m;
    mode=2;
    init();
    startflag=1;
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->returnclick->show();
}
