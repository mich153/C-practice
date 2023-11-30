//https://leetcode.com/problems/sqrtx/solutions/4343653/solution-in-c/
//find the sqrt of number
int mySqrt(int x) {
    int i = 0;
    while(1.0*i*i <= x){
        i++;
    }
    return i-1;
}

//https://leetcode.com/problems/number-of-1-bits/solutions/4343635/bits-with-c/
//find the count of 1 bits in binary number
#include <stdint.h>
int hammingWeight(uint32_t n) {
    uint32_t mask;
    int counter = 0;
    for(mask = 1; mask != 0; mask <<= 1){
        if(mask & n){
            counter++;
        }
    }
    return counter;
}

//https://leetcode.com/problems/search-insert-position/solutions/4343537/binary-search-in-c/
//find number place, or where the number place need to be if the number was in the array
//get sorted array, and use binary search
int searchInsert(int* nums, int numsSize, int target) {
    int top = 0;
    int bottom = numsSize - 1;
    int mid = numsSize/2;
    if(nums[top] > target || nums[top] == target){
        return top;
    }
    else if(nums[bottom] < target){
        return numsSize;
    }
    else if(nums[bottom] == target){
        return bottom;
    }
    while(top < bottom - 1){
        mid = (top + bottom)/2;
        if(target == nums[mid]){
            break;
        }
        if(target > nums[mid]){
            top = mid;
        }
        else{
            bottom = mid;
        }
    }
    if(target != nums[mid] && target > nums[top] && target < nums[bottom]){
        return bottom;
    }
    return mid;
}
