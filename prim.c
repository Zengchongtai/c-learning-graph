// 最小生成树 普里姆

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

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

// 最小生成树算法
void prim(matrix_graph* g) // 传入的是指针啦
{
    int i, j, k;
    int min; // 保存最小值.每一次都找权值最小的
    int weight[MAXSIZE]; // 用于保存候选边的数组

    int vex_index[MAXSIZE]; // 值表示出发点,下标表示到达点

    // 先从顶点A开始
    weight[0] = 0; // vex_index某点与下标对应点的权值 即从A到A的权值为0 详情见表格
    vex_index[0] = 0; // 值 0 下标 0 从A到A

    for (i = 1; i < g -> vertex_num ; i++)
    {
        weight[i] = g -> arc[0][i]; // 把候选路径存入,以权值的形式存储
        vex_index[i] = 0; // 分别表示从A到A,B,C,D,E,F,G,H,I
    }

    for (int i=1;i < g -> vertex_num; i++) // i=1表示处理A的下一个(此处是B),i=2表示处理B的下一个.怎么在第二次循环知道B的下一个是谁呢？B与所有顶点之间的权值都存在weight数组里面了,依靠weight数组进行信息传递
    // 该算法还杜绝了环路的形成,太牛啦
    {
        min = MAX;
        k = 0;

        // 找到最小的并与之连接
        for ( j = 0; j < g -> vertex_num; j++)
        {
            if (weight[j] != 0 && weight[j] < min) // 不能是自己
            {
                min = weight[j]; // 更新最小权值
                k = j; // 等该循环结束之后,k就记录了拥有最小权值路径的下标
            }

        }

        printf("\n\n本轮循环中,权值最小路径是从 %c 到 %c \n",g -> vertex[vex_index[k]], g -> vertex[k]); // 前面是值表示起始点,后面是下标表示到达点
        weight[k] = 0; // A和B已经连完了,所以A和B之间的路不能再作为待选路径,因此把权值设置为0

        // 拓展B的待选路径
        for (j = 0; j < g -> vertex_num; j++) // 在B作为起点时遍历其他所有点
        {
            if (weight[j] != 0 && g -> arc [k][j] < weight[j]) // 如果权值不为0且权值有比对应的待选列表中权值小的 注意,是对应的! k此时为1,表示顶点B
            {
                weight[j] = g -> arc[k][j]; // 更新最小权值列表
                vex_index[j] = k; // 值赋为1,表示出发点为B,而j表示能进入权值比小决赛圈的那些路径 表达的是B和j所对应的顶点之间的权值是weight[j],此处若j表示c则权值为18
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
}
