#define _CRT_SECURE_NO_WARNINGS 1
#ifndef __BTREE_H__
#define __BTREE_H__

#include <iostream>
using namespace std;
#include<queue>

size_t size = 0;
template <class T>
struct BinaryTreeNode
{
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	T _data;

	BinaryTreeNode(const T& x)
		:_left(NULL)
		, _right(NULL)
		, _data(x)
	{}
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;

public:
	BinaryTree()
		:_root(NULL)
	{}

	BinaryTree(const T* a, size_t size, const T& invalid)//1 2 3 # # 4 # # 5 6
		:_root(NULL)
	{
		size_t index = 0;
		_root = _CreatTree(a, size, index, invalid);
	}

	BinaryTree(const BinaryTree<T>& t)
	{
		_root = _Copy(t._root);
	}

	//�ִ�д��
	/*BinaryTree<T>& operator=(BinaryTree<T> t)
	{
		swap(_root, t._root);

		return *this;
	}*/

	//��ͳд��
	BinaryTree<T>& operator=(const BinaryTree<T>& t)
	{
		_Destroy(_root);

		_root = _Copy(t._root);

		return *this;
	}

	~BinaryTree()
	{
		_Destroy(_root);
	}

	void PrevOrder()
	{
		_PrevOrder(_root);
		cout << endl;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void PostOrder()
	{
		_PostOrder(_root);
		cout << endl;
	}

	void LevelOrder()
	{
		queue<Node*> q;
		q.push(_root);

		while (!q.empty())
		{
			if (q.front()->_left != NULL)
			{
				q.push(q.front()->_left);
			}
			if (q.front()->_right != NULL)
			{
				q.push(q.front()->_right);
			}
			cout << q.front()->_data <<" ";
			q.pop();
		}
		cout << endl;
	}

	size_t Size()
	{
		return _Size(_root);
	}

	size_t Depth()
	{
		return _Depth(_root);
	}

	size_t LeafSize()
	{
		size_t size = 0;
		return _LeafSize(_root,size);
	}

protected:
	void _Destroy(Node* root)
	{
		if (root == NULL)
			return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
		return;
	}

	//����һ
	/*size_t _LeafSize(Node* root)
	{
		static size_t size;
		if (root == NULL)
			return 0;

		if (root->_left == NULL && root->_right == NULL)
		{
			size++;
			return size;
		}

		_LeafSize(root->_left);
		_LeafSize(root->_right);

		return size;
	}*/
	//������ ȫ�ֱ�����
	/*size_t _LeafSize(Node* root)
	{
		if (root == NULL)
			return 0;

		if (root->_left == NULL && root->_right == NULL)
		{
			size++;
			return size;
		}

		_LeafSize(root->_left);
		_LeafSize(root->_right);

		return size;
	}*/
	//������ �������� ���� û���̰߳�ȫ���⣬���ݶ����ڵ�����ջ�ڣ��������ַ������������ݶ�->����ʹ��
	size_t _LeafSize(Node* root,size_t& size)
	{
		if (root == NULL)
		return 0;

		if (root->_left == NULL && root->_right == NULL)
		{
		size++;
		return size;
		}

		_LeafSize(root->_left,size);
		_LeafSize(root->_right,size);

		return size;
	}

	Node* _Copy(Node* root)
	{
		Node* Copyroot = NULL;
		if (root != NULL)
		{
			Copyroot = new Node(root->_data);
			Copyroot->_left = _Copy(root->_left);
			Copyroot->_right = _Copy(root->_right);
		}
		
		return Copyroot;
	}

	size_t _Depth(Node* root)
	{
		if (root == NULL)
			return 0;

		size_t leftDepth = _Depth(root->_left);
		size_t rightDepth = _Depth(root->_right);

		return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
	}

	size_t _Size(Node* root)
	{
		if (root == NULL)
			return 0;

		return _Size(root->_left) + _Size(root->_right) + 1;
	}


	void _PostOrder(Node* root)
	{
		if (root == NULL)
			return;

		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
		cout << root->_data << " ";
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;

		_PrevOrder(root->_left);
		cout << root->_data << " ";
		_PrevOrder(root->_right);
	}

	void _PrevOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	Node* _CreatTree(const T* a, size_t size, size_t& index, const T& invalid)
	{
		Node* root = NULL;
		if (index < size && a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = _CreatTree(a, size, ++index, invalid);
			root->_right = _CreatTree(a, size, ++index, invalid);
		}

		return root;
	}
protected:
	Node* _root;
};

void test()
{
	int a1[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int a2[10] = { 4, 5, 6, '#', '#', 7, '#', '#', 8, 9 };
	BinaryTree<int> t1(a1, 10, '#');
	t1.PrevOrder();
	t1.InOrder();
	t1.PostOrder();
	cout<<t1.Size()<<endl;
	cout << t1.Depth() << endl;
	cout << t1.LeafSize() << endl;
	t1.LevelOrder();
	BinaryTree<int> t2 = t1;
	t2.PrevOrder();
	BinaryTree<int> t3(a2, 10, '#');
	t3 = t2;
	t3.PrevOrder();
}

int main()
{
	test();
	system("pause");
	return 0;
}

#endif