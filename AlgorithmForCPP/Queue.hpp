#pragma once
/*
	循环队列
	数组实现
*/
#ifndef LOOP_QUEUE
template<typename T>
class Queue {
private:
	T *queue;
	//当前长度
	size_t length;
	//当前容量
	size_t capacity;
	//起始指针
	size_t head;
	//尾指针
	size_t rear;
public:
	//构造函数
	Queue();
	//设定容量
	Queue(size_t capacity);
	//析构函数
	~Queue();
	//队列当前长度
	size_t getLength();
	//当前容量
	size_t getCapacity();
	//弹出队列尾
	T& pop_back();
	//弹出队列头
	T& pop_head();
	//放入队尾
	void push_back(T val);
	//放入队头
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
		throw "队列已满!";
	}
	queue[rear] = val;
	rear = ++rear % capacity;
	length++;
}

template<typename T>
inline void Queue<T>::push_head(T val)
{
	if (head == rear && length == capacity) {
		throw "队列已满!";
	}
	head = --head < 0 ? --capacity : --head;
	queue[head] = val;
	length++;
}
