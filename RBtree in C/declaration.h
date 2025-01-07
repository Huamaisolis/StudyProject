#pragma once
#ifndef MyRBtree 
#define  MyRBtree
#include <stdio.h>
#include <stdlib.h>
typedef int T;
typedef enum colorType { BLACK, RED }colorType;
typedef enum RotationType { 
	//插入后会有需要旋转的情况 其中r型只需改色 b型则需要根据LL/LR/RL/RR进行旋转等操作
	isROOT,
	FINE,
	LLr,
	LRr,
	RRr,
	RLr,
	LLb,
	RRb,
	LRb,
	RLb
}RotationType;
typedef struct RBnode RBnode;
typedef struct RBtree RBtree;
struct RBnode
{
	T element;
	colorType color;//默认外部节点为黑色
	int DOUBLEBLACK;//双黑特性;红黑树要求从根到外部节点每条路径的黑色节点数量一样;
	//当假定需要删除A节点(黑色)后,经过A节点的所有路径都会缺少一个黑色节点,此时将DOUBLEBLACK改为true,并且进行维护
	RBnode* leftChild;
	RBnode* rightChild;
	RBnode* parent;
};
RBnode* createNode(T theElement,colorType color)
{
	RBnode* newNode = (RBnode*)malloc(sizeof(RBnode));
	if (newNode == NULL) {
		printf("Memory allocation failed\n");
		return NULL; 
	}
	newNode->element = theElement;
	newNode->color = color;
	newNode->DOUBLEBLACK = 0;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;
	newNode->parent = NULL;
	return newNode;
}

struct RBtree
{
	RBnode* root;
	int treeSize;
	colorType(*getColor)(RBnode* node);
};
void initializeTree(RBtree* tree,T element)
{
	tree->root = createNode(element, BLACK);
	tree->treeSize = 1;
}

colorType getColor(RBnode* node){return ((node==NULL) ? BLACK : node->color);}
void EZchangeColor(RBtree* tree,RBnode* node)
{
	if(node->leftChild!=NULL)
		node->leftChild->color = BLACK;
	if (node->rightChild != NULL)
	node->rightChild->color = BLACK;
	node->color = RED;
	if (node == tree->root)node->color = BLACK;
}

RotationType figureSituation(RBtree* tree,RBnode* Gnode);
RBnode* leftRotateWithColor(RBtree* tree, RBnode* GNode);
RBnode* leftRotate(RBtree* tree, RBnode* GNode);
RBnode* rightRotateWithColor(RBtree* tree, RBnode* GNode);
RBnode* rightRotate(RBtree* tree, RBnode* GNode);
RBnode* insert(RBtree* tree, T theElement);
RBnode* insertLogic(RBtree* tree,RBnode* node, T theElement);
void fixDoubleBlack(RBtree* tree,RBnode* node);
RBnode* erase(RBtree* tree, T theElement);
RBnode* eraseLogic(RBtree* tree, RBnode* node, T theElement);
int find(RBtree* tree,RBnode*node, T theElement);

void preOrder(RBtree* tree, RBnode* node);
void inOrder(RBtree* tree, RBnode* node);
void reverseOrder(RBtree* tree, RBnode* node);
void postOrder(RBtree* tree, RBnode* node);

