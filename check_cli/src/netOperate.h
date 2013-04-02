#ifndef __NET_OPERATE_H_
#define __NET_OPERATE_H_

#include "autotype.h"

void sendProtGetTime();
void msgOnGetTime(int sockId, int protId);
void sendProtToSignIn(const AutoType& name, const AutoType& dep, const AutoType& photo);
void msgOnSignIn(int sockId, int protId);
void regAllHandler();

#endif

