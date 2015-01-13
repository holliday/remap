########## DEFINITIONS ##########
TARGET		= remap.dll
SOURCES		= remap.cpp

PLATFORMSDK	= C:\Program Files\Microsoft Platform SDK
ORBITER		= C:\Orbiter 2010
ORBITERSDK	= $(ORBITER)\Orbitersdk
ORBITERADDON= $(ORBITER)\Modules\Plugin

INCLUDES	= /I "$(ORBITERSDK)\include" /I "$(PLATFORMSDK)\Include"
LIBRARIES	= /LIBPATH:"$(ORBITERSDK)\lib" orbiter.lib Orbitersdk.lib /LIBPATH:"$(PLATFORMSDK)\Lib" user32.lib
DEFINES		= /D WIN32 /D NDEBUG /D _WINDOWS /D _WIN32_WINNT=0x0501

CXX			= cl
CXXFLAGS	= /O2 /EHsc /MD /GS- /fp:fast /W3 /GL /LD

LINKFLAGS	= /MACHINE:X86 /SUBSYSTEM:WINDOWS /INCREMENTAL:NO /LTCG

all: $(TARGET)
	@echo Compiled $(TARGET)

$(TARGET): $(SOURCES)
	@echo Compiling $(SOURCES)
	$(CXX) $(INCLUDES) $(DEFINES) $(CXXFLAGS) $(SOURCES) /link /OUT:$(TARGET) $(LINKFLAGS) $(LIBRARIES)

clean:
	@echo Cleaning files
	-del *.obj *.lib *.exp *.manifest $(TARGET)

install: $(TARGET)
	@echo Installing $(TARGET)
	copy /y $(TARGET) "$(ORBITERADDON)\$(TARGET)"
