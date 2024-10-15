//Made by Huamai_Solis in 2024/10/15

#ifndef _RBTREE
#define _RETREE

#include <iostream>
#include "Exceptions_.h"
using namespace std;
enum colorType { BLACK, RED };
enum RotationType { //插入后会有需要旋转的情况 其中r型只需改色 b型则需要根据LL/LR/RL/RR进行旋转等操作
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
};

template<typename T>
struct RBnode
{
	T element;
	colorType color;//默认外部节点为黑色
	bool DOUBLEBLACK;//双黑特性;红黑树要求从根到外部节点每条路径的黑色节点数量一样;
						//当假定需要删除A节点(黑色)后,经过A节点的所有路径都会缺少一个黑色节点,此时将DOUBLEBLACK改为true,并且进行维护
	RBnode<T>* leftChild;
	RBnode<T>* rightChild;
	RBnode<T>* parent;
	RBnode(T theElement, colorType theColor)
	{//外部节点用nullptr表示
		element = theElement; color = theColor; DOUBLEBLACK = false;
		leftChild = rightChild = parent = nullptr;
	}
};

template<typename T>
class NewRBtree
{
private:
	RBnode<T>* root;
	int treeSize;
	colorType getColor(RBnode<T>* node)
	{
		return node ? node->color : BLACK; // 如果节点为是外部节点,返回空
	}
	//改色和不改色的旋转
	RBnode<T>* leftRotateWithColor(RBnode<T>* node);
	RBnode<T>* leftRotate(RBnode<T>* node);
	RBnode<T>* rightRotateWithColor(RBnode<T>* node);
	RBnode<T>* rightRotate(RBnode<T>* node);
	//找到后继节点的函数(虽然我没用到)
	RBnode<T>* findSuccessor(RBnode<T>* node);
	//insert使用递归
	RBnode<T>* insert(RBnode<T>* node, T theElement);
	RotationType figureSituation(RBnode<T>* node);
	//处理双黑节点和删除函数
	void fixDoubleBlack(RBnode<T>* node);
	RBnode<T>* erase(RBnode<T>*node,T theElement);
	void EZchangeColor(RBnode<T>* node)
	{
		node->leftChild->color = BLACK;
		node->rightChild->color = BLACK;
		node->color = RED;
		if (node == root)node->color = BLACK;
	}
protected:
	static void(*visit)(RBnode<T>*);
	static void preOrder(RBnode<T>* t);
	static void inOrder(RBnode<T>* t);
	static void postOrder(RBnode<T>* t);
	static void output(RBnode<T>* t) { cout << t->element << ' '; }

public:
	NewRBtree() { root = new RBnode<T>(nullptr, BLACK); }
	NewRBtree(T theElement) { root = new RBnode<T>(theElement, BLACK); treeSize = 1; }
	void insert(T theElement) { root = insert(root, theElement); }	//用户使用这个
	void erase(T theElement) {erase(root, theElement); }//用户使用这个
	void preOrder(void(*theVisit)(RBnode<T>*)) { visit = theVisit; preOrder(root); }
	void preOrderOutput() { preOrder(output); cout << endl; }
	void inOrder(void(*theVisit)(RBnode<T>*)) { visit = theVisit; inOrder(root); }
	void inOrderOutput() { inOrder(output); cout << endl; }
	void postOrder(void(*theVisit)(RBnode<T>*)) { visit = theVisit; postOrder(root); }
	void postOrderOutput() { postOrder(output); cout << endl; }
};

template<typename T>
RotationType NewRBtree<T>::figureSituation(RBnode<T>* Gnode)
{

	RBnode<T>* LChild = Gnode->leftChild, * RChild = Gnode->rightChild;
	if (LChild!=nullptr && getColor(LChild) == RED)
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

	if (RChild!=nullptr && getColor(RChild) == RED)
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
	if (Gnode == root)return isROOT;
	return FINE;
}

