#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define MAX_LIST 10

typedef struct list
{
	int value;
	struct list* next;
}list;

list *head[MAX_LIST]={NULL};

list* createnew(list *l,int value,int h)
{
	l=(list *)malloc(sizeof(list));
	l->value=value;
	l->next=NULL;
	head[h]=l;
	return l;

}

list* createlist(list *l,int value)
{
	list *temp;
	temp=(list *)malloc(sizeof(list));
	temp->value=value;
	temp->next=NULL;
	l->next=temp;
	return l->next;
}

list* insert(list *l,int value,int h)
  {
	if(l==NULL)
		l=createnew(l,value,h);
	else
		l=createlist(l,value);	
	return l;
}

list* search(int value,int h)
{
	list *temp=head[h];
	while(temp->next!=NULL)
	{
		if(temp->next->value==value)
			return temp;
		temp=temp->next;
	}
	return NULL;
}
void display(int h)
{
	list *temp=head[h];
	if(temp==NULL)
		printf("\nList is empty\n");
	else
	{	
		printf("\nElements of the list %d are shown below \n\n",h+1);
		while(temp->next!=NULL)
		{
			printf("%d->",temp->value);
			temp=temp->next;
		}	
		if(temp->next==NULL)
			printf("%d\n",temp->value);
	}
}

void delete_all(int h)
{
	list *temp,*temp1=head[h];
	while(temp1!=NULL)
	{
		temp=temp1->next;
		free(temp1);
		temp1=temp;
	}
	head[h]=NULL;
}

void delete_element(int value, int h)
{
	if(head[h]==NULL)
		return; 	
	list *temp,*temp1;
	if(head[h]->value==value)
	{
		temp=head[h];
		head[h]=head[h]->next;
		free(temp);		
	}
	else
	{
		temp=search(value,h);
		if(temp!=NULL)
		{
			temp1=temp->next;
			temp->next=temp1->next;
			free(temp1);
			printf("\nDeletion succeeded \n");
		}
		else
		printf("\n Element not found! \n");
	}
}

void counte(int value,int h)
{
	if(head[h]==NULL)
	{
		printf("\nList is empty\n");
		return;
	}
	int count=0;
	list *temp=head[h];
	while(temp!=NULL)
	{
		if(temp->value==value)
			count++;
		temp=temp->next;
	}
	printf("\nCount of %d is %d\n",value,count);
}

void find_nth(int value,int h)
{
	if(value<1)
		return;
	list *temp=head[h];
	int i=1;
	while(i<value)
	{
		if(temp==NULL)
		{
			printf("\n Oops it didnt work! \n");
			return;
		}
		temp=temp->next;
		i++;
	}
	printf("\nElement at %d node is %d\n",value,temp->value);
}

void pop(int h)
{
	if(head[h]==NULL)
	{
		printf("\n Oops list is empty \n");
	}
	else
	{
		list *temp=head[h];
		printf("\nPopped a node with element %d\n",temp->value);
		head[h]=temp->next;
		free(temp);
	}
}
void insertnth(int node,int value,int h)
{
	list *temp=head[h],*temp1;
	int i=1;
	if(head[h]==NULL)
		printf("\n List is empty\n");
	else if(node==1)
	{
		temp1=(list *)malloc(sizeof(list));
		temp1->value=value;
		temp1->next=temp;
		head[h]=temp1;
	}
	else
	{
		while(i<node)
		{
			temp1=temp;
			if(temp==NULL)
			{
				printf("\n Invalid node \n");
				return;
			}
			temp=temp->next;
			i++;
		}
		temp1->next=(list *)malloc(sizeof(list));
		temp1->next->value=value;
		temp1->next->next=temp;
	}
}

void append(list *l,int h)
{
	l->next=head[h];
	head[h]=NULL;
}

void split(list **l,list **q,int h)
{	
	int i,o;
	if(head[h]==NULL)
		return;
	list *temp=head[h];
	for(i=1;temp->next!=NULL;i++)
		temp=temp->next;
	*q=temp;	
	temp=head[h];
	o=i/2+i%2;
	for(i=1;i<o;i++)
		temp=temp->next;
	head[h+1]=temp->next;
	temp->next=NULL;
	*l=temp;
}

void del(list **l)
{
	list *temp;
	temp=(*l)->next;
	(*l)->next=temp->next;
	free(temp);
}
list *duplicate(int h)
{
	list *temp=head[h];
	while(temp->next!=NULL)
	{
		if(temp->value==temp->next->value)
		{
			del(&temp);
			continue;
		}
		temp=temp->next;
	}
	return temp;
}

list *sort(int h)
{
	if(head[h]==NULL)
		return;
	list *temp_delete=head[h],*temp_head=NULL,*temp_curr=NULL,*temp=head[h],*temp1;
	int min,i=0;
	while(head[h]!=NULL)
	{
		temp1=head[h];
		min=temp1->value;
		while(temp1!=NULL)
		{
			if(temp1->value<min)
				min=temp1->value;
			temp1=temp1->next;	
		}
		if(i==0)
		{
			temp_head=(list*)malloc(sizeof(list));
			temp_head->value=min;
			temp_head->next=NULL;
			temp_curr=temp_head;
		}
		else
		{
			temp_curr=insert(temp_curr,min,h);
		}
		delete_element(min,h);
		i++;
	}
	head[h]=temp_head;
	return temp_curr;		
}

