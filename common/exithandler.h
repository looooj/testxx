#ifndef exit_handler_hxx
#define exit_handler_hxx

#include <signal.h>


extern int ExitFlag;
extern int ExitSignal;

void SetExitHandler();
void SetExitHandler(sighandler_t func);

void WaitExitLoop();


#endif
