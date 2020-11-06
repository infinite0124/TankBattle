#include<iostream>
#include<Windows.h>
#include<ctime>
#include<assert.h>

#include "subwindow.h"
using namespace std;

#include "parameters.h"

int* Map::map= new int[LENGTH*WIDTH];

Bullet::Bullet()
{
    type = 1;
    hurt_id = 0;
    pre_x = 0;
    pre_y = 0;
}
bool Bullet::move()
{
    if (pre_x)
    {
        if (Map::map[pre_y*LENGTH + pre_x]>=30)//bullet
        {
            Map::map[pre_y*LENGTH + pre_x] = 0;
            Map::map[pre_y*LENGTH + pre_x] = 0;
        }
    }
    int pos = LENGTH*pos_y + pos_x;
    switch (Map::map[pos])
    {
    case EMPTY:
        Map::map[pos_y*LENGTH + pos_x] = master+20;
        break;
    case BRICK_WALL:
        if (pos_x <= 0 || pos_x >= LENGTH - 1 || pos_y <= 0 || pos_y >= WIDTH - 1)
            return 0;
        Map::map[pos] = 0;
        return 0;
    case STEEL_WALL:
        if (type == 2)
            Map::map[pos] = 0;
        return 0;
    case STAR:
        Map::map[pos] = 0;
        return 0;
    case SEA:
        return 0;
    case FOREST:
        break;
    default:
        hurt_id = Map::map[pos];
        if (hurt_id >= 30)//bullet
            Map::map[pos] = 0;
        return 0;
    }
    pre_x = pos_x;
    pre_y = pos_y;
    switch (dir)
    {
    case up:
        pos_y -= 1; break;
    case down:
        pos_y += 1; break;
    case left:
        pos_x -= 1; break;
    case right:
        pos_x += 1; break;
    default:
        return 0;
    }
    return 1;
}
void Bullet::delete_bullet()
{
    Map::map[LENGTH*pos_y + pos_x] = EMPTY;
}

