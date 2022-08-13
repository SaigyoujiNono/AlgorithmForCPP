#include <iostream>
#include "SegmentTree.hpp"


using namespace std;
int main() {
	int arr[] = { 1,3,5,7,9,11 };
	SegmentTree st(6, arr);
	int* mk = st.get();
	for (int i = 0; i < 16; i++) {
		cout << mk[i] << endl;
	}
	st.update(1, 13);
	cout << "****************" << endl;
	for (int i = 0; i < 16; i++) {
		cout << mk[i] << endl;
	}
	cout << "-------------" << endl;
	cout << st.query(1, 2) << endl;
	cout << "hhh" << endl;
}