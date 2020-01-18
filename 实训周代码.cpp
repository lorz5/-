/*
	18�Ƽ�һ��
	�źƽ�
	201824111141
*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/******************** ���ݽṹ ************************/
// ������Ϣ
typedef struct City_Type {
	int id;
	char name[20];
	char from[20];
	int view;
}CityType;

// ��ͨ��Ϣ
typedef struct Tra_Type {
	int dig;				// ����
	int time;				// ��ʱ
	int cost;				// ����
	int fun;				// ��Ȥ��
}TraType;

// �ߵ���Ϣ
typedef struct Edge_Type {
	// ������Ϣ
	int ch;					// ��ʾ�Ƿ���ڽ�ͨ��ʽ��1Ϊ�У�2Ϊ��
	TraType air;			// �ñߵķɻ���Ϊ��ͨ����Ϣ
	TraType train;			// �ñߵĻ���Ϊ��ͨ����Ϣ
	TraType car;			// �ñߵ�С����Ϊ��ͨ����Ϣ
	// ������Ϣ
	int anv;				// ����Floyd_Warshall�㷨���������������·��
}EdgeType;

// ջ�ṹ
typedef struct Stack_Type {
	int dis[52];
	int top;
}StackType;

// ·����Ϣ
typedef struct BestPath_Type {
	int best_path[55];
	int len;
	int adddis;			// ����·����·��
	int addtime;		// ����·���ĺ�ʱ
	int addmoney;		// ����·���Ļ���
	int addfun;			// ����·������Ȥ��
}BestPathType;

// �ŵ��������� 
typedef struct Bridge_Type {
	int u;
	int v;
}BridgeType;


/******************** �������� ************************/
// ǰ��׼��
int in();							// ������
void tip();							// ʡ����ʾ
void ReadText();					// ��ȡ�ļ�
int TheMinLong(int, int);			// ͬһ���ߵĽ�ͨ��ʽ��·����С���Ǹ�
int TheMinMoney(int, int);			// ͬһ���ߵĽ�ͨ��ʽ�л�����С���Ǹ�
void init_graph();					// ��ʼ��ͼ
void Change_pro(int, int &, int &);	// �ı�ʡ��
void init_flag();					// ��ʼ���������
void init_bridge();					// ��ʼ��
bool is_all();						// �жϵ�ǰ·�����Ƿ��Ѱ���ָ����k������
void init_Good();					// ��ʼ������·��
void init_bestway();				// ��ʼ���������з�ʽ

// ջ����
void push(int);				// ��ջ
int pop();					// ��ջ

// ���ܺ�������Ӧ����1-9
void traver();				// 1�������������
void Hamilton();			// 2����һ�����ܶٻ�·
void Que_3();				// 3�����������Ҿ���ָ��k������Ļ�·
void Que_4();				// 4����A��B�����·������Ȥ��·
void Floyd_Warshall();			// 4.1��Floyd_Warshall�㷨�������������С·��
void traverse(int, int);		// 4.2���ݹ����u��v�����·���� 
void Que_5();				// 5��A��B������k����ͬ���㣨���Զ���k�����㣬���������ڣ�����ʱ������C����Ȥ������·��
void Que_6();				// 6�����޵�ʱ�䣨��x�죩�ڣ�Ѱ��һ���Ӷ���a������b������Ȥ�����з�ʽ
void Que_7();				// 7�����޵ľ��ѣ���xԪ���ڣ�Ѱ��һ���Ӷ���a������b������Ȥ�����з�ʽ
void Que_8();				// 8���ۺ�6��7�����ƣ����ͬ��
void FindBridge();			// 9�����ź͹ؽڵ�


// DFS
void DFS_Hamilton(int, int, int, int, int);						//	���ܶ�
void DFS_MostFun(int, int, int, int, int, int);					//	���޾���������Ȥ��·
void DFS_fun(int, int, int, int, int);							//	A��B����Ȥ·��
void DFS_K_MostFun(int, int, int, int, int, int, int);			//	A��B����k�����������Ȥ·��
void DFS_Time_MostFun(int, int, int, int, int, int);			//	����ʱ���ڶ���a������b������Ȥ�����з�ʽ
void DFS_Money_MostFun(int, int, int, int, int, int);			//	���޾����ڶ���a������b������Ȥ�����з�ʽ
void DFS_TimeMoney_MostFun(int, int, int, int, int, int, int);	//	DFS�ۺ�6��7������Ѱ��һ���Ӷ���a������b������Ȥ�����з�ʽ
int Dfs_bridge(int, int);										//	��������



/******************** ȫ�ֱ��� ************************/
int n, e;					// �ܳ��и����ͱ���
CityType city[55];			// ���У�����51��
EdgeType graph[55][55];		// �洢�ߵ���Ϣ
StackType S;				// ջ
int flag[52];				// �������
int level;					// ��¼�ݹ����
int g[55][55];				// �ڽӱ����ʽ
BestPathType Good;			// ����·��
int path[55][55];			// ���ÿ�����㵽����һ����������·��
int addfun;					// ��ǰ·����Ȥ��֮��
int addtime;				// ��ǰ·����ʱ֮��
int goway[55];				// ��ǰ���з�ʽ�������ţ�
int best_way[55];			// �������з�ʽ


int main()
{
	int choice;

	init_graph();
	ReadText();

	do {
		choice = in();

		switch (choice)
		{
		case 1:	traver();	break;
		case 2:	Hamilton();	break;
		case 3:	Que_3();	break;
		case 4:	Que_4();	break;
		case 5:	Que_5();	break;
		case 6:	Que_6();	break;
		case 7:	Que_7();	break;
		case 8:	Que_8();	break;
		case 9:	FindBridge();	break;
		case 10:	
			printf("\n\n�Ѱ�ȫ�˳�ϵͳ��\a\n");	break;
		default:	
			printf("\n\n����Ĳ���ָ�\n\a\a\n");
		}

	} while (choice != 10);

	return 0;
}

