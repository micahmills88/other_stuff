
import java.util.*;

public class GraphStructure<T> 
{
    //Implementation by adjacency list
    protected List<T> graphVertices = new ArrayList<T>();
    protected List<List<Integer>> graphEdges = new ArrayList<List<Integer>>();

    //Constructor to create graph from list data
    protected GraphStructure(List<Edge> edges, List<T> vertices) 
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            graphVertices.add(vertices.get(i));
        }
        createAdjacencyLists(edges, vertices.size());
    }

    //for each vertex, create its list of edges
    private void createAdjacencyLists(List<Edge> edges, int numberOfVertices) 
    {
        //add each vertex to the list
        for (int i = 0; i < numberOfVertices; i++) 
        {
            graphEdges.add(new ArrayList<Integer>());
        }
        
        for (Edge edge: edges) 
        {
            graphEdges.get(edge.start).add(edge.end);
        }
    }

    //get the size of the list of vertices
    public int getSize() 
    {
        return graphVertices.size();
    }
    
    public T getVertex(int index) 
    {
        return graphVertices.get(index);
    }
    
    public int getIndex(T t) 
    {
        return graphVertices.indexOf(t);
    }

    //get the entire list of vertices
    public List<T> getVertices() 
    {
        return graphVertices;
    }

    //return the list of edges for an index
    public List<Integer> getNeighbors(int index) 
    {
        return graphEdges.get(index);
    }

    //prints the graph as a table
    public String toString() 
    {
        String temp = new String();
        for (int i = 0; i < graphEdges.size(); i++) 
        {
            temp += String.format(getVertex(i) + " (" + i + "): ");
            for (int j = 0; j < graphEdges.get(i).size(); j++) 
            {
                temp += String.format("(" + i + ", " + graphEdges.get(i).get(j) + ") ");
            }
            temp += "\n";
        }
        return temp;
    }

    //empty the graph contents
    public void clear() 
    {
        graphVertices.clear();
        graphEdges.clear();
    }

    //add vertex 
    public void addVertex(T t) 
    {
        graphVertices.add(t);
        graphEdges.add(new ArrayList<Integer>());
    }

    //add edge 
    public void addEdge(int s, int e) 
    {
        graphEdges.get(s).add(e);
        graphEdges.get(e).add(s);
    }

    //depth first traversal
    public List<Integer> depthFirstSearch(int vertex) 
    {
        List<Integer> searchOrder = new ArrayList<Integer>();
        int[] parent = new int[graphVertices.size()];
        for (int i = 0; i < parent.length; i++)
        {
            parent[i] = -1; // Initialize parent[i] to -1
        }

        boolean[] isVisited = new boolean[graphVertices.size()];
        dfsRecurse(vertex, parent, searchOrder, isVisited);
        return searchOrder;
    }

    //depth first search continued
    private void dfsRecurse(int vertex, int[] parent, List<Integer> searchOrder, boolean[] isVisited) 
    {
        // Store the visited vertex
        searchOrder.add(vertex);
        isVisited[vertex] = true; //mark vertex as visited

        for (int i : graphEdges.get(vertex)) 
        {
            if (!isVisited[i]) 
            {
                parent[i] = vertex; // The parent of vertex i is v
                dfsRecurse(i, parent, searchOrder, isVisited); // Recursive search
            }
        }
    }

    //breadth first search
    public List<Integer> breadthFirstSearch(int vertex) 
    {
        List<Integer> searchOrder = new ArrayList<Integer>();
        int[] parent = new int[graphVertices.size()];
        for (int i = 0; i < parent.length; i++)
        {
            parent[i] = -1;
        }

        java.util.LinkedList<Integer> queue = new java.util.LinkedList<Integer>();
        boolean[] isVisited = new boolean[graphVertices.size()];
        queue.offer(vertex);
        isVisited[vertex] = true;

        while (!queue.isEmpty()) 
        {
            int qp = queue.poll();
            searchOrder.add(qp);
            for (int edges : graphEdges.get(qp)) 
            {
                if (!isVisited[edges]) 
                {
                    queue.offer(edges);
                    parent[edges] = qp;
                    isVisited[edges] = true;
                }
            }
        }
        return searchOrder;
    }

    //edge class representing a connection between two vertices
    public static class Edge 
    {
        public int start; //beginning vertex
        public int end; //end vertex

        public Edge(int s, int e) 
        {
            start = s;
            end = e;
        }
    }
}