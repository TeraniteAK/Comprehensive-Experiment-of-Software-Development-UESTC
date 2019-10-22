/*HuffmanTree.h   
1.�����������������
2.�����������ɲ���
3.������ɲ���
 
3.��ȡԭ�ļ���ͳ�ƴ�Ƶ����
4.���ѹ���ļ�������ѹ���ļ�ӦΪ�����+���룩

5.��ȡ��ѹ���ļ�����ԭ�����������+���ɹ�����+�������������������������
6.���ԭ�ĵ�һ���µ��ļ�����
*/
//���������Ϣ������ѹ���ļ��ĵ�һ�� 

#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

#define  N 20
#define  M (2*N-1)   //�궨�� 




//������������������������������ɣ�

typedef struct freqcounttable   //����Ƶ���洢��ṹ���ڴ洢ͳ�Ƶ�Ƶ�� 
{
	char asciicode;   //�����Ӧascii��
	int freq;  //�������Ӧ��Ƶ��
	char huffmancode[15];  //��������Ĺ������� 
	int flag;  //1��ʾ��Ԫ�� 0��ʾ��Ԫ�� 
}FreqCountTable;

typedef struct huffmantree
{
	unsigned int weight; //������������ṹ�壬������棬����Ȩֵ�����Һ��Ӻ͸��׵��±� 
	unsigned int parent; //���մ˷�������Ĺ��������ṹ������Ҫ���ӵĹ��ɣ�������������뵱ǰ�ڵ���صĽڵ� 
	unsigned int LChild;
	unsigned int RChild; 
}HuffmanTree;

