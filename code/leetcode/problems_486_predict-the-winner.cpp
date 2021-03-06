
/* 
data-time 2020-09-10 14:14:53


题目描述:

486. 预测赢家

给定一个表示分数的非负整数数组。 玩家 1 从数组任意一端拿取一个分数，随后玩家 2 继续从剩余数组任意一端拿取分数，然后玩家 1 拿，…… 。每次一个玩家只能拿取一个分数，分数被拿取之后不再可取。直到没有剩余分数可取时游戏结束。最终获得分数总和最多的玩家获胜。

给定一个表示分数的数组，预测玩家1是否会成为赢家。你可以假设每个玩家的玩法都会使他的分数最大化。

 

示例 1：

输入：[1, 5, 2]
输出：False
解释：一开始，玩家1可以从1和2中进行选择。
如果他选择 2（或者 1 ），那么玩家 2 可以从 1（或者 2 ）和 5 中进行选择。如果玩家 2 选择了 5 ，那么玩家 1 则只剩下 1（或者 2 ）可选。
所以，玩家 1 的最终分数为 1 + 2 = 3，而玩家 2 为 5 。
因此，玩家 1 永远不会成为赢家，返回 False 。
示例 2：

输入：[1, 5, 233, 7]
输出：True
解释：玩家 1 一开始选择 1 。然后玩家 2 必须从 5 和 7 中进行选择。无论玩家 2 选择了哪个，玩家 1 都可以选择 233 。
     最终，玩家 1（234 分）比玩家 2（12 分）获得更多的分数，所以返回 True，表示玩家 1 可以成为赢家。
 

提示：

1 <= 给定的数组长度 <= 20.
数组里所有分数都为非负数且不会大于 10000000 。
如果最终两个玩家的分数相等，那么玩家 1 仍为赢家。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/predict-the-winner
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/**
主要思路:
使用动态规划的方法:
对于dp[i][j]记录当前玩家对应的和其它玩家的最大差值
dp[i][j] = max(nums[i]-dp[i+1][j],nums[j]-dp[i][j-1])

*/

#include <cmath>
#include <cctype>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <cstdint>

using namespace std;


class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int len = nums.size();
        int dp[len][len];
        memset(&dp,0,len*len*(sizeof(int)));
        for(int i=0;i<len;++i) {
            dp[i][i]=nums[i];
        }
        // 从后向前遍历
        for(int i=len-2;i>=0;--i) {
            for(int j=i+1;j<len;++j) {
                dp[i][j] = max(nums[i]-dp[i+1][j],nums[j]-dp[i][j-1]);
            }
        }
        return dp[0][len-1]>=0;
    }
};

//关闭流输出
static auto static_lambda = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    return 0;
}();

int main(int argc,char* argv[]){
    Solution a;
    vector<int> temp={0,2,1,-6,6,-7,9,1,2,0,1};
    auto res = a.PredictTheWinner(temp);
    cout<< res << endl;
    return 0;
}
/*
优质解析1:class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        // 这个题目就是改变自硬币游戏的

        // 但是因为硬币的数量有可能是基数，所以不一定先手必赢

        // 这里的选择就是：拿左边还是右边的
        // 状态就是：先手还是后手，以及当前的序列长度

        // 设:
        // dp[i][j][1]  序列i~j构成的数组，先手可以获取的最大值
        // dp[i][j][0]  后手可以获取的最大值
        // 难点：
        // 对于i~j序列的先手的话，必定是左右两边选择一个最大值
        // dp[i][j][1] = max(dp[i+1][j][0]+nums[i],dp[i][j-1][0]+nums[j]);

        // 问题在于后手，为什么需要min，因为前者的先手，必定决定了后者不可能选到最优值，所以只能在最min的里面选择一个。
        dp[i][j][0] = min(dp[i+1][j][1],dp[i][j-1][1]);
         if(nums.size()%2==0||nums.size()==0){
             return true;
         }
        vector<vector<vector<int>>> dp(nums.size(),vector<vector<int>>(nums.size(),vector<int>(2)));
        for(int i=0;i<nums.size();++i){
            dp[i][i][1]=nums[i];
            dp[i][i][0]=0;
        }
        for(int j=1;j<nums.size();++j){
            for(int i=j-1;i>=0;--i){
                dp[i][j][1] = max(dp[i+1][j][0]+nums[i],dp[i][j-1][0]+nums[j]);
                dp[i][j][0] = min(dp[i+1][j][1],dp[i][j-1][1]);
            }
        }
        cout<<dp[0][nums.size()-1][1]<<"  "<<dp[0][nums.size()-1][0]<<endl;
        if(dp[0][nums.size()-1][1]>=dp[0][nums.size()-1][0]){
            return true;
        }else{
            return false;
        }
    }
};

//官方题解：
https://leetcode-cn.com/problems/predict-the-winner/solution/yu-ce-ying-jia-by-leetcode-solution/

//优质解析1:
https://leetcode-cn.com/problems/predict-the-winner/solution/shou-hua-tu-jie-san-chong-xie-fa-di-gui-ji-yi-hua-/
*/