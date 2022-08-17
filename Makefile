SRC := $(wildcard *.cpp)
OBJS := $(SRC:%.cpp=obj/%.o)
FLAGS := -std=c++17 -lglfw -lGL -MMD #-O3

.PHONY: all
all: | build

.PHONY: clean
clean:
	rm -f obj/* out

obj_folder:
	mkdir -p obj/

build: obj_folder $(OBJS)
	$(CXX) -o out obj/*.o $(FLAGS)

-include $(OBJS:.o=.d)
obj/%.o: %.cpp
	$(CXX) -c $< -o $@ $(FLAGS)
