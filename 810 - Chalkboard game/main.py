from typing import List

class Solution:
    # Naive solution
    def xorGameRecursive(self, nums: List[List[object]]) -> bool:
        xor_res = 0
        for num, inList in nums:
            if inList:
                xor_res = xor_res ^ num
        if xor_res == 0:
            return True

        is_there_good_move = False
        for i in range(len(nums)):
            if nums[i][1]:
                nums[i][1] = False
                is_there_good_move = is_there_good_move || (nself.xorGameRecursive(nums)
                nums[i][1] = True
                if not self.xorGameRecursive(nums):

                    return True

        return False

    def xorGame(self, nums: List[int]) -> bool:
        nums_tmp = []
        for num in nums:
            nums_tmp.append([num, True])
        return self.xorGameRecursive(nums_tmp)

def main():
    sol = Solution()
    print(sol.xorGame([1, 1, 2]))

if __name__ == "__main__":
    main()