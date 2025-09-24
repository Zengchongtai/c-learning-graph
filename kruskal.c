// 克鲁苏卡尔算法
#include <stdio.h>

#define MAXSIZE 100
#define MAXEDGE 15

// 以int类型最大值表示∞
#define MAX 0x7fffffff

typedef char vertextype;
typedef int edgetype;

typedef struct 
{
    vertextype vertex[MAXSIZE];
    edgetype arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
}matrix_graph;


// 该结构体专门负责表达边
// 虽然有开头结尾,但用的是无向图,所以开头结尾其实无所谓顺序
typedef struct
{
    int begin; // 开头
    int end; // 结尾
    int weight; // 该路径的权值
}edge;


// 创建一张图
void create_graph(matrix_graph* g)
{
    g -> vertex_num = 9;
    g -> edge_num = 15;

    char str[] = "ABCDEFGHI";
    for (int i=0;i<g -> vertex_num;i++)
    {
        g -> vertex[i] = str[i];
    }

    for (int i = 0;i < g -> vertex_num; i++)
    {
        for (int j=0;j < g -> vertex_num; j++)
        {
            if (i==j)
            {
                g -> arc[i][j] = 0;
            }
            else
            {
                g -> arc[i][j] = MAX;
            }
        }
    }

    // 路上表示权值
    // A-B A-F
    g -> arc[0][1] = 10;
    g -> arc[0][5] = 11;

    // B-C B-G B-I
    g -> arc[1][2] = 18;
    g -> arc[1][6] = 16;
    g -> arc[1][8] = 12;

    // C-D C-I
    g -> arc[2][3] = 22;
    g -> arc[2][8] = 8;

    // D-E D-G D-H D-I
    g -> arc[3][4] = 20;
    g -> arc[3][6] = 24;
    g -> arc[3][7] = 16;
    g -> arc[3][8] = 21;

    // E-F E-H
    g -> arc[4][5] = 26;
    g -> arc[4][7] = 7;

    // F-G
    g -> arc[5][6] = 17;

    // G-H
    g -> arc[6][7] = 19;

    for (int i = 0; i< g -> vertex_num ; i++)
    {
        for (int j = 0; j < g -> vertex_num ; j++)
        {
            g -> arc[j][i] = g -> arc[i][j];
        }
    }

}
// 交换两个在数组中的位置
void swap(edge edges[],int big, int small)
{
    edge temp = edges[big];
    edges[big] = edges[small];
    edges[small] = temp;
}

// 以边的权值给边排序 由小到大
void sortedge(edge edges[], int edge_num)
{
    for (int i=0;i < edge_num;i++)
    {
        for (int j = i + 1; j < edge_num; j++)
        {
            if (edges[i].weight > edges[j].weight)
            {
                swap(edges,i,j);
            }
        }
    }

}

int find(int parent[], int index)
{
    while(parent[index] > 0) // 这段循环非常精彩,建议以后好好研究
    {
        index = parent[index];
    }
    return index;
}

// 克鲁斯卡尔
void kruskal(matrix_graph g)
{   
    edge edges[MAXEDGE]; // 声明一个数组专门用于存放边(路径)
    int k = 0;

    // 将所有路径(边)先存进edges数组
    for (int i =0; i < g.vertex_num; i++)
    {
        for (int j = i + 1; j < g.vertex_num; j++)
        {
            if (g.arc[i][j] < MAX)
            {
                edges[k].begin = i;
                edges[k].end = j;
                edges[k].weight = g.arc[i][j];
                k++; // k表示的是edges数组的下标,每次需要更新
            }
        }
    }

    // 给边去排序
    sortedge(edges,g.edge_num);

    int parent[MAXSIZE]; // 该数组用于保存整张图每一条边之间这种连接关系

    for (int i = 0; i < g.vertex_num; i++)
    {
        parent[i] = 0;
    }

    int m,n;
    for (int i=0;i < g.edge_num; i++)
    {
        n = find(parent, edges[i].begin); // 第一次取出了4
        m = find(parent, edges[i].end); // 第一次取出了7

        if (n!=m) // 该判断是为了防止形成环
        {
            parent[n] = m; // 第一次把parent下标为4(E)的地方赋值为了7(H),指的就是第一次把H,E连接了起来.下标表示begin,值表示end
            printf("\n\n%c 与 %c 已连接\n",g.vertex[edges[i].begin],edges[i].end);
        }
    }
}