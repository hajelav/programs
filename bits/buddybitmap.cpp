#include "../utils.h"

using namespace std;

class BuddyBitmap {

	public:
	vector<int>bitmap;
	int mSize;
	BuddyBitmap(vector<int> buddy):bitmap(buddy) {
		mSize = bitmap.size();
	}

	void printBuddyBitmap();
	int getParentIdx(int i);
	int getLeftChildIdx(int i);
	int getRightChildIdx(int i);

	//clear bit functions
	void clearBit(int offSet, int len);
	void clearAncestors(vector<int>& bitmap, int i);
	void clearDescendantLeft(vector<int>& bitmap, int i);
	void clearBits(int offset, int len);

	//set bit functions
	void setBit(int offSet, int len);

};

int BuddyBitmap::getParentIdx(int i) {

	if(i==0)
		return -1;
       return (i-1)/2;	
}


int BuddyBitmap::getLeftChildIdx(int i) {
	if(2*i+1 > mSize)
		return -1;
	return 2*i+1;
}


int BuddyBitmap::getRightChildIdx(int i) {
	if(2*i+2 > mSize)
		return -1;
	return 2*2+1;
}


void BuddyBitmap::printBuddyBitmap() {

	cout << "**************************************************" << endl;
	for(auto &a : bitmap)
		cout << a << " ";
	cout << endl;
	cout << "**************************************************" << endl;
}



/**********************************************************************************************
 * set bit code here
 **********************************************************************************************/


/**********************************************************************************************
 * clear bit code here
 **********************************************************************************************/


/* clear all the parent to 0 , from ith node till the root. There is an optimization here
 * we can stop the loop(need not go till root, if any bitmap[i] becomes 0
 * */ 
void BuddyBitmap::clearAncestors(vector<int>& bitmap, int i) {

	while(bitmap[i] > 0 && i > 0) {
		bitmap[i] = 0;
		i = getParentIdx(i);
	}
}
/* clear all the left children from node i */
void BuddyBitmap::clearDescendantLeft(vector<int>& bitmap, int i) {
	while(i > 0) {
		bitmap[i] = 0;
		i = getLeftChildIdx(i);
	}
}

void BuddyBitmap::clearBits(int offset, int len) {
	
	if(offset < 0 || offset+len-1 > mSize){
		cout << "no action" << endl;
		return;
	}

	int range = offset+len-1;
	for(int i=offset; i<=range; i++) {

		//bitmap is already cleared continue
		if(bitmap[i] == 0) {
			cout << i << " bit already cleared" << endl;
			continue;
		}

		/* here the bitmap is 1 , so we need to handle two cases
		 * 1. we have to make all the ancestors up to root(0-offset) to 0 - because if
		 * the current bit becomes zero, then if there are any 1's above it,  then those
		 * 1's have to be 0
		 * 2. since we cannot have a 0 in the parent, and all 1's below it, we need
		 * to make all 0's either to the left path or the right path
		 */

		clearAncestors(bitmap, i);
		clearDescendantLeft(bitmap, i);
	}
}


int main() {
	
	int n;
	vector<int> bm;
	cout << "enter size" << endl;
	cin >> n;
	
	cout << "enter elements" << endl;
	int x;
	for(int i=0; i<n; i++) {
		cin >> x;
	       bm.push_back(x);	
	}
	
	BuddyBitmap buddy(bm);
	buddy.printBuddyBitmap();
	int offset, len;
	cout << "CLEAR BITS : enter offset and len" << endl;
	cin >> offset;
	cin >> len;
	buddy.clearBits(offset, len);
	buddy.printBuddyBitmap();
}
