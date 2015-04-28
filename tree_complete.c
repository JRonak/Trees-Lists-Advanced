#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct tree
{
	int value;
	struct tree* right;
	struct tree* left;
}tree;

tree* create_tree(int value)
{
	tree *temp;
	temp=(tree*)malloc(sizeof(tree));
	temp->value=value;
	temp->right=temp->left=NULL;
	return temp;
}

void insert(tree* t,int value)
{
	if(t)
	{
		if(t->value>value)
		{
			if(t->left==NULL)
				t->left=create_tree(value);
			else
				insert(t->left,value);	
		}
		else
		{
			if(t->right==NULL)
				t->right=create_tree(value);
			else
				insert(t->right,value);	
		}
}
}

void display_inorder(tree *t)
{
	if(t)
	{
		display_inorder(t->left);
		printf("%d\n",t->value);
		display_inorder(t->right);
	}
}

void display_preorder(tree *t)
{
	if(t)
	{
		printf("%d\n",t->value);
		display_preorder(t->left);
		display_preorder(t->right);
	}
}

void display_postorder(tree *t)
{
	if(t)
	{
		display_postorder(t->left);
		display_postorder(t->right);
		printf("%d\n",t->value);
	}
}

void delete_all(tree *t)
{
	if(t!=NULL)
	{
		tree *temp=t->left,*temp2=t->right;
		free(t);
		delete_all(temp);
		delete_all(temp2);				
	}
}

int search(tree *t,int value)
{
	static int level=0;
	if(t)
	{	
		level++;
		if(t->value==value)
			return level;
		else if(t->value>value)
			return search(t->left,value);
		else
			return search(t->right,value);
	}
}

void find_level(tree *t,int value)
{
	int level=0;
	level=search(t,value);
	if(level==0)
		printf("\nKey not found\n");
	else
		printf("\n%d found at level %d",value,level);	
}

int find_height(tree *t)
{
	int r,l;
	if(t)
	{
		l=1+find_height(t->left);
		r=1+find_height(t->right);
		if(l>r)
			return l;
		else
			return r;
	}
	return 0;
}

int no_nodes(tree *t)
{
	int i=0,r=0,l=0;
	if(t->left!=NULL)
		l=no_nodes(t->left);
	if(t->right)
		r=no_nodes(t->right);
	i=1+l+r;
	return i;
}

void path_sum(tree *t,int key)
{
	static int i=1;
	key+=t->value;
	if(t->left==NULL&&t->right==NULL)
			printf("%d.Pathsum=%d\n",i++,key);	else
	{
		if(t->left!=NULL)
			path_sum(t->left,key);
		else
			printf("%d.Pathsum=%d\n",i++,key);
		
		if(t->right!=NULL)
			path_sum(t->right,key);
		else
			printf("%d.Pathsum=%d\n",i++,key);	}
	
}

void check_sum(tree *t,int key,int check)
{
	key+=t->value;
	if(t->left==NULL&&t->right==NULL)
		if(key==check)
			printf("Checksum verified\n");	
	else
	{
		if(t->left!=NULL)
			check_sum(t->left,key,check);
		else
			{
				if(key==check)
					printf("Checksum verified\n");
			}	
		if(t->right!=NULL)
			check_sum(t->right,key,check);
		else
			{
				if(key==check)
					printf("Checksum verified\n");
			}
	}
	
}

void mirror(tree *t)
{
	tree *temp;
	if(t!=NULL)
	{
		temp=t->left;
		t->left=t->right;
		t->right=temp;
	}
	if(temp->left!=NULL)
		mirror(t->left);
	if(temp->right!=NULL)
		mirror(t->right);
}

void duplicate(tree *t)
{
	tree *temp;
	if(t)
	{
		temp=(tree*)malloc(sizeof(tree));
		temp->value=t->value;
		temp->left=t->left;
		temp->right=NULL;
		t->left=temp;
	}	
	if(temp->left!=NULL)
		duplicate(temp->left);
	if(t->right!=NULL)
		duplicate(t->right);
}