#endif

	RotationType figureSituation(RBtree* tree, RBnode* GNode)
	{
		RBnode* LChild = GNode->leftChild, * RChild = GNode->rightChild;
		if (LChild != NULL && getColor(LChild) == RED)
		{
			if (getColor(LChild->leftChild) == RED)
			{
				if (getColor(RChild) == BLACK)return LLb;
				else return LLr;
			}
			else if (getColor(LChild->rightChild) == RED)
			{
				if (getColor(RChild) == BLACK)return LRb;
				else return LRr;
			}
		}
		if (RChild != NULL && getColor(RChild) == RED)
		{
			if (getColor(RChild->leftChild) == RED)
			{
				if (getColor(LChild) == BLACK)return RLb;
				else return RLr;
			}
			else if (getColor(RChild->rightChild) == RED)
			{
				if (getColor(LChild) == BLACK)return RRb;
				else return RRr;
			}
		}

		if (GNode == tree->root)return isROOT;
		return FINE;
	}

	RBnode* leftRotate(RBtree* tree, RBnode* GNode)
	{
		RBnode* PNode = GNode->rightChild;
		GNode->rightChild = PNode->leftChild;

		if (PNode->leftChild != NULL)
			PNode->leftChild->parent = GNode;
		PNode->parent = GNode->parent;
		if (GNode->parent == NULL)
			tree->root = PNode;
		else if (GNode == GNode->parent->leftChild)
			GNode->parent->leftChild = PNode;
		else
			GNode->parent->rightChild = PNode;

		PNode->leftChild = GNode;
		GNode->parent = PNode;
		return PNode;
	}
	RBnode* leftRotateWithColor(RBtree* tree, RBnode* GNode)
	{
		RBnode* PNode = GNode->rightChild;
		GNode->rightChild = PNode->leftChild;

		if (PNode->leftChild != NULL)
			PNode->leftChild->parent = GNode;
		PNode->parent = GNode->parent;
		if (GNode->parent == NULL)
			tree->root = PNode;
		else if (GNode == GNode->parent->leftChild)
			GNode->parent->leftChild = PNode;
		else
			GNode->parent->rightChild = PNode;

 		PNode->leftChild = GNode;
		GNode->parent = PNode;
		PNode->color = BLACK;
		GNode->color = RED;
		return PNode;
	}

	RBnode* rightRotate(RBtree* tree, RBnode* GNode)
	{
		RBnode* PNode = GNode->leftChild;
		GNode->leftChild = PNode->rightChild;
		if (PNode->rightChild != NULL)
			PNode->rightChild->parent = GNode;
		PNode->parent = GNode->parent;

		if (GNode->parent == NULL)
			tree->root = PNode;
		else if (GNode == GNode->parent->leftChild)
			GNode->parent->leftChild = PNode;
		else
			GNode->parent->rightChild = PNode;
		PNode->rightChild = GNode;
		GNode->parent = PNode;
		return PNode;
	}
	RBnode* rightRotateWithColor(RBtree* tree, RBnode* GNode)
	{
		RBnode* PNode = GNode->leftChild;
		GNode->leftChild = PNode->rightChild;
		if (PNode->rightChild != NULL)
			PNode->rightChild->parent = GNode;
		PNode->parent = GNode->parent;

		if (GNode->parent == NULL)
			tree->root = PNode;
		else if (GNode == GNode->parent->leftChild)
			GNode->parent->leftChild = PNode;
		else
			GNode->parent->rightChild = PNode;
		PNode->rightChild = GNode;
		GNode->parent = PNode;
		PNode->color = BLACK;
		GNode->color = RED;
		return PNode;
	}
RBnode* insert(RBtree* tree, T theElement)
{
	tree->root = insertLogic(tree, tree->root, theElement);
	if (tree->root->color == RED)tree->root->color = BLACK;
}
RBnode* insertLogic(RBtree* tree, RBnode* node, T theElement)
{
	if (node == NULL)
	{
		tree->treeSize++;
		return createNode(theElement, RED);
	}
	if (theElement < node->element)
	{
		node->leftChild = insertLogic(tree, node->leftChild, theElement);
		node->leftChild->parent = node;
	}
	else if (theElement > node->element)
	{ 
		node->rightChild = insertLogic(tree, node->rightChild, theElement);
		node->rightChild->parent = node;
	}
	else
	{
		puts("The Element had already been in the tree\n");
	}

	switch (figureSituation(tree, node))
	{
	case isROOT:
		node->color = BLACK;
		break;
	case LLr:
		EZchangeColor(tree, node);
		break;
	case LRr:
		EZchangeColor(tree, node);
		break;
	case RLr:
		EZchangeColor(tree, node);
		break;
	case RRr:
		EZchangeColor(tree, node);
		break;
	case LLb:
		return rightRotateWithColor(tree, node);
		break;
	case RRb:
		return leftRotateWithColor(tree, node);
		break;
	case LRb:
		leftRotate(tree, node->leftChild);
		return rightRotateWithColor(tree, node);
		break;
	case RLb:
		rightRotate(tree, node->rightChild);
		return leftRotateWithColor(tree, node);
		break;
	case FINE:
		break;
	}
	return node;
}

