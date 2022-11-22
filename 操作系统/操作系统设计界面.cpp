#include<bits/stdc++.h>
#define m 3
using namespace std; 

typedef struct PCB 
{//定义进程控制快PCB
	float ID;       //进程标识符 
	int Priority;     //进程优先数
	int Needtime;      //进程还需要运行时间 
	int CPUtime;      //已用CPU的时间 
	int State;        //状态（0--阻塞   1--就绪  2--执行） 
	float father;     //父进程
	float child;      //子进程
	int Max[m];       //最大需求
	int Allocation[m];//已分配
	int Need[m];      //需求 
	PCB *next;        //队列指针 
	int atime;
}pcb; 

class Queue
{
	public:
		Queue():rear(NULL),first(NULL){};         //声明构造函数并初始化是头节点和尾节点都为空
	    ~Queue();                                 //声明析构函数 
	    void enqueue(pcb *p);                     //声明入队函数 
	    void dequeue(pcb *p);                     //声明出队函数 
	    bool isempty(){return first==NULL&&rear==NULL;}//判队列空否 
	    void del(float id);                       
	    void display();                           //显示函数 
	    int find(float id);                       
	    void search1(float id,int x);             
	    float search2(float id,int x);            
	private:
	    pcb *first,*rear;                         //头指针和尾指针 
};
float a[8]={-1,-1,-1,-1,-1,-1,-1,-1};
Queue execute,ready,block;   //定义就绪阻塞执行队列（execute--执行  ready--就绪  block--阻塞）
PCB *ready_queue,*block_queue,*idleprocess; 
int num=0;     //进程数
int Available[m];   //定义资源
void output();   //输出函数，输出队列中进程的信息
void clean();    //清屏函数
void menu();     //菜单函数
void create();   //创建函数，创建进程并将进程送入就绪队列
void createchild(pcb *p);  //创建子进程函数，创建子进程并继承父进程资源
void run();   //执行函数，无进程运行可将进程送入执行队列
void lock();  //阻塞函数，将执行队列中的进程阻塞并送入阻塞队列
void change();  //唤醒函数，将阻塞队列中的进程唤醒送入就绪队列
void revoke();  //撤销函数，将进程从相应队列中删除，并修改子进程父进程信息
void jixu();//选择是否继续运行或退出程序 
void readTxt(string file);
void LRU();
void LFU(); 
void OPT();
Queue::~Queue()
{
	pcb *p;
	while(first!=NULL)
	{
		p=first;
		first=first->next;
		delete p;
	}
}

void Queue::enqueue(pcb *p)
{
	if(first==NULL)
	{
		first=p;
		first->next=NULL;
	}	
	else
	{
		rear->next=p;
	}
	rear=p;	
	rear->next=NULL;
}

void Queue::dequeue(pcb *p)
{
	p->Needtime=first->Needtime;
	p->child=first->child;
	p->CPUtime=first->CPUtime;
	p->father=first->father;
	p->ID=first->ID;
	p->Priority=first->Priority;
	p->State=first->State;
	for(int i=0;i<3;i++)
	{
		p->Allocation[i]=first->Allocation[i];
		p->Max[i]=first->Max[i];
		p->Need[i]=first->Need[i];
	}
	first=first->next;
	if(first==NULL)
	{
		rear=NULL;
	}
}

void Queue::display() 
{
	pcb *p;
	p=first;
	cout<<"*****************************************************************************"<<endl;
    cout<<"进程名\t优先级\t到达时间  运行时间  需要时间  状态  父进程  子进程   A  B  C"<<endl;
	while(p!=NULL)
	{
		cout<<"  "<<p->ID<<"\t  "<<p->Priority<<"\t  "<<p->atime<<"\t      "<<p->CPUtime<<"\t      "<<p->Needtime<<"\t        "<<p->State<<"      "<<p->father<<"      "<<p->child<<"     ";
        for(int i=0;i<3;i++)     	
            cout<<p->Allocation[i]<<"  ";
        cout<<endl;
		p=p->next;
	}
}

Queue::find(float id)
{
	pcb *p;
	p=first;
	while(p!=NULL)
	{
		if(id==p->ID)
		{
			return 1;
			break;
		}
		else
			p=p->next;
	}
	return 0;
}

void Queue::del(float id)
{
	pcb *p,*t;
	p=first;
	while(id!=p->ID&&p!=NULL)
	{
		t=p;
		p=p->next;	
	}
	if(p==first)
	{
		first=first->next;
		delete p;
	}	
	else 
	{
		if(p==rear)
		{
			rear=t;
			rear->next=NULL;
			delete p;	
		}
		else
		{
			t->next=p->next;
			delete p;
		}
	}
}

