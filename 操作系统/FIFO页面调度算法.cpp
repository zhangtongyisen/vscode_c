#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<iomanip>
using namespace std;
/*
2018.06.15
�������� 
------------------------------------------- 
3
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1 #
------------------------------------------- 
3
1 2 3 4 1 2 5 1 2 3 4 5 #
------------------------------------------- 
5
0 1 2 3 4 5 0 2 1 8 5 2 7 6 0 1 2 #
------------------------------------------- 
*/
class BLOCK{
public:
	int blockNum;	//���������
	int pageNum;	//������е�ҳ������ 
	int *pageID;	//ҳ��ţ���СΪblockNum��
	int *stayTime;	//ҳ����������е�ͣ��ʱ�䣨�������ID��Ӧ��
	BLOCK(int num)
	{
		int i;
		pageNum=0;
		blockNum=num;
		pageID=new int[num];
		stayTime=new int[num];
		for(i=0;i<num;i++)
		{
			pageID[i]=-1;	//��ʼ��ÿ���������û�з��ã�ҳ��ű�ʾΪ-1
			stayTime[i]=0;	//��ʼ��ͣ��ʱ��Ϊ0
		}
	}
	void Init()
	{
		int i;
		int num=blockNum;
		pageNum=0;
		pageID=new int[num];
		stayTime=new int[num];
		for(i=0;i<num;i++)
		{
			pageID[i]=-1;	//��ʼ��ÿ���������û�з��ã�ҳ��ű�ʾΪ-1
			stayTime[i]=0;	//��ʼ��ͣ��ʱ��Ϊ0
		}
	}
	int GetLongestStay()//��ȡ���������ͣ��ʱ�����ҳ������������ 
	{
		int i;
		int max_pos=0;
		for(i=0;i<pageNum;i++)
		if(stayTime[max_pos]<stayTime[i])
		max_pos=i;
		return max_pos;
	}
};	//��������ݽṹ����
//-----------------------ȫ�ֱ���-------------------------
int BLOCKNUM;		//�������
int *PVS;			//PageVisitSequenceҳ���������
int PVS_NUM;		//ҳ��������г���
int **replaceTable;	//ҳ���û����ά�ȣ�BLOCKNUM*PVS_NUM��
int *replaceArray;	//ҳ���û���־���飨��СΪ����ҳ��Ĵ������洢ÿ�η����Ƿ����ҳ���û��� 
int *lackArray;		//ȱҳ�жϱ�־���飨��СΪ����ҳ��Ĵ������洢ÿ�η����Ƿ����ȱҳ�жϣ� 
//-----------------------��������-------------------------
void showMenu();							//�˵���ʾ
void InputAndInit();						//��������ͱ�����ʼ��
void ReplaceFIFO(BLOCK block);				//FIFOҳ���û��㷨
int FindPage(int pageID,BLOCK block);		//ҳ����ң�����ҳ������������в���ҳ���Ƿ���ڣ� 
void ShowReplaceTable();					//�û�������
void InfoDisplay();							//��ʼ����Ϣ��ʾ
//-----------------------��������-------------------------
int main()
{
	int select;
	int i;
	cout<<"�밴��ʾ�����㷨ģ����Ҫ������..."<<endl;
	InputAndInit();
	BLOCK block(BLOCKNUM);	//��������飨ע����������ڱ��������ݳ�ʼ���󣬷���BLOCKNUMδ֪�� 
	cout<<"��Ϣ��ʼ����ɣ�"<<endl<<endl;
	showMenu();
	cout<<"������Ҫ���еĲ���..."<<endl;
	cin>>select;
	while(1)
	{
		switch(select)
		{
			case 1:
				InfoDisplay();
				cout<<endl;
			break;
			case 2:
				ReplaceFIFO(block);
				cout<<"|=================> FIFOҳ������㷨����ִ��......"<<endl;
				ShowReplaceTable();
				cout<<endl;
			break;
			case 0:
				cout<<"��ӭ�´�ʹ��..."<<endl;
			return 0;
			default:
				cout<<"������������������..."<<endl;
				cout<<endl;
			break; 
		}
		showMenu();
		cout<<"������Ҫ���еĲ������˳�������0��..."<<endl;
		cin>>select;
	}
	delete[] PVS;
	for(i=0;i<BLOCKNUM;i++)
	delete[] replaceTable[i];
	delete[] replaceTable;
	return 0;
}
//----------------------FIFOҳ���û��㷨--------------------------
void ReplaceFIFO(BLOCK block)			//FIFOҳ���û��㷨
{
	int i,j;
	for(i=0;i<BLOCKNUM;i++)
		for(j=0;j<PVS_NUM;j++)
			replaceTable[i][j]=0;
	block.Init();
	int replacePosition;				//���û�λ�� 
	for(i=0;i<PVS_NUM;i++)				//���ζ�ҳ��������е�ÿһ��ҳ��PVS[i]���в���
	{
		for(j=0;j<block.pageNum;j++)
		block.stayTime[j]++;			//ÿѭ��һ�Σ�����飨0~pageNum��ͣ��ʱ������ 
		if(block.pageNum<block.blockNum)
		{
			if(!FindPage(PVS[i],block))	//��ҳ��PVS[i]������
			{
				lackArray[i]=1;			//���ڷ���ҳ�治�������ҳ���ж� 
				block.pageID[block.pageNum]=PVS[i];
				block.pageNum++;
			}
		}
		else							//FIFO�㷨���û�ͣ��ʱ�����ҳ�����������λ�ã� 
		{
//			TODO:��ҳ���Ѵ��ڵ�����������������Ӧ����ҳ�治���ڵ������Ӧ����if(ҳ����������в�����)���жϣ�
			if(!FindPage(PVS[i],block))	//��ҳ��PVS[i]������
			{
				replaceArray[i]=1;		//���ڷ���ҳ�治�������޿�����������ҳ���û�
				lackArray[i]=1;			//���ڷ���ҳ�治�������ҳ���ж� 
				replacePosition=block.GetLongestStay();
				block.pageID[replacePosition]=PVS[i];	//ѡ��ͣ��ʱ�����ҳ���û�
				block.stayTime[replacePosition]=0;		//�û��󣬸�ҳ����������λ��ͣ��ʱ������ 
			}
		}
		for(j=0;j<BLOCKNUM;j++)
		replaceTable[j][i]=block.pageID[j];	//������һ��ҳ���Ľ�����������У�replaceTable��
	}
}
int FindPage(int pageID,BLOCK block)		//ҳ����ң�����ҳ�������Դ��ҳ�������飨����ΪpageNum���в���ҳ���Ƿ���ڣ� 
{
	int i=0;
	for(i=0;i<block.pageNum;i++)
	if(block.pageID[i]==pageID)
	break;
	return !(i==block.pageNum);				//��ҳ����ڣ��򷵻�1�����򷵻�0 
}
void showMenu()						//�˵���ʾ 
{
	cout<<"\t|---------------------------------------------------------------|"<<endl;
	cout<<"\t|----------------------------MENU-------------------------------|"<<endl;
	cout<<"\t|\t1. ��ʼ����Ϣ��ʾ                                       |"<<endl;
	cout<<"\t|\t2. FIFOҳ���û��㷨                                     |"<<endl;
	cout<<"\t|\t0. �˳�����                                             |"<<endl;
	cout<<"\t|---------------------------------------------------------------|"<<endl;
}
void InputAndInit()					//��������ͱ�����ʼ�� 
{
	int i=0;
	int j=0;
	char PVS_char[100];
	cout<<"�������������..."<<endl;
	cin>>BLOCKNUM;
	cout<<"����������ҳ��������У�0~9����#������..."<<endl;
	cin>>PVS_char[i];
	getchar();
	while(PVS_char[i]!='#')
	{
		i++;
		cin>>PVS_char[i];
		getchar();
	}
	PVS_char[i]='\0';					//�����ַ�����ֹ��
	PVS_NUM=i;
	PVS=new int[PVS_NUM];
	for(i=0;i<PVS_NUM;i++)
	PVS[i]=PVS_char[i]-'0';				//�ַ�ת���֣�ҳ��ţ�
	
	replaceArray=new int[PVS_NUM];
	lackArray=new int[PVS_NUM];
	replaceTable=new int*[BLOCKNUM];	//ҳ���û����ʼ��
	for(i=0;i<BLOCKNUM;i++)
		replaceTable[i]=new int[PVS_NUM];
}
void ShowReplaceTable()						//�û������� 
{
	int i,j;
	cout<<"ҳ���û���������ͼ��ʾ"<<endl<<endl;
	cout<<setw(PVS_NUM*3+14)<<setfill('-')<<"-"<<endl;
	cout.fill(' ');
	cout<<"ҳ��������� ";
	for(i=0;i<PVS_NUM;i++)
	cout<<" "<<setw(2)<<PVS[i];
	cout<<endl;
	cout<<setw(PVS_NUM*3+14)<<setfill('-')<<"-"<<endl;
	cout.fill(' ');
	cout<<"ҳ���û����� ";
	for(i=0;i<BLOCKNUM;i++)
	{
		if(i>0)
		cout<<"\t     ";
		for(j=0;j<PVS_NUM;j++)
		{
			if(replaceTable[i][j]!=-1)
			cout<<"|"<<setw(2)<<replaceTable[i][j];
			else cout<<"|"<<setw(2)<<" ";	//-1ʱ������������ҳ�棬�����
		}
		cout<<"|"<<endl;
	}
	cout<<setw(PVS_NUM*3+14)<<setfill('-')<<"-"<<endl;
	cout<<"ҳ���жϱ�־ ";
	cout.fill(' ');
	for(i=0;i<PVS_NUM;i++)
		cout<<" "<<setw(2)<<lackArray[i];
	cout<<endl;
	cout<<setw(PVS_NUM*3+14)<<setfill('-')<<"-"<<endl<<endl;
}
void InfoDisplay()							//��ʼ����Ϣ��ʾ 
{
	int i;
	cout<<"��ҳ���û�ģ���㷨��: "<<endl;
	cout<<"�������Ϊ�� "<<BLOCKNUM<<endl;
	cout<<"ҳ���������Ϊ��";
	for(i=0;i<PVS_NUM;i++)
	cout<<PVS[i]<<" ";
	cout<<endl;
}
