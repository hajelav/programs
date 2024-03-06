
#include <iostream>
#include <vector>

using namespace std;

/*
simple binary searh which returns -1  when the element is not found
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
simple binary searh which  returns-1 when the element is not found
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

/*
if the target is present - return the leftmost index
if the target is less than first element - return the first element
if the target is more then last element - return the last element
if the target is not present but lies between first and last element - return the element
smaller than the target
 */

int binSearch(vector<int>& ts, int low, int high, int target) {

        if (low == high)
            return low;

        int mid = low + ((high - low) >> 1);

        if (low == mid && target == ts[mid])
            return low;
        if (low == mid  && target < ts[high])
            return low;
        if (low == mid  && target > ts[high])
            return high;
        if (low == mid  && target == ts[high])
            return high;
        
        if (ts[mid] == target) {
            return binSearch(ts, low, mid, target);
        } else if (ts[mid] < target) {
            return binSearch(ts, mid, high, target);
        } else {
            return binSearch(ts, low, mid - 1, target);
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



    /*******************************************
     * TESTTING binSearch
    ********************************************/
    cout << "****************************************************" << endl;
     //search for element outside the arrray
    int idx11 = binSearch(V1, 0, V1.size()-1, 3);
    cout << "binSearch:" << idx11 << endl;
    int idx12 = binSearch(V1, 0, V1.size()-1, 10);
    cout << "binSearch:" << idx12 << endl;

    //search for element present in the list
    int idx13 = binSearch(V1, 0, V1.size()-1, 4);
    cout << "binSearch:" <<  idx13 << endl;
    int idx14 = binSearch(V1, 0, V1.size()-1, 7);
    cout << "binSearch:" <<  idx14 << endl;

    //searh for an element not present
    int idx15 = binSearch(V1, 0, V1.size()-1, 6);
    cout << "binSearch:" <<  idx15 << endl;


    return 0;
}