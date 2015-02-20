########## DEFINITIONS ##########
TARGET		= remapt.dll
SOURCES		= remap.cpp

# Windows SDK
WINDOWSSDK	= C:\Program Files\Microsoft SDKs\Windows\v6.0
INCLUDES	= /I "$(WINDOWSSDK)\VC\Include" /I "$(WINDOWSSDK)\Include" $(INCLUDES)
LIBRARIES	= /LIBPATH:"$(WINDOWSSDK)\VC\Lib" /LIBPATH:"$(WINDOWSSDK)\Lib" user32.lib $(LIBRARIES)

ORBITER		= $(MAKEDIR)\Orbiter 2010
ORBITERADDON= $(ORBITER)\Modules\Plugin

# Orbiter SDK
ORBITERSDK	= $(ORBITER)\Orbitersdk
INCLUDES	= /I "$(ORBITERSDK)\include" $(INCLUDES)
LIBRARIES	= /LIBPATH:"$(ORBITERSDK)\lib" orbiter.lib Orbitersdk.lib $(LIBRARIES)

DEFINES		= /D WIN32 /D NDEBUG /D _WINDOWS

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
