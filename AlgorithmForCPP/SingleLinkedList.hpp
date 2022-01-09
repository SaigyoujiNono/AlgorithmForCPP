#pragma once

#ifndef SINGLE_LINKED_LIST
template<typename T>
class Node {
public:
	T val;
	Node* next;
	Node(T val) :val(val), next(nullptr) {};
};
template<typename T>
class SingleLinkedList
{
public:
	Node<T>* head;
	size_t size;
public:
	SingleLinkedList() :head(nullptr), size(0) {};
	//判断是否为空:true为空,false非空
	bool isEmpty();
	//添加一个元素，成功返回true
	void add(T val);
	//根据下标删除一个元素，成功返回true
	void remove(size_t index);
	//链表长度
	size_t length();
	//重载数组读取
	T& operator [](size_t index);
	//反转链表
	void reverse();
};

template<typename T>
bool SingleLinkedList<T>::isEmpty() {
	if (this->head == nullptr || this->size == 0) {
		return true;
	}
	return false;
}

template<typename T>
void SingleLinkedList<T>::add(T val) {
	//如果头指针为空则直接赋值给头指针
	if (this->head == nullptr) {
		this->head = new Node<T>(val);
		this->size++;
		return;
	}
	Node<T>* cur = this->head;
	while (cur->next != nullptr) {
		cur = cur->next;
	}
	cur->next = new Node<T>(val);
	this->size++;
}

template<typename T>
void SingleLinkedList<T>::remove(size_t index) {
	if (index > this->size) {
		throw "下标越界!";
	}
	Node<T>* pre = nullptr;
	Node<T>* cur = this->head;
	for (size_t i = 0; i < index; i++)
	{
		pre = cur;
		cur = cur->next;
	}
	pre->next = cur->next;
	delete cur;
	this->size--;
}


template<typename T>
size_t SingleLinkedList<T>::length() {
	return this->size;
}
template<typename T>
T& SingleLinkedList<T>::operator [](size_t index) {
	if (index > this->size) {
		throw "下标越界!";
	}
	Node<T>* cur = this->head;
	for (size_t i = 0; i < index; i++)
	{
		if (cur->next != nullptr)
			cur = cur->next;
		else
			throw "下标越界!";
	}
	return cur->val;
}

template<typename T>
void SingleLinkedList<T>::reverse() {
	if (this->head == nullptr || this->head->next == nullptr) {
		return;
	}
	Node<T> *pre, *cur, *next;
	pre = this->head;
	cur = pre->next;
	next = cur->next;
	this->head->next = nullptr;

	while(true) {
		cur->next = pre;
		pre = cur;
		cur = next;
		if(next!=nullptr){
			next = next->next;
		}
		else {
			this->head = pre;
			return;
		}
	}
}
#endif
