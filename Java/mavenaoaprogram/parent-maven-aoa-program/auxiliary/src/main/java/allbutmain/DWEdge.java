package allbutmain;

/* Represents a weighted edge in a graph */
public class DWEdge {

    private final int source;
    private final int target;
    private final double rate;

    public DWEdge(int source, int target, double rate) {
        this.source = source;
        this.target = target;
        this.rate = rate;
    }

    public int getSource() {
        return source;
    }

    public int getTarget() {
        return target;
    }

    public double getRate() {
        return rate;
    }

    public String toString() {
        return String.format("%d -> %d : %.02f", source, target, rate);
    }

}
