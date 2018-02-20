		#include<iostream>
		#include<string>
		#include<stack>
		#include<stdlib.h>
		using namespace std;
		int countS=0,top=0; 
		char nfa[100][100];

		struct node
		{
		int state,CE=0;
		char label;
		node *next[10];
		};
		node *a[100];

		int priority(char ch)

		{
			switch(ch)
			{
				case '*': return 3;
				case '.': return 2;
				case '+': return 1;
				default: return 0;
		    	}
		}

		string convert_to_postfix(string expr)
		{
			string postfix;
			postfix.clear();
			char ch;
			stack <char> temp;

			for(int i=0;i<expr.length();i++)
			{
				ch=expr[i];
				if(ch=='a'||ch=='b')
				{
					postfix=postfix+ch;
				}
				else if(ch=='(')
				{
					temp.push(ch);
				}
				else if(ch==')')
				{
					while(temp.top()!='(')
					 {
					    postfix+=temp.top();
					    temp.pop();
					}
					temp.pop();
				}
				else if (ch=='*'||ch=='+'||ch=='.')
				{
					while(!temp.empty()&&priority(temp.top())>priority(ch))
					{
						postfix+=temp.top();
						temp.pop();
					}
					temp.push(ch);
				}
				else
				{
					cout<<"invalid input.";
				}
			}
			while(!temp.empty())
			{
				postfix+=temp.top();
				temp.pop();
			}
			return postfix;
		}


		node * singleChar(char ch)
		{

		node *start,*temp1,*temp2;

		temp1=(node *)malloc(sizeof(node));
		temp2=(node *)malloc(sizeof(node));

		start=temp1;

		temp1->state=countS++; 		temp1->CE=temp1->CE+1;		temp1->label='x';		temp1->next[temp1->CE]=temp2; 
		temp2->state=countS++; 		temp2->CE=0;			temp2->label=ch;		temp2->next[temp2->CE]=NULL;

		return start;
		}

		node * concat(node *n1,node *n2)
		{
		node *start;
		start=n1;
		n1=n1->next[n1->CE];
		n1->CE=n1->CE+1;
		n1->next[n1->CE]=n2;		n2->label='E';			

		return start;
		}


		node * add(node *n1,node *n2)
		{

		node *temp1,*temp2,*start;

		temp1=(node *)malloc(sizeof(node));
		temp2=(node *)malloc(sizeof(node));
		start=temp1;
		temp1->CE=temp1->CE+1;		temp1->state=countS++;		temp1->label='x';		temp1->next[temp1->CE]=n1;		
		temp1->CE=temp1->CE+1;		temp1->next[temp1->CE]=n2;
		n1->label='E';			n2->label='E';

		while(n1->next[n1->CE]!=NULL)
		{
			n1=n1->next[n1->CE];
		}

		while(n2->next[n2->CE]!=NULL)
		{
			n2=n2->next[n2->CE];
		}

		n1->CE=n1->CE+1;		n1->next[n1->CE]=temp2;		
		n2->CE=n2->CE+1;		n2->next[n1->CE]=temp2;
		temp2->CE=0;			temp2->state=countS++;		temp2->label='E';		temp2->next[temp2->CE]=NULL;

		return start;
		}


		node *star(node *n1)
		{
		node *start,*temp1,*temp2,*old;

		old=n1;
		temp1=(node *)malloc(sizeof(node));
		temp2=(node *)malloc(sizeof(node));

		start=temp1;

		temp1->state=countS++;		temp1->CE=temp1->CE+1;		temp1->label='x';	temp1->next[temp1->CE]=n1;
		temp1->CE=temp1->CE+1;		temp1->next[temp1->CE]=temp2;	n1->label='E';

		while(n1->next[n1->CE]!=NULL)
			n1=n1->next[n1->CE];


		n1->CE=n1->CE+1;	temp2->state=countS++;		n1->next[n1->CE]=temp2;		
		temp2->label='E';	temp2->CE=temp2->CE+1	;	temp2->next[temp2->CE]=old;	

		return start;			

		}

		void print(node *temp)
		{
			int y=temp->CE;
			if((temp->next[y]==0) || (nfa[temp->state][temp->next[y]->state]!=0))
			{
				return ;
			}
			else
			{
				while(y)
				{
				node *r=temp->next[y];
				nfa[temp->state][r->state]=r->label;
				cout<<"src : "<<temp->state<<"\t"<<"dest : "<<r->state<<"\t";
				cout<<"label is : "<<r->label<<"\t";
				cout<<"no of edges from state "<<r->state<<" is : "<<r->CE<<"\n\n";
				print(r);
				y--;
				temp->CE=temp->CE-1;
				}
			}		

		}
	
		void display(int top)
		{
			node *temp;
			temp=a[top];
			print(temp)	;
		
		}


		int main()
		{

		string expr,newExpr;
		cin>>expr;
		newExpr=convert_to_postfix(expr);
		cout<<newExpr<<"\n";

		int l=newExpr.length();
		for(int i=0;i<l;i++)
		{
			switch(newExpr[i])
			{
				case 'a':
				{
					cout<<"\nthis is a\n";
					node *temp;
					temp=singleChar(newExpr[i]);
					a[top++]=temp;	
					break;
				}
				case 'b':
				{
					cout<<"\nthis is b \n";
					node *temp;
					temp=singleChar(newExpr[i]);
					a[top++]=temp;
					break;
				}		
				case '+' :
				{
					cout<<"\n\nthis is +\n";
					node *temp1,*temp2,*temp;
					temp1=a[--top];	
					temp2=a[--top]; 
					temp=add(temp2,temp1);
					a[top++]=temp;	
					break;
				}
				case '*' :
				{
					cout<<"\nthis is *\n";
					node *temp1,*temp;
					temp1=a[--top];
					temp=star(temp1);
					a[top++]=temp;			
					break;
				}
				case '.' :
				{
					cout<<"\nthis is .\n";	
					node *temp1,*temp2,*temp;
					temp1=a[--top];
					temp2=a[--top];
					temp=concat(temp2,temp1);
					a[top++]=temp;		
					break;
				}
			}
		}
	
			
		top=top-1;
		display(top);
		
		for(int i=0;i<countS;i++)
		{
			for(int j=0;j<countS;j++)
			{
				if(nfa[i][j]!=0)
				cout<<"src : "<<i<<"\tdest : "<<j<<"\tinput is : "<<nfa[i][j]<<"\n";
			}
		}				
		return 0;
		}
