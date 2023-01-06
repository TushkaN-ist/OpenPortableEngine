#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# define the Cpp compiler to use
CXX = g++

# define any compile-time flags
CXXFLAGS	:= -std=c++11 -Wall -Wextra -g -DUNICODE -D_UNICODE
ifeq ($(TARGET), DEBUG)
CXXFLAGS += -DDEBUG -D_DEBUG 
endif
ifeq ($(TARGET), WIN)
CXXFLAGS += -D_WINFRAME_
endif
# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = 

# define output directory
OUTPUT	:= output

# define source directory
SRC		:= 

# define include directory
INCLUDE	:= 

# define lib directory
LIB		:= 

ifeq ($(OS),Windows_NT)
ifeq ($(TARGET), DEBUG)
MAIN	:= main_d.exe
else
MAIN	:= main.exe
endif
FIXPATH = $(subst /,\,$1)
RM			:= del /q /f
MD	:= mkdir
else
MAIN	:= main
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p
endif

OBJECTS := 
include $(wildcard files_*.inc)

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

$(warning $(INCLUDES))

# define the C libs
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))
# define the C object files 
#OBJECTS		:= $(SRC_FILES)

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(MAIN))

all: $(OUTPUT) $(MAIN)
	@echo Executing 'all' complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

$(MAIN): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@

.PHONY: clean
clean:
	$(RM) $(OUTPUTMAIN)
	$(RM) $(call FIXPATH,$(OBJECTS))
	@echo Cleanup complete!

run: all
	./$(OUTPUTMAIN)
	@echo Executing 'run: all' complete!