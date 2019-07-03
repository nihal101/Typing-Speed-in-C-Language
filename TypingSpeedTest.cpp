#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<conio.h>
#include<dirent.h>
#include<stdlib.h>
#define null 0
void countAccuracy(char*,char*);
float countCharacterAccuracy(char*,char*);
float countWordAccuracy(char*,char*);

struct Node* root=null;

struct Node
{
	char fileName[20];
	struct Node* next;
};

char inbuiltData[100]={"This is your data. Start typing here"};
double timeTaken;
char typedData[100];
int countC=0,countW=0,wrongCharacter=0,wrongWord=0;
int countCharacter(char* p)
{
	int nCharacter=0;
	for(int i=0;*(p+i)!='\0';i++)
	{
		nCharacter++;
	}
	return nCharacter;
}
int findLength(char* p)
{
	int length=0;
	for(int i=0;*(p+i)!='\0';i++)
	{
		length++;
	}
	return length;
}
int countWord(char* p)
{
	int nWord=0,length;
	length=findLength(p);
	for(int i=0;i<length;i++)
	{
		if(*(p+i)==' ')
		{
			nWord++;
		}
	}
	return nWord;
}
void start()
{
	int loop=5;
	printf("\nstart in...  ");
	while(loop--)
	{   
	    printf("%d  ",loop);
		sleep(1);
	}
}
char* getTypedData()
{
	clock_t start,end;
	start=clock();
	getchar();
	fgets(typedData,100,stdin);
	typedData[findLength(typedData)-1]=' ';
	end=clock();
	timeTaken=difftime(end,start)/1000;
	return typedData;
}
void process(char* inbuiltData1)
{
	int totalWord,totalCharacter;
    getTypedData();
	totalWord=countWord(typedData);
	totalCharacter=countCharacter(typedData)-1;
	printf("\n\n\t\tTotal Time:  %lf",timeTaken);
	printf("\n\t\tTotal Word:  %d",totalWord);
	printf("\n\t\tTotal Character: %d",totalCharacter);
	countAccuracy(typedData,inbuiltData1);
}

void countAccuracy(char* td,char* id)
{
	float accuracyC,accuracyW;
	accuracyC=countCharacterAccuracy(td,id);
	accuracyW=countWordAccuracy(td,id);
	printf("\n\t\tCharacter Accuracy:  %f",accuracyC);
}
float countCharacterAccuracy(char* td,char* id)
{
	float count=0,ilen,tlen;
	float acc;
	tlen=findLength(td)-1;
	for(int i=0;i<tlen;i++)
	{
		if(*(td+i)==*(id+i))
		{
			count++;
		}
	}
    wrongCharacter=tlen-count;
	acc=(count/tlen)*100.0;
	return acc;
}


  void equal(char* ch1,char* ch2)
{
   int len,i=0;
   len=findLength(ch1);
   if(findLength(ch1)==findLength(ch2))
   {
   	    for( i=0;i<len;i++)
        {
   	        if(*(ch1+i)!=*(ch2+i))
   	        {
   	  	        break;
	        }
        }
   }
   else
   {
   	    return;
   }
   
  
   if(i==len)
   {
   	countW++;
   }else
   {
         
   }
}

int findWord(char* ch,int num,char* s)
{
	int length=findLength(ch),i,j=0;
	for( i=num;i<length;i++)
	{
	    if(*(ch+i)==' ')
	    {
	        num++;
		    break;
	    }
	  else
	    {
		    *(s+j)=*(ch+i);
		    j++;
		    num++;
    	}
	}
    *(s+j)='\0';
	return num;
}

float countWordAccuracy(char*td,char* id)
{
	int len=0;
	int total=0;
	char p[20],p1[20];
	static int num=0,num1=0;
	float accuracyW;
	len=findLength(td);
	total=countWord(td);
	for(int i=0;i<total;i++)
	{
		num=findWord(id,num,p);
	    num1=findWord(td,num1,p1);
	    equal(p,p1);
	}
	wrongWord=total-countW;
	accuracyW=(countW*100.0)/total;
	printf("\n\t\tWord Accuracy:  %f",accuracyW);
}
void printWrong()
{
	printf("\n\n");
    printf("\n\t\tWrong Character:  %d%",wrongCharacter);
    printf("\n\t\tWrong Word:  %d%",wrongWord);
		
}

struct Node* createNode()
{
	struct Node* temp;
	temp=(struct Node*)malloc(sizeof(struct Node));
	return temp;
}

void push(char* ch,struct Node* obj,int len)
{
	int i=0;
	struct Node* temp;
	for( i=0;i<len;i++)
	{
		obj->fileName[i]=*(ch+i);
	}
	obj->fileName[i]='\0';
	obj->next=null;
	if(root==null)
	{
		root=obj;
	}else
	{
	    temp=root;
		while(temp->next)
		{
			temp=temp->next;
		}
		temp->next=obj;		
	}
}

struct Node* pop(int num)
{
	struct Node* temp=root;
	int i=1;
	while(i<num)
	{
		temp=temp->next;
		i++;
	}
	return temp;
}


char* createPath(char* path,int num)
{
	struct Node* temp;
	int len1,len2,i=0;
	temp=pop(num+2);
	len1=findLength(path);
	len2=findLength(temp->fileName);
	for( i=0;i<len2;i++)
	{
		*(path+len1+i)=*(temp->fileName+i);
	}
	*(path+len1+i)='\0';
	return path;
}

void readDataFromFile(FILE* p)
{
   if(p)
   {
   	    char dataFromFile[1000];
        fread(dataFromFile,1000,1,p);
        printf("\n\n\t%s",dataFromFile);
        printf("\n\n\n");
        start();
        printf("Go\n\n\t\t");
        process(dataFromFile);
        printWrong();
   }else
   {
   	  printf("some wrong");
   }
	
	
}


void enterChoice(char* path)
{
	int num;
	FILE* file;
	printf("\n\nenter file number\t");
	scanf("%d",&num);
	path=createPath(path,num);
	file=fopen(path,"r");
	readDataFromFile(file);
}

void getDataPath()
{
	char path[100];
	DIR *d;
	struct dirent *dir;
	FILE* p;
	struct Node* obj;
	scanf("%s",path);
	d=opendir(path);
	if(d)
	{
		while((dir=readdir(d))!=NULL)
		{
		    printf("%s\n",dir->d_name);
			obj=createNode();
			push(dir->d_name,obj,findLength(dir->d_name));	
		}
		enterChoice(path);
	}else
	{
		p=fopen(path,"r");
		if(p)
		{
			readDataFromFile(p);
		}else
		{
			printf("enter valid path");
		}
	}
}
int main()
{
   int choice;
   printf("-----------------------------------Welcome To Typing Speed-----------------------------------\n\n\t");
   printf("1.Use inbuilt data\n\t2.Use Your data\n\n");
   printf("enter choice\n\n\t");
   scanf("%d",&choice);
   switch(choice)
   {
   	    case 1:
   	    	printf("\n\n\t\t%s",inbuiltData);
   	    	start();
   	    	printf("Go\n\n\t\t");
   	    	process(inbuiltData);
   	    	printWrong();
   	    	break;
   	    	
   	    case 2:
		   printf("enter path where your data is present\t");
		   getDataPath();
		   break;
		   
		default:
		    printf("enter valid choice");   	
   }
   getch();
   return 0;
}
