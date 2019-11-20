package allbutmain;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.logging.Logger;

/* Represents an weighted digraph */
public class Graph {

    public int getNumberVertices() {
        return numberVertices;
    }

    public void setNumberVertices(int numberVertices) {
        this.numberVertices = numberVertices;
    }

    public int getEdges() {
        return edges;
    }

    public void setEdges(int edges) {
        this.edges = edges;
    }

    public Set<DWEdge>[] getAdjacency() {
        return adjacency;
    }

    public void setAdjacency(Set<DWEdge>[] adjacency) {
        this.adjacency = adjacency;
    }

    private int numberVertices = 0;
    private int edges;
    private Set<DWEdge>[] adjacency;
    private static Logger logger = Logger.getLogger(Graph.class.getName());

    public Graph(int V) {
        logger.info("Constructor Graph - class Graph");
        this.numberVertices = V;
        this.edges = 0;
        adjacency = (Set<DWEdge>[]) (new HashSet[V]);
        for (int v = 0; v < V; v++) {
            adjacency[v] = new HashSet<DWEdge>();
        }
        logger.info("End constructor Graph - class Graph");
    }


    public Graph(int V, int E, Set<DWEdge>[] alledges) {
        logger.info("Constructor Graph - class Graph");
        this.numberVertices = V;
        this.edges = E;
        this.adjacency = alledges;
        String graphinit = String.format("Ending constructor Graph created with %d vertices and %d edges\n", this.numberVertices, this.edges);
        logger.info(graphinit);
    }

    public double gettingRate(int source, int sink) {
        logger.info("Function gettingRate - class Graph");
        double ratefound = 0.0;
        if (sink != -1) {
            Iterable<DWEdge> edgesfromsource = this.adjacency(source);
            for (DWEdge ed : edgesfromsource) {
                if (ed.getTarget() == sink) {
                    ratefound = ed.getRate();
                    break;
                }
            }
        }
        return ratefound;
    }

    public void addEdge(DWEdge e) {
        logger.info("Function addEdge - class Graph");
        adjacency[e.getSource()].add(e);
        edges++;
        logger.info("Ending function addEdge - class Graph");
    }

    /* getting the neighbors of vertex whose id is v */
    public Iterable<DWEdge> adjacency(int v) {
        return adjacency[v];
    }


    public Iterable<DWEdge> edges() {
        Set<DWEdge> bagofedges = new HashSet<>();
        for (int i = 0; i < numberVertices; i++) {
            for (DWEdge ed : this.adjacency[i]) {
                bagofedges.add(ed);
            }
        }
        return bagofedges;
    }
}
