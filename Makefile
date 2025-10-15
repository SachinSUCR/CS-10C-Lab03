CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lgtest -lpthread

# Default rule: build test executable
test_list_doubly_linked: test_list_doubly_linked.cc
	$(CXX) $(CXXFLAGS) test_list_doubly_linked.cc -o test_list_doubly_linked $(LDFLAGS)

# Run tests
run: test_list_doubly_linked
	./test_list_doubly_linked
