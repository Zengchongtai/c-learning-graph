// 广度优先

#include <stdio.h>

typedef char vertextype;
typedef int edgetype;

#define MAXSIZE 100

typedef struct
{
    vertextype vertex[MAXSIZE];
    edgetype arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
}matrix_graph;

int visited[MAXSIZE];

// 类似层序遍历,需要用到队列
int front = 0;
int rear = 0;
int queue[MAXSIZE];

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

    for (int i=0;i<g -> vertex_num;i++)
    {
        for (int j=0;j<g -> vertex_num;j++)
        {
            g -> arc[i][j] = 0;
        }
    }

    // 开始连线 这把无向图

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
    for (int i=0;i< g -> vertex_num ;i++)
    {
        for (int j=0;j< g -> vertex_num ;j++)
        {
            g -> arc[j][i] = g -> arc[i][j];
        }
    }
}

// 广度优先
void bfs(matrix_graph g)
{
    int i = 0;
    visited[i] = 1; // 先访问了A
    printf("\n\n====== [ 广度优先 ] ======\n%c\n\n", g.vertex[i]);

    queue[rear++] = i; // 将A入队
    while(front!=rear)
    {
        i = queue[front++]; // 1.把A出队 3.把B出队
        for (int j = 0; j < g.vertex_num; j++)
        {
            if (g.arc[i][j] == 1 && visited[j] == 0) // 1.找到了与A连接的顶点B,B对应的下标为1,j赋值为1 2.找到了F 3.找到了与B连接的顶点,以此类推
            {
                visited[j] = 1; // 1.访问了B 2.访问了F
                printf("\n\n====== [ 广度优先 ] ======\n%c\n\n", g.vertex[j]);
                queue[rear++] = j; // 1.将B入队 2.将F入队

            }
        }
    }
}

int main()
{
    matrix_graph g;
    create_graph(&g);

    for (int i=0;i< g.vertex_num;i++)
    {
        visited[i] = 0;
    }
    bfs(g);
    return 0;
}
