#include<stdio.h>
#include<stdlib.h>

//definition of each node of a general linked list
//each node being used to store a line number and a command string
typedef struct node LINE;

struct node{

 int index;
 
 char line[100];
 
 LINE *link;

};


//function to create a blank general linked list
//the linked list just created has its index/line no. to be 0(0 indicates that the list is blank
//								for no line in the text input would have 0
//								as its index)
//and the line string is made blank using NULL characters
//also the next link is pointed to NULL to indicate termination of the linked list								       	
LINE *createList()
{
 LINE *listHead;
 int i;
 
 listHead=malloc(sizeof(LINE));
 
 listHead->index=0;
 
 for(i=0;i<100;i++)
 	listHead->line[i]='\0';
 	
 listHead->link=NULL;
 
 return listHead;
}


//function to insert/edit nodes in the structure
//if index of the input line already exists in structure, the previous line gets overwritten
//else, the line input is inserted in its appropiate position in the structure according to its index
LINE *insert(LINE *listHead,int index,char *string)
{
 LINE *pNew;
 int i;
 
 //Case I: list is blank, so no further memory allocation required
 //index of first node is changed from 0 and line is input
 if(listHead->index==0)
 { 	 
  listHead->index=index;
  
  for(i=0;string[i]!='\0';i++)
  	listHead->line[i]=string[i];
  	
  listHead->link=NULL;	
  	
  return listHead;	
 }
 
 
 else
 {	
 	//Case II: list is not blank and input line is to be inserted before the first node
 	//the header is made to point to the new node which has been previously made to point to the list
 	//the header/new node is then altered according to the input
 	if(index<listHead->index)
 	{
 		pNew=malloc(sizeof(LINE));
 		
 		pNew->link=listHead;
 		
 		listHead=pNew;
 		
 		listHead->index=index;
 		
 		for(i=0;i<100;i++)
 			listHead->line[i]='\0';
 			
 		for(i=0;string[i]!='\0';i++)
 			listHead->line[i]=string[i];
 			
 		return listHead;
 	}
 	
 	
 	//Case III: input index matches with a previous index in the list
 	//hence the node with the same index gets it's line string overwritten by input string
 	else if(index==listHead->index)
 	{
 		for(i=0;listHead->line[i]!='\0';i++)
 			listHead->line[i]='\0';
 			
 		for(i=0;string[i]!='\0';i++)
 			listHead->line[i]=string[i];
 			
 		return listHead;
 	}
 	
 	
 	else
 	{
 		//Case IV:line to be inserted is after the last node
 		//last node's pointer(previously made NULL) is made to point towards new node
 		//new node has it's fields changed according to input and next pointer points to NULL to signify termination
 		//of linked list
 		if(listHead->link==NULL)
 		{
 			pNew=malloc(sizeof(LINE));
 			
 			listHead->link=pNew;
 			
 			pNew->index=index;
 			
 			for(i=0;i<100;i++)
 				pNew->line[i]='\0';
 				
 			for(i=0;string[i]!='\0';i++)
 				pNew->line[i]=string[i];
 				
 			pNew->link=NULL;	
 		}
 		
 		//Case V:line to be inserted at a point inside the structure
 		//recursive function call used
 		else			
 			listHead->link=insert(listHead->link,index,string);
 		
 		return listHead;
 	}
 }
} 			


//function to erase a line in the structure if index matches with the input index
LINE *erase(LINE *listHead,int index)
{
 LINE *pPre,*pWalker,*pDel;
 int i;
 
 //if strcuture is blank
 if(listHead->index==0)
 {
 	printf("NO LINE PRESENT IN DOCUMENT!\n");
 	
 	return listHead;
 }
 
 //Case I:if index matches with header's index	
 if(listHead->index==index)
 {
 	//if there is just one node in the list
 	//header's index is set to 0 and line is made blank
 	if(listHead->link==NULL)
 	{
 		listHead->index=0;
 		
 		for(i=0;i<100;i++)
 			listHead->line[i]='\0';
 			
 		return listHead;	
 	}
 	
 	//if there are more than one node in the list
 	//header is made to point to second node and first node is deleted	
 	else
 	{
 		pDel=listHead;
 		
 		listHead=listHead->link;
 		
 		free(pDel);
 		
 		return listHead;
 	}
 }
 
 //Case II:if the first node's index doesn't match the input index
 if(listHead->index!=index)
 {
 	//Case IIa:if there is no second node
 	//index to be deleted is not in strcuture
 	if(listHead->link==NULL)
 	{
 		printf("INDEX NOT PRESENT IN DOCUMENT!\n");
 		
 		return listHead;
 	}
 	
 	
 	//Case IIb:if there are more nodes	
 	pPre=listHead;
 	pWalker=listHead->link;
 	
 	//Loop performing sequential traversal through list searching for a match in index
 	//deletes node if index is found after readjusting pointer of node to be deleted
 	while(pWalker->link!=NULL)
 	{
 		if(pWalker->index==index)
 		{
 			pPre->link=pWalker->link;
 			
 			free(pWalker);
 			
 			return listHead;
 		}
 		
 		else
 		{
 			pPre=pPre->link;
 			
 			pWalker=pWalker->link;
 		}
 	}
 	
 	//if last node is node to be deleted after list is traversed
 	if(pWalker->index==index)
 	{
 		free(pWalker);
 		
 		pPre->link=NULL;
 		
 		return listHead;
 	}
 	
 	//if index is not found after entire list is traversed
 	else
 	{
 		printf("INDEX NOT PRESENT IN DOCUMENT!\n");
 		
 		return listHead;
 	}
 }
} 									


