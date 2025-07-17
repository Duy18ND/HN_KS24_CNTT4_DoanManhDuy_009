#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Music {
    char NameMusic[100];
}Music;
typedef struct Queue {
    Music music;
    int front;
    int rear;
    int capacity;
} Queue;
typedef struct Stack {
    Music music;
    int top;
    int capacity;
}Stack;
Queue* createQueue(Music music) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    queue->music = music;
    return queue;
}
Stack* createStack(Music music) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    stack->music = music;
    return stack;
}
void pushQueue(Queue* queue, char name[100]) {
    if (queue->front == queue->capacity - 1) {
        printf("Danh sach da duoc khoi tao!\n");
        return;
    }
    queue->front++;
    queue->rear++;
    strcpy(queue->music.NameMusic, name);
}
//Case 2


int main() {
    int choice;
    Queue* queue = NULL;
    do {
        printf("---------------MENU---------------\n");
        printf("1. ADD\n");
        printf("2. PLAY NEXT\n");
        printf("3. PLAY PREVIOUS\n");
        printf("4. HISTORY\n");
        printf("5. EXIT\n");
        printf("----------------------------------\n");
        printf("Moi ban lua chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                char name[100];
                printf("Nhap ten bai hat moi: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = 0;
                pushQueue(queue, name);
                printf("Them bai hat thanh cong!\n");
                break;
            case 2:

                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                printf("Cam on ban da su dung chuong trinh\n");
                return 1;
                default:
                printf("Lua chon cua ban khong hop le. Vui long nhap lai!");

        }
    }while (choice != 5);
    return 0;
}
