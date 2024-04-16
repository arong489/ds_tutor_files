#include "dsdiy.h"
#include <stdio.h>
#include <stdlib.h>
struct Vertex; // 预先声明防止struct Edge不过编译

struct Edge { // 边的链表节点
    struct Vertex* toVertex;
    int id;
};

typedef struct Edge* edgeptr;
typedef define_list(edgeptr) EdgeList;
typedef struct Vertex* vertexptr;
typedef define_list(vertexptr) VertexList;

struct Vertex { // 点结构体
    int id; // 点编号
    // char name[];除了编号以外可以将点信息进一步拓展
    // int type;
    EdgeList edges;
};

struct Graph { // 邻接表
    VertexList vertexes;
    int vertex_number;
    int edge_number;
} global;

char check[1000] = {1};

define_stack(1000, int) path;
#define printpath(x) printf("%d ", x)

void DFS(struct Vertex* vertex)
{
    if (vertex->id == global.vertex_number - 1)
    {
        stack_foreach(path, printpath);
        fputc('\n', stdout);
        return;
    }
    struct Edge** temp;
    _LIST_FOREACH(vertex->edges, temp)
    {
        if (!check[(*temp)->toVertex->id]) {
            stack_push(path, (*temp)->id);
            check[(*temp)->toVertex->id] = 1;
            DFS((*temp)->toVertex);
            check[(*temp)->toVertex->id] = 0;
            stack_pop(path);
        }
    }
    return;
}

#define find_vertex(v, ver) (v->id == ver)
#define find_edge(e, ver, id) (e->toVertex->id == ver && e->id == id)
// int find_edge(struct Edge*e, int ver, int id){
//     return (e->toVertex->id == ver && e->id == id);
// }
int main(int argc, char const* argv[])
{
    list_flush(global.vertexes);
    struct Vertex *vertex1, *vertex2;
    struct Edge *edge1, *edge2;
    int ver1, ver2, id;
    // fputs("input: vertex1 vertex2 distance\n", stdout);
    scanf("%d%d", &global.vertex_number, &global.edge_number);
    while (~scanf("%d%d%d", &id, &ver1, &ver2)) {
        vertex1 = list_find(global.vertexes, find_vertex, ver1);
        vertex2 = list_find(global.vertexes, find_vertex, ver2);
        if (vertex1 == NULL) {
            vertex1 = (struct Vertex*)malloc(sizeof(struct Vertex));
            vertex1->id = ver1;
            list_flush(vertex1->edges);
            list_pushback(global.vertexes, vertex1);
        }
        if (vertex2 == NULL) {
            vertex2 = (struct Vertex*)malloc(sizeof(struct Vertex));
            vertex2->id = ver2;
            list_flush(vertex2->edges);
            list_pushback(global.vertexes, vertex2);
        }
        if (!list_has(vertex1->edges, find_edge, ver2, id)) {
            edge1 = (struct Edge*)malloc(sizeof(struct Edge));
            edge1->id = id;
            edge1->toVertex = vertex2;
            list_pushback(vertex1->edges, edge1);
        }
        if (!list_has(vertex2->edges, find_edge, ver1, id)) {
            edge2 = (struct Edge*)malloc(sizeof(struct Edge));
            edge2->id = id;
            edge2->toVertex = vertex1;
            list_pushback(vertex2->edges, edge2);
        }
    }
    stack_flush(path, 1000);
    DFS(list_find(global.vertexes, find_vertex, 0));
    return 0;
}