# define source directory
SRC		= Engine\src
# define include directory
INCLUDE	= Engine\include
# define lib directory
LIB		= Engine\lib

ifeq ($(OS),Windows_NT)
D_SOURCEDIRS	= $(DIR)
D_INCLUDEDIRS	= $(INCLUDE)
D_LIBDIRS		= $(LIB)
else
D_SOURCEDIRS	= $(shell find $(SRC) -type d)
D_INCLUDEDIRS	= $(shell find $(INCLUDE) -type d)
D_LIBDIRS		= $(shell find $(LIB) -type d)
endif

EXCLUDES := $(shell type $(OS)_exclude.txt)

$(eval SOURCEDIRS += $(D_SOURCEDIRS))
$(eval INCLUDEDIRS += $(D_INCLUDEDIRS))
$(eval LIBDIRS += $(D_LIBDIRS))

CODE := *.c *.cpp *.s

_SRCS := $(shell where /r $(SRC) $(CODE))
SRCS := $(filter-out $(addsuffix $(EXCLUDES),$(shell cd)),$(_SRCS))
#OBJCS := $(patsubst $(realpath $(SOURCEDIRS))%, $(realpath $(OBJDIR))%,$(realpath $(SRCS)))
OBJCS := $(SRCS:.c=.o)
OBJCS := $(OBJCS:.cpp=.o)
OBJCS := $(OBJCS:.s=.o)

#$(warning 'patsubst: $(patsubst $(realpath $(SOURCEDIRS))%, ./obj/$(SOURCEDIRS)%,$(realpath $(SOURCES)))')
$(eval OBJECTS += $(OBJCS))

$(warning 'Sources included: $(SRCS)')
#$(warning 'Sources objects: $(OBJECTS)')

LIBINCLUDED := $(addprefix -l,$(notdir $(wildcard $(LIB)/*)))

$(eval LFLAGS += $(LIBINCLUDED))

$(warning 'Libraryes included: $(LIBINCLUDED)')
$(warning 'Sources included: $(LFLAGS)')
