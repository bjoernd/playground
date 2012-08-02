#include <boost/tuple/tuple.hpp>          // tie()
#include <boost/graph/adjacency_list.hpp> // adjacency_list
#include <boost/graph/graphviz.hpp>       // dot output
#include <iostream>                       // std::cout
#include <fstream>                        // std::fstream
#include <string>

using namespace boost;

/*
 * Type for storing data along with vertices.
 */
struct MyVertexInfo
{
	std::string name;
};

/*
 * Graph type
 */
typedef adjacency_list<vecS, vecS, bidirectionalS, MyVertexInfo> Graph;

/*
 * BGL stores vertex properties independent from vertex nodes
 * (claiming to separate the generic container from the actual
 * stored data).
 */
typedef property_map<Graph, vertex_index_t>::type  IndexMap;

/*
 * Pretty-printing stuff
 */
static char const *Y   = "\033[33m";
static char const *B   = "\033[36m";
static char const *RES = "\033[0m";

std::string numToStr(unsigned n)
{
	switch (n) {
		case  0: return std::string("zero");
		case  1: return std::string("one");
		case  2: return std::string("two");
		case  3: return std::string("three");
		case  4: return std::string("four");
		case  5: return std::string("five");
		case  6: return std::string("six");
		case  7: return std::string("seven");
		case  8: return std::string("eight");
		case  9: return std::string("nine");
		default: return std::string("???");
	}
};

/*
 * Create graph edges
 */
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

	/* Now iterate over all vertices and set their name */
	graph_traits<Graph>::vertex_iterator vp_start, vp_end;
	IndexMap indices = get(vertex_index, g);
	for (tie(vp_start, vp_end) = vertices(g);
		 vp_start != vp_end; ++vp_start) {
		unsigned idx = indices[*vp_start];
		g[idx].name = numToStr(idx);
	}


}


void printVertices(Graph& g)
{

	std::cout << Y << "Vertices = " << RES;

	/*
	 * The fun begins: graph_traits allow to infer actual types
	 *    from the template BGL types. A vertex_iterator does
	 *    what its name suggests.
	 */
	graph_traits<Graph>::vertex_iterator vp_start, vp_end;

	IndexMap indices = get(vertex_index, g);
	/*
	 * vertices() returns a pair of iterators pointing to the
	 *     start and end element of the container.
	 */
	for (tie(vp_start,vp_end) = vertices(g);
		 vp_start != vp_end; ++vp_start)
	{
		unsigned idx = indices[*vp_start];
		if (vp_start != vertices(g).first) std::cout << " | ";
		std::cout << idx << " ["
		          << g[idx].name << "]";
	}

	std::cout << std::endl;
}


void printEdges(Graph& g)
{
	std::cout << Y << "Edges    = " << RES;

	/*
	 * An edge_iterator should be self-explanatory as well.
	 */
	graph_traits<Graph>::edge_iterator edge_start, edge_end;

	IndexMap indices = get(vertex_index, g);

	/*
	 * edges() gets (start,end) edge_iterator pair for the graph.
	 *
	 * [[Note the use of boost::tie().]]
	 */
	for (tie(edge_start, edge_end) = edges(g);
		 edge_start != edge_end; ++edge_start) {
		std::cout << "(" << indices[source(*edge_start, g)]
		          << ", " << indices[target(*edge_start, g)] << ") ";
	}

	std::cout << std::endl;
}


/*
 * Visitor functor.
 *
 * Code below iterates over all vertices. This functor defines
 * what is to be done with each vertex upon visiting.
 */
template <class Graph> struct vertex_visitor
{
	typedef typename graph_traits<Graph>::vertex_descriptor    Vertex;
	typedef graph_traits<Graph> GraphTraits;

	vertex_visitor(Graph& _g) : g(_g)
	{
		 index = get(vertex_index, g);
	}

	IndexMap index;
	Graph& g;

	/*
	 * Graphs with the bidirectionalS have an additional iterator
	 * set that allows examining their IN edges.
	 */
	void inEdges(const Vertex& v) const
	{
		std::cout << B << "      in edges: " << RES;
		typename GraphTraits::in_edge_iterator in_start, in_end;
		typename GraphTraits::edge_descriptor e;
		for (tie(in_start, in_end) = in_edges(v, g);
			 in_start != in_end; ++in_start) {
			e = *in_start;
			Vertex src = source(e,g);
			Vertex targ = target(e,g);
			std::cout << "(" << index[src] << ", " << index[targ] << ") ";
		}
		std::cout << std::endl;
	}

	/*
	 * out_edges() allows iterating over a vertex' OUT edges.
	 */
	void outEdges(const Vertex& v) const
	{
		std::cout << B << "     out edges: " << RES;
		typename GraphTraits::out_edge_iterator out_start, out_end;
		typename GraphTraits::edge_descriptor e;
		for (tie(out_start, out_end) = out_edges(v, g);
			 out_start != out_end; ++out_start) {
			e = *out_start;
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


/*
 * Functor that will be called by the Graphviz output writer
 * for every node in the graph.
 */
struct GraphvizNamedVertexWriter
{
	GraphvizNamedVertexWriter(Graph& _g)
		: g(_g)
	{ }

	Graph&   g;

	template <class Vertex>
	void operator() (std::ostream& out, const Vertex &v) const
	{
		out << " [label=\"" << g[v].name << "\"]";
	}
};


int main()
{
	Graph g;

	fillGraph(g);

	printVertices(g);
	printEdges(g);

	std::cout << Y << "Iterating vertices" << RES << std::endl;
	std::for_each(vertices(g).first, vertices(g).second, vertex_visitor<Graph>(g));

	GraphvizNamedVertexWriter gnw(g);
	/*
	 * BGL comes with functions to write the graph into a GraphViz file!
	 */
	std::cout << Y << "Graphviz =" << RES << std::endl;
	write_graphviz(std::cout, g, gnw);

	std::ofstream outfile("foo.dot");
	if (outfile.is_open()) {
		write_graphviz(outfile, g, gnw);
	}

	return 0;
}
