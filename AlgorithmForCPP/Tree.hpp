#pragma once
#include <iostream>
#include <vector>
#include <math.h>
template<typename T>
class TreeNode {
public:
	T data;
	TreeNode<T>* left, * right;
public:
	TreeNode(T val);
};

template<typename T>
class BinaryTree {
private:
	TreeNode<T>* root;	//���ڵ�
	void postDelete(TreeNode<T>* root);
public:
	BinaryTree();
	~BinaryTree();
	void add(T val);
	void pre(TreeNode<T>* root, std::vector<T> &list);
	void mid(TreeNode<T>* root, std::vector<T>& list);
	void post(TreeNode<T>* root, std::vector<T>& list);
	std::vector<T> preTraverse();//ǰ�����
	std::vector<T> midTraverse();//�������
	std::vector<T> postTraverse();//�������
	size_t deep(TreeNode<T>* root);//������
	void remove(T val);	//ɾ���ڵ�
};

template<typename T>
inline TreeNode<T>::TreeNode(T val):data(val),left(nullptr),right(nullptr)
{
}

template<typename T>
inline BinaryTree<T>::BinaryTree():root(nullptr)
{
}

template<typename T>
inline void BinaryTree<T>::add(T val)
{
	if (this->root == nullptr) {
		this->root = new TreeNode<T>(val);
		return;
	}
	TreeNode<T>* cur = root;
	while (true) {
		if (val > cur->data) {
			if (cur->right != nullptr) {
				cur = cur->right;
			}
			else {
				cur->right = new TreeNode<T>(val);
				return;
			}
		}
		else if (val < cur->data) {
			if (cur->left != nullptr) {
				cur = cur->left;
			}
			else {
				cur->left = new TreeNode<T>(val);
				return;
			}
		}
	}
}

template<typename T>
inline void BinaryTree<T>::pre(TreeNode<T>* root, std::vector<T>& list)
{
	list.push_back(root->data);
	if (root->left != nullptr) pre(root->left,list);
	if (root->right != nullptr) pre(root->right,list);
}

template<typename T>
inline void BinaryTree<T>::mid(TreeNode<T>* root, std::vector<T>& list)
{
	if (root->left != nullptr) mid(root->left, list);
	list.push_back(root->data);
	if (root->right != nullptr) mid(root->right, list);
}

template<typename T>
inline void BinaryTree<T>::post(TreeNode<T>* root, std::vector<T>& list)
{
	if (root->left != nullptr) post(root->left, list);
	if (root->right != nullptr) post(root->right, list);
	list.push_back(root->data);
}

template<typename T>
inline std::vector<T> BinaryTree<T>::preTraverse()
{
	std::vector<T> res;
	if (this->root == nullptr) return res;
	pre(this->root, res);
	return res;
}

template<typename T>
inline std::vector<T> BinaryTree<T>::midTraverse()
{
	std::vector<T> res;
	if (this->root == nullptr) return res;
	mid(this->root, res);
	return res;
}

template<typename T>
inline std::vector<T> BinaryTree<T>::postTraverse()
{
	std::vector<T> res;
	if (this->root == nullptr) return res;
	post(this->root, res);
	return res;
}

template<typename T>
inline size_t BinaryTree<T>::deep(TreeNode<T>* root)
{
	if (root == nullptr) {
		return 0;
	}
	return max(deep(root->left), deep(root->right))+1;
}

template<typename T>
inline void BinaryTree<T>::remove(T val)
{
	if (this->root == nullptr) return;
	TreeNode<T>* cur = this->root;	//��ǰ�α�
	TreeNode<T>* parent = nullptr;	//��ָ��
	while (cur->data != val) {
		if (val > cur->data) {
			parent = cur;
			if (cur->right == nullptr) {
				std::cout<<"���������ֵ"<<std::endl;
				return;
			}
			cur = cur->right;
		}
		else {
			parent = cur;
			if (cur->left == nullptr) {
				std::cout << "���������ֵ" << std::endl;
				return;
			}
			cur = cur->left;
		}
	}
	//���ҽ���
	//��Ϊ0
	if (cur->left == nullptr && cur->right == nullptr) {
		//���parentΪ�մ������Ǹ��ڵ�
		if (parent == nullptr) {
			delete this->root;
			this->root = nullptr;
		}
		//�ýڵ����丸�ڵ���ҽڵ�
		else if(parent->right == cur) {
			delete cur;
			parent->right = nullptr;
		}
		//�ýڵ����丸�ڵ����ڵ�
		else {
			delete cur;
			parent->left = nullptr;
		}
	}
	//��Ϊ1
	else if (cur->left == nullptr || cur->right == nullptr) {
		//���parentΪ�մ������Ǹ��ڵ�
		if (parent == nullptr) {
			TreeNode<T>* temp = this->root;
			this->root = cur->left == nullptr ? cur->right: cur->left;
			delete temp;
		}
		//�ýڵ����丸�ڵ���ҽڵ�
		else if(parent->right == cur) {
			parent->right = cur->left == nullptr ? cur->right: cur->left;
			delete cur;
		}
		else {
			parent->left = cur->left == nullptr ? cur->right: cur->left;
			delete cur;
		}
	}
	//��Ϊ2
	else {
		//Ѱ�������������ҵĽڵ㣬�ýڵ�Ķ�һ����0����
		TreeNode<T>* maxRightParent = cur;	//���ҽڵ�ĸ��ڵ�
		TreeNode<T>* maxRight = cur->left;	//���ҽڵ�
		while (maxRight->right != nullptr){
			maxRightParent = maxRight;
			maxRight = maxRight->right;
		}
		//�ж����ҽڵ�Ķ� 0
		if (maxRight->left == nullptr) {
			//�ж����ҽڵ��Ǹ��ڵ��left or right
			if (maxRightParent->left == maxRight) {
				maxRightParent->left = nullptr;
			}
			else {
				maxRightParent->right = nullptr;
			}
			//�����ҽڵ��Ƶ�ɾ���Ľڵ���
			maxRight->left = cur->left;
			maxRight->right = cur->right;
		}
		//�ж����ҽڵ�Ķ� 1
		else {
			//�ж����ҽڵ��Ǹ��ڵ��left or right
			if (maxRightParent->left == maxRight) {
				maxRightParent->left = maxRight->left;
			}
			else {
				maxRightParent->right = maxRight->left;
			}
			//�����ҽڵ��Ƶ�ɾ���Ľڵ���
			maxRight->left = cur->left;
			maxRight->right = cur->right;
		}
		//���ڵ�
		//���parentΪ�մ������Ǹ��ڵ�
		if (parent == nullptr) {
			TreeNode<T>* temp = this->root;
			this->root = cur->left == nullptr ? cur->right : cur->left;
			delete temp;
		}
		//�ýڵ����丸�ڵ���ҽڵ�
		else if (parent->right == cur) {
			parent->right = cur->left == nullptr ? cur->right : cur->left;
			delete cur;
		}
		else {
			parent->left = cur->left == nullptr ? cur->right : cur->left;
			delete cur;
		}
	}
}


template<typename T>
inline void BinaryTree<T>::postDelete(TreeNode<T>* root) {
	if (root->left != nullptr) {
		postDelete(root->left);
		root->left = nullptr;
	}
	if (root->right != nullptr) {
		postDelete(root->right);
		root->right = nullptr;
	}
	delete root;
}

template<typename T>
inline BinaryTree<T>::~BinaryTree() {
	std::cout << "������������" << std::endl;
	if (root == nullptr) {
		return;
	}
	postDelete(this->root);
}
