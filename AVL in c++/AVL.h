//Made by Huamaisolis at 2024/10/12

#ifndef _AVL
#define _AVL
#include <iostream>
#include "d:/vs/Exceptions_/Exceptions_/Exceptions_.h"
using namespace std;

template<typename T>
struct avlNode
{
	T element;
	avlNode* leftChild;
	avlNode* rightChild;
	int height;
	avlNode(T theElement) { element = theElement; leftChild = rightChild = nullptr;height = 1; }
};

int max(int a,int b)	{return (a > b) ? a : b;}

template<typename T>
class AVL
{
private:
	avlNode<T>* root;
	int size;
	int getBF(avlNode<T>* theNode) 
	{
		if (theNode->leftChild != nullptr && theNode->rightChild != nullptr)
			return (theNode->leftChild->height - theNode->rightChild->height);
		else if (theNode->leftChild == nullptr && theNode->rightChild != nullptr)
			return (0 - theNode->rightChild->height);
		else if (theNode->leftChild != nullptr && theNode->rightChild == nullptr)
			return (theNode->leftChild->height - 0);
		else return 0;
	}
	void updateHeight(avlNode<T>* node) 
	{
		if (node->leftChild != nullptr && node->rightChild != nullptr)
			node->height = 1 + max(node->leftChild->height, node->rightChild->height);
		else if (node->leftChild == nullptr && node->rightChild != nullptr)
			node->height = 1 + max(0, node->rightChild->height);
		else if (node->leftChild != nullptr && node->rightChild == nullptr)
			node->height = 1 + max(node->leftChild->height, 0);
		else node->height = 1;
	}
	avlNode<T>* leftRotate(avlNode<T>* Node);
	avlNode<T>* rightRotate(avlNode<T>* Node);
	avlNode<T>* insert(avlNode<T>* node, T theElement);
	avlNode<T>* erase(avlNode<T>* node, T theElement);
	void clear(avlNode<T>* node) {
		if (node != nullptr) {
			clear(node->leftChild);
			clear(node->rightChild);
			delete node;
		}
	}
protected:
	static void(*visit)(avlNode<T>*);
	static void preOrder(avlNode<T>* t);
	static void inOrder(avlNode<T>* t);
	static void postOrder(avlNode<T>* t);
	static void output(avlNode<T>* t) { cout << t->element << ' '; }
public:
	AVL(T element) { root = new avlNode<T>(element); size = 1; }
	~AVL() { clear(root); }
	void insert(T theElement) {
		root = insert(root, theElement);
	}
	void erase(T theElement) {
		root = erase(root, theElement);
	}
	void preOrder(void(*theVisit)(avlNode<T>*)) { visit = theVisit; preOrder(root); }
	void preOrderOutput() { preOrder(output); cout << endl; }
	void inOrder(void(*theVisit)(avlNode<T>*)) { visit = theVisit; inOrder(root); }
	void inOrderOutput() { inOrder(output); cout << endl; }
	void postOrder(void(*theVisit)(avlNode<T>*)) { visit = theVisit; postOrder(root); }
	void postOrderOutput() { postOrder(output); cout << endl; }
};

template<typename T>
avlNode<T>* AVL<T>::leftRotate(avlNode<T>* Node)//注意 此函数结束时,Node的祖先的子节点未更新
{
	avlNode<T>* newNode = Node->rightChild;
	avlNode<T>* Temp = newNode->leftChild;
	newNode->leftChild = Node;
	Node->rightChild = Temp;
	updateHeight(Node);
	updateHeight(newNode);
	return newNode;
}

template<typename T>
avlNode<T>* AVL<T>::rightRotate(avlNode<T>* Node)//注意 此函数结束时,Node的祖先的子节点未更新
{
	avlNode<T>* newNode = Node->leftChild;
	avlNode<T>* Temp = newNode->rightChild;
	newNode->rightChild = Node;
	Node->leftChild = Temp;
	updateHeight(Node);
	updateHeight(newNode);
	return newNode;
}