/******************** ׼������ ************************/
// ������
int in()
{
	int choice;

	for (int i = 0; i < 115; i++)
		printf("��");
	printf("\n\t1��������ͼ������\n");
	printf("\t2������һ��HAMILTON��·\n");
	printf("\t3������һ������ָ����k������Ļ�·��ʹ��һ�ֽ�ͨ��ʽ��ʹ�û�·���ò�����C����Ȥ�����\n");
	printf("\t4������һ���Ӷ���A������B�����·����һ��A��B����Ȥ��·\n");
	printf("\t5������һ���Ӷ���A������B������k����ͬ���㣨���Զ���k�����㣬���������ڣ�����ʱ������C����Ȥ������·��\n");
	printf("\t6���������޵�ʱ�䣨��x�죩�ڣ�Ѱ��һ���Ӷ���a������b������Ȥ���羰����/����棩�����з�ʽ��\n");
	printf("\t7���������޵ľ��ѣ���xԪ���ڣ�Ѱ��һ���Ӷ���a������b������Ȥ���羰����/����棩�����з�ʽ��\n");
	printf("\t8�����ۺ�6��7�����ƣ����ͬ��\n");
	printf("\t9����Ѱ�ҡ��ؽڵ㡱�͡��š�\n");
	printf("\t10������������\n");
	for (int i = 0; i < 115; i++)
		printf("��");
	printf("\n���������ѡ�");
	scanf("%d", &choice);

	return choice;
}

// ʡ����ʾ
void tip()
{
	for (int i = 0; i < 35; i++)
		printf("��");
	printf("\n\t1���㶫ʡ��1-23��\n");
	printf("\t2������ʡ��24-37��\n");
	printf("\t3������ʡ��38-51��\n");
	for (int i = 0; i < 35; i++)
		printf("��");
	printf("\n������ѡ�");
}

// ��ȡ�ļ�
void ReadText()
{
	FILE *fp = fopen("��������.txt", "r");
	int u, v, op;

	printf("���ڴ��ļ�...\n");
	if (fp == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n�����ĵ��Ƿ�������ȷ��·��!\n");
		exit(0);
	}
	printf("�ļ��򿪳ɹ�!\n");
	printf("��ʼ��ȡ�ļ�...\n");
	fscanf(fp, "%d", &n);
	for (int i = 1; i <= n; i++)
		fscanf(fp, "%d%s%s%d", &city[i].id, city[i].name, city[i].from, &city[i].view);
	fscanf(fp, "%d", &e);
	for (int i = 0; i < e; i++)
	{
		fscanf(fp, "%d%d%d", &u, &v, &op);
		graph[u][v].ch = graph[v][u].ch = 1;

		/* �����ڽӱ� */
		bool ch = true;
		// �ж��Ƿ��ظ�
		for (int t = 0; t <= g[u][0]; t++)
		{
			if (v == g[u][t])
				ch = false;
		}
		if (ch == true)
		{
			g[u][0]++;		// �ڽӵ�+1
			g[u][g[u][0]] = v;
			g[v][0]++;		// �ڽӵ�+1
			g[v][g[v][0]] = u;
		}

		switch (op)
		{
		case 1:
			fscanf(fp, "%d%d%d%d", &graph[u][v].air.dig, &graph[u][v].air.cost, &graph[u][v].air.time, &graph[u][v].air.fun);
			graph[v][u].air.dig = graph[u][v].air.dig;
			graph[v][u].air.cost = graph[u][v].air.cost;
			graph[v][u].air.time = graph[u][v].air.time;
			graph[v][u].air.fun = graph[u][v].air.fun;
			graph[u][v].anv = graph[v][u].anv = TheMinLong(u, v);
			break;
		case 2:
			fscanf(fp, "%d%d%d%d", &graph[u][v].train.dig, &graph[u][v].train.cost, &graph[u][v].train.time, &graph[u][v].train.fun);
			graph[v][u].train.dig = graph[u][v].train.dig;
			graph[v][u].train.cost = graph[u][v].train.cost;
			graph[v][u].train.time = graph[u][v].train.time;
			graph[v][u].train.fun = graph[u][v].train.fun;
			graph[u][v].anv = graph[v][u].anv = TheMinLong(u, v);
			break;
		case 3:
			fscanf(fp, "%d%d%d%d", &graph[u][v].car.dig, &graph[u][v].car.cost, &graph[u][v].car.time, &graph[u][v].car.fun);
			graph[v][u].car.dig = graph[u][v].car.dig;
			graph[v][u].car.cost = graph[u][v].car.cost;
			graph[v][u].car.time = graph[u][v].car.time;
			graph[v][u].car.fun = graph[u][v].car.fun;
			graph[u][v].anv = graph[v][u].anv = TheMinLong(u, v);
			break;
		}
	}

	printf("�ļ���ȡ�ɹ�!\n\n");

	fclose(fp);
}

// ͬһ���ߵĽ�ͨ��ʽ��·����С���Ǹ�
int TheMinLong(int u, int v)
{
	int min;

	if (graph[u][v].air.dig != 0 && graph[u][v].train.dig != 0 && graph[u][v].car.dig != 0)
	{
		if (graph[u][v].air.dig <= graph[u][v].train.dig && graph[u][v].air.dig <= graph[u][v].car.dig)
			min = graph[u][v].air.dig;
		else if (graph[u][v].train.dig <= graph[u][v].car.dig)
			min = graph[u][v].train.dig;
		else
			min = graph[u][v].car.dig;
	}
	else if (graph[u][v].air.dig != 0 && graph[u][v].train.dig != 0)
		min = graph[u][v].air.dig < graph[u][v].train.dig ? graph[u][v].air.dig : graph[u][v].train.dig;
	else if (graph[u][v].train.dig != 0 && graph[u][v].car.dig != 0)
		min = graph[u][v].train.dig < graph[u][v].car.dig ? graph[u][v].train.dig : graph[u][v].car.dig;
	else if (graph[u][v].air.dig != 0 && graph[u][v].car.dig != 0)
		min = graph[u][v].air.dig < graph[u][v].car.dig ? graph[u][v].air.dig : graph[u][v].car.dig;
	else if (graph[u][v].air.dig != 0)
		min = graph[u][v].air.dig;
	else if (graph[u][v].train.dig != 0)
		min = graph[u][v].train.dig;
	else
		min = graph[u][v].car.dig;

	return min;
}

