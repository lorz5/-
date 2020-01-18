/*
	18科技一班
	张浩杰
	201824111141
*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/******************** 数据结构 ************************/
// 城市信息
typedef struct City_Type {
	int id;
	char name[20];
	char from[20];
	int view;
}CityType;

// 交通信息
typedef struct Tra_Type {
	int dig;				// 距离
	int time;				// 耗时
	int cost;				// 花费
	int fun;				// 有趣度
}TraType;

// 边的信息
typedef struct Edge_Type {
	// 基本信息
	int ch;					// 表示是否存在交通方式，1为有，2为否
	TraType air;			// 该边的飞机作为交通的信息
	TraType train;			// 该边的火车作为交通的信息
	TraType car;			// 该边的小车作为交通的信息
	// 扩充信息
	int anv;				// 用于Floyd_Warshall算法求任意两点间的最短路径
}EdgeType;

// 栈结构
typedef struct Stack_Type {
	int dis[52];
	int top;
}StackType;

// 路径信息
typedef struct BestPath_Type {
	int best_path[55];
	int len;
	int adddis;			// 最优路劲的路程
	int addtime;		// 最优路劲的耗时
	int addmoney;		// 最优路劲的花费
	int addfun;			// 最优路劲的有趣度
}BestPathType;

// 桥的数据类型 
typedef struct Bridge_Type {
	int u;
	int v;
}BridgeType;


/******************** 函数声明 ************************/
// 前期准备
int in();							// 主界面
void tip();							// 省份提示
void ReadText();					// 读取文件
int TheMinLong(int, int);			// 同一条边的交通方式中路程最小的那个
int TheMinMoney(int, int);			// 同一条边的交通方式中花费最小的那个
void init_graph();					// 初始化图
void Change_pro(int, int &, int &);	// 改变省份
void init_flag();					// 初始化标记数组
void init_bridge();					// 初始化
bool is_all();						// 判断当前路径中是否已包含指定的k个顶点
void init_Good();					// 初始化最优路径
void init_bestway();				// 初始化最优旅行方式

// 栈操作
void push(int);				// 进栈
int pop();					// 出栈

// 功能函数，对应问题1-9
void traver();				// 1、输出城市数据
void Hamilton();			// 2、找一条哈密顿回路
void Que_3();				// 3、满足条件且经过指定k个顶点的回路
void Que_4();				// 4、找A到B的最短路和最有趣的路
void Floyd_Warshall();			// 4.1、Floyd_Warshall算法求任意两点的最小路径
void traverse(int, int);		// 4.2、递归输出u到v的最短路径点 
void Que_5();				// 5、A到B、经过k个不同顶点（可以多于k个顶点，但不能少于）、耗时不超过C、有趣度最大的路径
void Que_6();				// 6、有限的时间（如x天）内，寻找一条从顶点a到顶点b的最有趣的旅行方式
void Que_7();				// 7、有限的经费（如x元）内，寻找一条从顶点a到顶点b的最有趣的旅行方式
void Que_8();				// 8、综合6和7的限制，求解同上
void FindBridge();			// 9、找桥和关节点


// DFS
void DFS_Hamilton(int, int, int, int, int);						//	哈密顿
void DFS_MostFun(int, int, int, int, int, int);					//	有限经费内最有趣的路
void DFS_fun(int, int, int, int, int);							//	A到B最有趣路径
void DFS_K_MostFun(int, int, int, int, int, int, int);			//	A到B经过k个顶点的最有趣路径
void DFS_Time_MostFun(int, int, int, int, int, int);			//	有限时间内顶点a到顶点b的最有趣的旅行方式
void DFS_Money_MostFun(int, int, int, int, int, int);			//	有限经费内顶点a到顶点b的最有趣的旅行方式
void DFS_TimeMoney_MostFun(int, int, int, int, int, int, int);	//	DFS综合6、7条件，寻找一条从顶点a到顶点b的最有趣的旅行方式
int Dfs_bridge(int, int);										//	找桥与割点



