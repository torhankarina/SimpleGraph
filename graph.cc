//***************************************************************************
//
// Karina Torhan
// Z2111032
// CSCI 340 -OPE1 20268
// Assignment 10 Simple Graphs
// Due Date: 12/1/26, 5:00 PM
// I certify that this is my own work and where appropriate an extension
// of the starter code provided for the assignment.
//
//***************************************************************************

#include "graph.h"

#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

namespace {
vector<bool> visited;
vector<int> visit_order;
vector<pair<int, int> > traversal_edges;
}

void Graph::Depthfirst(int v)
{
  visited[v] = true;
  visit_order.push_back(v);

  for (int neighbor : adj_list[v]) {
    if (!visited[neighbor]) {
      traversal_edges.push_back(make_pair(v, neighbor));
      Depthfirst(neighbor);
    }
  }
}

Graph::Graph(const char* filename) : size(0)
{
  ifstream input(filename);

  if (!input) {
    cerr << "cannot open input file: " << filename << '\n';
    return;
  }

  if (!(input >> size) || size < 0) {
    cerr << "invalid graph size\n";
    size = 0;
    return;
  }

  adj_list.resize(size);
  labels.resize(size);

  // read the vertex labels
  for (int i = 0; i < size; ++i) {
    input >> labels[i];
  }

  // convert the matrix into adjacency lists
  for (int i = 0; i < size; ++i) {
    char row_label;
    input >> row_label;

    for (int j = 0; j < size; ++j) {
      int edge;
      input >> edge;

      if (edge == 1) {
        adj_list[i].push_back(j);
      }
    }
  }
}

Graph::~Graph()
{
}

int Graph::Getsize() const
{
  return size;
}

void Graph::Traverse()
{
  visited.assign(size, false);
  visit_order.clear();
  traversal_edges.clear();

  // visit every connected part of the graph
  for (int i = 0; i < size; ++i) {
    if (!visited[i]) {
      Depthfirst(i);
    }
  }

  cout << "\n------- traverse of graph ------\n";

  for (int v : visit_order) {
    cout << labels[v] << ' ';
  }
  cout << '\n';

  for (const auto& edge : traversal_edges) {
    cout << '(' << labels[edge.first] << ", "
         << labels[edge.second] << ") ";
  }

  cout << "\n--------- end of traverse -------\n\n";
}

void Graph::Print() const
{
  cout << "\nNumber of vertices in the graph: "
       << Getsize() << "\n\n";

  cout << "-------- graph -------\n";

  for (int i = 0; i < size; ++i) {
    cout << labels[i] << ":";

    bool first = true;

    for (int neighbor : adj_list[i]) {
      cout << (first ? " " : ", ") << labels[neighbor];
      first = false;
    }

    cout << '\n';
  }

  cout << "------- end of graph ------\n";
}