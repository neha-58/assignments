#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define infotype float
#define format "%g" // or "%f"

void swap(infotype* arr, int a, int b)
{
    infotype t;
    t = arr[a];
    arr[a] = arr[b];
    arr[b] = t;
}

typedef struct
{
    int count;
    infotype* data;
} Coll;

int initialize(Coll* c, int size)
{
    if (size < 1)
        return -1;
    c->count = size;
    c->data = (infotype*)calloc(size, sizeof(infotype));
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
        scanf(format, &c.data[i]);
}

int display(Coll c)
{
    int i;
    printf("\nOutput\n\n");
    for (i = 0; i < c.count; i++) {
        printf(format, c.data[i]);
        printf(" ");
    }
    printf("\n\n");
}

typedef struct
{
    Coll c;
    int cur;
} Heap;

int initialize_heap(Heap* h, int max)
{
    int temp;
    h->cur = 0;
    temp = initialize(&(h->c), max);
    return temp;
}

int insert_heap(Heap* h, infotype e)
{
    int pos, par;

    if (h->cur == h->c.count)
        return 0;

    pos = h->cur;
    par = (pos - 1) / 2;

    h->c.data[pos] = e;

    while ((pos > 0) && (h->c.data[par] < h->c.data[pos])) {
        swap(h->c.data, pos, par);
        pos = par;
        par = (pos - 1) / 2;
    }

    h->cur += 1;
    return 0;
}

infotype delete_heap(Heap* h)
{
    int pos, l, r;
    infotype val;

    if (h->cur == 0)
        return 0;

    h->cur -= 1;

    val = h->c.data[0];
    h->c.data[0] = h->c.data[h->cur];

    pos = 0; // root
    l = 1; // root's left child
    r = 2; // root's right child

    while (1) {
        if ((l <= h->cur && r <= h->cur) && (h->c.data[pos] < h->c.data[l] || h->c.data[pos] < h->c.data[r])) {
            if (h->c.data[l] > h->c.data[r]) {
                swap(h->c.data, l, pos);
                pos = l;
            } else {
                swap(h->c.data, r, pos);
                pos = r;
            }
        } else if (l <= h->cur && h->c.data[pos] < h->c.data[l]) {
            swap(h->c.data, l, pos);
            pos = l;
        } else
            break;

        l = (2 * pos) + 1;
        r = (2 * pos) + 2;
    }

    return val;
}

int heap_sort(Heap* h)
{
    int i;
    infotype retval;

    for (i = 0; i < h->c.count; i++)
        insert_heap(h, h->c.data[i]);

    for (i = 0; i < h->c.count; i++) {
        retval = delete_heap(h);
        h->c.data[h->cur] = retval;
    }

    return 0;
}

void main()
{
    Heap h;
    int size;

    printf("\nEnter size: ");
    scanf("%d", &size);

    initialize_heap(&h, size);

    entry(h.c);

    heap_sort(&h);

    display(h.c);
}