template<typename T>
RBnode<T>* NewRBtree<T>::leftRotateWithColor(RBnode<T>* GNode)
{
	RBnode<T>* PNode = GNode->rightChild;
	GNode->rightChild = PNode->leftChild;

	if (PNode->leftChild != nullptr) {
		PNode->leftChild->parent = GNode; // 更新新左子树的 parent 指针
	}

	PNode->parent = GNode->parent; // 更新 PNode 的 parent 指针
	if (GNode->parent == nullptr) {
		root = PNode; // 更新 root
	}
	else if (GNode == GNode->parent->leftChild) {
		GNode->parent->leftChild = PNode; // 更新父节点的左子树
	}
	else {
		GNode->parent->rightChild = PNode; // 更新父节点的右子树
	}

	PNode->leftChild = GNode;
	GNode->parent = PNode; // 更新 GNode 的 parent 指针
	PNode->color = BLACK;
	GNode->color = RED;
	return PNode;
}template<typename T>
RBnode<T>* NewRBtree<T>::leftRotate(RBnode<T>* GNode)
{
	RBnode<T>* PNode = GNode->rightChild;
	GNode->rightChild = PNode->leftChild;

	if (PNode->leftChild != nullptr) {
		PNode->leftChild->parent = GNode; // 更新新左子树的 parent 指针
	}

	PNode->parent = GNode->parent; // 更新 PNode 的 parent 指针
	if (GNode->parent == nullptr) {
		root = PNode; // 更新 root
	}
	else if (GNode == GNode->parent->leftChild) {
		GNode->parent->leftChild = PNode; // 更新父节点的左子树
	}
	else {
		GNode->parent->rightChild = PNode; // 更新父节点的右子树
	}

	PNode->leftChild = GNode;
	GNode->parent = PNode; // 更新 GNode 的 parent 指针

	return PNode;
}

template<typename T>
RBnode<T>* NewRBtree<T>::rightRotateWithColor(RBnode<T>* GNode)
{
	RBnode<T>* PNode = GNode->leftChild;
	GNode->leftChild = PNode->rightChild;

	if (PNode->rightChild != nullptr) {
		PNode->rightChild->parent = GNode; // 更新新左子树的 parent 指针
	}

	PNode->parent = GNode->parent; // 更新 PNode 的 parent 指针
	if (GNode->parent == nullptr) {
		root = PNode; // 更新 root
	}
	else if (GNode == GNode->parent->leftChild) {
		GNode->parent->leftChild = PNode; // 更新父节点的左子树
	}
	else {
		GNode->parent->rightChild = PNode; // 更新父节点的右子树
	}
	PNode->rightChild = GNode;
	GNode->parent = PNode; // 更新 GNode 的 parent 指针
	PNode->color = BLACK;
	GNode->color = RED;
	return PNode;
}template<typename T>
RBnode<T>* NewRBtree<T>::rightRotate(RBnode<T>* GNode)
{
	RBnode<T>* PNode = GNode->leftChild;
	GNode->leftChild = PNode->rightChild;

	if (PNode->rightChild != nullptr) {
		PNode->rightChild->parent = GNode; // 更新新左子树的 parent 指针
	}

	PNode->parent = GNode->parent; // 更新 PNode 的 parent 指针
	if (GNode->parent == nullptr) {
		root = PNode; // 更新 root
	}
	else if (GNode == GNode->parent->leftChild) {
		GNode->parent->leftChild = PNode; // 更新父节点的左子树
	}
	else {
		GNode->parent->rightChild = PNode; // 更新父节点的右子树
	}
	PNode->rightChild = GNode;
	GNode->parent = PNode; // 更新 GNode 的 parent 指针
	return PNode;
}


template<typename T>
RBnode<T>* NewRBtree<T>::insert(RBnode<T>* node, T theElement)
{
	if (node == nullptr)
	{
		treeSize++;
		return new RBnode<T>(theElement, RED);
	}
	if (theElement < node->element)
	{
		node->leftChild = insert(node->leftChild, theElement);
		node->leftChild->parent = node; // 更新 parent 指针
	}
	else if (theElement > node->element)
	{
		node->rightChild = insert(node->rightChild, theElement);
		node->rightChild->parent = node;
	}
	else
	{
		cout << "Element " << theElement << " has been in RB tree, insert failed." << endl;
		throw(insertFalse("Element has been in RB tree, insert failed."));
	}

	switch (figureSituation(node))
	{
	case isROOT:
		node->color = BLACK;
		break;
	case LLr:
		EZchangeColor(node);
		break;
	case LRr:
		EZchangeColor(node);
		break;
	case RLr:
		EZchangeColor(node);
		break;
	case RRr:
		EZchangeColor(node);
		break;
	case LLb:
		return rightRotateWithColor(node);
		break;
	case RRb:
		return leftRotateWithColor(node);
		break;
	case LRb:
		leftRotate(node->leftChild);
		return rightRotateWithColor(node);
		break;
	case RLb:
		rightRotate(node->rightChild);
		return leftRotateWithColor(node);
		break;
	case FINE:
		break;
	}
	return node;
}

