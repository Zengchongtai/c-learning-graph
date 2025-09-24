#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

// 没有连线的顶点之间的权值设置为无限
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


// 创建一张图
/*[ 思路 ]
1.先设置顶点和边的数量
2.遍历载入每一个结点
3.设置权值(自身与自身设置为0,其余先全部设置为MAX)
4.连接图 设置特定权值
5.沿对角线复制

*/
void create_graph(matrix_graph* g)
{
    g -> vertex_num = 9;
    g -> edge_num = 15;

    char str[] = "ABCDEFGHI";

    for (int i=0;i < g -> vertex_num; i++)
    {
        g -> vertex[i] = str[i];
    }

    // 设置表格中的权值
    // 没有连线的顶点之间的权值设置为无限 自身与自身设置权值为0
    for (int i=0; i < g -> vertex_num ;i ++)
    {
        for (int j=0; j < g -> vertex_num ; j++)
        {
            if (i==j)
            {
                g -> arc[i][j] = 0;
            }
            else
            {
                g -> arc[i][j] = MAX; // 先都设置为MAX
            }
        }
    }

    // 连接图
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

    // D-E D-H D-G D-I
    g -> arc[3][4] = 20;
    g -> arc[3][7] = 16;
    g -> arc[3][6] = 24;
    g -> arc[3][8] = 21;

    // E-H E-F
    g -> arc[4][7] = 7;
    g -> arc[4][5] = 26;

    // F-G
    g -> arc[5][6] = 17;
    
    // G-H
    g -> arc[6][7] = 19;

    // 沿对角线复制
    for (int i=0;i < g -> vertex_num ;i++)
    {
        for (int j=0; j < g -> vertex_num ; j++)
        {
            g -> arc[j][i] = g -> arc[i][j];
        }
    }

}

// 普里姆算法
/*[ 思路 ]
1.先从顶点A开始
    - 设置从A到A的权值
    - 以A为顶点,以权值的形式存储后选路径,并设置出发点和到达点

2.存入候选路径进入weight数组

2.主循环
    - 先把最小值设置为MAX,以后遍历时更新
    - 更新变量k,记录本次循环拥有最小权值路径的下标(到达点)
    
    1.找到最小值并与之连接
        - 循环 更新最小权值 使用k记录
    - 输出找到的最小权值的路径(测试使用)
    - “连接”完了之后把权值设置为0(相当于声明链接了)

    2.拓展下一个待选路径
        - 以新顶点为起点遍历其他所有的点
        - 若权值小于对应的在weight中的权值则记录
        - 更新可用路径,存储在vex_index中

*/

void prim(matrix_graph* g)
{
    int i,j,k;
    int min;
    int weight[g -> vertex_num];
    int vex_index[g -> vertex_num];


    // 设置A到A的权值
    weight[0] = 0;
    // 以A为顶点,以权值的形式存储后选路径,并设置出发点和到达点
    vex_index[0] = 0;

    // 存入候选路径
    for (i=0;i < g -> vertex_num; i++)
    {
        vex_index[i] = 0;
        weight[i] = g -> arc[0][i];
    }

    for (i=1;i<g -> vertex_num;i++)
    {
        min = MAX;
        k = 0;

        // 找到最小值并与之连接
        for (j=0;j < g -> vertex_num;j++)
        {
            if (weight[j]!=0 && weight[j] < min)
            {
                min = weight[j];
                k = j;
            }
        }

        printf("\n本次循环最小权值路径是从 %c 到 %c\n",g -> vertex[vex_index[k]], g -> vertex[k]);
        weight[k] = 0; // 让已经使用过的顶点以后不再参与

        // 拓宽下一个待选路径
        for (j=0;j < g -> vertex_num;j++)
        {
            if (weight[j]!=0 && g -> arc[k][j] < weight[j])
            {
                weight[j] = g -> arc[k][j];
                vex_index[j] = k;
            }
        }
    }

}


int main()
{
    matrix_graph g;
    create_graph(&g);
    prim(&g);
    return 0;


    return 0;
}
