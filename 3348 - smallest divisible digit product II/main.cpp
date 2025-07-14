#include <iostream>
#include <numeric>
#include <chrono>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>            // for std::set
#include <unordered_set>  // for std::unordered_set

using namespace std;

class Solution {
public:
    bool isDivisibleByOneToNineOnly(long long t) {
        for (int div = 2; div <= 9; div++) {
            while (1) {
                if (t % div != 0) {
                    break;
                }
                t /= div;
            }
        }
        if (t != 1) {
            return false; // t is not a product of 1-9 only
        }
        return true; // t is a product of 1-9 only
    }

    bool isZeroFree(long long num) {
        while (num > 0) {
            if (num % 10 == 0) {
                return false;
            }
            num /= 10;
        }
        return true;
    }
    
    string getNextBiggerEqualNonZeroNumber(string num) {
        string next_big_num = "";

        bool already_bigger = false;
        while (num != "")
        {
            long long digit = num[0] - '0'; // get last digit
            num = num.substr(1); // remove last digit
            if (already_bigger)
                digit = 1;

            if (digit == 0) {
                digit = 1; // replace zero with one
                already_bigger = true; // we are already bigger than num
            }
            next_big_num = next_big_num + string(1, '0' + digit); // prepend digit to next big number
        }
        return next_big_num;
    }

    long long getProductOfDigits(long long num) {
        long long product = 1;
        while (num > 0) {
            long long digit = num % 10;
            product *= digit;
            num /= 10;
        }
        return product;
    }

    string intToString(long long num) {
        string result = "";
        if (num == 0) {
            return "0";
        }
        while (num > 0) {
            result = char((num % 10) + '0') + result;
            num /= 10;
        }
        return result;
    }

    vector<int> getPrimeDigitPowers(long long t)
    {
        vector<int> digitPrimePowers(10, 0); // 2, 3, 5, 7

        while (t % 2 == 0) {
            digitPrimePowers[2]++;
            t /= 2;
        }
        while (t % 3 == 0) {
            digitPrimePowers[3]++;
            t /= 3;
        }
        while (t % 5 == 0) {
            digitPrimePowers[5]++;
            t /= 5;
        }
        while (t % 7 == 0) {
            digitPrimePowers[7]++;
            t /= 7;
        }

        return digitPrimePowers;
    }

    string buildSmallestNumberFromDigitsOccurences(vector<int> digitOccurences)
    {
        string result = "";
        for (int i = 1; i <= 9; i++) {
            int count = digitOccurences[i];
            for (int j = 0; j < count; j++) {
                result += char(i + '0'); // Convert digit to character
            }
        }

        if (result == "")
            result = "1";

        return result;
    }

    string buildBiggestNumberFromDigitsOccurences(vector<int> digitOccurences)
    {
        string result = "";
        for (int i = 9; i >= 1; i--) {
            int count = digitOccurences[i];
            for (int j = 0; j < count; j++) {
                result += char(i + '0'); // Convert digit to character
            }
        }
        return result;
    }

    unordered_map<string, vector<vector<int>>> memo;

    string makeKey(long long t, bool noThree, bool noTwo) {
        return to_string(t) + "_" + to_string(noThree) + "_" + to_string(noTwo);
    }

    // Since a digit product of 4 can stem from two-twos or one-four we have many different representations for a product of digits.
    vector<vector<int>> findMinimalDigitsOccurences(long long t, bool noThreeDivision = 0, bool noTwoDivision = 0)
    {
        string key = makeKey(t, noThreeDivision, noTwoDivision);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }

        vector<int> primeDigitPowers = getPrimeDigitPowers(t);
        vector<vector<int>> minimalDigitOccurences = {};

        if (t == 1)
        {
            minimalDigitOccurences.push_back(vector<int>(10, 0)); // t = 1 means no digits are needed
            removeReplicationsOfVectors(minimalDigitOccurences);
            memo[key] = minimalDigitOccurences;
            return minimalDigitOccurences;
        }
        int threeOccurence = primeDigitPowers[3];
        if (!noThreeDivision)
            for (int nine_occ = 0; nine_occ <= threeOccurence / 2 + 1; nine_occ++)
            {
                for (int six_occ = 0; six_occ <= max(threeOccurence - nine_occ * 2 + 1, 0); six_occ++)
                {
                    int three_occ = (threeOccurence - nine_occ * 2 - six_occ);

                    // If we added a 6, and it is possible to remove it lets do it
                    long long newT = t / pow(2, min(primeDigitPowers[2], six_occ));

                    vector<vector<int>> div3 = findMinimalDigitsOccurences(newT / pow(3, threeOccurence), 1, noTwoDivision);
                    for (auto& vec : div3)
                    {
                        if (three_occ > 0)
                            vec[3] += three_occ;
                        vec[6] += six_occ;
                        vec[9] += nine_occ;
                        minimalDigitOccurences.push_back(vec);
                    }
                }
            }
        