void alternate_split(list **l,list **l_new,int h)
{
	if(*l==NULL)
		return;
	int i=1;
	list *temp=head[h],*temp1,*dl;
	while(temp!=NULL)
	{
		if(i%2==0)
		{
			*l_new=insert(*l_new,temp->value,h+1);
			temp1->next=temp1->next->next;
			dl=temp;
			temp=temp1->next;
			free(dl);			
		}
		else
		{
			temp1=temp;
			*l=temp;
			temp=temp->next;
		}
		i++;

	}
		
}

void reverse(list **l,int h)
{
	list *next,*prev=NULL;
	*l=head[h];
	while(head[h]->next!=NULL)
	{
		next=head[h]->next;
		head[h]->next=prev;
		prev=head[h];
		head[h]=next;
	}
	head[h]->next=prev;		
}

int main()
{
	list *l[MAX_LIST]={NULL};
	int option,u,count=1,i=0;
	while(1)
	{
	
		printf("\n\n----Operations on Linked Lists-----\n\nList selected = %d\t\tNumber of lists=%d\n\n 1 - Insert\n\n 2 - Display \n\n 3 - Delete a element \n\n 4 - Delete the list\n\n 5 - Count the element\n\n 6 - Get nth node\n\n 7 - Pop \n\n 8 - Insert nth node\n\n 9 - Create new list\n\n10 - Switch to other list\n\n11 - Append last two lists\n\n12 - Split the list\n\n13 - Delete duplicates\n\n14 - Sort the list\n\n15 - Alternate Split\n\n16 - Merge and sort the lists\n\n17 - Reverse the list\n\noption = ",i+1,count);
		scanf("%d",&option);
		switch(option)
		{
			case 1:
					printf("\nEnter the element you want to insert = ");
					scanf("%d",&option);
					l[i]=insert(l[i],option,i);
					break;
			case 2:
					display(i);
					break;
			case 3: 
					printf("\n Which element do you want to delete ? \nelement = ");
					scanf("%d",&option);
					delete_element(option,i);
					printf("\nDeletion succeeded \n");
					break;
			case 4: if(count>1)
					{
						printf("\n Last list will be deleted (drawback of this program!)\n");
						delete_all(count-1);
						l[count-1]=NULL;
						count--;
						if(i==count)
						i--;
					}
					else
					{
						printf("\nDeleting the list \n");
						delete_all(0);
						l[i]=NULL;
					}
					printf("\nDeletion succeeded \n");
					break;
			case 5:
					printf("\nElement to be counted in the list = ");
					scanf("%d",&option);
					counte(option,i);
					break;
			case 6:
					printf("\n Enter the node to be found = ");
					scanf("%d",&option);
					find_nth(option,i);
					break;
			case 7:
					pop(i);
					break;
			case 8:
					printf("\nEnter the index of the node = ");
					scanf("%d",&u);
					printf("\nEnter the element = ");
					scanf("%d",&option);
					insertnth(u,option,i);
					break;
			case 9:
					printf("\n New linked list has been created!\n");
					count++;
					break;
			case 10:
					if(count>1)
					{
						printf("\nWhich list do you want to perform operations (Total linked list = %d) = ",count);
					 	scanf("%d",&i);
					 	if(i>count)
					 	{
					 		i=0;
					 		printf("\n Bad list number \n");
					 	}	
					 	else	
							i--;
					}
					break;
			case 11:
					if(count>1)
					{
					printf("\n Appending last two lists\n");
					append(l[count-2],count-1);
					l[count-2]=l[count-1];
					l[count-1]=NULL;
					count--;
					i=count-1;					
					}
					break;	
			case 12:
					printf("\nSpliting the last list\n");
					split(&l[count-1],&l[count],count-1);
					count++;
					break;
			case 13:
					printf("\nDelete the duplicates\nNote:List should be sorted\n");
					l[i]=duplicate(i);
					break;
			case 14:
					l[i]=sort(i);
					printf("\nList has been sorted!\n");
					break;
			case 15:
					printf("\nAlternately spliting the list\n");
					alternate_split(&l[count-1],&l[count],count-1);
					count++;
					break;
			case 16:
					if(count==1)
						continue;
					printf("\nLast two lists will be merged and sorted\n");
					append(l[count-2],count-1);				
					l[count-2]=l[count-1];
					l[count-1]=NULL;
					count--;
					i=count-1;
					l[i]=sort(i);
					break;	
			case 17:
					reverse(&l[i],i);
					printf("\nList has been reversed\n");
					break;				
			default :
					printf("\nDo you want to terminate ?\tyes=1\tno=0\noption = ");
					scanf("%d",&option);
					if(option==1)
					{
						for(option=0;option<=i;option++)
							delete_all(option);
						exit(0);
					}
					else;
		}
		
	}
}