template<typename T>
void (*(NewRBtree<T>::visit))(RBnode<T>*) = nullptr;

template<typename T>
void NewRBtree<T>::preOrder(RBnode<T>* t)
{
	if (t != nullptr)
	{
		NewRBtree<T>::visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}

template<typename T>
void NewRBtree<T>::inOrder(RBnode<T>* t)
{
	if (t != nullptr)
	{
		inOrder(t->leftChild);
		NewRBtree<T>::visit(t);
		inOrder(t->rightChild);
	}
}

template<typename T>
void NewRBtree<T>::postOrder(RBnode<T>* t)
{
	if (t != nullptr)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		NewRBtree<T>::visit(t);
	}
}
template<typename T>//这个函数没有用到
RBnode<T>* NewRBtree<T>::findSuccessor(RBnode<T>* node)
{
	RBnode<T>* p;
	p = node->rightChild;
	if (p != nullptr)
	{
		for (; p->leftChild != nullptr; p = p->leftChild);
	}
	else
	{
		for (p = node->parent; node == p->rightChild; node = p, p = p->parent);
		if (p == root)p = nullptr;
	}
	return p;	
}

template<typename T>
RBnode<T>* NewRBtree<T>::erase(RBnode<T>* node, T theElement) {
	// 找到需要删除的节点
	RBnode<T>* p = node;
	while (p->element != theElement)
	{
		if (p == nullptr)
		{//没找到
			cout << "Element " << theElement << " not found in RB tree, erase failed." << endl;
			return nullptr;
		}
		if (theElement < p->element) {
			p = p->leftChild;
		}
		else if (theElement > p->element) {
			p = p->rightChild;
		}
	}
	//找到了//接下来寻找前置节点
		RBnode<T>* Deletion = p->rightChild;

		if (Deletion != nullptr) {
			while (Deletion->leftChild != nullptr)
				Deletion = Deletion->leftChild;
		}
		else { 
			Deletion = p;
		}
		p->element = Deletion->element;

		//此时deletion要么只有一个孩子,要么没有孩子
		if (Deletion->leftChild != nullptr)//左孩子不为空,代替后变黑
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
		else if (Deletion->rightChild != nullptr)//右孩子不为空,代替后变黑
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
				Deletion->leftChild->parent = Deletion->parent;
			}
		}
		else {//没有孩子
			if (getColor(Deletion) == RED)//删除后无需调整
			{ }
			else {//Deletion颜色是黑的 //此时开始处理双黑
				Deletion->DOUBLEBLACK = true;
				RBnode<T>* Parent = Deletion->parent;
				RBnode<T>* Sibling = nullptr;
				if (Parent->leftChild == Deletion)Sibling = Parent->rightChild;
				else Sibling = Parent->leftChild;
				if (getColor(Sibling) == BLACK)//兄弟是黑色且一定存在(因为Deletion存在且颜色是黑色的
				{//至少有一个红孩子
					if (Parent->leftChild == Sibling)
					{
						if (getColor(Sibling->leftChild) == RED)
						{//LL型
							Sibling->leftChild->color = Sibling->color;
							Sibling->color = Parent->color;
							Parent->color = BLACK;
							rightRotate(Parent);
							Deletion->DOUBLEBLACK = false;
						}
						else if (getColor(Sibling->rightChild) == RED)
						{//LR型
							Sibling->rightChild->color = Parent->color;
							Parent->color = BLACK;
							leftRotate(Sibling);
							rightRotate(Parent);
							Deletion->DOUBLEBLACK = false;
						}
						else//双孩子都是黑色(包括外部节点
						{
							Sibling->color = RED;
							Deletion->DOUBLEBLACK = false;
							//双黑上移
							if (Parent->color == RED)Parent->color = BLACK;
							else {//父节点是黑色,成为双黑
								Parent->DOUBLEBLACK = true;
								//函数处理双黑
								fixDoubleBlack(Parent);
							}
						}
					}
					if (Parent->rightChild == Sibling)
					{
						if (getColor(Sibling->rightChild) == RED)
						{//RR型
							Sibling->rightChild->color = Sibling->color;
							Sibling->color = Parent->color;
							Parent->color = BLACK;
							leftRotate(Parent);
							Deletion->DOUBLEBLACK = false;
						}
						else if (getColor(Sibling->leftChild) == RED)
						{//RL型
							Sibling->leftChild->color = Parent->color;
							Parent->color = BLACK;
							rightRotate(Sibling);
							leftRotate(Parent);
							Deletion->DOUBLEBLACK = false;
						}
						else//双孩子都是黑色(包括外部节点
						{
							Sibling->color = RED;
							Deletion->DOUBLEBLACK = false;
							//双黑上移
							if (Parent->color == RED)Parent->color = BLACK;
							else {//父节点是黑色,成为双黑
								Parent->DOUBLEBLACK = true;
								//函数处理双黑
								fixDoubleBlack(Parent);
							}
						}
					}
				}
				else//兄弟节点是红色的
				{
					colorType temp = Parent->color;
					Parent->color = Sibling->color;
					Sibling->color = temp;
					//朝双黑节点旋转
					if (Parent->leftChild == Sibling)
						rightRotate(Parent);
					else
						leftRotate(Parent);
					fixDoubleBlack(Deletion);
				}
			}
		}
		//执行delete操作之前,需要把delete的位置设置成nullptr
		if (Deletion == Deletion->parent->leftChild)
			Deletion->parent->leftChild = nullptr;
		else
			Deletion->parent->rightChild = nullptr;

		delete Deletion;
		return nullptr;
}

