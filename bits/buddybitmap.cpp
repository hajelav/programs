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
	int getSiblingIdx(int i);


	//clear bit functions
	void clearBit(int offSet, int len);
	void clearAncestors(int i);
	void clearDescendantLeft(int i);
	void clearBits(int offset, int len);

	//set bit functions
	void setBit(int offSet, int len);
	void setBitAncestors(int i);
	void setBitDescendants(int i);


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
	return 2*i+2;
}


int BuddyBitmap::getSiblingIdx(int i) {
	int parent = getParentIdx(i);
	if(parent < 0)
		return -1;
	if(i == 2*parent + 1)
		return 2*parent+2;
	else
		return 2*parent+1;

}

void BuddyBitmap::printBuddyBitmap() {

	cout << "****************PRINT*****************************" << endl;
	for(auto &a : bitmap)
		cout << a << " ";
	cout << endl;
	cout << "**************************************************" << endl;
}



/**********************************************************************************************
 * set bit code here
 **********************************************************************************************/
/* recursively go through all the nodes below the node and set them as 1 */

void BuddyBitmap::setBitDescendants(int i) {

	cout << "i:" << " " << i << endl;
	/* return if you go beyond leaf nodes */
	if(i < 0)
		return;
	/* if you encounter a node with 1, then no need to go down as all the nodes
	 * below it , will be 1
	 */
	if(bitmap[i])
		return;
	bitmap[i] = 1;

	int left = getLeftChildIdx(i);
	int right = getRightChildIdx(i);
	setBitDescendants(left);
	setBitDescendants(right);

}

void BuddyBitmap::setBitAncestors(int i) {
	cout << "setBitAncestors:" << i << endl;

	int idx;
	while((idx = getSiblingIdx(i)) > 0 && bitmap[idx] > 0) {
		cout << "sibling:" << idx << endl;
		//set the parent idx to 1
		int parent = getParentIdx(i);
		bitmap[parent] = 1;
		i = parent;
	}

}

void BuddyBitmap::setBit(int offset, int len) {

	if(offset < 0 || offset+len-1 > mSize){
		cout << "setBit: no action" << endl;
		return;
	}

	int range = offset+len-1;
	for(int i=offset; i<=range; i++) {

		//bitmap is already set, continue
		if(bitmap[i] == 1) {
			cout << i << " bit already set" << endl;
			continue;
		}

		/* set the bit at pos i to 1. after that we need to do 2 steps
		 * 1. we need to travel down the tree and make sure all the bits below tree rooted at i 
		 * are 1 
		 * 2. since we have turned on the bit at i, we also need to see , if any path up to the
		 * root also needs to be set to 1 ?. To do this we go to sibling(i), and if its 1 then
		 * we set parent(i) to 1. Repeat this on the path to the root, till the time
		 * you find a sibling which is set to 1
		 */
		cout << "calling descendants" << endl;
		setBitDescendants(i);
		setBitAncestors(i);


	}

}

/**********************************************************************************************
 * clear bit code here
 **********************************************************************************************/


/* clear all the parent to 0 , from ith node till the root. There is an optimization here
 * we can stop the loop(need not go till root, if any bitmap[i] becomes 0
 * */ 
void BuddyBitmap::clearAncestors(int i) {

	while(bitmap[i] > 0 && i > 0) {
		bitmap[i] = 0;
		i = getParentIdx(i);
	}
}
/* clear all the left children from node i */
void BuddyBitmap::clearDescendantLeft(int i) {
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

		clearAncestors(i);
		clearDescendantLeft(i);
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

	cout << "SET BITS : enter offset and len" << endl;
	cin >> offset;
	cin >> len;
	buddy.setBit(offset, len);
	buddy.printBuddyBitmap();
}
