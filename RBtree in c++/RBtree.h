#pragma once
//Made by Huamai_Solis in 2024/10/15

#ifndef _RBTREE
#define _RBTREE

#include <iostream>
#include "_exceptions.h"
using namespace std;
enum colorType { BLACK, RED };
enum RotationType { //����������Ҫ��ת����� ����r��ֻ���ɫ b������Ҫ����LL/LR/RL/RR������ת�Ȳ���
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
	colorType color;
	bool DOUBLEBLACK;
	RBnode<T>* leftChild;
	RBnode<T>* rightChild;
	RBnode<T>* parent;
	RBnode(T theElement, colorType theColor)
	{//�ⲿ�ڵ���nullptr��ʾ
		element = theElement; color = theColor; DOUBLEBLACK = false;
		leftChild = rightChild = parent = nullptr;
	}
};

template<typename T>
class RBtree
{
private:
	RBnode<T>* root;
	int treeSize;
	colorType getColor(RBnode<T>* node)
	{
		return node ? node->color : BLACK;
	}
	RBnode<T>* leftRotateWithColor(RBnode<T>* node);
	RBnode<T>* leftRotate(RBnode<T>* node);
	RBnode<T>* rightRotateWithColor(RBnode<T>* node);
	RBnode<T>* rightRotate(RBnode<T>* node);
	RBnode<T>* findSuccessor(RBnode<T>* node);
	RBnode<T>* insert(RBnode<T>* node, T theElement);
	RotationType figureSituation(RBnode<T>* node);
	void fixDoubleBlack(RBnode<T>* node);
	RBnode<T>* erase(RBnode<T>* node, T theElement);
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
	RBtree() { root = new RBnode<T>(nullptr, BLACK); }
	RBtree(T theElement) { root = new RBnode<T>(theElement, BLACK); treeSize = 1; }
	void insert(T theElement) { root = insert(root, theElement); }	//�û�ʹ�����
	void erase(T theElement) { erase(root, theElement); }//�û�ʹ�����
	void preOrder(void(*theVisit)(RBnode<T>*)) { visit = theVisit; preOrder(root); }
	void preOrderOutput() { preOrder(output); cout << endl; }
	void inOrder(void(*theVisit)(RBnode<T>*)) { visit = theVisit; inOrder(root); }
	void inOrderOutput() { inOrder(output); cout << endl; }
	void postOrder(void(*theVisit)(RBnode<T>*)) { visit = theVisit; postOrder(root); }
	void postOrderOutput() { postOrder(output); cout << endl; }
};