RBnode* erase(RBtree* tree, T theElement)
{
	eraseLogic(tree, tree->root, theElement);
	if (tree->root->color == RED)tree->root->color = BLACK;
}
RBnode* eraseLogic(RBtree* tree, RBnode* node, T theElement)
{
	RBnode* p = node;
	while (p->element != theElement)
	{
		if (theElement < p->element)
			p = p->leftChild;
		else if (theElement > p->element)
			p = p->rightChild;
		if (p == NULL)
		{
			printf("Element %d can not be found in the tree,erase failed\n", theElement);
			return NULL;
		}
	}

	//寻找后继节点
	RBnode* Deletion = p->rightChild;
	if (Deletion != NULL)
		while (Deletion->leftChild != NULL)
			Deletion = Deletion->leftChild;
	else
		Deletion = p;
	p->element = Deletion->element;
	if (Deletion->parent == NULL && Deletion->leftChild != NULL)
		tree->root = Deletion->leftChild;
	//后继节点Deletion要么只有一个子树,要么没有子树
	else if (Deletion->leftChild != NULL)//左孩子不为空,代替后变黑
	{
		Deletion->leftChild->color = BLACK;
		if (Deletion->parent->leftChild = Deletion)
		{
			Deletion->parent->leftChild = Deletion->leftChild;
			Deletion->leftChild->parent = Deletion->parent;
		}
		else
		{
			Deletion->parent->rightChild = Deletion->leftChild;
			Deletion->leftChild->parent = Deletion->parent;
		}
	}
	else if (Deletion->rightChild != NULL)
	{
		Deletion->rightChild->color = BLACK;
		if (Deletion->parent->leftChild = Deletion)
		{
			Deletion->parent->leftChild = Deletion->leftChild;
			Deletion->leftChild->parent = Deletion->parent;
		}
		else
		{
			Deletion->parent->rightChild = Deletion->leftChild;
			Deletion->leftChild->parent = Deletion->rightChild;
		}
	}
	else//无孩子
	{
		if (getColor(Deletion) == RED) {};//直接删除无需调整
		if (getColor(Deletion) == BLACK)
		{
			Deletion->DOUBLEBLACK = 1;
			RBnode* Parent = Deletion->parent;
			RBnode* Sibling = NULL;
			if (Parent->leftChild == Deletion)Sibling = Parent->rightChild;
			else Sibling = Parent->leftChild;
			//兄弟一定存在
			if (getColor(Sibling) == RED)
			{
				colorType temp = Parent->color;
				Parent->color = Sibling->color;
				Sibling->color = temp;
				if (Parent->leftChild == Sibling)
					rightRotate(tree, Parent);
				else
					leftRotate(tree, Parent);
				fixDoubleBlack(tree, Deletion);
			}
			else if (getColor(Sibling) == BLACK)
			{//至少有一个红孩子
				if (Parent->leftChild == Sibling)
					if (getColor(Sibling->leftChild) == RED)
					{//LL型
						Sibling->leftChild->color = Sibling->color;
						Sibling->color = Parent->color;
						Parent->color = BLACK;
						rightRotate(tree, Parent);
						Deletion->DOUBLEBLACK = 0;
					}
					else if (getColor(Sibling->rightChild) == RED)
					{//LR型
						Sibling->rightChild->color = Parent->color;
						Parent->color = BLACK;
						leftRotate(tree, Sibling);
						rightRotate(tree, Parent);
						Deletion->DOUBLEBLACK = 0;
					}
					else//双孩子都是黑色(包括外部节点
					{
						Sibling->color = RED;
						Deletion->DOUBLEBLACK = 0;
						if (Parent->color == RED)Parent->color = BLACK;
						else
						{
							Parent->DOUBLEBLACK = 1;
							fixDoubleBlack(tree, Parent);
						}
					}
				if (Parent->rightChild == Sibling)
					if (getColor(Sibling->rightChild) == RED)
					{//RR
						Sibling->rightChild->color = Sibling->color;
						Sibling->color = Parent->color;
						Parent->color = BLACK;
						leftRotate(tree, Parent);
						Deletion->DOUBLEBLACK = 0;
					}
					else if (getColor(Sibling->leftChild) == RED)
					{//RL
						Sibling->leftChild->color = Parent->color;
						Parent->color = BLACK;
						rightRotate(tree, Sibling);
						leftRotate(tree, Parent);
						Deletion->DOUBLEBLACK = 0;
					}
					else//双孩子都是黑色(包括外部节点
					{
						Sibling->color = RED;
						Deletion->DOUBLEBLACK = 0;
						if (Parent->color == RED)Parent->color = BLACK;
						else
						{
							Parent->DOUBLEBLACK = 1;
							fixDoubleBlack(tree, Parent);
						}
					}
			}
		}
	}
	if (Deletion->parent != NULL)
	{
		if (Deletion == Deletion->parent->leftChild)
			Deletion->parent->leftChild = NULL;
		else
			Deletion->parent->rightChild = NULL;
	}
	printf("Element %d erase succeed.\n", theElement);
	free(Deletion);
	return NULL;
}

