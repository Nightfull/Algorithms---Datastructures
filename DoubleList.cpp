#include<iostream>
#include<cassert>
using namespace std;

typedef struct _Node
{
	int value;
	struct _Node *prev;
	struct _Node *next;
}Node;

void createDoubleList(Node **ppDoubleList, int val)
{
	Node *pDoubleList = NULL;
	pDoubleList = (Node *)malloc(sizeof(Node));
	assert(NULL != pDoubleList);

	memset(pDoubleList, NULL, sizeof(Node));
	pDoubleList->value = val;

	*ppDoubleList = pDoubleList;

	return;
}

void addToTail(Node **ppDoubleList, int val)
{
	Node *pNew = (Node *)malloc(sizeof(Node));
	memset(pNew, NULL, sizeof(Node));
	pNew->value = val;

	if (NULL == ppDoubleList)
		return;

	if (NULL == *ppDoubleList)
	{
		*ppDoubleList = pNew;
		return;
	}
	else
	{
		Node *pNode = *ppDoubleList;

		while (NULL != pNode->next)
			pNode = pNode->next;

		pNode->next = pNew;
		pNew->prev = pNode;

		return;
	}
}

void insertNode(Node **ppDoubleList, int pos, int val)
{
	if ((NULL == ppDoubleList) || (pos < 0))
		return;
	if (NULL == *ppDoubleList)        //链表为空，直接创建新链表    
		createDoubleList(ppDoubleList, val);

	Node *pNode, *pNew;
	pNode = *ppDoubleList;

	pNew = (Node *)malloc(sizeof(Node));
	memset(pNew, NULL, sizeof(Node));
	pNew->value = val;

	if (0 == pos)    //插入链表首位置  
	{
		pNode->prev = pNew;
		pNew->next = pNode;
		*ppDoubleList = pNew;

		return;
	}

	while (--pos)
	{
		pNode = pNode->next;
		if (NULL == pNode)  //插入位置大于链表长度  
			return;
	}

	pNew->next = pNode->next;
	pNode->next->prev = pNew;
	pNode->next = pNew;
	pNew->prev = pNode;

	return;
}

/*删除单个指定元素节点*/
void deleteValue(Node **ppDoubleList, int value)
{
	Node *pNode = *ppDoubleList;
	if ((NULL == ppDoubleList) || (NULL == *ppDoubleList))
		return;

	/*删除元素在头节点*/
	if (value == pNode->value)
	{
		*ppDoubleList = pNode->next;
		if (*ppDoubleList)  //链表仅一个节点  
			(*ppDoubleList)->prev = NULL;
	}
	else
	{
		/*查找指定待删除元素节点*/
		while (pNode->value != value)
		{
			pNode = pNode->next;
			if (NULL == pNode)    //元素不存在  
				return;
		}
		if (pNode->next)    //待删除元素是非尾节点  
		{
			pNode->prev->next = pNode->next;
			pNode->next->prev = pNode->prev;
		}
		else
		{     //待删除元素为尾节点  
			pNode->prev->next = pNode->next;
		}
	}
	free(pNode);
	pNode = NULL;

	return;
}

/*删除所有指定元素节点*/
void deleteAllValue(Node **ppDoubleList, int value)
{
	Node *pNode = *ppDoubleList;
	if ((NULL == ppDoubleList) || (NULL == *ppDoubleList))
		return;

	/*删除元素在头节点*/
	if (value == pNode->value)
	{
		*ppDoubleList = pNode->next;
		if (*ppDoubleList)
			(*ppDoubleList)->prev = NULL;
	}
	else
	{
		/*查找指定待删除元素节点*/
		while (pNode->value != value)
		{
			pNode = pNode->next;
			if (NULL == pNode)    //元素不存在  
				return;
		}
		if (pNode->next)    //待删除元素是非尾节点  
		{
			pNode->prev->next = pNode->next;
			pNode->next->prev = pNode->prev;
		}
		else
		{     //待删除元素为尾节点  
			pNode->prev->next = pNode->next;
		}
	}
	free(pNode);
	pNode = NULL;

	return deleteAllValue(ppDoubleList, value);
}

void deleteNode(Node **ppDoubleList, int pos)
{
	Node *pNode = *ppDoubleList;   //pNode为待删除节点  
	if ((NULL == ppDoubleList) || (NULL == *ppDoubleList) || (pos < 0))
		return;

	/*删除首节点情况*/
	if (0 == pos)
	{
		*ppDoubleList = pNode->next;
		(*ppDoubleList)->prev = NULL;
	}
	else
	{   /*找到待删除节点*/
		while (pos--)
		{
			pNode = pNode->next;
			if (NULL == pNode)  //位置大于长度返回  
				return;
		}
		pNode->prev->next = pNode->next;
		if (pNode->next)    //如果删除节点不是最后一个节点  
			pNode->next->prev = pNode->prev;
	}
	free(pNode);
	pNode = NULL;

	return;
}
