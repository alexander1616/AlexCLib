#ifndef eventdispatcher_h
#define eventdispatcher_h 1
#include "../container/container.h"
#define EVENTDISPATCHER_MODE_POLL 0
#define EVENTDISPATCHER_MODE_SELECT 1

//FDElement_t is private Element for container
typedef struct FDElement_t{
    int fd;
    int terminating;
    int readcount;
	int byteread;
	int allowbroadcast;
    int (*onReadEvent)(struct FDElement_t*, Container_t*);
} FDElement_t;

typedef struct Eventdispatcher_t{
	Container_t* 	containerP;
	int 			(*onTimeoutEvent)(struct Eventdispatcher_t*);
	int 	 		debugFlag; 	//debug flag
	int 	 		mode;			//using Poll or Select, mode 0 default
} Eventdispatcher_t;

#ifdef __cplusplus //if c++ we need to extern
extern "C" {
#endif
    Eventdispatcher_t* 	eventdispatcher_create();
    void 				eventdispatcher_free(Eventdispatcher_t*);
	int 				eventdispatcher_loop(Eventdispatcher_t*, int usec);
	
	//Helper functions for find FDElement_t
	int 			FDElement_findFD(FDElement_t* p, int value);
	FDElement_t* 	FDElement_alloc(Container_t *p, int fd, 
									int(*func)(FDElement_t *, Container_t*));
	void 			FDElement_print(FDElement_t* p);
	void 			FDElement_kill(FDElement_t* p);

#ifdef __cplusplus //removes the closing bracket for c compiler
};

#endif
#endif // eventdispatcher_h
