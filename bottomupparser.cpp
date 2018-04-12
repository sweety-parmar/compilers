#include<iostream>
using namespace std;
int n=3;
string prod[100];
char Stack[100];
char reduced[100];

int precedence(char ch)
{
switch (ch)
{
case '$':{return 0;}
case '+':{return 1;}
case '-':{return 1;}
case '*':{return 2;}
case 'i':{return 3;}

}
}


void display(int spos,int rpos)
{
cout<<"\n stack is :";
for(int i=0; i<=spos;i++)
{
    cout<<Stack[i]<<" ";
}
cout<<"\n reduced array is : ";
for(int i=0;i<=rpos;i++)
{
    cout<<reduced[i]<<"";
}
}


int main()
{
   
prod[0]="E=E+E";
prod[1]="E=E*E";
prod[2]="E=i";    
char ip[100];
int ipos=0,spos=0,rpos=-1;
//cout<<"enter the no. of productions :" ;
//cin>>n;

/*for(int i=0;i<n;i++)
{
cin>>prod[i];
}*/

cout<<"enter the input";
cin>>ip;

Stack[spos]='$';

while(Stack[spos]!='\0')
{
    if((precedence(Stack[spos]))<(precedence(ip[ipos])))
    {
        
        Stack[++spos]=ip[ipos++];
        cout<<"\nSHIFT :";
        display(spos,rpos);
    }
    else
    {
        for(int i=0;i<n;i++)
        {
            int temp=2;
            while(prod[i][temp]!='\0')
            {
                if(Stack[spos]==prod[i][temp])
                {
                    temp=2;
                    
                    
                        
                    if( Stack[spos]=='e')
                    {
                        reduced[++rpos]=prod[i][0];
                        cout<<"\nREDUCE : ";
                        display(spos,rpos);
                    }
                    else
                    {
                       reduced[rpos]='\0';
                       --rpos;
                       reduced[rpos]='\0';
                        --rpos;
                    }
                    Stack[spos]='\0';
                    --spos;
                    
                    break;
                }
                else
                {
                    ++temp;
                }
            }
        }
    }
}
return 0;
}
