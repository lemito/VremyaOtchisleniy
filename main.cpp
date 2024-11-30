#include <limits.h>
#include <limits.h>  // Для INT_MAX или INT_MIN
#include <stdio.h>
#include <stdlib.h>

#include <climits>

typedef struct node {
  int key;
  int val;
  node* l;
  node* r;
} node;

typedef struct tree {
  node* root;
  // cmp
} tree;

void tree_init(tree* tree) {
  tree->root = NULL;
  // cmp
}

node* insearch(tree* tr, int obj) {
  //
  node* nnew = (node*)malloc(sizeof(node));
  nnew->key = obj;
  nnew->l = nnew->r = NULL;
  if (tr->root == NULL) {
    tr->root = nnew;
    return NULL;
  }
  node* cur = tr->root;
  while (cur != NULL) {
    if (obj < cur->key) {
      if (cur->l == NULL) {
        cur->l = nnew;
        return NULL;
      }
      cur = cur->l;
    } else if (obj > cur->key) {
      if (cur->r == NULL) {
        cur->r = nnew;
        return NULL;
      }
      cur = cur->r;
    } else if (obj == cur->key) {
      // printf("%d нашел", obj);
      return cur;
    }
  }
  cur = nnew;
  return NULL;
}

void printt(node* node, int level) {
  if (node == NULL) return;

  printt(node->l, level + 1);
  for (size_t i = 0; i < level; i++) {
    printf("\t");
  }
  printf("%d", node->key);
  putchar('\n');
  printt(node->r, level + 1);
}

void print_tree(tree* tr) { printt(tr->root, 0); }

node* findMax_fromNode(node* tr) {
  node* cur = tr;
  while (cur->r != NULL) {
    cur = cur->r;
  }
  return cur;
}

node* findMin_fromNode(node* tr) {
  node* cur = tr;
  while (cur->l != NULL) {
    cur = cur->l;
  }
  return cur;
}

/*

        6
     4    9
    1 5  8  11
             12
*/
void remove(node** nodee) {
  //
  node* maxi = NULL;
  if ((*nodee)->l == NULL && (*nodee)->r == NULL) {
    free(*nodee);
    *nodee = NULL;
  } else if ((*nodee)->l == NULL && (*nodee)->r != NULL) {
    node* tmp = *nodee;
    *nodee = (*nodee)->r;
    free(tmp);
  } else if ((*nodee)->l != NULL && (*nodee)->r == NULL) {
    node* tmp = *nodee;
    *nodee = (*nodee)->l;
    free(tmp);
  } else {
    // maxi = findMax_fromNode(*nodee);
    node* tmp = *nodee;
    while (tmp->r->r != NULL) {
      tmp = tmp->r;
    }
    maxi = tmp->r;
    tmp->r = NULL;

    // swap сложно, ппоэтому скопирую
    (*nodee)->key = maxi->key;
    free(maxi);
    maxi = NULL;
  }
}

void destroy_node(node* nn) {
  if (nn == NULL) return;

  destroy_node(nn->l);
  destroy_node(nn->r);
  free(nn);
}

void destroy_tree(tree* tr) {
  if (tr == NULL) return;
  destroy_node(tr->root);
}

typedef struct uninode {
  int data;
  struct uninode* pNext;
} uninode;

typedef struct unilist {
  uninode* pHead;
  size_t size;
} unilist;

void init_list(unilist* li) {
  li->pHead = NULL;
  li->size = 0;
}

void traversal_unilist(unilist* li, void (*action)(uninode* li)) {
  //...
  uninode* cur = li->pHead;
  while (cur != NULL) {
    uninode* next = cur->pNext;
    action(cur);
    cur = next;
  }
}

void destroy_node(uninode* cur) { free(cur); }

void destroy_list(unilist* li) { traversal_unilist(li, destroy_node); }

