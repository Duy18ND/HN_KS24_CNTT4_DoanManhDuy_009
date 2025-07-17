#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
typedef struct Product {
    int Id;
    char Name[100];
    int Price;
    int Quantity;
} Product;

typedef struct SingleNode {
    Product product;
    struct SingleNode* next;
} SingleNode;

typedef struct DoubleNode {
    Product product;
    struct DoubleNode* next;
    struct DoubleNode* prev;
} DoubleNode;
//Tao ham cap phat bo nho
SingleNode* createSingleNode(Product product) {
    SingleNode* node = (SingleNode*)malloc(sizeof(SingleNode));
    node->product = product;
    node->next = NULL;
    return node;
}
DoubleNode* createDoubleNode(Product product) {
    DoubleNode* node = (DoubleNode*)malloc(sizeof(DoubleNode));
    node->product = product;
    node->next = NULL;
    node->prev = NULL;
    return node;
}
//Ham kiem tra rong
int isEmptySingleNode(SingleNode* head) {
    return head == NULL;
}
int isEmptyDoubleNode(DoubleNode* head) {
    return head == NULL;
}

//Them vao cuoi
void addProduct(SingleNode** head, Product product) {
    SingleNode* newNode = createSingleNode(product);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    SingleNode* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}
//Them vao cuoi DSLK doi
void addDobleNode(DoubleNode** head, Product product) {
    DoubleNode* newNode = createDoubleNode(product);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    DoubleNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}
