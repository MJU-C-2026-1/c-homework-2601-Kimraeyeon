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
  int bonus; 

 // 변수 추가
 char continue_flag; //다음 사람 계산 여부를 묻는 변수 

  while(1) //전체 프로그램 무한 반복 시작 
  {
    bonus=0;
    printf("\n===새로운 알바생 급여 계산을 시작합니다.===\n");
  //2. 정보 입력받기 
    // 입력값 오류 방어
    while(1)
    {
      printf("근무 조를 입력하세요(주간D / 야간 N) : ");
      scanf(" %c", &group);
      if(group == 'D' || group == 'd' || group == 'C' || group == 'c')
      {
        break;
      }
      printf("[오류] 잘못된 입력입니다. D 또는 N을 입력해주세요 .\n");
    }  
    
    while(1)
    {
      printf("시급을 입력하세요(원) : ");
      scanf("%d",&pay_hr);
      if(pay_hr>0)
      {
        break;
      }
      printf("[오류] 시급은 0원보다 커야 합니다. 다시 입력해주세요. \n");
    }
    
    while(1)
    {
      printf("이번달 일한 시간을 입력하세요(시간) : ");
      scanf("%d", &work_hours);
      if(work_hours>=0 && work_hours <= 744) //한달 (31일*24시간=744시간) 최대치 
      {
        break;
      }
      printf("[오류] 비정상적인 근무시간입니다. (0에서 744사이 시간 입력)");
    }
 
    while(1)
    {
      printf("적용할 세율을 입력(예:3.3%%면 0.033) : ");
      scanf("%f", &tax_rate);
      if(tax_rate >= 0.0 && tax_rate<1.0)
      {
        break;
      }
      printf("[오류] 세율은 0 이상 1 미만의 값이어야 합니다.\n");
    }
  
  //3. 알바비 계산 (산술연산 사용)
  base_pay = pay_hr*work_hours ;  //기본급 계산

  //야간조 수당 추가 
  if(group == 'N' || group == 'n')
  {
    bonus = base_pay / 2;
  }

  //초과 근무 수당 추가
  if(work_hours>160)
  {
    int over_hours = work_hours-160; //초과한 시간만 계산
    bonus= bonus + (over_hours*pay_hr/2);
  }

  // 세전/ 세후 계산 
  pre_tax = base_pay + bonus;
  final_pay = pre_tax - (pre_tax*tax_rate);
  

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

  } //전체 프로그램 반복문 끝 
  return 0; 
}
