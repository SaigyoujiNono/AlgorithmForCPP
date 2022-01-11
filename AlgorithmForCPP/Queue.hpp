#pragma once
/*
	ѭ������
	����ʵ��
*/
#ifndef LOOP_QUEUE
template<typename T>
class Queue {
private:
	T *queue;
	//��ǰ����
	size_t length;
	//��ǰ����
	size_t capacity;
	//��ʼָ��
	size_t head;
	//βָ��
	size_t rear;
public:
	//���캯��
	Queue();
	//�趨����
	Queue(size_t capacity);
	//��������
	~Queue();
	//���е�ǰ����
	size_t getLength();
	//��ǰ����
	size_t getCapacity();
	//��������β
	T& pop_back();
	//��������ͷ
	T& pop_head();
	//�����β
	void push_back(T val);
	//�����ͷ
	void push_head(T val);
};
#endif

template<typename T>
inline Queue<T>::Queue():length(0), capacity(10), head(0), rear(0), queue(new T[capacity]{ 0 }) {}

template<typename T>
inline Queue<T>::Queue(size_t capacity):length(0),capacity(capacity), head(0), rear(0), queue(new T[capacity]{ 0 }){}

template<typename T>
inline Queue<T>::~Queue()
{
	delete[]queue;
}

template<typename T>
inline size_t Queue<T>::getLength()
{
	return this->length;
}

template<typename T>
inline size_t Queue<T>::getCapacity()
{
	return this->capacity;
}

template<typename T>
inline T& Queue<T>::pop_back()
{
	length--;
	size_t cur = rear;
	rear = --rear < 0 ? --capacity : --rear;
	length--;
	return queue[cur];
}

template<typename T>
inline T& Queue<T>::pop_head()
{
	size_t cur = head;
	head = ++head % capacity;
	length--;
	return queue[cur];
}

template<typename T>
inline void Queue<T>::push_back(T val)
{
	if (head == rear && length == capacity) {
		throw "��������!";
	}
	queue[rear] = val;
	rear = ++rear % capacity;
	length++;
}

template<typename T>
inline void Queue<T>::push_head(T val)
{
	if (head == rear && length == capacity) {
		throw "��������!";
	}
	head = --head < 0 ? --capacity : --head;
	queue[head] = val;
	length++;
}
