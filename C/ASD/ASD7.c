#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct list {
    char symbol;
    struct list* next;
} Node;

// Функція створює список розміром amount (тобто N)
Node* createRandomList(int amount) {
    Node* head = NULL; 
    Node* newNode = NULL;

    for (int i = 0; i < amount; i++) {
        newNode = (Node*)malloc(sizeof(Node));
        // Генеруємо випадкову літеру
        newNode->symbol = 'A' + rand() % 26;
        newNode->next = head;
        head = newNode;
    }

    return head; 
}

// Функція видалення перших M елементів
Node* removeFirstM(Node* head, int M) {
    for (int i = 0; i < M; i++) {
        if (head == NULL) break;
        Node* temp = head;
        head = head->next; // Переходимо до наступного
        free(temp);        // Видаляємо поточний
    }
    return head;
}

void printlist(Node* head){
    if (head == NULL) {
        printf("Список порожній (NULL)\n");
        return;
    }
    Node* current = head;
    while (current != NULL) {
        printf("%c -> ", current->symbol);
        current = current->next;
    }
    printf("NULL\n");
}

Node* sortedlist(Node* head, char symbol){
    Node* newHead = NULL;
    while(head != NULL){
        if(head->symbol > symbol){
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->symbol = head->symbol;
            newNode->next = newHead; 
            newHead = newNode;
        }
        head = head->next;
    }
    return newHead;
}

void freeList(Node* head) {
    Node* temp = NULL;

    while (head != NULL) {
        temp = head->next; 
        free(head);       
        head = temp;       
    }
}

int main(){
    srand(time(NULL));
    int N, M;

    // 1. Введення N
    do {
        printf("Введіть N (0-15) для створення списку: ");
        scanf("%d", &N);
    } while (N < 0 || N > 15);

    // 2. Введення M
    do {
        printf("Введіть M (0-15) для видалення елементів: ");
        scanf("%d", &M);
    } while (M < 0 || M > 15);

    // 3. Створення списку на N елементів
    Node* head = createRandomList(N);
    printf("Початковий список (розмір %d):\n", N);
    printlist(head);

    // 4. Видалення M елементів
    head = removeFirstM(head, M);
    printf("Список після видалення %d елементів:\n", M);
    printlist(head);

    // 5. Створення відсортованого списку з елементів більших за 'K'
    Node* newHead = sortedlist(head, 'H');
    printf("Відсортований новий список (> 'H'):\n");
    printlist(newHead);

    freeList(head);
    freeList(newHead);
    return 0;
}