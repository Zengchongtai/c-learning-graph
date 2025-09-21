#include <stdio.h>

typedef char vertextype;
typedef int edgetype;

#define MAXSIZE 100

typedef struct 
{
    vertextype vertex[MAXSIZE]; // 该数组用于保存顶点
    edgetype arc[MAXSIZE][MAXSIZE]; // 该二维数组用于保存边 有向图<1,0> 无向图(1,0)
    int vertex_num; // 顶点的数量
    int edge_num; // 边的数量

}matrix_graph; // 矩阵的英文单词叫做matrix

int visited[MAXSIZE]; // 遍历时使用,记录哪些顶点被访问过,哪些顶点没被访问过 以下标作为顶点记录,0表示未被访问,1表示已被访问

// 创建一张图
void create_graph(matrix_graph* g)
{
    g -> vertex_num = 9; // 设定为9个顶点,15条边
    g -> edge_num = 15;

    char str[] = "ABCDEFGHI";
    for (int i=0;i < g-> vertex_num;i++)
    {
        g -> vertex[i] = str[i];
    }

    // 给二维数组做初始化,都赋值为0
    for (int i=0;i < g -> vertex_num; i++)
    {
        for (int j=0;j < g -> vertex_num; j++)
        {
            g -> arc[i][j] = 0;
        }
    }

    // 开始连线 这把有向图

    // A-B A-F
    g -> arc[0][1] = 1;
    g -> arc[0][5] = 1;

    // B-C B-G B-I
    g -> arc[1][2] = 1;
    g -> arc[1][6] = 1;
    g -> arc[1][8] = 1;

    // C-D C-I
    g -> arc[2][3] = 1;
    g -> arc[2][8] = 1;

    // D-E D-G D-H D-I
    g -> arc[3][4] = 1;
    g -> arc[3][6] = 1;
    g -> arc[3][7] = 1;
    g -> arc[3][8] = 1;

    // E-F E-H
    g -> arc[4][5] = 1;
    g -> arc[4][7] = 1;

    // F-G
    g -> arc[5][6] = 1;

    // G-H
    g -> arc[6][7] = 1;

    // 沿对角线复制
    for (int i = 0; i < g -> vertex_num ; i++)
    {
        for (int j = 0; j < g -> vertex_num ; j++)
        {
            g -> arc[j][i] = g -> arc[i][j];
        }
    }
}

// 深度优先
void dfs(matrix_graph g, int i)
{
    visited[i] = 1; // 先把顶点A的对应的遍历记录改为1,表示已经遍历
    printf("\n\n====== [ 深度搜索 ] ======\n%c\n\n", g.vertex[i]);

    // 深度优先
    for (int j = 0;j < g.vertex_num; j++)
    {
        if (g.arc[i][j]==1 && visited[j] == 0) // 这行注释不用管,反正懂了,但是表达不出来 g.arc[i][j]==1代表有连线 visited[j] == 0代表未被遍历过
        {
            dfs(g,j);
        }
    }

}

int main()
{   
    matrix_graph g; // 声明了一个图的变量(但是图还未被创造出来)
    create_graph(&g); // 创造了一张图

    // 初始化遍历记录数组 visited
    for (int i=0;i< g.vertex_num;i++)
    {
        visited[i] = 0;
    }

    // 深度搜索
    dfs(g,0); // 第一个参数传入的是图,第二个参数传入的是顶点A的下标0

    return 0;
}