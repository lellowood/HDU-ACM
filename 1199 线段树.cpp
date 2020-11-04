/*
* * =====================================================================================
* *
* *       Filename:  hdu1199.cpp
* *
* *    Description:
*
*          建立线段树
*                                  [0-4294967295]
*                                  /            \
*                     [0-2147483647]             [2147483648-4294967295]
*                      /           \             /           \
*           [0-]***********************************************************
*          如果某个节点不是混色节点就不需要向下生长子节点
*          注意：
*          1、虽然题目只要一个输入，但请用while持续读入
*          2、数据类型用unsigned long
*			3、注意父节点更新后需要同步子节点！！！！！
*
*
*          不过确实有一点笨，完全可以用数组来存储，还用动态空间
* *        Version:  1.0
* *        Created:  2020年09月30日 15时12分22秒
* * =====================================================================================
* */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NN 2000
#define WW 2147483647
/****************************这里是失败多次的关键*********************************
之前定义：
#define WW1 4294967296
如果采用这个，就会导致 unsigned long类型初始化为0
*********************************************************************************/
#define WW1 4294967295

/*  **************************************pre-define************************************************ */

typedef unsigned long uuint;
typedef struct segment_tree_node * STNodePtr;

#define min(x,y) x>y?y:x
#define max(x,y) x>y?x:y

struct  segment_tree_node {
	uuint left;
	uuint right;
	char w_or_b;            //'w': white, 'b': black, 2: mixed
	STNodePtr left_child;
	STNodePtr right_child;
};

/*  *************************************  function  *********************************************** */

//segment_tree_node root = {0, WW, 1, NULL, NULL};
//STNodePtr rootptr = &root;


void construct_seg_tree(STNodePtr node, uuint left, uuint right, char wb) {
	if ((*node).w_or_b == wb) {
		return;                           //如果颜色一致不需要生成子节点
	}
	uuint middle = (((*node).right + (*node).left) >> 1) + 1;
	if (left == (*node).left && right == (*node).right) {
		/****************************这里是失败多次的关键*********************************
		原始做法：
		(*node).w_or_b = wb;
		return;
		这种做法没有考虑的情况是：如果父节点发生改变没有更新子节点，就会导致如果有新的例子走入子节点会沿用之前的没有更新的状态！！
		举例：
		4
		1 4 w
		5 8 w
		1 8 b
		2 3 w
		错误输出：1 8
		*********************************************************************************/
		if ((*node).w_or_b != wb) {
			(*node).w_or_b = wb;
			if ((*node).left_child != NULL) {
				construct_seg_tree((*node).left_child, left, min(middle - 1, right), wb);
			}
			if ((*node).right_child != NULL) {
				construct_seg_tree((*node).right_child, max(middle, left), right, wb);
			}
		}
		return;
	}
	if ((*node).left_child == NULL) {
		(*node).left_child = new segment_tree_node{ (*node).left, middle - 1, (*node).w_or_b, NULL, NULL };
	}
	if ((*node).right_child == NULL) {
		(*node).right_child = new segment_tree_node{ middle, (*node).right, (*node).w_or_b, NULL, NULL };
	}
	if (left < middle) {
		construct_seg_tree((*node).left_child, left, min(middle - 1, right), wb);
	}
	if (right >= middle) {
		construct_seg_tree((*node).right_child, max(middle, left), right, wb);
	}
	(*node).w_or_b = 2;
}

void count_seg_tree(STNodePtr node, uuint &left, uuint &right, uuint &m_left, uuint &m_right) {
	left = right = m_left = m_right = WW1;

	if ((*node).w_or_b == 'b')
		return;
	if ((*node).w_or_b == 'w') {
		left = (*node).right;
		right = (*node).left;
		m_left = (*node).left;
		m_right = (*node).right;
		return;
	}
	uuint l_left, l_right, l_m_left, l_m_right;
	if ((*node).left_child != NULL)
		count_seg_tree((*node).left_child, l_left, l_right, l_m_left, l_m_right);
	uuint r_left, r_right, r_m_left, r_m_right;
	if ((*node).right_child != NULL)
		count_seg_tree((*node).right_child, r_left, r_right, r_m_left, r_m_right);

	uuint middle = (((*node).right + (*node).left) >> 1) + 1;
	left = l_left;
	if (l_left == middle - 1 && r_left != WW1) { left = r_left; }
	right = r_right;
	if (r_right == middle && l_right != WW1) { right = l_right; }

	if (left != WW1) { m_left = (*node).left; m_right = left; }                         //最左侧
	if (l_m_right != WW1 && l_m_left != WW1 && (l_m_right - l_m_left > m_right - m_left || (l_m_right - l_m_left == 0 && m_right == WW1 && m_left == WW1))) { m_left = l_m_left; m_right = l_m_right; }//左侧中间
	if (l_right != WW1 && (middle - 1 - l_right > m_right - m_left || (middle - 1 - l_right == 0 && m_right == WW1 && m_left == WW1))) { m_left = l_right; m_right = middle - 1; }//左侧右边

	if (l_right != WW1 && r_left != WW1 && (r_left - l_right > m_right - m_left || (r_left - l_right == 0 && m_right == WW1 && m_left == WW1))) { m_left = l_right; m_right = r_left; }//左右连接
	if (r_left != WW1 && (r_left - middle > m_right - m_left || (r_left - middle == 0 && m_right == WW1 && m_left == WW1))) { m_left = middle; m_right = r_left; }//右侧左边
	if (r_m_right != WW1 && r_m_left != WW1 && (r_m_right - r_m_left > m_right - m_left || (r_m_right - r_m_left == 0 && m_right == WW1 && m_left == WW1))) { m_left = r_m_left; m_right = r_m_right; }//右侧中间
	if (right != WW1 && ((*node).right - right > m_right - m_left || ((*node).right - right == 0 && m_right == WW1 && m_left == WW1))) { m_left = right; m_right = (*node).right; } //最右侧
}

void destroy_seg_tree(STNodePtr node) {
	if ((*node).left_child != NULL) {
		destroy_seg_tree((*node).left_child);
		(*node).left_child = NULL;
	}
	if ((*node).right_child != NULL) {
		destroy_seg_tree((*node).right_child);
		(*node).right_child = NULL;
	}
	delete node;
	node = NULL;
}

int main() {
	int N;
	uuint left, right, m_left, m_right;
	char wb;
	while (scanf("%d", &N) != EOF) {
		STNodePtr rootptr = new segment_tree_node{ 0, WW, 'b', NULL, NULL };
		while (N--) {
			scanf("%ld %ld %c", &left, &right, &wb);
			construct_seg_tree(rootptr, left - 1, right - 1, wb);
		}
		count_seg_tree(rootptr, left, right, m_left, m_right);
		if (m_left != WW1 && m_right != WW1)
			printf("%ld %ld\n", m_left + 1, m_right + 1);
		else
			printf("Oh, my god\n");
		destroy_seg_tree(rootptr);
	}
	return 0;
}
