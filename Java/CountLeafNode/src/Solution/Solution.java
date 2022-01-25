package Solution;

import java.util.*;

public class Solution {
    
    static class Node {
        int key;
        Node left;
        Node right;
        
        Node(int n) {
            key = n;
            left = null;
            right = null;
        }
    }
    
    static Node createTree(int in[], int post[], int n) {
        if(n <= 0) {
            return null;
        }
        if(n == 1) {
            return new Node(in[0]);
        }
        
        int rootNode = post[n-1];
        Node root = new Node(rootNode);
        int i;
        for(i = 0; i < n; i++) {
            if(in[i] == rootNode) {
                break;
            }
        }
        
        int leftlen = i, rightlen = n-i-1;
        int leftin[] = new int[leftlen];
        int rightin[] = new int[rightlen];
        System.arraycopy(in,0,leftin,0,leftlen);
        System.arraycopy(in,leftlen+1,rightin,0,rightlen);
        
        int leftpost[] = new int[leftlen];
        int rightpost[] = new int[rightlen];
        System.arraycopy(post,0,leftpost,0,leftlen);
        System.arraycopy(post,leftlen,rightpost,0,rightlen);
        
        root.left = createTree(leftin,leftpost,leftlen);
        root.right = createTree(rightin,rightpost,rightlen);
        return root;
    }
    
    //Check left, if left has children, recursive left,
    //Check right, if right has children, recursive right,
    //If none, increase count by one.
    static int solution(Node node) {
        int numOfLeafNodes = 0;
        System.out.println(node.key);
        //Checking left, left has one
        if(node.left != null) {
            
            // Go down and see if it's a dead end or not
            numOfLeafNodes += solution(node.left);
        
        }
        // Checking right, right has one
        if(node.right != null) {
            
            // Go down and see if dead end or not
            numOfLeafNodes += solution(node.right);
        
        }
        
        if(node.left == null && node.right == null) {
            
            numOfLeafNodes += 1;
            
        }
        
        return numOfLeafNodes;
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        if(n == 0) {
            return;
        }
        int in[] = new int[n];
        int post[] = new int[n];
        for(int i = 0; i < n; i++) {
            post[i] = sc.nextInt();
        }
        for(int i = 0; i < n; i++) {
            in[i] = sc.nextInt();
        }
        Node root = createTree(in,post,n);
        int ans = solution(root);
        System.out.println(ans);
        sc.close();
    }
}
