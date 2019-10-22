#include "HuffmanTree.h"

int main()
{
	HuffmanTree * pbtnodehead;  //定义哈夫曼树的头结点 
	FILE * pFILE;  //定义文件类型指针 
	FreqCountTable F[300]; 
	FreqCountTable * pF = F;  //定义指向频数统计表的指针，用于某些函数操作
	HuffmanTree * pt;  //定义哈夫曼树结构 
	int n;
	int m;
	int * pintn = &n; //建立int叶子数n及其指针 
	FILE * pold;
	FILE * pnew;
	InitialFreq(F);  //初始化统计表
	FreqCount(pFILE, F);  //进行统计频数  
	n = LeavesNum(pF);   //计算叶子数 
	m = 2*n-1;       //节点数 
	HuffmanTree HT[m+1];
	pt = HT;	
	InitialHuffmanTree(pt , pF, n, m); //创建树  //有问题 
	CreateHuffmanCode(pt, pF, n); //创建哈夫曼码 
	OutputFile(pold, pnew, pt, pF);
	return 0;
}
