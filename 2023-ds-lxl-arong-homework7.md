# hw7

前言:

图的基本概念包括，顶点、边(期末大概率考，编程题反而可能不考)，这里就略过了，自行看PPT或者网上的blog了解

为了让同学们快速上手，这里讲讲代码上的东西

- 代码中，图常见组织形式
  
  - 邻接矩阵
一个矩阵，下标记点编号，内容记连通性 or 距离
e.g.
    
    ```puml
    @startuml
skinparam componentStyle rectangle
    [0] - [1]
    [1] - [3]
    [3] - [6]
    [6] -- [2]
    [2] - [1]
    [2] - [3]
@enduml
    ```
    
    在邻接矩阵中应该表示
    
    | 不联通为0 联通为1 | 0   | 1   | 2   | 3   | 4   | 5   | 6   |
    | ---------- | --- | --- | --- | --- | --- | --- | --- |
    | 0          | 0   | 1   | 0   | 0   | 0   | 0   | 0   |
    | 1          | 1   | 0   | 1   | 1   | 0   | 0   | 0   |
    | 2          | 0   | 1   | 0   | 1   | 0   | 0   | 1   |
    | 3          | 0   | 1   | 1   | 0   | 0   | 0   | 1   |
    | 4          | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
    | 5          | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
    | 6          | 0   | 0   | 1   | 1   | 0   | 0   | 0   |

    ```c
    int graph[7][7] =
{
    {0, 1, 0, 0, 0, 0, 0},
    {1, 0, 1, 1, 0, 0, 0},
    {0, 1, 0, 1, 0, 0, 1},
    {0, 1, 1, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 0}
}
    ```
    
    对于有向有距离无负距离(考不到负距离那么难)的图，将1换为距离，0换成负数标记不可到达即可
    
    ```puml
    @startuml
skinparam componentStyle rectangle
    [0] -> [1]: 1
    [1] -> [3]: 2
    [3] -> [6]: 3
    [6] --> [2]: 4
    [2] -> [1]: 5
    [2] -> [3]: 6
@enduml
    ```
    
  | 不联通为-7 联通为距离 | 0   | 1                | 2                | 3                | 4   | 5   | 6                |
  | ------------ | --- | ---------------- | ---------------- | ---------------- | --- | --- | ---------------- |
  | 0            | -7  | $\color{red}{1}$ | -7               | -7               | -7  | -7  | -7               |
  | 1            | -7  | -7               | -7               | $\color{red}{2}$ | -7  | -7  | -7               |
  | 2            | -7  | $\color{red}{5}$ | -7               | $\color{red}{6}$ | -7  | -7  | -7               |
  | 3            | -7  | -7               | -7               | -7               | -7  | -7  | $\color{red}{3}$ |
  | 4            | -7  | -7               | -7               | -7               | -7  | -7  | -7               |
  | 5            | -7  | -7               | -7               | -7               | -7  | -7  | -7               |
  | 6            | -7  | -7               | $\color{red}{4}$ | -7               | -7  | -7  | -7               |

  ```c
  int graph[7][7] =
{
    {-7,  1, -7, -7, -7, -7, -7},
    {-7, -7, -7,  2, -7, -7, -7},
    {-7,  5, -7,  6, -7, -7, -7},
    {-7, -7, -7, -7, -7, -7,  3},
    {-7, -7, -7, -7, -7, -7, -7},
    {-7, -7, -7, -7, -7, -7, -7},
    {-7, -7,  4, -7, -7, -7, -7}
};
  ```
  
  - 邻接表
用类似链表的方法将其串起来
    
    ```puml
    @startuml
skinparam componentStyle rectangle
    [0] -> [1]: 1
    [1] -> [3]: 2
    [3] -> [6]: 3
    [6] --> [2]: 4
    [2] -> [1]: 5
    [2] -> [3]: 6
@enduml
    ```
    
    ```c
    struct Vertex;//预先声明防止struct Edge不过编译

struct Edge{//边的链表节点
    struct Vertex* toVertex;
    int distance;
    struct towards *nextEdge;
};

struct Vertex{//点结构体
    int id;//点编号
    //char name[];除了编号以外可以将点信息进一步拓展
    //int type;
    struct Edge* toEdge;//记录到达地点
};
    ```
    
    会形成下面类似的结构:
    
    ```puml
    @startjson
    ["Vertex", 0, ["Edge", ["Vertex", 1, ["Edge", ["Vertex", 3], 2, "null"]], 1, "null"]]
@endjson
    ```
    
  - 其它拓展(ds用不到)参见: 十字链表、邻接多重表、边集数组
    
- 其次是常见的操作
  
  - 遍历
    
    - 深度优先
      
    ```c
    #define MAX_VERTEX 7
int graph[MAX_VERTEX][MAX_VERTEX] =
{
    {-7,  1, -7, -7, -7, -7, -7},
    {-7, -7, -7,  2, -7, -7, -7},
    {-7,  5, -7,  6, -7, -7, -7},
    {-7, -7, -7, -7, -7, -7,  3},
    {-7, -7, -7, -7, -7, -7, -7},
    {-7, -7, -7, -7, -7, -7, -7},
    {-7, -7,  4, -7, -7, -7, -7}
};
char arrive[MAX_VERTEX] = {};//用于判断是否到达
void DFS(int id) {
    if (id == destination) {
        //do something here
        return;//到终点，回头
    }
    for (int i = 0; i < MAX_VERTEX; i++) {
        if (!arrive[i]/*i没到过*/ && graph[id][i] >= 0/*id能到i*/) {
            arrive[i] = 1;//现在到i了【官话：修改现场】
            DFS(i);       //从i出发【官话：深搜】
            arrive[i] = 0;//发现走不通，回id，换一条路【官话：恢复现场】
        }
    }
    return;//都试过了该回头了
}
    ```
    
    ```c
    struct Vertex;//预先声明防止struct Edge不过编译

struct Edge{//边的链表节点
    struct Vertex* toVertex;
    int distance;
    struct towards *nextEdge;
};

struct Vertex{//点结构体
    int id;//点编号
    //char name[];除了编号以外可以将点信息进一步拓展
    //int type;
    struct Edge* toEdge;//记录到达地点
};

#define stack(MAX_VERTEX, struct Vertex*)

void DFS(struct Vertex *vertex) {
    if (vertex->id == destination) {
        //do something here
    }
}
    ```
    
    - 广度优先
      
      <!-- more -->
      
## T1

