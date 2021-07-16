#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)
typedef struct client {
    char* id;
    char* password;
    char* name;
    struct client* nextNode;
}client;
typedef struct dictionary
{
    char* eng;
    char* kor;
    struct dictionary* nextNode;
}dictionary;

dictionary* dictionaryHeadNode;
client* clientHeadNode;

int loginCheckNum;  //�α����̸� 1, �α׾ƿ��̸� 0
char loginClientID[100];

void menu(void);
///
void signUp();
void linkedLIstForSignUp(char* v, char* w, char* x);
void writeToSignUpFile();
///
void logIn();
void logOut();
///
void englishWordGame();
void linkedLIstForEnglishWordGame(char* v, char* w);
void sort();
///
void signOut();
///
void exitProgram();
int main()
{
    menu();
}
void menu(void) {
    while (1) {
        printf("=======================================\n");
        printf("============= 2021 SPLUG ==============\n");
        printf("=======================================");
        if (loginCheckNum) {  //�α��� ������ �� ���̵� ���
            for (int i = 0; i < strlen(loginClientID); i++) { printf("\b"); }
            printf("%s", loginClientID);
        }
        printf("\n=======================================\n");
        printf("=                �޴�                 =\n");
        printf("=======================================\n");
        printf("\t1.ȸ������\n\t2.�α���\n\t3.�α׾ƿ�\n\t4.���� �ܾ� ���߱�\n\t5.ȸ��Ż��\n\t6.���α׷� ����\n");
        printf("=======================================\n");
        printf(":");

        int num;
        scanf("%d", &num);
        switch (num) {
        case 1:
            printf("ȸ������ ������\n");
            signUp();
            break;
        case 2:
            printf("�α���\n");
            logIn();
            break;
        case 3:
            logOut();
            break;
        case 4:
            englishWordGame();
            break;
        case 5:
            signOut();
            break;
        case 6:
            exitProgram();
            break;
        default:
            printf("������ �� ���� �޴��Դϴ�.");
        }
        if (num == 6) { break; }
    }
}
void signUp() {
    char tempID[100];
    char tempPassword[100];
    char tempName[100];

    printf("���̵� : ");
    scanf("%s", tempID);

    //���̵� �ߺ�����ó��
    if (clientHeadNode == NULL) {
        ;
    }
    else {
        client* temp = clientHeadNode;
        int c = 1;
        while (temp->nextNode != NULL)
        {
            temp = temp->nextNode;
            c++;
        }

        temp = clientHeadNode;
        int i;
        for (i = 0; i < c; i++) {
            if (strcmp(temp->id, tempID) == 0) {
                printf("�̹� �����ϴ� ���̵� �Դϴ�.\n");
                signUp();   //�̹� �����ϴ� ���̵��̸� �Լ���ȣ��
                return;
            }
            temp = temp->nextNode;
        }
    }

    //��� ���� ���̵�� ��й�ȣ, �̸� �Է�
    printf("��� ������ ���̵� �Դϴ�.\n");

    printf("��й�ȣ : ");
    scanf("%s", tempPassword);
    printf("�̸� : ");
    scanf("%s", tempName);

    linkedLIstForSignUp(tempID, tempPassword, tempName);//���Ḯ��Ʈ�� client ���� ����
    writeToSignUpFile();//�ܺ� ���Ͽ� client ���� ���
}
void linkedLIstForSignUp(char* v, char* w, char* x)
{
    client* newNode = (client*)malloc(sizeof(client));
    newNode->id = malloc(sizeof(strlen(v) + 1));
    strcpy(newNode->id, v);
    newNode->password = malloc(sizeof(strlen(w) + 1));
    strcpy(newNode->password, w);
    newNode->name = malloc(sizeof(strlen(x) + 1));
    strcpy(newNode->name, x);

    newNode->nextNode = clientHeadNode;
    clientHeadNode = newNode;
}
void writeToSignUpFile() {
    if (clientHeadNode == NULL) { return; }   //���� ��� ���� ������ ����

    FILE* signUpFile;
    if ((signUpFile = fopen("SignUpFile.txt", "w")) == NULL) { //����ó��
        printf("����: fopen(\"SingUpFile\") ����");
        return;
    }

    client* temp = clientHeadNode;
    while (temp->nextNode != NULL)
    {
        fprintf(signUpFile, "%s %s %s\n", temp->id, temp->password, temp->name);
        temp = temp->nextNode;
    }
    fprintf(signUpFile, "%s %s %s", temp->id, temp->password, temp->name);

    fclose(signUpFile);
}
void logIn() {
    char tempID[100], tempPassword[100];
    printf("���̵� : ");
    scanf("%s", tempID);
    printf("��й�ȣ : ");
    scanf("%s", tempPassword);

    if (clientHeadNode == NULL) { printf("�߸��� �Է� �Ǵ� ���� ȸ���Դϴ�.\n"); }    //����ó��
    else {
        client* temp = clientHeadNode;
        int c = 1;
        while (temp->nextNode != NULL)
        {
            temp = temp->nextNode;
            c++;    //���Ḯ��Ʈ ��� �� count
        }

        temp = clientHeadNode;
        int i;
        for (i = 0; i < c; i++) {
            if (strcmp(temp->id, tempID) == 0 && strcmp(temp->password, tempPassword) == 0) { break; }  //���Ḯ��Ʈ�� id�� �����ϸ� �α��� ���·� ��ȯ
            temp = temp->nextNode;
        }

        if (i == c) {   //���Ḯ��Ʈ�� id�� �������� ������ �α��� �Ұ� �޽��� ���
            printf("���̵� ��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �õ��ϼ���.\n");
            logIn();
            return;
        }
        else {  //�α��� ���·� ��ȯ ���� ���������� ���� ��ȯ
            loginCheckNum = 1;
            strcpy(loginClientID, temp->id);
        }
    }
}
void logOut() {
    if (loginCheckNum == 1) {
        printf("���� �α׾ƿ� �Ͻðڽ��ϱ�? [y/n] : ");
        getchar();
        char c = getchar();
        if (c == 'y' || c == 'Y') { loginCheckNum = 0; }    //�α��� �����̰� Y �Է� �� �α׾ƿ�
        else if (c == 'n' || c == 'N') { return; }    //N �Է� �� �Լ� ����
        else {   //�� �� ���� �Է� ��
            printf("������ �� ���� �޴��Դϴ�.\n");
            return;
        }
    }
    else {
        printf("�α��� ���� �ʾҽ��ϴ�. �ٽ� �õ��ϼ���.\n");
    }
}
void englishWordGame() {
    printf(">>���� �ܾ� ���߱� ���α׷�<<\n");
    printf("1. ���� �ܾ� ���߱�\t2. ���α׷� ����\n\n");

    int num;
    printf("��ȣ�� �����ϼ��� : ");
    scanf("%d", &num);
    switch (num) {
    case 1:
        break;  //����ġ�� Ż�� �� ���� ����
    case 2:
        return; //�Լ� ����
    default:
        printf("������ �� ���� ��ȣ�Դϴ�.");
        return;
    }
    FILE* dictionaryFile = fopen("dic.txt", "r");
    char v[100], w[100];
    while (1)
    {
        fscanf(dictionaryFile, "%s %s", v, w);

        if (feof(dictionaryFile)) { break; }   //���� ���� �����ϸ� while�� Ż��
        else
        {
            linkedLIstForEnglishWordGame(v, w);    //���Ḯ��Ʈ�� ����
        }
    }
    sort(); //���Ḯ��Ʈ�� ������������ ���� & ���� ����
    fclose(dictionaryFile);
}
void linkedLIstForEnglishWordGame(char* v, char* w)
{
    dictionary* newNode = (dictionary*)malloc(sizeof(dictionary));
    newNode->eng = malloc(sizeof(strlen(v) + 1));
    strcpy(newNode->eng, v);
    newNode->kor = malloc(sizeof(strlen(w) + 1));
    strcpy(newNode->kor, w);
    newNode->nextNode = dictionaryHeadNode;
    dictionaryHeadNode = newNode;
}
void sort()
{
    dictionary* temp = dictionaryHeadNode;
    int c = 1;
    while (temp->nextNode != NULL)
    {
        temp = temp->nextNode;
        c++;
    }
    temp = dictionaryHeadNode;
    char x[100];
    char y[100];
    for (int i = 0; i < c; i++)
    {
        temp = dictionaryHeadNode;
        while (temp->nextNode != NULL)
        {
            if (strcmp(temp->eng, temp->nextNode->eng) > 0)
            {
                strcpy(x, temp->eng);
                strcpy(temp->eng, temp->nextNode->eng);
                strcpy(temp->nextNode->eng, x);

                strcpy(y, temp->kor);
                strcpy(temp->kor, temp->nextNode->kor);
                strcpy(temp->nextNode->kor, y);
            }
            temp = temp->nextNode;
        }
    }

    double score = 0;
    temp = dictionaryHeadNode;
    while (temp != NULL)
    {
        char z[100];
        printf("%s -> ", temp->kor);
        scanf("%s", z);
        if (strcmp(z, temp->eng) == 0) {
            printf("correct!\n");
            score += 1;
            temp = temp->nextNode;
        }
        else if (strcmp(z, ".quit") == 0) {
            break;
        }
        else {
            printf("incorrect!\n");
            temp = temp->nextNode;
        }
    }
    printf("����� ������ %.2lf�� �Դϴ�.\n\n", score);
}
void signOut()
{
    if (loginCheckNum == 1) {
        printf("���� ȸ���� Ż���Ͻðڽ��ϱ�? [y/n] : ");
        getchar();
        char c = getchar();
        if (c == 'y' || c == 'Y') { loginCheckNum = 0; }    //�α��� �����̰� Y �Է� �� �������� �α��� ���� �ٲٱ�
        else if (c == 'n' || c == 'N') { return; }    //N �Է� �� �Լ� ����
        else {
            printf("������ �� ���� �޴��Դϴ�.\n");
            return;
        }

        client* temp = clientHeadNode;
        client* prev=NULL;

        //����� ����
        if (temp != NULL && strcmp(temp->id, loginClientID) == 0) {
            clientHeadNode = temp->nextNode; // ��尡 ����Ű�� ��� �̵�
            free(temp); // ���� ����� free()
        }
        else {
            //�α���idŽ�� & preNode�� tempNode�� ���� ��带 �����ϰ� tempNode�� free()
            while (temp != NULL && strcmp(temp->id, loginClientID) != 0) {
                prev = temp;
                temp = temp->nextNode;
            }
            prev->nextNode = temp->nextNode;
            free(temp);
        }
        writeToSignUpFile();
    }
    else {
        printf("�α��� ���°� �ƴմϴ�.\n");
    }
}
void exitProgram() {
    system("clear");    //�͹̳� ȭ�� clear �� ���α׷� ����
    printf("������ �� ������ !!\n");
}