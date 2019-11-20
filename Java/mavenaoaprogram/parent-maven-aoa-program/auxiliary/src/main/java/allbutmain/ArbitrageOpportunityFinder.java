package allbutmain;
import java.util.List;
import java.util.Stack;
import java.util.logging.Logger;

public class ArbitrageOpportunityFinder {
    private static Logger logger = Logger.getLogger(ArbitrageOpportunityFinder.class.getName());
    private boolean[] marked;
    private int[] edgeTo;
    private boolean[] onStack;

    public List<Iterable<DWEdge>> getCycles() {
        return cycles;
    }

    public void setCycles(List<Iterable<DWEdge>> cycles) {
        this.cycles = cycles;
    }

    private List<Iterable<DWEdge>> cycles;


    public ArbitrageOpportunityFinder(Graph G) {
        logger.info("Constructor ArbitrageOpportunityFinder - Searching arbitrage opportunity");
        onStack = new boolean[G.getNumberVertices()];
        edgeTo = new int[G.getNumberVertices()];
        marked = new boolean[G.getNumberVertices()];
        for (int i = 0; i < G.getNumberVertices(); i++) {
            if (!marked[i])
                dfs(G, i);
        }
    }

    public boolean hasArbitrageOpprotunity() {
        return cycles.isEmpty();
    }

    private void dfs(Graph G, int vertex) {
        logger.info("Running dfs class ArbitrageOpportunityFinder");
        onStack[vertex] = true;
        marked[vertex] = true;
        for (DWEdge ed : G.adjacency(vertex)) {
            int w = ed.getTarget();
            if (this.hasArbitrageOpprotunity()) return;
            else if (!marked[w]) {
                edgeTo[w] = vertex;
                dfs(G, w);
            }
            // already on the recursive call
            else if (onStack[w]) {
                double currentrate = 0.0;
                DWEdge oneedge = null;
                Stack<Integer> onecycle = new Stack<Integer>();
                Stack<DWEdge> edgescycles = new Stack<>();
                double totalcostpath = 0.0;
                int lastvertex = -1;
                for (int x = vertex; x != w; x = edgeTo[x]) {
                    onecycle.push(x);
                    currentrate = G.gettingRate(x, lastvertex);
                    totalcostpath += currentrate;
                    if (lastvertex != -1) {
                        oneedge = new DWEdge(x, lastvertex, currentrate);
                        edgescycles.add(oneedge);
                    }
                    lastvertex = x;
                }
                onecycle.push(w);
                currentrate = G.gettingRate(w, lastvertex);
                totalcostpath += currentrate;
                oneedge = new DWEdge(w, lastvertex, currentrate);
                edgescycles.add(oneedge);
                lastvertex = w;
                onecycle.push(vertex);
                currentrate = G.gettingRate(vertex, lastvertex);
                totalcostpath += currentrate;
                oneedge = new DWEdge(w, lastvertex, currentrate);
                edgescycles.add(oneedge);

                /* IF THE CYCLE DOES NOT HAVE A NEGATIVE LENGTH GET RID OF IT */
                if (totalcostpath < 0)
                    cycles.add(edgescycles);
            }
        }

    }

}
