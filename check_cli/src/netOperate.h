#ifndef __NET_OPERATE_H_
#define __NET_OPERATE_H_

void sendProtGetTime();
void msgOnGetTime(int sockId, int protId);
void sendProtToSignIn(const char *name, const char *dep, const char *photo);
void msgOnSignIn(int sockId, int protId);
void regAllHandler();

#endif

