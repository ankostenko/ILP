#include "graph.h"

bool are_edges_the_same_undirected_graphs(Edge edge1, Edge edge2) {
  return ((edge1.start.number == edge2.start.number) && (edge1.end.number == edge2.end.number)) || 
         ((edge1.start.number == edge2.end.number) && (edge1.end.number == edge2.start.number));
}

/// Compare two edges for equality
/// @param edge1 first edge
/// @param edge2 second edge
/// @return true if edges are equal false otherwise
bool are_edges_the_same_directed_graphs(Edge edge1, Edge edge2) {
  return (edge1.start.number == edge2.start.number) && (edge1.end.number == edge2.end.number);
}