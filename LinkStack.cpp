#include<iostream>
#include<cassert>
using namespace std;

typedef struct _Stack
{
	int *pData;   //数据域指针  
	int size;     //栈容量  
	int top;      //栈顶  
}Stack;

Stack* createStack(int MaxElements)
{
	Stack *pStack = NULL;
	if (0 == MaxElements)
		return NULL;

	pStack = (Stack *)malloc(sizeof(Stack));   //开辟栈节点空间  
	assert(NULL != pStack);
	memset(pStack, 0, sizeof(Stack));

	pStack->pData = (int *)malloc(sizeof(int)* MaxElements);   //开辟数据空间  
	if (NULL == pStack->pData)
	{
		free(pStack);
		pStack = NULL;
	}

	memset(pStack->pData, 0, sizeof(int)* MaxElements);
	pStack->size = MaxElements;
	pStack->top = -1;    //这里按照数组形式，初始值为-1  
	//也设置为栈顶“指针”时刻指向栈顶元素  
	return pStack;
}

bool isFull(Stack *pStack)
{
	return (pStack->size == (pStack->top + 1));
}

bool isEmpty(Stack *pStack)
{
	return (-1 == pStack->top);
}

bool push(Stack *pStack, int value)
{
	if (NULL == pStack)
		return false;

	if (isFull(pStack))
		return false;

	pStack->pData[++pStack->top] = value;
	return true;
}

bool pop(Stack *pStack, int *value)
{
	if (NULL == pStack)
		return false;

	if (isEmpty(pStack))
		return false;

	*value = pStack->pData[pStack->top--];
	return true;
}

bool freeStack(Stack **ppStack)
{
	if (NULL == *ppStack)
		return false;

	if (NULL == (*ppStack)->pData)
	{
		free(*ppStack);
		*ppStack = NULL;
		return true;
	}

	free((*ppStack)->pData);
	free(*ppStack);
	*ppStack = NULL;   //设置，便于后面判断  
	//所以设置二级指针传递  
	return true;
}

void printStack(Stack *pStack)
{
	if (pStack)
	{
		int num = pStack->top;

		while (-1 != num)
			printf("%d\n", pStack->pData[num--]);
	}
}
