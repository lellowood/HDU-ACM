#include "stdafx.h"

// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

/*
1107 教会我的经验就是不认真一点会出各种各样的错误
*/



#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define SUB(x,y) (x>y?(x-y):(y-x))
#define R  12
#define C  12
#define N  1000

int r, c;

int map[R+1][C+1][4];

int direct[6][2] = { 1,0,0,1,1,1,-1,0, 0,-1, -1,-1 };
double param[3][2] = {0.5,0.5,0.8,0.2,0.2,0.8};
int SWE[1000][6];
int nums[3][2];
int swe;

int main() {
	int n, t;
	int s[2];
	char ch;
	freopen("data.txt", "r",stdin);
	//freopen("output.txt", "w", stdout);
	scanf("%d\n", &n);
	while (n--) {
		swe = 1;
		nums[0][0] = nums[0][1] = nums[1][0] = nums[1][1] =nums[2][0] = nums[2][1] = 0;
		memset(SWE, 0, sizeof(SWE));
		scanf("%d\n", &t);
		ch = getchar();
		while (ch != '0') {
			scanf("%d %d %d %d %d\n", SWE[swe], SWE[swe] + 1, SWE[swe] + 2, SWE[swe] + 3, SWE[swe] + 4);
			switch (ch) {
			case 'S':
				SWE[swe][5] = 0;
				nums[0][0]++;
				nums[0][1]+= SWE[swe][4];
				break;
			case 'W':
				SWE[swe][5] = 1;
				nums[1][0]++;
				nums[1][1] += SWE[swe][4];
				break;
			case 'E':
				SWE[swe][5] = 2;
				nums[2][0]++;
				nums[2][1] += SWE[swe][4];
				break;
			}
			++swe;
			ch = getchar();
		}
		while (t--) {
			memset(map, 0, sizeof(map));
			for (int i = 1; i < swe; i++) {
				if (SWE[i][5] < 6) {
					if (map[SWE[i][0]][SWE[i][1]][SWE[i][5]%3] == 0) {
						map[SWE[i][0]][SWE[i][1]][SWE[i][5]%3] = i;
						map[SWE[i][0]][SWE[i][1]][3]++;
					}
					else map[SWE[i][0]][SWE[i][1]][3] = 3;
					if (SWE[i][0] + direct[SWE[i][5]][0] < 1 || SWE[i][0] + direct[SWE[i][5]][0] > R || SWE[i][1] + direct[SWE[i][5]][1] < 1 || SWE[i][1] + direct[SWE[i][5]][1] > C)	
						SWE[i][5] = (SWE[i][5] + 3) % 6;
					if (SWE[i][0] + direct[SWE[i][5]][0] > 0 && SWE[i][0] + direct[SWE[i][5]][0] <= R&&SWE[i][1] + direct[SWE[i][5]][1] > 0 && SWE[i][1] + direct[SWE[i][5]][1] <= C) {
						SWE[i][0] += direct[SWE[i][5]][0];
						SWE[i][1] += direct[SWE[i][5]][1];
					}
				}
			}
			for (int i = 1; i <= R; i++) {
				for (int j = 1; j <= C; j++) {
					if (map[i][j][3] == 2) {
						for (int k = 0, p = 0; k < 3; k++) {
							if (map[i][j][k])
								s[p++] = map[i][j][k];
						}
						int atk1 = ((SWE[s[0]][2] * param[SWE[s[0]][5] % 3][0] + SWE[s[0]][3] * param[SWE[s[0]][5] % 3][1])*(SWE[s[0]][4] + 10)) / 100.0;
						int atk2 = ((SWE[s[1]][2] * param[SWE[s[0]][5] % 3][0] + SWE[s[1]][3] * param[SWE[s[0]][5] % 3][1])*(SWE[s[1]][4] + 10)) / 100.0;
						if (SWE[s[0]][4] <= atk2) {
							nums[SWE[s[0]][5] % 3][0]--;
							nums[SWE[s[0]][5] % 3][1]-= SWE[s[0]][4];
							SWE[s[0]][5] = 6;
						}
						else {
							nums[SWE[s[0]][5] % 3][1] -= atk2;
							SWE[s[0]][4] -= atk2;
						}
						if (SWE[s[1]][4] <= atk1) {
							nums[SWE[s[1]][5] % 3][0]--;
							nums[SWE[s[1]][5] % 3][1] -= SWE[s[1]][4];
							SWE[s[1]][5] = 6;
						}
						else {
							nums[SWE[s[1]][5] % 3][1] -= atk1;
							SWE[s[1]][4] -= atk1;
						}
					}
				}
			}
		}
		printf("%d %d\n", nums[0][0], nums[0][1]);
		printf("%d %d\n", nums[1][0], nums[1][1]);
		printf("%d %d\n***\n", nums[2][0], nums[2][1]);
	}
	return 0;
}