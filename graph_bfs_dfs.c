#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

// --- Utility functions / definitions for menu

#if defined _WIN32
#define clear() system("cls")
#elif defined unix
#define clear() system("clear")
#endif

#define SUCCESS 1
#define FAILURE 0
#define TRUE 1
#define FALSE 0
#define WEIGHTED 1
#define NON_WEIGHTED 0

#define flush() while (getchar() != '\n')

char get_choice()
{
    char choice;
    scanf("%c", &choice);
    flush();
    return choice;
}

void pause()
{
    printf("\n\nPress enter to continue...\n");
    flush();
}

// --- Node & realted functions

typedef struct NODE {
    int info;
    struct NODE* next;
} NODE;

int value(NODE* node)
{
    if (node == NULL) {
        printf("error: attempt to access value of a NULL node.");
        exit(EXIT_FAILURE);
    }

    return node->info;
}

NODE* newNODE(int info)
{
    NODE* node;
    node = (NODE*)malloc(sizeof(NODE));
    node->info = info;
    node->next = NULL;
    return node;
}

// --- Edge & related functions

typedef struct EDGE {
    NODE *src, *dst;
    int wt;
    struct EDGE* next;
} EDGE;

EDGE* newEDGE(int src_val, int dst_val, int wt)
{
    EDGE* e = (EDGE*)malloc(sizeof(EDGE));
    e->src = newNODE(src_val);
    e->dst = newNODE(dst_val);
    e->wt = wt;
    return e;
}

void deleteEDGE(EDGE* e)
{
    free(e->src);
    free(e->dst);
    free(e);
}

// --- Queue of Edges

typedef struct EDGE_QUEUE {
    EDGE *head, *tail;
} EDGE_QUEUE;

int is_empty_edge_queue(EDGE_QUEUE* q)
{
    return q->head == NULL ? 1 : 0;
}

int enqueue_edge(EDGE_QUEUE* q, EDGE* e)
{
    if (q == NULL || e == NULL)
        return FAILURE;

    e->next = NULL;

    if (is_empty_edge_queue(q))
        q->head = q->tail = e;

    else {
        q->tail->next = e;
        q->tail = e;
    }

    return SUCCESS;
}

EDGE* dequeue_edge(EDGE_QUEUE* q)
{
    EDGE* dequeued;

    if (is_empty_edge_queue(q))
        dequeued = NULL;

    else {
        dequeued = q->head;
        if (q->head == q->tail)
            q->head = q->tail = NULL;
        else
            q->head = q->head->next;
    }

    return dequeued;
}

// --- Graph & related operations

typedef struct GRAPH {
    int numOfNodes;
    EDGE_QUEUE* queues;
} GRAPH;

int initialize(GRAPH* g)
{
    int n, i;
    EDGE_QUEUE* q;

    printf("Enter number of nodes: ");
    scanf("%d", &n);
    flush();

    if (n < 0) // negative
    {
        g->numOfNodes = -1;
        return FAILURE;
    } else if (n == 0) // zero
    {
        g->queues = NULL;
        return SUCCESS;
    } else // positive
    {
        q = (EDGE_QUEUE*)malloc(n * sizeof *q);
        if (q) {
            for (i = 0; i < n; ++i)
                q[i].head = q[i].tail = NULL;

            g->queues = q;
            g->numOfNodes = n;

            return SUCCESS;
        } else // allocation un-successful
        {
            g->numOfNodes = -1;
            return FAILURE;
        }
    }
}

int add_edge(EDGE_QUEUE* q, EDGE* e)
{
    if (e == NULL) {
        printf("\n\nCan't add edge; edge passed to add_edge() is NULL.\n");
        return FAILURE;
    }

    if (enqueue_edge(q, e) == FAILURE) {
        printf("\n\nCan't add edge: enqueue_edge() failed!\n");
        return FAILURE;
    }

    // else
    printf("\nEdge added.\n");
    return SUCCESS;
}