void Queue::search1(float id,int x)
{//进程撤销时查找有没有子进程和父进程 
	pcb *p;
	p=first;
	while(p!=NULL)
	{	
		if(id==p->ID)
		{
			if(x==1)   //1查找有没有父进程
				p->child=0;
			else
				p->father=0;
			break;
		}
		p=p->next;
	}
}

float Queue::search2(float id,int x)
{
	pcb *p;
	p=first;
	while(p!=NULL)
	{
		if(id==p->ID)
		{
			for(int i=0;i<3;i++)
				Available[i]=Available[i]+p->Allocation[i];
			if(x==1)
				return p->father;
			else
				return p->child; 
		}
		else
			p=p->next;
	}
} 

void create()
{//创建进程--根据进程的顺序依次放入就绪队列，并创建其子进程副本
    srand((int)time(0)); //随机生成 
	clean();
	pcb *p;
	int  k,j;
	float id;
	int q=0;
	cout<<"\t请输入进程名（按到达顺序输入，输入ID=0结束）"<<endl;
	for(int i=0;;i++)
	{
		cout<<"\t请输入进程ID：";
		cin>>id;
		for(k=0;k<8;k++)
		{
			if(id==a[k])
			{
				j=k;
				q=1;
				break;
			}
		}
		if(q!=1)
		{
			a[j]=id;
		}
		else
		{
			cout<<"\t\t\t\t!!!ID重复，请重新输入!!!"<<endl<<endl;
			create();
		}
		if(id==0)
			break;
		else
		{
			p=new pcb;
			p->ID=id;
			p->atime=id;
			cout<<endl<<"\t请输入进程优先数：";
			p->Priority=rand()%3;
			cout<<p->Priority<<endl;
			cout<<endl<<"\t请输入所需运行时间(Needtime)：";
			p->Needtime=rand()%10;
			cout<<p->Needtime<<endl;
			cout<<endl<<"\t请输入进程所需的各个资源数目(Max)："; 
			for(int i=0;i<3;i++) 
			{   
			    p->Max[i]=rand()%10;
            	cout<<p->Max[i]<<" ";
			}
				cout<<endl;    		
			cout<<endl<<"\t请输入进程已分配的各个资源数目(Allocation)："; 
			for(int i=0;i<3;i++) 
			{
				p->Allocation[i]=rand()%5;
            	cout<<p->Allocation[i]<<" ";
			}
				cout<<endl;	
            for(int i=0;i<3;i++)     	
            	p->Need[i]=(p->Max[i])-(p->Allocation[i]);	
			cout<<endl;
			p->father=0;
			p->child=0;
			p->CPUtime=0;
			p->State=1; 		
			ready.enqueue(p); 
			createchild(p);	
			p->child=p->ID+0.1*num;
			num++; 
		}
	}
	output();
	jixu();
} 

void createchild(pcb *p)
{//创建子进程 
	pcb *t;
	t=new pcb;
	cout<<"\t正在创建子进程……"<<endl<<endl;
	num++; 
	for(int i=0;i<3;i++)     	
	{
		t->Allocation[i]=p->Allocation[i]; 	
        t->Max[i]=p->Max[i];
        t->Need[i]=p->Need[i];
	}                                                        
	t->ID=p->ID+0.1*num;
	t->Priority=p->Priority;
	t->Needtime=p->Needtime;
	t->father=p->ID;
	t->child=0;
	t->atime=p->atime;
	t->CPUtime=0;
	t->State=1; 		
	ready.enqueue(t);
	cout<<"\t创建完成!"<<endl<<endl;
}

void run()
{//执行进程--管理系统将就绪队列中的第一个进程调入运行队列
	pcb *p;
	p=new pcb;
	int flag=0;
	clean();
	if(!execute.isempty())
	{
		cout<<"\t已经有进程在执行!操作失败！"<<endl;	
	}	
	else
	{
		if(!ready.isempty())
		{
			ready.dequeue(p);
			for(int i=0;i<3;i++)
			{
				if((p->Need[i])<(Available[i]))
					flag++;//flag用来记录要执行的进程的各种资源数是否足够
			}
			if(flag==3)//当flag=3时意味着三种资源都足够可以执行该进程
			{
				p->CPUtime++;	//占用CPU的时间+1 
				p->State=2;
				for(int i=0;i<3;i++)
				{
					p->Allocation[i]=p->Max[i];         // Max是执行所需的，All是已经分配得到的，资源满足它所需的，就给它执行所需的所有资源 ，此时已经分配=所需 ，也不需要再分配了 
					p->Need[i]=0;                       //所以Need=0 
				}
				execute.enqueue(p);
				if(p->CPUtime>=p->Needtime)
				{	
					for(int i=0;i<3;i++)
						Available[i]=Available[i]+p->Allocation[i];
					execute.del(p->ID);
				}	
				output();
			}
			else
			{
				cout<<"\t未获得资源，进程阻塞!"<<endl;
				block.enqueue(p);
			}	
					
		}
		else
			cout<<"\t无就绪进程!"<<endl;
	}
	cout<<endl;
	output();
	jixu();
}

