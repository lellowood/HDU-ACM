#include "stdafx.h"

////堆调整
//void HeapAdjust(double H[], int T[], int start, int end){
//	double temp = H[start];
//	int tem = T[start];
//	for (int i = 2 * start + 1; i < end; i = i * 2 + 1){
//		//i结点的子节点为2i+1和2i+2
//		if (i<end - 1 && H[i]<H[i + 1])//左右孩子的比较
//			++i;//i为较大的记录的子节点
//		if (temp > H[i])//左右节点中获胜者与父亲的比较
//			break;		//若无胜者，则没有影响到子节点，退出循环
//		//若子节点比父节点大
//		//将子结点上位，从子结点的位置进行下一轮的筛选
//		H[start] = H[i];
//		T[start] = T[i];
//		start = i;
//	}
//	H[start] = temp; //将父节点放入最后空的位置
//	T[start] = tem;
//};
//void heapsort(double * s, int * t, const int K, const int N) {
//	//建立大顶堆
//	for (int i = N / 2; i >= 0; --i)
//		HeapAdjust(s, t, i, N);
//	//进行排序
//	for (int i = N - 1; i >= N - K; --i)
//	{
//		//最后一个元素和第一元素进行交换
//		double temp = s[i];
//		int tem = t[i];
//		s[i] = s[0];
//		t[i] = t[0];
//		s[0] = temp;
//		t[0] = tem;
//		//然后将剩下的无序元素继续调整为大顶堆
//		HeapAdjust(s, t, 0, i - 1);
//	}
//};

/*

1055 树节点染色
每个节点i有一标记Ci
要求最后 min ∑Ci*Fi 最小，Fi是到达节点i的时间，到达节点i的条件是i的父节点已达

设目标解为：{P1, P2,...Pt}
当前状态为Pt，下一状态为Pt+1，表示从Pt未染色点的点选择一条路径走到某一结点停止
在状态Pt下，如果有这样两个选择：
1）先染色Ci...Ci+q，在染色Cj...Cj+p
2）先染色Cj...Cj+p，在染色Ci...Ci+q

这两种方法之后，状态是一样的，所以比较这两种方案的好坏的方式是
t*Ci + (t+1)*Ci+1 + (t+2)*Ci+2 + ... + (t+q)*Ci+q + (t+q+1)*Cj + (t+q+2)*Cj+1 + (t+q+3)*Cj+2 + ... + (t+q+p+1)*Cj+p		(1)
t*Cj + (t+1)*Cj+1 + (t+2)*Cj+2 + ... + (t+p)*Cj+p + (t+p+1)*Ci + (t+p+2)*Ci+1 + (t+p+3)*Ci+2 + ... + (t+p+q+1)*Ci+q		(2)

(1)-(2) = (q+1)*(Cj + Cj+1 + Cj+2 ... + Cj+p) - (p+1)(Ci + Ci+1 + Ci+2 + ... + Ci+q)
当(Ci + Ci+1 + Ci+2 + ... + Ci+q)/(q+1) > (Cj + Cj+1 + Cj+2 ... + Cj+p)/(p+1)时，(1)<(2) 第一种方案好
当(Ci + Ci+1 + Ci+2 + ... + Ci+q)/(q+1) < (Cj + Cj+1 + Cj+2 ... + Cj+p)/(p+1)时，(1)>(2) 第二种方案好
当两者相等的时候，随便选
所以，在Pt抉择的时候，对剩余节点计算到达该点的值与时间的比值，选择最大的比值那条路径作为下一个状态

wrong answer!

后来证明这种方法是错误的！！
某一个条路径并不止会影响这条路径，还会影响这条路径上节点的子节点！！！
				1
			1		1
		   6 6		 1
					  1
					   12
这样一颗树，10位置的比值是15/4	6位置的比值是7/2

但是上面方案还是对的，只是我们在实现的时候出了问题

重新设计算法
dp[node][t]:表示给node节点t个时间所能得到的最大值和t的比值
则
dp[node][1] = Cnode;
dp[node][i+1] = (max{∑dp[subnode][j]} + Cnode)/(i+1) 其中∑j = i
			  = max(dp[node][i+1], dp[node][k] + dp[subnode][i+1-k])

由公式可以看出要先计算叶节点然后朝上计算

ok通过
中间有一个插曲，在计算的时候需要用一个零时变量保存dp
***************************************************************************************************************************************************

*/

#include <stdio.h>
#include <string>
#include <vector>
#define MAX(a,b) (a>b)?a:b

#define N 1005

int n, r;
int fi, sum;
int size;
std::vector<int> subnodes[N];					//树子节点

int dp[N][N];

