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
void Intro() {
    printf("부산헹 게임 시작합니다.\n");
    printf("시민의 게임 승리 조건은, 현재 열차 칸에서 탈출하는 것 입니다.\n");
    printf("패배 조건은 좀비에게 잡히는 것입니다.\n");
}

// 아웃트로 
void Outro(int success) {
    if (success) {
        printf("탈출 성공\n");
        printf("시민이 다음 열차로 넘어갔습니다.\n");
    }
    else {
        printf("게임 끝\n");
        printf("시민이 좀비에게 공격당했습니다.\n");
    }
}

// 열차 입력
void Train() {
    length = get_valid_input("열차의 길이를 입력하세요", Len_MIN, Len_MAX);
    m_stamina = get_valid_input("마동석의 체력을 입력하세요", STM_MIN, STM_MAX);
    p = get_valid_input("이동 확률을 입력하세요", PROB_MIN, PROB_MAX);

    c = length - 7;
    z = length - 4;
    m = length - 3;
}

// 열차를 형성
void form_train() {
    for (int j = 0; j < 2; j++) {
        if (j == 1) {
            printf("#");
            for (int a = 0; a < length - 2; a++) {
                if (j == 1 && a == c) {
                    printf("C");
                }
                else if (j == 1 && a == z) {
                    printf("Z");
                }
                else if (j == 1 && a == m) {
                    printf("M");
                }
                else {
                    printf(" ");
                }
            }printf("#\n");
        }for (int i = 0; i < length; i++) {
            printf("#");
        }printf("\n");
    }
}
//시민 좀비 이동
void z_c_m(int sum1, int sum2, int turn) {
    if (sum1) {
        printf("시민: 이동 %d -> %d\n", c + 1, c);
    }
    else {
        printf("시민: 정지 %d -> %d\n", c, c);
    }
    if (turn % 2 == 1) {
        if (sum2) {
            printf("좀비: 이동 %d -> %d\n", z + 1, z);
        }
        else {
            printf("좀비: 정지 %d -> %d\n", z, z);
        }
    }
    else {
        printf("좀비: %d (이동 불가 턴)\n", z);
    }
}

// 게임 진행
void play_game() {
    int turn = 0;
    while (1) {
        ++turn;
        int sum1 = 0;
        int sum2 = 0;

        // 시민 이동
        int b = rand() % 100;
        if (b <= 100 - p) {
            --c;
            ++sum1;
        }

        // 좀비 이동 (2턴 주기)
        if (turn % 2 == 1) {
            int d = rand() % 100;
            if (d <= p) {
                --z;
                ++sum2;
            }
        }

        // 기차 형성 및 상태 출력
        form_train();
        z_c_m(sum1, sum2, turn);

        // 게임 종료 조건 확인
        if (c == 1 || z == c + 1) {
            break;
        }
    }

    if (c == 1) {
        Outro(1);
    }
    else {
        Outro(0);
    }
}

int main(void) {
    srand((unsigned int)time(NULL)); // 난수 초기화
    Intro();
    Train();
    play_game();
    return 0;
}