void insert_li(unilist* li, size_t ix, int data) {
  uninode* ne = (uninode*)malloc(sizeof(uninode));
  ne->data = data;
  ne->pNext = NULL;
  if (ix == 0 || li->pHead == NULL) {
    ne->pNext = li->pHead;
    li->pHead = ne;
  }
  uninode* cur = li->pHead;
  for (size_t i = 0; i < ix - 1; i++) {
    if (cur->pNext == NULL) {
      return;
    }
    cur = cur->pNext;
  }
  ne->pNext = cur->pNext;
  cur->pNext = ne;
  li->size++;
}

void remove_li(unilist* li, size_t ix) {
  if (li->pHead == NULL) {
    return;
  }
  if (ix == 0) {
    uninode* tmp = li->pHead->pNext;
    free(li->pHead);
    li->pHead = tmp;
  }
  uninode* cur = li->pHead;
  for (size_t i = 0; i < ix - 1; i++) {
    if (cur->pNext == NULL) {
      return;
    }
    cur = cur->pNext;
  }
  uninode* need = cur->pNext->pNext;
  free(cur->pNext);
  cur->pNext = need;
}

void print_node(uninode* node) { printf("%d ", node->data); }

void print_li(unilist* li) {
  // ...
  uninode* cur = li->pHead;
  while (cur != NULL) {
    uninode* next = cur->pNext;
    printf("%d ", cur->data);
    cur = next;
  }
  return;
}

typedef struct queue {
  uninode* first;
  uninode* last;
} queue;

void queue_push(queue* q, int data) {
  uninode* ne = (uninode*)malloc(sizeof(uninode));
  ne->data = data;
  ne->pNext = NULL;
  if (q->first == NULL) {
    q->first = ne;
    // q->last
  }
  if (q->last) q->last->pNext = ne;
  q->last = ne;
}

int queue_pop(queue* q) {
  if (q == NULL) return INT_MAX;
  int res = q->first->data;
  uninode* tmp = q->first->pNext;
  free(q->first);
  q->first = tmp;
  return res;
}

// структура для узла дерева биноминальной кучи
typedef struct BinomialNode {
  int key;                      // значение узла
  int degree;                   // степень узла
  struct BinomialNode* parent;  // указатель на родителя
  struct BinomialNode* child;  // указатель на самое левое поддерево
  struct BinomialNode* sibling;  // указатель на правое "соседнее" дерево
} BinomialNode;

// структура для биноминальной кучи
typedef struct BinomialHeap {
  BinomialNode* head;  // указатель на список деревьев
} BinomialHeap;

// Создание нового узла биноминальной кучи
BinomialNode* createNode(int key) {
  BinomialNode* newNode = (BinomialNode*)malloc(sizeof(BinomialNode));
  newNode->key = key;
  newNode->degree = 0;
  newNode->parent = NULL;
  newNode->child = NULL;
  newNode->sibling = NULL;
  return newNode;
}

// Создание пустой биномиальной кучи
BinomialHeap* createHeap() {
  BinomialHeap* heap = (BinomialHeap*)malloc(sizeof(BinomialHeap));
  heap->head = NULL;
  return heap;
}

void freeNode(BinomialNode* node) {
  if (!node) return;

  freeNode(node->child);
  freeNode(node->sibling);
  free(node);
}

void freeHeap(BinomialHeap* heap) {
  if (!heap) return;
  freeNode(heap->head);
  free(heap);
}

BinomialHeap* destroyHeap(BinomialHeap* heap) {
  freeHeap(heap);
  return NULL;
}

// Слияние двух биномиальных деревьев одинаковой степени
BinomialNode* mergeTrees(BinomialNode* t1, BinomialNode* t2) {
  if (t1->key > t2->key) {  // Пусть t1 всегда будет с наименьшим ключом
    BinomialNode* temp = t1;
    t1 = t2;
    t2 = temp;
  }
  t2->parent = t1;
  t2->sibling = t1->child;
  t1->child = t2;
  t1->degree++;
  return t1;
}

