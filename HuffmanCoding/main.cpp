#include "HuffmanTree.h"

int main()
{
	HuffmanTree * pbtnodehead;  //�������������ͷ��� 
	FILE * pFILE;  //�����ļ�����ָ�� 
	FreqCountTable F[300]; 
	FreqCountTable * pF = F;  //����ָ��Ƶ��ͳ�Ʊ��ָ�룬����ĳЩ��������
	HuffmanTree * pt;  //������������ṹ 
	int n;
	int m;
	int * pintn = &n; //����intҶ����n����ָ�� 
	FILE * pold;
	FILE * pnew;
	InitialFreq(F);  //��ʼ��ͳ�Ʊ�
	FreqCount(pFILE, F);  //����ͳ��Ƶ��  
	n = LeavesNum(pF);   //����Ҷ���� 
	m = 2*n-1;       //�ڵ��� 
	HuffmanTree HT[m+1];
	pt = HT;	
	InitialHuffmanTree(pt , pF, n, m); //������  //������ 
	CreateHuffmanCode(pt, pF, n); //������������ 
	OutputFile(pold, pnew, pt, pF);
	return 0;
}