tree *search_node(tree **head,int value)
{
	tree *temp=NULL;
	while(*head)
	{	
		if((*head)->value==value)
			return temp;
		temp=*(head);
		if((*head)->value>value)
			(*head)=(*head)->left;
		else
			(*head)=(*head)->right;
	}	
}

tree *delete_node(tree *t,int key)
{
	tree *head=t,*prev=search_node(&t,key),*max,*max_par=NULL;
	if(t)
	{
		if(t->left)
		{
			max=t->left;
			while(max->right)
			{
				max_par=max;
				max=max->right;
			}
			if(max_par)
			{
				t->value=max->value;
				max_par->right=max->left;
				free(max);
			}
			else
			{
				t->value=max->value;
				free(max);
				t->left=NULL;
			}
		}
		else if(!prev)
		{
			if(prev->value>key)
				prev->left=t->right;
			else
				prev->right=t->right;
			free(t);
		}
		else
		{
			head=t->right;
			free(t);
			return head;
		}
		
	}
	return head;
	
			
} 

int main()
{
	tree *head=NULL;
	int option;
	char num;
	while(1)
	{
		option=0;
		printf("\n\n1 - Insert\n\n2 - Display Inorder\n\n3 - Display postorder\n\n4 - Display preorder\n\n5 - Delete all\n\n6 - Multiple inputs\n\n7 - Level of a key\n\n8 - Find the height\n\n9 - Total number of nodes\n\n10 - Path Sum\n\n11 - Check Sum\n\n12 - Mirror the tree\n\n13 - Duplicate\n\n14 - Delete node\n\n15 - Terminate\n\noption = ");
		scanf(" %d",&option);
		switch(option)
		{
			case 1:
					printf("\nKey = ");
					scanf("%d",&option);
					if(head==NULL)
						head=create_tree(option);
					else
						insert(head,option);
					puts("Insertion completed\n");
					break;
			case 2:
					if(head!=NULL)
						printf("\nInorder Tree\n");
					display_inorder(head);
					break;
			case 3:
					if(head!=NULL)
						printf("\nPostorder Tree\n");
					display_postorder(head);
					break;
			case 4:
					if(head!=NULL)
						printf("\nPreorder Tree\n");
					display_preorder(head);
					break;
			case 5:
					if(head!=NULL)
						printf("\nDelete\n");
					delete_all(head);
					head=NULL;
					break;
			case 6:
					printf("\nEnter the numbers! (type d to stop)\n");
					printf("\nEnter the keys \n");
					while(1)	
					{
						scanf(" %c",&num);
						if(num=='d')
							break;
						if(head==NULL)
							head=create_tree(num-'0');
						else
							insert(head,num-'0');
					}
					break;
			case 7:
					if(head!=NULL){
					printf("\nENter the number whose level has to found = ");
					scanf("%d",&option);
					find_level(head,option);	
					}
					break;
			case 8:
					if(head!=NULL)
					{
						printf("\nThe height of the tree = ");
						option=find_height(head);
						printf("%d",option);
					}			
					break;
			case 9:
					if(head!=NULL)
					{
						printf("\nNumber of nodes = ");
						option=no_nodes(head);
						printf("%d\n",option);
					}
					break;
			case 10:
					if(head!=NULL)
						path_sum(head,0);
					break;
			case 11:
					if(head!=NULL)
					{
						printf("Enter the check sum = ");
						scanf("%d",&option);
						check_sum(head,0,option);
					}
					break;
			case 12:
					if(head!=NULL)
						mirror(head);
					break;
			case 13:
					if(head!=NULL)
						duplicate(head);
					break;
			case 14:
					if(head)
					{
						printf("Enter the key to be deleted = ");
						scanf("%d",&option);
						delete_node(head,option);
					}
					break;
			default:
					printf("\nTerminating\n");
					delete_all(head);
					exit(0);
		}

	}
}
