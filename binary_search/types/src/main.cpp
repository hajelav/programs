
#include <iostream>
#include <vector>

using namespace std;

/*
simple binary searh which -1 false when the element is not found
else return the leftmost index of the found element
*/
int binSearchLeft(vector<int>& nums, int low, int high, int key) {

    if(low > high)
        return -1;

    int mid = low + ((high-low)>>1);

    if(low == high && key == nums[low])
        return low;

    if(key == nums[mid]) {
        return binSearchLeft(nums, low, mid, key);   
    } else if(key < nums[mid]) {
        return binSearchLeft(nums, low, mid-1, key);
    } else {
        return binSearchLeft(nums, mid+1, high, key);
    }

}

/*
simple binary searh which -1 false when the element is not found
else return the right index of the found element
*/
int binSearchRight(vector<int>& nums, int low, int high, int key) {

    if(low > high)
        return -1;

    int mid = low + ((high-low)>>1);

    if(low == high && key == nums[low])
        return low;
    if(low == mid && key == nums[low] && key == nums[high])
        return high;

    if(key == nums[mid]) {
        return binSearchRight(nums, mid, high, key);   
    } else if(key < nums[mid]) {
        return binSearchRight(nums, low, mid-1, key);
    } else {
        return binSearchRight(nums, mid+1, high, key);
    }

}

int main() {

    vector<int> V1 = {4,4,4,4,5,5,7,7,7};

    /*******************************************
     * TESTTING binSearchLeft
    ********************************************/
    //search for element outside the arrray
    int idx1 = binSearchLeft(V1, 0, V1.size()-1, 3);
    cout << "binSearchLeft:" << idx1 << endl;
    int idx2 = binSearchLeft(V1, 0, V1.size()-1, 10);
    cout << "binSearchLeft:" << idx2 << endl;

    //search for element present in the list
    int idx3 = binSearchLeft(V1, 0, V1.size()-1, 4);
    cout << "binSearchLeft:" <<  idx3 << endl;
    int idx4 = binSearchLeft(V1, 0, V1.size()-1, 7);
    cout << "binSearchLeft:" <<  idx4 << endl;

    //searh for an element not present
    int idx5 = binSearchLeft(V1, 0, V1.size()-1, 6);
    cout << "binSearchLeft:" <<  idx5 << endl;

    cout << "*********************************************" << endl;

    /*******************************************
     * TESTTING binSearchRight
    ********************************************/
     //search for element outside the arrray
    int idx6 = binSearchRight(V1, 0, V1.size()-1, 3);
    cout << "binSearchRight:" << idx6 << endl;
    int idx7 = binSearchRight(V1, 0, V1.size()-1, 10);
    cout << "binSearchRight:" << idx7 << endl;

    //search for element present in the list
    int idx8 = binSearchRight(V1, 0, V1.size()-1, 4);
    cout << "binSearchRight:" <<  idx8 << endl;
    int idx9 = binSearchRight(V1, 0, V1.size()-1, 7);
    cout << "binSearchRight:" <<  idx9 << endl;

    //searh for an element not present
    int idx10 = binSearchRight(V1, 0, V1.size()-1, 6);
    cout << "binSearchRight:" <<  idx10 << endl;

    return 0;
}