//使用递归的方法 可以使函数insert和erase 从上向下搜索后,能够按照原来的路径返回到root,并在返回的途中对各个节点的height进行修改
template<typename T>
avlNode<T>* AVL<T>::insert(avlNode<T>* node, T theElement)
{//先向下寻找,记录可能会失衡的节点
	if (node == nullptr)
	{
		size++;
		return new avlNode<T>(theElement);
	}

	if (theElement < node->element)
		node->leftChild = insert(node->leftChild, theElement);
	else if (theElement > node->element)
		node->rightChild = insert(node->rightChild, theElement);
	else
	{
		cout << "Element " << theElement << " has been in AVL tree, insert failed." << endl;
		throw(insertFalse("Element has been in AVL tree, insert failed."));
	}

	updateHeight(node);
	int balance = getBF(node);

	// 左左情况
	if (balance > 1 && theElement < node->leftChild->element) {
		return rightRotate(node);
	}
	// 右右情况
	if (balance < -1 && theElement > node->rightChild->element) {
		return leftRotate(node);
	}
	// 左右情况
	if (balance > 1 && theElement > node->leftChild->element) {
		node->leftChild = leftRotate(node->leftChild);
		return rightRotate(node);
	}
	// 右左情况
	if (balance < -1 && theElement < node->rightChild->element) {
		node->rightChild = rightRotate(node->rightChild);
		return leftRotate(node);
	}
	return node; // 返回未改变的节点指针
}

template<typename T>
avlNode<T>* AVL<T>::erase(avlNode<T>* node, T theElement) {
	if (node == nullptr) {
		cout << "元素 " << theElement << " 未找到，删除失败。" << endl;
		throw(illegalParameterValue("Element could not be found.")); // 元素未找到
	}

	// 执行标准的二叉搜索树删除操作
	if (theElement < node->element) {
		node->leftChild = erase(node->leftChild, theElement); // 向左子树向下寻找
	}
	else if (theElement > node->element) {
		node->rightChild = erase(node->rightChild, theElement); // 向右子树向下寻找
	}
	else {
		// 找到要删除的节点
		if (node->leftChild == nullptr) {
			avlNode<T>* temp = node->rightChild; // 只有右子树
			delete node; // 删除当前节点
			return temp; // 返回右子树
		}
		else if (node->rightChild == nullptr) {
			avlNode<T>* temp = node->leftChild; // 只有左子树
			delete node; // 删除当前节点
			return temp; // 返回左子树
		}

		// 有两个子节点：找到右子树中的最小节点（中序后继）
		avlNode<T>* temp = node->rightChild;
		while (temp->leftChild != nullptr) {
			temp = temp->leftChild; // 找到右子树中的最小节点
		}

		// 将中序后继的值复制到当前节点
		node->element = temp->element;

		// 删除中序后继
		node->rightChild = erase(node->rightChild, temp->element);
	}

	// 更新当前节点的高度
	updateHeight(node);

	// 获取当前节点的平衡因子
	int balance = getBF(node);

	// 进行平衡操作
	// LL情况
	if (balance > 1 && getBF(node->leftChild) >= 0) {
		return rightRotate(node);
	}
	// LR情况
	if (balance > 1 && getBF(node->leftChild) < 0) {
		node->leftChild = leftRotate(node->leftChild);
		return rightRotate(node);
	}
	// RR情况
	if (balance < -1 && getBF(node->rightChild) <= 0) {
		return leftRotate(node);
	}
	// RL情况
	if (balance < -1 && getBF(node->rightChild) > 0) {
		node->rightChild = rightRotate(node->rightChild);
		return leftRotate(node);
	}

	return node; // 返回（可能已经改变的）子树根节点
}

template<typename T>
void (*(AVL<T>::visit))(avlNode<T>*) = nullptr;

template<typename T>
void AVL<T>::preOrder(avlNode<T>* t)
{
	if (t != nullptr)
	{
		AVL<T>::visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}

template<typename T>
void AVL<T>::inOrder(avlNode<T>* t)
{
	if (t != nullptr)
	{
		inOrder(t->leftChild);
		AVL<T>::visit(t);
		inOrder(t->rightChild);
	}
}

template<typename T>
void AVL<T>::postOrder(avlNode<T>* t)
{
	if (t != nullptr)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		AVL<T>::visit(t);
	}
}
#endif

