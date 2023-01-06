ifeq ($(TARGET), DEBUG)
LFLAGS += 
else
LFLAGS += -s -Os -static -g -ffunction-sections -fdata-sections -fvisibility-inlines-hidden
ifeq ($(TARGET), WIN)
LFLAGS += -mwindows
endif
endif
