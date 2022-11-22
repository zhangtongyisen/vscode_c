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
void init();/*产生idle进程，输入用户进程数目，调用insert()*/
void print(PCB *pcb);/*输出进程属性信息*/
void print_init(PCB *pcb);/*输出所有PCB的初始值*/
void insert();/*生成进程属性信息，插入进程就绪队列*/
void Run_priority(PCB *pcb);/*运行进程，随机阻塞进程、产生新进程，插入就绪队列，唤醒阻塞进程*/
void block(PCB *pcb);/*调用destroy()将进程插入阻塞队列*/
void wakeup();/*唤醒进程，插入就绪队列*/
void proc_priority();/*优先权调度算法模拟*/
//void Run_loop(PCB *pcb);
void proc_loop();/*轮转法调度算法模拟*/
void proc_atime();
void update(PCB *pcb);/*更新进程信息*/
void pushback_queue(PCB *queue,PCB *item);/*将item插入到队列的尾部*/
void insert_queue(PCB *queue,PCB *item);/*将item插入到队列中，使得插入后，队列中按照优先级从高到低有序*/
void sort_queue(PCB *&queue);/*对queue中的结点进行排序，按照优先级从大到小*/
PCB *ready_queue,*block_queue,*idleprocess;/*就绪队列，阻塞队列及闲逛进程指针变量*/
int main(int argc, char* argv[])
{
int m=0;
int i,j,e; 
	while(1)
{
cout<<"\t\t\t\t欢迎进入进程管理系统"<<endl;
cout<<"\t\t*****************************************************"<<endl;
cout<<"\t\t\t1.模拟实现FIFO调度"<<endl;
cout<<"\t\t\t2.模拟实现动态优先级调度"<<endl;
cout<<"\t\t\t3.模拟实现时间片轮转调度"<<endl;
cout<<"\t\t\t0.退   出"<<endl;
cout<<"\t\t*****************************************************"<<endl;
cout<<"\t\t请选择（0-3）：";
cin>>m;
while(m)
{
if(m==2)
{
cout<<("\n 正在模拟动态优先级调度算法: \n ");
init();
proc_priority();
}
else if (m==3)
{
cout<<("\n 正在模拟时间片轮转调度算法: \n ");
init();
proc_loop();
}
else if (m==1)
{
cout<<("\n 正在模拟FIFO调度算法: \n ");
init();
proc_atime();
}
else
{
cout<<"请输入你的选择(0,1,2,3)\n";
}
cout<<"\t\t*****************************************************"<<endl;
cout<<"\t\t\t1.模拟实现FIFO调度"<<endl;
cout<<"\t\t\t2.模拟实现动态优先级调度"<<endl;
cout<<"\t\t\t3.模拟实现时间片轮转调度"<<endl;
cout<<"\t\t\t0.退   出"<<endl;
cout<<"\t\t*****************************************************"<<endl;
cout<<"请输入数字:";
cin>>m;
}
return 0;
}}
///////输出所有PCB的初始值
void print_init(PCB *pcb)
{
PCB* temp=pcb->next ;
cout<<("\n编号       优先级     已用时间片     总需时间片        到达时间        状态");
while(temp!=NULL)
{
cout<<"\n"<<temp->ID<<"            "<<temp->priority<<"            "<<temp->CPUtime<<"            "<<temp->ALLtime<<"                 "<<temp->artime<<"             ";
if(temp->State==0)
cout<<("已就绪");
else if(temp->State ==1)
cout<<("运行中");
else
cout<<("被阻塞");
temp=temp->next;
}
}
///////输出进程属性信息
void print(PCB *pcb)
{
PCB *temp;
temp=pcb;
if(pcb->ID==0)
cout<<("\n 排序一次完成");
else
{
cout<<"\n"<<temp->ID<<"            "<<temp->priority<<"            "<<temp->CPUtime<<"            "<<temp->ALLtime<<"                 "<<temp->artime<<"             ";
if(temp->State==0)
cout<<("已就绪");
else if(temp->State ==1)
cout<<("运行中");
else
cout<<("被阻塞");
}
}
///////将item插入到队列中，使得插入后，队列中按照优先级从高到低有序
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
///////将item插入到阻塞队列的尾部
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
///////对queue中的结点进行排序，按照优先级从大到小
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
///////生成进程属性信息，插入进程就绪队列,显示进程信息
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
////////生成n个进程属性信息，插入进程就绪队列，显示进程信息
void insert(int n)
{
for(int i=0;i<n;i++)
insert();
}
///////产生idle进程，输入用户进程数目，调用insert()
void init()
{
block_queue=new PCB;
block_queue->next=0;
ready_queue=new PCB;
ready_queue->next=0;
int i=0,pcb_number=-1;//闲逛进程放入就绪队列
idleprocess=NULL;
idleprocess=(PCB *)malloc(sizeof(PCB));
idleprocess->ID=0;
idleprocess->State=0;
idleprocess->CPUtime=0;
idleprocess->priority=0;
idleprocess->artime=0;
idleprocess->ALLtime=0;
idleprocess->next=NULL;
idleprocess->next=ready_queue->next;//闲逛进程放入就绪队列
ready_queue->next=idleprocess;
//也可以假定初始时系统中只有一个idle进程
//输入初始进程的个数
while(pcb_number<0)
{
cout<<("请设定初始进程的数目:");
cin>>pcb_number;
}
cout<<("\n编号------ 优先级---- 已用时间片---- 总需时间片------- 状态---- 到达时间\n");
for(;i<pcb_number;i++)
insert();
cout<<"*********就绪队列初始化成功******"<<endl;
::print_init(ready_queue);
cout<<endl;
}
///////调用destroy()将进程插入阻塞队列
void block(PCB *pcb)
{
pcb->State=2;
pcb->CPUtime-=2;
if(pcb->CPUtime<=0)
{
pcb->CPUtime+=2;
}
cout<<"\n进程号"<<pcb->ID<<"已经被阻塞";
print(pcb);
cout<<(" 状态转换;运行中-->被阻塞\n");
pcb->next=block_queue->next;
block_queue->next =pcb;
}
///////更新进程信息,就绪队列中进程的优先级均增加1
void update(PCB *pcb)
{
PCB *temp=pcb->next;
while(temp&&temp->next )
{
temp->priority++;
temp=temp->next;
}
}
///////唤醒进程，插入就绪队列
void wakeup()
{
if(block_queue->next==0)/*此时没有阻塞的进程，无所谓的唤醒*/
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
cout<<"状态变化: 阻塞-->就绪"<<endl;
insert_queue(ready_queue,p);
}
///////运行进程，随机阻塞进程、产生新进程，插入就绪队列，唤醒阻塞进程
void Run_priority(PCB *pcb)
{
if(pcb->ID==0)
{
insert_queue(ready_queue,pcb);
print(pcb);
cout<<"状态变化: 就绪-->运行\n";
}
else
{
pcb->State=1;
pcb->CPUtime+=1;
pcb->priority=pcb->priority -1;/*每运行一个时间片，其优先数减1*/
if(pcb->priority <1)
pcb->priority=1;
print(pcb);
printf("状态变化: 就绪-->运行\n");
if(rand()%3==1)/*PCB不是闲逛进程，满足条件阻塞此进程*/
{
if(pcb->CPUtime-2<=pcb->ALLtime)
block(pcb);
else/*已执行完毕，应该销毁进程*/
{
cout<<'\n';
cout<<"进程号"<<pcb->ID<<"已经完成  状态变化：进行中-->撤销"<<endl;
delete pcb;
}
}
else/*否则看该进程是否执行完毕，如果执行完，则释放，否则再次放入就绪队列
	*/
{
if(pcb->CPUtime>pcb->ALLtime)/*释放*/
{
cout<<'\n';
cout<<"进程号"<<pcb->ID<<" 还没有执行完成 状态变化：进行中-->就绪"<<endl;
delete pcb;
}
else
{
::insert_queue(::ready_queue,pcb);
}
}
}
update(ready_queue);/*更新就绪队列的优先级数*/
if(rand()%5==1)
{
insert(3);
::sort_queue(ready_queue);
}
if(rand()%7==1)
wakeup();
}
///////运行进程，随机阻塞进程、产生新进程，插入就绪队列，唤醒阻塞进程
void Run_loop(PCB *pcb)
{
if(pcb->ID==0)
{
insert_queue(ready_queue,pcb);
print(pcb);
cout<<"状态变化: 就绪-->进行\n";
}
else
{
pcb->State=1;
pcb->CPUtime=pcb->ALLtime;
print(pcb);
printf("状态变化: 就绪-->进行\n");
if(rand()%3==1)/*PCB不是闲逛进程，满足条件侧阻塞此进程*/
{
_state=1;
block(pcb);
}
else
{
cout<<'\n';
cout<<"进程号"<<pcb->ID<<" 正在进行判断是否完成 如果完成，则状态变化为：运行-->撤销"<<endl;
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
///////优先权调度算法模拟
void proc_priority()
{cout<<"请输入时间片总数：";
sort_queue(ready_queue);
PCB *temp=0,*running=0;
int times=0;
int ss;
cin>>ss;
cout<<" *调度前* :";
::print_init(ready_queue);
for(;times<ss;times++)
{
running=ready_queue->next;
ready_queue->next =running->next ;
cout<<endl;
cout<<" *开始调度* "<<endl;
Run_priority(running);
}
cout<<"\n *本次调度结束* "<<endl;
}
///////轮转调度算法模拟
void proc_loop()
{
PCB *temp=0,*running=0;
int times;
cout<<"请输入时间片总数：";
cin>>times;
cout<<" *调度前* :";
::print_init(ready_queue);
while(1)
{
running=ready_queue->next;
ready_queue->next =running->next ;
cout<<endl;
if(times>0)
{
times=times-running->ALLtime;//每次运行一个进程减去ALLtime;
if(times>=0)
{
Run_loop(running);
}
else if(_state) //如果运行时被阻塞，则运行2个时间单位
{
times=times+2;
_state=0;
cout<<"阻塞中(消耗两个时间片)";
}
else
pushback_queue(block_queue,running);//时间不够，则阻塞该进程，放到阻塞队列
}
else if(times<=0)
{
cout<<"\n!*********时间片用尽!!!!!***********";
break;
}
}
cout<<"\n时间片用尽或任务全部完成，请下次再来!!!!!。"<<endl;
}
///////FIFO调度算法模拟
void proc_atime()
{
cout<<"请输入时间片总数：";
PCB *temp=0,*running=0;
int times=0;
int ss;
cin>>ss;
cout<<" *调度前* :";
::print_init(ready_queue);
for(;times<ss;times++)
{
running=ready_queue->next;
ready_queue->next =running->next ;
cout<<endl;
cout<<" *开始调度* "<<endl;
ru
}
cout<<"\n* 本次调度结束* "<<endl;
}
