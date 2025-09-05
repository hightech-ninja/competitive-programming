CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra

.PHONY: clean monotonic/stack monotonic/queue monotonic/deque

monotonic/stack:
	$(CXX) $(CXXFLAGS) stack.cpp -o stack
	./stack
	@rm stack
monotonic/queue:
	$(CXX) $(CXXFLAGS) queue.cpp -o queue
	./queue
	@rm queue
monotonic/deque:
	$(CXX) $(CXXFLAGS) deque.cpp -o deque
	./deque
	@rm deque

clean:
	@rm -f stack queue deque
