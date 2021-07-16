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

int loginCheckNum;  //로그인이면 1, 로그아웃이면 0
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
        if (loginCheckNum) {  //로그인 상태일 때 아이디 출력
            for (int i = 0; i < strlen(loginClientID); i++) { printf("\b"); }
            printf("%s", loginClientID);
        }
        printf("\n=======================================\n");
        printf("=                메뉴                 =\n");
        printf("=======================================\n");
        printf("\t1.회원가입\n\t2.로그인\n\t3.로그아웃\n\t4.영어 단어 맞추기\n\t5.회원탈퇴\n\t6.프로그램 종료\n");
        printf("=======================================\n");
        printf(":");

        int num;
        scanf("%d", &num);
        switch (num) {
        case 1:
            printf("회원가입 페이지\n");
            signUp();
            break;
        case 2:
            printf("로그인\n");
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
            printf("선택할 수 없는 메뉴입니다.");
        }
        if (num == 6) { break; }
    }
}
void signUp() {
    char tempID[100];
    char tempPassword[100];
    char tempName[100];

    printf("아이디 : ");
    scanf("%s", tempID);

    //아이디 중복예외처리
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
                printf("이미 존재하는 아이디 입니다.\n");
                signUp();   //이미 존재하는 아이디이면 함수재호출
                return;
            }
            temp = temp->nextNode;
        }
    }

    //사용 가능 아이디면 비밀번호, 이름 입력
    printf("사용 가능한 아이디 입니다.\n");

    printf("비밀번호 : ");
    scanf("%s", tempPassword);
    printf("이름 : ");
    scanf("%s", tempName);

    linkedLIstForSignUp(tempID, tempPassword, tempName);//연결리스트에 client 정보 저장
    writeToSignUpFile();//외부 파일에 client 정보 출력
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
    if (clientHeadNode == NULL) { return; }   //파일 출력 내용 없으면 종료

    FILE* signUpFile;
    if ((signUpFile = fopen("SignUpFile.txt", "w")) == NULL) { //오류처리
        printf("오류: fopen(\"SingUpFile\") 실패");
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
    printf("아이디 : ");
    scanf("%s", tempID);
    printf("비밀번호 : ");
    scanf("%s", tempPassword);

    if (clientHeadNode == NULL) { printf("잘못된 입력 또는 없는 회원입니다.\n"); }    //예외처리
    else {
        client* temp = clientHeadNode;
        int c = 1;
        while (temp->nextNode != NULL)
        {
            temp = temp->nextNode;
            c++;    //연결리스트 노드 수 count
        }

        temp = clientHeadNode;
        int i;
        for (i = 0; i < c; i++) {
            if (strcmp(temp->id, tempID) == 0 && strcmp(temp->password, tempPassword) == 0) { break; }  //연결리스트에 id가 존재하면 로그인 상태로 전환
            temp = temp->nextNode;
        }

        if (i == c) {   //연결리스트에 id가 존재하지 않으면 로그인 불가 메시지 출력
            printf("아이디나 비밀번호가 틀렸습니다. 다시 시도하세요.\n");
            logIn();
            return;
        }
        else {  //로그인 상태로 전환 위해 전역변수의 정보 변환
            loginCheckNum = 1;
            strcpy(loginClientID, temp->id);
        }
    }
}
void logOut() {
    if (loginCheckNum == 1) {
        printf("정말 로그아웃 하시겠습니까? [y/n] : ");
        getchar();
        char c = getchar();
        if (c == 'y' || c == 'Y') { loginCheckNum = 0; }    //로그인 상태이고 Y 입력 시 로그아웃
        else if (c == 'n' || c == 'N') { return; }    //N 입력 시 함수 종료
        else {   //그 외 문자 입력 시
            printf("선택할 수 없는 메뉴입니다.\n");
            return;
        }
    }
    else {
        printf("로그인 되지 않았습니다. 다시 시도하세요.\n");
    }
}
void englishWordGame() {
    printf(">>영어 단어 맞추기 프로그램<<\n");
    printf("1. 영어 단어 맞추기\t2. 프로그램 종료\n\n");

    int num;
    printf("번호를 선택하세요 : ");
    scanf("%d", &num);
    switch (num) {
    case 1:
        break;  //스위치문 탈출 후 게임 진행
    case 2:
        return; //함수 종료
    default:
        printf("선택할 수 없는 번호입니다.");
        return;
    }
    FILE* dictionaryFile = fopen("dic.txt", "r");
    char v[100], w[100];
    while (1)
    {
        fscanf(dictionaryFile, "%s %s", v, w);

        if (feof(dictionaryFile)) { break; }   //파일 끝에 도달하면 while문 탈출
        else
        {
            linkedLIstForEnglishWordGame(v, w);    //연결리스트에 저장
        }
    }
    sort(); //연결리스트를 오름차순으로 정렬 & 게임 진행
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
    printf("당신의 점수는 %.2lf점 입니다.\n\n", score);
}
void signOut()
{
    if (loginCheckNum == 1) {
        printf("정말 회원을 탈퇴하시겠습니까? [y/n] : ");
        getchar();
        char c = getchar();
        if (c == 'y' || c == 'Y') { loginCheckNum = 0; }    //로그인 상태이고 Y 입력 시 전역변수 로그인 상태 바꾸기
        else if (c == 'n' || c == 'N') { return; }    //N 입력 시 함수 종료
        else {
            printf("선택할 수 없는 메뉴입니다.\n");
            return;
        }

        client* temp = clientHeadNode;
        client* prev=NULL;

        //헤드노드 삭제
        if (temp != NULL && strcmp(temp->id, loginClientID) == 0) {
            clientHeadNode = temp->nextNode; // 헤드가 가르키는 노드 이동
            free(temp); // 이전 헤드노드 free()
        }
        else {
            //로그인id탐색 & preNode와 tempNode의 다음 노드를 연결하고 tempNode를 free()
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
        printf("로그인 상태가 아닙니다.\n");
    }
}
void exitProgram() {
    system("clear");    //터미널 화면 clear 후 프로그램 종료
    printf("다음에 또 만나요 !!\n");
}