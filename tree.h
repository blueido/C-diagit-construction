#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "listStack.h"

using namespace std;

class binaryTree
{
public:

	//创建结点关系
	void createtree();

	//树的深度(高度)
	int depth(binaryTree* rootnode);

	//拷贝树
	binaryTree* copyTree(binaryTree* rootnode);

	//遍历
	void search(binaryTree* rootnode, int* num);

	//先序遍历
	void recursior(binaryTree* rootnode);

	//中序遍历
	void midrecursior(binaryTree* rootnode);

	//后序遍历
	void lastrecursior(binaryTree* rootnode);

	//销毁树
	void deletetree(binaryTree* rootnode);

	char data;
	binaryTree* lchild;  //左子结点
	binaryTree* rchild;  //右子结点
};

class treenode
{
public:
	//遍历
	void NonRecursion(binaryTree* root);

	listStackNode node;
	binaryTree* bt;
	bool status;
};