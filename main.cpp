#include<iostream>
#include<iomanip>
#include<string.h>
#include<graphics.h>
#include<math.h>

using namespace std;

const int win_x=1360, win_y=700, line_spc=20;
const int eqn_length=20;
int o[2]={win_x/2,win_y/2};
int scale;

void input(char*, int&);
void initial();
int texteqns(char*, int&);
double getnum(char*, int&);
void draw_axis(int&, int&);

class eqn
{
    protected:
        char str_eqn[eqn_length*3];
};

class sub_eqn : private eqn
{
    double co[eqn_length];
    char var[eqn_length];
    double var_pow[eqn_length];
    int sign[eqn_length];
    int ctr;
    
    public:

    sub_eqn()
    {
        for(int i=0;i<eqn_length;i++)
        {
            co[i]=0;
            var[i]='0';
            var_pow[i]=1;
            sign[i]=1;
        }
    }
    
    void get_eqn()
    {
        //if(!texteqns(str_eqn, scale))
          //
        input(str_eqn, scale);
        cout<<"\nscale = "<<scale<<endl;

    }
    
    void display()
    {
        cout<<"\nEquation = "<<str_eqn<<"\n";
        for(int i=0;i<=ctr;i++)
        {
            cout<<"\n";
            cout<<"co["<<i<<"] = "<<co[i]<<"\t";
            cout<<"var_pow["<<i<<"] = "<<var_pow[i]<<"\t";
            cout<<"var["<<i<<"] = "<<var[i]<<"\t";
            cout<<"sign["<<i<<"] = "<<sign[i]<<"\t";
        }
    }

    void analyse();
    
    void draw()
    {
        int lim_x, lim_y, i;
        double x, y;
        draw_axis(lim_x, lim_y);
        
        setcolor(YELLOW);
        settextstyle(0,0,0);
        x=-lim_x;

        y=0;
        for(i=0;i<=ctr;i++)
            y+=pow(var_fun(i,x),var_pow[i])*co[i]*sign[i];

        moveto(o[0]+(x*scale),o[1]-(y*scale));

        while(x<lim_x)
        {
            x+=0.01;
            y=0;
            
            for(i=0;i<=ctr;i++)
                y+=pow(var_fun(i,x),var_pow[i])*co[i]*sign[i];

            lineto(o[0]+(x*scale),o[1]-(y*scale));
            
        }
    }
    
    double var_fun(int ctr, double x)
    {

        switch(var[ctr])
        {
            case 's':   return (sin(x));
                        break;

            case 'c':   return (cos(x));
                        break;

            case 't':   return (tan(x));
                        break;

            case 'x':   return x;
                        break;
                        
            case 'f':   return exp(x);
                        break;
            
            case 'e':   return exp(1);
                        break;

            default:    return 1;
        }
    }

};

void sub_eqn::analyse()
{
    int i;
    ctr=0;

    for(i=0;i<(eqn_length*3) && str_eqn[i]!='\0';i++)
    {
        switch(str_eqn[i])
        {
            case '-':   sign[++ctr]=-1;
                        break;
                        
            case '+':   sign[++ctr]=1;
                        break;
                        
            case 'x':   if(co[ctr]==0)
                            co[ctr]=1;
                        var[ctr]='x';
                        var_pow[ctr]=1;
                        break;
                        
            case '^':   i++;
                        if(str_eqn[i]=='x')
                            var[ctr]='f';
                        else
                            var_pow[ctr]=getnum(str_eqn,i);
                        break;

            case 'c':
            case 't':
            case 's':   if(co[ctr]==0)
                            co[ctr]=1;
                        var[ctr]=str_eqn[i];
                        while(str_eqn[++i]!='x');
                        break;

            case 'e':   if(co[ctr]==0)
                            co[ctr]=1;
                        var[ctr]='e';
                        
            default:
                    {
                         if(isdigit(str_eqn[i]))
                            co[ctr]=getnum(str_eqn,i);
                    }
        }
     }

    display();
}



main()
{
    initwindow(win_x, win_y, "Graph Painter 1.1");
    sub_eqn s;
    char ch;
    settextstyle(0, 0, 0);

    do
    {
        cleardevice();
        s.get_eqn();
        s.analyse();
        s.draw();
    
        ch=getch();
    }while(ch==' ');
    
    return 0;
}

void initial()
{
    outtextxy(120,100,"SCOPE");
}

void draw_axis(int &lim_x, int &lim_y)
{
    int i;
    setcolor(15);
    line(win_x/2,0,win_x/2,win_y);
    line(0,win_y/2,win_x,win_y/2);

    lim_x=(o[0]+o[0]*scale)/pow(scale,2);
    for(i=-lim_x;i<lim_x;i++)
    {
        moveto(o[0]+i*scale,win_y/2);
        lineto(getx(),gety()+2);
    }
    
    lim_y=(o[1]+o[1]*scale)/pow(scale,2);
    for(i=-lim_y;i<lim_y;i++)
    {
        moveto(win_x/2,o[1]+i*scale);
        lineto(getx()-2,gety());
    }
    
    outtextxy(1100,660,"Press space to repeat");
    outtextxy(1100,680,"or any other key to exit");
}

double getnum(char *eq, int &i)
{
    int flag_sign=1,j;
    double deg=0;
    
    if(eq[i]=='-')
    {
        i++;
        flag_sign=-1;
    }
    
    for(j=0;isdigit(eq[i+j]);j++)
        deg=deg*10+int(eq[i+j]-48);

    if(eq[i+j]=='.')
    {
        i+=j;
        for(j=1;isdigit(eq[i+j]);j++)
            deg+=((int)eq[i+j]-48)/(pow(10.00,j));
    }
                
    i+=j-1;
    return (deg*flag_sign);
}

void input(char *str_eqn,int &scale)
{
    char *str_ptr;
    int i,num;
    char eq[eqn_length];

    setcolor(15);
    outtextxy(0, 0, "Enter an equation");
    outtextxy(0,1*line_spc,"f(x) = ");
    moveto(70,1*line_spc);
    str_ptr=eq;

    for(i=0;i<50 && eq[i-1]!='\r';i++)
    {
        do
        {
            eq[i]=getch();
            num=(int)eq[i];
            if(num==8)
            {
                outtextxy(getx()-10,gety()," ");
                moverel(-10,0);
                i--;
            }
        }while(num==8);

        str_ptr=&eq[i];
        eq[i+1]='\0';

        outtext(str_ptr);
    }

    strcpy(str_eqn,eq);

    outtextxy(0, 2*line_spc, "Enter the scale ( 1 unit in pixels )");
    outtextxy(0, 3*line_spc, "Scale = ");
    moveto(80, 3*line_spc);

    for(i=0;i<10 && eq[i-1]!='\r';i++)
    {
        do
        {

            eq[i]=getch();
            num=(int)eq[i];
            if(num==8)
            {
                outtextxy(getx()-10,gety()," ");
                moverel(-10,0);
                i--;
            }
        }while(num==8);

        str_ptr=&eq[i];
        eq[i+1]='\0';

        outtext(str_ptr);
    }

    scale=atoi(eq);
}