        int twoOccurence = primeDigitPowers[2];
        if (!noTwoDivision)
            for (int eight_occ = 0; eight_occ <= twoOccurence / 3 + 1; eight_occ++)
            {
                for (int four_occ = 0; four_occ <= max((twoOccurence - eight_occ * 3) / 2 + 1, 0); four_occ++)
                {
                    for (int six_occ = 0; six_occ <= max((twoOccurence - eight_occ * 3 - four_occ * 2) + 1, 0); six_occ++)
                    {
                        int two_occ = (twoOccurence - eight_occ * 3 - six_occ - four_occ * 2);

                        // If we added a 6, and it is possible to remove it lets do it
                        long long newT = t / pow(3, min(primeDigitPowers[3], six_occ));

                        vector<vector<int>> div2 = findMinimalDigitsOccurences(newT / pow(2, twoOccurence), noThreeDivision, 1);
                        for (auto& vec : div2)
                        {
                            if (two_occ > 0)
                                vec[2] += two_occ;
                            vec[4] += four_occ;
                            vec[6] += six_occ;
                            vec[8] += eight_occ;
                            minimalDigitOccurences.push_back(vec);
                        }
                    }
                }
            }
        if (minimalDigitOccurences.empty())
            minimalDigitOccurences.push_back(primeDigitPowers);