// ͬһ���ߵĽ�ͨ��ʽ��ʱ����С���Ǹ�
int TheMinMoney(int u, int v)
{
	int min;

	if (graph[u][v].air.cost != 0 && graph[u][v].train.cost != 0 && graph[u][v].car.cost != 0)
	{
		if (graph[u][v].air.cost <= graph[u][v].train.cost && graph[u][v].air.cost <= graph[u][v].car.cost)
			min = graph[u][v].air.cost;
		else if (graph[u][v].train.cost <= graph[u][v].car.cost)
			min = graph[u][v].train.cost;
		else
			min = graph[u][v].car.cost;
	}
	else if (graph[u][v].air.cost != 0 && graph[u][v].train.cost != 0)
		min = graph[u][v].air.cost < graph[u][v].train.cost ? graph[u][v].air.cost : graph[u][v].train.cost;
	else if (graph[u][v].train.cost != 0 && graph[u][v].car.cost != 0)
		min = graph[u][v].train.cost < graph[u][v].car.cost ? graph[u][v].train.cost : graph[u][v].car.cost;
	else if (graph[u][v].air.cost != 0 && graph[u][v].car.cost != 0)
		min = graph[u][v].air.cost < graph[u][v].car.cost ? graph[u][v].air.cost : graph[u][v].car.cost;
	else if (graph[u][v].air.cost != 0)
		min = graph[u][v].air.cost;
	else if (graph[u][v].train.cost != 0)
		min = graph[u][v].train.cost;
	else
		min = graph[u][v].car.cost;

	return min;
}

// ��ʼ��ͼ
void init_graph()
{
	for (int i = 0; i < 55; i++)
	{
		for (int j = 0; j < 55; j++)
		{
			graph[i][j].ch = 0;
			// �ɻ�
			graph[i][j].air.cost = 0;
			graph[i][j].air.dig = 0;
			graph[i][j].air.fun = 0;
			graph[i][j].air.time = 0;
			// ��
			graph[i][j].train.cost = 0;
			graph[i][j].train.dig = 0;
			graph[i][j].train.fun = 0;
			graph[i][j].train.time = 0;
			// С��
			graph[i][j].car.cost = 0;
			graph[i][j].car.dig = 0;
			graph[i][j].car.fun = 0;
			graph[i][j].car.time = 0;
			graph[i][j].anv = 0;

			if (i != j)
				graph[i][j].anv = 99999;	// ��ʾ����վ��֮��û������
			else
				graph[i][j].anv = 0;
			path[i][j] = -1;				// -1��ʾ���辭���м�� 
		}
	}
}

// �ı�ʡ��
void Change_pro(int op, int & xia, int & shang)
{
	switch (op)
	{
	case 1:
		xia = 1;	shang = 23;	break;
	case 2:
		xia = 24;	shang = 37;	break;
	case 3:
		xia = 38;	shang = 51;	break;
	}
}

// ��ʼ���������
void init_flag()
{
	for (int i = 0; i < 52; i++)
		flag[i] = 0;
}

// ��ʼ��������Ҫ�õ��Ľṹ
int dfs_clock;					// dfsʱ���
int pre[55], low[55];			// pre�Ǽ�¼ʱ��������飬low[u]��ʾu�Լ�u������������������������
bool iscut[55];					// ����i�Ƿ�Ϊ���
int len_bridge;
BridgeType bridge[55];			// �洢ͼ�е���
void init_bridge()
{
	dfs_clock = 0;
	memset(pre, 0, sizeof(pre));
	memset(low, 0, sizeof(low));
	memset(iscut, 0, sizeof(iscut));
	for (int i = 0; i < 52; i++)
		for (int j = 0; j < 52; j++)
			g[i][j] = 0;
	for (int i = 0; i < 52; ++i)
	{
		bridge[i].u = 0;
		bridge[i].v = 0;
	}

	len_bridge = 0;
}

// �ж�·�����Ƿ��Ѱ���ָ����k������
int way[30];		// ��0λ���k������	
bool is_all()
{
	int num = 0;

	for (int i = 1; i <= S.top; i++)
		for (int k = 1; k <= way[0]; k++)
		{
			if (S.dis[i] == way[k])
				num++;
		}

	if (num == way[0])
		return true;
	else
		return false;
}

// ��ʼ������·��
void init_Good()
{
	Good.adddis = 0;
	Good.addfun = 0;
	Good.addmoney = 0;
	Good.addtime = 0;
	Good.len = 0;
}

// ��ʼ���������з�ʽ
void init_bestway()
{
	for (int i = 0; i < 55; i++)
	{
		goway[i] = 0;
		best_way[i] = 0;
	}
}


/********************  ջ����  ************************/
// ��ջ
void push(int ch)
{
	S.top++;
	S.dis[S.top] = ch;
}

// ��ջ
int pop()
{
	return S.dis[S.top--];
}


