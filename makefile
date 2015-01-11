########## DEFINITIONS ##########
TARGET		= remap.dll

SOURCES		= remap.cpp
INCLUDES	= /I ../Orbitersdk/include/
LIBRARIES	= /LIBPATH:../Orbitersdk/lib/ orbiter.lib Orbitersdk.lib user32.lib
DEFINES		= /D WIN32 /D NDEBUG /D WINDLL

CXX			= cl
CXXFLAGS	= /O2 /EHsc /MD /GS- /fp:fast /W3 /GL /LD

LINKFLAGS	= /MACHINE:X86 /SUBSYSTEM:WINDOWS /INCREMENTAL:NO /LTCG

RM			= del

all: $(TARGET)
	@echo Compiled $(TARGET)

$(TARGET): $(SOURCES)
	@echo Compiling $(SOURCES)
	$(CXX) $(INCLUDES) $(DEFINES) $(CXXFLAGS) $(SOURCES) /link /OUT:$(TARGET) $(LINKFLAGS) $(LIBRARIES)

clean:
	@echo Cleaning files
	-$(RM) *.obj *.lib *.exp *.manifest

distclean: clean
	@echo Removing $(TARGET)
	-$(RM) $(TARGET)
