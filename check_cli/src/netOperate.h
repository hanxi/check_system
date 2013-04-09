#ifndef __NET_OPERATE_H_
#define __NET_OPERATE_H_

#include "autotype.h"

void sendProtGetTime();
void msgOnGetTime(int sockId, int protId);
void sendProtToSignIn(const AutoType& name, const AutoType& dep, const AutoType& photo, int idx);
void msgOnSignIn(int sockId, int protId);
void sendProtGetPhotoInfo(const AutoType& photo);
void sendProtCheckIn(const AutoType& photo);

void sendProtToUpdateModel();

void regAllHandler();
#endif

