#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>


#define ARRAY_SIZE 100
#define LOW_RANGE 1
#define HIGH_RANGE 10
#define CHAR_LEN 26

int sample[ARRAY_SIZE];
int count_rule;

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
while(temp->next!=last && temp->next!=NULL)
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
			last->next=node;
			last=node;
			}
		}
	}
}

char *getrule(int num)
{
int rulenum=num-HIGH_RANGE;
int len=rulenum/CHAR_LEN;
char *rules=malloc(sizeof(char)*(len +2));
char *ret_rule=malloc(sizeof(char)*(len +2));
int i=0,j;
while(rulenum>0)
	{
	rules[i]=(rulenum%CHAR_LEN) -1 + 'A';
	rulenum=rulenum/CHAR_LEN;
	i++;
	}
rules[i]='\0';

for(j=0;j<i;j++)
	ret_rule[j]=rules[i-j-1];
	
return(ret_rule);

}


int main()
{
int i;
srand(time(NULL));
first=NULL;
last=NULL;
count_rule=0;
for(i=0;i<ARRAY_SIZE;i++)
	sample[i] = rand()%HIGH_RANGE + LOW_RANGE;
/*sample[0]=10;
sample[1]=20;
sample[2]=30;
sample[3]=10;
sample[4]=20;
sample[5]=40;	
*/
for(i=0;i<ARRAY_SIZE;i++)
	sequitur(sample[i]);
	
for(i=0;i<ARRAY_SIZE;i++)
	printf("%d ",sample[i]);

printf("\n\n");

diagram *x=first;
while(x!=NULL)
	{
	if(x->num <= HIGH_RANGE)	
		printf("%d ",x->num);

	else
		printf("%s ",getrule(x->num));
	x=x->next;
	}

printf("\n\n");

for(i=0;i<count_rule;i++)
	{
	if(rule_list[i]->num <= HIGH_RANGE && rule_list[i]->next->num <=HIGH_RANGE)
		printf("%s: %d %d\n",getrule(i+1+HIGH_RANGE),rule_list[i]->num,rule_list[i]->next->num);
	
	else if(rule_list[i]->num <= HIGH_RANGE && rule_list[i]->next->num >HIGH_RANGE)
		printf("%s: %d %s\n",getrule(i+1+HIGH_RANGE),rule_list[i]->num,getrule(rule_list[i]->next->num));
	
	else if(rule_list[i]->num > HIGH_RANGE && rule_list[i]->next->num <= HIGH_RANGE)
                printf("%s: %s %d\n",getrule(i+1+HIGH_RANGE),getrule(rule_list[i]->num),rule_list[i]->next->num);

	else if(rule_list[i]->num > HIGH_RANGE && rule_list[i]->next->num >HIGH_RANGE)
                printf("%s: %s %s\n",getrule(i+1+HIGH_RANGE),getrule(rule_list[i]->num),getrule(rule_list[i]->next->num));

	}
return 0;
}
