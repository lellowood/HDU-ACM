#include "stdafx.h"

/*
1045 

*/

#include <stdio.h>  
#include <queue>

#define W 4	//宽
#define H 4	//高

char map[H][W];//地图  

int m,w;

int affectnodex(int x, int y) {
	int num = 0;
	if (map[x][y] == '.')num++; else return 5;
	bool flag = true;
	if (x - 1 >= 0 && map[x - 1][y] != 'X')num++; else flag = false;
	if (flag && x - 2 >= 0 && map[x - 2][y] != 'X')num++; else flag = false;
	if (flag && x - 3 >= 0 && map[x - 3][y] != 'X')num++;
	flag = true;
	if (x + 1 < w && map[x + 1][y] != 'X')num++; else flag = false;
	if (flag && x + 2 < w && map[x + 2][y] != 'X')num++; else flag = false;
	if (flag && x + 3 < w && map[x + 3][y] != 'X')num++;
	return num;
};

int affectnodey(int x, int y) {
	int num = 0;
	if (map[x][y] == '.')num++; else return 5;
	bool flag = true;
	if (y - 1 >= 0 && map[x][y - 1] != 'X')num++; else flag = false;
	if (flag && y - 2 >= 0 && map[x][y - 2] != 'X')num++; else flag = false;
	if (flag && y - 3 >= 0 && map[x][y - 3] != 'X')num++;
	flag = true;
	if (y + 1 < w && map[x][y + 1] != 'X')num++; else flag = false;
	if (flag && y + 2 < w && map[x][y + 2] != 'X')num++; else flag = false;
	if (flag && y + 3 < w && map[x][y + 3] != 'X')num++;
	return num;
};

