CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -Werror -fno-omit-frame-pointer -fsanitize=address,undefined

.PHONY: run clean
run:
	$(CXX) $(CXXFLAGS) $(task).cpp -o $(task).out
	./$(task).out
	rm -rf *.out
build:
	$(CXX) $(CXXFLAGS) $(task).cpp -o $(task).out
clean:
	rm -rf *.out
