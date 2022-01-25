package quiz2makeup;

import java.util.Arrays;
import java.util.Scanner;

class DriverMain {
	public static TreeNode findClosestNode(TreeNode treeNode, int target) {
        TreeNode returnVal = treeNode;
        boolean isDeadEnd = false;
        // if target is less than node and tree has left subtree
            // recursively find Closest node that is either the current node or a node in the left subtree
            // return closest node
        
        if(target < treeNode.getElement()) {
            if(treeNode.getLeft() != null) {
                
                isDeadEnd = getIsDeadEnd(treeNode.getLeft());
                if(isDeadEnd == true) {
                    
                    returnVal = getClosestNode(treeNode, treeNode.getLeft(), target);
                }
                else {
                    returnVal = findClosestNode(treeNode.getLeft(), target);
                }
            }
            else {
            
                returnVal = treeNode;
            }
        }
        // else if target is greater than node and tree has right subtree
            // recursively find Closest node that is either the current node or a node in the right subtree
            // return closest node
        else if (target > treeNode.getElement()) {
            if(treeNode.getRight() != null) {
                
                isDeadEnd = getIsDeadEnd(treeNode.getRight());
                if(isDeadEnd == true) {
                    
                    returnVal = getClosestNode(treeNode, treeNode.getRight(), target);
                }
                else {
                    returnVal = findClosestNode(treeNode.getRight(), target);
                }
            }
            else {
                
                returnVal = treeNode;
            }
        }
        // else (if the node is equal to the target)
            // return node
        else {
            
            returnVal = treeNode;
        }
        
        return returnVal;
	}
    
    private static boolean getIsDeadEnd(TreeNode node1) {
        boolean returnVal = true;
        
        if(node1.getLeft() != null) {
            
            returnVal = false;
        }
        if (node1.getRight() != null) {
        
            returnVal = false;
        }
        return returnVal;
    }

	private static TreeNode getClosestNode(TreeNode node1, TreeNode node2, int target) {
        TreeNode smallest;
       // Determine smallest of the two elements and assign to smallest
        if(node1.getElement() - node2.getElement() > 0) {
        
            smallest = node2;
        } else {
        
            smallest = node1;
        }
        // If two elements are equal to each other in distance, use smallest
        if (Math.abs(target - node1.getElement()) == Math.abs(target - node2.getElement())) {
        
            return smallest;
        
        } // If not, see which one is closer in distance.
		else if (Math.abs(target - node1.getElement()) < Math.abs(target - node2.getElement())) {
			return node1;
		} else {
			return node2;
		}
	}

	public static void main(String args[]) {
		try (Scanner input = new Scanner(System.in)) {
			String str = input.nextLine();

			int[] arr = Arrays.stream(str.substring(0, str.length()).split("\\s")).map(String::trim)
					.mapToInt(Integer::parseInt).toArray();
			MyBST BSTree = new MyBST();
			for (int i = 0; i < arr.length; i++) {
				BSTree.insert(arr[i]);
			}
			// get the target
			int target = input.nextInt();
			int result = findClosestNode(BSTree.getRoot(), target).getElement();
			System.out.print(result);
		}
	}
}