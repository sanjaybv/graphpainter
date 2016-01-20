#include <fstream.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#include <process.h>

void cycle(int c);           //Main loop - calls the function.
void scores(int r,int z);    //Records scores and displays it.
void winner(int a);          //Winning screen.
void samtic(int x,int y);    //Displays the format of TicTacToe.
void move();                 //Makes the computer's move.
void oxo();                  //Outputs Xs and Os.
void input();                //Gets the Human's move.
void frontpage();            //Displays the first page, gets the human's name.
void ifwin();                //Checks if anyone has won.
void ifdraw();               //Checks if the game is a draw.
void initial();              //Neutralizes the values.

struct score                      //Structure to record scores.
{
 char name[20];
 int w,l,d;
} p;
int tic[3][3],win=1;              //tic is the main 2-D array.


void main()                       //Main function.
{
 clrscr();
 int gdriver = DETECT, gmode;
 initgraph(&gdriver, &gmode, "");

 randomize();
 cycle(0);
}

void scores(int r,int z=1)        //reads and updates the scores from file.
{
 cleardevice();
 score s[50],t;
 char a[80],n[20],ch[20];
 int i=0,j,k,found=0,c,l,num,q;
 fstream f("ticscn.txt",ios::in|ios::out);

 while(f.getline(a,80))                //Reads the file.
 {
  strcpy(s[i].name,a);

  f.getline(a,80);
  s[i].w=atoi(a);

  f.getline(a,80);
  s[i].l=atoi(a);

  f.getline(a,80);
  s[i].d=atoi(a);

  i++;
 }
 f.close();

 for(j=0;j<i;j++)                       //Checks if the human's name already
 {                                      //exists and updates the score.
   if(strcmpi(p.name,s[j].name)==0)
   {
     switch(r)
     {
      case 0:s[j].d++;break;
      case 1:s[j].w++;break;
      case 4:s[j].l++;break;
     }
     found=1;
   }
 }

 if(!found)                            //If the human is playing for the
 {                                     //first time, it creates a new record.
  p.w=p.l=p.d=0;
  switch(r)
     {
      case 0:p.d++;break;
      case 1:p.w++;break;
      case 4:p.l++;break;
     }
  s[i]=p;
  i++;
 }

 for(k=1;k<i;k++)                      //Sorts according the no. of wins
 {                                     //using insertion sort.
   t=s[k];
   j=k-1;
   while(t.w>s[j].w && j>=0)
   {
    s[j+1]=s[j];
    j--;
   }
   s[j+1]=t;
 }

 fstream fn("ticscn.txt",ios::out);    //Writes into the file.
 for(j=0;j<i;j++)
   fn<<s[j].name<<endl<<s[j].w<<endl<<s[j].l<<endl<<s[j].d<<endl;


 setcolor(6);                          //Displays the scoreboard.
 settextstyle(10,0,5);
 outtextxy(90,0,"SCOREBOARD");
 settextstyle(6,0,4);
 outtextxy(20,95,"Rank");
 outtextxy(100,95,"Name");
 outtextxy(340,95,"Wins");
 outtextxy(440,95,"Loses");
 outtextxy(540,95,"Draws");
 setcolor(4);
 rectangle(10,100,630,470);
 line(10,140,630,140);

 settextstyle(6,0,1);
 if(z)
 {
  for(j=0;j<i && j<12;j++)
  {
   itoa(j+1,ch,10);
   outtextxy(20,150+j*25,ch);

   outtextxy(100,150+j*25,s[j].name);

   itoa(s[j].w,ch,10);
   outtextxy(340,150+j*25,ch);

   itoa(s[j].l,ch,10);
   outtextxy(440,150+j*25,ch);

   itoa(s[j].d,ch,10);
   outtextxy(540,150+j*25,ch);
  }
  getch();
 }

 fn.close();
}


