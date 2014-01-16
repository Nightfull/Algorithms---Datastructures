//排序二叉树
#include<iostream>
#include<assert.h>

typedef struct _BinaryTree
{
	int value;
	struct _BinaryTree *left_child;     //左儿子
	struct _BinaryTree *right_child;
}BinaryTree;

/*创建一个树节点*/
BinaryTree* createTreeNode(int value)
{
	BinaryTree* pBinaryTree = NULL;
	pBinaryTree = (BinaryTree *)malloc(sizeof(BinaryTree));

	memset(pBinaryTree, 0, sizeof(BinaryTree));
	pBinaryTree->value = value;

	return pBinaryTree;
}

/*这里可能会修改根节点指针，所以采用二级指针传递
任意左右子树也是二叉查找树，也有相应的“根节点”*/
bool insertNode(BinaryTree **ppBinaryTree, int value)
{
	if (NULL == ppBinaryTree)
		return false;

	if (NULL == *ppBinaryTree)    //空树及递归终止条件
	{
		*ppBinaryTree = createTreeNode(value);  //创建树节点插入
		assert(NULL != *ppBinaryTree);
		return true;
	}
	else
	{   //插入值小于其根节点键值，遍历左子树
		if (value < (*ppBinaryTree)->value)
			return insertNode(&(*ppBinaryTree)->left_child, value);

		//插入值大于其根节点键值，遍历右子树
		else if (value > (*ppBinaryTree)->value)
			return insertNode(&(*ppBinaryTree)->right_child, value);

		//重复元插入，直接返回
		else
			return false;
	}
}

BinaryTree* findTreeNode(BinaryTree *pBinaryTree, int key)
{
	if (NULL == pBinaryTree)        //二叉树不存在或递归终止条件(键值未找到)
		return NULL;

	if (key == pBinaryTree->value)  //根节点为键值或递归终止条件(找到对应键值)
		return pBinaryTree;

	else if (key < pBinaryTree->value)
		return findTreeNode(pBinaryTree->left_child, key);

	else
		return findTreeNode(pBinaryTree->right_child, key);
}

/*二叉查找树的性质让我们可以很方便的查找最小最大键值*/
/*查找最小键值节点：直接递归遍历左子树叶子节点*/
BinaryTree* findMin(BinaryTree *pBinaryTree)
{
	if (NULL == pBinaryTree)
		return NULL;

	else if (NULL == pBinaryTree->left_child)
		return pBinaryTree;

	else
		return findMin(pBinaryTree->left_child);
}

/*非递归实现查找最大键值节点*/
BinaryTree* findMax(BinaryTree *pBinaryTree)
{
	if (pBinaryTree != NULL)
	{
		while (pBinaryTree->right_child)
			pBinaryTree = pBinaryTree->right_child;
	}

	return pBinaryTree;
}
/*
*              6                             6                       6                 
*             /                             /                       /                 
*            2                             3                       3                  
*             \            -->              \            -->        \     
*              4                             4                       4            
*             /                             /                        
*            3                             3                        
*/
/*
*删除操作需要修改节点指针，故采用二级指针传递
*删除操作就是不断的转移目标节点，直到目标节点为叶子节点了，就删除
*/
bool deleteNode(BinaryTree **pBinaryNode, int key)
{
	BinaryTree *pTempNode = NULL;

	if ((NULL == pBinaryNode) || (NULL == *pBinaryNode))  //树为空或未找到目标节点
		return false;

	/*查找目标节点*/
	else if (key < (*pBinaryNode)->value)
		return deleteNode(&(*pBinaryNode)->left_child, key);
	else if (key >(*pBinaryNode)->value)
		return deleteNode(&(*pBinaryNode)->right_child, key);

	/*已找到目标节点pBinaryNode*/
	/*目标节点有两个儿子*/
	else if ((*pBinaryNode)->left_child && (*pBinaryNode)->right_child)
	{
		pTempNode = findMin((*pBinaryNode)->right_child);  //找到右子树的最小节点
		(*pBinaryNode)->value = pTempNode->value;
		return deleteNode(&(*pBinaryNode)->right_child, (*pBinaryNode)->value);  //递归地删除该节点
	}/*此处参数以及后面的递归删除参数均不能用pDelNode替代，必须用现在这个，否则打印时出现乱码*/
	else
	{    /*目标节点只有左儿子*/
		if ((*pBinaryNode)->left_child && (NULL == (*pBinaryNode)->right_child))
		{
			pTempNode = findMax((*pBinaryNode)->left_child);  //找到左子树的最大节点
			(*pBinaryNode)->value = pTempNode->value;
			return deleteNode(&(*pBinaryNode)->left_child, (*pBinaryNode)->value);
		}
		/*目标节点只有右儿子*/
		else if ((*pBinaryNode)->right_child && (NULL == (*pBinaryNode)->left_child))
		{
			pTempNode = findMin((*pBinaryNode)->right_child); //找到右子树的最小节点
			(*pBinaryNode)->value = pTempNode->value;
			return deleteNode(&(*pBinaryNode)->right_child, (*pBinaryNode)->value);
		}
		/*目标节点没有儿子，含叶子节点和没有儿子的根节点情况*/
		/*实际上几乎所有删除节点操作都会执行下面这步，也就是递归地删除节点最终会递归到删除某叶子节点*/
		else
		{
			free(*pBinaryNode);       //已经递归到叶子节点
			(*pBinaryNode) = NULL;   
		}
	}

	return true;
}

/*
*              6             先序遍历： 6 2 1 4 3 8 10
*             / \                      
*            2   8           中序遍历： 1 2 3 4 6 8 10
*           / \   \       
*          1   4   10        后序遍历： 1 3 4 2 10 8 6
*             /                           
*            3                           
*/
/*先序遍历*/
void printPreorder(BinaryTree *pBinaryTree)
{
	if (NULL != pBinaryTree)
	{
		printf("%d\n", pBinaryTree->value);
		printPreorder(pBinaryTree->left_child);
		printPreorder(pBinaryTree->right_child);
	}
}

/*中序遍历*/
void printInorder(BinaryTree *pBinaryTree)
{
	if (NULL != pBinaryTree)
	{
		printInorder(pBinaryTree->left_child);
		printf("%d\n", pBinaryTree->value);
		printInorder(pBinaryTree->right_child);
	}
}

/*后序遍历*/
void printPostorder(BinaryTree *pBinaryTree)
{
	if (NULL != pBinaryTree)
	{
		printPostorder(pBinaryTree->left_child);
		printPostorder(pBinaryTree->right_child);
		printf("%d\n", pBinaryTree->value);
	}
}
