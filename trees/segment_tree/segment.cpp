#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

int  createTree(vector<int>& arr, vector<int>& segTree, int low, int high, int idx) {

	if(low == high ) {
		//		cout << "low:" << low << " high:" << high << "idx:" << idx << endl;
		segTree[idx] = arr[low];
		return arr[low];
	}

	int mid = low + ((high-low)>>1);
	int left = createTree(arr, segTree, low, mid, 2*idx+1);
	int right = createTree(arr, segTree, mid+1, high, 2*idx+2);
	segTree[idx] = left+right;
	return left+right;
}


vector<int> createSegmentTree(vector<int> arr) {
	/* segment treee will be represented by an array of size 2N-1 where
	 *  N is the number of element in the original array
	 *  total number of nodes in segment tree : 1 + 2 + 4 + 8 + ... pow(2, h)   where h= logN ( N = no of nodes in arr)
	 *                                        : pow(2, h+1) - 1  
	 */

	//calculate height of seg tree
	int x = (int)(ceil(log2(arr.size())));
	int size =  2*pow(2,x) -1;
	vector<int> segTree(size, 0);
	int low = 0;
	int high = arr.size()-1;
	int sum = createTree(arr, segTree, low, high, 0);
	cout << "Sum: " << sum << endl;
	return segTree;

}

void update(vector<int>& segTree, int low, int high, int idx, int i, int delta) {


	if(idx < low || idx > high)
		return;
	if(low == high) {
		//	cout << "low:" << low << " high:" << high << " idx:" << idx << endl;
		segTree[i] += delta;
		return;
	}
	int mid = low + ((high-low)>>1);
	segTree[i] += delta; 
	//cout << "segTree[" << i << "] :" << segTree[i] << endl;
	update(segTree, low, mid, idx, 2*i+1, delta);
	update(segTree, mid+1, high, idx, 2*i+2, delta);
}

void  updateSegmentTree(vector<int> &segTree, vector<int>& arr, int idx, int val) {

	//update the original array
	int oldVal = arr[idx];
	arr[idx] = val;
	int delta = val - oldVal;
	update(segTree, 0, arr.size()-1, idx, 0, delta); 

}

void print(vector<int>& arr) {
	for(auto &a : arr) {
		cout << a << " ";
	}
	cout << endl;
}

bool isOverlap(int qStart, int qEnd, int low, int high) {

	if((qEnd < low) || (high < qStart))
		return false;
	return true;	       
}

int query(vector<int>& segTree, int i, int low, int high, int qStart, int qEnd) {

	if(!isOverlap(qStart, qEnd, low, high))
		return 0;

	/* case 3; low and high lies completely between query range : return the value at node
	 * note that = is added for the case say low = 2 , hight 2, qStart = 2, qEnd = 8*/
	if(qStart <= low && high <= qEnd)
		return segTree[i];
	/* case 1: query range partial overlaps between low and high : recurse both sides of tree*/
	/* case 2: query range lies completely between low and high : recurse both sides of the tree*/
	int mid = low + ((high-low)>>1);
	int left = query(segTree, 2*i+1, low, mid, qStart, qEnd);
	int right = query(segTree, 2*i+2, mid+1, high, qStart, qEnd);

	return left+right;
}

int queryRange(vector<int>& segTree, vector<int>& arr, int start, int end) {

	int low = 0; int high = arr.size()-1;
	if(!isOverlap(start, end, low, high))
		return -1;
	return query(segTree, 0, low, high, start, end);
}


/*
 * #################################
 * g++ segment.cpp -o segment -Werror
 * #################################
 */ 


int main() {


	vector<int> arr = {5, 2, 1, 3, 4, 6, 7, 9, 8, 3};

	//create a segment tree
	vector<int> segTree = createSegmentTree(arr);
	print(segTree);
	//update the 5th index from 6 to 10
	//updateSegmentTree(segTree, arr, 9, 10);
	//print(segTree);
	cout << queryRange(segTree, arr, 7, 9);
	cout << endl;
	return 0;
}

