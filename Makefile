CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
GTEST_FLAGS = -lgtest -lgtest_main -pthread

TARGET = test_list_doubly_linked
SOURCES = test_list_doubly_linked.cc
HEADERS = list_doubly_linked.h

# Default rule: compile the test program
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES) $(GTEST_FLAGS)

# Rule to run the tests (must be called explicitly)
.PHONY: run
run: $(TARGET)
	./$(TARGET)

# Clean rule for convenience
.PHONY: clean
clean:
	rm -f $(TARGET)
