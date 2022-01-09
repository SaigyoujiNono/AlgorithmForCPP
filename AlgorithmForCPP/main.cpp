#include <iostream>
#include "SingleLinkedList.hpp"


using namespace std;
int main() {
	SingleLinkedList<int> list;
	list.isEmpty();
	list.add(2);
	list.add(3);
	list.add(4);
	for (size_t i = 0; i < list.length(); i++)
	{
		cout << list[i] << endl;
	}
	list.reverse();

	for (size_t i = 0; i < list.length(); i++)
	{
		cout << list[i] << endl;
	}

	return 0;
}