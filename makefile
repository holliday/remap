########## DEFINITIONS ##########
TARGET		:= remap.dll

SUBDIRS		:= .
INCLUDES	:= /I ../Orbitersdk/include/
LIBRARIES	:= /LIBPATH:../Orbitersdk/lib/ orbiter.lib Orbitersdk.lib
DEFINES		:= /D WIN32 /D NDEBUG /D WINDLL
OBJECTS		:=

########## OPTIONS ##########

include makefile_tgt.mk
