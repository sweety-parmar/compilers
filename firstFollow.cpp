#include<iostream>
#include<string.h>
#include<set>
#include<map>
using namespace std;
string prod[100];
char nonterm[100],term[100];
int n,x,TC;
void first(char symbol,int p);
void follow(char symbol);

string table[100][100];

set <char> Cfirst[100];
set <char> Cfollow[100];



bool notexist(char ch , char arr[])
{
	for(int i=0;i<n;i++)
        {
		if(ch==arr[i])
	        return false;
    	}
    	return true ;
}



int FI(char ch,char arr[])
{
	for(int i=0;i<x;i++)
	{
		if(arr[i]==ch)
        	return i;
    	}
}

void Funion(char symbol , int z,int p,int i)
{
	int temp=FI(symbol,nonterm);
	for(set <char>::iterator it=Cfirst[temp].begin();it!=Cfirst[temp].end();++it)
	{
		if(*it=='e')
		{
			p=p+1;
			if(prod[i][p]=='\0')
				Cfirst[z].insert('e');
			else
			{ 	
				first(prod[i][p],p);
				Funion(prod[i][p],z,p,i);
			}
		}
		else			
			Cfirst[z].insert(*it);  
	 }
}

void first(char symbol,int p)
{
	int z=FI(symbol,nonterm);

	if(!isupper(symbol))
		Cfirst[z].insert(symbol);
	else
	{
		for(int i=0;i<n;i++)
		{
			if(symbol==prod[i][0])
			{
     				if(!isupper(prod[i][2]))
       					Cfirst[z].insert(prod[i][2]);
				else
     				{
					first(prod[i][p],p);
					Funion(prod[i][p],z,p,i);	
     				}
	 		}	
		}
	
	}
}

void Unionf2(int symbol,int z,int i,int p)
{
	int temp=FI(symbol,nonterm);
	for(set <char>::iterator it=Cfollow[temp].begin();it!=Cfollow[temp].end();++it)
	{
		Cfollow[z].insert(*it);	
	}
}


void Unionf1(int symbol,int z,int i,int p)
{
	int temp=FI(symbol,nonterm);
	for(set <char>::iterator it=Cfirst[temp].begin();it!=Cfirst[temp].end();++it)
	{
		if(*it=='e')
		{
			p=p+1;
			if(prod[i][p]=='\0')
			{
				follow(prod[i][0]);
				Unionf2(prod[i][0],z,i,p);
			}	
			else
			{ 	
				//first(prod[i][p],p);
				Unionf1(prod[i][p],z,i,p);
			}
		}
		else
			Cfollow[z].insert(*it);	
	}
}

void follow(char symbol)
{
	
	int x,p;
	int z=FI(symbol,nonterm);
	

		for(int i=0;i<n;i++)
		{
			x=2;
			while(prod[i][x]!='\0')
			{
				if(symbol==prod[i][x])
				{
					p=x+1;
					if(prod[i][p]=='\0' && prod[i][x]!=prod[i][0])
					{
						follow(prod[i][0]);
						Unionf2(prod[i][0],z,i,p);
					}
					if(!isupper(prod[i][p]))
					{
						Cfollow[z].insert(prod[i][p]);	
					}
						
					if(isupper(prod[i][p]) && prod[i][p]!='\0')
					{
						//first(prod[i][p],p);
						Unionf1(prod[i][p],z,i,p);
					}		
				}
				++x;
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
        if(notexist(prod[i][0],nonterm))
        {
            nonterm[x]=prod[i][0];
            x++;
        }
}


for(int i=0;i<n;i++)
{
        if(notexist(prod[i][0],term))
        {
            term[TC]=prod[i][0];
            TC++;
        }
}


for(int i=x-1;i>=0;i--)
{
	first(nonterm[i],2);
}

for(int i=0;i<x;i++)
{
	Cfollow[0].insert('$');
	follow(nonterm[i]);	
}



cout<<"\nFirst are : \n";
for(int i=0;i<x;i++)
{
	cout<<nonterm[i]<<" : ";
    	for(set <char>::iterator it=Cfirst[i].begin();it!=Cfirst[i].end();++it)
    	{
        	cout<<" "<<*it;
    	}
    	cout<<"\n";
}

cout<<"\nFollow are : \n";
for(int i=0;i<x;i++)
{
	cout<<nonterm[i]<<" : ";
    	for(set <char>::iterator it=Cfollow[i].begin();it!=Cfollow[i].end();++it)
    	{
        	cout<<" "<<*it;
    	}
    	cout<<"\n";
}


int row,col;
for(int i=0;i<n;i++)
{
  if(islower(prod[i][2]))
  {
        row=FI(prod[i][0],term);
        col=FI(prod[i][2],term);
      
  }
       
}


return 0;
}
