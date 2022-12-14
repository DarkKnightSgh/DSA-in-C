#include<stdio.h>
#include<stdlib.h>
#include"sll.h"

void initList(LLIST *pl)
{
	pl->head=NULL;
}

NODE* createNode(int ele)
{
	NODE *newNode=malloc(sizeof(NODE));
	newNode->info=ele;
	newNode->next=NULL;
	
	return newNode;
}
void insertFront(LLIST *pl,int ele)
{
	NODE* newNode=createNode(ele);
	
	newNode->next=pl->head;
	pl->head=newNode;
}

void insertLast(LLIST *pl,int ele)
{
	NODE* newNode=createNode(ele);
	
	NODE* p=pl->head;
	
	if(pl->head==NULL)	//List is empty
	{
		pl->head=newNode;
	}
	else
	{
		while(p->next!=NULL)
			p=p->next;
		
		p->next=newNode;
	}
}
void display(LLIST *pl)
{
	NODE *p=pl->head;
	
	if(pl->head==NULL)
		printf("List is empty\n");
	else
	{
		while(p!=NULL)
		{
			printf("%d ",p->info);
			p=p->next;
		}
	}
}
/*
Precondition: List is already created and not empty
*/
int deleteFront1(LLIST *pl)
{
	NODE *p=pl->head;
	int ele;
	
	ele=p->info;				//ele=pl->head->info;
	pl->head=pl->head->next;	//pl->head=p->next;
	free(p);
	return ele;
}

/*List is created and may be empty or may have nodes*/
//Return value: indicates success or failure status
int deleteFront2(LLIST *pl,int *pele)
{
	NODE *p=pl->head;
	
	if(pl->head==NULL)
		return 0;
	else
	{
		*pele=p->info;		//*pele=pl->head->info
		pl->head=pl->head->next;
		free(p);
		return 1;
	}
	
}
/* 
int deleteFront2(LLIST *pl,int *pele)
{
	NODE *p=pl->head;
	int retValue;
	if(pl->head==NULL)
		retValue=0;
	else
	{
		*pele=p->info;		//*pele=pl->head->info
		pl->head=pl->head->next;
		free(p);
		retValue=1;
	}
	return retValue;
} */

void destroyList(LLIST *pl)
{
	NODE *p;
	
	while(pl->head!=NULL)
	{
		p=pl->head;
		pl->head=pl->head->next;	//pl->head=p->next;
		printf("%d freed\n",p->info);
		free(p);
	}
}

//Precondition: List is already created and not empty
int deleteLast(LLIST *pl)
{
	NODE *p=pl->head;
	int ele;
	if(p->next==NULL)//if(pl->head->next==NULL)//single node case
	{
		ele=p->info;
		free(p);
		pl->head=NULL;
	}
	else
	{
		while(p->next->next!=NULL)
			p=p->next;
		
		ele=p->next->info;
		free(p->next);
		p->next=NULL;
	}
	return ele;
}

int countNodes(LLIST *pl)
{
	/*
	Think of hare and tortoise algo to find count nodes
	*/
	NODE *p=pl->head;
	int count=0;
	
	if(pl->head==NULL)
		return count;
	else
	{
		while(p!=NULL)
		{
			count++;
			p=p->next;
		}
		return count;
	}
}

int insertAtPos(LLIST *pl,int ele,int pos)
{
	int n=countNodes(pl);
	
	NODE *p,*newNode;
	if(pos<0 || pos>n)
		return 0;
	else if(pos==0)
	{
		insertFront(pl,ele);
		return 1;
	}
	else
	{
		p=pl->head;
		newNode=createNode(ele);
		
		for(int i=1;i<pos;i++)
			p=p->next;
		
		newNode->next=p->next;
		p->next=newNode;
		return 1;
	}
}
int deleteAtPos(LLIST *pl,int *pele,int pos)
{
	int n=countNodes(pl); // not efficient
	
	NODE *q=NULL,*p=pl->head;
	
	if(pos<0 || pos>=n)
		return 0;
	else if(pos==0)
	{
		return deleteFront2(pl,pele);
	}
	else
	{
		for(int i=0;i<pos;i++)
		{
			q=p;// prev
			p=p->next; //next ptr
		}
		*pele=p->info;
		q->next=p->next;
		free(p);
		return 1;
	}
}