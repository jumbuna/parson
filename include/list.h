typedef enum ValueType {
    STRING,
    NUMBER,
    JSON,
    KYWRD,
    ARRAY,
} valuetype_e;

typedef struct Value {
    valuetype_e type;
    void *val;
} value_t;

/* key-val pair */
typedef struct Node {
    char *key;
    value_t *val;
    struct Node *next;
} node_t;

typedef struct List {
    int length;
    node_t *head, *tail;
} list_t;

node_t *NodeCreate();

void NodeDestroy(node_t *);

list_t *ListCreate();

// void ListInsertFront(list_t *, void *);

void ListInsertBack(list_t *, char *, void *);

void ListForEach(list_t *, void (*) (char *, void *));