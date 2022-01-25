package CountVertex;

import java.io.*;
import java.util.*;
import java.util.LinkedList; 
public class Solution {  
    private int V;   // No. of vertices 
    private LinkedList<Integer> adj[]; //Adjacency List
    private boolean hasVisited[]; // Visitation array
  
    //Constructor 
    Solution(int v) 
    { 
        V = v;
        hasVisited = new boolean[v];
        adj = new LinkedList[v]; 
        for (int i=0; i<v; ++i) {
        	adj[i] = new LinkedList();
        	hasVisited[i] = false;
        }
    } 
  
    //Function to add an edge into the graph 
    void addEdge(int v,int w)  {   adj[v].add(w);   } 
    
    //Function to reset the marked list
    void resetMarked() {
    	
    	for(int i = 0; i < hasVisited.length; i++) {
    		
    		hasVisited[i] = false;
    	}
    }
  
    //do BFS traversal from a given source s 
    Boolean isReachable(int s, int d) 
    { 
        boolean isReachable = false;
        int i = 0;
        hasVisited[s] = true;
        // While doing BFS traversal if d is reachable from s return true
        // set is reachable to true if reachable
        if(s != d) {
            while(isReachable == false && i < adj[s].size()) {
                
            	if(hasVisited[adj[s].get(i)] != true) {
                isReachable = isReachable(adj[s].get(i), d);
            	}
                i++;
            }
        } else {
        
            isReachable = true;
        
        }
        
        // If BFS is complete without visited d 
        return isReachable; 
    } 
    
    
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int M = s.nextInt();
        
        
        int A[][] = new int[M][M];        
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                A[i][j] = s.nextInt();
            }
        }
        int V = M+M; 
        Solution g = new Solution(V); 
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {   
			    if(A[i][j]!=0) {
                    g.addEdge( i,j); 
                }                
            }
        }
        int S = s.nextInt();
        int x=0;
        for(int i=1;i<M;i++){
        	g.resetMarked();
            int u = S; 
            if (g.isReachable(u, i))
                x++;
        }
        System.out.println(x);
    
    }
}