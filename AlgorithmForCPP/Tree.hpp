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
	TreeNode<T>* root;	//根节点
	void postDelete(TreeNode<T>* root);
public:
	BinaryTree();
	~BinaryTree();
	void add(T val);
	void pre(TreeNode<T>* root, std::vector<T> &list);
	void mid(TreeNode<T>* root, std::vector<T>& list);
	void post(TreeNode<T>* root, std::vector<T>& list);
	std::vector<T> preTraverse();//前序遍历
	std::vector<T> midTraverse();//中序遍历
	std::vector<T> postTraverse();//后序遍历
	size_t deep(TreeNode<T>* root);//最大深度
	void remove(T val);	//删除节点
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
	TreeNode<T>* cur = this->root;	//当前游标
	TreeNode<T>* parent = nullptr;	//父指针
	while (cur->data != val) {
		if (val > cur->data) {
			parent = cur;
			if (cur->right == nullptr) {
				std::cout<<"不存在这个值"<<std::endl;
				return;
			}
			cur = cur->right;
		}
		else {
			parent = cur;
			if (cur->left == nullptr) {
				std::cout << "不存在这个值" << std::endl;
				return;
			}
			cur = cur->left;
		}
	}
	//查找结束
	//度为0
	if (cur->left == nullptr && cur->right == nullptr) {
		//如果parent为空代表这是根节点
		if (parent == nullptr) {
			delete this->root;
			this->root = nullptr;
		}
		//该节点是其父节点的右节点
		else if(parent->right == cur) {
			delete cur;
			parent->right = nullptr;
		}
		//该节点是其父节点的左节点
		else {
			delete cur;
			parent->left = nullptr;
		}
	}
	//度为1
	else if (cur->left == nullptr || cur->right == nullptr) {
		//如果parent为空代表这是根节点
		if (parent == nullptr) {
			TreeNode<T>* temp = this->root;
			this->root = cur->left == nullptr ? cur->right: cur->left;
			delete temp;
		}
		//该节点是其父节点的右节点
		else if(parent->right == cur) {
			parent->right = cur->left == nullptr ? cur->right: cur->left;
			delete cur;
		}
		else {
			parent->left = cur->left == nullptr ? cur->right: cur->left;
			delete cur;
		}
	}
	//度为2
	else {
		//寻找左子树中最右的节点，该节点的度一定是0或者
		TreeNode<T>* maxRightParent = cur;	//最右节点的父节点
		TreeNode<T>* maxRight = cur->left;	//最右节点
		while (maxRight->right != nullptr){
			maxRightParent = maxRight;
			maxRight = maxRight->right;
		}
		//判断最右节点的度 0
		if (maxRight->left == nullptr) {
			//判断最右节点是父节点的left or right
			if (maxRightParent->left == maxRight) {
				maxRightParent->left = nullptr;
			}
			else {
				maxRightParent->right = nullptr;
			}
			//将最右节点移到删除的节点上
			maxRight->left = cur->left;
			maxRight->right = cur->right;
		}
		//判断最右节点的度 1
		else {
			//判断最右节点是父节点的left or right
			if (maxRightParent->left == maxRight) {
				maxRightParent->left = maxRight->left;
			}
			else {
				maxRightParent->right = maxRight->left;
			}
			//将最右节点移到删除的节点上
			maxRight->left = cur->left;
			maxRight->right = cur->right;
		}
		//父节点
		//如果parent为空代表这是根节点
		if (parent == nullptr) {
			TreeNode<T>* temp = this->root;
			this->root = cur->left == nullptr ? cur->right : cur->left;
			delete temp;
		}
		//该节点是其父节点的右节点
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
	std::cout << "析构函数来咯" << std::endl;
	if (root == nullptr) {
		return;
	}
	postDelete(this->root);
}