void samtic(int x,int y)               //Displays the format of TicTacToe
{
   setcolor(4);
    line(200+x,200-y,200+x,350-y);
    line(250+x,200-y,250+x,350-y);
    line(150+x,250-y,300+x,250-y);
    line(150+x,300-y,300+x,300-y);
   settextstyle(0,0,2);
   setcolor(6);
   outtextxy(170+x,220-y,"7");
   outtextxy(220+x,220-y,"8");
   outtextxy(270+x,220-y,"9");
   outtextxy(170+x,270-y,"4");
   outtextxy(220+x,270-y,"5");
   outtextxy(270+x,270-y,"6");
   outtextxy(170+x,320-y,"1");
   outtextxy(220+x,320-y,"2");
   outtextxy(270+x,320-y,"3");
}


void frontpage()                       //Displays the title screen,
{                                      //instructions and gets the
 cleardevice();                        //human's name.
 int c1,i,x=280,y=0;
  settextstyle(10,0,6);
  setcolor(RED);
  setfillstyle(7,4);
  bar(40,16,596,140);
  bar(24,200,416,324);
  setfillstyle(1,0);
  bar(49,25,587,131);
  bar(29,205,411,319);
  setcolor(6);
  outtextxy(55,15,"TIC TAC TOE");
  settextstyle(2,0,8);
  outtextxy(45,220,"Press ENTER key to START");
  outtextxy(45,270,"Press ESC key to EXIT");

  setcolor(4);
    line(200+x,200-y,200+x,350-y);
    line(250+x,200-y,250+x,350-y);
    line(150+x,250-y,300+x,250-y);
    line(150+x,300-y,300+x,300-y);
   settextstyle(0,0,2);
   setcolor(6);
   outtextxy(170+x,220-y,"X");
   outtextxy(220+x,220-y,"O");
   outtextxy(270+x,220-y,"X");
   outtextxy(170+x,270-y,"O");
   outtextxy(220+x,270-y,"X");
   outtextxy(270+x,270-y,"O");
   outtextxy(170+x,320-y,"X");
   outtextxy(220+x,320-y,"O");
   outtextxy(270+x,320-y,"X");

  if(getch()==27)
   exit(1);

   cleardevice();                      //Second page, displays the
   setcolor(RED);                      //instructions.
   rectangle(67,19,530,100);
   setcolor(6);
   settextstyle(10,0,5);
   outtextxy(90,5,"TIC TAC TOE");
   settextstyle(6,0,3);
   outtextxy(5,100,"Welcome to Tic Tac Toe!!!");
   outtextxy(5,125,"Assuming you know how to play let me show you the");
   outtextxy(5,150,"format of the board. The numbers indicate the position.");
   outtextxy(220,190,"You will always play first as X.");
   outtextxy(220,220,"CAUTION! Please play very patiently!");
   samtic(-100,0);

   settextstyle(6,0,3);
   setcolor(6);
   outtextxy(5,340,"You should enter the position no. according to your choice.");
   outtextxy(300,360,"Press any key to start...");
   if(getch()=='x')
    exit(0);

   cleardevice();                      //Gets the human's name.
   setcolor(6);
   settextstyle(6,0,3);
   outtextxy(190,170,"Enter your name");
   setcolor(4);
   rectangle(190,215,400,250);
   gotoxy(26,15);
   gets(p.name);
}

void oxo()                   //Displays Xs and Os.
{
 char ch[2];
 int i,j;

  settextstyle(3,0,4);
  setusercharsize(3,1,3,1);

 for(i=0;i<3;i++)
  for(j=0;j<3;j++)
  {
   switch(tic[i][j])
   {
    case 0:ch[0]=' ';break;
    case 1:ch[0]='X';break;
    case 4:ch[0]='O';break;
   }
   ch[1]='\0';
   outtextxy(180+(j*100),85+(i*100),ch);
  }
}

