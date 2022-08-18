CPP_SRC  := $(wildcard *.cpp)
C_SRC    := $(wildcard *.c)
OBJS     := $(CPP_SRC:%.cpp=obj/%.o) $(C_SRC:%.c=obj/%.o)
FLAGS    := -std=c++17 -lglfw -lGL -limgui -lstb -lsndfile -lopenal -MMD -O3
INCLUDES := -I/usr/include/imgui/
EXECUTABLE := oscilloscope

.PHONY: all clean
all: | build

clean:
	rm -f obj/* out
	rm -f $(EXECUTABLE)

obj_folder:
	mkdir -p obj/

build: obj_folder $(OBJS)
	$(CXX) -o $(EXECUTABLE) obj/*.o $(FLAGS) $(INCLUDES)

-include $(OBJS:.o=.d)
obj/%.o: %.cpp
	$(CXX) -c $< -o $@ $(FLAGS) $(INCLUDES)
obj/%.o: %.c
	$(CC) -c $< -o $@ $(FLAGS) $(INCLUDES)