/******************** 全局变量 ************************/
int n, e;					// 总城市个数和边数
CityType city[55];			// 城市，共有51个
EdgeType graph[55][55];		// 存储边的信息
StackType S;				// 栈
int flag[52];				// 标记数组
int level;					// 记录递归深度
int g[55][55];				// 邻接表的形式
BestPathType Good;			// 最优路径
int path[55][55];			// 存放每个顶点到另外一个顶点的最短路径
int addfun;					// 当前路径有趣度之和
int addtime;				// 当前路径耗时之和
int goway[55];				// 当前旅行方式（非最优）
int best_way[55];			// 最优旅行方式


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
			printf("\n\n已安全退出系统！\a\n");	break;
		default:	
			printf("\n\n错误的操作指令！\n\a\a\n");
		}

	} while (choice != 10);

	return 0;
}

/******************** 准备工作 ************************/
// 主界面
int in()
{
	int choice;

	for (int i = 0; i < 115; i++)
		printf("━");
	printf("\n\t1——生成图的数据\n");
	printf("\t2——找一条HAMILTON回路\n");
	printf("\t3——找一条经过指定的k个顶点的回路，使用一种交通方式，使得回路费用不超过C、有趣度最大\n");
	printf("\t4——找一条从顶点A到顶点B的最短路，找一条A到B最有趣的路\n");
	printf("\t5——找一条从顶点A到顶点B、经过k个不同顶点（可以多于k个顶点，但不能少于）、耗时不超过C、有趣度最大的路径\n");
	printf("\t6——在有限的时间（如x天）内，寻找一条从顶点a到顶点b的最有趣（风景最美/最好玩）的旅行方式。\n");
	printf("\t7——在有限的经费（如x元）内，寻找一条从顶点a到顶点b的最有趣（风景最美/最好玩）的旅行方式。\n");
	printf("\t8——综合6和7的限制，求解同上\n");
	printf("\t9——寻找“关节点”和“桥”\n");
	printf("\t10——结束程序\n");
	for (int i = 0; i < 115; i++)
		printf("━");
	printf("\n请输入操作选项：");
	scanf("%d", &choice);

	return choice;
}

// 省份提示
void tip()
{
	for (int i = 0; i < 35; i++)
		printf("━");
	printf("\n\t1、广东省（1-23）\n");
	printf("\t2、广西省（24-37）\n");
	printf("\t3、湖南省（38-51）\n");
	for (int i = 0; i < 35; i++)
		printf("━");
	printf("\n请输入选项：");
}

