#include <iostream>
#include "SingleLinkedList.hpp"
#include "Queue.hpp"


using namespace std;
int main() {
	/*SingleLinkedList<int> list;
	list.isEmpty();
	list.add(2);
	list.add(3);
	list.add(4);
	for (size_t i = 0; i < list.length(); i++)
	{
		cout << list[i] << endl;
	}
	list.reverse();
	list.remove(1);
	for (size_t i = 0; i < list.length(); i++)
	{
		cout << list[i] << endl;
	}*/
	Queue<int> queue;
	cout << queue.getCapacity() << endl;
	cout << queue.getLength() << endl;
	queue.push_back(1);
	queue.push_back(2);
	queue.push_back(3);
	cout << queue.getLength() << endl;
	queue.pop_head();
	cout << queue.getLength() << endl;
	return 0;
}