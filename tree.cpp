#include "tree.h"

//创建结点
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

	//创建结点关系
	node1.lchild = &node2;
	node1.rchild = &node6;
	node2.rchild = &node3;
	node3.lchild = &node4;
	node3.rchild = &node5;
	node6.rchild = &node7;
	node7.lchild = &node8;

	////先序遍历
	recursior(&node1);

	////中序遍历
	//midrecursior(&node1);

	//后序遍历
	//lastrecursior(&node1);

	//寻找树的叶子数
	//int num = 0;
	//search(rootnode, &num);
	//cout << num << endl;

	//寻找树的深度
	int deep = depth(&node1);
	//cout << deep << endl;

	//拷贝树
	//binaryTree* newtree = copyTree(&node1);
	//recursior(newtree);
	//deletetree(newtree);

	//二叉树的非递归打印
	treenode td;
	td.NonRecursion(&node1);
}

//拷贝树
binaryTree* binaryTree::copyTree(binaryTree* rootnode)
{
	//拷贝根结点
	if (rootnode == NULL)
	{
		return NULL;
	}

	//拷贝左子树
	binaryTree* lefttree = copyTree(rootnode->lchild);
	//拷贝右子树
	binaryTree* righttree = copyTree(rootnode->rchild);

	//创建结点
	binaryTree* newtree = new binaryTree();
	newtree->data = rootnode->data;  //将结点值赋给新树
	newtree->lchild = lefttree;      //将左子树赋给新树
	newtree->rchild = righttree;     //将右子树赋给新树
	return newtree;
}

//树的深度(高度)
int binaryTree::depth(binaryTree* rootnode)
{
	if (rootnode == NULL) //到达最底层的结点
	{
		return 0;
	}
	//先序遍历
	int deep = 0;
	//先求左子树高
	int deepleft = depth(rootnode->lchild);
	//再求右子树高
	int deepright = depth(rootnode->rchild);
	//做比较
	deep = deepleft > deepright ? deepleft + 1 : deepright + 1;

	return deep;
}

//遍历
void binaryTree::search(binaryTree* rootnode, int* num)
{
	if (rootnode == NULL) //到达最底层的结点
	{
		return;
	}
	if (rootnode->lchild == 0 && rootnode->rchild == 0)
	{
		(*num)++;
	}

	//再左子树
	search(rootnode->lchild, num);
	//再右子树
	search(rootnode->rchild, num);
}

//先序遍历
void binaryTree::recursior(binaryTree* rootnode)
{
	if (rootnode == NULL) //到达最底层的结点
	{
		return;
	}
	//先序遍历--先根后左再右
	//先根
	cout << rootnode->data << " ";
    //再左子树
	recursior(rootnode->lchild);
	//再右子树
	recursior(rootnode->rchild);
}

//中序遍历
void binaryTree::midrecursior(binaryTree* rootnode)
{
	//中序遍历--先左再根再右
	if (rootnode == NULL)
	{
		return;
	}
	
	//先左
	midrecursior(rootnode->lchild);
	//再根
	cout << rootnode->data << " ";
	//再右
	midrecursior(rootnode->rchild);
}

//后序遍历
void binaryTree::lastrecursior(binaryTree* rootnode)
{
	//中序遍历--先左再根再右
	if (rootnode == NULL)
	{
		return;
	}

	//先左
	lastrecursior(rootnode->lchild);
	//再右
	lastrecursior(rootnode->rchild);
	//再根
	cout << rootnode->data << " ";
}

//销毁树
void binaryTree::deletetree(binaryTree* rootnode)
{
	if (rootnode == NULL)
	{
		return;
	}
	//递归销毁左子树
	deletetree(rootnode->lchild);
	//递归销毁右子树
	deletetree(rootnode->rchild);
	//销毁操作
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
	//新建栈
	listStack ls;
	//将root赋给tn.bt，并且将tn状态初始化为false
	ls.push((listStackNode*)PutToStack(root, false));
	while (ls.size)
	{
		//先弹出栈顶元素
		treenode* tnode = new treenode();
		tnode = (treenode*)ls.front();
		ls.pop();
		//判断弹出结点状态
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
			//根结点更新
			tnode->status = true;
			//入栈--这种是先序遍历，可以通过改变入栈顺序来实现不同的遍历方式，比如先入右结点，
			//再入根结点，最后入左结点，这样弹出的时候就是左结点先出，然后是根结点，最后是右结点，这样就是中序遍历了。
			ls.push((listStackNode*)PutToStack(tnode->bt->rchild, false));  //将当前结点的右结点入栈
			ls.push((listStackNode*)PutToStack(tnode->bt->lchild, false));  //将当前结点的左结点入栈
			ls.push((listStackNode*)tnode);                                 //根结点入栈
		}
	}
}