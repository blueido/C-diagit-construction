#include "tree.h"

//�������
void binaryTree::createtree()
{
	binaryTree node1 = { 'A',NULL,NULL };
	binaryTree node2 = { 'B',NULL,NULL };
	binaryTree node3 = { 'C',NULL,NULL };
	binaryTree node4 = { 'D',NULL,NULL };
	binaryTree node5 = { 'E',NULL,NULL };
	binaryTree node6 = { 'F',NULL,NULL };
	binaryTree node7 = { 'G',NULL,NULL };
	binaryTree node8 = { 'H',NULL,NULL };

	//��������ϵ
	node1.lchild = &node2;
	node1.rchild = &node6;
	node2.rchild = &node3;
	node3.lchild = &node4;
	node3.rchild = &node5;
	node6.rchild = &node7;
	node7.lchild = &node8;

	////�������
	recursior(&node1);

	////�������
	//midrecursior(&node1);

	//�������
	//lastrecursior(&node1);

	//Ѱ������Ҷ����
	//int num = 0;
	//search(rootnode, &num);
	//cout << num << endl;

	//Ѱ���������
	int deep = depth(&node1);
	//cout << deep << endl;

	//������
	//binaryTree* newtree = copyTree(&node1);
	//recursior(newtree);
	//deletetree(newtree);

	//�������ķǵݹ��ӡ
	treenode td;
	td.NonRecursion(&node1);
}

//������
binaryTree* binaryTree::copyTree(binaryTree* rootnode)
{
	//���������
	if (rootnode == NULL)
	{
		return NULL;
	}

	//����������
	binaryTree* lefttree = copyTree(rootnode->lchild);
	//����������
	binaryTree* righttree = copyTree(rootnode->rchild);

	//�������
	binaryTree* newtree = new binaryTree();
	newtree->data = rootnode->data;  //�����ֵ��������
	newtree->lchild = lefttree;      //����������������
	newtree->rchild = righttree;     //����������������
	return newtree;
}

//�������(�߶�)
int binaryTree::depth(binaryTree* rootnode)
{
	if (rootnode == NULL) //������ײ�Ľ��
	{
		return 0;
	}
	//�������
	int deep = 0;
	//������������
	int deepleft = depth(rootnode->lchild);
	//������������
	int deepright = depth(rootnode->rchild);
	//���Ƚ�
	deep = deepleft > deepright ? deepleft + 1 : deepright + 1;

	return deep;
}

//����
void binaryTree::search(binaryTree* rootnode, int* num)
{
	if (rootnode == NULL) //������ײ�Ľ��
	{
		return;
	}
	if (rootnode->lchild == 0 && rootnode->rchild == 0)
	{
		(*num)++;
	}

	//��������
	search(rootnode->lchild, num);
	//��������
	search(rootnode->rchild, num);
}

//�������
void binaryTree::recursior(binaryTree* rootnode)
{
	if (rootnode == NULL) //������ײ�Ľ��
	{
		return;
	}
	//�������--�ȸ���������
	//�ȸ�
	cout << rootnode->data << " ";
    //��������
	recursior(rootnode->lchild);
	//��������
	recursior(rootnode->rchild);
}

//�������
void binaryTree::midrecursior(binaryTree* rootnode)
{
	//�������--�����ٸ�����
	if (rootnode == NULL)
	{
		return;
	}
	
	//����
	midrecursior(rootnode->lchild);
	//�ٸ�
	cout << rootnode->data << " ";
	//����
	midrecursior(rootnode->rchild);
}

//�������
void binaryTree::lastrecursior(binaryTree* rootnode)
{
	//�������--�����ٸ�����
	if (rootnode == NULL)
	{
		return;
	}

	//����
	lastrecursior(rootnode->lchild);
	//����
	lastrecursior(rootnode->rchild);
	//�ٸ�
	cout << rootnode->data << " ";
}

//������
void binaryTree::deletetree(binaryTree* rootnode)
{
	if (rootnode == NULL)
	{
		return;
	}
	//�ݹ�����������
	deletetree(rootnode->lchild);
	//�ݹ�����������
	deletetree(rootnode->rchild);
	//���ٲ���
	delete rootnode;
}

treenode* PutToStack(binaryTree* root, bool status)
{
	treenode* tnode = new treenode();
	tnode->bt = root;
	tnode->status = status;
	return tnode;
}

void treenode::NonRecursion(binaryTree* root)
{
	//�½�ջ
	listStack ls;
	//��root����tn.bt�����ҽ�tn״̬��ʼ��Ϊfalse
	ls.push((listStackNode*)PutToStack(root, false));
	while (ls.size)
	{
		//�ȵ���ջ��Ԫ��
		treenode* tnode = new treenode();
		tnode = (treenode*)ls.front();
		ls.pop();
		//�жϵ������״̬
		if (tnode->bt == NULL)
		{
			continue;
		}
		if (tnode->status == true)
		{
			cout << tnode->bt->data << " ";
		}
		if (tnode->status == false && tnode->bt != NULL)
		{
			//��������
			tnode->status = true;
			//��ջ--�������������������ͨ���ı���ջ˳����ʵ�ֲ�ͬ�ı�����ʽ�����������ҽ�㣬
			//�������㣬��������㣬����������ʱ����������ȳ���Ȼ���Ǹ���㣬������ҽ�㣬����������������ˡ�
			ls.push((listStackNode*)PutToStack(tnode->bt->rchild, false));  //����ǰ�����ҽ����ջ
			ls.push((listStackNode*)PutToStack(tnode->bt->lchild, false));  //����ǰ����������ջ
			ls.push((listStackNode*)tnode);                                 //�������ջ
		}
	}
}