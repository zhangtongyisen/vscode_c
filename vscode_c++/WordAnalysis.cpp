// WordAnalysis.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include "Chars.h"

#define MAX_DATA_LEN	256	// ���ݻ���������

// word type
#define WT_OPERATOR		0	// ������
#define WT_UINT			1	// �Ǹ�����
#define WT_VARIABLE		2	// ����

struct WORDNODE
{
	unsigned short byType;		// ���
	char Value[MAX_DATA_LEN];	// ֵ
	WORDNODE *pNext;			// ��һ���
};


// Ԥ����������ո�ȥ��
void Prefix(char c[])
{
	int i,j;
	for (i = 0, j = 0; j < MAX_DATA_LEN && c[j] != '\0'; j++)
	{
		if (c[j] != ' ')
			c[i++] = c[j];
	}
	c[i] = '\0';
}

// �������
void Clear(WORDNODE *pHeader)
{
	WORDNODE *pNode;

	while (pHeader != NULL)
	{
		pNode = pHeader->pNext;
		free(pHeader);
		pHeader = pNode;
	}
}

// ���ӽ��
WORDNODE* AddNode(char c[], int nBegin, int nEnd, unsigned short byType, WORDNODE *pTail)
{
	WORDNODE *pNode = (WORDNODE *)malloc(sizeof(WORDNODE));
	pNode->byType = byType;
	//printf("%d",byType);
	pNode->pNext = NULL;

	int nChars = nEnd - nBegin + 1;
	memcpy(pNode->Value, &c[nBegin], nChars);
	pNode->Value[nChars] = '\0';

	pTail->pNext = pNode;
	return pNode;
}

// ������һ״̬��ȡ�������
unsigned short GetWordType(int nStatus)
{
	switch (nStatus)
	{
	case 1:
		return WT_OPERATOR;
	case 2:
		return WT_UINT;
	case 3:
		return WT_VARIABLE;
	}
	return 0xFF;
}

/*************************************
* �������ܣ���ȡ��һ״̬
* ��ڲ�����cChar ��ǰ�ַ�
*			nStatus ��ǰ״̬
* �� �� ֵ����һ״̬
***************************************/
int GetNextStatus(char cChar, int nStatus)
{
	if(nStatus==0){
		if(IsOperator(cChar)){
			return 1;
		}
		if(IsNum(cChar)){
			return 2;
		}
		if(IsEnglishCharOr_(cChar)){
			return 3;
		}
		return 5;
	}
	if(nStatus==1){
		return 4;
	}
	if(nStatus==2){
		if(!IsNum(cChar))
		return 4;
	}
	if(nStatus==3){
		if(!IsNum(cChar)&&!IsEnglishCharOr_(cChar))
		return 4;
	}
	return nStatus;
}

/***************************************
* �������ܣ�ʶ��һ������
* ��ڲ�����c ɨ�軺����
*			nCur ɨ����ָ��
*			pTail ��������βָ��
* �� �� ֵ��ʶ����ĵ���ָ�룬NULL��ʾ����
*****************************************/
WORDNODE* IdentifyOneWord(char c[], int &nCur, WORDNODE *pTail)
{
	int Status=GetNextStatus(c[nCur],0);
	
	int nBegin=nCur;
	if(Status==5){
		//printf("%d+",nCur);
		return NULL;
	}
	nCur++;
	
	for (; c[nCur] != '\0'; nCur++)
	{
		if(GetNextStatus(c[nCur],Status)==5){
			//nCur--;
			//printf("%d*",nCur);
			return NULL;
		}	
		if(GetNextStatus(c[nCur],Status)==4){
			nCur--;
			//printf("%d-",nCur);
			return AddNode(c,nBegin,nCur,GetWordType(Status),pTail);
		}		
	}
	
	return AddNode(c,nBegin,nCur,GetWordType(Status),pTail);
}

// �ʷ�����
WORDNODE* WordAnalysis(char c[])
{
	// ��һ�������Ϊͷ��㣬��ʹ��
	WORDNODE *pHeader = (WORDNODE *)malloc(sizeof(WORDNODE));
	pHeader->pNext = NULL;
	WORDNODE *pTail = pHeader, *pNode = NULL;

	// �ʷ�����
	for (int nCur = 0; c[nCur] != '\0'; nCur++)
	{
		
		// ʶ��һ������
		pTail = IdentifyOneWord(c, nCur, pTail);
		
		if (pTail == NULL)	// ����
		{
			
			Clear(pHeader);
			return NULL;
		}

	}

	return pHeader;
}

bool Save(WORDNODE *pHeader)
{
	// �ļ���
	char FileName[256];
	printf("������������ļ�������a.txt����\n");
	scanf("%s", FileName);

	// ���ļ�
	FILE *f = fopen(FileName, "w");
	if (f == NULL)
	{
		Clear(pHeader);
		return false;
	}

	// �ճ���һ�����
	WORDNODE *pNode = pHeader->pNext;

	// ��������
	while (pNode != NULL)
	{
		fprintf(f, "%c,%s\n", pNode->byType + '0', pNode->Value);
		pNode = pNode->pNext;
	}

	// �ر��ļ�
	fclose(f);

	return true;
}

// ������
int main(int argc, char* argv[])
{
	// ����
	char c[MAX_DATA_LEN];
	printf("��������ʽ��\n");
	gets(c);

	// Ԥ����
	Prefix(c);

	// �ʷ�����
	WORDNODE *pHeader = WordAnalysis(c);
	if (pHeader == NULL)
	{
		printf("\n�ʷ���������!\n");
		return 0;
	}

	// ����
	if (!Save(pHeader))
	{
		printf("\n�����ļ�ʧ��\n");
		return 0;
	}

	// �������
	Clear(pHeader);

	// ���
	printf("\n�ʷ������ɹ������ѱ��浽�ļ�\n", c);
	printf("��������˳�\n", c);
	getchar();
	getchar();
	return 0;
}
