# Microsoft Developer Studio Generated NMAKE File, Based on oTDK.dsp
!IF "$(CFG)" == ""
CFG=oTDK - Win32 Debug
!MESSAGE No configuration specified. Defaulting to oTDK - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "oTDK - Win32 Release" && "$(CFG)" != "oTDK - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "oTDK.mak" CFG="oTDK - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "oTDK - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "oTDK - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "oTDK - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\oTDK.exe"


CLEAN :
	-@erase "$(INTDIR)\CntrItem.obj"
	-@erase "$(INTDIR)\LeftView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\oTDK.obj"
	-@erase "$(INTDIR)\oTDK.pch"
	-@erase "$(INTDIR)\oTDK.res"
	-@erase "$(INTDIR)\oTDKDoc.obj"
	-@erase "$(INTDIR)\oTDKView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\oTDK.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\oTDK.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\oTDK.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\oTDK.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\oTDK.pdb" /machine:I386 /out:"$(OUTDIR)\oTDK.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CntrItem.obj" \
	"$(INTDIR)\LeftView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\oTDK.obj" \
	"$(INTDIR)\oTDKDoc.obj" \
	"$(INTDIR)\oTDKView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\oTDK.res"

"$(OUTDIR)\oTDK.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "oTDK - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\oTDK.exe" "$(OUTDIR)\oTDK.bsc"


CLEAN :
	-@erase "$(INTDIR)\CntrItem.obj"
	-@erase "$(INTDIR)\CntrItem.sbr"
	-@erase "$(INTDIR)\LeftView.obj"
	-@erase "$(INTDIR)\LeftView.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\oTDK.obj"
	-@erase "$(INTDIR)\oTDK.pch"
	-@erase "$(INTDIR)\oTDK.res"
	-@erase "$(INTDIR)\oTDK.sbr"
	-@erase "$(INTDIR)\oTDKDoc.obj"
	-@erase "$(INTDIR)\oTDKDoc.sbr"
	-@erase "$(INTDIR)\oTDKView.obj"
	-@erase "$(INTDIR)\oTDKView.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\oTDK.bsc"
	-@erase "$(OUTDIR)\oTDK.exe"
	-@erase "$(OUTDIR)\oTDK.ilk"
	-@erase "$(OUTDIR)\oTDK.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\oTDK.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\oTDK.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\oTDK.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CntrItem.sbr" \
	"$(INTDIR)\LeftView.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\oTDK.sbr" \
	"$(INTDIR)\oTDKDoc.sbr" \
	"$(INTDIR)\oTDKView.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\oTDK.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\oTDK.pdb" /debug /machine:I386 /out:"$(OUTDIR)\oTDK.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\CntrItem.obj" \
	"$(INTDIR)\LeftView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\oTDK.obj" \
	"$(INTDIR)\oTDKDoc.obj" \
	"$(INTDIR)\oTDKView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\oTDK.res"

"$(OUTDIR)\oTDK.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("oTDK.dep")
!INCLUDE "oTDK.dep"
!ELSE 
!MESSAGE Warning: cannot find "oTDK.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "oTDK - Win32 Release" || "$(CFG)" == "oTDK - Win32 Debug"
SOURCE=.\CntrItem.cpp

!IF  "$(CFG)" == "oTDK - Win32 Release"


"$(INTDIR)\CntrItem.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oTDK.pch"


!ELSEIF  "$(CFG)" == "oTDK - Win32 Debug"


"$(INTDIR)\CntrItem.obj"	"$(INTDIR)\CntrItem.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oTDK.pch"


!ENDIF 

SOURCE=.\LeftView.cpp

!IF  "$(CFG)" == "oTDK - Win32 Release"


"$(INTDIR)\LeftView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oTDK.pch"


!ELSEIF  "$(CFG)" == "oTDK - Win32 Debug"


"$(INTDIR)\LeftView.obj"	"$(INTDIR)\LeftView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oTDK.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "oTDK - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oTDK.pch"


!ELSEIF  "$(CFG)" == "oTDK - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oTDK.pch"


!ENDIF 

SOURCE=.\oTDK.cpp

!IF  "$(CFG)" == "oTDK - Win32 Release"


"$(INTDIR)\oTDK.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oTDK.pch"


!ELSEIF  "$(CFG)" == "oTDK - Win32 Debug"


"$(INTDIR)\oTDK.obj"	"$(INTDIR)\oTDK.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oTDK.pch"


!ENDIF 

SOURCE=.\oTDK.rc

"$(INTDIR)\oTDK.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\oTDKDoc.cpp

!IF  "$(CFG)" == "oTDK - Win32 Release"


"$(INTDIR)\oTDKDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oTDK.pch"


!ELSEIF  "$(CFG)" == "oTDK - Win32 Debug"


"$(INTDIR)\oTDKDoc.obj"	"$(INTDIR)\oTDKDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oTDK.pch"


!ENDIF 

SOURCE=.\oTDKView.cpp

!IF  "$(CFG)" == "oTDK - Win32 Release"


"$(INTDIR)\oTDKView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oTDK.pch"


!ELSEIF  "$(CFG)" == "oTDK - Win32 Debug"


"$(INTDIR)\oTDKView.obj"	"$(INTDIR)\oTDKView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\oTDK.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "oTDK - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\oTDK.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\oTDK.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "oTDK - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\oTDK.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\oTDK.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

