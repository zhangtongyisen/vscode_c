#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct PCB {
	int PID;    	    //��������
	int priority;    	//�������ȼ�
	int arriveTime;  	//���̵���ʱ��
	int allTime;     	//���̻�������ʱ��
	int Ts;             //ϵͳ�ṩ�����ʱ�� 
	int CPUTime;     	//�Ѿ�ʹ��CPUʱ��
	int startTime;  	//��ʾ����������StartTime��ʱ��Ƭ�󣬽��̽��������״̬
	int startBlock;   	//��ʾ������������StartBlock��ʱ��Ƭ�󣬽��̽���������״̬  
	int block;          //�ж��Ƿ񵽴�����
	int start;          //�ж��Ƿ�������� 
	char state;      	//����״̬��R N F B
	struct PCB* Next;	//ָ����һ��PCB��ָ��
} PCB;

int T=0;                  //ƽ����תʱ��
double W=0;                  //ƽ����Ȩ��תʱ�� 
int runCounter=0;         //�������д��� 
int num;				  //������Ŀ 
PCB* ready = NULL;		  //�������е�һ������ 
PCB* p;					  //����ָ�� 
PCB* blockfirst = NULL;   //�������е�һ������ 
PCB* blocklast = NULL;	  //�����������һ������ 
PCB* finish = NULL;		  //��ɶ��е�һ������ 
PCB* noreach = NULL;      //δ������е�һ������ 


//δ�����������(������ʱ������)
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
//������������ (�����ȼ�����) 
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
//������������ (��巨)
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
//����Ƿ����½��̵��� 
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
	cout<<"����"<<num<<"�����̵���Ϣ��PID�����ȼ�������ʱ�䡢����ʱ�䡢startTime��startBlock��"<<endl;
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
	cout<<endl<<"PID\t״̬\t���ȼ�\t����ʱ��\tʣ��ʱ��\t����ʱ��"<<endl;
	cout<<"��������������������������������������������������"<<endl;
	cout<<p->PID<<"\t";
	cout<<p->state<<"\t";
	cout<<p->priority<<"\t";
	cout<<p->CPUTime<<"\t\t";
	cout<<p->allTime<<"\t\t";
	cout<<p->arriveTime<<"\t"<<endl;
}
//�ͷŽ������� 
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
	cout<<endl<<"*************************����"<<p->PID<<"�ѽ���****************************"<<endl;
}
//���н��� 
void Run() {
	PCB* s;
	p=ready;
	ready=p->Next;
	s=ready;
	p->Next=NULL;
	(p->CPUTime)++;
	(p->allTime)--;
	(p->block)++;
	while(s!=NULL) {		//���о��������еȴ��Ľ������ȼ�����һ 
		s->priority+=1;
		s=s->Next;
	}
	(p->priority)-=3;
	if(p->allTime==0) {
		Destroy();
	} else if(p->block==p->startBlock) {	//�ж��Ƿ����� 
		sortblock();	 
	} else {
		sortPCB();
	}
}

void outready() {
	p=ready;
	cout<<endl<<"�������У�"<<endl;
	while(p!=NULL) {
		output();
		p=p->Next;
	}
}

void outblock() {
	cout<<endl<<"�������У�"<<endl;
	p=blockfirst;
	while(p!=NULL) {
		output();
		p=p->Next;
	}
}

void outfinish() {
	cout<<endl<<"��ɶ��У�"<<endl;
	p=finish;
	while(p!=NULL) {
		output();
		p=p->Next;
	}
}

void outnoreach() {
	cout<<endl<<"δ������У�"<<endl;
	p=noreach;
	while(p!=NULL) {
		output();
		p=p->Next;
	}
}
//����Ƿ����������̽������������ 
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
		cout<<endl<<"���д�����"<<runCounter<<endl;
		if(ready!=NULL)
			Run();
		checkstarttime();
		checkready();
		outready();  //����������� 
		outblock();  //����������� 
		outfinish(); //�����ɶ��� 
		outnoreach();//���δ������� 
	}
	cout<<endl<<"�����Ѿ����"<<endl;
}


int main() {
	cout<<"����������������������������������̬���ȼ������㷨��������������������������������"<<endl;
	cout<<"���������Ŀ��";
	cin>>num;
	algorithm();
	cout<<"ƽ����תʱ�䣺"<<T/num<<endl;
	cout<<"ƽ����Ȩ��תʱ�䣺"<<W/num<<endl;
	 
}
