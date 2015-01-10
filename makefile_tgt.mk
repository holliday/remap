########## DEFINITIONS ##########
FLAVORS		:= .c .C .cc .c++ .cpp .cxx

INCLUDES	:= $(INCLUDES) $(foreach n,$(SUBDIRS),/I $(n))
SOURCES		:= $(SOURCES) $(foreach n,$(SUBDIRS),$(foreach f,$(FLAVORS),$(wildcard $(n)/*$(f))))

OBJECTS		:= $(OBJECTS) $(notdir $(SOURCES))
$(foreach f,$(FLAVORS),$(eval OBJECTS := $(patsubst %$(f),%.obj,$(OBJECTS))))

ifneq ($(patsubst %.dll,%,$(TARGET)),$(TARGET))
TYPE := shared
else ifneq ($(TARGET),)
TYPE := binary
else
TYPE := object
endif

########## OPTIONS ##########
CL			?= cl
CLFLAGS		?= /O2 /EHsc /MD /GS- /fp:fast /W3 /GL

LINK		?= link
LINKFLAGS	?= /MACHINE:X86 /SUBSYSTEM:WINDOWS /INCREMENTAL:NO /LTCG
LINKFLAGS	+= $(if $(filter shared,$(TYPE)),/DLL,) 

RM			?= rm -vf

########## RULES ##########

########## OBJECT ##########
ifeq (object,$(TYPE))

all: $(OBJECTS)
	@echo "Created $(OBJECTS)"
	@echo

########## BINARY ##########
########## SHARED ##########
else

all: $(TARGET)
	@echo "Compiled $(TARGET)"
	@echo

$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)"
	$(LINK) /OUT:$(TARGET) $(LINKFLAGS) $(LIBRARIES) $(OBJECTS)
	@echo

endif

define RULE_OBJ =
$(1): $(2)
	@echo "Compiling $(1)"
	$(CL) $(INCLUDES) $(DEFINES) $(CLFLAGS) /Fo $(1) /c $(2)
	@echo
endef

# dynamically generate rules for .obj files
$(foreach n,$(shell seq 1 $(words $(SOURCES))),$(eval $(call RULE_OBJ,$(word $(n),$(OBJECTS)),$(word $(n),$(SOURCES)))))

########## CLEAN ##########
clean:
	@echo "Cleaning files"
	$(RM) $(OBJECTS) $(DEPENDENCIES)
	@echo

distclean: clean
	@echo "Removing $(TARGET)"
	$(RM) $(TARGET)
	@echo

.PHONY: all clean distclean
