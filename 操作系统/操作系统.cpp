#include<bits/stdc++.h> 
#define NULL 0
#define false 0
#define true 1
#define I 8
#define R 150
using namespace std;
bool _state=0;
struct PCB
{
int ID;
int priority;
int CPUtime;
int ALLtime;
int State;
int artime;
PCB* next;
};
void init();/*����idle���̣������û�������Ŀ������insert()*/
void print(PCB *pcb);/*�������������Ϣ*/
void print_init(PCB *pcb);/*�������PCB�ĳ�ʼֵ*/
void insert();/*���ɽ���������Ϣ��������̾�������*/
void Run_priority(PCB *pcb);/*���н��̣�����������̡������½��̣�����������У�������������*/
void block(PCB *pcb);/*����destroy()�����̲�����������*/
void wakeup();/*���ѽ��̣������������*/
void proc_priority();/*����Ȩ�����㷨ģ��*/
//void Run_loop(PCB *pcb);
void proc_loop();/*��ת�������㷨ģ��*/
void proc_atime();
void update(PCB *pcb);/*���½�����Ϣ*/
void pushback_queue(PCB *queue,PCB *item);/*��item���뵽���е�β��*/
void insert_queue(PCB *queue,PCB *item);/*��item���뵽�����У�ʹ�ò���󣬶����а������ȼ��Ӹߵ�������*/
void sort_queue(PCB *&queue);/*��queue�еĽ��������򣬰������ȼ��Ӵ�С*/
PCB *ready_queue,*block_queue,*idleprocess;/*�������У��������м��й����ָ�����*/
int main(int argc, char* argv[])
{
int m=0;
int i,j,e; 
	while(1)
{
cout<<"\t\t\t\t��ӭ������̹���ϵͳ"<<endl;
cout<<"\t\t*****************************************************"<<endl;
cout<<"\t\t\t1.ģ��ʵ��FIFO����"<<endl;
cout<<"\t\t\t2.ģ��ʵ�ֶ�̬���ȼ�����"<<endl;
cout<<"\t\t\t3.ģ��ʵ��ʱ��Ƭ��ת����"<<endl;
cout<<"\t\t\t0.��   ��"<<endl;
cout<<"\t\t*****************************************************"<<endl;
cout<<"\t\t��ѡ��0-3����";
cin>>m;
while(m)
{
if(m==2)
{
cout<<("\n ����ģ�⶯̬���ȼ������㷨: \n ");
init();
proc_priority();
}
else if (m==3)
{
cout<<("\n ����ģ��ʱ��Ƭ��ת�����㷨: \n ");
init();
proc_loop();
}
else if (m==1)
{
cout<<("\n ����ģ��FIFO�����㷨: \n ");
init();
proc_atime();
}
else
{
cout<<"���������ѡ��(0,1,2,3)\n";
}
cout<<"\t\t*****************************************************"<<endl;
cout<<"\t\t\t1.ģ��ʵ��FIFO����"<<endl;
cout<<"\t\t\t2.ģ��ʵ�ֶ�̬���ȼ�����"<<endl;
cout<<"\t\t\t3.ģ��ʵ��ʱ��Ƭ��ת����"<<endl;
cout<<"\t\t\t0.��   ��"<<endl;
cout<<"\t\t*****************************************************"<<endl;
cout<<"����������:";
cin>>m;
}
return 0;
}}
///////�������PCB�ĳ�ʼֵ
void print_init(PCB *pcb)
{
PCB* temp=pcb->next ;
cout<<("\n���       ���ȼ�     ����ʱ��Ƭ     ����ʱ��Ƭ        ����ʱ��        ״̬");
while(temp!=NULL)
{
cout<<"\n"<<temp->ID<<"            "<<temp->priority<<"            "<<temp->CPUtime<<"            "<<temp->ALLtime<<"                 "<<temp->artime<<"             ";
if(temp->State==0)
cout<<("�Ѿ���");
else if(temp->State ==1)
cout<<("������");
else
cout<<("������");
temp=temp->next;
}
}
///////�������������Ϣ
void print(PCB *pcb)
{
PCB *temp;
temp=pcb;
if(pcb->ID==0)
cout<<("\n ����һ�����");
else
{
cout<<"\n"<<temp->ID<<"            "<<temp->priority<<"            "<<temp->CPUtime<<"            "<<temp->ALLtime<<"                 "<<temp->artime<<"             ";
if(temp->State==0)
cout<<("�Ѿ���");
else if(temp->State ==1)
cout<<("������");
else
cout<<("������");
}
}
///////��item���뵽�����У�ʹ�ò���󣬶����а������ȼ��Ӹߵ�������
void insert_queue(PCB *queue,PCB *item)
{
PCB *p,*q;
q=queue;p=q->next;
while(p!=0&&p->priority>=item->priority)
{
q=p;
p=p->next;
}
if(p==0)
{
item->next =0;
q->next=item;
}
else
{
item->next =p;
q->next =item;
}
}
///////��item���뵽�������е�β��
void pushback_queue(PCB *queue,PCB *item)
{
PCB *p,*q;
q=queue,p=q->next;
while(p!=0)
{
q=p;
p=p->next;
}
item->next =q->next ;
q->next =item;
}
///////��queue�еĽ��������򣬰������ȼ��Ӵ�С
void sort_queue(PCB *&queue)
{
PCB *temp=new PCB;
temp->next =0;
while(queue->next )
{
PCB *p;
p=queue->next;
queue->next =p->next ;
insert_queue(temp,p);
}
queue->next =temp->next ;
delete temp;
}
///////���ɽ���������Ϣ��������̾�������,��ʾ������Ϣ
void insert()
{
PCB *newp=0;
static long id =0;
newp=new PCB;
id++;
newp->ID =id;
newp->State=0;
newp->CPUtime=0;
newp->priority=rand()%3+1;
newp->ALLtime=rand()%3+1;
newp->artime=id;
newp->next =NULL;
pushback_queue(ready_queue,newp);
}
////////����n������������Ϣ��������̾������У���ʾ������Ϣ
void insert(int n)
{
for(int i=0;i<n;i++)
insert();
}
///////����idle���̣������û�������Ŀ������insert()
void init()
{
block_queue=new PCB;
block_queue->next=0;
ready_queue=new PCB;
ready_queue->next=0;
int i=0,pcb_number=-1;//�й���̷����������
idleprocess=NULL;
idleprocess=(PCB *)malloc(sizeof(PCB));
idleprocess->ID=0;
idleprocess->State=0;
idleprocess->CPUtime=0;
idleprocess->priority=0;
idleprocess->artime=0;
idleprocess->ALLtime=0;
idleprocess->next=NULL;
idleprocess->next=ready_queue->next;//�й���̷����������
ready_queue->next=idleprocess;
//Ҳ���Լٶ���ʼʱϵͳ��ֻ��һ��idle����
//�����ʼ���̵ĸ���
while(pcb_number<0)
{
cout<<("���趨��ʼ���̵���Ŀ:");
cin>>pcb_number;
}
cout<<("\n���------ ���ȼ�---- ����ʱ��Ƭ---- ����ʱ��Ƭ------- ״̬---- ����ʱ��\n");
for(;i<pcb_number;i++)
insert();
cout<<"*********�������г�ʼ���ɹ�******"<<endl;
::print_init(ready_queue);
cout<<endl;
}
///////����destroy()�����̲�����������
void block(PCB *pcb)
{
pcb->State=2;
pcb->CPUtime-=2;
if(pcb->CPUtime<=0)
{
pcb->CPUtime+=2;
}
cout<<"\n���̺�"<<pcb->ID<<"�Ѿ�������";
print(pcb);
cout<<(" ״̬ת��;������-->������\n");
pcb->next=block_queue->next;
block_queue->next =pcb;
}
///////���½�����Ϣ,���������н��̵����ȼ�������1
void update(PCB *pcb)
{
PCB *temp=pcb->next;
while(temp&&temp->next )
{
temp->priority++;
temp=temp->next;
}
}
///////���ѽ��̣������������
void wakeup()
{
if(block_queue->next==0)/*��ʱû�������Ľ��̣�����ν�Ļ���*/
return ;
PCB *q,*p;
while(true)
{
q=block_queue;
p=q->next;
while(p&&rand()%20!=1)
{
q=p;
p=p->next;
}
if(p!=0)
{
q->next =p->next ;
break;
}
}
p->State=0;
cout<<endl;
print(p);
cout<<"״̬�仯: ����-->����"<<endl;
insert_queue(ready_queue,p);
}
///////���н��̣�����������̡������½��̣�����������У�������������
void Run_priority(PCB *pcb)
{
if(pcb->ID==0)
{
insert_queue(ready_queue,pcb);
print(pcb);
cout<<"״̬�仯: ����-->����\n";
}
else
{
pcb->State=1;
pcb->CPUtime+=1;
pcb->priority=pcb->priority -1;/*ÿ����һ��ʱ��Ƭ������������1*/
if(pcb->priority <1)
pcb->priority=1;
print(pcb);
printf("״̬�仯: ����-->����\n");
if(rand()%3==1)/*PCB�����й���̣��������������˽���*/
{
if(pcb->CPUtime-2<=pcb->ALLtime)
block(pcb);
else/*��ִ����ϣ�Ӧ�����ٽ���*/
{
cout<<'\n';
cout<<"���̺�"<<pcb->ID<<"�Ѿ����  ״̬�仯��������-->����"<<endl;
delete pcb;
}
}
else/*���򿴸ý����Ƿ�ִ����ϣ����ִ���꣬���ͷţ������ٴη����������
	*/
{
if(pcb->CPUtime>pcb->ALLtime)/*�ͷ�*/
{
cout<<'\n';
cout<<"���̺�"<<pcb->ID<<" ��û��ִ����� ״̬�仯��������-->����"<<endl;
delete pcb;
}
else
{
::insert_queue(::ready_queue,pcb);
}
}
}
update(ready_queue);/*���¾������е����ȼ���*/
if(rand()%5==1)
{
insert(3);
::sort_queue(ready_queue);
}
if(rand()%7==1)
wakeup();
}
///////���н��̣�����������̡������½��̣�����������У�������������
void Run_loop(PCB *pcb)
{
if(pcb->ID==0)
{
insert_queue(ready_queue,pcb);
print(pcb);
cout<<"״̬�仯: ����-->����\n";
}
else
{
pcb->State=1;
pcb->CPUtime=pcb->ALLtime;
print(pcb);
printf("״̬�仯: ����-->����\n");
if(rand()%3==1)/*PCB�����й���̣����������������˽���*/
{
_state=1;
block(pcb);
}
else
{
cout<<'\n';
cout<<"���̺�"<<pcb->ID<<" ���ڽ����ж��Ƿ���� �����ɣ���״̬�仯Ϊ������-->����"<<endl;
delete pcb;
} 
}
if(rand()%5==1)
{
insert(3);
}
if(rand()%7==1)
wakeup();
}
///////����Ȩ�����㷨ģ��
void proc_priority()
{cout<<"������ʱ��Ƭ������";
sort_queue(ready_queue);
PCB *temp=0,*running=0;
int times=0;
int ss;
cin>>ss;
cout<<" *����ǰ* :";
::print_init(ready_queue);
for(;times<ss;times++)
{
running=ready_queue->next;
ready_queue->next =running->next ;
cout<<endl;
cout<<" *��ʼ����* "<<endl;
Run_priority(running);
}
cout<<"\n *���ε��Ƚ���* "<<endl;
}
///////��ת�����㷨ģ��
void proc_loop()
{
PCB *temp=0,*running=0;
int times;
cout<<"������ʱ��Ƭ������";
cin>>times;
cout<<" *����ǰ* :";
::print_init(ready_queue);
while(1)
{
running=ready_queue->next;
ready_queue->next =running->next ;
cout<<endl;
if(times>0)
{
times=times-running->ALLtime;//ÿ������һ�����̼�ȥALLtime;
if(times>=0)
{
Run_loop(running);
}
else if(_state) //�������ʱ��������������2��ʱ�䵥λ
{
times=times+2;
_state=0;
cout<<"������(��������ʱ��Ƭ)";
}
else
pushback_queue(block_queue,running);//ʱ�䲻�����������ý��̣��ŵ���������
}
else if(times<=0)
{
cout<<"\n!*********ʱ��Ƭ�þ�!!!!!***********";
break;
}
}
cout<<"\nʱ��Ƭ�þ�������ȫ����ɣ����´�����!!!!!��"<<endl;
}
///////FIFO�����㷨ģ��
void proc_atime()
{
cout<<"������ʱ��Ƭ������";
PCB *temp=0,*running=0;
int times=0;
int ss;
cin>>ss;
cout<<" *����ǰ* :";
::print_init(ready_queue);
for(;times<ss;times++)
{
running=ready_queue->next;
ready_queue->next =running->next ;
cout<<endl;
cout<<" *��ʼ����* "<<endl;
ru
}
cout<<"\n* ���ε��Ƚ���* "<<endl;
}