// Слияние двух списков деревьев
BinomialNode* mergeHeaps(BinomialNode* h1, BinomialNode* h2) {
  if (!h1) return h2;
  if (!h2) return h1;

  BinomialNode* result = NULL;
  if (h1->degree <= h2->degree) {
    result = h1;
    h1 = h1->sibling;
  } else {
    result = h2;
    h2 = h2->sibling;
  }

  BinomialNode* current = result;
  while (h1 && h2) {
    if (h1->degree <= h2->degree) {
      current->sibling = h1;
      h1 = h1->sibling;
    } else {
      current->sibling = h2;
      h2 = h2->sibling;
    }
    current = current->sibling;
  }

  if (h1) current->sibling = h1;
  if (h2) current->sibling = h2;

  return result;
}

// Объединение двух биноминальных куч
BinomialHeap* unionHeaps(BinomialHeap* h1, BinomialHeap* h2) {
  BinomialHeap* newHeap = createHeap();
  newHeap->head = mergeHeaps(h1->head, h2->head);

  if (!newHeap->head) return newHeap;

  BinomialNode* prev = NULL;
  BinomialNode* current = newHeap->head;
  BinomialNode* next = current->sibling;

  while (next) {
    if ((current->degree != next->degree) ||
        (next->sibling && next->sibling->degree == current->degree)) {
      prev = current;
      current = next;
    } else {
      if (current->key <= next->key) {
        current->sibling = next->sibling;
        current = mergeTrees(current, next);
      } else {
        if (prev == NULL) {
          newHeap->head = next;
        } else {
          prev->sibling = next;
        }
        current = mergeTrees(next, current);
      }
    }
    next = current->sibling;
  }

  return newHeap;
}

// Вставка нового узла в биномиальную кучу
void insert(BinomialHeap* heap, int key) {
  BinomialHeap* tempHeap = createHeap();
  tempHeap->head = createNode(key);

  heap->head = unionHeaps(heap, tempHeap)->head;

  free(tempHeap);
}

// Поиск минимального элемента в биномиальной куче
BinomialNode* findMinNode(BinomialHeap* heap) {
  if (!heap->head) return NULL;

  BinomialNode* minNode = heap->head;
  int minValue = minNode->key;

  BinomialNode* current = minNode->sibling;
  while (current) {
    if (current->key < minValue) {
      minValue = current->key;
      minNode = current;
    }
    current = current->sibling;
  }

  return minNode;
}

int findMin(BinomialHeap* heap) {
  if (heap == NULL) return 0;
  return findMinNode(heap)->key;
}

// Удаление минимального элемента из биномиальной кучи
void extractMin(BinomialHeap* heap) {
  if (!heap->head) return;

  // Найти минимальное дерево
  BinomialNode* minNode = heap->head;
  BinomialNode* minNodePrev = NULL;
  BinomialNode* prev = NULL;
  BinomialNode* current = heap->head;

  while (current) {
    if (current->key < minNode->key) {
      minNode = current;
      minNodePrev = prev;
    }
    prev = current;
    current = current->sibling;
  }

  // Удалить минимальное дерево из корневого списка
  if (minNodePrev) {
    minNodePrev->sibling = minNode->sibling;
  } else {
    heap->head = minNode->sibling;
  }

  // Перевернуть список детей минимального узла
  BinomialNode* child = minNode->child;
  BinomialNode* reverse = NULL;
  while (child) {
    BinomialNode* next = child->sibling;
    child->sibling = reverse;
    reverse = child;
    child = next;
  }

  // Создать временную кучу из перевёрнутого списка
  BinomialHeap* tempHeap = createHeap();
  tempHeap->head = reverse;

  // Объединить временную кучу с текущей
  heap->head = unionHeaps(heap, tempHeap)->head;

  // Освободить память
  free(minNode);
  free(tempHeap);
}

struct binary_heap {
  int* data;
  size_t size;
  size_t capacity;
  int (*cmp)(int*, int*);
};

typedef struct binary_heap binary_heap;

int cnt(int* a, int* b) { return *a - *b; }

int init_bin_heap(binary_heap* elem, size_t siz) {
  elem->cmp = cnt;
  elem->data = (int*)malloc(sizeof(int) * siz);
  if (elem->data == NULL) {
    return -1;
  }
  elem->capacity = siz;
  elem->size = 0;
  return 0;
}

