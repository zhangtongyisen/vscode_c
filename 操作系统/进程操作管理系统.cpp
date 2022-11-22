#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>

# define increment 5
using namespace std;
//�����ǽ�����Ķ���
class process
{
	friend void SuspendProcess(process *headptr,int counter);	//��Ԫ����
	friend void WakeupProcess(process *headptr,int counter);	//��Ԫ����
protected:
	int pid;				  //������
	int priority;		      //�������ȼ�
	int cputime;			  //����ʹ��CPUʱ��
	int status;		          //����״̬
	int Rotationtimeslice;    //��תʱ��Ƭ
	int large;                //���̴�С
public:
	process(){}				  //Ĭ�Ϲ��캯��
	process(process &p)
	{
		p.pid=pid;
		p.priority=priority;
		p.cputime=cputime;
		p.large=large;
		p.status=status;
	}
	virtual ~process(){}
	void display()
	{
		cout<<"��������"<<pid<<endl<<"���ȼ���"<<priority<<endl<<"CPUʱ�䣺"<<cputime<<endl<<"��С��"<<large<<endl
		<<"״̬��"<<status<<endl;
	}
	void setall(int &counter)
	{
		cout<<"0-������1-����2-����" <<endl;
		cout<<"�������µĽ�������"; cin>>pid;
		cout<<"�������µĽ������ȼ���"; cin>>priority;
		cout<<"�������½��̴�С��"; cin>>large;
		cout<<"�������½���ʹ��CPUʱ����"; cin>>cputime;
		cout<<"�������½���״̬��"; cin>>status;         //0-������1-����2-����
		counter++;
	}
	int Getpid()
	{
		return pid;
	}
	int Getstatus()
	{
		return status;
	}
	int Getpriority()
	{
		return priority;
	}int Getcputime()
	{
		return cputime;
	}
	int Getlarge()
	{
		return large;
	}
};//process

void CreateNewprocess(process *headptr,int &counter,int capacity)
{
	if(counter < capacity)
	{
		(headptr+counter)->setall(counter);
	}
	else
	{
		cout<<"�ڴ������޷������½��̣��������µ��ڴ�ռ����ִ�л�������"<<endl;
	}
	
}

void ViewProcess(process *headptr,int capacity,int counter)
{
	for(int i=0;i < counter;i++)
	{
		(headptr+i)->display();
	}
	cout<<"��ǰ�ڴ�����"<<counter<<"������"<<endl;
	cout<<"ʣ������ڴ�ռ�Ϊ"<< capacity-counter<<"������"<<endl; 
}

void KillProcess(process *headptr,int &counter)
{
	int pid;
	cout<<"��������Ҫɱ���Ľ�����";cin>>pid;
	for(int i=0;i<counter;i++)
	{
		if((headptr+i)->Getpid()==pid)
		{
			for(int j=i;j<counter;j++)
				*(headptr+j)=*(headptr+j+1);
			break;
		}
		else if((i==counter-1)&&((headptr+i)->Getpid()!=pid))
		{
			cout<<"�������˴���Ľ�����"<<endl;
			Sleep(1000);
		}			
	}
	--counter;
}

void SwapOutProcess(process *headptr,int &counter)
{
	int pid;
	cout<<"��������Ҫ�����Ľ�����";cin>>pid;
	for(int i=0;i<counter;i++)
	{
		if((headptr+i)->Getpid()==pid)
		{
			--counter;
			(headptr+i)->setall(counter);
			break;
		}
		else if((i==counter-1)&&((headptr+i)->Getpid()!=pid))
		{
			cout<<"�������˴���Ľ�����"<<endl;
			Sleep(1000);
		}			
	}
}

void SuspendProcess(process *headptr,int counter)
{
	int pid;
	cout<<"��������Ҫ����Ľ�����";cin>>pid;
	for(int i=0;i<counter;i++)
	{
		if((headptr+i)->Getpid()==pid)
		{
			(headptr+i)->status=1;
			break;
		}
		else if((i==counter-1)&&((headptr+i)->Getpid()!=pid))
		{
			cout<<"�������˴���Ľ�����"<<endl;
			Sleep(1000);
		}			
	}
}

void WakeupProcess(process *headptr,int counter)
{
	int pid;
	cout<<"��������Ҫ���ѵĽ�����";cin>>pid;
	for(int i=0;i<counter;i++)
	{
		if((headptr+i)->Getpid()==pid)
		{
			(headptr+i)->status=0;
			cout<<"���ѳɹ�"<<endl;
			break;
		}
		else if((i==counter-1)&&((headptr+i)->Getpid()!=pid))
		{
			cout<<"�������˴���Ľ�����"<<endl;
			Sleep(1000);
		}			
	}	
}

void ApplyForNewMemory(process *&headptr,int &capacity,int counter)
{
	
	if(counter==capacity)
	{
		capacity+=increment;
		process *p=headptr;	
		process *newheadptr = new process[capacity];
		process *q=newheadptr;
		for(int i=0;i<counter;i++)
		{
			*q=*p;
			p++;
			q++;
		}
		p=headptr;
		headptr=newheadptr;
		delete[] p;
	}
	else
		cout<<"�����������µĴ洢�ռ�"<<endl;

}
int counter=0;				//��ǰ��������
int capacity=5;				//��ʼ����
int applystatus=0;
int main()
{

	time_t Time;
	time(&Time);
	int control;
	process *headptr = new process[capacity];
	do
	{
		cout <<  "��ǰϵͳʱ����:" << ctime(&Time) <<endl;
		cout<<"|========================���̲�������ϵͳ===========================|"<<endl
			<<"|                        *1.�����µĽ���	                           |"<<endl
			<<"|                        *2.�鿴���н���                            |"<<endl
			<<"|                        *3.�л��µĽ���                            |"<<endl
			<<"|                        *4.�������н���                            |"<<endl
			<<"|                        *5.�������н���                            |"<<endl
			<<"|                        *6.���ѹ������                            |"<<endl
			<<"|                        *7.�����µ��ڴ�                            |"<<endl
			<<"|                        *0.�˳�                                    |"<<endl
			<<endl;
		cout<<"���������ָ�";
		cin>>control;
		switch(control)
		{
		case 1: 
				system("cls");
				cout<<"�������µĽ��̺�����"<<endl;
				CreateNewprocess(headptr,counter,capacity);
				break;
		case 2: 
				system("cls");
				cout<<"���鿴���н��̺�����"<<endl;
				ViewProcess(headptr,capacity,counter);
				break;
		case 3: 
				system("cls");
				cout<<"�������µĽ��̺�����"<<endl;
				SwapOutProcess(headptr,counter);
				break;
		case 4: 
				system("cls");
				cout<<"��ɱ�����н��̺�����"<<endl;
				KillProcess(headptr,counter);
				break;
		case 5: 
				system("cls");
				cout<<"���������н��̺�����"<<endl;
				SuspendProcess(headptr,counter);
				break;
		case 6: 
				system("cls");
				cout<<"�����ѹ�����̺�����"<<endl;
				WakeupProcess(headptr,counter);
				break;
		case 7: 
				system("cls");
				cout<<"�������µ��ڴ溯����"<<endl;
				ApplyForNewMemory(headptr,capacity,counter);
				break;
		case 0: 
				cout<<"                         ��лʹ�ã� 3���������"<<endl;
				Sleep(3000);
				break;
		default:
				cout<<"                         ����������������룺";
				Sleep(1000);
				system("cls");
		}
	}
	while(control!=0);
	delete[] headptr;
	return 0;
}
