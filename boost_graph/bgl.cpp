#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graphviz.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace boost;

typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;
typedef property_map<Graph, vertex_index_t>::type IndexMap;

IndexMap indices;

static char const *Y   = "\033[33m";
static char const *B   = "\033[34m";
static char const *RES = "\033[0m";

void fillGraph(Graph& g)
{
	enum { A, B, C, D, E, _END_ };
	const unsigned num_vertices = _END_;

	typedef std::pair<int,int> Edge;
	Edge edges [] = {
		Edge(A,B),
		Edge(A,C),
		Edge(A,D),
		Edge(B,D),
		Edge(D,E)
	};

	for (unsigned i = 0; i < num_vertices; i++) {
		add_edge(edges[i].first, edges[i].second, g);
	}
}


void printVertices(Graph& g)
{

	std::cout << Y << "Vertices = " << RES;

	typedef graph_traits<Graph>::vertex_iterator viter;
	std::pair<viter, viter> vp;
	for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
		unsigned id = *(vp.first);
		std::cout << indices[id] << " ";
	}

	std::cout << std::endl;
}


void printEdges(Graph& g)
{
	std::cout << Y << "Edges    = " << RES;
	graph_traits<Graph>::edge_iterator ei, ei_end;

	for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
		std::cout << "(" << indices[source(*ei, g)]
		          << ", " << indices[target(*ei, g)] << ") ";
	}

	std::cout << std::endl;
}


template <class Graph> struct vertex_visitor
{
	typedef typename graph_traits<Graph>::vertex_descriptor    Vertex;
	typedef typename property_map<Graph, vertex_index_t>::type IndexType;
	typedef graph_traits<Graph> GraphTraits;

	vertex_visitor(Graph& _g) : g(_g)
	{
		 index = get(vertex_index, g);
	}

	IndexType index;
	Graph& g;

	void inEdges(const Vertex& v) const
	{
		std::cout << B << "      in edges: " << RES;
		typename GraphTraits::in_edge_iterator in_i, in_end;
		typename GraphTraits::edge_descriptor e;
		for (tie(in_i, in_end) = in_edges(v, g); in_i != in_end; ++in_i) {
			e = *in_i;
			Vertex src = source(e,g);
			Vertex targ = target(e,g);
			std::cout << "(" << index[src] << ", " << index[targ] << ") ";
		}
		std::cout << std::endl;
	}

	void outEdges(const Vertex& v) const
	{
		std::cout << B << "     out edges: " << RES;
		typename GraphTraits::out_edge_iterator out_i, out_end;
		typename GraphTraits::edge_descriptor e;
		for (tie(out_i, out_end) = out_edges(v, g); out_i != out_end; ++out_i) {
			e = *out_i;
			Vertex src = source(e,g);
			Vertex targ = target(e,g);
			std::cout << "(" << index[src] << ", " << index[targ] << ") ";
		}
		std::cout << std::endl;
	}

	void operator () (const Vertex& v) const
	{
		std::cout << "Vertex " << index[v] << std::endl;
		outEdges(v);
		inEdges(v);
	}
};


int main()
{
	Graph g;
	
	const char *vert_names = "ABCDE";

	fillGraph(g);

	indices = get(vertex_index,  g);

	printVertices(g);
	printEdges(g);

	std::cout << Y << "Iterating " << RES << std::endl;
	std::for_each(vertices(g).first, vertices(g).second, vertex_visitor<Graph>(g));

	std::cout << Y << "Graphviz =" << RES << std::endl;
	write_graphviz(std::cout, g);

	std::ofstream outfile("foo.dot");
	if (outfile.is_open()) {
		write_graphviz(outfile, g);
	}

	return 0;
}
