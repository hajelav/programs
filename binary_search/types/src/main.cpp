
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

    if(key == nums[mid]) {
        return binSearchLeft(nums, mid, high, key);   
    } else if(key < nums[mid]) {
        return binSearchLeft(nums, low, mid-1, key);
    } else {
        return binSearchLeft(nums, mid+1, high, key);
    }

}

int main() {

    vector<int> V1 = {4,4,4,4,5,5,7,7,7};

    /*******************************************
     * TESTTING binSearchLeft
    ********************************************/
    //search for element outside the arrray
    int idx1 = binSearchLeft(V1, 0, V1.size()-1, 3);
    cout <<  idx1 << endl;
    int idx2 = binSearchLeft(V1, 0, V1.size()-1, 10);
    cout <<  idx2 << endl;

    //search for element present in the list
    int idx3 = binSearchLeft(V1, 0, V1.size()-1, 4);
    cout <<  idx3 << endl;
    int idx4 = binSearchLeft(V1, 0, V1.size()-1, 7);
    cout <<  idx4 << endl;

    //searh for an element not present
    int idx5 = binSearchLeft(V1, 0, V1.size()-1, 6);
    cout <<  idx5 << endl;


    return 0;
}