/*HuffmanTree.h   
1.二叉树及其基本操作
2.哈夫曼树生成操作
3.码表生成操作
 
3.读取原文件并统计词频操作
4.输出压缩文件操作（压缩文件应为：码表+编码）

5.读取已压缩文件并还原（包括读码表+生成哈夫曼+按哈夫曼逐个解码三个操作）
6.输出原文到一个新的文件操作
*/
//码表（编码信息）放在压缩文件的第一行 

#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

#define  N 20
#define  M (2*N-1)   //宏定义 




//哈夫曼树的生成与哈夫曼编码表的生成：

typedef struct freqcounttable   //定义频数存储表结构用于存储统计的频数 
{
	char asciicode;   //储存对应ascii码
	int freq;  //储存其对应的频数
	char huffmancode[15];  //储存编码后的哈夫曼码 
	int flag;  //1表示有元素 0表示无元素 
}FreqCountTable;

typedef struct huffmantree
{
	unsigned int weight; //定义哈夫曼树结构体，用数组存，包含权值，左右孩子和父亲的下标 
	unsigned int parent; //按照此方法定义的哈弗曼树结构，不需要复杂的构成，可以任意查找与当前节点相关的节点 
	unsigned int LChild;
	unsigned int RChild; 
}HuffmanTree;

void select(HuffmanTree *ht,int n, int *s1, int *s2)  //哈夫曼生成算法操作 ht指向huffmantree数组首元（空），n是叶子节点数（词的种类数），s1，s2分别是两个int指针，指向权值最小的两个节点 
{
	int i;  //循环变量 
	int min;  //存储最小权值结点的下标 
	for(i=1; i<=n; i++)   //开始对叶子节点进行遍历 
	{
		if((ht+i)->parent == 0)   //如果遇到有节点的parent成员为0 则令min=i（暂存该节点下标），i = n+1跳出循环 
		{
			min = i;
			i = n+1;
		}
	}
	for(i=1; i<=n; i++)    //再次遍历，找第二个parent为0的结点（parent为0表示还没有进行哈夫曼编码） 
	{
		if((ht+i)->parent == 0)  
		{
			if((ht+i)->weight < (ht+min)->weight)  //如果这个结点的parent的权值小于刚才那个点的权值 
			{
				min = i;   //现在把最小结点的下标换成你的 
			}	
		}
	}      //因为循环不跳出，所以经过循环后必定min存储的是最小权值结点的下标 
	*s1 = min;  //用s1传出下标 
	for(i=1; i<=n; i++)    //同理，现在找出除了上面那个结点第二小的结点的下标 
	{
		if((ht+i)->parent == 0 && i!=(*s1))   //判断加一个不是s1，就可以实现找第二小 
		{
			min = i;
			i = n+1;
		}
	}
	for(i=1; i<=n; i++)
	{
		if((ht+i)->parent == 0 && i!=(*s1))
		{
			if((ht+i)->weight < (ht+min)->weight)
				min = i;
		}
	}
	*s2 = min;  //传出下标 
}

void InitialHuffmanTree(HuffmanTree *ht , FreqCountTable *w, int n, int m)  //初始化哈弗曼树   //w是存放已知频数（即0权值）的数组  n是关键词的个数（即叶子节点数） 
{ 
	int i;   //i是循环变量 
	int s1;
	int s2;
	//ht=(HuffmanTree*)malloc((m+1)*sizeof(HTNode));  /*0号单元未使用*/   //ht指向分配的huffmantree结构体数组的首空间，0号单元不使用的原因是为了方便子树和父亲的计算 
	for(i=1;i<=n;i++)    //循环结构，对每个叶子节点进行初始化赋值为0，权值为频数。先是让2~n+1位置的点存放叶子节点 
	{
		(ht+i)->weight = (w+i)->freq;
		(ht+i)->LChild = 0;
		(ht+i)->parent = 0;
		(ht+i)->RChild = 0;
	}		
	for(i=n+1;i<=m;i++)  //这是对非叶子的初始化，先都弄成0，并且存放的位置是从n+1一直到所有节点 
	{
		(ht+i)->weight = 0;
		(ht+i)->LChild = 0;
		(ht+i)->parent = 0;
		(ht+i)->RChild = 0;
	}    /*非叶子结点初始化*/
	
	for(i=n+1;i<=m;i++)    /*创建非叶子结点,建哈夫曼树*/  //从n+1开始循环 
	{
		select(ht,i-1,&s1,&s2);   //传出下标 
		(ht+s1)->parent=i;   //令他们的父亲都是第i个位置的元素 
		(ht+s2)->parent=i;
		(ht+i)->LChild=s1;   //左孩子取较小的那个 
		(ht+i)->RChild=s2;   //右孩子取较大的那个 
		(ht+i)->weight=(ht+s1)->weight+(ht+s2)->weight;
	} 
}

