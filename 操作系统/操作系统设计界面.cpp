#include<bits/stdc++.h>
#define m 3
using namespace std; 

typedef struct PCB 
{//������̿��ƿ�PCB
	float ID;       //���̱�ʶ�� 
	int Priority;     //����������
	int Needtime;      //���̻���Ҫ����ʱ�� 
	int CPUtime;      //����CPU��ʱ�� 
	int State;        //״̬��0--����   1--����  2--ִ�У� 
	float father;     //������
	float child;      //�ӽ���
	int Max[m];       //�������
	int Allocation[m];//�ѷ���
	int Need[m];      //���� 
	PCB *next;        //����ָ�� 
	int atime;
}pcb; 

class Queue
{
	public:
		Queue():rear(NULL),first(NULL){};         //�������캯������ʼ����ͷ�ڵ��β�ڵ㶼Ϊ��
	    ~Queue();                                 //������������ 
	    void enqueue(pcb *p);                     //������Ӻ��� 
	    void dequeue(pcb *p);                     //�������Ӻ��� 
	    bool isempty(){return first==NULL&&rear==NULL;}//�ж��пշ� 
	    void del(float id);                       
	    void display();                           //��ʾ���� 
	    int find(float id);                       
	    void search1(float id,int x);             
	    float search2(float id,int x);            
	private:
	    pcb *first,*rear;                         //ͷָ���βָ�� 
};
float a[8]={-1,-1,-1,-1,-1,-1,-1,-1};
Queue execute,ready,block;   //�����������ִ�ж��У�execute--ִ��  ready--����  block--������
PCB *ready_queue,*block_queue,*idleprocess; 
int num=0;     //������
int Available[m];   //������Դ
void output();   //�����������������н��̵���Ϣ
void clean();    //��������
void menu();     //�˵�����
void create();   //�����������������̲������������������
void createchild(pcb *p);  //�����ӽ��̺����������ӽ��̲��̳и�������Դ
void run();   //ִ�к������޽������пɽ���������ִ�ж���
void lock();  //������������ִ�ж����еĽ���������������������
void change();  //���Ѻ����������������еĽ��̻��������������
void revoke();  //���������������̴���Ӧ������ɾ�������޸��ӽ��̸�������Ϣ
void jixu();//ѡ���Ƿ�������л��˳����� 
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
    cout<<"������\t���ȼ�\t����ʱ��  ����ʱ��  ��Ҫʱ��  ״̬  ������  �ӽ���   A  B  C"<<endl;
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
{//���̳���ʱ������û���ӽ��̺͸����� 
	pcb *p;
	p=first;
	while(p!=NULL)
	{	
		if(id==p->ID)
		{
			if(x==1)   //1������û�и�����
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
{//��������--���ݽ��̵�˳�����η���������У����������ӽ��̸���
    srand((int)time(0)); //������� 
	clean();
	pcb *p;
	int  k,j;
	float id;
	int q=0;
	cout<<"\t�������������������˳�����룬����ID=0������"<<endl;
	for(int i=0;;i++)
	{
		cout<<"\t���������ID��";
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
			cout<<"\t\t\t\t!!!ID�ظ�������������!!!"<<endl<<endl;
			create();
		}
		if(id==0)
			break;
		else
		{
			p=new pcb;
			p->ID=id;
			p->atime=id;
			cout<<endl<<"\t�����������������";
			p->Priority=rand()%3;
			cout<<p->Priority<<endl;
			cout<<endl<<"\t��������������ʱ��(Needtime)��";
			p->Needtime=rand()%10;
			cout<<p->Needtime<<endl;
			cout<<endl<<"\t�������������ĸ�����Դ��Ŀ(Max)��"; 
			for(int i=0;i<3;i++) 
			{   
			    p->Max[i]=rand()%10;
            	cout<<p->Max[i]<<" ";
			}
				cout<<endl;    		
			cout<<endl<<"\t����������ѷ���ĸ�����Դ��Ŀ(Allocation)��"; 
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
{//�����ӽ��� 
	pcb *t;
	t=new pcb;
	cout<<"\t���ڴ����ӽ��̡���"<<endl<<endl;
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
	cout<<"\t�������!"<<endl<<endl;
}

void run()
{//ִ�н���--����ϵͳ�����������еĵ�һ�����̵������ж���
	pcb *p;
	p=new pcb;
	int flag=0;
	clean();
	if(!execute.isempty())
	{
		cout<<"\t�Ѿ��н�����ִ��!����ʧ�ܣ�"<<endl;	
	}	
	else
	{
		if(!ready.isempty())
		{
			ready.dequeue(p);
			for(int i=0;i<3;i++)
			{
				if((p->Need[i])<(Available[i]))
					flag++;//flag������¼Ҫִ�еĽ��̵ĸ�����Դ���Ƿ��㹻
			}
			if(flag==3)//��flag=3ʱ��ζ��������Դ���㹻����ִ�иý���
			{
				p->CPUtime++;	//ռ��CPU��ʱ��+1 
				p->State=2;
				for(int i=0;i<3;i++)
				{
					p->Allocation[i]=p->Max[i];         // Max��ִ������ģ�All���Ѿ�����õ��ģ���Դ����������ģ��͸���ִ�������������Դ ����ʱ�Ѿ�����=���� ��Ҳ����Ҫ�ٷ����� 
					p->Need[i]=0;                       //����Need=0 
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
				cout<<"\tδ�����Դ����������!"<<endl;
				block.enqueue(p);
			}	
					
		}
		else
			cout<<"\t�޾�������!"<<endl;
	}
	cout<<endl;
	output();
	jixu();
}

void lock()
{//������������ִ�ж����еĽ���������������������
	clean();
	if(!execute.isempty() )
	{
		pcb *p; 
		p=new pcb;
		execute.dequeue(p) ;
		p->State=0;
		block.enqueue(p);
		cout<<"\t�����������"<<endl;
		cout<<endl;
		output();
	}
	else
		cout<<"\t�޽������У�" <<endl;
	jixu();
}

void revoke()
{//���������������̴���Ӧ������ɾ�������޸��ӽ��̸�������Ϣ
	float id,x,y;
	clean();
	cout<<"\t������Ҫ�����Ľ�����:";
	cin>>id;
	if(execute.find(id)==1||ready.find(id)==1||block.find(id)==1)	
	{
		x=execute.search2(id,0);//0ѡ����ӽ��̣����ӽ��̵Ļ���x��¼�ӽ��̺� 
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
		y=execute.search2(id,1);//1������û�и����̣��о��޸ĸ��������¼�ӽ��̵����ݽṹ 
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
		cout<<"\t�������̳ɹ���"<<endl;
		output();
	}	
	else
		cout<<"\tû�д˽��̣�"<<endl;
	jixu();
}

void change()//���Ѻ����������̴���Ӧ������ɾ�������޸��ӽ��̸�������Ϣ
{
	clean();
	if(!block.isempty())
	{
		pcb *p;
		p=new pcb;
		block.dequeue(p);
		p->State=1;
		ready.enqueue(p);
		cout<<"\t���̻��ѳɹ���"<<endl;
		cout<<endl;
		output();
	}
	else
		cout<<"\t�޽���������"<<endl;	
	jixu();
}

void output()
{ 
	cout<<"\t\t\t\tִ�ж���"<<endl;
	execute.display();
	cout<<"\t\t\t\t��������"<<endl;
	ready.display();
	cout<<"\t\t\t\t��������"<<endl;
	block.display();
}
void clean()
{//���� 
	system("cls");
}
void jixu()
{
	char n;
	cout<<"\t�Ƿ����"<<endl;
	cout<<"\t1.����\t2.����"<<endl;
	cout<<"\t��ѡ��(1-2)��";
	cin>>n;
	switch(n)
	{
		case '1':clean();menu();
		case '2':exit(1);
		default:cout<<"\t\t\t\t!!!������������������!!!"<<endl<<endl;jixu();
	}
}


void menu()
{
	char n;
	string file;
	cout<<"\t\t\t\t��ӭ������̹���ϵͳ"<<endl;
	cout<<"\t\t*****************************************************"<<endl;
	cout<<"\t\t\t1.���̴���\t\t2.����ִ��"<<endl;
	cout<<"\t\t\t3.��������\t\t4.������ֹ"<<endl;
	cout<<"\t\t\t5.���̻���\t\t6.��   ��"<<endl;
	cout<<"\t\t*****************************************************"<<endl;
	cout<<"\t\t��ѡ��1-6����"; 
	cin>>n; 
	switch(n)
	{
		case '1':create();break;
		case '2':run();break;
		case '3':lock();break;
		case '4':revoke();break;
		case '5':change();break;
		case '6':exit(1);
		default:clean();cout<<"\t\t\t\t!!!������������������!!!"<<endl<<endl;menu();
	}
}

main()
{
	for(int i=0;i<3;i++)
		Available[i]=30;
	menu();
}
