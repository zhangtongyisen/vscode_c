#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct PCB {
	int PID;    	    //进程名称
	int priority;    	//进程优先级
	int arriveTime;  	//进程到达时间
	int allTime;     	//进程还需运行时间
	int Ts;             //系统提供服务的时间 
	int CPUTime;     	//已经使用CPU时间
	int startTime;  	//表示当进程阻塞StartTime个时间片后，进程将进入就绪状态
	int startBlock;   	//表示当进程在运行StartBlock个时间片后，进程将进入阻塞状态  
	int block;          //判断是否到达阻塞
	int start;          //判断是否阻塞完毕 
	char state;      	//进程状态：R N F B
	struct PCB* Next;	//指向下一个PCB的指针
} PCB;

int T=0;                  //平均周转时间
double W=0;                  //平均带权周转时间 
int runCounter=0;         //程序运行次数 
int num;				  //进程数目 
PCB* ready = NULL;		  //就绪队列第一个进程 
PCB* p;					  //公共指针 
PCB* blockfirst = NULL;   //阻塞队列第一个进程 
PCB* blocklast = NULL;	  //阻塞队列最后一个进程 
PCB* finish = NULL;		  //完成队列第一个进程 
PCB* noreach = NULL;      //未到达队列第一个进程 


//未到达进程排序(按到达时间升序)
void sortnoreach() {
	PCB* first,* second;
	int insert=0;
	p->state=' ';
	if((noreach==NULL)||((p->arriveTime)<(noreach->arriveTime))) {
		p->Next=noreach;
		noreach=p;
	} else {
		first=noreach;
		second=first->Next;
		while(second!=NULL) {
			if((p->arriveTime)<(second->arriveTime)) {
				p->Next=second;
				first->Next=p;
				second=NULL;
				insert=1;
			} else {
				first=first->Next;
				second=second->Next;
			}
		}
		if(insert==0) first->Next=p;
	}
}
//就绪进程排序 (按优先级降序) 
void sortPCB() {
	PCB* first,* second;
	int insert=0;
	p->state='R';
	if((ready==NULL)||((p->priority)>(ready->priority))) {
		p->Next=ready;
		ready=p;
	} else {
		first=ready;
		second=first->Next;
		while(second!=NULL) {
			if((p->priority)>(second->priority)) {
				p->Next=second;
				first->Next=p;
				second=NULL;
				insert=1;
			} else {
				first=first->Next;
				second=second->Next;
			}
		}
		if(insert==0) first->Next=p;
	}
}
//阻塞进程排序 (后插法)
void sortblock(){
	p->state='B';
	(p->start)++;
	if(blockfirst==NULL) {
		blockfirst=p;
		blocklast=p;
	} else {
		blocklast->Next=p;
		blocklast=p;
	}
}
//检查是否有新进程到达 
void checkready() {
	p=noreach;
	while(p!=NULL) {
		if(noreach->arriveTime==(runCounter+1)) {
			noreach=p->Next;
			p->Next=NULL;
			sortPCB();
			p=noreach;
		}else{
			break;
		} 
	}
}

void input() {
	int i;
	i=num;
	cout<<"输入"<<num<<"个进程的信息（PID、优先级、运行时间、到达时间、startTime、startBlock）"<<endl;
	while(i--) {
		p = new PCB();
		cin>>p->PID>>p->priority>>p->allTime>>p->arriveTime>>p->startTime>>p->startBlock;
		p->Ts=p->allTime;
		p->CPUTime=0;
		p->block=0;
		p->start=p->startTime;
		p->Next=NULL;
		sortnoreach();
	}
}

void output() {
	cout<<endl<<"PID\t状态\t优先级\t已用时间\t剩余时间\t到达时间"<<endl;
	cout<<"—————————————————————————"<<endl;
	cout<<p->PID<<"\t";
	cout<<p->state<<"\t";
	cout<<p->priority<<"\t";
	cout<<p->CPUTime<<"\t\t";
	cout<<p->allTime<<"\t\t";
	cout<<p->arriveTime<<"\t"<<endl;
}
//释放结束进程 
void Destroy() {
	p->state='F';
	if(finish!=NULL) {
		p->Next=finish;
		finish=p;
	} else {
		finish=p;
	}
	T=T+(runCounter-p->arriveTime+1);  
	double s=p->Ts;
	W=W+(runCounter-p->arriveTime+1)/s;
	cout<<endl<<"*************************进程"<<p->PID<<"已结束****************************"<<endl;
}
//运行进程 
void Run() {
	PCB* s;
	p=ready;
	ready=p->Next;
	s=ready;
	p->Next=NULL;
	(p->CPUTime)++;
	(p->allTime)--;
	(p->block)++;
	while(s!=NULL) {		//所有就绪队列中等待的进程优先级数加一 
		s->priority+=1;
		s=s->Next;
	}
	(p->priority)-=3;
	if(p->allTime==0) {
		Destroy();
	} else if(p->block==p->startBlock) {	//判断是否阻塞 
		sortblock();	 
	} else {
		sortPCB();
	}
}

void outready() {
	p=ready;
	cout<<endl<<"就绪队列："<<endl;
	while(p!=NULL) {
		output();
		p=p->Next;
	}
}

void outblock() {
	cout<<endl<<"阻塞队列："<<endl;
	p=blockfirst;
	while(p!=NULL) {
		output();
		p=p->Next;
	}
}

void outfinish() {
	cout<<endl<<"完成队列："<<endl;
	p=finish;
	while(p!=NULL) {
		output();
		p=p->Next;
	}
}

void outnoreach() {
	cout<<endl<<"未到达队列："<<endl;
	p=noreach;
	while(p!=NULL) {
		output();
		p=p->Next;
	}
}
//检查是否有阻塞进程将进入就绪队列 
 void checkstarttime() {
	PCB* s;
	p=blockfirst;
	while(p!=NULL){			
		(p->start)-=1;		
		p=p->Next;
	} 
	s=blockfirst;
	while(s!=NULL){
	if((s==blockfirst)&&(blockfirst->start==0)){
		p=blockfirst;
		blockfirst=p->Next;
		p->Next=NULL;
		s=blockfirst;
		p->block=0;
		p->start=p->startTime;
		sortPCB();
	}
	else{
		p=s->Next;
		if((p!=NULL)&&(p->start==0)){
			p->block=0;
			p->start=p->startTime;
			//if(p==blocklast){
			//	blocklast=s;
			//}
			s->Next=p->Next;
			p->Next=NULL;
			sortPCB();
		}else{
			s=s->Next;
		}
	}

	}
}

void algorithm() {
	input();
	checkready();
	outready();
	outnoreach();
	while((ready!=NULL)||(blockfirst!=NULL)||(noreach!=NULL)) {
		runCounter++;
		cout<<endl<<"运行次数："<<runCounter<<endl;
		if(ready!=NULL)
			Run();
		checkstarttime();
		checkready();
		outready();  //输出就绪队列 
		outblock();  //输出阻塞队列 
		outfinish(); //输出完成队列 
		outnoreach();//输出未到达队列 
	}
	cout<<endl<<"进程已经完成"<<endl;
}


int main() {
	cout<<"————————————————动态优先级调度算法————————————————"<<endl;
	cout<<"输入进程数目：";
	cin>>num;
	algorithm();
	cout<<"平均周转时间："<<T/num<<endl;
	cout<<"平均带权周转时间："<<W/num<<endl;
	 
}
