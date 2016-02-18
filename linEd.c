//the driver through which the line editor is run
//the functions are defined in line.h

#include"line.h"

main()
{
 LINE *listHead;
 char s[100],string[100],fName[20],reply;
 int index,i,j,flag=1;
 
 system("clear");
 
 listHead=createList();
 
 printf("=========================================Welcome to LinEd==========================================\n\n\n");	 
 
 while(1)
 {
  
  printf(">");
  gets(s);
  index=0;
  
  if(s[0]=='c' && s[1]=='r' && s[2]=='e' && s[3]=='a' && s[4]=='t' && s[5]=='e' && s[6]==' ')
  {
  	
  	if(s[7]=='\0')
  		printf("Provide a <filename> to create <filename>.BAS !\n");
  		
  	else
  	{
  		for(i=0;i<20;i++)
  			fName[i]='\0';
  		
  		for(i=7,j=0;s[i]!='\0';i++,j++)
  			fName[j]=s[i];
  			
  		createFile(fName);
  	}
  }
  
  else if(s[0]=='o' && s[1]=='p' && s[2]=='e' && s[3]=='n' && s[4]==' ')
  {
  	if(listHead->index!=0)
  	{
  		printf("Opening new file will result in loss of data! Are you sure you want to continue?(y/n)\n");
  		scanf("%c",&reply);
  		getchar();
  		
  		if(reply=='n' || reply=='N')
  			continue;
  			
  		if(reply=='y' || reply=='Y')
  		{
  			listHead=destroyList(listHead);
  			listHead=createList();
  		}		
  	}
  		
  	if(s[5]=='\0')
  		printf("Provide a <filename> to open <filename>.BAS !\n");
  		
  	else
  	{
  		for(i=0;i<20;i++)
  			fName[i]='\0';
  		
  		for(i=5,j=0;s[i]!='\0';i++,j++)
  			fName[j]=s[i];
  			
  		listHead=openFile(fName);
  		
  		if(listHead==NULL)
  		{
  			printf("NO such file EXISTS!\n");
  			
  			listHead=createList();
  		}	
  	}
  }
  
  else if(s[0]=='s' && s[1]=='a' && s[2]=='v' && s[3]=='e' && s[4]==' ')
  {
  	 if(s[5]=='\0')
  		printf("Provide a <filename> to save <filename>.BAS !\n");
  		
  	else
  	{
  		for(i=0;i<20;i++)
  			fName[i]='\0';				
  			
  		for(i=5,j=0;s[i]!='\0';i++,j++)
  			fName[j]=s[i];
  			
  		if(!(saveFile(fName,listHead)))
  			printf("NO such file EXISTS!\n");
  	}
  	
  	flag=1;
  }
  
  else if(s[0]=='r' && s[1]=='e' && s[2]=='m' && s[3]=='o' && s[4]=='v' && s[5]=='e' && s[6]==' ')
  {
  	if(s[7]=='\0')
  		printf("Provide a <filename> to remove <filename>.BAS !\n");											
  	
  	else
  	{
  		for(i=0;i<20;i++)
  			fName[i]='\0';
  		
  		for(i=7,j=0;s[i]!='\0';i++,j++)
  			fName[j]=s[i];
  			
  		if(removeFile(fName)==0)
  			printf("NO such file EXISTS!\n");
  	}
  }
  				
  else if(s[0]=='e' && s[1]=='x' && s[2]=='i' && s[3]=='t' && s[4]=='\0')
  {
  	if(flag==1)
  		break;
  		
  	else
  	{
  		printf("Are you sure you want to exit without saving?(y/n)\n");	
  		scanf("%c",&reply);
  		getchar();
  		
  		if(reply=='Y' || reply=='y')
  			break;
  	}
  }			
  
  else if(s[0]>='0' && s[0]<='9')
  {
  	for(i=0;s[i]!='\0' && s[i]!=' ';i++)
  		index=10*index + (s[i]-'0');
  		
  	if(s[i]=='\0')
  		listHead=erase(listHead,index);
  		
  	else if(s[i]==' ')
  	{
  		i++;
  		
  		for(i=i,j=0;s[i]!='\0';i++,j++)
  			string[j]=s[i];
  			
  		string[j]='\0';
  		
  		listHead=insert(listHead,index,string);
  	}
  	
  	flag=0;
  }
  
  else if(s[0]=='r' && s[1]=='\0')
  {
  	listHead=renumber(listHead);
  	
  	flag=0;
  }	
  	
  else if(s[0]=='l' && s[1]=='\0')
  	printList(listHead);				
  
  else
  	printf("UNIDENTIFIED COMMAND INPUT!\n");
 }
 
 listHead=destroyList(listHead);

 system("clear");
 
}		
