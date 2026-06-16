/* 
  파일이름: 알바비 정산 프로그램 
  작 성 자: 김래연 , 26-06-16
  하 는 일: 아르바이트생의 근무 정보를 입력받아 세금 공제 전후의 알바비를 정확하게 계산하고 명세서를 발급

*/

#include <stdio.h>

#define MAX_EMP 5 // 배열의 최대 크기는 5 

int global_total_employees = 0; // 현재까지 입력된 알바생 수
float global_tax_rate = 0.033f; // 공통 적용 세율

int calculate_bonus(char group, int wage, int hours); 
void input_data(char groups[], int pay_hrs[], int work_hours_arr[], int pre_taxes[], double final_pays[]);
void view_data(char groups[], int pay_hrs[], int work_hours_arr[], int pre_taxes[], double final_pays[]);
double analyze_data(double *final_pays_ptr); 

int main() 
{
    char groups[MAX_EMP];
    int pay_hrs[MAX_EMP];
    int work_hours_arr[MAX_EMP];
    int pre_taxes[MAX_EMP];
    double final_pays[MAX_EMP];

    int menu_choice;

    while(1) {
        printf("\n======= [알바비 종합 관리 시스템] =======\n");
        printf("1. 알바생 정보 입력\n");
        printf("2. 전체 급여 조회 (배열 인덱스 방식)\n");
        printf("3. 총 지출액 분석 (포인터 연산 방식)\n");
        printf("4. 프로그램 종료\n");
        printf("=========================================\n");
        printf("메뉴를 선택하세요: ");
        scanf("%d", &menu_choice);

        if (menu_choice == 1) 
		{
            input_data(groups, pay_hrs, work_hours_arr, pre_taxes, final_pays);
        } 
        else if (menu_choice == 2) 
		{
            view_data(groups, pay_hrs, work_hours_arr, pre_taxes, final_pays);
        } 
        else if (menu_choice == 3) 
		{
            double total_expense = analyze_data(final_pays); 
            if (global_total_employees > 0) 
			{
                printf("\n[분석 결과] 이번 달 매장 총 지출 예정 급여(세후): %.0f원\n", total_expense);
            }
        } 
        else if (menu_choice == 4) 
		{
            printf("프로그램을 안전하게 종료합니다.\n");
            break; 
        } 
        else 
		{
            printf("[오류] 1~4 사이의 번호를 입력해주세요.\n");
        }
    }

    return 0; 
}


// 개별 함수 정의부

// 수당 계산 함수 
int calculate_bonus(char group, int wage, int hours) 
{
    int bonus = 0;
    if (group == 'N' || group == 'n') 
	{
        bonus += (wage * hours / 2);
    }
    if (hours > 160) 
	{
        bonus += ((hours - 160) * wage / 2);
    }
    return bonus;
}

// [기능 1] 데이터 입력 함수
void input_data(char groups[], int pay_hrs[], int work_hours_arr[], int pre_taxes[], double final_pays[]) 
{
    if (global_total_employees >= MAX_EMP) 
	{
        printf("[안내] 최대 입력 인원(%d명)을 초과하여 더 이상 입력할 수 없습니다!\n", MAX_EMP);
        return;
    }
    
    int i = global_total_employees; 
    
    printf("\n[%d번째 알바생 정보 입력]\n", i + 1);
    printf("근무 조를 입력하세요(주간D / 야간 N) : ");
    scanf(" %c", &groups[i]);

    printf("시급을 입력하세요(원) : ");
    scanf("%d", &pay_hrs[i]);

    printf("이번달 일한 시간을 입력하세요(시간) : ");
    scanf("%d", &work_hours_arr[i]);

    // 연산
    int base_pay = pay_hrs[i] * work_hours_arr[i];
    int bonus = calculate_bonus(groups[i], pay_hrs[i], work_hours_arr[i]);
    
    pre_taxes[i] = base_pay + bonus;
    final_pays[i] = pre_taxes[i] - (pre_taxes[i] * global_tax_rate);

    global_total_employees++; 
    printf(">> 입력 성공! (현재 등록 인원: %d/%d명)\n", global_total_employees, MAX_EMP);
}

// [기능 2] 데이터 조회 함수
void view_data(char groups[], int pay_hrs[], int work_hours_arr[], int pre_taxes[], double final_pays[]) 
{
    if (global_total_employees == 0) 
	{
        printf("\n[안내] 등록된 알바생 데이터가 없습니다.\n");
        return;
    }
    
    printf("\n============= [전체 알바생 급여 조회] =============\n");
	
	int i;
    for (i = 0; i < global_total_employees; i++) 
	{
        printf("ID: %d | 조: %c | 시급: %d원 | 시간: %dH | 세전: %d원 | 세후: %.0f원\n",
               i + 1, groups[i], pay_hrs[i], work_hours_arr[i], pre_taxes[i], final_pays[i]);
    }
    printf("===================================================\n");
}

// [기능 3] 데이터 분석 함수 (포인터 연산)
double analyze_data(double *final_pays_ptr) 
{
    if (global_total_employees == 0) 
	{
        printf("\n[안내] 분석할 데이터가 없습니다.\n");
        return 0.0;
    }
    
    double total_sum = 0;
 
 	int i;
    for (i = 0; i < global_total_employees; i++) 
	{
        total_sum += *(final_pays_ptr + i); 
    }
    
    return total_sum; 
}
}