Tank::Tank()
{
    ;
}
Tank::Tank(int t, int x, int y, int i)
{
    type = t;
    pos_x = x;
    pos_y = y;
    id = i;
    bullets = NULL;
}
void Tank::basic_move()
{
    int pre_x=pos_x;
    int pre_y=pos_y;
    switch (dir)
    {
    case up:
        if ((Map::map[LENGTH*(pos_y - 2) + pos_x] == 0|| Map::map[LENGTH*(pos_y - 2) + pos_x] == FOREST) &&
            (Map::map[LENGTH*(pos_y - 2) + pos_x - 1] == 0|| Map::map[LENGTH*(pos_y - 2) + pos_x - 1] == FOREST) &&
            (Map::map[LENGTH*(pos_y - 2) + pos_x + 1] == 0|| Map::map[LENGTH*(pos_y - 2) + pos_x + 1] == FOREST))
            pos_y--;
        break;
    case down:
        if ((Map::map[LENGTH*(pos_y + 2) + pos_x] == 0 || Map::map[LENGTH*(pos_y + 2) + pos_x] == FOREST) &&
            (Map::map[LENGTH*(pos_y + 2) + pos_x - 1] == 0 || Map::map[LENGTH*(pos_y + 2) + pos_x - 1] == FOREST) &&
            (Map::map[LENGTH*(pos_y + 2) + pos_x + 1] == 0 || Map::map[LENGTH*(pos_y + 2) + pos_x + 1] == FOREST))
            pos_y++;
        break;
    case left:
        if ((Map::map[LENGTH*pos_y + pos_x-2] == 0 || Map::map[LENGTH*pos_y + pos_x-2] == FOREST) &&
            (Map::map[LENGTH*(pos_y - 1) + pos_x - 2] == 0 || Map::map[LENGTH*(pos_y - 1) + pos_x - 2] == FOREST) &&
            (Map::map[LENGTH*(pos_y + 1) + pos_x - 2] == 0 || Map::map[LENGTH*(pos_y + 1) + pos_x - 2] == FOREST))
            pos_x -= 1;
        break;
    case right:
        if ((Map::map[LENGTH*pos_y + pos_x+2] == 0 || Map::map[LENGTH*pos_y + pos_x+2] == FOREST) &&
            (Map::map[LENGTH*(pos_y - 1) + pos_x +2] == 0 || Map::map[LENGTH*(pos_y - 1) + pos_x - 2] == FOREST) &&
            (Map::map[LENGTH*(pos_y + 1) + pos_x +2] == 0 || Map::map[LENGTH*(pos_y + 1) + pos_x + 2] == FOREST))
            pos_x += 1;
        break;
    default:;
    }


    if (pre_x!=pos_x||pre_y!=pos_y)
    {
        for (int i = pre_x - 1; i <= pre_x + 1; i++)
            for (int j = pre_y - 1; j <= pre_y + 1; j++)
            {
                if ((i>0&&i<LENGTH-1&&j>0&&j<WIDTH-1)&&Map::map[j*LENGTH + i] != FOREST)
                {
                    Map::map[j*LENGTH + i] =0;
                }
            }
    }
    for (int i = pos_x - 1; i <= pos_x + 1; i++)
        for (int j = pos_y - 1; j <= pos_y + 1; j++)
            if(Map::map[j*LENGTH + i]!=FOREST&&(i!=pos_x||j!=pos_y)&&(i>0&&i<LENGTH-1&&j>0&&j<WIDTH-1))
                Map::map[j*LENGTH + i] = id;
    if(Map::map[pos_y*LENGTH + pos_x]!=FOREST)
    {
        switch(pre_dir)
        {
        case up:
            Map::map[pos_y*LENGTH+pos_x]=TANK1_UP;break;
        case down:
            Map::map[pos_y*LENGTH+pos_x]=TANK1_DN;break;
        case left:
            Map::map[pos_y*LENGTH+pos_x]=TANK1_LEFT;break;
        case right:
            Map::map[pos_y*LENGTH+pos_x]=TANK1_RIGHT;break;
        }
        switch(dir)
        {
        case up:
            Map::map[pos_y*LENGTH+pos_x]=TANK1_UP;break;
        case down:
            Map::map[pos_y*LENGTH+pos_x]=TANK1_DN;break;
        case left:
            Map::map[pos_y*LENGTH+pos_x]=TANK1_LEFT;break;
        case right:
            Map::map[pos_y*LENGTH+pos_x]=TANK1_RIGHT;break;
        }
        switch(type)
        {
        case 2:
            Map::map[pos_y*LENGTH+pos_x]+=4;break;
        case 3:
            Map::map[pos_y*LENGTH+pos_x]+=8;break;
        case 4:
            Map::map[pos_y*LENGTH+pos_x]+=12;break;
        case 0:
            Map::map[pos_y*LENGTH+pos_x]+=16;break;
        case -1:
            Map::map[pos_y*LENGTH+pos_x]+=20;break;
        }
    }
}
void Tank::shoot()
{
    if (bullets != NULL)
        return;
    Bullet *b = new Bullet;
    b->dir = pre_dir;
    assert(b->dir != 0);
    b->pos_x = pos_x;
    b->pos_y = pos_y;
    switch (b->dir)
    {
    case up:
        b->pos_y -= 2; break;
    case down:
        b->pos_y += 2; break;
    case left:
        b->pos_x -= 2; break;
    case right:
        b->pos_x += 2; break;
    }
    b->sleep_time = bullet_sleep_time;
    if (type == 3)
        b->type = 2;
    else
        b->type = 1;
    b->master = id;
    bullets = b;
}

void Tank::delete_tank()
{
    for (int i = pos_x - 1; i <= pos_x + 1; i++)
        for (int j = pos_y - 1; j <= pos_y + 1; j++)
            Map::map[LENGTH*j + i] = 0;
}

void Enemy::move()
{
    int choices[3][10] = { 0,right,right, right, down, down, down,left,up ,
                         0,0,down, right,down,left,down, down, down,up,
                         0,0,right,up,left, down,left,down, down,left };
    if (dir != 0)
        pre_dir = dir;

    if (pos_x > LENGTH / 2)
        dir = left;
    else if (pos_x < LENGTH / 2-1)
        dir = right;
    if (pos_y >WIDTH - 3)
        dir = up;
    else if (pos_y < WIDTH - 3)
        dir = down;
    srand((unsigned)time(NULL));
    if (pos_x != LENGTH / 2-1 && pos_y != WIDTH - 3 && dir == pre_dir)
        dir = choices[id - 10][rand() % 10];

    basic_move();
    int temp;
    srand((unsigned)time(NULL));
    temp = (rand() + type) % 2;
    if (bullets == NULL && temp == 1)
    {
        shoot();
    }
}
void Player::move()
{
    //捕捉键盘信息决定移动方向
    if (dir != 0)
        pre_dir = dir;
    basic_move();
    dir=0;
}

