#include <stdio.h>
#include <vector>
#include <string.h>
#define MAXN 10005
using namespace std;

int eachCarLength[MAXN], 
    sum[MAXN];
int dp[305][MAXN];
vector<int> ans;

void init() {
    for (int i = 0; i < 10005; ++i) {
        eachCarLength[i] = 0;
        sum[i] = 0;
    }
    memset(dp, 0, sizeof(dp));
    ans.clear();
}

int main()
{
    int numOfCases, temp, maxCars, maxLength, ferryLength, total;
    scanf("%d", &numOfCases);
    for (int t = 0; t < numOfCases; ++t) {
        //Initialization
        init();
        int count = 1;
        eachCarLength[0] = 0, total = 0, maxCars = 0, maxLength = 0;
        scanf("%d", &ferryLength);
        ferryLength *= 100;
        while(scanf("%d", &eachCarLength[count]) && eachCarLength[count] != 0) {
            total += eachCarLength[count];
            sum[count] = total;
            ++count;
        }
        //Use DP to find the best way to park cars!
        dp[0][0] = 1;
        for (int i = 1; i <= count - 1; ++i) {
            for (int j = 0; j <= ferryLength; ++j) {
                if (dp[i-1][j] && sum[i] - j <= ferryLength || j >= eachCarLength[i] && dp[i-1][j - eachCarLength[i]]) {
                    dp[i][j] = 1;
                    if (i > maxCars) {
                        maxCars = i;
                        maxLength = j;
                    }
                }
            }
        }
        printf("%d\n", maxCars);
        //Print how to park to get the maximum of parking cars
        int i, j = maxLength;
        for (int i = maxCars; i > 0; --i) {
            for (;j >= 0;) {
                if (sum[i] - j <= ferryLength && dp[i-1][j]) {
                    ans.push_back(0);
                    break;
                } else if (j >= eachCarLength[i] && dp[i-1][j - eachCarLength[i]]) {
                    ans.push_back(1);
                    j -= eachCarLength[i];
                    break;
                }
            }
        }
        for (int i = ans.size() - 1; i >= 0; --i) {
            printf(ans.at(i)? "port\n": "starboard\n");
        }
        if (t < numOfCases - 1) printf("\n");
    }
    return 0;
}