template<typename T>
RotationType RBtree<T>::figureSituation(RBnode<T>* Gnode)
{

	RBnode<T>* LChild = Gnode->leftChild, * RChild = Gnode->rightChild;
	if (LChild != nullptr && getColor(LChild) == RED)
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

	if (RChild != nullptr && getColor(RChild) == RED)
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
RBnode<T>* RBtree<T>::leftRotateWithColor(RBnode<T>* GNode)
{
	RBnode<T>* PNode = GNode->rightChild;
	GNode->rightChild = PNode->leftChild;

	if (PNode->leftChild != nullptr) {
		PNode->leftChild->parent = GNode; // �������������� parent ָ��
	}

	PNode->parent = GNode->parent; // ���� PNode �� parent ָ��
	if (GNode->parent == nullptr) {
		root = PNode; // ���� root
	}
	else if (GNode == GNode->parent->leftChild) {
		GNode->parent->leftChild = PNode; // ���¸��ڵ��������
	}
	else {
		GNode->parent->rightChild = PNode; // ���¸��ڵ��������
	}

	PNode->leftChild = GNode;
	GNode->parent = PNode; // ���� GNode �� parent ָ��
	PNode->color = BLACK;
	GNode->color = RED;
	return PNode;
}template<typename T>
RBnode<T>* RBtree<T>::leftRotate(RBnode<T>* GNode)
{
	RBnode<T>* PNode = GNode->rightChild;
	GNode->rightChild = PNode->leftChild;

	if (PNode->leftChild != nullptr) {
		PNode->leftChild->parent = GNode; // �������������� parent ָ��
	}

	PNode->parent = GNode->parent; // ���� PNode �� parent ָ��
	if (GNode->parent == nullptr) {
		root = PNode; // ���� root
	}
	else if (GNode == GNode->parent->leftChild) {
		GNode->parent->leftChild = PNode; // ���¸��ڵ��������
	}
	else {
		GNode->parent->rightChild = PNode; // ���¸��ڵ��������
	}

	PNode->leftChild = GNode;
	GNode->parent = PNode; // ���� GNode �� parent ָ��

	return PNode;
}

template<typename T>
RBnode<T>* RBtree<T>::rightRotateWithColor(RBnode<T>* GNode)
{
	RBnode<T>* PNode = GNode->leftChild;
	GNode->leftChild = PNode->rightChild;

	if (PNode->rightChild != nullptr) {
		PNode->rightChild->parent = GNode; // �������������� parent ָ��
	}

	PNode->parent = GNode->parent; // ���� PNode �� parent ָ��
	if (GNode->parent == nullptr) {
		root = PNode; // ���� root
	}
	else if (GNode == GNode->parent->leftChild) {
		GNode->parent->leftChild = PNode; // ���¸��ڵ��������
	}
	else {
		GNode->parent->rightChild = PNode; // ���¸��ڵ��������
	}
	PNode->rightChild = GNode;
	GNode->parent = PNode; // ���� GNode �� parent ָ��
	PNode->color = BLACK;
	GNode->color = RED;
	return PNode;
}template<typename T>
RBnode<T>* RBtree<T>::rightRotate(RBnode<T>* GNode)
{
	RBnode<T>* PNode = GNode->leftChild;
	GNode->leftChild = PNode->rightChild;

	if (PNode->rightChild != nullptr) {
		PNode->rightChild->parent = GNode; // �������������� parent ָ��
	}

	PNode->parent = GNode->parent; // ���� PNode �� parent ָ��
	if (GNode->parent == nullptr) {
		root = PNode; // ���� root
	}
	else if (GNode == GNode->parent->leftChild) {
		GNode->parent->leftChild = PNode; // ���¸��ڵ��������
	}
	else {
		GNode->parent->rightChild = PNode; // ���¸��ڵ��������
	}
	PNode->rightChild = GNode;
	GNode->parent = PNode; // ���� GNode �� parent ָ��
	return PNode;
}


template<typename T>
RBnode<T>* RBtree<T>::insert(RBnode<T>* node, T theElement)
{
	if (node == nullptr)
	{
		treeSize++;
		return new RBnode<T>(theElement, RED);
	}
	if (theElement < node->element)
	{
		node->leftChild = insert(node->leftChild, theElement);
		node->leftChild->parent = node; // ���� parent ָ��
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
void (*(RBtree<T>::visit))(RBnode<T>*) = nullptr;

template<typename T>
void RBtree<T>::preOrder(RBnode<T>* t)
{
	if (t != nullptr)
	{
		RBtree<T>::visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}

template<typename T>
void RBtree<T>::inOrder(RBnode<T>* t)
{
	if (t != nullptr)
	{
		inOrder(t->leftChild);
		RBtree<T>::visit(t);
		inOrder(t->rightChild);
	}
}

template<typename T>
void RBtree<T>::postOrder(RBnode<T>* t)
{
	if (t != nullptr)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		RBtree<T>::visit(t);
	}
}
template<typename T>//�������û���õ�
RBnode<T>* RBtree<T>::findSuccessor(RBnode<T>* node)
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
RBnode<T>* RBtree<T>::erase(RBnode<T>* node, T theElement) {
	// �ҵ���Ҫɾ���Ľڵ�
	RBnode<T>* p = node;
	while (p->element != theElement)
	{
		if (p == nullptr)
		{//û�ҵ�
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
	//�ҵ���//������Ѱ��ǰ�ýڵ�
	RBnode<T>* Deletion = p->rightChild;

	if (Deletion != nullptr) {
		while (Deletion->leftChild != nullptr)
			Deletion = Deletion->leftChild;
	}
	else {
		Deletion = p;
	}
	p->element = Deletion->element;

	//��ʱdeletionҪôֻ��һ������,Ҫôû�к���
	if (Deletion->leftChild != nullptr)//���Ӳ�Ϊ��,�������
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
	else if (Deletion->rightChild != nullptr)//�Һ��Ӳ�Ϊ��,�������
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
	else {//û�к���
		if (getColor(Deletion) == RED)//ɾ�����������
		{
		}
		else {//Deletion��ɫ�Ǻڵ� //��ʱ��ʼ����˫��
			Deletion->DOUBLEBLACK = true;
			RBnode<T>* Parent = Deletion->parent;
			RBnode<T>* Sibling = nullptr;
			if (Parent->leftChild == Deletion)Sibling = Parent->rightChild;
			else Sibling = Parent->leftChild;
			if (getColor(Sibling) == BLACK)//�ֵ��Ǻ�ɫ��һ������(��ΪDeletion��������ɫ�Ǻ�ɫ��
			{//������һ���캢��
				if (Parent->leftChild == Sibling)
				{
					if (getColor(Sibling->leftChild) == RED)
					{//LL��
						Sibling->leftChild->color = Sibling->color;
						Sibling->color = Parent->color;
						Parent->color = BLACK;
						rightRotate(Parent);
						Deletion->DOUBLEBLACK = false;
					}
					else if (getColor(Sibling->rightChild) == RED)
					{//LR��
						Sibling->rightChild->color = Parent->color;
						Parent->color = BLACK;
						leftRotate(Sibling);
						rightRotate(Parent);
						Deletion->DOUBLEBLACK = false;
					}
					else//˫���Ӷ��Ǻ�ɫ(�����ⲿ�ڵ�
					{
						Sibling->color = RED;
						Deletion->DOUBLEBLACK = false;
						//˫������
						if (Parent->color == RED)Parent->color = BLACK;
						else {//���ڵ��Ǻ�ɫ,��Ϊ˫��
							Parent->DOUBLEBLACK = true;
							//��������˫��
							fixDoubleBlack(Parent);
						}
					}
				}
				if (Parent->rightChild == Sibling)
				{
					if (getColor(Sibling->rightChild) == RED)
					{//RR��
						Sibling->rightChild->color = Sibling->color;
						Sibling->color = Parent->color;
						Parent->color = BLACK;
						leftRotate(Parent);
						Deletion->DOUBLEBLACK = false;
					}
					else if (getColor(Sibling->leftChild) == RED)
					{//RL��
						Sibling->leftChild->color = Parent->color;
						Parent->color = BLACK;
						rightRotate(Sibling);
						leftRotate(Parent);
						Deletion->DOUBLEBLACK = false;
					}
					else//˫���Ӷ��Ǻ�ɫ(�����ⲿ�ڵ�
					{
						Sibling->color = RED;
						Deletion->DOUBLEBLACK = false;
						//˫������
						if (Parent->color == RED)Parent->color = BLACK;
						else {//���ڵ��Ǻ�ɫ,��Ϊ˫��
							Parent->DOUBLEBLACK = true;
							//��������˫��
							fixDoubleBlack(Parent);
						}
					}
				}
			}
			else//�ֵܽڵ��Ǻ�ɫ��
			{
				colorType temp = Parent->color;
				Parent->color = Sibling->color;
				Sibling->color = temp;
				//��˫�ڽڵ���ת
				if (Parent->leftChild == Sibling)
					rightRotate(Parent);
				else
					leftRotate(Parent);
				fixDoubleBlack(Deletion);
			}
		}
	}
	//ִ��delete����֮ǰ,��Ҫ��delete��λ�����ó�nullptr
	if (Deletion == Deletion->parent->leftChild)
		Deletion->parent->leftChild = nullptr;
	else
		Deletion->parent->rightChild = nullptr;

	delete Deletion;
	return nullptr;
}

template<typename T>
void RBtree<T>::fixDoubleBlack(RBnode<T>* node) {
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

	if (getColor(Sibling) == BLACK)
	{
		if (Parent->leftChild == Sibling)
		{
			if (getColor(Sibling->leftChild) == RED)
			{
				Sibling->leftChild->color = Sibling->color;
				Sibling->color = Parent->color;
				Parent->color = BLACK;
				rightRotate(Parent);
				node->DOUBLEBLACK = false;
			}
			else if (getColor(Sibling->rightChild) == RED)
			{
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
			{
				Sibling->rightChild->color = Sibling->color;
				Sibling->color = Parent->color;
				Parent->color = BLACK;
				leftRotate(Parent);
				node->DOUBLEBLACK = false;
			}
			else if (getColor(Sibling->leftChild) == RED)
			{
				Sibling->leftChild->color = Parent->color;
				Parent->color = BLACK;
				rightRotate(Sibling);
				leftRotate(Parent);
				node->DOUBLEBLACK = false;
			}
		}
		else
		{
			Sibling->color = RED;
			node->DOUBLEBLACK = false;
			if (Parent->color == RED)Parent->color = BLACK;
			else {
				Parent->DOUBLEBLACK = true;
				fixDoubleBlack(Parent);
			}
		}
	}
}
#endif