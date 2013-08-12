#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define ARRAY_SIZE 10000
#define LOW_RANGE 1
#define HIGH_RANGE 1000

int sample[ARRAY_SIZE];
int count_rule=0;
int count_diagram=0;

typedef struct diagram{
int num;
struct diagram *next;
}diagram;

diagram *first, *last;

typedef struct rule{
int num;
struct rule *next;
}rule;

rule *rule_list[100];


int see_for_rule(int num1,int num2)
{
int i;
for(i=0;i<count_rule;i++)
	{
	rule *start=rule_list[i];
	if(start->num==num1 && start->next->num==num2 && start->next->next==NULL)
		{
		last->num=HIGH_RANGE+i+1;
		return 1;
		}
		
	}
return 0;
}


void make_new_rule(int num1,int num2)
{
rule_list[count_rule]=(rule*)malloc(sizeof(rule));
rule_list[count_rule]->num=num1;
rule *node=(rule*)malloc(sizeof(rule));
rule_list[count_rule]->next=node;
node->next=NULL;
node->num=num2; 
count_rule++;
}

int search_in_diagram(int num1,int num2)
{
diagram *temp=first;
while(temp->next!=NULL)
	{
	if(temp->num==num1 && temp->next->num==num2)
		{
		diagram *del = temp->next;
		temp->next=del->next;
		free(del);
		temp->num=HIGH_RANGE+1+count_rule;
		last->num=temp->num;
		make_new_rule(num1,num2);
		return 1;
		}
	temp=temp->next;
	}
return 0;
}

void sequitur(int new_num)
{
int exist_rule,exist_diagram;
if(first==NULL)
	{
	diagram *node = (diagram *)malloc(sizeof(diagram));	
	node->num=new_num;
	node->next=NULL;
	first=node;
	last=node;
	count_diagram++;
	}

else
	{
	exist_rule=see_for_rule(last->num,new_num);
	if(exist_rule==0)
		{
		exist_diagram=search_in_diagram(last->num,new_num);
		if(exist_diagram==0)
			{
			diagram *node=(diagram*)malloc(sizeof(diagram));	
			node->num=new_num;
			node->next=NULL;
			last=node;
			}
		}
	}
}

int main()
{
int i;
srand(time(NULL));
first=NULL;
last=NULL;
for(i=0;i<ARRAY_SIZE;i++)
	sample[i] = rand()%HIGH_RANGE + LOW_RANGE;
	
for(i=0;i<ARRAY_SIZE;i++)
	{
	sequitur(sample[i]);
	}

diagram *x=first;
while(x!=NULL)
	{
	printf("%d ",x->num);
	x=x->next;
	}
printf("\n");

for(i=0;i<count_rule;i++)
	{
	printf("%d %d\n",rule_list[i]->num,rule_list[i]->next->num);
	}
return 0;
}
