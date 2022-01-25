package quiz2makeup;

class MyBST {
	  private TreeNode root;

	  public void insert(int key) {
	    TreeNode newNode = new TreeNode(key);
	    if (root == null) {
	      root = newNode;
	    } else {
	      TreeNode current = root;
	      TreeNode parent;

	      while (true) {
	        parent = current;

	        if (key < current.getElement()) {
	          current = current.getLeft();
	          if (current == null) {
	            parent.setLeft(newNode);
	            return;
	          }
	        } else {
	          current = current.getRight();
	          if (current == null) {
	            parent.setRight(newNode);
	            return;
	          }
	        }
	      }
	    }
	  }

	  public int getSize() {
	    return getSize(root);
	  }

	  private int getSize(TreeNode root) {
	    if (root == null) {
	      return 0;
	    } else {
	      return getSize(root.getLeft()) + getSize(root.getRight()) + 1;
	    }
	  }

	  public TreeNode getRoot() {
	    return this.root;
	  }
	}

	class TreeNode {

	  private int element;
	  private TreeNode left;
	  private TreeNode right;

	  public TreeNode() {
	  }

	  public TreeNode(int e) {
	    this.element = e;
	  }

	  public int getElement() {
	    return element;
	  }

	  public TreeNode getLeft() {
	    return left;
	  }

	  public TreeNode getRight() {
	    return right;
	  }

	  public void setElement(int element) {
	    this.element = element;
	  }

	  public void setLeft(TreeNode left) {
	    this.left = left;
	  }

	  public void setRight(TreeNode right) {
	    this.right = right;
	  }

	}