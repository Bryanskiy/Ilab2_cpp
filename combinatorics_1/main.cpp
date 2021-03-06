#include <iostream>
#include <iomanip>
#include <fstream>

#include "kgraph.hpp"

struct edge_t {
    std::size_t v1, v2, w;
};

std::vector<edge_t> read_input(std::istream& in) {
    std::vector<edge_t> edges;
    while(in) {
        edge_t tmp;
        in >> tmp.v1;
        if(!in) { break; } 
        in.ignore(3);
        in >> tmp.v2; 
        in.ignore(1);
        in >> tmp.w;
        edges.push_back(tmp);
    }

    return edges;
}

int main(int argc, char** argv) {
    std::ifstream input(argv[1]);
    std::vector<edge_t> edges = read_input(input);

    kgraph::kgraph_t<std::size_t, std::size_t> graph;

    for(auto&& edge : edges) {
        graph.push_edge(edge.v1, edge.v2, edge.w);
    }

    graph.dump(std::cout);
}