CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -Werror

.PHONY: run clean
run:
	$(CXX) $(CXXFLAGS) $(task).cpp -o $(task).out
	./$(task).out
	rm -rf *.out
clean:
	rm -rf *.out
