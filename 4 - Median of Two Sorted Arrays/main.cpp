#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    double getMedianSortedArray(vector<int>& nums2)
    {
        int n = nums2.size();
        return n % 2 == 0 ? (nums2[n / 2 - 1] + nums2[n / 2]) / 2.0 : nums2[n / 2];
    }
    double findAboveEqualIndex(vector<int>& nums, int value)
    {
        if (value < nums[0])
            return -1;
        if (value > nums[nums.size() - 1])
            return nums.size();
        int left = 0, right = nums.size() - 1;
        
        while (left < right) { // preserve nums[left] <= value
            int mid = floorUp(left + (right - left) / 2.0);
            if (nums[mid] <= value) {
                left = mid;
            } else {
                right = mid - 1;    
            }
        }
        
        value = nums[left];
        right = left, left = 0;
        // Find first occurence of value
        while (left < right) { // preserve nums[left] == value
            int mid = left + (right - left) / 2;
            if (nums[mid] == value) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return left;
    }
    double findBelowEqualIndex(vector<int>& nums, int value)
    {
        if (value < nums[0])
            return -1;
        if (value > nums[nums.size() - 1])
            return nums.size();
        int left = 0, right = nums.size() - 1;
        while (left < right) { // preserve value <= nums[right]
            int mid = left + (right - left) / 2;
            if (value <= nums[mid]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        value = nums[right];
        left = right, right = nums.size() - 1;
        // Find last occurence of value
        while (left < right) { // preserve nums[right] == value
            int mid = floorUp(left + (right - left) / 2.0);
            if (nums[mid] == value) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        return right;
    }

    int floorUp(double value) {
        return (int)value + ((value - (int)value) > 0 ? 1 : 0);
    }
    int floorDown(double value) {
        return ((int)value);
    }

    int moveUpEqualIdx(vector<int>& nums, int idx) {
        if (idx < 0 || idx >= (int)nums.size())
            return idx;
        int value = nums[idx];
        int idxA = idx;
        int idxB = nums.size() - 1;
        while(idxA != idxB)
        {
            int mid = floorUp((idxA + idxB) / 2.0);
            if (nums[mid] == value) {
                idxA = mid;
            }
            else
            {
                idxB = mid - 1;
            }
        }
        return idxA;
    }

    int moveDownEqualIdx(vector<int>& nums, int idx) {
        if (idx < 0 || idx >= (int)nums.size())
            return idx;
        int value = nums[idx];
        int idxA = 0;
        int idxB = idx;
        while(idxA != idxB)
        {
            int mid = (idxA + idxB) / 2.0;
            if (nums[mid] == value) {
                idxB = mid;
            }
            else
            {
                idxA = mid + 1;
            }
        }
        return idxB;
    }

    int countBiggerThan(vector<int>& nums, int value) {
        if (value <= nums[0])
            return 0;
        if (value > nums[nums.size() - 1])
            return nums.size();
        
        int idxA = 0;
        int idxB = nums.size() - 1; // value <= nums[idxB]
        while(idxA != idxB)
        {
            int mid = (idxA + idxB) / 2.0;
            if (value <= nums[mid]) {
                idxB = mid;
            }
            else
            {
                idxA = mid + 1;
            }
        }
        return idxB;
    }

    int countSmallerThan(vector<int>& nums, int value) {
        if (value < nums[0])
            return nums.size();
        if (value >= nums[nums.size() - 1])
            return 0;
        int idxA = 0;   // value >= nums[idxA]
        int idxB = nums.size() - 1;
        while(idxA != idxB)
        {
            int mid = floorUp((idxA + idxB) / 2.0);
            if (value >= nums[mid]) {
                idxA = mid;
            }
            else
            {
                idxB = mid - 1;
            }
        }
        return nums.size() - idxA - 1;
    }

    bool checkValidityOfBoundaries(vector<int>& nums1, vector<int>& nums2, int medianAboveEqualIndex_num1, int medianAboveEqualIndex_num2, int medianBelowEqualIndex_num1, int medianBelowEqualIndex_num2) {
        int m = nums1.size();
        int n = nums2.size();
        
        int aboveValue = 0;
        bool aboveConfigured = false;
        if (medianAboveEqualIndex_num1 >= 0 && medianAboveEqualIndex_num1 < m) {
            aboveValue = nums1[medianAboveEqualIndex_num1];
            aboveConfigured = true;
        }

        if (medianAboveEqualIndex_num2 >= 0 && medianAboveEqualIndex_num2 < n) {
            if (aboveConfigured) {
                aboveValue = max(aboveValue, nums2[medianAboveEqualIndex_num2]);
            } else {
                aboveValue = nums2[medianAboveEqualIndex_num2];
                aboveConfigured = true;
            }
        }

        int belowValue = 0;
        bool belowConfigured = false;
        if (medianBelowEqualIndex_num1 >= 0 && medianBelowEqualIndex_num1 < m) {
            belowValue = nums1[medianBelowEqualIndex_num1];
            belowConfigured = true;
        }
        if (medianBelowEqualIndex_num2 >= 0 && medianBelowEqualIndex_num2 < n) {
            if (belowConfigured) {
                belowValue = min(belowValue, nums2[medianBelowEqualIndex_num2]);
            } else {
                belowValue = nums2[medianBelowEqualIndex_num2];
                belowConfigured = true;
            }
        }

        int biggerThanInNums1 = 0;
        int smallerThanInNums1 = 0;
        int biggerThanInNums2 = 0;
        int smallerThanInNums2 = 0;

        if (aboveConfigured)
        {
            biggerThanInNums1 = countBiggerThan(nums1, aboveValue);
            biggerThanInNums2 = countBiggerThan(nums2, aboveValue);
        }
        else 
        {
            if (medianAboveEqualIndex_num1 == -1 && medianAboveEqualIndex_num2 == -1) {
                biggerThanInNums1 = 0;
                biggerThanInNums2 = 0;
            }
            else if (medianAboveEqualIndex_num1 == m && medianAboveEqualIndex_num2 == n) {
                biggerThanInNums1 = nums1.size();
                biggerThanInNums2 = nums2.size();
            }
            else {
                std::cerr << "Invalid configuration for above value" << std::endl;
            }
        }
        
        if (belowConfigured)
        {
            smallerThanInNums1 = countSmallerThan(nums1, belowValue);
            smallerThanInNums2 = countSmallerThan(nums2, belowValue);
        }
        else 
        {
            if (medianBelowEqualIndex_num1 == -1 && medianBelowEqualIndex_num2 == -1) {
                smallerThanInNums1 = nums1.size();
                smallerThanInNums2 = nums2.size();
            }
            else if (medianBelowEqualIndex_num1 == m && medianBelowEqualIndex_num2 == n) {
                smallerThanInNums1 = 0;
                smallerThanInNums2 = 0;
            }
            else {
                std::cerr << "Invalid configuration for below value" << std::endl;
            }
        }

        if (biggerThanInNums1 + biggerThanInNums2 >= floorUp((n + m) / 2.0)) {
            return false; // Invalid boundaries
        }
        if (smallerThanInNums1 + smallerThanInNums2 >= floorUp((n + m) / 2.0)) {
            return false; // Invalid boundaries
        }

        return true;
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        
        if (m == 0)
            return getMedianSortedArray(nums2);
        else
        if (n == 0)
            return findMedianSortedArrays(nums2, nums1);

        // First we address a situation where nums1 numbers are all below nums numbers
        if (nums1[m - 1] < nums2[0]) {
            double medianIndex = (m + n - 1) / 2.0;
            if (medianIndex <= m - 1)
            {
                return (medianIndex - (int)medianIndex) == 0.5 ? (nums1[(int)medianIndex] + nums1[(int)medianIndex + 1]) / 2.0 : nums1[medianIndex];
            }
            else if (medianIndex >= m) 
            {
                return (medianIndex - (int)medianIndex) == 0.5 ? (nums2[(int)medianIndex - m] + nums2[(int)medianIndex - m + 1]) / 2.0 : nums2[medianIndex - m];
            }
            else
                return (nums1[m - 1] + nums2[0]) / 2.0;
        }
        else if (nums2[n - 1] < nums1[0]) {
            return findMedianSortedArrays(nums2, nums1);
        }

        // From now on we know m >= 1, n >= 1, and they have an intersection
        int medianAboveEqualIndex_num1 = -1;
        int medianAboveEqualIndex_num2 = -1;
        int medianBelowEqualIndex_num1 = m;
        int medianBelowEqualIndex_num2 = n;

        if (m < n)
            return findMedianSortedArrays(nums2, nums1);

        // From here on assume m >= n
        while(min(medianAboveEqualIndex_num1 + 1, m) + min(medianAboveEqualIndex_num2 + 1, n) < floorUp((n+m)/2.0) ||
             min((m - medianBelowEqualIndex_num1), m) + min((n - medianBelowEqualIndex_num2), n) < floorUp((n+m)/2.0))
        {
            int attemptMedianAboveEqualIndex_num1;
            int attemptMedianAboveEqualIndex_num2;
            int attemptMedianBelowEqualIndex_num1;
            int attemptMedianBelowEqualIndex_num2;

            // First attempt to update AboveIndex in num1
            attemptMedianAboveEqualIndex_num1 = floorDown((medianAboveEqualIndex_num1 + medianBelowEqualIndex_num1) / 2.0);
            if (attemptMedianAboveEqualIndex_num1 >= 0 && attemptMedianAboveEqualIndex_num1 < m) {
                int attemptMedianAboveEqualIndex_num2 = findAboveEqualIndex(nums2, nums1[attemptMedianAboveEqualIndex_num1]);
                if (checkValidityOfBoundaries(nums1, nums2, attemptMedianAboveEqualIndex_num1, attemptMedianAboveEqualIndex_num2, medianBelowEqualIndex_num1, medianBelowEqualIndex_num2))
                {
                    medianAboveEqualIndex_num1 = min(max(medianAboveEqualIndex_num1, attemptMedianAboveEqualIndex_num1), medianBelowEqualIndex_num1);
                    medianAboveEqualIndex_num2 = min(max(medianAboveEqualIndex_num2, attemptMedianAboveEqualIndex_num2), medianBelowEqualIndex_num2);
                }
            }

            // Then attempt to update AboveIndex in num2
            attemptMedianAboveEqualIndex_num2 = floorDown((medianAboveEqualIndex_num2 + medianBelowEqualIndex_num2) / 2.0);
            if (attemptMedianAboveEqualIndex_num2 >= 0 && attemptMedianAboveEqualIndex_num2 < n) {
                attemptMedianAboveEqualIndex_num1 = findAboveEqualIndex(nums1, nums2[attemptMedianAboveEqualIndex_num2]);
                if (checkValidityOfBoundaries(nums1, nums2, attemptMedianAboveEqualIndex_num1, attemptMedianAboveEqualIndex_num2, medianBelowEqualIndex_num1, medianBelowEqualIndex_num2))
                {
                    medianAboveEqualIndex_num1 = min(max(medianAboveEqualIndex_num1, attemptMedianAboveEqualIndex_num1), medianBelowEqualIndex_num1);
                    medianAboveEqualIndex_num2 = min(max(medianAboveEqualIndex_num2, attemptMedianAboveEqualIndex_num2), medianBelowEqualIndex_num2);
                }
            }

            // Now attempt to update BelowIndex in num1
            attemptMedianBelowEqualIndex_num1 = floorUp((medianAboveEqualIndex_num1 + medianBelowEqualIndex_num1) / 2.0);
            if (attemptMedianBelowEqualIndex_num1 >= 0 && attemptMedianBelowEqualIndex_num1 < m) {
                attemptMedianBelowEqualIndex_num2 = findBelowEqualIndex(nums2, nums1[attemptMedianBelowEqualIndex_num1]);
                if (checkValidityOfBoundaries(nums1, nums2, medianAboveEqualIndex_num1, medianAboveEqualIndex_num2, attemptMedianBelowEqualIndex_num1, attemptMedianBelowEqualIndex_num2))
                {
                    medianBelowEqualIndex_num1 = max(min(medianBelowEqualIndex_num1, attemptMedianBelowEqualIndex_num1), medianAboveEqualIndex_num1);
                    medianBelowEqualIndex_num2 = max(min(medianBelowEqualIndex_num2, attemptMedianBelowEqualIndex_num2), medianAboveEqualIndex_num2);
                }
            }

            // Then attempt to update BelowIndex in num2
            attemptMedianBelowEqualIndex_num2 = floorUp((medianAboveEqualIndex_num2 + medianBelowEqualIndex_num2) / 2.0);
            if (attemptMedianBelowEqualIndex_num2 >= 0 && attemptMedianBelowEqualIndex_num2 < n) {
                attemptMedianBelowEqualIndex_num1 = findBelowEqualIndex(nums1, nums2[attemptMedianBelowEqualIndex_num2]);
                if (checkValidityOfBoundaries(nums1, nums2, medianAboveEqualIndex_num1, medianAboveEqualIndex_num2, attemptMedianBelowEqualIndex_num1, attemptMedianBelowEqualIndex_num2))
                {
                    medianBelowEqualIndex_num1 = max(min(medianBelowEqualIndex_num1, attemptMedianBelowEqualIndex_num1), medianAboveEqualIndex_num1);
                    medianBelowEqualIndex_num2 = max(min(medianBelowEqualIndex_num2, attemptMedianBelowEqualIndex_num2), medianAboveEqualIndex_num2);
                }
            }

            attemptMedianAboveEqualIndex_num1 = floorUp((medianAboveEqualIndex_num1 + medianBelowEqualIndex_num1) / 2.0);
            if (attemptMedianAboveEqualIndex_num1 >= 0 && attemptMedianAboveEqualIndex_num1 < m) {
                attemptMedianAboveEqualIndex_num2 = findAboveEqualIndex(nums2, nums1[attemptMedianAboveEqualIndex_num1]);
                if (checkValidityOfBoundaries(nums1, nums2, attemptMedianAboveEqualIndex_num1, attemptMedianAboveEqualIndex_num2, medianBelowEqualIndex_num1, medianBelowEqualIndex_num2))
                {
                    medianAboveEqualIndex_num1 = min(max(medianAboveEqualIndex_num1, attemptMedianAboveEqualIndex_num1), medianBelowEqualIndex_num1);
                    medianAboveEqualIndex_num2 = min(max(medianAboveEqualIndex_num2, attemptMedianAboveEqualIndex_num2), medianBelowEqualIndex_num2);
                }
            }

            // Then attempt to update AboveIndex in num2
            attemptMedianAboveEqualIndex_num2 = floorUp((medianAboveEqualIndex_num2 + medianBelowEqualIndex_num2) / 2.0);
            if (attemptMedianAboveEqualIndex_num2 >= 0 && attemptMedianAboveEqualIndex_num2 < n) {
                attemptMedianAboveEqualIndex_num1 = findAboveEqualIndex(nums1, nums2[attemptMedianAboveEqualIndex_num2]);
                if (checkValidityOfBoundaries(nums1, nums2, attemptMedianAboveEqualIndex_num1, attemptMedianAboveEqualIndex_num2, medianBelowEqualIndex_num1, medianBelowEqualIndex_num2))
                {
                    medianAboveEqualIndex_num1 = min(max(medianAboveEqualIndex_num1, attemptMedianAboveEqualIndex_num1), medianBelowEqualIndex_num1);
                    medianAboveEqualIndex_num2 = min(max(medianAboveEqualIndex_num2, attemptMedianAboveEqualIndex_num2), medianBelowEqualIndex_num2);
                }
            }

            // Now attempt to update BelowIndex in num1
            attemptMedianBelowEqualIndex_num1 = floorDown((medianAboveEqualIndex_num1 + medianBelowEqualIndex_num1) / 2.0);
            if (attemptMedianBelowEqualIndex_num1 >= 0 && attemptMedianBelowEqualIndex_num1 < m) {
                attemptMedianBelowEqualIndex_num2 = findBelowEqualIndex(nums2, nums1[attemptMedianBelowEqualIndex_num1]);
                if (checkValidityOfBoundaries(nums1, nums2, medianAboveEqualIndex_num1, medianAboveEqualIndex_num2, attemptMedianBelowEqualIndex_num1, attemptMedianBelowEqualIndex_num2))
                {
                    medianBelowEqualIndex_num1 = max(min(medianBelowEqualIndex_num1, attemptMedianBelowEqualIndex_num1), medianAboveEqualIndex_num1);
                    medianBelowEqualIndex_num2 = max(min(medianBelowEqualIndex_num2, attemptMedianBelowEqualIndex_num2), medianAboveEqualIndex_num2);
                }
            }

            // Then attempt to update BelowIndex in num2
            attemptMedianBelowEqualIndex_num2 = floorDown((medianAboveEqualIndex_num2 + medianBelowEqualIndex_num2) / 2.0);
            if (attemptMedianBelowEqualIndex_num2 >= 0 && attemptMedianBelowEqualIndex_num2 < n) {
                attemptMedianBelowEqualIndex_num1 = findBelowEqualIndex(nums1, nums2[attemptMedianBelowEqualIndex_num2]);
                if (checkValidityOfBoundaries(nums1, nums2, medianAboveEqualIndex_num1, medianAboveEqualIndex_num2, attemptMedianBelowEqualIndex_num1, attemptMedianBelowEqualIndex_num2))
                {
                    medianBelowEqualIndex_num1 = max(min(medianBelowEqualIndex_num1, attemptMedianBelowEqualIndex_num1), medianAboveEqualIndex_num1);
                    medianBelowEqualIndex_num2 = max(min(medianBelowEqualIndex_num2, attemptMedianBelowEqualIndex_num2), medianAboveEqualIndex_num2);
                }
            }

            // Handle special cases
            if (medianAboveEqualIndex_num1 >= 0 && medianAboveEqualIndex_num2 >= 0 &&
                medianAboveEqualIndex_num1 < m && medianAboveEqualIndex_num2 < n &&
                medianBelowEqualIndex_num1 >= 0 && medianBelowEqualIndex_num2 >= 0 &&
                medianBelowEqualIndex_num1 < m && medianBelowEqualIndex_num2 < n &&
                nums1[medianAboveEqualIndex_num1] == nums1[medianBelowEqualIndex_num1] &&
                nums2[medianAboveEqualIndex_num2] == nums2[medianBelowEqualIndex_num2]) {
                break;
            }

            medianAboveEqualIndex_num1 = moveUpEqualIdx(nums1, medianAboveEqualIndex_num1);
            medianAboveEqualIndex_num2 = moveUpEqualIdx(nums2, medianAboveEqualIndex_num2);
            medianBelowEqualIndex_num1 = moveDownEqualIdx(nums1, medianBelowEqualIndex_num1);
            medianBelowEqualIndex_num2 = moveDownEqualIdx(nums2, medianBelowEqualIndex_num2);
        }

        int a;
        if (medianAboveEqualIndex_num1 < 0 || medianAboveEqualIndex_num1 >= m)
            a = nums2[medianAboveEqualIndex_num2];
        else if (medianAboveEqualIndex_num2 < 0 || medianAboveEqualIndex_num2 >= n)
            a = nums1[medianAboveEqualIndex_num1];
        else if (nums1[medianAboveEqualIndex_num1] > nums2[medianAboveEqualIndex_num2]) {
            a = nums1[medianAboveEqualIndex_num1];
        }
        else {
            a = nums2[medianAboveEqualIndex_num2];
        }

        int b;
        if (medianBelowEqualIndex_num1 >= m || medianBelowEqualIndex_num1 < 0)
            b = nums2[medianBelowEqualIndex_num2];
        else if (medianBelowEqualIndex_num2 >= n || medianBelowEqualIndex_num2 < 0)
            b = nums1[medianBelowEqualIndex_num1];
        else if (nums1[medianBelowEqualIndex_num1] < nums2[medianBelowEqualIndex_num2]) {
            b = nums1[medianBelowEqualIndex_num1];
        }
        else {
            b = nums2[medianBelowEqualIndex_num2];
        }

        return (a + b) / 2.0;
    }
};

void printVector(const vector<int>& vec) {
    for (const auto& val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

void prettyPrint(Solution& sol, vector<int>& nums1, vector<int>& nums2) {
    cout << "nums1: ";
    printVector(nums1);
    cout << "nums2: ";
    printVector(nums2);
    double median = sol.findMedianSortedArrays(nums1, nums2);
    cout << "Median: " << median << endl;
    cout << "------------------------" << endl;
}

int main() {
    Solution solution;
    
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};
    prettyPrint(solution, nums1, nums2);

    nums1 = {1, 2};
    nums2 = {3, 4};
    prettyPrint(solution, nums1, nums2);

    nums1 = {0, 0};
    nums2 = {0, 0};
    prettyPrint(solution, nums1, nums2);

    nums1 = {2, 2, 4, 4};
    nums2 = {2, 2, 2, 4, 4};
    prettyPrint(solution, nums1, nums2);

    nums1 = {2, 2, 4, 4};
    nums2 = {2, 2, 4, 4};
    prettyPrint(solution, nums1, nums2);

    nums1 = {1, 2};
    nums2 = {-1, 3};
    prettyPrint(solution, nums1, nums2);

    nums1 = {2};
    nums2 = {1, 3, 4};
    prettyPrint(solution, nums1, nums2);

    nums1 = {2};
    nums2 = {1, 3, 4, 5};
    prettyPrint(solution, nums1, nums2);

    nums1 = {1, 3};
    nums2 = {2, 4, 5, 6, 7, 8, 9};
    prettyPrint(solution, nums1, nums2);

    return 0;
}