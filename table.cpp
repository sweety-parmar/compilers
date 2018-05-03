#include<iostream>
#include<set>
#include<vector>
#include<string.h>
using namespace std;
int n=3,in=0,z=0;
string prod[100],lr[100];
set <string> moves[100];
vector <string> tempo;

void display(int in)
{
for(int i=0;i<=in;i++)
{
    cout<<i;
    for(set <string>::iterator itr=moves[i].begin() ; itr!=moves[i].end(); itr++)
    {   cout<<" \t"<<*itr<<"\n";    }
    cout<<"\n\n";
}   }

void closure(int in)
{
    string temp;
    int q=2;
    set <string>::iterator itr=moves[in].begin();
    tempo.push_back(*itr);
    temp=*itr;
    while(temp[q]!='\0')
    {   q=q+1;  }

    if(temp[q-1]=='.')
    {
        tempo.pop_back();
        return;
    }
    else
    {
        while(!tempo.empty())
        {
            temp=tempo.back();
            tempo.pop_back();

            if(temp[q-1]=='.')
            {
                cout<<"\ni m returning \n";
                return;
            }
                for(int i=2;i<=5;i++)
                {
                    if(temp[i]=='.')
                    {
                        if(isupper(temp[i+1]))
                        {
                            for(int j=0;j<=3;j++)
                            {
                                if(temp[i+1]==lr[j][0])
                                {
                                    moves[in].insert(lr[j]);
                                    tempo.push_back(lr[j]); }   }
                        }
                        break;
                    }
               }
            }
        }
}

void table(int in,char symbol[])
{
    closure(in);
   // display(in);

    int y=0;
    while(symbol[y]!='\0')
    {
        for(set <string>::iterator itr=moves[in].begin();itr!=moves[in].end();itr++)
        {   string temp=*itr;
            for(int i=0;i<5;i++)
            {
                if(temp[i]=='.')
                {
                    if(symbol[y]==temp[i+1])
                    {
                        int x=temp[i];
                        temp[i]=temp[i+1];
                        temp[i+1]=x;

                        z=z+1;

                        moves[z].insert(temp);
                        closure(z);
                       // display(z);
                    }
                }
            }
        }
        y=y+1;
    }

 in=in+1;


}

int main()
{
prod[0]="S=AA";
prod[1]="A=aA";
prod[2]="A=b";

lr[0]="Z=.S";
lr[1]="S=.AA";
lr[2]="A=.aA";
lr[3]="A=.b";

char symbol[5]={'S','A','a','b','\0'};

moves[0].insert("Z=.S");
table(in,symbol);
display(z);

return 0;
}
