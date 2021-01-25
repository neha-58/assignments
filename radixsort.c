#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define FORMAT "%x" // hex
#define BASE 16

// --- Coll

typedef struct
{
    int *data, count;
} Coll;

int initialize(Coll* c, int n)
{
    if (n < 1)
        return -1;
    c->count = n;
    c->data = (int*)malloc(n * sizeof(int));
    if (c->data != NULL)
        return 0;
    c->count = 0;
    return -2;
}

int entry(Coll c)
{
    int i;
    printf("\nInput\n\n");
    for (i = 0; i < c.count; i++)
        scanf(FORMAT, &c.data[i]);
}

int display(Coll c)
{
    int i;
    printf("\nOutput (sorted) \n\n");
    for (i = 0; i < c.count; i++) {
        printf(FORMAT, c.data[i]);
        printf("\n");
    }
    printf("\n");
}

typedef struct NODE {
    int info;
    struct NODE* next;
} NODE;

NODE* newNODE(int info)
{
    NODE* node;
    node = (NODE*)malloc(sizeof(NODE));
    node->info = info;
    node->next = NULL;
    return node;
}

typedef struct QUEUE {
    NODE *head, *tail;
} QUEUE;

int is_empty(QUEUE* q) { return q->head == NULL ? 1 : 0; }

int enqueue(QUEUE* Q, int data)
{
    NODE* node = newNODE(data);

    if (is_empty(Q)) {
        Q->head = Q->tail = node;
        return 0;
    }

    Q->tail->next = node;
    Q->tail = node;

    return 0;
}

int dequeue(QUEUE* Q)
{
    NODE* dequeued;
    int data;

    if (is_empty(Q))
        dequeued = NULL;
    else {
        dequeued = Q->head;
        Q->head = dequeued->next;
    }

    data = dequeued->info;
    free(dequeued);

    return data;
}

int radix_sort(Coll c, int radix)
{
    int i, j, t, k, largest, dig, exp, bucketIndex;
    QUEUE* buckets; // to be changed and test allocation

    // allocate buckets
    buckets = (QUEUE*)malloc(radix * sizeof(QUEUE));
    if (buckets == NULL)
        return -1;

    // inititlise buckets
    for (i = 0; i < radix; ++i)
        buckets[i].head = buckets[i].tail = NULL;

    // find largest
    largest = c.data[0];
    for (i = 1; i < c.count; ++i)
        if (largest < c.data[i])
            largest = c.data[i];

    // digits in the largest element
    for (dig = 0; largest != 0; largest /= radix)
        dig++;

    exp = 1;

    // 0 to (dig - 1) passes
    for (i = 0; i < dig; i++) {
        // bucketing
        for (j = 0; j < c.count; j++) {
            bucketIndex = (c.data[j] / exp) % radix;
            enqueue(&buckets[bucketIndex], c.data[j]);
        }

        // collect from buckets
        k = 0;
        for (j = 0; j < radix; j++)
            while (!is_empty(&buckets[j]))
                c.data[k++] = dequeue(&buckets[j]);

        exp *= radix;
    }

    return 0;
}

int main()
{
    Coll c;
    int size;

    printf("Enter size: ");
    scanf("%d", &size);

    initialize(&c, size);
    entry(c);

    radix_sort(c, BASE);
    display(c);

    return 0;
}