void lock()
{//阻塞函数，将执行队列中的进程阻塞并送入阻塞队列
	clean();
	if(!execute.isempty() )
	{
		pcb *p; 
		p=new pcb;
		execute.dequeue(p) ;
		p->State=0;
		block.enqueue(p);
		cout<<"\t进程阻塞完成"<<endl;
		cout<<endl;
		output();
	}
	else
		cout<<"\t无进程运行！" <<endl;
	jixu();
}

void revoke()
{//撤销函数，将进程从相应队列中删除，并修改子进程父进程信息
	float id,x,y;
	clean();
	cout<<"\t请输入要结束的进程名:";
	cin>>id;
	if(execute.find(id)==1||ready.find(id)==1||block.find(id)==1)	
	{
		x=execute.search2(id,0);//0选择查子进程，有子进程的话，x记录子进程号 
		if(x!=0) 
		{
			execute.search1(x,0);
		}
		x=ready.search2(id,0);
		if(x!=0) 
		{
			ready.search1(x,0);
		}
		x=block.search2(id,0);
		if(x!=0) 
		{
			block.search1(x,0);
		}			
		y=execute.search2(id,1);//1查找有没有父进程，有就修改父进程里记录子进程的数据结构 
		if(y!=0) 
		{
			execute.search1(y,1);
		}
		y=ready.search2(id,1);
		if(y!=0) 
		{
			ready.search1(y,1);
		}
		y=block.search2(id,1);
		if(y!=0) 
		{
			block.search1(y,1);
		}
		if(execute.find(id)==1)
			execute.del(id);
		else if(ready.find(id)==1)
			ready.del(id);
		else if(block.find(id)==1)	
			block.del(id);
		num--;
		cout<<"\t结束进程成功！"<<endl;
		output();
	}	
	else
		cout<<"\t没有此进程！"<<endl;
	jixu();
}

void change()//唤醒函数，将进程从相应队列中删除，并修改子进程父进程信息
{
	clean();
	if(!block.isempty())
	{
		pcb *p;
		p=new pcb;
		block.dequeue(p);
		p->State=1;
		ready.enqueue(p);
		cout<<"\t进程唤醒成功！"<<endl;
		cout<<endl;
		output();
	}
	else
		cout<<"\t无进程阻塞！"<<endl;	
	jixu();
}

void output()
{ 
	cout<<"\t\t\t\t执行队列"<<endl;
	execute.display();
	cout<<"\t\t\t\t就绪队列"<<endl;
	ready.display();
	cout<<"\t\t\t\t阻塞队列"<<endl;
	block.display();
}
void clean()
{//清屏 
	system("cls");
}
void jixu()
{
	char n;
	cout<<"\t是否继续"<<endl;
	cout<<"\t1.继续\t2.结束"<<endl;
	cout<<"\t请选择(1-2)：";
	cin>>n;
	switch(n)
	{
		case '1':clean();menu();
		case '2':exit(1);
		default:cout<<"\t\t\t\t!!!输入有误，请重新输入!!!"<<endl<<endl;jixu();
	}
}


void menu()
{
	char n;
	string file;
	cout<<"\t\t\t\t欢迎进入进程管理系统"<<endl;
	cout<<"\t\t*****************************************************"<<endl;
	cout<<"\t\t\t1.进程创建\t\t2.进程执行"<<endl;
	cout<<"\t\t\t3.进程阻塞\t\t4.进程终止"<<endl;
	cout<<"\t\t\t5.进程唤醒\t\t6.退   出"<<endl;
	cout<<"\t\t*****************************************************"<<endl;
	cout<<"\t\t请选择（1-6）："; 
	cin>>n; 
	switch(n)
	{
		case '1':create();break;
		case '2':run();break;
		case '3':lock();break;
		case '4':revoke();break;
		case '5':change();break;
		case '6':exit(1);
		default:clean();cout<<"\t\t\t\t!!!输入有误，请重新输入!!!"<<endl<<endl;menu();
	}
}

main()
{
	for(int i=0;i<3;i++)
		Available[i]=30;
	menu();
}
