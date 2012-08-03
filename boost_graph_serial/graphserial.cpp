#include <boost/tuple/tuple.hpp>                 // tie()
#include <boost/graph/adjacency_list.hpp>        // adjacency_list
#include <boost/graph/adj_list_serialize.hpp>    // adjacency_list serialization
#include <boost/graph/graphviz.hpp>              // dot output
#include <boost/serialization/serialization.hpp> // serialization
#include <boost/archive/binary_iarchive.hpp>     // input archive
#include <boost/archive/binary_oarchive.hpp>     // output archive
#include <iostream>                              // std::cout
#include <fstream>                               // std::fstream
#include <string>

using namespace boost;

/*
 * Type for storing data along with vertices.
 */
struct MyVertexInfo
{
	std::string name;

	/* 
	 * In order for a Boost::graph to be serializable, its
	 * vertex and edge info objects need to be serializable.
	 * Hence, we need this function.
	 */
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & name;
	}

	MyVertexInfo(std::string _n = "")
		: name(_n)
	{ }
};

/*
 * Graph type
 */
typedef adjacency_list<vecS, vecS, bidirectionalS, MyVertexInfo> Graph;

/*
 * Pretty-printing stuff
 */
static char const *Y   = "\033[33m";
static char const *B   = "\033[36m";
static char const *RES = "\033[0m";
/*
 * Create graph edges
 */
void fillGraph(Graph& g)
{
	graph_traits<Graph>::vertex_descriptor desc[5];

	desc[0] = add_vertex(MyVertexInfo("Dresden"), g);
	desc[1] = add_vertex(MyVertexInfo("Leipzig"), g);
	desc[2] = add_vertex(MyVertexInfo("Görlitz"), g);
	desc[3] = add_vertex(MyVertexInfo("Zittau"), g);
	desc[4] = add_vertex(MyVertexInfo("Chemnitz"), g);

	add_edge(desc[0], desc[1], g);
	add_edge(desc[0], desc[2], g);
	add_edge(desc[0], desc[4], g);
	add_edge(desc[1], desc[4], g);
	add_edge(desc[2], desc[3], g);
}

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

void gvOutputGraph(Graph& g, char const *file)
{
	GraphvizNamedVertexWriter gnw(g);
	std::ofstream outfile(file);
	if (outfile.is_open()) {
		write_graphviz(outfile, g, gnw);
		std::cout << B << "     Success." << RES << std::endl;
	} else {
		std::cout << "     Could not open file." << std::endl;
	}
}

void serializeGraph(Graph& g, char const *file)
{
	std::ofstream of(file);
	boost::archive::binary_oarchive oa(of);
	oa << g;
}

Graph deserializeGraph(char const *file)
{
	Graph ret = 0;

	std::ifstream ifs(file);
	boost::archive::binary_iarchive ia(ifs);
	ia >> ret;

	return ret;
}

int main()
{
	Graph g;
	std::cout << Y << "Filling graph." << RES << std::endl;
	fillGraph(g);

	std::cout << Y << "Writing Graphviz" << RES << std::endl;
	gvOutputGraph(g, "foo.dot");

	std::cout << Y << "Storing graph." << RES << std::endl;
	serializeGraph(g, "graph.dat");

	std::cout << Y << "Loading graph." << RES << std::endl;
	Graph g2 = deserializeGraph("graph.dat");
	gvOutputGraph(g, "foo2.dot");
	
	return 0;
}
