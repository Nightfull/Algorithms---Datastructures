#include<iostream>
#include<cassert>

typedef struct _Queue
{
	int *pData;       //数据域指针  
	int capacity;     //队列容量  
	int front;        //队列首位置  
	int rear;         //队列尾位置  
	int count;        //队列数据量  
}Queue;

Queue* createQueue(int num)
{
	Queue *pQueue = NULL;
	if (0 == num)
		return NULL;

	pQueue = (Queue *)malloc(sizeof(Queue));  //开辟队列节点  
	assert(NULL != pQueue);
	memset(pQueue, 0, sizeof(Queue));

	pQueue->pData = (int *)malloc(sizeof(int)* num);   //开辟数据域空间  
	if (NULL == pQueue->pData)
	{
		free(pQueue);          //数据域开辟失败，释放队列节点空间  
		pQueue = NULL;
		return NULL;
	}
	pQueue->capacity = num;    //指定容量  

	return pQueue;
}

bool isFull(Queue *pQueue)
{
	return (pQueue->count == pQueue->capacity);
}

bool isEmpty(Queue *pQueue)
{
	return (0 == pQueue->count);
}

/*入队*/
bool enQueue(Queue *pQueue, int value)
{
	if (NULL == pQueue)
		return false;

	if (isFull(pQueue))
		return false;

	pQueue->pData[pQueue->rear] = value;
	pQueue->rear = (pQueue->rear + 1) % pQueue->capacity;   //循环线性队列
	pQueue->count++;

	return true;
}

bool deQueue(Queue *pQueue, int *value)
{
	if (NULL == pQueue)
		return false;

	if (isEmpty(pQueue))
		return false;

	*value = pQueue->pData[pQueue->front];
	pQueue->count--;
	pQueue->front = (pQueue->front + 1) % pQueue->capacity;

	return true;
}

bool freeQueue(Queue **ppQueue)
{
	if ((NULL == ppQueue) || (NULL == *ppQueue))
		return false;

	if (NULL == (*ppQueue)->pData)
	{
		free(*ppQueue);
		*ppQueue = NULL;
		return true;
	}

	free((*ppQueue)->pData);
	(*ppQueue)->pData = NULL;
	free(*ppQueue);
	*ppQueue = NULL;

	return true;
}

void printQueue(Queue *pQueue)
{
	if (pQueue)
	{
		int i = pQueue->front;
		int cnt = pQueue->count;
		while (0 != cnt)
		{
			printf("%d\n", pQueue->pData[(i++) % pQueue->capacity]);
			--cnt;
		}

		return;
	}
}
