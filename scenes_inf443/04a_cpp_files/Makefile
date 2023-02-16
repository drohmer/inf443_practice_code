# This Makefile will generate an executable file named cpp_files


TARGET ?= cpp_files #name of the executable
SRC_DIRS ?= src/ 
CXX = g++ #Or clang++

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS  := . 
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) $(shell pkg-config --cflags glfw3)

CPPFLAGS += $(INC_FLAGS) -g -O2 -std=c++14 -Wall -Wextra -Wfatal-errors -Wno-sign-compare -Wno-type-limits -Wno-pragmas 

LDLIBS += -ldl -lm

$(TARGET): $(OBJS)
	echo $(CURDIR)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LOADLIBES) $(LDLIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)