// removes and edge from the given queue
// without violating the queue property
int rem_edge(EDGE_QUEUE* q, int dst_val)
{
    EDGE_QUEUE tmp_q = { NULL, NULL };
    EDGE* dequeued;

    if (q == NULL) {
        return FAILURE;
        printf("\n\nInvalid source for edge removal: queue passed is NULL\n\n");
    }

    // dequeue each edge from q and
    // enqueue it into tmp_q if its
    // destination is same as 'dst'
    while (!is_empty_edge_queue(q)) {
        dequeued = dequeue_edge(q);
        if (value(dequeued->dst) != dst_val)
            enqueue_edge(&tmp_q, dequeued);
        else
            free(dequeued);
    }

    // dequeue each node from tmp_q
    // and enqueue it into q
    while (!is_empty_edge_queue(&tmp_q))
        enqueue_edge(q, dequeue_edge(&tmp_q));

    printf("\nEdge removed.\n");
    return SUCCESS;
}

int exists_edge(GRAPH* g, EDGE* e)
{
    int i;
    EDGE_QUEUE q;
    EDGE* __e;

    for (i = 0; i < g->numOfNodes; ++i) {
        q = g->queues[i];
        while (!is_empty_edge_queue(&q)) {
            __e = dequeue_edge(&q);
            if (value(e->src) == value(__e->src) && value(e->src) == value(__e->dst))
                return TRUE;
        }
    }

    return FALSE;
}

EDGE* get_edge(GRAPH* g, int is_weighted)
{
    int i, src_val, dst_val, wt;

    printf("\nsrc & dst: ");
    scanf("%d %d", &src_val, &dst_val);
    flush();

    if (src_val < 0 || src_val >= g->numOfNodes
        || dst_val < 0 || dst_val >= g->numOfNodes
        || src_val == dst_val) {

        printf("\nInvalid Edge!!\n");
        return NULL;
    }

    if (is_weighted) {
        printf("\nweight: ");
        scanf("%d", &wt);
        flush();
        if (wt <= 0) {
            printf("\nInvalid Weight!!\n");
            return NULL;
        }
    }

    // else
    return newEDGE(src_val, dst_val, wt);
}

void display_edges(GRAPH* g)
{
    int i;
    EDGE* e;
    for (i = 0; i < g->numOfNodes; ++i)
        for (e = g->queues[i].head; e != NULL; e = e->next)
            printf(" (%d, %d, %d)\n", e->src->info, e->dst->info, e->wt);
}

void REL_MEM(GRAPH* g)
{
    int i;
    EDGE *n, *cur;

    // for each queue
    for (i = 0; i < g->numOfNodes; ++i) {
        // free all its elements
        n = g->queues[i].head;
        while (n) {
            cur = n;
            n = n->next;
            free(cur);
        }
    }

    // free the queue array
    free(g->queues);

    // graph becomes empty
    g->queues = NULL;
    g->numOfNodes = 0;
}

// --- Stack of Nodes

typedef struct STACK {
    NODE* top;
} STACK;

int is_empty_stack(STACK s)
{
    return s.top == NULL ? 1 : 0;
}

int push(STACK* S, NODE* node)
{
    if (is_empty_stack(*S)) {
        node->next = NULL;
        S->top = node;
        return SUCCESS;
    }

    // else
    node->next = S->top;
    S->top = node;

    return SUCCESS;
}

NODE* pop(STACK* S)
{
    NODE* popped;

    if (S->top == NULL)
        return NULL;

    // else
    popped = S->top;
    S->top = S->top->next;

    return popped; // freed in bfs / dfs
}

// --- Queue of Nodes

typedef struct QUEUE {
    NODE *head, *tail;
} QUEUE;

int is_empty_queue(QUEUE q)
{
    return q.head == NULL ? 1 : 0;
}

int enqueue(QUEUE* Q, NODE* node)
{
    node->next = NULL;

    if (is_empty_queue(*Q)) {
        Q->head = Q->tail = node;
        return 0;
    }

    // else
    Q->tail->next = node;
    Q->tail = node;

    return 0;
}

NODE* dequeue(QUEUE* Q)
{
    NODE* dequeued;

    if (Q->head == NULL)
        dequeued = NULL;
    else {
        dequeued = Q->head;
        Q->head = dequeued->next;
    }

    return dequeued;
}

// --- DFS