// 读取文件
void ReadText()
{
	FILE *fp = fopen("城市数据.txt", "r");
	int u, v, op;

	printf("正在打开文件...\n");
	if (fp == NULL)
	{
		printf("文件打开失败！\n请检查文档是否存放在正确的路径!\n");
		exit(0);
	}
	printf("文件打开成功!\n");
	printf("开始读取文件...\n");
	fscanf(fp, "%d", &n);
	for (int i = 1; i <= n; i++)
		fscanf(fp, "%d%s%s%d", &city[i].id, city[i].name, city[i].from, &city[i].view);
	fscanf(fp, "%d", &e);
	for (int i = 0; i < e; i++)
	{
		fscanf(fp, "%d%d%d", &u, &v, &op);
		graph[u][v].ch = graph[v][u].ch = 1;

		/* 构造邻接表 */
		bool ch = true;
		// 判断是否重复
		for (int t = 0; t <= g[u][0]; t++)
		{
			if (v == g[u][t])
				ch = false;
		}
		if (ch == true)
		{
			g[u][0]++;		// 邻接点+1
			g[u][g[u][0]] = v;
			g[v][0]++;		// 邻接点+1
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

	printf("文件读取成功!\n\n");

	fclose(fp);
}

// 同一条边的交通方式中路程最小的那个
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

// 同一条边的交通方式中时间最小的那个
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

// 初始化图
void init_graph()
{
	for (int i = 0; i < 55; i++)
	{
		for (int j = 0; j < 55; j++)
		{
			graph[i][j].ch = 0;
			// 飞机
			graph[i][j].air.cost = 0;
			graph[i][j].air.dig = 0;
			graph[i][j].air.fun = 0;
			graph[i][j].air.time = 0;
			// 火车
			graph[i][j].train.cost = 0;
			graph[i][j].train.dig = 0;
			graph[i][j].train.fun = 0;
			graph[i][j].train.time = 0;
			// 小车
			graph[i][j].car.cost = 0;
			graph[i][j].car.dig = 0;
			graph[i][j].car.fun = 0;
			graph[i][j].car.time = 0;
			graph[i][j].anv = 0;

			if (i != j)
				graph[i][j].anv = 99999;	// 表示两个站点之间没有连接
			else
				graph[i][j].anv = 0;
			path[i][j] = -1;				// -1表示无需经过中间点 
		}
	}
}

// 改变省份
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

// 初始化标记数组
void init_flag()
{
	for (int i = 0; i < 52; i++)
		flag[i] = 0;
}

// 初始化找桥需要用到的结构
int dfs_clock;					// dfs时间戳
int pre[55], low[55];			// pre是记录时间戳的数组，low[u]表示u以及u的所有子孙中能连回祖先中
bool iscut[55];					// 顶点i是否为割点
int len_bridge;
BridgeType bridge[55];			// 存储图中的桥
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

// 判断路径中是否已包含指定的k个顶点
int way[30];		// 第0位存放k个顶点	
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

// 初始化最优路径
void init_Good()
{
	Good.adddis = 0;
	Good.addfun = 0;
	Good.addmoney = 0;
	Good.addtime = 0;
	Good.len = 0;
}

// 初始化最优旅行方式
void init_bestway()
{
	for (int i = 0; i < 55; i++)
	{
		goway[i] = 0;
		best_way[i] = 0;
	}
}


/********************  栈操作  ************************/
// 进栈
void push(int ch)
{
	S.top++;
	S.dis[S.top] = ch;
}

// 出栈
int pop()
{
	return S.dis[S.top--];
}


/******************** 功能函数 ************************/
//	1、输出城市数据
void traver()
{
	printf("\n");
	printf("------------------------------------------------------\n");
	printf("城市id\t城市名称\t所属省份\t有趣度\n");
	printf("------------------------------------------------------\n");
	for (int i = 1; i <= n; i++)
		printf("%4d\t%s\t\t%s\t\t%4d\n", city[i].id, city[i].name, city[i].from, city[i].view);
	printf("------------------------------------------------------------------------------------------------------------------\n");
	printf("出发编号\t目标编号\t交通方式\t路程(km)\t耗时(h)\t\t费用(元)\t有趣度\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 1; i <= n; i++)
	{
		for (int k = 1; k <= n; k++)
		{
			if (graph[i][k].air.dig != 0)
				printf("%4d\t\t%4d\t\t  飞机\t\t%4d\t\t%.2lf\t\t%4d\t\t%4d\n", i, k, graph[i][k].air.dig, (double)graph[i][k].air.time/10, graph[i][k].air.cost, graph[i][k].air.fun);
			if (graph[i][k].train.dig != 0)
				printf("%4d\t\t%4d\t\t  火车\t\t%4d\t\t%.2lf\t\t%4d\t\t%4d\n", i, k, graph[i][k].train.dig, (double)graph[i][k].train.time/10, graph[i][k].train.cost, graph[i][k].train.fun);
			if (graph[i][k].car.dig != 0)
				printf("%4d\t\t%4d\t\t  驾车\t\t%4d\t\t%.2lf\t\t%4d\t\t%4d\n", i, k, graph[i][k].car.dig, (double)graph[i][k].car.time/10, graph[i][k].car.cost, graph[i][k].car.fun);
		}
	}
}

//	2、找一条哈密顿回路
int fl;
void Hamilton()
{
	int op;
	int low, hi, citynum;
	int start;

	level = 0;			// 路径数组初始长度为0
	S.top = 0;			// 初始化栈顶
	fl = 0;
	tip();
	init_flag();
	scanf("%d", &op);
	Change_pro(op, low, hi);
	citynum = hi - low + 1;
	printf("请输入出发城市（%d-%d）：", low, hi);
	scanf("%d", &start);
	push(start);
	flag[start] = 1;
	DFS_Hamilton(start, start, low, hi, citynum);
	if (fl == 0)
		printf("以%d号城市出发，该省份没有哈密顿回路\n\n\a", start);
}

//	3、满足条件且经过指定k个顶点的回路
int add_fun;
int add_money;
int min_money;
void Que_3()
{
	int op;
	int low, hi, citynum;
	int start;
	int traff;

	init_Good();		// 初始化最优路径
	level = 0;			// 递归深度
	S.top = 0;			// 初始化栈顶，0为栈底
	add_fun = add_money = 0;
	tip();
	init_flag();
	scanf("%d", &op);
	Change_pro(op, low, hi);
	citynum = hi - low + 1;
	printf("请输入需要经过的顶点的个数：");
	scanf("%d", &way[0]);
	printf("请依次输入 %d 个顶点（%d - %d）：", way[0], low, hi);
	for (int i = 1; i <= way[0]; i++)
		scanf("%d", &way[i]);
	printf("请输入预算（元）：");
	scanf("%d", &min_money);
	printf("请输入出发城市的编号（%d - %d）：", low, hi);
	scanf("%d", &start);
	printf("请选择交通方式（1--飞机，2--火车，3--驾车）：");
	scanf("%d", &traff);
	push(start);
	flag[start] = 1;

	DFS_MostFun(start, start, low, hi, citynum, traff);

	// 存在最优路径
	if (Good.len != 0)
	{
		printf("\n成功找到最优路径！\n\n");
		for (int i = 1; i <= Good.len; i++)
			printf("%d ->", Good.best_path[i]);
		printf("%d\n\n", start);
		printf("该路径预算（元）：%d\n", Good.addmoney);
		printf("该路径有趣度：%d\n\n", Good.addfun);
	}
	else
		printf("\n没有满足条件的路径！\n\n");

}

//	4、找A到B的最短路和最有趣的路
void Que_4()
{
	int A, B;			// 顶点A为出发点，B为目标点
	int op;
	int low, hi, citynum;

	init_Good();		// 初始化最优路径
	level = 0;			// 递归深度
	S.top = 0;			// 初始化栈顶，0为栈底
	addfun = 0;
	tip();
	init_flag();
	scanf("%d", &op);
	Change_pro(op, low, hi);
	citynum = hi - low + 1;
	printf("请输入出发点：");
	scanf("%d", &A);
	printf("请输入目标点：");
	scanf("%d", &B);
	
	Floyd_Warshall();			// 求最短路径
	if (graph[A][B].anv == 99999)
	{
		printf("\n%d无法到达%d！\a\n\n", A, B);
	}
	// 两点可达，输出两点之间的最短路程以及经过的城市 
	else
	{
		printf("\n%d到达%d的最短路程为 %d km\n\n", A, B, graph[A][B].anv);		// 输出两个城市的最短路程 
		printf("经过的城市编号如下：\n\n\t");
		traverse(A, B);															// 输出两点的最短路径之间的站点
		printf("%d\n", B);														// 输出终点
		printf("\n");
	}

	push(A);
	flag[A] = 1;

	DFS_fun(A, B, low, hi, citynum);

	// 存在最有趣的路径
	if (Good.len != 0)
	{
		printf("\n成功找到最有趣的路径！\n\n\t");
		for (int i = 1; i < Good.len; i++)
			printf("%d ->", Good.best_path[i]);
		printf("%d\n\n", Good.best_path[Good.len]);
		printf("该路径有趣度为：%d\n\n", Good.addfun);
	}
	else
		printf("\n没有满足条件的路径！\n\n");
}

//	Floyd_Warshall算法求任意两点的最小路径
void Floyd_Warshall()
{
	int i, j, k;		// 中间变量 

	//  Floyd_Warshall核心算法 
	for (k = 1; k <= 51; k++)
		for (i = 1; i <= 51; i++)
			for (j = 1; j <= 51; j++)
			{
				// 发现了更加小的路径 
				if (graph[i][j].anv > graph[i][k].anv + graph[k][j].anv)
				{
					graph[i][j].anv = graph[i][k].anv + graph[k][j].anv;		// 更新路径 
					path[i][j] = k;			// 添加中间站点
				}
			}
}

//	递归输出u到v的最短路径点 
void traverse(int u, int v)
{
	// 递归终点
	if (path[u][v] == -1)
	{
		printf("%d ->", u);
		return;
	}
	// 往后继续递归输出路径站点
	int mid = path[u][v];
	traverse(u, mid);
	traverse(mid, v);
}

//	5、A到B经过k个不同顶点（可以多于k个顶点，但不能少于）、耗时不超过C、有趣度最大的路径
void Que_5()
{
	int A, B;			// 顶点A为出发点，B为目标点
	int op, k;
	int low, hi, citynum;
	int mostlong;

	init_Good();		// 初始化最优路径
	level = 0;			// 递归深度
	S.top = 0;			// 初始化栈顶，0为栈底
	addfun = 0;
	addtime = 0;
	tip();
	init_flag();
	scanf("%d", &op);
	Change_pro(op, low, hi);
	citynum = hi - low + 1;
	printf("请输入出发点：");
	scanf("%d", &A);
	printf("请输入目标点：");
	scanf("%d", &B);
	printf("请输入最少经过的顶点数量：");
	scanf("%d", &k);
	printf("请输入可以接受的最长时间(小时)：");
	scanf("%d", &mostlong);
	mostlong *= 10;

	push(A);
	flag[A] = 1;

	DFS_K_MostFun(A, B, low, hi, citynum, mostlong, k);

	// 存在最有趣的路径
	if (Good.len != 0)
	{
		printf("\n成功找到最有趣的路径！\n\n\t");
		for (int i = 1; i < Good.len; i++)
			printf("%d ->", Good.best_path[i]);
		printf("%d\n\n", Good.best_path[Good.len]);
		printf("该路径有趣度：%d\n\n", Good.addfun);
		printf("该路径时间：%.1lf（h）\n\n", Good.addtime/10.0);
		printf("%d到%d经过的顶点数为：%d\n\n", A, B, Good.len-2);
	}
	else
		printf("\n没有满足条件的路径！\n\n");
}

//	6、有限的时间（如x天）内，寻找一条从顶点a到顶点b的最有趣的旅行方式
void Que_6()
{
	int A, B;			// 顶点A为出发点，B为目标点
	int op;
	int low, hi, citynum;
	int mostlong;

	init_Good();		// 初始化最优路径
	init_bestway();		// 初始化旅行方式
	level = 0;			// 递归深度
	S.top = 0;			// 初始化栈顶，0为栈底
	addfun = 0;
	addtime = 0;
	tip();
	init_flag();
	scanf("%d", &op);
	Change_pro(op, low, hi);
	citynum = hi - low + 1;
	printf("请输入出发点：");
	scanf("%d", &A);
	printf("请输入目标点：");
	scanf("%d", &B);
	printf("请输入可以接受的最长时间(天)：");
	scanf("%d", &mostlong);
	mostlong *= (24 * 10);

	push(A);
	flag[A] = 1;

	DFS_Time_MostFun(A, B, low, hi, citynum, mostlong);

	// 存在最有趣的路径
	if (Good.len != 0)
	{
		printf("\n成功找到%d天内最有趣的旅行方式！\n\n  ", mostlong/24/10);
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
		printf("该旅行方式有趣度：%d\n\n", Good.addfun);
		printf("该旅行方式时间：%.1lf（h）\n\n", Good.addtime / 10.0);
	}
	else
		printf("\n没有满足条件的路径！\n\n");
}

//	7、有限的经费（如x元）内，寻找一条从顶点a到顶点b的最有趣的旅行方式
int addmoney;
void Que_7()
{
	int A, B;			// 顶点A为出发点，B为目标点
	int op;
	int low, hi, citynum;
	int mostmoney;

	init_bestway();		// 初始化旅行方式
	init_Good();		// 初始化最优路径
	level = 0;			// 递归深度
	S.top = 0;			// 初始化栈顶，0为栈底
	addfun = 0;
	addmoney = 0;
	tip();
	init_flag();
	scanf("%d", &op);
	Change_pro(op, low, hi);
	citynum = hi - low + 1;
	printf("请输入出发点：");
	scanf("%d", &A);
	printf("请输入目标点：");
	scanf("%d", &B);
	printf("请输入预算(元)：");
	scanf("%d", &mostmoney);

	push(A);
	flag[A] = 1;

	DFS_Money_MostFun(A, B, low, hi, citynum, mostmoney);

	// 存在最有趣的路径
	if (Good.len != 0)
	{
		printf("\n成功找到 %d 元内最有趣的旅行方式！\n\n  ", mostmoney);
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
		printf("该旅行方式有趣度：%d\n\n", Good.addfun);
		printf("该旅行方式花费 %d 元\n\n", Good.addmoney);
	}
	else
		printf("\n没有满足条件的路径！\n\n");
}

//	8、综合6和7的限制，求解同上
void Que_8()
{
	int A, B;			// 顶点A为出发点，B为目标点
	int op;
	int low, hi, citynum;
	int mostmoney;
	int mostlong;

	init_Good();		// 初始化最优路径
	init_bestway();		// 初始化旅行方式
	level = 0;			// 递归深度
	S.top = 0;			// 初始化栈顶，0为栈底
	addfun = 0;
	addmoney = 0;
	tip();
	init_flag();
	scanf("%d", &op);
	Change_pro(op, low, hi);
	citynum = hi - low + 1;
	printf("请输入出发点：");
	scanf("%d", &A);
	printf("请输入目标点：");
	scanf("%d", &B);
	printf("请输入可以接受的最长时间(天)：");
	scanf("%d", &mostlong);
	mostlong *= (24 * 10);
	printf("请输入预算(元)：");
	scanf("%d", &mostmoney);

	push(A);
	flag[A] = 1;

	DFS_TimeMoney_MostFun(A, B, low, hi, citynum, mostlong, mostmoney);

	// 存在最有趣的路径
	if (Good.len != 0)
	{
		printf("\n成功找到 %d 小时和 %d 元内最有趣的旅行方式！\n\n  ", mostlong / 24 / 10, mostmoney);
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
		printf("该旅行方式有趣度：%d\n\n", Good.addfun);
		printf("该旅行方式花费 %d 元\n\n", Good.addmoney);
		printf("该旅行方式耗时 %.1lf 时\n\n", Good.addtime / 10.0);
	}
	else
		printf("\n没有满足条件的路径！\n\n");
}

//	找关节点和桥
void FindBridge()
{
	printf("\n\n-----关节点-----\n");
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
	printf("\n-------桥-------\n");
	for (int i = 1; i <= len_bridge; ++i) {
		printf("    %d -- %d\n", bridge[i].u, bridge[i].v);
	}
}


/********************** DFS **************************/
//	2、DFS哈密顿
void DFS_Hamilton(int start, int cur, int low, int hi, int citynum)
{
	level++;
	if (level == citynum)
	{
		// 路径经过所有点并且能够构成回路
		if (graph[cur][start].ch != 0 && fl == 0)
		{
			printf("\n成功找到一条哈密顿回路！\n\n\t");
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

//	3、DFS满足条件，指定k个顶点的回路
void DFS_MostFun(int start, int cur, int low, int hi, int citynum, int traff)
{
	level++;

	switch (traff)
	{
	case 1:
		// 指定的顶点在指定预算内已全部包含且构成回路的情况下，有趣度比最优路径的大，更新最优路径
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

	if (add_money > min_money || level >= citynum)		// 超出预算或者达到递归终点
		return;

	for (int i = low; i <= hi; i++)
	{
		switch (traff)
		{
		case 1:
			if (graph[cur][i].air.dig != 0 && flag[i] == 0)
			{
				add_fun += graph[cur][i].air.fun;		// 更新当前有趣度总和
				add_money += graph[cur][i].air.cost;	// 更新当前花费总和
				flag[i] = 1;
				push(i);
				DFS_MostFun(start, i, low, hi, citynum, traff);
				int ls = pop();
				add_fun -= graph[cur][i].air.fun;		// 更新当前有趣度总和
				add_money -= graph[cur][i].air.cost;	// 更新当前花费总和
				level--;
				flag[i] = 0;
			}
			break;
		case 2:
			if (graph[cur][i].train.dig != 0 && flag[i] == 0)
			{
				add_fun += graph[cur][i].train.fun;		// 更新当前有趣度总和
				add_money += graph[cur][i].train.cost;	// 更新当前花费总和
				flag[i] = 1;
				push(i);
				DFS_MostFun(start, i, low, hi, citynum, traff);
				int ls = pop();
				add_fun -= graph[cur][i].train.fun;		// 更新当前有趣度总和
				add_money -= graph[cur][i].train.cost;	// 更新当前花费总和
				level--;
				flag[i] = 0;
			}
			break;
		case 3:
			if (graph[cur][i].car.dig != 0 && flag[i] == 0)
			{
				add_fun += graph[cur][i].car.fun;		// 更新当前有趣度总和
				add_money += graph[cur][i].car.cost;	// 更新当前花费总和
				flag[i] = 1;
				push(i);
				DFS_MostFun(start, i, low, hi, citynum, traff);
				int ls = pop();
				add_fun -= graph[cur][i].car.fun;		// 更新当前有趣度总和
				add_money -= graph[cur][i].car.cost;	// 更新当前花费总和
				level--;
				flag[i] = 0;
			}
			break;
		}

	}
}

//	4、DFS最有趣的路
void DFS_fun(int cur, int aim, int low, int hi, int citynum)
{
	level++;
	// 当前路径有趣度之和已超过最优路径的有趣度
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

//	5、DFS经过k个不同顶点（可以多于k个顶点，但不能少于）、耗时不超过C、有趣度最大的路径
void DFS_K_MostFun(int cur, int aim, int low, int hi, int citynum, int mostlong, int k)
{
	level++;
	
	// 当前路径有趣度之和已超过最优路径的有趣度
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

//	6、DFS有限的时间（如x天）内，寻找一条从顶点a到顶点b的最有趣的旅行方式
void DFS_Time_MostFun(int cur, int aim, int low, int hi, int citynum, int mostlong)
{
	level++;

	// 当前路径有趣度之和已超过最优路径的有趣度
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

//	7、DFS有限的经费（如x元）内，寻找一条从顶点a到顶点b的最有趣的旅行方式
void DFS_Money_MostFun(int cur, int aim, int low, int hi, int citynum, int mostmoney)
{
	level++;

	// 当前路径有趣度之和已超过最优路径的有趣度
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

//	8、DFS综合6、7条件，寻找一条从顶点a到顶点b的最有趣的旅行方式
void DFS_TimeMoney_MostFun(int cur, int aim, int low, int hi, int citynum, int mostlong, int mostmoney)
{
	level++;

	// 当前路径有趣度之和已超过最优路径的有趣度
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

//	9、DFS桥
int Dfs_bridge(int u, int fa)
{
	int lowu = pre[u] = ++dfs_clock;
	int child = 0;				// 子节点个数

	for (int i = 1; i <= g[u][0]; ++i) {
		int v = g[u][i];
		if (0 == pre[v])
		{
			++child;
			int lowv = Dfs_bridge(v, u);
			if (lowu > lowv)
				lowu = lowv;
			if (lowv >= pre[u]) {
				iscut[u] = true;					// 割点
				if (lowv > pre[u])
				{
					// 桥
					len_bridge++;
					bridge[len_bridge].u = u;
					bridge[len_bridge].v = v;

				}
			}
		}
		else if (pre[v] < pre[u] && v != fa) {		// 反向边(u,v)
			if (lowu > pre[v])
				lowu = pre[v];
		}
	}
	if (fa < 0 && child == 1)
		iscut[u] = false;//判断根结点
	low[u] = lowu;

	return lowu;
}
