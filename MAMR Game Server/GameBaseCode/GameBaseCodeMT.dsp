# Microsoft Developer Studio Project File - Name="GameBaseCodeMT" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=GameBaseCodeMT - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GameBaseCodeMT.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GameBaseCodeMT.mak" CFG="GameBaseCodeMT - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GameBaseCodeMT - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "GameBaseCodeMT - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/GameBaseCode/GameBaseCodeMT", BFAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GameBaseCodeMT - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\common" /I "..\DDServer\share" /I "." /D "MULTITHREAD_SAFE" /D "NO_MUTEX" /D "USE_NEW" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "GameBaseCodeMT - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\common" /I "..\DDServer\share" /I "." /D "MULTITHREAD_SAFE" /D "NO_MUTEX" /D "USE_NEW" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fr /YX /FD /GZ /c
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

# Name "GameBaseCodeMT - Win32 Release"
# Name "GameBaseCodeMT - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\source\MyConstRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\source\myConstrecord.h
# End Source File
# Begin Source File

SOURCE=.\source\mydatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\source\mydatabase.h
# End Source File
# Begin Source File

SOURCE=.\source\MyField.cpp
# End Source File
# Begin Source File

SOURCE=.\source\MyField.h
# End Source File
# Begin Source File

SOURCE=.\source\MyRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\source\myrecord.h
# End Source File
# Begin Source File

SOURCE=.\source\myrecordset.cpp
# End Source File
# Begin Source File

SOURCE=.\source\myrecordset.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ConstGameData.h
# End Source File
# Begin Source File

SOURCE=.\GameData.h
# End Source File
# Begin Source File

SOURCE=.\I_mydb.h
# End Source File
# Begin Source File

SOURCE=.\T_GameDataMap.h
# End Source File
# Begin Source File

SOURCE=.\T_GameDataSet.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Common\common.h
# End Source File
# Begin Source File

SOURCE=.\source\Mydb.h
# End Source File
# End Target
# End Project