void winner(int a)                     //Winning screen.
{
 int i,j,c,k;
 delay(1000);
 win=0;

 setfillstyle(0,0);
 bar(0,0,640,100);
 bar(450,100,640,480);

 setcolor(6);
 settextstyle(6,0,6);

 char pname[20];

 strcpy(pname,p.name);
 strcat(pname," wins!!!");

 switch(a)
 {
  case 1:outtextxy(10,0,pname);break;
  case 4:outtextxy(10,0,"I win!");break;
  case 0:outtextxy(10,0,"Draw...");break;
  default:cout<<"Error at winner()!";break;
 }

 settextstyle(6,0,4);
 outtextxy(10,50,"Press space to play again or enter to continue.");
 if(getch()==32)
 {
  scores(a,0);                         //Calls the function scores.
  cycle(1);
 }

 scores(a,1);
 cycle(0);
}

void input()                           //Gets the human's move.
{
 char in,c;

 settextstyle(0,0,1);
 setcolor(RED);
 setfillstyle(EMPTY_FILL,0);
 bar(11,11,219,94);
 outtextxy(15,15,"Your turn");
 outtextxy(15,30,"Press esc to return");
 outtextxy(15,45,"to the main menu");
 do
 {
  c=0;
  in=getch()-48;
  switch(in)                           //Checks if the box is empty.
   {
    case -21:cycle(0);break;
    case 7:if(tic[0][0]!=0)
	    in=0;break;
    case 8:if(tic[0][1]!=0)
	    in=0;break;
    case 9:if(tic[0][2]!=0)
	    in=0;break;
    case 4:if(tic[1][0]!=0)
	    in=0;break;
    case 5:if(tic[1][1]!=0)
	    in=0;break;
    case 6:if(tic[1][2]!=0)
	    in=0;break;
    case 1:if(tic[2][0]!=0)
	    in=0;break;
    case 2:if(tic[2][1]!=0)
	    in=0;break;
    case 3:if(tic[2][2]!=0)
	    in=0;break;
  }

  switch(in)                           //Records the human's move.
   {
    case 7:tic[0][0]=1;break;
    case 8:tic[0][1]=1;break;
    case 9:tic[0][2]=1;break;
    case 4:tic[1][0]=1;break;
    case 5:tic[1][1]=1;break;
    case 6:tic[1][2]=1;break;
    case 1:tic[2][0]=1;break;
    case 2:tic[2][1]=1;break;
    case 3:tic[2][2]=1;break;
    default:{                                         //This is displayed in
	     settextstyle(0,0,1);                     //the message box.
	     setcolor(RED);
	     outtextxy(15,60,"Enter an appropriate");
	     outtextxy(15,75,"key.");
	     c=1;
	    }
   }
  }while(c);
  setfillstyle(EMPTY_FILL,0);          //Empties the message box.
  bar(15,55,219,94);
}

void ifwin()                           //Checks if anyone has won.
{
 int i,j,m,n,o,p;

 for(i=0;i<3;i++)
 {
  m=n=o=p=1;
  for(j=0;j<3;j++)
  {
   m*=tic[i][j];
   n*=tic[j][i];
   o*=tic[j][j];
   p*=tic[j][2-j];
  }
  if(m==1 || n==1 || o==1 || p==1)
   {winner(1);break;}
  if(m==64 || n==64 || o==64 || p==64)
   {winner(4);break;}
 }
}