void fillnode(int x, int y) {
		bool flag = true;
		map[x][y] = '@';
		if (flag && x - 1 >= 0 && map[x - 1][y] == '.')map[x - 1][y] = '@'; else flag = false;
		if (flag && x - 2 >= 0 && map[x - 2][y] == '.')map[x - 2][y] = '@'; else flag = false;
		if (flag && x - 3 >= 0 && map[x - 3][y] == '.')map[x - 3][y] = '@';		 flag = true;
		if (flag && y - 1 >= 0 && map[x][y - 1] == '.')map[x][y - 1] = '@'; else flag = false;
		if (flag && y - 2 >= 0 && map[x][y - 2] == '.')map[x][y - 2] = '@'; else flag = false;
		if (flag && y - 3 >= 0 && map[x][y - 3] == '.')map[x][y - 3] = '@';		 flag = true;
		if (flag && x + 1 < w && map[x + 1][y] == '.')map[x + 1][y] = '@'; else flag = false;
		if (flag && x + 2 < w && map[x + 2][y] == '.')map[x + 2][y] = '@'; else flag = false;
		if (flag && x + 3 < w && map[x + 3][y] == '.')map[x + 3][y] = '@';		flag = true;
		if (flag && y + 1 < w && map[x][y + 1] == '.')map[x][y + 1] = '@'; else flag = false;
		if (flag && y + 2 < w && map[x][y + 2] == '.')map[x][y + 2] = '@'; else flag = false;
		if (flag && y + 3 < w && map[x][y + 3] == '.')map[x][y + 3] = '@';		flag = true;
};
//int affectnode(int x, int y) {
//	int num = 0;
//	if (map[x][y] == '.')num++;
//	if (x - 1 >= 0 && map[x - 1][y] == '.')num++;
//	if (x - 2 >= 0 && map[x - 2][y] == '.')num++;
//	if (x - 3 >= 0 && map[x - 3][y] == '.')num++;
//	if (y - 1 >= 0 && map[x][y - 1] == '.')num++;
//	if (y - 2 >= 0 && map[x][y - 2] == '.')num++;
//	if (y - 3 >= 0 && map[x][y - 3] == '.')num++;
//	if (x + 1 < W && map[x + 1][y] == '.')num++;
//	if (x + 2 < W && map[x + 2][y] == '.')num++;
//	if (x + 3 < W && map[x + 3][y] == '.')num++;
//	if (y + 1 < W && map[x][y + 1] == '.')num++;
//	if (y + 2 < W && map[x][y + 2] == '.')num++;
//	if (y + 3 < W && map[x][y + 3] == '.')num++;
//};
int main()
{
	freopen("data.txt", "r", stdin);// 
	while (scanf("%d", &w)!=EOF && w){
		m = 0;
		for (int i = 0; i<w; i++)
			scanf("%s", map[i]);
		for (int i = 0; i<w; i++){
			for (int j = 0; j<w; j++){
				if (map[i][j] == '.') {
					int min = affectnodey(i,j);
					int mx = i, my = j;
					//横轴 在横轴里面选一个最小影响的点
					bool left = true;
					if (i - 1 >= 0 && map[i - 1][j] != 'X') {
						int temp = affectnodey(i - 1, j);
						if (temp < min) {
							min = temp; mx = i - 1;
						}
					}
					else left = false;
					if (left && i - 2 >= 0 && map[i - 2][j] != 'X') {
						int temp = affectnodey(i - 2, j);
						if (temp < min) {
							min = temp; mx = i - 2;
						}
					}
					else left = false;
					if (left && i - 3 >= 0 && map[i - 3][j] != 'X') {
						int temp = affectnodey(i - 3, j);
						if (temp < min) {
							min = temp; mx = i - 3;
						}
					}
					left = true;
					if (i + 1 < w && map[i + 1][j] != 'X') {
						int temp = affectnodey(i + 1, j);
						if (temp < min) {
							min = temp; mx = i + 1;
						}
					}
					else left = false;
					if (left && i + 2 < w && map[i + 2][j] != 'X') {
						int temp = affectnodey(i + 2, j);
						if (temp < min) {
							min = temp; mx = i + 2;
						}
					}
					else left = false;
					if (left && i + 3 < w && map[i + 3][j] != 'X') {
						int temp = affectnodey(i + 3, j);
						if (temp < min) {
							min = temp; mx = i + 3;
						}
					}
					min += affectnodex(mx, my);
					//纵轴
					int minn = affectnodex(i, j);
					int mxx = i, myy = j;
					left = true;
					if (j - 1 >= 0 && map[i][j - 1] != 'X') {
						int temp = affectnodex(i, j - 1);
						if (temp < minn) {
							minn = temp; myy = j - 1;
						}
					}
					else left = false;
					if (left && j - 2 >= 0 && map[i][j - 2] != 'X') {
						int temp = affectnodex(i, j - 2);
						if (temp < minn) {
							minn = temp; myy = j - 2;
						}
					}
					else left = false;
					if (left && j - 3 >= 0 && map[i][j - 3] != 'X') {
						int temp = affectnodex(i, j - 3);
						if (temp < minn){
							minn = temp;myy = j - 3; 
						}
					}
					left = true;
					if (j + 1 < w && map[i][j + 1] != 'X') {
						int temp = affectnodex(i, j + 1);
						if (temp < minn) {
							minn = temp; myy = j + 1;
						}
					}
					else left = false;
					if (left && j + 2 < w && map[i][j + 2] != 'X') {
						int temp = affectnodex(i, j + 2);
						if (temp < minn) {
							minn = temp; myy = j + 2;
						}
					}
					else left = false;
					if (left && j + 3 < w && map[i][j + 3] != 'X') {
						int temp = affectnodex(i, j + 3);
						if (temp < minn) {
							minn = temp; myy = j + 3;
						}
					}
					minn += affectnodey(mxx, myy);
					if(minn>min)
						fillnode(mx, my);
					else
						fillnode(mxx, myy);
					m++;
				}
				// 1)确定map[i][j]的属性，如果可以放置，沿着横轴和竖轴遍历，比较两个的数值大小，选择数值较大的轴，在轴上找到影响最小的位置标记
			}
		}
		printf("%d\n", m);
	}
	return 0;
}