int DFS(GRAPH G, int start_val)
{
    int i;
    char* status;
    STACK S = { NULL };
    NODE *cur, *start_node;
    EDGE* e;
    EDGE_QUEUE q;

    status = (char*)malloc(G.numOfNodes * sizeof(char));
    for (i = 0; i < G.numOfNodes; i++)
        status[i] = '0';

    start_node = newNODE(start_val);
    push(&S, start_node);

    while (!is_empty_stack(S)) {
        cur = pop(&S);
        if (status[value(cur)] == '0') {
            status[value(cur)] = '1';
            printf("%d ", value(cur));
            q = G.queues[value(cur)];
            while (!is_empty_edge_queue(&q)) {
                e = dequeue_edge(&q);
                if (status[value(e->dst)] == '0')
                    push(&S, e->dst);
            }
        }
    }

    free(start_node); // free the extra node created for start_val
    free(status);

    return SUCCESS;
}

// --- BFS

int BFS(GRAPH G, int start_val)
{
    int i;
    char* status;
    QUEUE Q;
    NODE *cur, *start_node;
    EDGE* e;
    EDGE_QUEUE q;

    status = (char*)malloc(G.numOfNodes * sizeof(char));
    for (i = 0; i < G.numOfNodes; i++)
        status[i] = '0';

    start_node = newNODE(start_val);

    status[value(start_node)] = '1';

    enqueue(&Q, start_node);

    while (!is_empty_queue(Q)) {
        cur = dequeue(&Q);
        printf("%d ", value(cur));
        q = G.queues[value(cur)];
        while (!is_empty_edge_queue(&q)) {
            e = dequeue_edge(&q);
            if (status[value(e->dst)] == '0') {
                status[value(e->dst)] = '1';
                enqueue(&Q, e->dst);
            }
        }
    }

    free(start_node);
    free(status);

    return SUCCESS;
}

// --- Menu

void main(void)
{
    GRAPH* g;
    EDGE* e;
    int i, n;

    clear();

    g = (GRAPH*)malloc(sizeof *g);
    int initialized = initialize(g);

    int done = 0;
    while (!done) // menu loop
    {
        if (initialized) {
            printf("\n\
  1 -- Add an edge\n\
  2 -- Remove an edge\n\
  3 -- Display information of all edges\n\
  4 -- DFS\n\
  5 -- BFS\n\
  q -- exit\n\
  \n\
  >>> ");

            switch (get_choice()) {
            case '1':
                clear();
                printf("Enter an edge to add\n");
                e = get_edge(g, WEIGHTED);
                if (e) {
                    if (exists_edge(g, e) == TRUE) {
                        printf("\nEdge already exists!!\n");
                        deleteEDGE(e);
                    } else if (add_edge(&(g->queues[value(e->src)]), e) == FAILURE)
                        deleteEDGE(e);
                }
                pause();
                break;

            case '2':
                clear();
                printf("Enter an edge to delete\n");
                e = get_edge(g, NON_WEIGHTED);
                if (e) {
                    if (exists_edge(g, e) == TRUE)
                        rem_edge(&(g->queues[value(e->dst)]), value(e->dst));
                    else
                        printf("\nEdge doesn't exist!!\n\n");
                }
                deleteEDGE(e);
                pause();
                break;

            case '3':
                clear();
                printf("Edges\n-----\n\n");
                display_edges(g);
                pause();
                break;

            case '4':
                clear();
                printf("\nDFS: Enter starting node: ");
                scanf("%d", &n);
                flush();
                DFS(*g, n);
                printf("\n");
                pause();
                break;

            case '5':
                clear();
                printf("\nBFS: Enter starting node: ");
                scanf("%d", &n);
                flush();
                BFS(*g, n);
                printf("\n");
                pause();
                break;

            case 'q':
                REL_MEM(g);
                done = 1; // to exit the menu loop
                break;
            }

            clear();
        } else {
            printf("\n\
  Message: Initialisation failed!\n\
  \n\
  r -- re-initialised\n\
  q -- exit\n\
  \n\
  >>> ");
            switch (get_choice()) {
            case 'r':
                clear();
                initialized = initialize(g);
                break;
            case 'q':
                done = 1; // to exit the menu loop
                break;
            }

            clear();
        }
    }
}
