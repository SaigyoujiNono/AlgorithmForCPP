#pragma once
#include <math.h>
#include <iostream>

using namespace std;
class SegmentTree {
private:
	int* tree;
	int length;
	int originSize;
	void updateVal(int l, int r, int index, int val, int node);
	int queryVal(int l, int r, int start, int end, int index);
public:
	/*
		构造函数
		size代表实际数组长度
	*/
	SegmentTree(int size, int nums[]);
	/*
		析构函数
		清除额外的内存占用
	*/
	~SegmentTree();
	void build(int l, int r, int index, int nums[]);
	// 更新某个下标的值
	void update(int index, int val);
	int query(int start, int end);
	int* get();
};


SegmentTree::SegmentTree(int size, int nums[]):originSize(size) {
	length = pow(2, (int)(ceil(sqrt(size))) + 1);
	tree = new int[length]{0};
	build(0, originSize - 1, 0, nums);
}

void SegmentTree::build(int l, int r, int index, int nums[]) {
	if (index >= length) return;
	if (l >= r) {
		tree[index] = nums[l];
		return;
	}
	int leftIndex = index * 2 + 1;
	int rightIndex = index * 2 + 2;
	int mid = (l + r) / 2;
	build(l, mid, index * 2 +1, nums);
	build(mid + 1, r, index * 2 + 2, nums);
	tree[index] = (leftIndex < length ? tree[leftIndex] : 0) + (rightIndex < length ? tree[rightIndex] : 0);
}

void SegmentTree::update(int index, int val) {
	updateVal(0, originSize - 1, index, val, 0);
}

int SegmentTree::query(int start, int end) {
	return queryVal(0, originSize - 1, start, end, 0);
}

int SegmentTree::queryVal(int l, int r, int start, int end, int index) {
	if (index >= length) return 0;
	if ((l >= start && r <= end) || l >= r) {
		return tree[index];
	}
	int leftIndex = index * 2 + 1;
	int rightIndex = index * 2 + 2;
	int mid = (l + r) / 2;
	int leftVal = queryVal(l, mid, start, end, leftIndex);
	int rightVal = queryVal(mid + 1, r, start, end, rightIndex);
	return leftVal + rightVal;
}

void SegmentTree::updateVal(int l, int r, int index, int val, int node){
	if (node >= length) return;
	if (l == r) {
		tree[node] = val;
		return;
	}
	int leftIndex = node * 2 + 1;
	int rightIndex = node * 2 + 2;
	int mid = (l + r) / 2;
	if (index <= mid) {
		updateVal(l, mid, index, val, leftIndex);
	}
	if (index > mid) {
		updateVal(mid + 1, r, index, val, rightIndex);
	}
	tree[node] = (leftIndex < length ? tree[leftIndex] : 0) + (rightIndex < length ? tree[rightIndex] : 0);
}

int* SegmentTree::get() {
	return tree;
}

SegmentTree::~SegmentTree() {
	if (tree != nullptr) {
		delete[] tree;
		tree = nullptr;
	}
}
