#include<iostream>
#include<string.h>
#include<set>
#include<map>
using namespace std;
string prod[100];
char nonterm[100];
int n,x;

set <char> container[100];

bool notexist(char ch)
{
    for(int i=0;i<n;i++)
    {
        if(ch==nonterm[i])
            return false;
    }
    return true ;
}

int findindex(char ch)
{
    for(int i=0;i<x;i++)
    {
        if(nonterm[i]==ch)
            return i;
    }
}


void first(char symbol,int k)
{
for(int i=0;i<n;i++)
{
  int z=findindex(symbol);
 if(symbol==prod[i][0])
 {
     if(islower(prod[i][2]) && prod[i][2]!='e')
     {
         container[z].insert(prod[i][2]);
     }
     if(set<char>::iterator itr=container[z].find('e') && itr=='e')
     {
            first(prod[i][++k],2);
     }
     if(isupper(prod[i][k]))
     {
         first(prod[i][k],2);
     }
 }
}

}


int main()
{
cout<<"enter the no. of production : ";
cin>>n;

for(int i=0;i<n;i++)
    cin>>prod[i];

x=0;
for(int i=0;i<n;i++)
{
        if(notexist(prod[i][0]))
        {
            nonterm[x]=prod[i][0];
            x++;
        }
}

for(int i=x-1;i>=0;i--)
{
    container[i].insert(nonterm[i]);
    first(nonterm[i],2);
}

cout<<"\nFirst are : \n";
for(int i=0;i<x;i++)
{
    for(set <char>::iterator it=container[i].begin();it!=container[i].end();++it)
    {
        cout<<" "<<*it;
    }
    cout<<"\n";
}

return 0;
}
