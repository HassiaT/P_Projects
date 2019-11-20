package allbutmain;
import java.util.*;
import java.util.logging.Logger;



/* Bellman-Ford Algorithm */
public class BFAlgorithm {

    private double[] distances;
    private DWEdge[] edgeTo;
    private boolean[] onqueue;
    private Queue<Integer> queue;
    private int cost;

    public List<Iterable<DWEdge>> getCycle() {
        return cycle;
    }

    public void setCycle(List<Iterable<DWEdge>> cycle) {
        this.cycle = cycle;
    }

    private List<Iterable<DWEdge>> cycle;
    private static Logger logger = Logger.getLogger(BFAlgorithm.class.getName());

    public double[] getDistances() {
        return distances;
    }

    public void setDistances(double[] distances) {
        this.distances = distances;
    }

    public DWEdge[] getEdgeTo() {
        return edgeTo;
    }

    public void setEdgeTo(DWEdge[] edgeTo) {
        this.edgeTo = edgeTo;
    }

    public boolean[] getOnqueue() {
        return onqueue;
    }

    public void setOnqueue(boolean[] onqueue) {
        this.onqueue = onqueue;
    }

    public Queue<Integer> getQueue() {
        return queue;
    }

    public void setQueue(Queue<Integer> queue) {
        this.queue = queue;
    }

    public int getCost() {
        return cost;
    }

    public void setCost(int cost) {
        this.cost = cost;
    }


    private void relaxEdge(Graph G, int v) {
        logger.info("Starting function relax in class BFAlgorithm");
        Iterable<DWEdge> edgesfromv = G.adjacency(v);

        for (DWEdge ed : edgesfromv) {
            int sink = ed.getTarget();

            if (distances[sink] > distances[v] + ed.getRate()) {
                distances[sink] = distances[v] + ed.getRate();
                edgeTo[sink] = ed;
                if (!onqueue[sink]) {
                    queue.add(sink);
                }
            }
            if (cost++ % G.getNumberVertices() == 0)
                findArbitrageOpportunity();
        }
    }

    private void findArbitrageOpportunity() {
        logger.info("Running function findArbitrageOpportunity - class BFAlgorithm");
        int V = edgeTo.length;
        Graph bisgraph = new Graph(V);
        for (int v = 0; v < V; v++) {
            if (edgeTo[v] != null) {
                bisgraph.addEdge(edgeTo[v]);
            }
        }
        ArbitrageOpportunityFinder opp = new ArbitrageOpportunityFinder(bisgraph);
        this.cycle = opp.getCycles();
    }


    public boolean hasarbitrageopportunity() {
        logger.info("Starting function hasarbitrageopportunity - class BFAlgorithm - checking if AO found");
        return (cycle.isEmpty());
    }

    public String gettingArbitrageAnswer(Map<String, Integer> _ids) {
        String result = "";
        String aofound = "";
        logger.info("Runnning function gettingArbitrageAnswer - class BFAlgorithm");
        if (!this.hasarbitrageopportunity()) {
            double stake = 1000.0;
            for (Iterable<DWEdge> it : this.cycle) {
                for (DWEdge e : it) {
                    String currencySource = ArbitrageFunctions.getKey(_ids, e.getSource());
                    String currencySink = ArbitrageFunctions.getKey(_ids, e.getTarget());
                    aofound = String.format("%10.5f  %s ", stake, currencySource);
                    stake *= Math.exp(-e.getRate());
                    aofound += String.format("  %10.5f  %s ", stake, currencySink);
                }
            }
            result += aofound;
            result += "\n";
        }
        else
        {
            result += "No arbitrage opportunity has been found for those currencies \n";
        }
        return result;
    }


    public BFAlgorithm(Graph G, int source) {
        logger.info("Starting constructor BFAlgorithm - class BFAlgorithm");
        distances = new double[G.getNumberVertices()];
        edgeTo = new DWEdge[G.getNumberVertices()];
        queue = new LinkedList<>();
        for (int v = 0; v < G.getNumberVertices(); v++) {
            distances[v] = Double.POSITIVE_INFINITY;
        }
        distances[source] = 0.0;
        queue.add(source);
        onqueue[source] = true;
        while (!queue.isEmpty() && !this.hasarbitrageopportunity()) {
            int v = queue.poll();
            onqueue[v] = false;
            relaxEdge(G, v);
        }
    }
}
