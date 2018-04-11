#include<iostream>
#include<string.h>
#include<set>
#include<map>
using namespace std;
string prod[100];
char nonterm[100];
int n,x;
void first(char symbol,int p);

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



int FI(char ch)
{
	for(int i=0;i<x;i++)
	{
		if(nonterm[i]==ch)
        	return i;
    	}
}

void Union(char symbol , int z,int p,int i)
{
	int temp=FI(symbol);
	for(set <char>::iterator it=container[temp].begin();it!=container[temp].end();++it)
	{
		if(*it=='e')
		{
			p=p+1;
			if(prod[i][p]=='\0')
				container[z].insert('e');
			else
			{ 	
				first(prod[i][p],p);
				Union(prod[i][p],z,p,i);
			}
		}
		else			
			container[z].insert(*it);  
	 }
}

void first(char symbol,int p)
{

	for(int i=0;i<n;i++)
	{
		int z=FI(symbol);
		if(islower(symbol))
			container[z].insert(symbol);
		else
		{
			if(symbol==prod[i][0])
			{
     				if(islower(prod[i][2]))
         				container[z].insert(prod[i][2]);
				else
     				{
					first(prod[i][p],p);
					Union(prod[i][p],z,p,i);	
     				}
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
    first(nonterm[i],2);
}


cout<<"\nFirst are : \n";
for(int i=0;i<x;i++)
{
	cout<<nonterm[i]<<" : ";
    	for(set <char>::iterator it=container[i].begin();it!=container[i].end();++it)
    	{
        	cout<<" "<<*it;
    	}
    	cout<<"\n";
}

return 0;
}
