#pragma once
//陆地,墙,边框,铁
enum emSence {
    LAND = 0, WALL = 1, FRAME = 4, IRON = 6,ENEMY_TANK,MY_TANK
};
//函数
void GoToxy(int x, int y);
void PrintMap();

enum MyEnum
{
    UP, DOWN ,LEFT, RIGHT
};
#define GAME_WIDTH  41
#define GAME_HEIGHT 41
#define SPPED 7
//游戏地图
extern int g_arrMap[GAME_HEIGHT][GAME_WIDTH];
//坦克模型
const extern char* g_TankModel[2][3][4];
void InitMap();




