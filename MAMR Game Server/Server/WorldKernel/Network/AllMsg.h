#ifndef _ALLMSG_H
#define _ALLMSG_H

#define	_WINSOCKAPI_		// ◊Ë÷πº”‘ÿwinsock.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <windows.h>

#include "NetMsgW.h"

using namespace world_kernel;		// all msg use namespace world_kernel!!!
#include "MsgTalkW.h"
#include "MsgMessageBoard.h"
#include "MsgRegister.h"
#include "MsgLogin.h" //Login handled by account server, this packet is more for NPC server
#include "MsgLogin_C.h" //replicated for return 1002 message
//#include "MsgAiNpcInfo.h"
#include "MsgConnect.h"
#include "MsgTime.h" //Only contains 'Hour'
#include "MsgNameW.h"
#include "MsgFriendW.h"
#include "MsgDialogW.h"
#include "MsgChatRoom.h"
#include "MsgRole.h"


#endif