double Rio[N];										//节点比值
int Bubble[N];									//冒泡
//调整排序结果
//采用冒泡排序，先上浮，得到最大值，接着多次下潜，将数组中的0排到最后
void BubbleSort(int k, int z) {
	//上浮，得到最大的值
	for (int i = k - 1; i > 0; i--) {
		if (Rio[Bubble[i]] > Rio[Bubble[i - 1]]) {
			int temp = Bubble[i];
			Bubble[i] = Bubble[i - 1];
			Bubble[i - 1] = temp;
		}
	}
	//下潜z次，z是数组中0的个数
	int bound = k-1,t = k-1;
	for (int i = 1; i <= z; i++) {
		for (int j = i; j < bound; j++) {
			if (Rio[Bubble[j]] < Rio[Bubble[j + 1]]) {
				int temp = Bubble[j];
				Bubble[j] = Bubble[j + 1];
				Bubble[j + 1] = temp;
				t = j;
			}
		}
		bound = t;
	}
};

//void Dfs(int node,int t,int s) {
//	s += Ci[node];
//	Rio[node] = (t ? (1.0*s) / t : 0);
//	t++;
//	for (int i = 0; i < subnodes[node].size(); i++)
//		//if(Ci[subnode[node][i]])
//			Dfs(subnodes[node][i],t,s);
//};
//
//void Recall(int node) {
//	if (Parent[node]&&Ci[Parent[node]])
//		Recall(Parent[node]);//回溯
//	sum += fi*Ci[node];
//	Ci[node] = 0;
//	fi++;
//	Dfs(node, 0, 0);
//};



int Dfs(int node) {
	int sub = 0;	//记录该节点下有多少子节点
	int tempdp[N];
	memset(tempdp, 0, sizeof(tempdp));
	for (int i = 0; i < subnodes[node].size(); i++) {
		int subnode = subnodes[node][i];
		int temp = Dfs(subnode);	//返回子树中节点数量
		for (int j = 1; j <= temp; j++)
			for (int k = 1; k <= sub + 1; k++)
				//dp[node][k+j] = MAX(dp[node][k+j], dp[node][k] + dp[subnode][j]);
				tempdp[k + j] = MAX(tempdp[k + j], dp[node][k] + dp[subnode][j]);	//为了防止同一子树反复计算
		sub += temp;
		for (int k = 2; k <= sub + 1; k++)
			dp[node][k] = tempdp[k];
	}
	for (int k = 1; k <= sub + 1; k++) {
		double temp = (1.0*dp[node][k]) / k;
		if (Rio[node] < temp)
			Rio[node] = temp;
	}
	return sub + 1;
};

//int main()
//{
//	int f, s;
//	freopen("data.txt", "r", stdin);
//
//	while (scanf("%d%d", &n,&r)!=EOF && (n||r)){
//		for (int i = 1; i <= n; i++) {
//			scanf("%d", Ci + i);
//			subnode[i].clear();
//			Bubble[i-1] = i;
//		}
//		Bubble[r - 1] = 1;
//		Bubble[0] = r;
//		for (int i = 1; i < n; i++) {
//			scanf("%d %d", &f, &s);
//			subnode[f].push_back(s);
//			Parent[s] = f;
//		}
//		Parent[r] = 0;//将根节点父节点设为0
//		fi = 1;
//		sum = 0;
//		while (n) {
//			int node = Bubble[0];
//			int temp = fi;//保存之前的fi，之后与更新的fi做差计算得到有多少个节点被使用
//			Recall(node);
//			temp = fi - temp;
//			BubbleSort(n, temp);
//			n -= temp;
//			//在堆中找到最大的元素
//			//计算路径值
//			//更新rio
//			//更新堆
//		}
//		printf("%d\n", sum);
//	}
//	return 0;
//}

int main()
{
	int f, s;
	freopen("data.txt", "r", stdin);
	while (scanf("%d%d", &n, &r) != EOF && (n || r)) {
		//初始化
		fi = 1;
		sum = 0;
		memset(dp, 0, sizeof(dp));
		Bubble[0] = r;
		size = 1;

		//读入数据
		for (int i = 1; i <= n; i++) {
			scanf("%d", &dp[i][1]);
			subnodes[i].clear();
			Rio[i] = 0;
		}
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &f, &s);
			subnodes[f].push_back(s);
		}

		//处理数据
		//nextnode.push_back(r);
		Dfs(r);

		while (size) {
			int node = Bubble[0]; //有最大Rio的且染色的节点
			sum += fi*dp[node][1];
			fi++;
			for (int i = 0; i < subnodes[node].size(); i++) {
				Bubble[size++] = subnodes[node][i];//将node的子节点加入可染色节点
			}
			size--;
			Bubble[0] = Bubble[size];//将最后一位的值替代到第0位，也就是将node从Bubble中剔除
			BubbleSort(size, 0);
		}

		printf("%d\n", sum);
	}
	return 0;
}