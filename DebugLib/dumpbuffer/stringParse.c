#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char s1[256], s2[256], s3[256], s4[256], s5[256], s6[256], s7[256], s8[256], s9[256], s10[256];
char *s_store[10] = {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10};
char newbuf[280];

char* combine(int n){
	newbuf[0] = 0;	
	for (int i = 1; i < n; i++){
		strcat(newbuf, " ");
		strcat(newbuf, s_store[i]);
	};
	return;
};

void do_CMD(int n){
	combine(n);
	printf("String is: %s \n", newbuf);
	int x = 0;
	x = system(newbuf);
	if (x < 0){
		printf("Bad command. \n");
	};
	return;
};

void clear_Buffs(int n){
	for (int i = 0; i <= n; i++){
		memset(s_store[i], 0, 256);
	};
	return;
};

void do_ECHO(int n){
	combine(n);
	printf("%s\n", newbuf);
	return;
};

void do_Unknown(int x){
};

int main(){
	char buff[256];
	int jj;
	int n;
	while (1){
		printf("Enter a command.\n");
		jj = read(0, buff, 255);
		if (jj <= 0 ){
			printf("bye.\n");
			return 1;
		};
		printf("Bytes read:[%d]\n", jj);
		buff[jj]=0;
		n = sscanf(buff, "%s%s%s%s%s%s%s%s%s%s", s1, s2, s3, s4, s5, s6, s7, s8, s9, s10);
		if (n < 1){
			continue;
		};
		if (strcmp(s1,"CMD")==0){
			printf("N = %d\n", n);
			do_CMD(n);
		} else if (strcmp(s1,"ECHO")==0){
			printf("N = %d\n", n);
			do_ECHO(n);
		} else if (strcmp(s1,"QUIT")==0){
			printf("N = %d\n", n);
			printf("mad dad.\n");
			return 0;
		} else {
			printf("N = %d\n", n);
			printf("Unknown command.\n");
			do_Unknown(n);
		};
		//memset(buff, 0, 256);
		//n = 0;
	};
	return 0;
}
