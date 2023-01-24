#ifndef client_control_handler_h
#define client_control_handler_h 1

typedef struct {
	int fd; //current file descriptor	
} CCH_data_t;

CCH_data_t*	CCH_create(char* host, int port); //create socket
int			CCH_write(CCH_data_t*, void* source, int size); //write method
int			CCH_read(CCH_data_t*, void* destination, int size); //read method
void		CCH_close(CCH_data_t*); //close
CCH_data_t*	CCH_accept(int port);

#endif