/******************** ���ܺ��� ************************/
//	1�������������
void traver()
{
	printf("\n");
	printf("------------------------------------------------------\n");
	printf("����id\t��������\t����ʡ��\t��Ȥ��\n");
	printf("------------------------------------------------------\n");
	for (int i = 1; i <= n; i++)
		printf("%4d\t%s\t\t%s\t\t%4d\n", city[i].id, city[i].name, city[i].from, city[i].view);
	printf("------------------------------------------------------------------------------------------------------------------\n");
	printf("�������\tĿ����\t��ͨ��ʽ\t·��(km)\t��ʱ(h)\t\t����(Ԫ)\t��Ȥ��\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 1; i <= n; i++)
	{
		for (int k = 1; k <= n; k++)
		{
			if (graph[i][k].air.dig != 0)
				printf("%4d\t\t%4d\t\t  �ɻ�\t\t%4d\t\t%.2lf\t\t%4d\t\t%4d\n", i, k, graph[i][k].air.dig, (double)graph[i][k].air.time/10, graph[i][k].air.cost, graph[i][k].air.fun);
			if (graph[i][k].train.dig != 0)
				printf("%4d\t\t%4d\t\t  ��\t\t%4d\t\t%.2lf\t\t%4d\t\t%4d\n", i, k, graph[i][k].train.dig, (double)graph[i][k].train.time/10, graph[i][k].train.cost, graph[i][k].train.fun);
			if (graph[i][k].car.dig != 0)
				printf("%4d\t\t%4d\t\t  �ݳ�\t\t%4d\t\t%.2lf\t\t%4d\t\t%4d\n", i, k, graph[i][k].car.dig, (double)graph[i][k].car.time/10, graph[i][k].car.cost, graph[i][k].car.fun);
		}
	}
}

//	2����һ�����ܶٻ�·
int fl;
void Hamilton()
{
	int op;
	int low, hi, citynum;
	int start;

	level = 0;			// ·�������ʼ����Ϊ0
	S.top = 0;			// ��ʼ��ջ��
	fl = 0;
	tip();
	init_flag();
	scanf("%d", &op);
	Change_pro(op, low, hi);
	citynum = hi - low + 1;
	printf("������������У�%d-%d����", low, hi);
	scanf("%d", &start);
	push(start);
	flag[start] = 1;
	DFS_Hamilton(start, start, low, hi, citynum);
	if (fl == 0)
		printf("��%d�ų��г�������ʡ��û�й��ܶٻ�·\n\n\a", start);
}

//	3�����������Ҿ���ָ��k������Ļ�·
int add_fun;
int add_money;
int min_money;
void Que_3()
{
	int op;
	int low, hi, citynum;
	int start;
	int traff;

	init_Good();		// ��ʼ������·��
	level = 0;			// �ݹ����
	S.top = 0;			// ��ʼ��ջ����0Ϊջ��
	add_fun = add_money = 0;
	tip();
	init_flag();
	scanf("%d", &op);
	Change_pro(op, low, hi);
	citynum = hi - low + 1;
	printf("��������Ҫ�����Ķ���ĸ�����");
	scanf("%d", &way[0]);
	printf("���������� %d �����㣨%d - %d����", way[0], low, hi);
	for (int i = 1; i <= way[0]; i++)
		scanf("%d", &way[i]);
	printf("������Ԥ�㣨Ԫ����");
	scanf("%d", &min_money);
	printf("������������еı�ţ�%d - %d����", low, hi);
	scanf("%d", &start);
	printf("��ѡ��ͨ��ʽ��1--�ɻ���2--�𳵣�3--�ݳ�����");
	scanf("%d", &traff);
	push(start);
	flag[start] = 1;

	DFS_MostFun(start, start, low, hi, citynum, traff);

	// ��������·��
	if (Good.len != 0)
	{
		printf("\n�ɹ��ҵ�����·����\n\n");
		for (int i = 1; i <= Good.len; i++)
			printf("%d ->", Good.best_path[i]);
		printf("%d\n\n", start);
		printf("��·��Ԥ�㣨Ԫ����%d\n", Good.addmoney);
		printf("��·����Ȥ�ȣ�%d\n\n", Good.addfun);
	}
	else
		printf("\nû������������·����\n\n");

}

//	4����A��B�����·������Ȥ��·
void Que_4()
{
	int A, B;			// ����AΪ�����㣬BΪĿ���
	int op;
	int low, hi, citynum;

	init_Good();		// ��ʼ������·��
	level = 0;			// �ݹ����
	S.top = 0;			// ��ʼ��ջ����0Ϊջ��
	addfun = 0;
	tip();
	init_flag();
	scanf("%d", &op);
	Change_pro(op, low, hi);
	citynum = hi - low + 1;
	printf("����������㣺");
	scanf("%d", &A);
	printf("������Ŀ��㣺");
	scanf("%d", &B);
	
	Floyd_Warshall();			// �����·��
	if (graph[A][B].anv == 99999)
	{
		printf("\n%d�޷�����%d��\a\n\n", A, B);
	}
	// ����ɴ�������֮������·���Լ������ĳ��� 
	else
	{
		printf("\n%d����%d�����·��Ϊ %d km\n\n", A, B, graph[A][B].anv);		// ����������е����·�� 
		printf("�����ĳ��б�����£�\n\n\t");
		traverse(A, B);															// �����������·��֮���վ��
		printf("%d\n", B);														// ����յ�
		printf("\n");
	}

	push(A);
	flag[A] = 1;

	DFS_fun(A, B, low, hi, citynum);

	// ��������Ȥ��·��
	if (Good.len != 0)
	{
		printf("\n�ɹ��ҵ�����Ȥ��·����\n\n\t");
		for (int i = 1; i < Good.len; i++)
			printf("%d ->", Good.best_path[i]);
		printf("%d\n\n", Good.best_path[Good.len]);
		printf("��·����Ȥ��Ϊ��%d\n\n", Good.addfun);
	}
	else
		printf("\nû������������·����\n\n");
}

//	Floyd_Warshall�㷨�������������С·��
void Floyd_Warshall()
{
	int i, j, k;		// �м���� 

	//  Floyd_Warshall�����㷨 
	for (k = 1; k <= 51; k++)
		for (i = 1; i <= 51; i++)
			for (j = 1; j <= 51; j++)
			{
				// �����˸���С��·�� 
				if (graph[i][j].anv > graph[i][k].anv + graph[k][j].anv)
				{
					graph[i][j].anv = graph[i][k].anv + graph[k][j].anv;		// ����·�� 
					path[i][j] = k;			// ����м�վ��
				}
			}
}

//	�ݹ����u��v�����·���� 
void traverse(int u, int v)
{
	// �ݹ��յ�
	if (path[u][v] == -1)
	{
		printf("%d ->", u);
		return;
	}
	// ��������ݹ����·��վ��
	int mid = path[u][v];
	traverse(u, mid);
	traverse(mid, v);
}

//	5��A��B����k����ͬ���㣨���Զ���k�����㣬���������ڣ�����ʱ������C����Ȥ������·��
void Que_5()
{
	int A, B;			// ����AΪ�����㣬BΪĿ���
	int op, k;
	int low, hi, citynum;
	int mostlong;

	init_Good();		// ��ʼ������·��
	level = 0;			// �ݹ����
	S.top = 0;			// ��ʼ��ջ����0Ϊջ��
	addfun = 0;
	addtime = 0;
	tip();
	init_flag();
	scanf("%d", &op);
	Change_pro(op, low, hi);
	citynum = hi - low + 1;
	printf("����������㣺");
	scanf("%d", &A);
	printf("������Ŀ��㣺");
	scanf("%d", &B);
	printf("���������پ����Ķ���������");
	scanf("%d", &k);
	printf("��������Խ��ܵ��ʱ��(Сʱ)��");
	scanf("%d", &mostlong);
	mostlong *= 10;

	push(A);
	flag[A] = 1;

	DFS_K_MostFun(A, B, low, hi, citynum, mostlong, k);

	// ��������Ȥ��·��
	if (Good.len != 0)
	{
		printf("\n�ɹ��ҵ�����Ȥ��·����\n\n\t");
		for (int i = 1; i < Good.len; i++)
			printf("%d ->", Good.best_path[i]);
		printf("%d\n\n", Good.best_path[Good.len]);
		printf("��·����Ȥ�ȣ�%d\n\n", Good.addfun);
		printf("��·��ʱ�䣺%.1lf��h��\n\n", Good.addtime/10.0);
		printf("%d��%d�����Ķ�����Ϊ��%d\n\n", A, B, Good.len-2);
	}
	else
		printf("\nû������������·����\n\n");
}

//	6�����޵�ʱ�䣨��x�죩�ڣ�Ѱ��һ���Ӷ���a������b������Ȥ�����з�ʽ
void Que_6()
{
	int A, B;			// ����AΪ�����㣬BΪĿ���
	int op;
	int low, hi, citynum;
	int mostlong;

	init_Good();		// ��ʼ������·��
	init_bestway();		// ��ʼ�����з�ʽ
	level = 0;			// �ݹ����
	S.top = 0;			// ��ʼ��ջ����0Ϊջ��
	addfun = 0;
	addtime = 0;
	tip();
	init_flag();
	scanf("%d", &op);
	Change_pro(op, low, hi);
	citynum = hi - low + 1;
	printf("����������㣺");
	scanf("%d", &A);
	printf("������Ŀ��㣺");
	scanf("%d", &B);
	printf("��������Խ��ܵ��ʱ��(��)��");
	scanf("%d", &mostlong);
	mostlong *= (24 * 10);

	push(A);
	flag[A] = 1;

	DFS_Time_MostFun(A, B, low, hi, citynum, mostlong);

	// ��������Ȥ��·��
	if (Good.len != 0)
	{
		printf("\n�ɹ��ҵ�%d��������Ȥ�����з�ʽ��\n\n  ", mostlong/24/10);
		for (int i = 1; i < Good.len; i++)
		{
			printf("%d-", Good.best_path[i]);
			switch (best_way[i])
			{
			case 1:
				printf("air->");	break;
			case 2:
				printf("train->");	break;
			case 3:
				printf("car->");	break;
			default:
				break;
			}
		}
			
		printf("%d\n\n", Good.best_path[Good.len]);
		printf("�����з�ʽ��Ȥ�ȣ�%d\n\n", Good.addfun);
		printf("�����з�ʽʱ�䣺%.1lf��h��\n\n", Good.addtime / 10.0);
	}
	else
		printf("\nû������������·����\n\n");
}

//	7�����޵ľ��ѣ���xԪ���ڣ�Ѱ��һ���Ӷ���a������b������Ȥ�����з�ʽ
int addmoney;
void Que_7()
{
	int A, B;			// ����AΪ�����㣬BΪĿ���
	int op;
	int low, hi, citynum;
	int mostmoney;

	init_bestway();		// ��ʼ�����з�ʽ
	init_Good();		// ��ʼ������·��
	level = 0;			// �ݹ����
	S.top = 0;			// ��ʼ��ջ����0Ϊջ��
	addfun = 0;
	addmoney = 0;
	tip();
	init_flag();
	scanf("%d", &op);
	Change_pro(op, low, hi);
	citynum = hi - low + 1;
	printf("����������㣺");
	scanf("%d", &A);
	printf("������Ŀ��㣺");
	scanf("%d", &B);
	printf("������Ԥ��(Ԫ)��");
	scanf("%d", &mostmoney);

	push(A);
	flag[A] = 1;

	DFS_Money_MostFun(A, B, low, hi, citynum, mostmoney);

	// ��������Ȥ��·��
	if (Good.len != 0)
	{
		printf("\n�ɹ��ҵ� %d Ԫ������Ȥ�����з�ʽ��\n\n  ", mostmoney);
		for (int i = 1; i < Good.len; i++)
		{
			printf("%d-", Good.best_path[i]);
			switch (best_way[i])
			{
			case 1:
				printf("air->");	break;
			case 2:
				printf("train->");	break;
			case 3:
				printf("car->");	break;
			}
		}

		printf("%d\n\n", Good.best_path[Good.len]);
		printf("�����з�ʽ��Ȥ�ȣ�%d\n\n", Good.addfun);
		printf("�����з�ʽ���� %d Ԫ\n\n", Good.addmoney);
	}
	else
		printf("\nû������������·����\n\n");
}

//	8���ۺ�6��7�����ƣ����ͬ��
void Que_8()
{
	int A, B;			// ����AΪ�����㣬BΪĿ���
	int op;
	int low, hi, citynum;
	int mostmoney;
	int mostlong;

	init_Good();		// ��ʼ������·��
	init_bestway();		// ��ʼ�����з�ʽ
	level = 0;			// �ݹ����
	S.top = 0;			// ��ʼ��ջ����0Ϊջ��
	addfun = 0;
	addmoney = 0;
	tip();
	init_flag();
	scanf("%d", &op);
	Change_pro(op, low, hi);
	citynum = hi - low + 1;
	printf("����������㣺");
	scanf("%d", &A);
	printf("������Ŀ��㣺");
	scanf("%d", &B);
	printf("��������Խ��ܵ��ʱ��(��)��");
	scanf("%d", &mostlong);
	mostlong *= (24 * 10);
	printf("������Ԥ��(Ԫ)��");
	scanf("%d", &mostmoney);

	push(A);
	flag[A] = 1;

	DFS_TimeMoney_MostFun(A, B, low, hi, citynum, mostlong, mostmoney);

	// ��������Ȥ��·��
	if (Good.len != 0)
	{
		printf("\n�ɹ��ҵ� %d Сʱ�� %d Ԫ������Ȥ�����з�ʽ��\n\n  ", mostlong / 24 / 10, mostmoney);
		for (int i = 1; i < Good.len; i++)
		{
			printf("%d-", Good.best_path[i]);
			switch (best_way[i])
			{
			case 1:
				printf("air->");	break;
			case 2:
				printf("train->");	break;
			case 3:
				printf("car->");	break;
			}
		}

		printf("%d\n\n", Good.best_path[Good.len]);
		printf("�����з�ʽ��Ȥ�ȣ�%d\n\n", Good.addfun);
		printf("�����з�ʽ���� %d Ԫ\n\n", Good.addmoney);
		printf("�����з�ʽ��ʱ %.1lf ʱ\n\n", Good.addtime / 10.0);
	}
	else
		printf("\nû������������·����\n\n");
}

//	�ҹؽڵ����
void FindBridge()
{
	printf("\n\n-----�ؽڵ�-----\n");
	for (int i = 1; i <= 51; i++)
	{
		if (g[i][0] != 0 && 0 == pre[i])
		{
			Dfs_bridge(i, -1);
		}

	}

	for (int i = 1; i <= n; ++i) {
		if (iscut[i])
			printf("       %d\n", i);
	}
	printf("\n");
	printf("\n-------��-------\n");
	for (int i = 1; i <= len_bridge; ++i) {
		printf("    %d -- %d\n", bridge[i].u, bridge[i].v);
	}
}


/********************** DFS **************************/
//	2��DFS���ܶ�
void DFS_Hamilton(int start, int cur, int low, int hi, int citynum)
{
	level++;
	if (level == citynum)
	{
		// ·���������е㲢���ܹ����ɻ�·
		if (graph[cur][start].ch != 0 && fl == 0)
		{
			printf("\n�ɹ��ҵ�һ�����ܶٻ�·��\n\n\t");
			for (int i = 1; i <= S.top; i++)
				printf("%d ->", S.dis[i]);
			printf("%d\n\n", start);
			fl = 1;
		}

		return;
	}

	for (int i = low; i <= hi; i++)
	{
		if (graph[cur][i].ch == 1 && flag[i] == 0)
		{
			flag[i] = 1;
			push(i);
			DFS_Hamilton(start, i, low, hi, citynum);
			int ls = pop();
			level--;
			flag[i] = 0;
		}

	}
}

//	3��DFS����������ָ��k������Ļ�·
void DFS_MostFun(int start, int cur, int low, int hi, int citynum, int traff)
{
	level++;

	switch (traff)
	{
	case 1:
		// ָ���Ķ�����ָ��Ԥ������ȫ�������ҹ��ɻ�·������£���Ȥ�ȱ�����·���Ĵ󣬸�������·��
		if (is_all() && graph[S.dis[S.top]][start].air.dig != 0 && add_fun > Good.addfun)
		{
			if ((add_money + graph[S.dis[S.top]][start].air.cost) > min_money)
				break;
			else
				add_money += graph[S.dis[S.top]][start].air.cost;
			for (int i = 1; i <= S.top; i++)
				Good.best_path[i] = S.dis[i];
			Good.addfun = add_fun;
			Good.addmoney = add_money;
			Good.len = S.top;
		}
		break;
	case 2:
		if (is_all() && graph[S.dis[S.top]][start].train.dig != 0 && add_fun > Good.addfun)
		{
			if ((add_money + graph[S.dis[S.top]][start].train.cost) > min_money)
				break;
			else
				add_money += graph[S.dis[S.top]][start].train.cost;
			for (int i = 1; i <= S.top; i++)
				Good.best_path[i] = S.dis[i];
			Good.addfun = add_fun;
			Good.addmoney = add_money;
			Good.len = S.top;
		}
		break;
	case 3:
		if (is_all() && graph[S.dis[S.top]][start].car.dig != 0 && add_fun > Good.addfun)
		{
			if ((add_money + graph[S.dis[S.top]][start].car.cost) > min_money)
				break;
			else
				add_money += graph[S.dis[S.top]][start].car.cost;
			for (int i = 1; i <= S.top; i++)
				Good.best_path[i] = S.dis[i];
			Good.addfun = add_fun;
			Good.addmoney = add_money;
			Good.len = S.top;
		}
		break;
	default:
		break;
	}

	if (add_money > min_money || level >= citynum)		// ����Ԥ����ߴﵽ�ݹ��յ�
		return;

	for (int i = low; i <= hi; i++)
	{
		switch (traff)
		{
		case 1:
			if (graph[cur][i].air.dig != 0 && flag[i] == 0)
			{
				add_fun += graph[cur][i].air.fun;		// ���µ�ǰ��Ȥ���ܺ�
				add_money += graph[cur][i].air.cost;	// ���µ�ǰ�����ܺ�
				flag[i] = 1;
				push(i);
				DFS_MostFun(start, i, low, hi, citynum, traff);
				int ls = pop();
				add_fun -= graph[cur][i].air.fun;		// ���µ�ǰ��Ȥ���ܺ�
				add_money -= graph[cur][i].air.cost;	// ���µ�ǰ�����ܺ�
				level--;
				flag[i] = 0;
			}
			break;
		case 2:
			if (graph[cur][i].train.dig != 0 && flag[i] == 0)
			{
				add_fun += graph[cur][i].train.fun;		// ���µ�ǰ��Ȥ���ܺ�
				add_money += graph[cur][i].train.cost;	// ���µ�ǰ�����ܺ�
				flag[i] = 1;
				push(i);
				DFS_MostFun(start, i, low, hi, citynum, traff);
				int ls = pop();
				add_fun -= graph[cur][i].train.fun;		// ���µ�ǰ��Ȥ���ܺ�
				add_money -= graph[cur][i].train.cost;	// ���µ�ǰ�����ܺ�
				level--;
				flag[i] = 0;
			}
			break;
		case 3:
			if (graph[cur][i].car.dig != 0 && flag[i] == 0)
			{
				add_fun += graph[cur][i].car.fun;		// ���µ�ǰ��Ȥ���ܺ�
				add_money += graph[cur][i].car.cost;	// ���µ�ǰ�����ܺ�
				flag[i] = 1;
				push(i);
				DFS_MostFun(start, i, low, hi, citynum, traff);
				int ls = pop();
				add_fun -= graph[cur][i].car.fun;		// ���µ�ǰ��Ȥ���ܺ�
				add_money -= graph[cur][i].car.cost;	// ���µ�ǰ�����ܺ�
				level--;
				flag[i] = 0;
			}
			break;
		}

	}
}

//	4��DFS����Ȥ��·
void DFS_fun(int cur, int aim, int low, int hi, int citynum)
{
	level++;
	// ��ǰ·����Ȥ��֮���ѳ�������·������Ȥ��
	if (cur == aim && addfun > Good.addfun)
	{
		for (int i = 1; i <= S.top; i++)
			Good.best_path[i] = S.dis[i];
		Good.addfun = addfun;
		Good.len = S.top;

		return;
	}
	if (level == citynum)
		return;

	for (int i = low; i <= hi; i++)
	{
		if (graph[cur][i].ch == 1 && flag[i] == 0)
		{
			if (graph[cur][i].train.fun > graph[cur][i].car.fun)
				addfun += graph[cur][i].train.fun;
			else
				addfun += graph[cur][i].car.fun;

			flag[i] = 1;
			push(i);
			DFS_fun(i, aim, low, hi, citynum);
			int ls = pop();
			if (graph[cur][i].train.fun > graph[cur][i].car.fun)
				addfun -= graph[cur][i].train.fun;
			else
				addfun -= graph[cur][i].car.fun;
			level--;
			flag[i] = 0;
		}

	}
}

//	5��DFS����k����ͬ���㣨���Զ���k�����㣬���������ڣ�����ʱ������C����Ȥ������·��
void DFS_K_MostFun(int cur, int aim, int low, int hi, int citynum, int mostlong, int k)
{
	level++;
	
	// ��ǰ·����Ȥ��֮���ѳ�������·������Ȥ��
	if (addtime <= mostlong && S.top >= k + 2 && cur == aim && addfun > Good.addfun)
	{
		for (int i = 1; i <= S.top; i++)
			Good.best_path[i] = S.dis[i];
		Good.addfun = addfun;
		Good.len = S.top;
		Good.addtime = addtime;

		return;
	}
	if (level == citynum)
		return;

	for (int i = low; i <= hi; i++)
	{
		if (graph[cur][i].ch == 1 && flag[i] == 0)
		{
			if (graph[cur][i].train.fun > graph[cur][i].car.fun)
			{
				addfun += graph[cur][i].train.fun;
				addtime += graph[cur][i].train.time;
			}
			else
			{
				addfun += graph[cur][i].car.fun;
				addtime += graph[cur][i].car.time;
			}

			flag[i] = 1;
			push(i);
			DFS_K_MostFun(i, aim, low, hi, citynum, mostlong, k);
			int ls = pop();
			if (graph[cur][i].train.fun > graph[cur][i].car.fun)
			{
				addfun -= graph[cur][i].train.fun;
				addtime -= graph[cur][i].train.time;
			}
			else
			{
				addfun -= graph[cur][i].car.fun;
				addtime -= graph[cur][i].car.time;
			}
				
			level--;
			flag[i] = 0;
		}

	}
}

//	6��DFS���޵�ʱ�䣨��x�죩�ڣ�Ѱ��һ���Ӷ���a������b������Ȥ�����з�ʽ
void DFS_Time_MostFun(int cur, int aim, int low, int hi, int citynum, int mostlong)
{
	level++;

	// ��ǰ·����Ȥ��֮���ѳ�������·������Ȥ��
	if (addtime <= mostlong && cur == aim && addfun > Good.addfun)
	{
		for (int i = 1; i <= S.top; i++)
			Good.best_path[i] = S.dis[i];
		for (int i = 1; i < S.top; i++)
			best_way[i] = goway[i];
		Good.addfun = addfun;
		Good.len = S.top;
		Good.addtime = addtime;

		return;
	}
	if (level == citynum)
		return;

	for (int i = low; i <= hi; i++)
	{
		if (graph[cur][i].ch == 1 && flag[i] == 0)
		{
			if (graph[cur][i].car.fun != 0 && graph[cur][i].train.fun > graph[cur][i].car.fun || graph[cur][i].train.fun == 0 && graph[cur][i].car.fun != 0)
			{
				addfun += graph[cur][i].train.fun;
				addtime += graph[cur][i].train.time;
				goway[S.top] = 2;
			}
			else if (graph[cur][i].train.fun != 0 && graph[cur][i].train.fun <= graph[cur][i].car.fun || graph[cur][i].train.fun != 0 && graph[cur][i].car.fun == 0)
			{
				addfun += graph[cur][i].car.fun;
				addtime += graph[cur][i].car.time;
				goway[S.top] = 3;
			}
			else
			{
				addtime += graph[cur][i].air.time;
				goway[S.top] = 1;
			}

			flag[i] = 1;
			push(i);
			DFS_Time_MostFun(i, aim, low, hi, citynum, mostlong);
			int ls = pop();
			if (graph[cur][i].car.fun != 0 && graph[cur][i].train.fun > graph[cur][i].car.fun || graph[cur][i].train.fun == 0 && graph[cur][i].car.fun != 0)
			{
				addfun -= graph[cur][i].train.fun;
				addtime -= graph[cur][i].train.time;
			}
			else if (graph[cur][i].train.fun != 0 && graph[cur][i].train.fun <= graph[cur][i].car.fun || graph[cur][i].train.fun != 0 && graph[cur][i].car.fun == 0)
			{
				addfun -= graph[cur][i].car.fun;
				addtime -= graph[cur][i].car.time;
			}
			else
			{
				addtime -= graph[cur][i].air.time;
			}
			goway[S.top] = 0;
			level--;
			flag[i] = 0;
		}

	}
}

//	7��DFS���޵ľ��ѣ���xԪ���ڣ�Ѱ��һ���Ӷ���a������b������Ȥ�����з�ʽ
void DFS_Money_MostFun(int cur, int aim, int low, int hi, int citynum, int mostmoney)
{
	level++;

	// ��ǰ·����Ȥ��֮���ѳ�������·������Ȥ��
	if (addmoney <= mostmoney && cur == aim && addfun > Good.addfun)
	{
		for (int i = 1; i <= S.top; i++)
			Good.best_path[i] = S.dis[i];
		for (int i = 1; i < S.top; i++)
			best_way[i] = goway[i];
		Good.addfun = addfun;
		Good.len = S.top;
		Good.addmoney = addmoney;

		return;
	}
	if (level == citynum)
		return;

	for (int i = low; i <= hi; i++)
	{
		if (graph[cur][i].ch == 1 && flag[i] == 0)
		{
			if (graph[cur][i].car.fun != 0 && graph[cur][i].train.fun > graph[cur][i].car.fun || graph[cur][i].train.fun == 0 && graph[cur][i].car.fun != 0)
			{
				addfun += graph[cur][i].train.fun;
				addmoney += graph[cur][i].train.cost;
				goway[S.top] = 2;
			}
			else if (graph[cur][i].train.fun != 0 && graph[cur][i].train.fun <= graph[cur][i].car.fun || graph[cur][i].train.fun != 0 && graph[cur][i].car.fun == 0)
			{
				addfun += graph[cur][i].car.fun;
				addmoney += graph[cur][i].car.cost;
				goway[S.top] = 3;
			}
			else
			{
				addmoney += graph[cur][i].air.cost;
				goway[S.top] = 1;
			}
				
			flag[i] = 1;
			push(i);
			DFS_Money_MostFun(i, aim, low, hi, citynum, mostmoney);
			int ls = pop();
			if (graph[cur][i].car.fun != 0 && graph[cur][i].train.fun > graph[cur][i].car.fun || graph[cur][i].train.fun == 0 && graph[cur][i].car.fun != 0)
			{
				addfun -= graph[cur][i].train.fun;
				addmoney -= graph[cur][i].train.cost;
			}
			else if (graph[cur][i].train.fun != 0 && graph[cur][i].train.fun <= graph[cur][i].car.fun || graph[cur][i].train.fun != 0 && graph[cur][i].car.fun == 0)
			{
				addfun -= graph[cur][i].car.fun;
				addmoney -= graph[cur][i].car.cost;
			}
			else
			{
				addmoney -= graph[cur][i].air.cost;
			}
			goway[S.top] = 0;
			level--;
			flag[i] = 0;
		}

	}
}

//	8��DFS�ۺ�6��7������Ѱ��һ���Ӷ���a������b������Ȥ�����з�ʽ
void DFS_TimeMoney_MostFun(int cur, int aim, int low, int hi, int citynum, int mostlong, int mostmoney)
{
	level++;

	// ��ǰ·����Ȥ��֮���ѳ�������·������Ȥ��
	if (addfun > Good.addfun && addtime <= mostlong && addmoney <= mostmoney && cur == aim)
	{
		for (int i = 1; i <= S.top; i++)
			Good.best_path[i] = S.dis[i];
		for (int i = 1; i < S.top; i++)
			best_way[i] = goway[i];
		Good.addfun = addfun;
		Good.len = S.top;
		Good.addtime = addtime;
		Good.addmoney = addmoney;

		return;
	}
	if (level == citynum)
		return;

	for (int i = low; i <= hi; i++)
	{
		if (graph[cur][i].ch == 1 && flag[i] == 0)
		{
			if (graph[cur][i].car.fun != 0 && graph[cur][i].train.fun > graph[cur][i].car.fun || graph[cur][i].train.fun == 0 && graph[cur][i].car.fun != 0)
			{
				addfun += graph[cur][i].train.fun;
				addtime += graph[cur][i].train.time;
				addmoney += graph[cur][i].train.cost;
				goway[S.top] = 2;
			}
			else if (graph[cur][i].train.fun != 0 && graph[cur][i].train.fun <= graph[cur][i].car.fun || graph[cur][i].train.fun != 0 && graph[cur][i].car.fun == 0)
			{
				addfun += graph[cur][i].car.fun;
				addtime += graph[cur][i].car.time;
				addmoney += graph[cur][i].car.cost;
				goway[S.top] = 3;
			}
			else
			{
				addtime += graph[cur][i].air.time;
				addmoney += graph[cur][i].air.cost;
				goway[S.top] = 1;
			}

			flag[i] = 1;
			push(i);
			DFS_TimeMoney_MostFun(i, aim, low, hi, citynum, mostlong, mostmoney);
			int ls = pop();
			if (graph[cur][i].car.fun != 0 && graph[cur][i].train.fun > graph[cur][i].car.fun || graph[cur][i].train.fun == 0 && graph[cur][i].car.fun != 0)
			{
				addfun -= graph[cur][i].train.fun;
				addtime -= graph[cur][i].train.time;
				addmoney -= graph[cur][i].train.cost;
			}
			else if (graph[cur][i].train.fun != 0 && graph[cur][i].train.fun <= graph[cur][i].car.fun || graph[cur][i].train.fun != 0 && graph[cur][i].car.fun == 0)
			{
				addfun -= graph[cur][i].car.fun;
				addtime -= graph[cur][i].car.time;
				addmoney -= graph[cur][i].car.cost;
			}
			else
			{
				addtime -= graph[cur][i].air.time;
				addmoney -= graph[cur][i].air.cost;
			}
			goway[S.top] = 0;
			level--;
			flag[i] = 0;
		}

	}
}

//	9��DFS��
int Dfs_bridge(int u, int fa)
{
	int lowu = pre[u] = ++dfs_clock;
	int child = 0;				// �ӽڵ����

	for (int i = 1; i <= g[u][0]; ++i) {
		int v = g[u][i];
		if (0 == pre[v])
		{
			++child;
			int lowv = Dfs_bridge(v, u);
			if (lowu > lowv)
				lowu = lowv;
			if (lowv >= pre[u]) {
				iscut[u] = true;					// ���
				if (lowv > pre[u])
				{
					// ��
					len_bridge++;
					bridge[len_bridge].u = u;
					bridge[len_bridge].v = v;

				}
			}
		}
		else if (pre[v] < pre[u] && v != fa) {		// �����(u,v)
			if (lowu > pre[v])
				lowu = pre[v];
		}
	}
	if (fa < 0 && child == 1)
		iscut[u] = false;//�жϸ����
	low[u] = lowu;

	return lowu;
}
