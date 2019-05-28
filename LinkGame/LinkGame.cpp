#include "LinkGame.h"
#define BOX_WHITH  30
#define BOX_LENGTH  35
#define START_X  22
#define START_Y  187


int g_nSpeed = 50;
LinkGame::LinkGame(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
   
    
    setFixedSize(300, 80);
    ui.lineEdit->setValidator(new QIntValidator(0, 1000, this));

    connect(ui.start, &QPushButton::clicked,this,&LinkGame::StartGame);
    connect(ui.lineEdit, &QLineEdit::returnPressed,this,&LinkGame::SetGameSpeed);

}

void LinkGame::StartGame()
{
    bool falg = true;
    int cnt = 0;
    InitProc();
    ReadProcessMemory(m_hProcessDst, (PUINT)0x00199F68, &m_aChess, MAX_X*MAX_Y, 0);

    while (1)
    {
        falg = true;
        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 19; j++)
            {
                if (m_aChess[i][j] != 0)
                {
                    falg = false;
                    SeekSameCheek(j, i);
                }
            }
        }
        if (cnt++ == 3 ||falg == true)
        {
            break;
        }
    }

    return;
}

void LinkGame::InitProc()
{
    DWORD processID = 0;

    m_hwndGame = FindWindowA(NULL, "QQ游戏 - 连连看角色版");
    GetWindowThreadProcessId(m_hwndGame, &processID);
    m_hProcessDst = OpenProcess(PROCESS_ALL_ACCESS, false, processID);


}

int LinkGame::isBlocked(int x, int y)
{
    if (m_aChess[y][x] != 0)
    {
        return 1;
    }
    return 0;
}

int LinkGame::Remove(int x1, int y1, int x2, int y2)
{
    int ret = false;

    ret = horizon(x1, y1, x2, y2);
    if (ret)
    {
        return 1;
    }
    ret = vertical(x1, y1, x2, y2);
    if (ret)
    {
        return 1;
    }
    ret = turn_once(x1, y1, x2, y2);
    if (ret)
    {
        return 1;
    }
    ret = turn_twice(x1, y1, x2, y2);
    if (ret)
    {
        return 1;
    }

    return 0;
}

bool LinkGame::horizon(int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
    {
        return false;
    }

    if (y1 != y2)
    {
        return false;
    }

    int start_x = min(x1,x2);
    int end_x = max(x1, x2);

    for (int j = start_x+1; j < end_x; j++)
    {
        if (isBlocked(j,y1 ))
        {
            return false;
        }
    }
    return true;

}

int LinkGame::vertical(int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
    {
        return false;
    }

    if (x1 != x2)
    {
        return false;
    }

    int start_y = min(y1, y2);
    int end_y = max(y1, y2);

    for (int i = start_y+1; i < end_y; i++)
    {
        if (isBlocked(x1,i ))
        {
            return false;
        }
    }

    return true;
}

int LinkGame::turn_once(int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
    {
        return false;
    }

    int c_x = x1, c_y = y2;
    int d_x = x2, d_y = y1;

    int ret = false;
    if (!isBlocked(c_x, c_y))
    {
        ret |= vertical(x1, y1, c_x, c_y) && horizon(c_x, c_y, x2, y2);
    }

    if (!isBlocked(d_x, d_y))
    {
        ret |= horizon(x1, y1, d_x, d_y) && vertical(d_x, d_y, x2, y2);
    }
    if (ret)
    {
        return true;
    }

    return false;
}

int LinkGame::turn_twice(int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && y1 == y2)
    {
        return false;
    }

    for (int i = 0; i <  MAX_X; i++)
    {
        for (int j = 0; j <MAX_Y; j++)
        {
            if (i != x1 && i != x2 &&j != y1   && j != y2)
            {
                continue;
            }

            if ((i == x1 && j == y1) || (i == x2 && j == y2))
            {
                continue;
            }

            if (isBlocked(i, j))
            {
                continue;
            }

            if (turn_once(x1, y1, i, j) && (horizon(i, j, x2, y2) || vertical(i, j, x2, y2)))
            {
                return true;
            }
            if (turn_once(i, j, x2, y2) && (horizon(x1, y1, i, j) || vertical(x1, y1, i, j)))
            {
                return true;
            }

        }
    }

    return false;
}


void LinkGame::SetGameSpeed()
{
   
    auto nSpeed = ui.lineEdit->text().toInt();
    ui.speed->setText(QString::fromLocal8Bit("游戏速度") + '\n'+ ui.lineEdit->text());

}

bool LinkGame::SeekSameCheek(int x, int y)//x横坐标 y纵坐标
{
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            if (m_aChess[y][x] == m_aChess[i][j])
            {
                bool bRet = Remove(x, y, j, i);
                if (bRet)
                {
                    POINTS pos;
                    pos.x = x * BOX_WHITH + START_X+10;
                    pos.y = y * BOX_LENGTH + START_Y + 10;
                    
                    SendMessageA(m_hwndGame, WM_LBUTTONDOWN, MK_LBUTTON, *(LPARAM*)&pos);
                    pos.x = j * BOX_WHITH + START_X + 10;
                    pos.y = i * BOX_LENGTH + START_Y + 10;
                    Sleep(g_nSpeed);
                    SendMessageA(m_hwndGame, WM_LBUTTONDOWN, MK_LBUTTON, *(LPARAM*)&pos);
                    m_aChess[y][x] = 0;
                    m_aChess[i][j] = 0;
                    Sleep(g_nSpeed);
                   
                    return true;
                }
            }
        }
    }

    return false;
}