        removeReplicationsOfVectors(minimalDigitOccurences);
        memo[key] = minimalDigitOccurences;
        return minimalDigitOccurences;
    }

    bool isAllDigitsInVectorInNum(vector<int> minimalDigitOccurence, string num)
    {
        vector<int> numVector;
        createVectorDigitsFromNum(numVector, num);
        for (int i = 0; i < 10; i++) {
            if (minimalDigitOccurence[i] > numVector[i]) {
                return false; // not all digits in vector are in num
            }
        }

        return true;
    }

    void createVectorDigitsFromNum(vector<int>& minimalDigitOccurence, string num)
    {
        minimalDigitOccurence = vector<int>(10, 0); // reset vector to zero
        for (char c : num) {
            int digit = c - '0';
            minimalDigitOccurence[digit]++; // add missing digit
        }
    }

    bool isSmallerOrEqual(string num1, string num2)
    {
        if (num1.length() < num2.length()) {
            return true; // num1 is smaller
        }
        if (num1.length() > num2.length()) {
            return false; // num2 is smaller
        }
        return num1 <= num2; // compare lexicographically
    }

    bool isSmaller(string num1, string num2)
    {
        if (num1.length() < num2.length()) {
            return true; // num1 is smaller
        }
        if (num1.length() > num2.length()) {
            return false; // num2 is smaller
        }
        return num1 < num2; // compare lexicographically
    }

    // Function assumes it is possible to use the digit occurences to build a number bigger equal to num
    string buildSmallestNumberBiggerEqualToNum(vector<int> minimalDigitOccurence, string num)
    {
        string biggerNumber = "";

        if (accumulate(minimalDigitOccurence.begin(), minimalDigitOccurence.end(), 0) > num.length()) {
            return buildSmallestNumberFromDigitsOccurences(minimalDigitOccurence); // no digits available to build a number
        }

        string numCopy = num;
        bool alreadyBigger = false;
        for (int i = 0; i < num.length(); i++)
        {
            int digit = num[i] - '0';
            numCopy = numCopy.substr(1); // remove first digit
            for (int possibleDigit = 1; possibleDigit <= 9; possibleDigit++)
            {
                if (minimalDigitOccurence[possibleDigit] == 0)
                    continue; // skip if digit is not available

                // Check if possible to build a bigger number without the digit
                vector<int> possibleRemainder = minimalDigitOccurence;
                possibleRemainder[possibleDigit]--;
                if (alreadyBigger == 0 && possibleDigit < digit)
                    continue;

                if (alreadyBigger == 0 && possibleDigit == digit && isSmaller(buildBiggestNumberFromDigitsOccurences(possibleRemainder), numCopy)) {
                    continue; // skip if possible remainder is smaller than numCopy
                }

                if (possibleDigit > digit && !alreadyBigger)
                    alreadyBigger = true;

                // If we reach here, we can use the digit
                minimalDigitOccurence[possibleDigit]--; // use digit
                biggerNumber += char(possibleDigit + '0'); // add digit to bigger number
                break;
            }
        }
        return biggerNumber;
    }

    /*void removeReplicationsOfVectors(vector<vector<int>>& minimalDigitOccurences)
    {
        sort(minimalDigitOccurences.begin(), minimalDigitOccurences.end());
        minimalDigitOccurences.erase(unique(minimalDigitOccurences.begin(), minimalDigitOccurences.end()), minimalDigitOccurences.end());
    }*/
    void removeReplicationsOfVectors(vector<vector<int>>& minimalDigitOccurences)
    {
        set<vector<int>> uniqueSet(minimalDigitOccurences.begin(), minimalDigitOccurences.end());
        minimalDigitOccurences.assign(uniqueSet.begin(), uniqueSet.end());
    }

    void removeMinusOneOptions(vector<string>& options)
    {
        options.erase(remove(options.begin(), options.end(), "-1"), options.end());
    }

    string findExceedingSmallestNumber(vector<int> minimalDigitOccurence, string num, bool keepNumLength = false)
    {
        if (keepNumLength)
        {
            if (accumulate(minimalDigitOccurence.begin(), minimalDigitOccurence.end(), 0) > num.length())
                return "-1";
        }

        num = getNextBiggerEqualNonZeroNumber(num); // make sure num is with no zeros

        if (accumulate(minimalDigitOccurence.begin(), minimalDigitOccurence.end(), 0) == 0)
        {
            string ret = num;
            return ret;
        }

        // From here on we can assume at least one digit is in minimalDigitOccurence

        if (num.length() == 1)
        {
            string ret = buildSmallestNumberFromDigitsOccurences(minimalDigitOccurence);
            if (isSmaller(ret, num))
            {
                return "1" + ret;
            }
            return ret;
        }



        // From here we can assume at least two digits are in num
        if (accumulate(minimalDigitOccurence.begin(), minimalDigitOccurence.end(), 0) > num.length()) {
            string ret = buildSmallestNumberFromDigitsOccurences(minimalDigitOccurence);
            return ret;
        }

        // From here we can assume num length is not bigger than digits total.
        if (isAllDigitsInVectorInNum(minimalDigitOccurence, num)) {
            string ret = num;
            return ret;
        }

        if (accumulate(minimalDigitOccurence.begin(), minimalDigitOccurence.end(), 0) < num.length()) {
            string ret = buildSmallestNumberFromDigitsOccurences(minimalDigitOccurence);
            ret = string(num.length() - ret.length(), '1') + ret; // fill the rest with 1s
            if (isSmallerOrEqual(num, ret))
                return ret;
        }

        if (accumulate(minimalDigitOccurence.begin(), minimalDigitOccurence.end(), 0) == num.length())
        {
            if (isSmallerOrEqual(num, buildBiggestNumberFromDigitsOccurences(minimalDigitOccurence))) {
                string ret = buildSmallestNumberBiggerEqualToNum(minimalDigitOccurence, num);
                return ret;
            }
            else
            {
                vector<int> minimalDigitOccurenceCopy = minimalDigitOccurence; // make a copy of the vector
                minimalDigitOccurenceCopy[1]++; // use the digit 1
                string ret = buildSmallestNumberFromDigitsOccurences(minimalDigitOccurenceCopy);
                return ret;
            }
        }

        // Assumptions here:
        /*
        1. num is not zero-free
        2. at least one digit is in minimalDigitOccurence
        3. num has at least 2 digits
        4. num length is not bigger than digits total
        5. There are less digits than the length of num
        */
        int biggest_digit = num[0] - '0';

        // First try to keep length of num
        vector<string> options;
        for (int first_digit = biggest_digit; first_digit <= 9; first_digit++)
        {
            vector<int> minimalDigitOccurenceCopy = minimalDigitOccurence;
            if (minimalDigitOccurenceCopy[first_digit] > 0) {
                minimalDigitOccurenceCopy[first_digit]--; // use the digit
            }

            if (first_digit == biggest_digit)
            {
                string ret = findExceedingSmallestNumber(minimalDigitOccurenceCopy, num.substr(1), true);
                if (ret != "-1") {
                    options.push_back(string(1, '0' + first_digit) + ret); // prepend the digit to the option
                }
            }
            else if (accumulate(minimalDigitOccurenceCopy.begin(), minimalDigitOccurenceCopy.end(), 0) <= num.length() - 1)
            {
                string remainder = buildSmallestNumberFromDigitsOccurences(minimalDigitOccurenceCopy);
                options.push_back(string(1, '0' + first_digit) + string(num.length() - remainder.length() - 1, '1') + remainder);
            }
        }

        removeMinusOneOptions(options); // remove -1 options
        if (!options.empty())
        {
            string smallest_option = options[0];
            for (const auto& option : options) {
                if (isSmaller(option, smallest_option)) {
                    smallest_option = option;
                }
            }
            string ret = smallest_option; // return the smallest option found
            return ret;
        }
        else if (keepNumLength == false)
        {
            // We tried finding a number with the same length as num, but failed. We now try bigger length.
            string nextBiggestNumFromDifferentScale = string(num.length() + 1, '1'); // create a number with one more digit than num, filled with 1s
            string ret = findExceedingSmallestNumber(minimalDigitOccurence, nextBiggestNumFromDifferentScale, false);
            return ret;
        }

        return "-1";
    }

    vector<int> getLeftPrimePowers(vector<int> primePowers, string num)
    {
        vector<int> numPrimePowers = vector<int>(10, 0);
        for (int i = 0; i < num.length(); i++)
        {
            if (num[i] == '2') {
                numPrimePowers[2]++;
            }
            else if (num[i] == '3') {
                numPrimePowers[3]++;
            }
            else if (num[i] == '5') {
                numPrimePowers[5]++;
            }
            else if (num[i] == '7') {
                numPrimePowers[7]++;
            }
            else if (num[i] == '4') {
                numPrimePowers[2] += 2; // 4 = 2 * 2
            }
            else if (num[i] == '6') {
                numPrimePowers[2]++; // 6 = 2 * 3
                numPrimePowers[3]++;
            }
            else if (num[i] == '8') {
                numPrimePowers[2] += 3; // 8 = 2 * 2 * 2
            }
            else if (num[i] == '9') {
                numPrimePowers[3] += 2; // 9 = 3 * 3
            }
        }

        vector<int> leftPrimePowers(10, 0);

        for (int digit = 2; digit <= 9; digit++)
        {
            if (numPrimePowers[digit] > primePowers[digit]) {
                leftPrimePowers[digit] = 0;
            }
            else {
                leftPrimePowers[digit] = primePowers[digit] - numPrimePowers[digit]; // calculate how many digits are left
            }
        }

        return leftPrimePowers;
    }

    string smallestNumber(string num, long long t)
    {
        // First verify t is a product of 1 - 9 only
        if (!isDivisibleByOneToNineOnly(t)) {
            return "-1";
        }

        vector<vector<int>> minimalDigitOccurences = findMinimalDigitsOccurences(t);
        string smallest_possible_number = "";
        for (auto& vec : minimalDigitOccurences) {
            string possible_number = findExceedingSmallestNumber(vec, num);
            if (smallest_possible_number == "" || isSmaller(possible_number, smallest_possible_number)) {
                smallest_possible_number = possible_number;
            }
        }
        return smallest_possible_number;
    }
};

