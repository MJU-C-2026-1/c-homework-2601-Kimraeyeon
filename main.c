/* 
  파일이름: 알바비 정산 프로그램 
  작 성 자: 김래연 , 26-04-04
  하 는 일: 아르바이트생의 근무 정보를 입력받아 세금 공제 전후의 알바비를 정확하게 계산하고 명세서를 발급

*/

#include <stdio.h>

int main()
{
  //1. 변수 선언
  char group;
  int pay_hr;
  int work_hours;
  float tax_rate;
  int pre_tax;
  double final_pay;

  //변수 2개 추가
  int base_pay;   
  int bonus = 0;  //추가 수당 처음엔 0원으로 시작 

  //2. 정보 입력받기
  printf("근무 조를 입력하세요(주간D / 야간 N) : ");
  scanf(" %c", &group);

  printf("시급을 입력하세요(원) : ");
  scanf("%d",&pay_hr);

  printf("이번달 일한 시간을 입력하세요(시간) : ");
  scanf("%d", &work_hours);

  printf("적용할 세율을 입력(예:3.3%%면 0.033) : ");
  scanf("%f", &tax_rate);
  
  //3. 알바비 계산 (산술연산 사용)
  base_pay = pay_hr*work_hours ;  //기본급 계산

  //야간조 수당 추가 
  if(group == 'N' || group == 'n')
  {
    bonus = bonus + (base_pay / 2);
  }

  //초과 근무 수당 추가
  if(hours>160)
  {
    int over_hours = work_hours-160; //초과한 시간만 계산
    bonus=bonus + (over_hours*pay_hr/2);
  }

  // 세전/ 세후 계산 
  pre_tax = base_pay + bonus;
  finaly_pay = pre_tax - (pre_tax*tax_rate);
  

  //4. 영수증 형태의 결과 출력 
  printf("\n=================================\n");
  printf("[알바비 급여 명세서]\n");
  printf("==================================\n");
  printf("근무 조 : %c조\n", group);
  printf("시급 : %d원\n", pay_hr);
  printf("근무 시간 : %d시간\n",work_hours);
  printf("적용 세율 : %.1f%%\n", tax_rate*100);
  printf("----------------------------------\n");
  printf("기본급 : %d\n", base_pay);
  printf("추가수당 (야간/초과) : %d원\n", bonus);
  printf("세전 총 급여 : %d원\n", pre_tax);
  printf("세후 실 수령액 : %.1f원\n", final_pay);
  printf("==================================\n");

  return 0; 
}
