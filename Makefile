CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

simplegraph: graph.o simplegraph.o
	$(CXX) $(CXXFLAGS) -o simplegraph graph.o simplegraph.o

graph.o: graph.cc graph.h
	$(CXX) $(CXXFLAGS) -c graph.cc

simplegraph.o: simplegraph.cc graph.h
	$(CXX) $(CXXFLAGS) -c simplegraph.cc

clean:
	rm -f simplegraph graph.o simplegraph.o

.PHONY: clean