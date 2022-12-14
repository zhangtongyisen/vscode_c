// WordAnalysis.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include "Chars.h"

#define MAX_DATA_LEN	256	// 数据缓冲区长度

// word type
#define WT_OPERATOR		0	// 操作符
#define WT_UINT			1	// 非负整数
#define WT_VARIABLE		2	// 变量

struct WORDNODE
{
	unsigned short byType;		// 类别
	char Value[MAX_DATA_LEN];	// 值
	WORDNODE *pNext;			// 下一结点
};


// 预处理：将多余空格去掉
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

// 清空链表
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

// 增加结点
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

// 根据上一状态获取单词类别
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
* 函数功能：获取下一状态
* 入口参数：cChar 当前字符
*			nStatus 当前状态
* 返 回 值：下一状态
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
* 函数功能：识别一个单词
* 入口参数：c 扫描缓冲区
*			nCur 扫描器指针
*			pTail 单词序列尾指针
* 返 回 值：识别出的单词指针，NULL表示出错
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

// 词法分析
WORDNODE* WordAnalysis(char c[])
{
	// 第一个结点作为头结点，不使用
	WORDNODE *pHeader = (WORDNODE *)malloc(sizeof(WORDNODE));
	pHeader->pNext = NULL;
	WORDNODE *pTail = pHeader, *pNode = NULL;

	// 词法分析
	for (int nCur = 0; c[nCur] != '\0'; nCur++)
	{
		
		// 识别一个单词
		pTail = IdentifyOneWord(c, nCur, pTail);
		
		if (pTail == NULL)	// 出错
		{
			
			Clear(pHeader);
			return NULL;
		}

	}

	return pHeader;
}

bool Save(WORDNODE *pHeader)
{
	// 文件名
	char FileName[256];
	printf("单词序列输出文件名（如a.txt）：\n");
	scanf("%s", FileName);

	// 打开文件
	FILE *f = fopen(FileName, "w");
	if (f == NULL)
	{
		Clear(pHeader);
		return false;
	}

	// 空出第一个结点
	WORDNODE *pNode = pHeader->pNext;

	// 保存数据
	while (pNode != NULL)
	{
		fprintf(f, "%c,%s\n", pNode->byType + '0', pNode->Value);
		pNode = pNode->pNext;
	}

	// 关闭文件
	fclose(f);

	return true;
}

// 主函数
int main(int argc, char* argv[])
{
	// 输入
	char c[MAX_DATA_LEN];
	printf("请输入表达式：\n");
	gets(c);

	// 预处理
	Prefix(c);

	// 词法分析
	WORDNODE *pHeader = WordAnalysis(c);
	if (pHeader == NULL)
	{
		printf("\n词法分析错误!\n");
		return 0;
	}

	// 保存
	if (!Save(pHeader))
	{
		printf("\n保存文件失败\n");
		return 0;
	}

	// 清空数据
	Clear(pHeader);

	// 完成
	printf("\n词法分析成功，并已保存到文件\n", c);
	printf("按任意键退出\n", c);
	getchar();
	getchar();
	return 0;
}
