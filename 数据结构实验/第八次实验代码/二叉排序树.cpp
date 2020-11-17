#include<iostream>
#include<iomanip>

using namespace std;

typedef int TElemType;

typedef struct node
{
	TElemType data;    //结点数据值
	struct  node* lchild, * rchild;   //左右孩子指针
}BSTNode, * BSTree;
BSTree BSTSearch(BSTree root, TElemType x, BSTree& father);    //在以root为根的树中查找元素x，father指向其双亲，返回指向元素x的指针
bool BSTInsert(BSTree& root, TElemType x);   //在以root为根的树中插入元素x
bool BSTRemove(BSTree& root, TElemType x);     // 在以root为根的树中删除元素x
void ShowTree(BSTree ptr);    //以括号的形式显示二叉树
BSTree CreatBSTree();   //创建BS树

//****************************************************************
int main()
{
	BSTree T;
	T = CreatBSTree();
	cout << "创建的树如下：" << endl;
	ShowTree(T);
	int c;
	cout<< endl << "请输入要删除的数据：" << endl;
	cin >> c;
	BSTRemove(T, c);
	cout << "删除该元素后树为：" << endl;
	ShowTree(T);
	cout << endl;
	system("pause");
	return 0;
}
//****************************************************************
BSTree CreatBSTree()
{
	int n, i, num;
	BSTree root;
	root = NULL;
	cout << "请输入初始BS树元素个数：\n";
	cin >> n;
	cout << "请依次输入各个元素：\n";
	for (i = 0; i < n; i++)
	{
		cin >> num;
		BSTInsert(root, num);
	}
	return root;
}
//****************************************************************
BSTree BSTSearch(BSTree root, TElemType x, BSTree& father)
{
	BSTree p = root;
	father = NULL;
	while (p)
	{
		if (x == p->data)
		{
			break;
		}
		else if (x > p->data)
		{
			father = p;
			p = p->rchild;
		}
		else
		{
			father = p;
			p = p->lchild;
		}
	}
	return p;
}
//****************************************************************
bool BSTInsert(BSTree& root, TElemType x)
{
	BSTree p, fa;
	if (BSTSearch(root, x, fa))  //判断元素是否在树中
	{
		cout << "元素" << x << "已在树中" << endl;
		return NULL;
	}
	p = new BSTNode;
	if (!p)
	{
		cout << "空间分配失败";
		exit(0);
	}
	p->data = x;
	p->lchild = NULL;
	p->rchild = NULL;
	if (fa == NULL)   //空树
	{
		root = p;
	}
	else
	{
		if (x < fa->data)
		{
			fa->lchild = p;
		}
		else
		{
			fa->rchild = p;
		}
	}
	return true;
}
//****************************************************************
bool BSTRemove(BSTree& root, TElemType x)
{
	BSTree s, p, fa;
	p = BSTSearch(root, x, fa);
	if (p == NULL)
	{
		cout << "树中不存在元素" << x << endl;
		exit(0);
	}
	if (p->lchild != NULL && p->rchild != NULL)  //有两个子女，找*p的中序前驱*s,也可以找中序后继*s
	{
		s = p->lchild;
		while (s->rchild != NULL)
		{
			fa = s;
			s = s->rchild;
		}
		//此时*s为其中序前驱,*fa为其双亲
		p->data = s->data;  //用其替换,再删s
		p = s;
	}

	if (p->rchild == NULL)   //记下要被删除的结点左子树结点
	{
		s = p->lchild;
	}
	else  //记下右子树结点
	{
		s = p->rchild;    //可能也空
	}

	if (p == root)
	{
		root = s;
	}
	else if(fa->lchild == p)
	{
		fa->lchild = s;
	}
	else
	{
		fa->rchild = s;
	}
	delete p;
	return true;
}
//****************************************************************
void ShowTree(BSTree ptr)    //以括号的形式显示二叉树
{
	BSTree p;
	if (ptr)
	{
		cout << ptr->data;   //打印根节点
		if (ptr->lchild || ptr->rchild)
		{
			cout << "(";
			if (ptr->lchild)
			{
				ShowTree(ptr->lchild);
			}
			cout << ",";
			if (ptr->rchild)
			{
				ShowTree(ptr->rchild);
			}
			cout << ")";
		}
	}
}