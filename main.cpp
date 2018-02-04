    #define _UNICODE
    #define UNICODE
    #include <iostream>
    #include <string>
    #include <fstream>
    #include <windows.h>
    #include <ctime>
    #include <stdlib.h>
    #include <stdio.h>
    #include<cstdlib>    //ʹ��system�����cstdlib��


    using namespace std;

    char winner[16];
    int const ROW = 4;
    int const COL = 4;
    int game[ROW][COL] = {0};

    //��������
    int const UP = 1;
    int const DOWN = 2;
    int const LEFT = 3;
    int const RIGHT = 4;

    //��Ϸ������״̬
    int const GAME_OVER = 1;
    int const GAME_WIN = 2;
    int const GAME_CONTINUE = 3;

    enum GameNum
    {
        Game_2 = 2,
        Game_4 = 4,
        Game_8 = 8,
        Game_16 = 16,
        Game_32 = 32,
        Game_64 = 64,
        Game_128 = 128,
        Game_256 = 256,
        Game_512 = 512,
        Game_1024 = 1024,
        Game_2048 = 2048,
    };

    //�޸Ŀ���̨��С
void ChangeScale(int lines, int cols){
    char szStrCmd[128];
    sprintf(szStrCmd ,"mode con lines=%d cols=%d", lines, cols);
    system(szStrCmd);
}

    //��ӡ���õ�����
    void Print()
    {
        system("cls");
        cout << "************  2048 �ر��  *************" << endl;
        cout << "************  For wonder-7 *************" << endl << endl;
        for (int i = 0; i < ROW; i++)
        {
            cout << "   ---------------------------------"<< endl;
            for (int j = 0; j < COL; j++)
            {
                cout<<"   ";
                if (game[i][j] == 0)
                {
                    cout <<"|    ";
                }
                else if ( 10 <game[i][j] <128)
                {
                    cout <<"|   " << game[i][j];
                }
                else if ( 128 <=game[i][j])
                {
                    cout <<"|  " << game[i][j];
                }
            }
                cout << "  |" << endl;
        }
        cout << "   ---------------------------------"<< endl;
    }


    bool CreateNumber()
    {
        int x = -1;
        int y = -1;
        int times = 0;
        int maxTimes = ROW * COL;
        //����֮���ĸ�������2������֮һ�ĸ�������4
        int whitch = rand() % 3;
        do
        {
            x = rand() % ROW;
            y = rand() % COL;
            ++times;
        } while (game[x][y] != 0 && times <= maxTimes);

        //˵�������Ѿ�����
        if(times >= maxTimes)
        {
            return false;
        }
        else
        {
            GameNum num;
            if(whitch == 0)
            {
                num = Game_4;
            }
            else if(whitch)
            {
                num = Game_2;
            }
            game[x][y] = num;
        }

        return true;
    }

    void Process(int direction)
    {
        switch (direction)
        {
        case UP:
            //������һ�в���
            for(int row = 1; row < ROW; ++row)
            {
                for(int crow = row; crow >= 1; --crow)
                {
                    for(int col = 0; col < COL; ++col)
                    {
                        //��һ������Ϊ��
                        if(game[crow-1][col] == 0)
                        {
                            game[crow-1][col] = game[crow][col];
                            game[crow][col] = 0;
                        }
                        else
                        {
                            //�ϲ�
                            if(game[crow-1][col] == game[crow][col])
                            {
                                game[crow - 1][col] *= 2;
                                game[crow][col] = 0;
                            }

                        }
                    }
                }
            }
            break;
        case DOWN:
            //������һ�в���
            for(int row = ROW - 2; row >= 0; --row)
            {
                for(int crow = row; crow < ROW - 1; ++crow)
                {
                    for(int col = 0; col < COL; ++col)
                    {
                        //��һ������Ϊ��
                        if(game[crow + 1][col] == 0)
                        {
                            game[crow + 1][col] = game[crow][col];
                            game[crow][col] = 0;
                        }
                        else
                        {
                            //�ϲ�
                            if(game[crow + 1][col] == game[crow][col])
                            {
                                game[crow + 1][col] *= 2;
                                game[crow][col] = 0;
                            }

                        }
                    }
                }
            }
            break;
        case LEFT:
            //�����һ�в���
            for(int  col = 1; col < COL; ++col)
            {
                for(int ccol = col; ccol >= 1; --ccol)
                {
                    for(int row = 0; row < ROW; ++row)
                    {
                        //��һ������Ϊ��
                        if(game[row][ccol-1] == 0)
                        {
                            game[row][ccol - 1] = game[row][ccol];
                            game[row][ccol] = 0;
                        }
                        else
                        {
                            //�ϲ�
                            if(game[row][ccol - 1] == game[row][ccol])
                            {
                                game[row][ccol - 1] *= 2;
                                game[row][ccol] = 0;
                            }

                        }
                    }
                }
            }
            break;
        case RIGHT:
            //���ұ�һ�в���
            for(int  col = COL - 2; col >= 0; --col)
            {
                for(int ccol = col; ccol <= COL - 2; ++ccol)
                {
                    for(int row = 0; row < ROW; ++row)
                    {
                        //��һ������Ϊ��
                        if(game[row][ccol + 1] == 0)
                        {
                            game[row][ccol + 1] = game[row][ccol];
                            game[row][ccol] = 0;
                        }
                        else
                        {
                            //�ϲ�
                            if(game[row][ccol + 1] == game[row][ccol])
                            {
                                game[row][ccol + 1] *= 2;
                                game[row][ccol] = 0;
                            }

                        }
                    }
                }
            }
            break;
        }

    }

    //�������������������������
    int Input()
    {
        //��ȡ���������ĸ������
        int upArrow = 0;
        int downArrow = 0;
        int leftArrow = 0;
        int rightArrow = 0;
        int direction = 0;
        while (true)
        {
            upArrow = GetAsyncKeyState(VK_UP);
            downArrow = GetAsyncKeyState(VK_DOWN);
            leftArrow = GetAsyncKeyState(VK_LEFT);
            rightArrow = GetAsyncKeyState(VK_RIGHT);

            if(upArrow)
            {
                direction = UP;
                break;
            }
            else if(downArrow)
            {
                direction = DOWN;
                break;
            }
            else if(leftArrow)
            {
                direction = LEFT;
                break;
            }
            else if(rightArrow)
            {
                direction = RIGHT;
                break;
            }

            Sleep(100);
        }

        return direction;
    }

    //�ж���Ϸ״̬
    int Judge()
    {
        //Ӯ����Ϸ
        for(int i = 0; i < ROW; ++i)
        {
            for(int j = 0; j < COL; ++j)
            {
                if(game[i][j] == 256)
                {
                    cout<<endl<<endl<<"                  win"<<endl<<endl<<endl;
                    system("pause");
                    return GAME_WIN;
                    break;
                }
            }
        }

        //������
        for(int i = 0 ; i < ROW; ++i)
        {
            for(int j = 0; j < COL - 1; ++j)
            {
                if(!game[i][j] || (game[i][j] == game[i][j+1]))
                {
                    return GAME_CONTINUE;
                    break;
                }
            }
        }
        //������
        for(int j = 0; j< COL; ++j)
        {
            for(int i = 0; i < ROW -1; ++i)
            {
                if(!game[i][j] || (game[i][j] == game[i+1][j]))
                {
                    return GAME_CONTINUE;
                    break;
                }
            }
        }

        //��������������״������Ϸ����
        return GAME_OVER;

    }

    int main()
    {
        ChangeScale(18,40);
        system("color 1f");
        //����һ�����������
        srand((unsigned int)time(0));
        CreateNumber();
        CreateNumber();
        Print();
        int direction = 0;
        int gameState = 3;

        while(gameState==GAME_CONTINUE)
        {
            direction = Input();
            gameState = Judge();
            if(direction)
            {
                Process(direction);
                CreateNumber();
                Print();
                Sleep(600);
            }
        }

        if (gameState==1){            //game_over
            system("cls");
            cout<<"lose,������"<<endl;
            system("pause");
            exit(1);
        }
        else if (gameState==2){            //game_win
            system("cls");
            while (strcmp(winner,"31/01/1996")){
            cout<<"�ҵ������� ����/����/��������"<<endl;
            gets(winner);
            }
            cout<<endl<<endl<<"            ����������������"<<endl<<"            ���϶�������ȫ��"<<endl<<endl;
            system ("pause");
            system("D:\\7-7.mp4");
            exit(0);
        }
        return 0;
    }
