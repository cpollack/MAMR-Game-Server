# Microsoft Developer Studio Project File - Name="NpcKernel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=NpcKernel - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NpcKernel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NpcKernel.mak" CFG="NpcKernel - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NpcKernel - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "NpcKernel - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/NpcServer/NpcKernel", FLAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NpcKernel - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "NetWork" /I "..\..\common" /I "..\..\GameBaseCode" /I "..\..\AiModule" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_DDNPC_" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "NpcKernel - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "NetWork" /I "..\..\common" /I "..\..\GameBaseCode" /I "..\..\AiModule" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_DDNPC_" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "NpcKernel - Win32 Release"
# Name "NpcKernel - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Agent.cpp
# End Source File
# Begin Source File

SOURCE=.\AgentData.cpp
# End Source File
# Begin Source File

SOURCE=.\Body.cpp
# End Source File
# Begin Source File

SOURCE=.\DynaNpcGen.cpp
# End Source File
# Begin Source File

SOURCE=.\GameBlock.cpp
# End Source File
# Begin Source File

SOURCE=.\GameMap.cpp
# End Source File
# Begin Source File

SOURCE=.\GameObj.cpp
# End Source File
# Begin Source File

SOURCE=.\Item.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemPack.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemType.cpp
# End Source File
# Begin Source File

SOURCE=.\MapManager.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgItem.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgItemInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgMagicEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgSyndicate.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgTeam.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgTeamMember.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgUserInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Npc.cpp
# End Source File
# Begin Source File

SOURCE=.\NpcGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\NpcManager.cpp
# End Source File
# Begin Source File

SOURCE=.\NpcType.cpp
# End Source File
# Begin Source File

SOURCE=.\NpcWorld.cpp
# End Source File
# Begin Source File

SOURCE=.\RoleFight.cpp
# End Source File
# Begin Source File

SOURCE=.\RoleMove.cpp
# End Source File
# Begin Source File

SOURCE=.\Sense.cpp
# End Source File
# Begin Source File

SOURCE=.\SynManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Team.cpp
# End Source File
# Begin Source File

SOURCE=.\User.cpp
# End Source File
# Begin Source File

SOURCE=.\UserManager.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Agent.h
# End Source File
# Begin Source File

SOURCE=.\AgentData.h
# End Source File
# Begin Source File

SOURCE=.\Body.h
# End Source File
# Begin Source File

SOURCE=.\chn_rc.h
# End Source File
# Begin Source File

SOURCE=.\DynaNpcGen.h
# End Source File
# Begin Source File

SOURCE=.\eng_rc.h
# End Source File
# Begin Source File

SOURCE=.\GameBlock.h
# End Source File
# Begin Source File

SOURCE=.\GameMap.h
# End Source File
# Begin Source File

SOURCE=.\GameObj.h
# End Source File
# Begin Source File

SOURCE=.\I_Role.h
# End Source File
# Begin Source File

SOURCE=.\Item.h
# End Source File
# Begin Source File

SOURCE=.\ItemPack.h
# End Source File
# Begin Source File

SOURCE=.\ItemType.h
# End Source File
# Begin Source File

SOURCE=.\MapManager.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgItem.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgItemInfo.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgMagicEffect.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgSyndicate.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgTeam.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgTeamMember.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgUserInfo.h
# End Source File
# Begin Source File

SOURCE=.\Npc.h
# End Source File
# Begin Source File

SOURCE=.\NpcGenerator.h
# End Source File
# Begin Source File

SOURCE=.\NpcManager.h
# End Source File
# Begin Source File

SOURCE=.\NpcType.h
# End Source File
# Begin Source File

SOURCE=.\NpcWorld.h
# End Source File
# Begin Source File

SOURCE=.\RoleFight.h
# End Source File
# Begin Source File

SOURCE=.\RoleMove.h
# End Source File
# Begin Source File

SOURCE=.\Sense.h
# End Source File
# Begin Source File

SOURCE=.\SynManager.h
# End Source File
# Begin Source File

SOURCE=.\T_SingleMap2.h
# End Source File
# Begin Source File

SOURCE=.\Team.h
# End Source File
# Begin Source File

SOURCE=.\User.h
# End Source File
# Begin Source File

SOURCE=.\UserManager.h
# End Source File
# End Group
# Begin Group "NetWork"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NetWork\MsgAction.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgAction.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgAiNpcInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgAiNpcInfo.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgInteract.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgInteract.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgLogin.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgLogin.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgNpc.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgNpc.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgPlayer.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgTalk.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgTalk.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgUserAttrib.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgUserAttrib.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgWalk.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgWalk.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgWalkEx.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\MsgWalkEx.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\NetMsg.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\NetWork\AllMsg.h
# End Source File
# Begin Source File

SOURCE=.\define.h
# End Source File
# Begin Source File

SOURCE=.\I_MapData.h
# End Source File
# Begin Source File

SOURCE=.\I_Shell.h
# End Source File
# Begin Source File

SOURCE=.\NetWork\NetMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\NetWork\NetworkDef.h
# End Source File
# Begin Source File

SOURCE=.\protocol.h
# End Source File
# End Target
# End Project
