#include<iostream>
#include<assert.h>
using namespace std;

typedef struct _Node
{
	int value;
	struct _Node *pnext;
}Node;

void createList(Node **ppListNode, int value)
{
	Node *pListNode = NULL;
	pListNode = (Node *)malloc(sizeof(Node));
	assert(pListNode != NULL);

	pListNode->value = value;
	pListNode->pnext = NULL;

	*ppListNode = pListNode;

	return;
}

void addToTail(Node **ppListNode, int value)
{
	Node *pNew = (Node *)malloc(sizeof(Node));
	pNew->value = value;
	pNew->pnext = NULL;

	if (NULL == *ppListNode)  //空链表时，此时创建的是头结点，二重指针  
	{
		*ppListNode = pNew;
		return;
	}
	else
	{
		Node *pNode = *ppListNode;

		while (pNode->pnext != NULL)
			pNode = pNode->pnext;

		pNode->pnext = pNew;
	}
	return;
}

/*链表第pos个位置后面插入元素value*/
void insertNode(Node **ppListNode, int pos, int value)
{
	if ((NULL == ppListNode) || (pos < 0))
		return;
	if (NULL == *ppListNode)        //链表为空，直接创建新链表  
		createList(ppListNode, value);

	Node *pNode, *pNew;
	pNode = *ppListNode;

	pNew = (Node *)malloc(sizeof(Node));
	pNew->value = value;
	pNew->pnext = NULL;

	/*插入第0个位置，即新元素取代头结点*/
	if (0 == pos)
	{
		pNew->pnext = pNode;
		*ppListNode = pNew;

		return;
	}

	/*寻找第pos个位置的前一个结点pNode*/
	while (--pos)
	{
		pNode = pNode->pnext;
		if (NULL == pNode)
			return;       //插入位置大于链表长度，直接返回  
	}

	pNew->pnext = pNode->pnext;
	pNode->pnext = pNew;

	return;
}

/*删除指定数据结点*/
void deleteValue(Node **ppListNode, int value)
{
	Node *pNode;
	if ((NULL == ppListNode) || (NULL == *ppListNode))
		return;

	if ((*ppListNode)->value == value)     //结点为头结点  
	{
		pNode = *ppListNode;
		*ppListNode = pNode->pnext;
		free(pNode);

		return;
	}

	pNode = *ppListNode;
	/*链表仅一个非待删除节点处理，不然下面的while会出错*/
	if (NULL == pNode->pnext)
		return;

	/*寻找该元素的上一个结点pNode*/
	while (pNode->pnext->value != value)
	{
		pNode = pNode->pnext;
		if (NULL == pNode->pnext)
			return;        //没找到，直接返回  
	}

	Node *pDel = pNode->pnext;     //pNode的下一节点为待删除节点  
	pNode->pnext = pDel->pnext;
	free(pDel);

	return;
}

/*删除链表中所有指定数据结点*/
void deleteAllValue(Node **ppListNode, int value)
{
	Node *pNode;
	if ((NULL == ppListNode) || (NULL == *ppListNode))
		return;

	if ((*ppListNode)->value == value)     //结点为头结点  
	{
		pNode = *ppListNode;
		*ppListNode = pNode->pnext;
		free(pNode);

		return deleteAllValue(ppListNode, value);
	}

	pNode = *ppListNode;
	/*链表仅一个非待删除节点处理，不然下面的while会出错*/
	if (NULL == pNode->pnext)
		return;

	/*寻找该元素的上一个结点pNode*/
	while (pNode->pnext->value != value)
	{
		pNode = pNode->pnext;
		if (NULL == pNode->pnext)
			return;        //没找到，直接返回  
	}

	Node *pDel = pNode->pnext;     //pNode的下一节点为待删除节点  
	pNode->pnext = pDel->pnext;
	free(pDel);

	return deleteAllValue(ppListNode, value);
}

/*删除指定位置pos的节点*/
void deleteNode(Node **ppListNode, int pos)
{
	if ((NULL == ppListNode) || (NULL == *ppListNode) || (pos < 0))
		return;

	Node *pNode = *ppListNode;
	if (0 == pos)         //头结点位置  
	{
		*ppListNode = pNode->pnext;
		free(pNode);

		return;
	}

	/*寻找第pos-1位置的节点*/
	while (--pos)
	{
		pNode = pNode->pnext;
		if (NULL == pNode)
			return;    //删除位置大于链表长度  
	}

	Node *pDel = pNode->pnext;
	if (NULL == pDel)    //删除位置为链表尾节点后面的那个位置  
		return;

	pNode->pnext = pDel->pnext;
	free(pDel);

	return;
}

/*顺序打印链表*/
void printNode(Node *pListNode)
{
	if (pListNode)
	{
		printf("%d\n", pListNode->value);
		printNode(pListNode->pnext);
	}
}

/*逆序打印链表*/
void printNodeReverse(Node *pListNode)
{
	if (pListNode)
	{
		printNodeReverse(pListNode->pnext);
		printf("%d\n", pListNode->value);
	}
}

int countNode(Node *pListNode)
{
	/*if (NULL == pListNode)
	return 0;

	return 1 + countNode(pListNode->pnext);*/

	int count = 0;
	while (pListNode)
	{
		pListNode = pListNode->pnext;
		++count;
	}

	return count;
}
