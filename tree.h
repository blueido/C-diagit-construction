#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "listStack.h"

using namespace std;

class binaryTree
{
public:

	//��������ϵ
	void createtree();

	//�������(�߶�)
	int depth(binaryTree* rootnode);

	//������
	binaryTree* copyTree(binaryTree* rootnode);

	//����
	void search(binaryTree* rootnode, int* num);

	//�������
	void recursior(binaryTree* rootnode);

	//�������
	void midrecursior(binaryTree* rootnode);

	//�������
	void lastrecursior(binaryTree* rootnode);

	//������
	void deletetree(binaryTree* rootnode);

	char data;
	binaryTree* lchild;  //���ӽ��
	binaryTree* rchild;  //���ӽ��
};

class treenode
{
public:
	//����
	void NonRecursion(binaryTree* root);

	listStackNode node;
	binaryTree* bt;
	bool status;
};