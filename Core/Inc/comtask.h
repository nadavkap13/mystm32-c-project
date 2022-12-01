#ifndef INC_COMTASK_H_
#define INC_COMTASK_H_

typedef void (*HandlerFunc)(void*,char*);
typedef struct _function{
	char* CommandName;
	HandlerFunc Func;
	void* obj;
}Function;

int commTask();
void handleCommand();
void RegisterCallbacks(HandlerFunc onFunc, HandlerFunc offFunc,void* object);
void RegisterCommand(char* CommandName, HandlerFunc Func,void* obj);

#endif /* INC_COMTASK_H_ */
