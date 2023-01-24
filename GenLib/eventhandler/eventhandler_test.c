#include <stdio.h>

#include "client_control_handler.h"

void testfunc(){
    CCH_data_t* p = CCH_create("127.0.0.1", 8080);
	if (p == 0){
		return;
	};
	
	//waiting for server to send message
	char ibuff[50];
    int numRead = CCH_read(p, ibuff, 49);
	printf("numRead: %d\n",numRead);
	if (numRead <= 0){
		perror("badsocket");
		CCH_close(p);
		return;
	};
	ibuff[numRead] = 0;
	printf("%s\n", ibuff);
	
	//waiting for user to enter message
	printf("Please enter string for server: \n");
	char obuff[50];
	int n = 0;
    while ((obuff[n++] = getchar()) !='\n')
        ;
	int flag;
	flag = CCH_write(p, obuff, n);
	if (flag != n){
		perror("bad write");
		CCH_close(p);
		return;
	};
	printf("flag: %d\n",flag);

    CCH_close(p);
};

int main(int ac, char* av[]){
    testfunc();
    return 0;
}