Map::Map()
{

    for (int i = 0; i < LENGTH*WIDTH; i++)
        map[i] = EMPTY;
    //surrending walls
    for (int i = 0; i < LENGTH; i++)
    {
        map[i] = BRICK_WALL;
        map[LENGTH*(WIDTH - 1) + i] = BRICK_WALL;
    }
    for (int i = 1; i < WIDTH; i++)
    {
        map[LENGTH*i] = BRICK_WALL;
        map[LENGTH*(i + 1) - 1] = BRICK_WALL;
    }

    //base
    map[LENGTH*(WIDTH - 3) + LENGTH / 2-1] = STAR;
    map[LENGTH*(WIDTH - 3) + LENGTH / 2] = STAR;
    map[LENGTH*(WIDTH - 2) + LENGTH / 2-1] = STAR;
    map[LENGTH*(WIDTH - 2) + LENGTH / 2] = STAR;
    for (int i = LENGTH / 2 - 2; i < LENGTH / 2 + 2; i ++)
        map[LENGTH*(WIDTH - 4) + i] = BRICK_WALL;
    for (int i = WIDTH - 4; i < WIDTH - 1; i++)
    {
        map[LENGTH*i + LENGTH / 2 - 2] = BRICK_WALL;
        map[LENGTH*i + LENGTH / 2 + 1] = BRICK_WALL;
    }

    //brick wall
    for (int i = 3; i < 5; i ++)
        for (int j = 16; j < WIDTH-1; j++)
            map[j*LENGTH + i] = BRICK_WALL;
    for (int i = 10; i < 12; i ++)
        for (int j = 26; j < WIDTH-1; j++)
            map[j*LENGTH + i] = BRICK_WALL;
    for (int i = 10; i < 12; i ++)
        for (int j = 19; j < 23; j++)
            map[j*LENGTH + i] = BRICK_WALL;
    for (int i = 4; i < 13; i ++)
        for (int j = 11; j < 13; j++)
            map[j*LENGTH + i] = BRICK_WALL;
    for (int i = 16; i < 24; i ++)
        for (int j = 16; j < 20; j++)
            map[j*LENGTH + i] = BRICK_WALL;
    for (int i = 28; i < 30; i ++)
        for (int j = 5; j < 9; j++)
            map[j*LENGTH + i] = BRICK_WALL;
    for (int i = 28; i < 35; i ++)
        for (int j = 7; j < 9; j++)
            map[j*LENGTH + i] = BRICK_WALL;
    for (int i = 19; i < 21; i ++)
        for (int j = 3; j < 9; j++)
            map[j*LENGTH + i] = BRICK_WALL;
    for (int i = 32; i < 34; i ++)
        for (int j = 20; j < 26; j++)
            map[j*LENGTH + i] = BRICK_WALL;

    //sea
    for (int i = 1; i < 3; i++)
        for (int j = 18; j < WIDTH-1; j++)
            map[j*LENGTH + i] = SEA;
    for (int i = 37; i < 39; i++)
        for (int j = 22; j < WIDTH-1; j++)
            map[j*LENGTH + i] = SEA;

    //steel wall
    for (int i = 1; i < 3; i ++)
        for (int j = 16; j < 18; j++)
            map[j*LENGTH + i] = STEEL_WALL;
    for (int i = 10; i < 12; i ++)
        for (int j = 15; j < 19; j++)
            map[j*LENGTH + i] = STEEL_WALL;
    for (int i = 10; i < 12; i ++)
        for (int j = 1; j < 5; j++)
            map[j*LENGTH + i] = STEEL_WALL;
    for (int i = 20; i < 22; i += 2)
        for (int j = 1; j < 3; j++)
            map[j*LENGTH + i] = STEEL_WALL;
    for (int i = 26; i < 31; i ++)
        for (int j = 14; j < 16; j++)
            map[j*LENGTH + i] = STEEL_WALL;
    for (int i = 28; i < 30; i ++)
        for (int j = 1; j < 5; j++)
            map[j*LENGTH + i] = STEEL_WALL;
    for (int i = 24; i < 26; i ++)
        for (int j = 23; j < 25; j++)
            map[j*LENGTH + i] = STEEL_WALL;
    for (int i = 17; i < 23; i ++)
        for (int j = 12; j < 14; j++)
            map[j*LENGTH + i] = STEEL_WALL;

    //forest
    for (int i = 1; i < 4; i++)
        for (int j = 4; j < 13; j++)
            map[j*LENGTH + i] = FOREST;
    for (int i = 10; i <16; i++)
        for (int j = 5; j < 7; j++)
            map[j*LENGTH + i] = FOREST;

}