//function to print the list by iterartion using a walker pointer
void printList(LINE *listHead)
{
 LINE *pWalker;
 
 pWalker=listHead;
 
 if(listHead->index==0)
 	printf("DOCUMENT HAS NO LINES TO DISPLAY!\n");
 	
 else
 {
 	while(pWalker->link!=NULL)
 	{
 		printf("%d %s\n",pWalker->index,pWalker->line);
 	
 		pWalker=pWalker->link;
 	}
 	
 	printf("%d %s\n",pWalker->index,pWalker->line);
 	
 }
}


//function which readjusts index numbers of the lines in the list as consecutive multiples of 10 by iterartion
LINE *renumber(LINE *listHead)
{
 int i=1;
 LINE *pWalker=listHead;
 
 if(listHead->index==0)
 {
 	printf("NO DATA IN DOCUMENT TO RENUMBER!\n");
 	
 	return listHead;
 }
 
 else
 {
	while(pWalker->link!=NULL)
	{
		pWalker->index=10*i;
		
		i++;
		
		pWalker=pWalker->link;
	}
	
	pWalker->index=10*i;
	
	printList(listHead);
	
	return listHead;
 }
} 		


//function to detroy list by freeing allocated memeory node by node using iteration via a walker pointer 
LINE *destroyList(LINE *listHead)
{
 LINE *pWalker;
 
 pWalker=listHead;
 
 while(pWalker->link!=NULL)
 {
 	listHead=listHead->link;
 	
 	free(pWalker);
 	
 	pWalker=listHead;
 }
 
 free(listHead);
 
 return listHead;
} 


//function that creates a file <filename>.BAS where <filename> is passed as argument to function as a string
//if file by same name already exists function provides a warning before erasing previous contents of file
void createFile(char *fName)
{
 int i;
 FILE *file;
 char reply;
 
 for(i=0;fName[i]!='\0';i++);
 
 fName[i++]='.';
 fName[i++]='B';
 fName[i++]='A';
 fName[i++]='S';
 fName[i]='\0';

 file=fopen(fName,"r");
 
 if(file!=NULL)
 {
 	printf("File by same filename already EXISTS!\nAre you sure you want to overwrite it and create a NEW file?(y/n)\n");
 	scanf("%c",&reply);
 	getchar();
 	fclose(file);
 	
 	if(reply=='y' || reply=='Y')
 	{
 		fopen(fName,"w");
 		fclose(file);
 	}	
 }
 
 else
 {	
 	file=fopen(fName,"w");
 	fclose(file);
 }	
 
} 


//function to open <filename>.BAS where <filename> is passed as argument as a string
//if file doesn't exist it returns NULL
//else, it opens file in "read" mode and puts the contents and line numbers in a linked list and returns the list
LINE *openFile(char *fName)
{
 LINE *listHead;
 FILE *file;
 char a;
 int i=0,j=0,flag=0;
 char string[100];
 
 for(i=0;i<100;i++)
 	string[i]='\0';
 
 for(i=0;fName[i]!='\0';i++);
 
 fName[i++]='.';
 fName[i++]='B';
 fName[i++]='A';
 fName[i++]='S';
 fName[i]='\0';

 file=fopen(fName,"r");
 
 if(file==NULL)
 	return NULL;
 	
 i=0;
 
 listHead=createList();
 
 while(1)
 {
  	a=getc(file);
  
 	if(flag==0 && a>='0' && a<='9')
  	{
  		while(1)
  		{
  			i=10*i+a-'0';
  			
  			a=fgetc(file);
  		
  			if(a==' ')
  			{
  				flag=1;
  				
  				break;
  			}	
  		}		
 	 }			 	
  
  	else if(a!='\n' && a!=EOF)
  		string[j++]=a;
  	
  	else if(a=='\n' || a==EOF)
  	{
  		
  		listHead=insert(listHead,i,string);
  		
  		if(a==EOF)
  			break;
  		
  		i=0;
  	
  		for(j=j;j>0;j--)
  			string[j-1]='\0';
  			
  		
  		flag=0;	
 	 }
 }
 
 fclose(file);

 return listHead;
 
} 


//saves contents of the linked list into <filename>.BAS where <filename> is passed as argument as a string
//returns 0 if file doesn't exist
//returns 1 if file is successfully saved
int saveFile(char *fName, LINE *listHead)
{
 FILE *file;
 int i;
 LINE *pWalker=listHead;
 
 for(i=0;fName[i]!='\0';i++);
 
 fName[i++]='.';
 fName[i++]='B';
 fName[i++]='A';
 fName[i++]='S';
 fName[i]='\0';
 
 file=fopen(fName,"r");
 
 if(file==NULL)
 	return 0;
 	
 else
 {
 	fclose(file);
 	
 	file=fopen(fName,"w");
 	
 	while(pWalker->link!=NULL)
 	{
 		fprintf(file,"%d %s\n",pWalker->index,pWalker->line);
 		
 		pWalker=pWalker->link;
 	}
 	
 	fprintf(file,"%d %s",pWalker->index,pWalker->line);
 }
 
 fclose(file);
 
 return 1;
 
}  


//deletes <filename>.BAS wher<filename> is passed as argument as a string
//returns 0 if file does not exist
//returns 1 if file is successfully deleted
int removeFile(char *fName)
{
 int i;
 FILE *file;
 
 for(i=0;fName[i]!='\0';i++);
 
 fName[i++]='.';
 fName[i++]='B';
 fName[i++]='A';
 fName[i++]='S';
 fName[i]='\0';
 
 file=fopen(fName,"r");
 
 if(file==NULL)
 	return 0;
 	
 else
 {
  fclose(file);
  
  remove(fName);
  
  return 1;
 }
 
}											 	