//Tao ham In
void printProduct(SingleNode** head) {
    //Kiem tra danh sach trong
    if (isEmptySingleNode(*head)) {
        printf("Danh sach rong!");
        return;
    }
    SingleNode* temp = *head;
    printf("In danh sach\n");
    while (temp != NULL) {
        printf("------------------------------------------\n");
        printf("ID: %d\n", temp->product.Id);
        printf("Name: %s\n", temp->product.Name);
        printf("Price: %d\n", temp->product.Price);
        printf("Quantity: %d\n", temp->product.Quantity);
        temp = temp->next;
    }
}
//Xoa san pham theo id
SingleNode* deleteProduct(SingleNode** head, int id) {
    if (isEmptySingleNode(*head)) {
        printf("Danh sach rong!\n");
        return NULL;
    }
    SingleNode* temp = *head;
    SingleNode* prev = NULL;
    while (temp != NULL) {
        if (temp->product.Id == id) {
            if (prev == NULL) {
                *head = temp->next;
            }
            else {
                prev->next = temp->next;
            }
            printf("Xoa thanh cong!\n");
            free(temp);
            return temp;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Khong tim thay ID can xoa\n");
}
//Kiem tra ten bi trung
int isDuplicateName(SingleNode* head, const char* name, int skipId) {
    while (head != NULL) {
        if (strcmp(head->product.Name, name) == 0 && head->product.Id != skipId) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

//Cap nhap san pham
void updateProduct(SingleNode** head, int id) {
    if (isEmptySingleNode(*head)) {
        printf("Danh sach rong!\n");
        return;
    }
    SingleNode* temp = *head;
    while (temp != NULL) {
        if (temp->product.Id == id) {
            printf("ID: %d\n", temp->product.Id);

            char newName[100];
            getchar();
            printf("Moi ban nhap ten san pham: ");
            fgets(newName, 100, stdin);
            newName[strcspn(newName, "\n")] = 0;

            // Kiem tra ten trung lap
            if (isDuplicateName(*head, newName, id)) {
                printf("Ten san pham da ton tai. Cap nhat that bai!\n");
                return;
            }

            strcpy(temp->product.Name, newName);
            printf("Moi ban nhap gia ban san pham: ");
            scanf("%d", &temp->product.Price);
            printf("Moi ban nhap so luong san pham: ");
            scanf("%d", &temp->product.Quantity);
            printf("Cap nhat thanh cong!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Khong tim thay ID can cap nhat\n");
}
//Danh dau san pham da ban
void markProduct(SingleNode** head, DoubleNode** soldHead, int id) {
    if (isEmptySingleNode(*head)) {
        printf("Danh sach san pham rong!\n");
        return;
    }

    SingleNode* temp = *head;
    SingleNode* prev = NULL;

    while (temp != NULL) {
        if (temp->product.Id == id) {
           addDobleNode(soldHead, temp->product);

            if (prev == NULL) {
                *head = temp->next;
            } else {
                prev->next = temp->next;
            }

            free(temp);
            printf("San pham ID %d da duoc danh dau la da ban.\n", id);
            return;
        }

        prev = temp;
        temp = temp->next;
    }
    printf("Khong tim thay san pham co ID = %d\n", id);
}
//In san pham da ban
void printDoubleNode(DoubleNode* head) {
    if (isEmptyDoubleNode(head)) {
        printf("Danh sach san pham da ban rong!\n");
        return;
    }

    DoubleNode* temp = head;
    printf("\n----- Danh sach san pham da ban -----\n");
    while (temp != NULL) {
        printf("------------------------------------------\n");
        printf("ID: %d\n", temp->product.Id);
        printf("Name: %s\n", temp->product.Name);
        printf("Price: %d\n", temp->product.Price);
        printf("Quantity: %d\n", temp->product.Quantity);
        temp = temp->next;
    }
}

//Sap xep
void sortProduct(SingleNode** head) {
    if (isEmptySingleNode(*head)) {
        printf("Danh sach rong!\n");
        return;
    }

    for (SingleNode* i = *head; i != NULL; i = i->next) {
        for (SingleNode*  j = i->next; j != NULL; j = j->next) {
            if (i->product.Price > j->product.Price) {
                Product tempProduct = i->product;
                i->product = j->product;
                j->product = tempProduct;
            }
        }
    }
}

int main(){
    int choice;
    int countId = 1;
    SingleNode* singleNode = NULL;
    DoubleNode* doubleNode = NULL;
    do {
        printf("\n---------------------MENU---------------------\n");
        printf("1. Them san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Xoa san phan theo id\n");
        printf("4. Cap nhap thong tin san pham\n");
        printf("5. Danh dau san pham da ban\n");
        printf("6. Hien thi danh sach san pham da ban\n");
        printf("7. Sap xep san phan theo gia tang dan\n");
        printf("8. Tim kiem san phan theo theo\n");
        printf("9. Thoat chuong trinh\n");
        printf("-------------------------------------------------\n");
        printf("Nhap chuc nang cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Product product;
                product.Id = countId++;
                printf("ID: %d\n", product.Id);
                getchar();
                printf("Moi ban nhap ten san phan: ");
                fgets(product.Name, 100, stdin);
                product.Name[strcspn(product.Name, "\n")] = 0;
                printf("Moi ban nhap gia ban san pham: ");
                scanf("%d", &product.Price);
                printf("Moi ban nhap so luong san pham: ");
                scanf("%d", &product.Quantity);
                addProduct(&singleNode, product);
                printf("Them san pham thanh cong!\n");
                break;
            case 2:
                printProduct(&singleNode);
                break;
            case 3:
                int DeleteId;
                printf("Moi ban nhap id san pham muon xoa: ");
                scanf("%d", &DeleteId);
                deleteProduct(&singleNode, DeleteId);
                break;
            case 4:
                int UpdateId;
                printf("Moi ban nhap id san pham muon cap nhat: ");
                scanf("%d", &UpdateId);
                updateProduct(&singleNode, UpdateId);
                break;
            case 5:
                if (isEmptySingleNode(singleNode)) {
                    printf("Danh sach san pham trong!\n");
                        break;
                }
                int soldId;
                printf("Nhap ID san pham muon danh dau da ban: ");
                scanf("%d", &soldId);
                markProduct(&singleNode, &doubleNode, soldId);
                break;
            case 6:
                printDoubleNode(doubleNode);
                break;
            case 7:
                sortProduct(&singleNode);
                break;
            case 8:

            case 9:
                printf("Cam on ban da su dung chuong trinh\n");
                return 1;
            default:
                printf("Chuc nang khong hop le. Vui long nhap lai!");
        }
    }while (choice != 9);
return 0;
}