void select(HuffmanTree *ht,int n, int *s1, int *s2)  //�����������㷨���� htָ��huffmantree������Ԫ���գ���n��Ҷ�ӽڵ������ʵ�����������s1��s2�ֱ�������intָ�룬ָ��Ȩֵ��С�������ڵ� 
{
	int i;  //ѭ������ 
	int min;  //�洢��СȨֵ�����±� 
	for(i=1; i<=n; i++)   //��ʼ��Ҷ�ӽڵ���б��� 
	{
		if((ht+i)->parent == 0)   //��������нڵ��parent��ԱΪ0 ����min=i���ݴ�ýڵ��±꣩��i = n+1����ѭ�� 
		{
			min = i;
			i = n+1;
		}
	}
	for(i=1; i<=n; i++)    //�ٴα������ҵڶ���parentΪ0�Ľ�㣨parentΪ0��ʾ��û�н��й��������룩 
	{
		if((ht+i)->parent == 0)  
		{
			if((ht+i)->weight < (ht+min)->weight)  //����������parent��ȨֵС�ڸղ��Ǹ����Ȩֵ 
			{
				min = i;   //���ڰ���С�����±껻����� 
			}	
		}
	}      //��Ϊѭ�������������Ծ���ѭ����ض�min�洢������СȨֵ�����±� 
	*s1 = min;  //��s1�����±� 
	for(i=1; i<=n; i++)    //ͬ�������ҳ����������Ǹ����ڶ�С�Ľ����±� 
	{
		if((ht+i)->parent == 0 && i!=(*s1))   //�жϼ�һ������s1���Ϳ���ʵ���ҵڶ�С 
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
	*s2 = min;  //�����±� 
}

void InitialHuffmanTree(HuffmanTree *ht , FreqCountTable *w, int n, int m)  //��ʼ����������   //w�Ǵ����֪Ƶ������0Ȩֵ��������  n�ǹؼ��ʵĸ�������Ҷ�ӽڵ����� 
{ 
	int i;   //i��ѭ������ 
	int s1;
	int s2;
	//ht=(HuffmanTree*)malloc((m+1)*sizeof(HTNode));  /*0�ŵ�Ԫδʹ��*/   //htָ������huffmantree�ṹ��������׿ռ䣬0�ŵ�Ԫ��ʹ�õ�ԭ����Ϊ�˷��������͸��׵ļ��� 
	for(i=1;i<=n;i++)    //ѭ���ṹ����ÿ��Ҷ�ӽڵ���г�ʼ����ֵΪ0��ȨֵΪƵ����������2~n+1λ�õĵ���Ҷ�ӽڵ� 
	{
		(ht+i)->weight = (w+i)->freq;
		(ht+i)->LChild = 0;
		(ht+i)->parent = 0;
		(ht+i)->RChild = 0;
	}		
	for(i=n+1;i<=m;i++)  //���ǶԷ�Ҷ�ӵĳ�ʼ�����ȶ�Ū��0�����Ҵ�ŵ�λ���Ǵ�n+1һֱ�����нڵ� 
	{
		(ht+i)->weight = 0;
		(ht+i)->LChild = 0;
		(ht+i)->parent = 0;
		(ht+i)->RChild = 0;
	}    /*��Ҷ�ӽ���ʼ��*/
	
	for(i=n+1;i<=m;i++)    /*������Ҷ�ӽ��,����������*/  //��n+1��ʼѭ�� 
	{
		select(ht,i-1,&s1,&s2);   //�����±� 
		(ht+s1)->parent=i;   //�����ǵĸ��׶��ǵ�i��λ�õ�Ԫ�� 
		(ht+s2)->parent=i;
		(ht+i)->LChild=s1;   //����ȡ��С���Ǹ� 
		(ht+i)->RChild=s2;   //�Һ���ȡ�ϴ���Ǹ� 
		(ht+i)->weight=(ht+s1)->weight+(ht+s2)->weight;
	} 
}

/*��Ҷ�ӽ�㵽����������ÿ��Ҷ�ӽ���Ӧ�Ĺ���������*/
void CreateHuffmanCode(HuffmanTree *ht, FreqCountTable *hc, int n)  //��������������� ����һ���� һ��ԭ����� һ��Ҷ����n 
{
	char			*cd;  //���huffman�������ʱ���� 
	int				i;  //ѭ������ 
	unsigned int	c;  //ָ��ǰ�ڵ� 
	int				start; //������ʼָ�� 
	int				p;  //ָ���׽�� 
	 
	cd=(char * )malloc(n * sizeof(char ));  		 /*������ǰ����Ĺ����ռ�*/
	cd[n-1]='\0';   /*����������λ��ű��룬���ȴ�ű��������*/ //��Ϊ�Ǵӽ�㿪ʼ��ǰ��������������� 
	
	for(i=1;i<=n;i++)  /*��n��Ҷ�ӽ���Ӧ�Ĺ���������*/
	{
		start=n-1;    /*��ʼ��������ʼָ��*/
		for(c=i,p=(ht+i)->parent; p!=0; c=p,p=(ht+p)->parent) /*��Ҷ�ӵ�����������*/  //ֻҪiλ�õĸ��״��ڣ���һֱѭ����ѭ��һ�κ�ѵ�ǰ�ڵ� 
			if( (ht+p)->LChild == c) 
				cd[--start]='0';  /*���֧��0*/
			else 
				cd[--start]='1';  /*�ҷ�֧��1*/
	strcpy((hc+i)->huffmancode,&cd[start]);
	}
	free(cd);
	for(i=1;i<=n;i++) //��������ht���Ȩֵ��hc.huffmancode��ű��룬���ߵ��±��໥��Ӧ 
	{
		printf("%c����Ϊ%s\n",(hc+i)->asciicode,(hc+i)->huffmancode);
	}	
}

void OutputHuffman(HuffmanTree *HT, int m)   //������������е�Ԫ�أ���ӡ������ �����ӡ �պ�����ȫ�������Ĵ洢˳�� 
{
	if(m!=0)   //m�����±� 
	{
		printf("%d  ", (HT+m)->weight);   //�ݹ� 
		OutputHuffman(HT,(HT+m)->LChild);
		OutputHuffman(HT,(HT+m)->RChild);
	}
}

//���ļ������Ի��Ƶ��ͳ�Ʊ� 
 
void InitialFreq(FreqCountTable *pF)  //������ 
{
	int i;
	for(i=1;i<300;i++)
	{
		(pF+i)->asciicode = -1;  //��asciicode��ֵNULL
		(pF+i)->freq = 0;  //���е�Ƶ������ʼ��Ϊ0
		(pF+i)->flag = 0;   //flag=0��ʾ��Ԫ�� 1��ʾ��Ԫ�� 
	}	
	return;
}

int SearchFreq(char a, FreqCountTable * pF)     //Freq����������������鵽�и��ַ����򷵻��±꣬���û�У��򷵻�-1 
{
	int i;
	for(i=1;i<300;i++)  //Ҫ��1��ʼ���� 
	{
		if((pF+i)->asciicode == a)
		{
			return i;
		}
	} 
	
	return(-1);   //��ʾδ�ҵ���Ԫ�� 
}

void FreqCount(FILE * pFILE, FreqCountTable *pF)   //��ȡԭ�ļ���ͳ�ƴʵ�����ʹ�Ƶ���� �βΣ�һ���ļ�ָ��  //������ 
{
	pFILE = fopen("D:\\Data.txt","rt");  //��ֻ���ļ��ķ�ʽ�򿪡�Data.txt���ļ������ļ�����cppͬĿ¼�£�Ϊһ�ı��ļ���
	if(pFILE == NULL)
	{
		printf("���ļ�����\n");
		return;
	} 
	while(!feof(pFILE))  //��û�ж����ļ�ĩβʱ��һֱִ��ѭ�� 
	{   
	    char temp = fgetc(pFILE);  //�ݴ��ļ���дλ�ñ��ָ����ַ�
	    int j = SearchFreq(temp, pF);  //j���±��-1 
	    if(j == -1)  //���û����Ƶ�������ҵ���Ӧ�ַ����Ҳ����ʹ�������� 
	    {	
    		int i=1;  //ѭ������ 
	        for(i=1;i<300;i++)  //����Ƶ���� 
	        {
        		if((pF+i)->flag == 0)   //�����λ��û��Ԫ�� 
	            {
	        	    (pF+i)->asciicode = temp;  //�洢Ԫ�أ�Ƶ��+1�������˴α��������ַ���Ƶ�����м�¼�ɹ� 
	                (pF+i)->freq++;
	                (pF+i)->flag = 1;
                    break;
	            }
        	}
	    }
	    else   //�����Ƶ�������ҵ���Ӧ�ַ� 
	    {
				(pF+j)->freq++;   //Ƶ��+1�����ַ���Ƶ�����м�¼�ɹ� 
	    }
	} 
	if(fclose(pFILE) == EOF)
	{
		printf("�ر��ļ�����\n"); 
	}
	return;
} 

void OutputFile(FILE * pold, FILE * pnew, HuffmanTree * pt, FreqCountTable * pc)  //�����ѹ���ļ�����    //Debug��� 
{
	char temp; //��ʱ�洢�������ַ� 
	
	pold = fopen("D:\\Data.txt","rt");  //��ֻ���ļ��ķ�ʽ�򿪡�Data.txt���ļ������ļ�����cppͬĿ¼�£�Ϊһ�ı��ļ���
	if(pold == NULL)
	{
		printf("���ļ�����\n");
		return;
	} 
	
	pnew = fopen("D:\\Code.txt","wt");  //��ֻд�ļ��ķ�ʽ�½���Code.txt���ļ������ļ�����cppͬĿ¼�£�Ϊһ�ı��ļ���
	if(pnew == NULL)
	{
		printf("���ļ�����\n");
		return;
	} 
	

	int j; //ѭ������ 
	for(j = 1;(pc+j)->asciicode != -1;j++)
	{
		fputc((pc+j)->asciicode,pnew); //��һ��ԭ��һ�������˳��д��ȥ 
		fputs((pc+j)->huffmancode,pnew); 
	}
	fputc('\n',pnew);  //��βдһ�����з���Ϊ������־ 
	
    int i=1;  //ѭ������ 
    for(;;i++) //��������Ա����ڵ��ַ��ǲ�������ж�Ӧԭ�루�ض��ǣ�
    {
    	temp = fgetc(pold);
        if((pc+i)->asciicode == temp)
        {
            fputs((pc+i)->huffmancode,pnew);  //��iλ�õı���д��ȥ	
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
	fclose(pold);  //�ر��ļ����غ��� 
	fclose(pnew);
	return;
} 

int LeavesNum(FreqCountTable * pf)  //ͳ��Ҷ�ӽڵ��� 
{
	int i = 1;    //ѭ������ 
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

