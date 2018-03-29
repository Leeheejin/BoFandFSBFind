bof.c has 3 BoF points.
	some points are vulnerable,
	and some points are not vulnerable, buf there IS a BoF

fsb.c has 2 FSB points

만일 본인의 리눅스 환경에서 가산점 문제를 해결하길 원하시는 분들께서는 아래의 커맨드를 적용하신 이후 실습해주시기 바랍니다.

1. ASLR 해제
	$ sudo -s                                                              <-관리자 권한으로 진입, 커맨드 이후 앞에 "$"가 "#"으로 변하는 것 확인
	# echo "0" > /proc/sys/kernel/randomize_va_space                                      <- ASLR 이라는 운영체제 차원에서의 보호기법 해제

2. core dump 획득(해당 커맨드는 쉘을 닫았다가 다시 연 경우, 다시 입력해주어야 함)
	$ ulimit -c unlimited
	coredump 확인방법 : gdb -q -c core 실행파일명

추가적인 문의사항은 조교에게 연락주시기 바랍니다
	Email : tlawodn94@gmail.com
	위치 : 단국대학교 미디어센터 504호