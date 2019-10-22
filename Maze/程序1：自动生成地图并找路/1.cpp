// maze.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <stdlib.h>


using namespace std;
const int N = 20;

int top;

struct map {
	int s[N*N]; //ÿ�����ӵĸ�

	int wall_row[N][N];//��ǽ
	int wall_col[N][N];//��ǽ

	int stack[N*N];
	int visit[N*N]; //ÿ��Ԫ�ط���״̬

	int maxsize;
};

bool empty(map *a) {
	return(top == -1);
}

bool full(map *a) {
	return(top == a->maxsize - 1);
}

void push(map *a, int num) {  //��ջ 
	if (full(a)) {
		cout << "full";
	}
	else {
		top++;
		a->stack[top] = num;
	}
}

void pop(map *a, int num) {  //��ջ 
	if (empty(a)) {
		cout << "empty";
	}
	else {
		top--;
	}
}

bool instack(map*a ,int num) {  //���� �ж��Ƿ���ջ ���ڴ�ӡ��ջԪ�� 
	for (int x = 0; x < (N*N - 1);x++) {
		if (a->stack[x] == num)
			return 1;
	}
	return 0;
}


bool left(map *a, int num) {   //�ж��Ƿ��������� 
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

bool isvalid(map *a, int num) {   //�ж��Ƿ���� ����ͬʱ����û�߹���ûǽ  ֻҪ����������һ�����ԾͿ�ȡ 
	if ((left(a,num)&&(a->visit[num-1]==0))||(right(a, num) && (a->visit[num + 1] == 0))||(up(a, num) && (a->visit[num - N] == 0))||(down(a, num) && (a->visit[num + N] == 0))) {
		return 1;
	}		
	else return 0;
}

void findnext(map *m, int num) {   //��·���� 
	
	if (m->visit[num] == 0) {
		m->visit[num] = 1;
		cout << "(" << num / N << "," << num%N << ")";
		if (num == (N*N - 1)) {
			cout << "successful"<<endl;
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


using namespace std;

map map1;


int find(int x)//�Ҹ�
{
	if (map1.s[x] < 0)
		return x;
	else
		return find(map1.s[x]);
}

void unionSets(int node1, int node2)//���������ĸ��ಢ
{
	int root1 = find(node1);
	int root2 = find(node2);
	if (root1 == root2)
		return;
	if (map1.s[root2] < map1.s[root1])
		map1.s[root1] = root2;
	else {
		if (map1.s[root1] == map1.s[root2]) {
			map1.s[root1]--;
			map1.s[root2] = root1; 
		}
		map1.s[root2] = root1; 
	}
}


int main()
{
	
	srand((unsigned)time(NULL));   //����RAND����

	//��ʼ��map
	for (int i = 0; i < N*N; i++) {
		map1.s[i] = -1;
	}
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map1.wall_row[i][j] = -1;

		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map1.wall_col[i][j] = -1;

		}
	}

	int x = 1;
	while (find(0)!=find(N*N-1)) { 
		if (x %2==1) {  //�������Ϳ�ǽ
			int a = rand() % (N*N);
 			if (a % N !=( N - 1)) {
				int b = a + 1;
				unionSets(a, b);

				int c = a / N;
				int d = a % N;
				map1.wall_row[c][d] = 0;
			}
		}

		else if (x %2==0) {  //�������Ϳ�ǽ
			int a = rand() % (N*(N - 1));
			int b = a + N;
			unionSets(a, b);

			int c = a / N;
			int d = a % N;
			map1.wall_col[c][d] = 0;
		}
		x++;
	}

	//����
	top = -1;
	map1.maxsize = N*N;
	for (int i = 0; i < N*N; i++) {
		map1.stack[i] = -1;
		map1.visit[i] = 0;
	}

	int item = 0;
	map *map2 = &map1;
	push(map2, item);   
	findnext(map2, item);

	int k = 0;//��ӡ��ͼ
	unsigned char m = 'X';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map1.s[k] != -1) {
				if (instack(map2, k)) {
					cout << "��";
					//cout << "��";
				}
				else cout << "��";
			}
			else cout << "��";
			k++;
			if (map1.wall_row[i][j] == -1) {
				cout << "��";
			}
			else cout << "��";
		}
		cout << endl;
		for (int j = 0; j < N; j++) {
			if (map1.wall_col[i][j] == -1) {
				cout << "��"<<"��";
			}
			else cout <<"��"<<"��";
		}
		cout << endl;
	}
	getchar();
    return 0;
}