/*从叶子结点到根，逆向求每个叶子结点对应的哈夫曼编码*/
void CreateHuffmanCode(HuffmanTree *ht, FreqCountTable *hc, int n)  //建立哈夫曼编码表 传入一个树 一个原编码表 一个叶子数n 
{
	char			*cd;  //存放huffman编码的临时变量 
	int				i;  //循环变量 
	unsigned int	c;  //指向当前节点 
	int				start; //编码起始指针 
	int				p;  //指向父亲结点 
	 
	cd=(char * )malloc(n * sizeof(char ));  		 /*分配求当前编码的工作空间*/
	cd[n-1]='\0';   /*从右向左逐位存放编码，首先存放编码结束符*/ //因为是从结点开始往前编码所以逆向编码 
	
	for(i=1;i<=n;i++)  /*求n个叶子结点对应的哈夫曼编码*/
	{
		start=n-1;    /*初始化编码起始指针*/
		for(c=i,p=(ht+i)->parent; p!=0; c=p,p=(ht+p)->parent) /*从叶子到根结点求编码*/  //只要i位置的父亲存在，就一直循环，循环一次后把当前节点 
			if( (ht+p)->LChild == c) 
				cd[--start]='0';  /*左分支标0*/
			else 
				cd[--start]='1';  /*右分支标1*/
	strcpy((hc+i)->huffmancode,&cd[start]);
	}
	free(cd);
	for(i=1;i<=n;i++) //输入编码表，ht存放权值，hc.huffmancode存放编码，两者的下标相互对应 
	{
		printf("%c编码为%s\n",(hc+i)->asciicode,(hc+i)->huffmancode);
	}	
}

void OutputHuffman(HuffmanTree *HT, int m)   //输出哈夫曼树中的元素（打印出来） 中序打印 刚好是完全二叉树的存储顺序 
{
	if(m!=0)   //m代表下标 
	{
		printf("%d  ", (HT+m)->weight);   //递归 
		OutputHuffman(HT,(HT+m)->LChild);
		OutputHuffman(HT,(HT+m)->RChild);
	}
}

//对文件操作以获得频数统计表： 
 
void InitialFreq(FreqCountTable *pF)  //无问题 
{
	int i;
	for(i=1;i<300;i++)
	{
		(pF+i)->asciicode = -1;  //给asciicode赋值NULL
		(pF+i)->freq = 0;  //所有的频数都初始化为0
		(pF+i)->flag = 0;   //flag=0表示无元素 1表示有元素 
	}	
	return;
}

int SearchFreq(char a, FreqCountTable * pF)     //Freq表搜索操作，如果查到有该字符，则返回下标，如果没有，则返回-1 
{
	int i;
	for(i=1;i<300;i++)  //要从1开始编码 
	{
		if((pF+i)->asciicode == a)
		{
			return i;
		}
	} 
	
	return(-1);   //表示未找到该元素 
}

void FreqCount(FILE * pFILE, FreqCountTable *pF)   //读取原文件并统计词的种类和词频操作 形参：一个文件指针  //有问题 
{
	pFILE = fopen("D:\\Data.txt","rt");  //以只读文件的方式打开“Data.txt”文件（该文件存在cpp同目录下，为一文本文件）
	if(pFILE == NULL)
	{
		printf("打开文件出错！\n");
		return;
	} 
	while(!feof(pFILE))  //当没有读到文件末尾时，一直执行循环 
	{   
	    char temp = fgetc(pFILE);  //暂存文件读写位置标记指向的字符
	    int j = SearchFreq(temp, pF);  //j是下标或-1 
	    if(j == -1)  //如果没有在频数表中找到对应字符（找不到就创建这个） 
	    {	
    		int i=1;  //循环变量 
	        for(i=1;i<300;i++)  //遍历频数表 
	        {
        		if((pF+i)->flag == 0)   //如果该位置没有元素 
	            {
	        	    (pF+i)->asciicode = temp;  //存储元素，频数+1，结束此次遍历，该字符在频数表中记录成功 
	                (pF+i)->freq++;
	                (pF+i)->flag = 1;
                    break;
	            }
        	}
	    }
	    else   //如果在频数表中找到对应字符 
	    {
				(pF+j)->freq++;   //频数+1，该字符在频数表中记录成功 
	    }
	} 
	if(fclose(pFILE) == EOF)
	{
		printf("关闭文件出错！\n"); 
	}
	return;
} 

void OutputFile(FILE * pold, FILE * pnew, HuffmanTree * pt, FreqCountTable * pc)  //输出到压缩文件操作    //Debug完成 
{
	char temp; //临时存储被读的字符 
	
	pold = fopen("D:\\Data.txt","rt");  //以只读文件的方式打开“Data.txt”文件（该文件存在cpp同目录下，为一文本文件）
	if(pold == NULL)
	{
		printf("打开文件出错！\n");
		return;
	} 
	
	pnew = fopen("D:\\Code.txt","wt");  //以只写文件的方式新建“Code.txt”文件（该文件存在cpp同目录下，为一文本文件）
	if(pnew == NULL)
	{
		printf("打开文件出错！\n");
		return;
	} 
	

	int j; //循环变量 
	for(j = 1;(pc+j)->asciicode != -1;j++)
	{
		fputc((pc+j)->asciicode,pnew); //按一个原码一个编码的顺序写进去 
		fputs((pc+j)->huffmancode,pnew); 
	}
	fputc('\n',pnew);  //结尾写一个换行符作为结束标志 
	
    int i=1;  //循环变量 
    for(;;i++) //遍历码表，对比现在的字符是不是码表中对应原码（必定是）
    {
    	temp = fgetc(pold);
        if((pc+i)->asciicode == temp)
        {
            fputs((pc+i)->huffmancode,pnew);  //把i位置的编码写上去	
        }
        if(temp == EOF)
        {
            break;
        }
        else
        {
        	continue;
        }
        i = 1;
        }
	fclose(pold);  //关闭文件返回函数 
	fclose(pnew);
	return;
} 

int LeavesNum(FreqCountTable * pf)  //统计叶子节点数 
{
	int i = 1;    //循环变量 
	for(i=1;i<300;i++)
	{
		if((pf+i)->flag == 1)
		{
		
		}
		else
		{
			break;
		}
	}
	
	return i-1;
}  