void move()                            //Makes the computers move.
{
 int i,j,k,m,n,o,p;

 settextstyle(0,0,1);
 setcolor(RED);
 setfillstyle(EMPTY_FILL,0);
 bar(11,11,219,94);
 outtextxy(15,15,"My turn. Please wait");
 delay(1000);

 if(tic[1][1]==0)            //Defined move 1.
  { tic[1][1]=4;
    return;     }

 if(tic[1][1]==1)            //Defined move 2.
  { if(tic[0][0]==0)
    { tic[0][0]=4;
      return;     }
  }

 for(i=0;i<3;i++)            //Checks if the computer can win.
 {
  m=n=o=p=0;
  for(j=0;j<3;j++)
  {
   m+=tic[i][j];
   n+=tic[j][i];
   o+=tic[j][j];
   p+=tic[j][2-j];
  }

  if(m==8)
   for(k=0;k<3;k++)
    if(tic[i][k]==0)
     { tic[i][k]=4;
       return;     }

  if(n==8)
   for(k=0;k<3;k++)
    if(tic[k][i]==0)
     { tic[k][i]=4;
       return;     }

  if(o==8)
   for(k=0;k<3;k++)
    if(tic[k][k]==0)
     { tic[k][k]=4;
       return;     }

  if(p==8)
   for(k=0;k<3;k++)
    if(tic[k][2-k]==0)
     { tic[k][2-k]=4;
       return;       }
 }

 for(i=0;i<3;i++)            //Checks if the human can win.
 {
  m=n=o=p=0;
  for(j=0;j<3;j++)
  {
   m+=tic[i][j];
   n+=tic[j][i];
   o+=tic[j][j];
   p+=tic[j][2-j];
  }

  if(m==2)
   for(k=0;k<3;k++)
    if(tic[i][k]==0)
     { tic[i][k]=4;
       return;     }

  if(n==2)
   for(k=0;k<3;k++)
    if(tic[k][i]==0)
     { tic[k][i]=4;
       return;     }

  if(o==2)
   for(k=0;k<3;k++)
    if(tic[k][k]==0)
     { tic[k][k]=4;
       return;     }

  if(p==2)
   for(k=0;k<3;k++)
    if(tic[k][2-k]==0)
     { tic[k][2-k]=4;
       return;       }
 }

 for(i=0;i<3;i++)           //Makes the computer's advance move.
 {
  m=n=o=p=0;
  for(j=0;j<3;j++)
  {
   m+=tic[i][j];
   n+=tic[j][i];
   o+=tic[j][j];
   p+=tic[j][2-j];
  }

  if(p==6 || o==6)                     //Defined move 3.
    if(tic[0][2]==0 && tic[1][1]==1)
      { tic[0][2]=4;
	return;     }
    else
     if(tic[0][1]==0)
      { tic[0][1]=4;
	 return;    }


  if(m==4)
   for(k=0;k<3;k++)
    if(tic[i][k]==0)
     { tic[i][k]=4;
       return;     }

  if(n==4)
   for(k=0;k<3;k++)
    if(tic[k][i]==0)
     { tic[k][i]=4;
       return;     }

  if(o==4)
   for(k=0;k<3;k++)
    if(tic[k][k]==0)
     { tic[k][k]=4;
       return;     }

  if(p==4)
   for(k=0;k<3;k++)
    if(tic[k][2-k]==0)
     { tic[k][2-k]=4;
       return;     }

 }

 do                          //Backup move.
 { i=random(3);j=random(3); }while(tic[i][j]!=0);
 tic[i][j]=4;
 return;
}

void ifdraw()                //Checks if the game is a draw(in advance).
{
 int d=1,i,j,m,n,o,p;

 for(i=0;i<3;i++)
 {
  m=n=o=p=0;
  for(j=0;j<3;j++)
  {
   m+=tic[i][j];
   n+=tic[j][i];
   o+=tic[j][j];
   p+=tic[j][2-j];
  }

  if(m==1 || m==2 || m==4 || m==8)
   d=0;
  if(n==1 || n==2 || n==4 || n==8)
   d=0;
  if(o==1 || o==2 || o==4 || o==8)
   d=0;
  if(p==1 || p==2 || p==4 || p==8)
   d=0;
 }
 if(d==1)
  winner(0);
}

void initial()               //Neutralizes the values.
{
 int i,j,x,y;

 win=1;

 for(i=0;i<3;i++)            //Initializing all squares to blank.
  for(j=0;j<3;j++)
   tic[i][j]=0;

 cleardevice();
 setcolor(RED);              //Draws the message box.
 rectangle(10,10,220,95);
   setcolor(6);
   line(250,100,250,400);    //Draws the four lines.
   line(350,100,350,400);
   line(150,200,450,200);
   line(150,300,450,300);

  samtic(320,185);

}

void cycle(int c)            //The loop which controls the gaming functions.
{
 while(1)
 {
  if(!c)
   frontpage();
  initial();
  while(win)
  {
   input();
   oxo();
   ifwin();
   ifdraw();
   if(win!=0)
   {
    move();
    oxo();
    ifwin();
    ifdraw();
   }
  }
 }
}
