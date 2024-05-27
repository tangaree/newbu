#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

//파라미터
#define STM_MAX 5 //마동석 체력
#define STM_MIN 0
#define Len_MIN 15 // 기차 길이 
#define Len_MAX 50  
#define PROB_MIN 10 // 확률 
#define PROB_MAX 90 
#define AGGRO_MIN 0 //어그로 범위
#define AGGRO_MAX 5

//마동석 이동방향
#define MOVE_LEFT 1
#define MOVE_STAY 0

//좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

//마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

int length, p; // 열차 길이와 확률을 전역 변수로 선언
int c, z, m; // 시민, 좀비, 마동석 위치
int m_stamina;
int c_aggro = 1;
int m_aggro = 1;


int get_valid_input(const char*, int, int);
// 유효하지 않을 경우 재입력
int get_valid_input(const char* prompt, int min, int max) {
    int value;
    while (1) {
        printf("%s (%d~%d)>>\n", prompt, min, max);
        int result = scanf_s("%d", &value);
        while (getchar() != '\n'); // 버퍼 비우기
        if (result == 1 && value >= min && value <= max) {
            return value;
        }
    }
}


// 인트로
void print_intro() {
    printf("부산헹 게임 시작합니다.\n");
    printf("시민의 게임 승리 조건은, 현재 열차 칸에서 탈출하는 것 입니다.\n");
    printf("패배 조건은 좀비에게 잡히는 것입니다.\n");
}
