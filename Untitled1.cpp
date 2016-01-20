#include<iostream>
#include<conio.h>
using namespace std;
class Z
{
    int a;
    public:
        friend class X;
}s1;
class X
{
    int b;
    public:

        void readdata()
        {
            cin>>s1.a>>b;
        }
        void hello()
        {
            cout<<s1.a<<b;
        }
}s;
int main()
{
    s.readdata();
    s.hello();
    getch();
    return 0;
}
