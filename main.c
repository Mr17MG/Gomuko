#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void gotoxy(int x,int y)
{
    COORD c={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

int mainScreen[19][19],playerNumber,Resume,over;//For Play Game Scope
time_t m;
struct tm* timeinfo;
int hour,min,sec;

void hBorderBox(int x,int y,int Ascii1,int Ascii2)
{
    gotoxy(x,y);
    int i;
    for(i=1;i<57;i++)
    {
        if(i%3==0)
            printf("%c",Ascii1);
        else printf("%c",Ascii2);
    }
}
void vBorderBox(int x,int y,int Ascii1,int Ascii2)
{
    int i;
    for(i=1;i<38;i++)
    {
        gotoxy(x,y+i);
        if(i%2==0)
            printf("%c",Ascii1);
        else printf("%c",Ascii2);
    }
}

void printBox()
{
    int i;
    for(i=0;i<19;i++)
    {
        gotoxy(6+(i*3),0);
        printf("%d",i);
        gotoxy(3,2+(i*2));
        printf("%d",i);
    }
    gotoxy(5,1);
    printf("%c",201);
    hBorderBox(6,1,203,205);//Border-Top
    gotoxy(62,1);
    printf("%c",187);
    vBorderBox(5,1,204,186);//Border-Left
    gotoxy(5,39);
    printf("%c",200);
    hBorderBox(6,39,202,205);//Border-bottom
    gotoxy(62,39);
    printf("%c",188);
    vBorderBox(62,1,185,186);//Border-Right

    for(i=3;i<39;i+=2)
        hBorderBox(6,i,206,205);//Center Horizontal Border
    for(i=8;i<62;i+=3)
        vBorderBox(i,1,206,186);//Center Vertical Border
}

int isWin(int x,int y,int playerNumber,int z)
{
    int i,counter=0;
    /*Horizontal*/
    for(i=0;i<5;i++)
    {
        if(mainScreen[(x-z)+i][y]==playerNumber)
            counter++;
        else
            counter=0;
        if(counter==5)
            return 1;
    }
    /*Vertical*/
    for(i=0;i<5;i++)
    {
        if(mainScreen[x][(y-z)+i]==playerNumber)
            counter++;
        else
            counter=0;
        if(counter==5)
            return 1;
    }
    /*CaterCorner*/
    for(i=0;i<5;i++)
    {
        if(mainScreen[(x-z)+i][(y-z)+i]==playerNumber)
            counter++;
        else
            counter=0;
        if(counter==5)
            return 1;
    }
    for(i=0;i<5;i++)
    {
        if(mainScreen[(x+z)-i][(y-z)+i]==playerNumber)
            counter++;
        else
            counter=0;
        if(counter==5)
            return 1;
    }
    return 0;

}

void gameOver(int state)
{
    system("cls");
    time(&m);
    timeinfo=localtime(&m);
    hour=timeinfo->tm_hour-hour;
    min=timeinfo->tm_min-min;
    sec=timeinfo->tm_sec-sec;
    if(sec<0)
    {
        sec+=60;
        min--;
    }
    if(min<0)
    {
        min+=60;
        hour--;
    }
    if(state==0)
    {
        gotoxy(45,15);
        printf("Game Over ");
        gotoxy(42,16);
        printf(" With Draw");
    }
    else if(state==1)
    {
        gotoxy(45,15);
        printf("Game Over");
        gotoxy(42,16);
        printf("Player1 Winner");
    }
    else if(state==2)
    {
        gotoxy(45,15);
        printf("Game Over");
        gotoxy(42,16);
        printf("Player1 Winner");
    }

    gotoxy(70,16);
    printf("GameTime:%d : %d : %d",hour,min,sec);

    gotoxy(35,18);
    printf("Do You Want to Play Again?");
    gotoxy(29,19);
    printf("Enter 1 For Play Again else Other For Exit\n");
    int Restart;
    scanf("%d",&Restart);
    if(Restart==1)
    {
        system("cls");
        Loading();
    }

    else exit(0);

}

void insertNumber()
{
    int x=0,y=0,valid=0;
    gotoxy(63,3);
    if(playerNumber==1)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE ),252);
         printf("\"Player1\" ");
    }

    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE ),249);
        printf("\"Player2\"");
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE ),240);

    do
    {
        gotoxy(73,3);
        printf("Please Insert your Position:");
        gotoxy(65,4);
        printf("                                       ");

        gotoxy(65,4);
        printf("x:");
        scanf("%d",&x);

        gotoxy(75,4);
        printf("y:");
        scanf("%d",&y);


        if((x>=0 && x<=18) && (y>=0 && y<=18))
        {
            if(mainScreen[x][y]==0)
            {
                mainScreen[x][y]=playerNumber;
                valid =0;
                gotoxy(65,10);
                printf("                             ");
            }
            else
            {
               gotoxy(65,10);
               printf("Please Enter Another Position");
               valid=1;
            }

        }
        else
        {
            gotoxy(65,10);
            printf("Please Enter Valid Position");
            valid=1;
        }
    }
    while(valid);
    for(valid=0;valid<5;valid++)
        if(isWin(x,y,playerNumber,valid)==1)
           {
                if(playerNumber==1)
                    over=1;
                else over=2;
                Resume=0;
                break;
           }
    gotoxy(6+(x*3),2+(y*2));
    if(playerNumber==1)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE ),252);
        printf("%c",219);
        playerNumber=2;
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE ),249);
        printf("%c",219);
        playerNumber=1;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE ),240);

}

void draw()
{
    int i,j;
    for(i=0;i<19;i++)
        for(j=0;j<19;j++)
            if(mainScreen[i][j]==0)
                {
                    Resume=1;
                    return;
                }
    Resume=2;
    over=0;
    return;
}

void playGame()
{
    time(&m);
    timeinfo=localtime(&m);
    hour=timeinfo->tm_hour;
    min=timeinfo->tm_min;
    sec=timeinfo->tm_sec;
    while(Resume==1)
    {
        insertNumber();//Insert Number In mainScreen Array And Screen
        if(Resume==0)
        {
            system("cls");
            gameOver(over);
            break;
        }
        draw();//For Drawing Game
    }
    if(Resume==2)
        gameOver(over);
}

void Loading()
{
    int i=0,j=0,a[3]={50,75,100};
    playerNumber=1,Resume=1,over=3;
    for(i=0;i<19;i++)
        for(j=0;j<19;j++)
            mainScreen[i][j]=0;
    i=0;j=0;
    gotoxy(35,7);
    printf("Please Wait For Loading...");
    while(i<60)
    {
        gotoxy(20+i,10);
        printf("%c",177);
        gotoxy(20+i,12);
        printf("%c",177);
        i++;
    }
    i=0;
    while (i<3)
    {
        gotoxy(20,10+i);
        printf("%c",177);
        gotoxy(80,10+i);
        printf("%c",177);
        i++;
    }
    i=0;
    while(i<59)
    {
        j=rand()%3;
        gotoxy(21+i,11);
        printf("%c",219);
        Sleep(a[j]);
        i++;
    }
    system("cls");
    printBox();//Print Border Box
    playGame();//play Game
}

int main()
{
    //pthread_t tid;
    //pthread_t m;
    // pthread_create(&tid,NULL,ClockCounter,NULL);
    //pthread_create(&m,NULL,playGame,NULL);
    // pthread_join(tid,NULL);
    // pthread_join(m,NULL);

    system("mode con: cols=103 lines=40 && color F0 && cls && title GomukoGame");//Change Size & Color & clear Of Console
    Loading();

    return 0;
}