void fixDoubleBlack(RBtree* tree, RBnode* node)
{
	if (node->DOUBLEBLACK == 0)
		return;
	if (node == tree->root)
	{
		node->DOUBLEBLACK = 0;
		return;
	}

	RBnode* Parent = node->parent;
	RBnode* Sibling = NULL;
	if (Parent->leftChild == node)Sibling = Parent->rightChild;
	else Sibling = Parent->leftChild;

	if (getColor(Sibling) == BLACK)
	{
		if (Parent->leftChild == Sibling)
			if (getColor(Sibling->leftChild) == RED)
			{//LL
				Sibling->leftChild->color = Sibling->color;
				Sibling->color = Parent->color;
				Parent->color = BLACK;
				rightRotate(tree, Parent);
				node->DOUBLEBLACK = 0;
			}
			else if (getColor(Sibling->rightChild) == RED)
			{//LR
				Sibling->rightChild->color = Parent->color;
				Parent->color = BLACK;
				leftRotate(tree, Sibling);
				rightRotate(tree, Parent);
				node->DOUBLEBLACK = 0;
			}
			else
			{//双孩子都是黑色(包括外部节点
				Sibling->color = RED;
				node->DOUBLEBLACK = 0;
				if (Parent->color = RED)Parent->color = BLACK;
				else
				{
					Parent->DOUBLEBLACK = 1;
					fixDoubleBlack(tree, Parent);
				}
			}
		if (Parent->rightChild == Sibling)
			if (getColor(Sibling->rightChild) == RED)
			{//RR
				Sibling->rightChild->color = Sibling->color;
				Sibling->color = Parent->color;
				Parent->color = BLACK;
				leftRotate(tree, Parent);
				node->DOUBLEBLACK = 0;
			}
			else if (getColor(Sibling->leftChild) == RED)
			{//RL
				Sibling->leftChild->color = Parent->color;
				Parent->color = BLACK;
				rightRotate(tree, Sibling);
				leftRotate(tree, Parent);
				node->DOUBLEBLACK = 0;
			}
			else
			{//双孩子都是黑色(包括外部节点
				Sibling->color = RED;
				node->DOUBLEBLACK = 0;
				if (Parent->color = RED)Parent->color = BLACK;
				else
				{
					Parent->DOUBLEBLACK = 1;
					fixDoubleBlack(tree, Parent);
				}
			}
	}
}

int find(RBtree* tree, RBnode* node, T theElement)
{
	int count=1;
	RBnode* p = node;
	while (p != NULL)
	{
		if (p->element > theElement)
		{
			p = p->leftChild;
			count *= 2;
		}
		else if (p->element < theElement)
		{  
			p = p->rightChild;
			count *= 2;
			count += 1;
		}
		else
			return count;
	}
	return -1;
}



void preOrder(RBtree* tree, RBnode* node)
{
	if (node == NULL)return;
	printf("( %d,", node->element);
	printf("%s )	", ((node->color == RED) ? "Red" : "Black"));
	preOrder(tree, node->leftChild);
	preOrder(tree, node->rightChild);
}
void inOrder(RBtree* tree, RBnode* node)
{
	if (node == NULL)return;
	inOrder(tree, node->leftChild);
	printf("( %d,", node->element);
	printf("%s )	", ((node->color == RED) ? "Red" : "Black"));
	inOrder(tree, node->rightChild);
}
void reverseOrder(RBtree* tree, RBnode* node)
{
	if (node == NULL)return;
	reverseOrder(tree, node->rightChild);
	printf("( %d,", node->element);
	printf("%s )	", ((node->color == RED) ? "Red" : "Black"));
	reverseOrder(tree, node->leftChild);

}
void postOrder(RBtree* tree, RBnode* node)
{
	if (node == NULL)return;
	postOrder(tree, node->leftChild);
	postOrder(tree, node->rightChild);
	printf("( %d,", node->element);
	printf("%s )	", ((node->color == RED) ? "Red" : "Black"));
}

void printTreeHelper(RBnode* root, int space, int level, char dir)
{
	if (root == NULL) { return; } space += 10;
	// 打印右子树 
	printTreeHelper(root->rightChild, space, level + 1, '/');
	// 打印当前节点 
	printf("\n");
	for (int i = 10; i < space; i++)
	{ 
		printf(" ");
	} 
	if (level > 0) 
	{ 
		if (dir == '/')
		{
			printf("/---");
		} 
		else if (dir == '\\') 
		{
			printf("\\---"); 
		} 
	} 
	printf("%d,%s\n", root->element, ((root->color == RED) ? "Red" : "Black"));
	// 打印左子树 
	printTreeHelper(root->leftChild, space, level + 1, '\\'); 
}

void printTree(RBnode* root) 
{
	printTreeHelper(root, 0, 0, ' '); 
}