#include<iostream>
#include<iomanip>

using namespace std;

typedef int DataType;  //结点关键码的数据类型
#define StackSize 40       //预定义栈大小
typedef struct node
{
	DataType data;      //结点的数据值
	int bf;             //平衡因子
	struct node* lchild, * rchild;     //指向左、右孩子结点的指针
}AVLNode,*AVLTree;

void Rotate_LL(AVLTree& ptr);
void Rotate_RR(AVLTree& ptr);
void Rotate_LR(AVLTree& ptr);
void Rotate_RL(AVLTree& ptr);
AVLTree CreatAVLTree(int n);    //创建具有n的结点的AVL树
AVLTree AVLSearch(AVLTree ptr, DataType x);   //在以ptr为根的AVL树中查找元素x
bool AVLInsert(AVLTree& ptr, DataType& x);   //在以ptr为根的AVL树中插入新元素x，插入成则返回true，否则返回false
bool AVLRemove(AVLTree& ptr, DataType x);    //在以ptr为根的AVL树中删除元素x，删除成则返回true，否则返回false
void ShowTree(AVLTree ptr);   //以括号形式显示树


int main()
{
	int n;
	AVLTree ptr, p;
	cout << "请输入AVL树初始的元素个数：";
	cin >> n;
	ptr = CreatAVLTree(n);
	cout << "创建的树如下：" << endl;
	ShowTree(ptr);
	cout << endl << "请输入要查找的元素：";
	cin >> n;
	p = AVLSearch(ptr, n);
	if (p != NULL)
	{
		cout << "元素 " << n << " 在AVL树中" << endl;
	}
	else
	{
		cout << "元素 " << n << " 不在AVL树中" << endl;
	}
	cout << endl << "请输入要查找的元素：";
	cin >> n;
	p = AVLSearch(ptr, n);
	if (p != NULL)
	{
		cout << "元素 " << n << " 在AVL树中" << endl;
	}
	else
	{
		cout << "元素 " << n << " 不在AVL树中" << endl;
	}
	cout << endl << "请输入要插入的元素：";
	cin >> n;
	AVLInsert(ptr, n);
	cout << "插入后的树为：" << endl;
	ShowTree(ptr);
	cout << endl << "请输入要删除的元素：";
	cin >> n;
	AVLRemove(ptr, n);
	cout << "删除后的树为：" << endl;
	ShowTree(ptr);
	cout << endl;
	system("pause");
	return 0;
}
//****************************************************************
bool AVLInsert(AVLTree& ptr, DataType& x)
{
	if (ptr == NULL) //当前AVL树为空
	{
		ptr = (AVLTree)malloc(sizeof(AVLNode));  //创建新结点
		if (!ptr)
		{
			cout << "空间分配失败";
			exit(0);
		}
		ptr->data = x;
		ptr->lchild = NULL;
		ptr->rchild = NULL;
		ptr->bf = 0;
		return true;
	}
	AVLTree pr = NULL, p = ptr, q;
	int d;
	AVLTree S[StackSize];
	int top = -1;   //栈顶指针
	S[++top] = NULL;
	while (p != NULL)   //寻找插入位置
	{
		if (x == p->data)   //树中找到x，不插入
		{
			cout << "元素" << x << "已在树中" << endl;
			return false;
		}
		S[++top] = p;     //否则用栈记录查找路径
		p = (x < p->data) ? p->lchild : p->rchild;   //向下层继续查找
	}

	p = (AVLTree)malloc(sizeof(AVLNode));     //创建新结点
	if (!p)
	{
		cout << "空间分配失败";
		exit(0);
	}
	p->data = x;
	p->bf = 0;
	p->lchild = NULL;
	p->rchild = NULL;

	if (S[top] == NULL)   //空树，新节点成为根
	{
		ptr = p;
	}
	else if (x < S[top]->data)   //新结点插入到双亲下
	{
		S[top]->lchild = p;
	}
	else
	{
		S[top]->rchild = p;
	}

	while (top > 0)   //重新平衡化
	{
		pr = S[top--];    //从栈中退出双亲结点
		if (p == pr->lchild)
		{
			pr->bf++;     //调整双亲的平衡因子
		}
		else
		{
			pr->bf--;
		}

		if (pr->bf == 0)   //情形1，直接平衡退出
		{
			break;
		}
		if (pr->bf == 1 || pr->bf == -1)   //情形2，|bf| = 1
		{
			p = pr;
		}
		else                             //情形3，|bf| = 2
		{
			d = (pr->bf < 0) ? -1 : 1;      //区别单双旋转标志
			if (p->bf == d)     
			{ //两结点bf同号，单旋转
				if (d == 1)
				{
					Rotate_LL(pr);     //LL单旋转
				}
				else
				{
					Rotate_RR(pr);  //RR单旋转
				}
			}
			else
			{
				if (d == 1)
				{
					Rotate_LR(pr);     //LR双旋转
				}
				else
				{
					Rotate_RL(pr);     //RL双旋转
				}
			}
			break;
		}
	}
	if (top == 0)
	{
		ptr = pr;   //根节点
	}
	else   //中间重新链接
	{
		q = S[top--];
		if (q->data > pr->data)
		{
			q->lchild = pr;
		}
		else
		{
			q->rchild = pr;
		}
	}
	return true;
}
//****************************************************************
void Rotate_LL(AVLTree &ptr)
{
	AVLTree subR = ptr;     //要右旋转的结点
	ptr = subR->lchild;     //卸掉ptr右边的负载
	subR->lchild = ptr->rchild;  //卸掉ptr右边的负载
	ptr->rchild = subR;          //右单旋，ptr成为新根
	ptr->bf = 0;
	subR->bf = 0;
}
//****************************************************************
void Rotate_RR(AVLTree &ptr)
{
	AVLTree subL = ptr;
	ptr = subL->rchild;
	subL->rchild = ptr->lchild;     //卸掉ptr左边的负载
	ptr->lchild = subL;
	ptr->bf = 0;           //左单旋，ptr成为新根
	subL->bf = 0;
}
//****************************************************************
void Rotate_LR(AVLTree &ptr)
{
	AVLTree subR = ptr, subL = subR->lchild;
	ptr = subL->rchild;
	subL->rchild = ptr->lchild;
	ptr->lchild = subL;   //卸掉ptr左边的负载
	subR->lchild = ptr->rchild;
	ptr->rchild = subR;   //卸掉ptr右边的负载
	if (ptr->bf == 1)  //原ptr左子树高
	{
		subL->bf = 0;
		subR->bf = -1;
	}
	else if(ptr->bf == -1)  //原ptr右子树高
	{   
		subL->bf = 1;
		subR->bf = 0;
	}
	else   //原ptr两子树同高
	{
		subL->bf = 0;
		subR->bf = 0;
	}
	ptr->bf = 0;
}
//****************************************************************
void Rotate_RL(AVLTree &ptr)
{
	AVLTree subL = ptr, subR = subL->rchild;
	ptr = subR->lchild;     //ptr成为新根
	subR->lchild = ptr->rchild;
	ptr->rchild = subR;    //卸掉ptr右边的负载
	subL->rchild = ptr->lchild;
	ptr->lchild = subL;    //卸掉ptr左边的负载
	if (ptr->bf == 1)   //原ptr的左子树高
	{
		subL->bf = 0;
		subR->bf = -1;
	}
	else if (ptr->bf == -1)  //原Ptr右子树高
	{
		subL->bf = 1;
		subR->bf = 0;
	}
	else   //同高
	{
		subL->bf = 0;
		subR->bf = 0;
	}
	ptr->bf = 0;
}
//****************************************************************
bool AVLRemove(AVLTree& ptr, DataType x)
{
	AVLTree pr = NULL, p = ptr, q, gr = NULL;
	int d, dd = 0;
	AVLTree S[StackSize];
	int top = -1;
	while (p != NULL)   //寻找被删除结点
	{
		if (x == p->data)    //找到则停止查找
		{
			break;
		}    
		//否则用栈记录查找路径
		pr = p;
		S[++top] = pr;
		p = (x < p->data) ? p->lchild : p->rchild;
	}
	if (p == NULL)
	{
		cout << "未找到元素为" << x << "的结点" << endl;
		return false;
	}
	if (p->lchild != NULL && p->rchild != NULL)
	{
		pr = p;
		S[++top] = pr;    //被删结点有两个孩子
		q = p->lchild;    //在p的左子树找p的直接前驱
		while (q->rchild != NULL)
		{
			pr = q;
			S[++top] = pr;   
			q = q->rchild;
		}
		p->data = q->data;    //用q的值填补p
		p = q;   //被删结点转换为q
	}

	if (p->lchild != NULL)
	{
		q = p->lchild;      //被删结点p只有一个孩子q
	}
	else
	{
		q = p->rchild;
	}
	if (pr == NULL)
	{
		ptr = q;     //被删结点为根结点
	}
	else
	{
		if (pr->lchild == p)
		{
			pr->lchild = q;    //链接
		}
		else
		{
			pr->rchild = q;
		}
	}
	while (top > -1)      //重新平衡化
	{
		pr = S[top--];    //从栈中退出双亲结点pr
		if (pr->lchild == q)   //调整pr的平衡因子
		{
			pr->bf--;
		}
		else
		{
			pr->bf++;
		}
		if (top > -1)
		{
			gr = S[top];     //从栈中取出祖父结点gr
			dd = (gr->lchild == pr) ? 1 : -1;    //旋转后与上层链接
		}
		else
		{
			dd = 0;    //栈空，旋转后不与上层链接
		}
		if (pr->bf == 1 || pr->bf == -1)   //未失去平衡，不再调整
		{
			break;
		}
		if (pr->bf != 0)   //  |bf| = 2,失去平衡
		{
			if (pr->bf == 2)    //左高
			{
				d = 1;
				q = pr->lchild;
			}
			else             //右高
			{
				d = -1;
				q = pr->rchild;
			}
			if (q->bf == 0)          //pr较高子树q的bf为0
			{
				if (d == 1)
				{
					Rotate_LL(pr);
					pr->bf = -1;
					pr->rchild->bf = 1;
				}
				else
				{
					Rotate_RR(pr);
					pr->bf = 1;
					pr->lchild->bf = -1;
				}
				break;
			}
			if (q->bf == d)      //两结点的平衡因子同号
			{
				if (d == 1)
				{
					Rotate_LL(pr);   //LL单旋转
				}
				else
				{
					Rotate_RR(pr);   //RR单旋转
				}
			}
			else                //两结点的平衡因子异号
			{
				if (d == 1)
				{
					Rotate_LR(pr);      //LR双旋转
				}
				else
				{
					Rotate_RL(pr);    //RL双旋转
				}
			}
			if (dd == 1)
			{
				gr->lchild = pr;
			}
			else if (dd == -1)
			{
				gr->rchild = pr;              //旋转后新根与上层链接
			}
		}
		q = pr;
	}
	if (top == -1)
	{
		ptr = pr;     //调整到树的根节点
	}
	free(p);
	return true;
}
//****************************************************************
AVLTree AVLSearch(AVLTree ptr, DataType x)
{
	if (!ptr)
	{
		return NULL;  //查找不成功
	}
	else if (ptr->data == x)
	{
		return ptr;
	}
	else if (ptr->data < x)
	{
		return AVLSearch(ptr->rchild, x);
	}
	else
	{
		return AVLSearch(ptr->lchild, x);
	}
}
//****************************************************************
AVLTree CreatAVLTree(int n)
{
	AVLTree T = NULL;    //表示要创建的树的根节点
	DataType key;
	int i;
	cout << "请依次输入AVL树的元素（空格隔开）：" << endl;
	for (i = 0; i < n; i++)
	{
		cin >> key;
		AVLInsert(T, key);
	}
	return T;
}
//****************************************************************
void ShowTree(AVLTree ptr)    //以括号的形式显示二叉树
{
	AVLTree p;
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
//****************************************************************