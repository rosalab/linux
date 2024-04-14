#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/syscall.h>

#define __NR_hello 451
#define DELAY_S 1 

int main(int argc, char** arg){
	if (argc==1){
		printf("Starting throughput performance test for the hello syscall...\n");
		printf("-------------------------------------------------------------\n");
		int cnt=0, num_calls=0;

		while(cnt<40){
			clock_t start_clocks = clock();
			while (clock() - start_clocks < DELAY_S * CLOCKS_PER_SEC) {
				syscall(__NR_hello);	
				num_calls++;
			}
			printf("%d:%d\n", cnt, num_calls);
			cnt++;
			num_calls=0;

		}
	}
	else if (argc==2){
		printf("Triggering sys_hello once..");
		syscall(__NR_hello);	

	}

	return 0;
	
}
