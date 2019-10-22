#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

typedef struct map {
	int s[N*N]; //每个格子的根

	int wall_row[N][N];//行墙
	int wall_col[N][N];//列墙

	int stack[N*N];
	int visit[N*N]; //每个元素访问状态

	int maxsize;
}MAP;

void ReadA(FILE *pf, MAP *pm)   ///////////////有问题 
{
	pf = fopen("Maze.txt","rt"); 
	int count=0;
	char temp;
	for(;;)
	{
		temp = fgetc(pf);
		if(temp == EOF)
		{
			break;
		}
		if(temp!='#')   
		{
			int a=count/(2*N);
			int b=count%(2*N);
			int c=a/2;
			int d=b/2;
			if(a%2==0&&b%2==0){ //JJ
				if(temp=='0'){
					pm->s[N*c+d]=0;
				}
				else
				pm->s[N*c+d]=-1;
			}
		}
	    if(temp!='#')   //JJ
		{
			int a=count/(2*N);
			int b=count%(2*N);
			int c=a/2;
			int d=b/2;
			if(a%2==0&&b%2!=0){
				if(temp=='0'){
					pm->wall_row[c][d]=0;
				}
				else
				pm->wall_row[c][d]=-1;
			}
		}
		if(temp!='#')   //JJ
		{
			int a=count/(2*N);
			int b=count%(2*N);
			int c=a/2;
			int d=b/2;
			if(a%2!=0&&b%2==0){
				if(temp=='0'){
					pm->wall_col[c][d]=0;
				}
				else
				pm->wall_col[c][d]=-1;
			}
		}
		if(temp=='#')
		{
			count--;
		}
		count++;
	}
	fclose(pf);
	return;
}

int top;

bool empty(map *a) {
	return(top == -1);
}

bool full(map *a) {
	return(top == a->maxsize - 1);
}

void push(map *a, int num) {  //入栈 
	if (full(a)) {
		//cout << "full";
		printf("full");
	}
	else {
		top++;
		a->stack[top] = num;
	}
}

void pop(map *a, int num) {  //出栈 
	if (empty(a)) {
		//cout << "empty";
		printf("empty");
	}
	else {
		top--;
	}
}

bool instack(map*a ,int num) {  //遍历 判断是否在栈 用于打印在栈元素 
	for (int x = 0; x < (N*N - 1);x++) {
		if (a->stack[x] == num)
			return 1;
	}
	return 0;
}


bool left(map *a, int num) {   //判断是否能往左走 
	if (num%N != 0) {
		int b = num / N;
		int c = num % N-1;
		if (a->wall_row[b][c] != -1) {
			return 1;
		}
		else return 0;
	}
	else return 0;
}

bool right(map *a, int num) {    
	if (num%N != N - 1) {
		int b = num / N;
		int c = num % N;
		if (a->wall_row[b][c] != -1) {
			return 1;
		}
		else return 0;
	}
	else return 0;
}

bool up(map *a, int num) {
	if (num-N>=0) {
		int b = num / N-1;
		int c = num % N;
		if (a->wall_col[b][c] != -1) {
			return 1;
		}
		else return 0;
	}
	else return 0;
}

bool down(map *a, int num) {
	if (num+N<=(N*N-1)){
		int b = num / N;
		int c = num % N;
		if (a->wall_col[b][c] != -1) {
			return 1;
		}
		else return 0;
	}
	else return 0;
}

bool isvalid(map *a, int num) {   //判断是否可走 必须同时满足没走过和没墙  只要上下左右有一个可以就可取 
	if ((left(a,num)&&(a->visit[num-1]==0))||(right(a, num) && (a->visit[num + 1] == 0))||(up(a, num) && (a->visit[num - N] == 0))||(down(a, num) && (a->visit[num + N] == 0))) {
		return 1;
	}		
	else return 0;
}

void findnext(map *m, int num) {   //找路过程 
	
	if (m->visit[num] == 0) {
		m->visit[num] = 1;
		//cout << "(" << num / N << "," << num%N << ")";
		printf("(%d,%d)",num / N,num%N);
		if (num == (N*N - 1)) {
			//cout << "successful"<<endl;
			printf("successful!\n");
			return;
		}
		if (isvalid(m, num)) {
			if (left(m, num) && (m->visit[num - 1] == 0)) {
				push(m, num - 1);
			}
			if (right(m, num) && (m->visit[num + 1] == 0)) {
				push(m, num + 1);
			}
			if (up(m, num) && (m->visit[num - N] == 0)) {
				push(m, num - N);
			}
			if (down(m, num) && (m->visit[num + N] == 0)) {
				push(m, num + N);
			}
		}
		else pop(m, num);
	}
	else pop(m, num);
	findnext(m, m->stack[top]);
}

void Convert(int aa[], int a[], int b[], int c[])
{
	int i;
	for(i=0;i<3*N*N;i++)
	{
		if(i%3==0)
		{
			a[i/3]=aa[i];
		}
		if(i%3==1)
		{
			b[i/3]=aa[i];
		}
		if(i%3==2)
		{
			c[i/3]=aa[i];
		}
	}
	return;
}

int main()
{

	FILE *pf;
	MAP mapa;
	MAP * pm=&mapa;
	ReadA(pf, pm);
	
	//查找
	top = -1;
	mapa.maxsize = N*N;
	for (int i = 0; i < N*N; i++) {
		mapa.stack[i] = -1;
		mapa.visit[i] = 0;
	}

	int item = 0;
	map *map2 = &mapa;
	push(map2, item);   
	findnext(map2, item);
	int k = 0;//打印地图
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (mapa.s[k] != -1) {
				if (instack(map2, k)) {
					//cout << "O";
					printf("※"); 
				}
				else //cout << " ";
				printf("□"); 
			}
			else //cout << m;
			printf("■"); 
			k++;
			if (mapa.wall_row[i][j] == -1) {
				//cout << m;
				printf("■"); 
			}
			else //cout << " ";
			printf("□"); 
		}
		//cout << endl;
		printf("\n");
		for (int j = 0; j < N; j++) {
			if (mapa.wall_col[i][j] == -1) {
				//cout << m<<m;
				printf("■■"); 
			}
			else //cout <<" "<<m;
			printf("□■"); 
		}
		//cout << endl;
		printf("\n");
	}
	getchar(); 
	return 0;
}


