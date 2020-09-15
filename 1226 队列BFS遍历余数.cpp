/*
1226 超级密码
思考点：
1、n==0，选择最小的数即可，即使最小的数为0
2、n==1，选择最小的非0数即可
3、n>2，使用广度优先遍历填充0-n的残差值，广度的标准是每次增加一位

4、有0数字存在的时候，注意0对余数的影响——其实对余数没影响，影响的是位数
5、注意累乘是n的倍数的情况
6、注意int累乘溢出问题
7、注意C比N大的情况，不能直接初始，需要取余

*******************************************************************************
经过暴力数据和别人贴出来的代码对比发现最终的原因：
之前就有发现如果有0存在已达的余数位置需要重复访问，但是我没想到的是：
没有0的时候更需要重复访问！！！！！

还要注意初始化条件后是否就已经满足条件该结束了
*******************************************************************************
做题的时候会做很多假设来方便建模——————————一旦假设出错！就从根本上错了
*/

#include <iostream>
#include <queue>
#include <vector>
//#include <pair>


#define CC 500
#define NN 5000 //0<=N<=NN
#define CI 2
#define CA 16	//CI<=C<=CA
#define MI 1
#define MA 16	//MI<=M<=MA


bool dig[16];	//提供的可用数字
char num[CC + 50];	//最后的结果

struct rd_node {
	char c;
	short m;
	short n;
};

std::vector<rd_node> rd[NN + 50];		//余数——对应的dig
//std::vector<int> prd[NN + 50];	//上一个余数——对应rd的index

int main() {
	freopen("data.txt", "r", stdin);
	int t, m, s, c, j, n;
	int ch;
	char i;
	scanf("%d", &t);
	while (t--) {
		memset(dig, 0, sizeof(bool) * 16);
		scanf("%d %d %d", &n, &c, &m);
		for (i = 0; i<m; i++) {
			scanf("%X ", &ch);
			dig[ch] = 1;
		}
		for (j = 0; j <= n; ++j) {
			rd[j].clear();
		}
		s = 0;
		//如果n==0，选择最小的数即可
		if (n == 0) {
			if (dig[0]) {
				num[0] = 0;
				s = 1;
			}
		}
		else if (n == 1) {
			for (i = 1; i < 16 && !dig[i]; ++i);
			if (i < 16) {
				num[0] = i;
				s = 1;
			}
		}
		else {
			std::queue<int> rd_queue;	//当前到达的余数队列
			for (i = 0; i < 16; ++i) {
				if (dig[i]) {
					int next_rd = i;
					if (next_rd > n) {
						next_rd %= n;
						if (next_rd == 0)next_rd = n;
					}
					if (rd[next_rd].size() == 0) {				//避免有重复
						rd[next_rd].push_back({ i, 0, -1});
						rd_queue.push(next_rd);
					}
				}
			}
			int multip = c;										//累乘因子
			for (j = 1; j < CC; ++j) {
				std::queue<int> old_queue;
				while (!old_queue.empty())old_queue.pop();		//清空
				swap(old_queue, rd_queue);						//交换
				int sum_multip = 0;								//累乘值
				bool rd_reached[NN] = { 0 };
				for (i = 0; i < 16 && rd[n].size() == 0; ++i) {		//防止初始化时就满足要求
					if (dig[i]) {
						std::queue<int> tmp_queue(old_queue);
						while (!tmp_queue.empty()) {
							int current_rd = tmp_queue.front();		//当前残差
							tmp_queue.pop();
							int next_rd = current_rd + sum_multip;	//下一残差
							if (next_rd > n) {
								next_rd %= n;
								if (next_rd == 0)next_rd = n;
							}
							if (rd[next_rd].size() < CC&&!rd_reached[next_rd]) {
								rd_reached[next_rd] = 1;
								rd[next_rd].push_back({ i, (short)j, (short)current_rd });
								rd_queue.push(next_rd);
							}
						}
					}
					sum_multip += multip;
				}
				if (rd[n].size() > 0) {
					short current_rd = n;
					short last_rd = rd[n].back().n;
					short last_m = rd[n].back().m;
					s = 0;
					num[s++] = rd[n].at(0).c;
					while (last_rd != -1) {
						while(rd[last_rd].back().m >= last_m)rd[last_rd].pop_back();
						num[s++] = rd[last_rd].back().c;
						current_rd = last_rd;
						last_m = rd[last_rd].back().m;
						last_rd = rd[last_rd].back().n;
						rd[current_rd].pop_back();
					}
					break;
				}
				multip *= c;
				if (multip%n)		//排除multip等于n的倍数情况
					multip %= n;
				else
					multip = n;		//防止累乘溢出
			}
		}
		if (s > 0) {
			for (j = 0; j < s; ++j) {
				printf("%X", num[j]);
			}
			printf("\n");
		}
		else
			printf("give me the bomb please\n");
	}
	return 0;
}