void destroy_bin_heap(binary_heap* elem) { free(elem->data); }

void swap(int* a, int* b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void bubble_up(binary_heap* heap, size_t index) {
  while (index > 0) {
    size_t parent = (index - 1) / 2;
    if (heap->cmp(&heap->data[parent], &heap->data[index]) <= 0) {
      break;
    }
    swap(&heap->data[parent], &heap->data[index]);
    index = parent;
  }
}

void bubble_down(binary_heap* heap, size_t index) {
  size_t left, right, smallest;

  while (index < heap->size) {
    left = 2 * index + 1;
    right = 2 * index + 2;
    smallest = index;

    if (left < heap->size &&
        heap->cmp(&heap->data[left], &heap->data[smallest]) < 0) {
      smallest = left;
    }
    if (right < heap->size &&
        heap->cmp(&heap->data[right], &heap->data[smallest]) < 0) {
      smallest = right;
    }
    if (smallest == index) {
      break;
    }
    swap(&heap->data[index], &heap->data[smallest]);
    index = smallest;
  }
}

int pop_bin_heap(binary_heap* elem) {
  if (elem->size == 0) {
    return -1;  // Куча пуста
  }
  int res = elem->data[0];
  elem->data[0] = elem->data[--elem->size];
  bubble_down(elem, 0);
  return res;
}

int push_bin_heap(binary_heap* elem, int value) {
  if (elem->size >= elem->capacity) {
    elem->capacity *= 2;
    int* tmp = (int*)realloc(elem->data, sizeof(int) * elem->capacity);
    if (tmp == NULL) {
      free(elem->data);
      return -1;
    }
    elem->data = tmp;
  }
  elem->data[elem->size++] = value;
  bubble_up(elem, elem->size - 1);
  return 0;
}

int main(int argc, char* argv[]) {
  // binary_heap meow;

  // if (init_bin_heap(&meow, 10) != 0) {
  //   fprintf(stderr, "Не удалось инициализировать бинарную кучу.\n");
  //   return EXIT_FAILURE;
  // }

  // int test[] = {7, 5, 3, 1, 5, 9, 8, 4, 6, 2, 10, 100, 52, 25, 55, 78, 88};

  // for (size_t i = 0; i < sizeof(test) / sizeof(test[0]); i++) {
  //   push_bin_heap(&meow, test[i]);
  // }

  // printf("Извлеченные значения из кучи:\n");

  // while (meow.size > 0) {
  //   printf("%d ", pop_bin_heap(&meow));
  // }

  // printf("\n");

  // destroy_bin_heap(&meow);

  // BinomialHeap* heap = createHeap();

  // insert(heap, 10);
  // insert(heap, 20);
  // insert(heap, 5);
  // insert(heap, 15);

  // BinomialNode* minNode = findMinNode(heap);
  // if (minNode) printf("\nMinimum element: %d\n", minNode->key);

  // extractMin(heap);

  // destroyHeap(heap);

  // unilist meow;
  // init_list(&meow);

  // insert_li(&meow, 0, 0);
  // insert_li(&meow, 1, 1);
  // insert_li(&meow, 2, 2);

  // print_li(&meow);
  // putchar('\n');

  // remove_li(&meow, 1);
  // print_li(&meow);
  // putchar('\n');

  // queue qq;
  // qq.first = qq.last = NULL;
  // queue_push(&qq, 1);
  // queue_push(&qq, 2);
  // queue_push(&qq, 3);
  // queue_push(&qq, 4);
  // int a = queue_pop(&qq);
  // int b = queue_pop(&qq);
  // printf("%d %d", a, b);

  tree meow;
  tree_init(&meow);
  insearch(&meow, 6);
  insearch(&meow, 4);
  insearch(&meow, 9);
  insearch(&meow, 1);
  insearch(&meow, 5);
  insearch(&meow, 8);
  insearch(&meow, 11);
  insearch(&meow, 12);

  node* ch = insearch(&meow, 4);

  remove(&ch);

  print_tree(&meow);

  return EXIT_SUCCESS;
}