int main() {
    std::cout << "Hello, LeetCode Questions!  h" << std::endl;
    string num1 = "1234";
    long long t1 = 256;
    Solution solution;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "12355";
    t1 = 50;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "12";
    t1 = 1968750;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "10";
    t1 = 320;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "12";
    t1 = 22020096000;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "18";
    t1 = 24;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "26";
    t1 = 9;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "45";
    t1=15;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "59";
    t1 = 8;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "64";
    t1 = 20;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "815";
    t1 = 70;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "896";
    t1 = 35;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "50726";
    t1 = 2;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "6833357";
    t1 = 18;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    /*auto a = solution.getPrimeDigitPowers(22020096000);
    std::cout << "Prime digit powers for 22020096000: ";
    for (int i = 0; i < a.size(); i++) {
        std::cout << i << ": " << a[i] << " ";
    }*/

    num1 = "888744";
    t1 = 256;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "3541897";
    t1 = 128;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "19";
    t1 = 2;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "24796";
    t1 = 175;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "11111111111111104254";
    t1 = 97977600000000;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "23683531427283985145";
    t1 = 34560000000000;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    num1 = "48932796924578729577";
    t1 = 510183360;
    std::cout << "Input: num = " << num1 << ", t = " << t1 << ". Output: " << solution.smallestNumber(num1, t1) << std::endl;

    return 0;
}