template<typename T>
void NewRBtree<T>::fixDoubleBlack(RBnode<T>* node) {
	if (node->DOUBLEBLACK == false)
		return;
	if (node == root)
	{
		node->DOUBLEBLACK = false;
		return;
	}

	RBnode<T>* Parent = node->parent;
	RBnode<T>* Sibling = nullptr;
	if (Parent->leftChild == node)Sibling = Parent->rightChild;
	else Sibling = Parent->leftChild;

	if (getColor(Sibling) == BLACK)//兄弟是黑色且一定存在(因为Deletion存在且颜色是黑色的
	{//至少有一个红孩子
		if (Parent->leftChild == Sibling)
		{
			if (getColor(Sibling->leftChild) == RED)
			{//LL型
				Sibling->leftChild->color = Sibling->color;
				Sibling->color = Parent->color;
				Parent->color = BLACK;
				rightRotate(Parent);
				node->DOUBLEBLACK = false;
			}
			else if (getColor(Sibling->rightChild) == RED)
			{//LR型
				Sibling->rightChild->color = Parent->color;
				Parent->color = BLACK;
				leftRotate(Sibling);
				rightRotate(Parent);
				node->DOUBLEBLACK = false;
			}
		}
		if (Parent->rightChild == Sibling)
		{
			if (getColor(Sibling->rightChild) == RED)
			{//RR型
				Sibling->rightChild->color = Sibling->color;
				Sibling->color = Parent->color;
				Parent->color = BLACK;
				leftRotate(Parent);
				node->DOUBLEBLACK = false;
			}
			else if (getColor(Sibling->leftChild) == RED)
			{//RL型
				Sibling->leftChild->color = Parent->color;
				Parent->color = BLACK;
				rightRotate(Sibling);
				leftRotate(Parent);
				node->DOUBLEBLACK = false;
			}
		}
		else//双孩子都是黑色(包括外部节点
		{
			Sibling->color = RED;
			node->DOUBLEBLACK = false;
			//双黑上移
			if (Parent->color == RED)Parent->color = BLACK;
			else {//父节点是黑色,成为双黑
				Parent->DOUBLEBLACK = true;
				//函数处理双黑
				fixDoubleBlack(Parent);
			}
		}
	}
}

#endif


/*test.cpp
int main()
{
	NewRBtree<int> tree(2);
	int list[] = { 3,114514,5,14,17,9,6,4,100,13,10,153};
	for (int i = 0; i < 10; i++)
		tree.insert(list[i]);
	tree.insert(10);
	tree.insert(153);
	tree.erase(2);
	tree.erase(5);
	tree.erase(14);
	tree.erase(100);
	tree.erase(114514);
	cout << "preOrder:   ";
	tree.preOrderOutput();
	cout << "inOrder:    ";
	tree.inOrderOutput();
	cout << "postOrder:  ";
	tree.postOrderOutput();
	return 0;
}
*/