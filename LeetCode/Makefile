CXX := g++
CXXFLAGS := -std=c++23

.PHONY: run clean
run:
	$(CXX) $(CXXFLAGS) $(task).cpp -o $(task)
	./$(task)
	rm -rf $(task)
clean:
	rm -rf $(task)
