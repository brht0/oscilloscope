SRC := $(wildcard *.cpp)
OBJS := $(SRC:%.cpp=obj/%.o)
FLAGS := -std=c++17 -lglfw -lGL -O3 -MMD

.PHONY: all
all: | build

.PHONY: clean
clean:
	rm -f obj/* out

obj_folder:
	mkdir -p obj/

build: obj_folder $(OBJS)
	$(CXX) $(FLAGS) obj/*.o -o out

-include $(OBJS:.o=.d)
obj/%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@
