#include <iostream>
#include <stdlib.h>
using namespace std;

class Node { // Define a tree node class which contains an integer data value, and Node pointers for left and right children.
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node() { // No-argument constructor which initializes the node's value to 0, and both of its child pointers to null.
        data = 0;
        left = NULL;
        right = NULL;
        height = 1;
    }

    Node(int val) { // User-defined constructor which initializes the node's value to the one inputted. Child pointers are set to null.
        data = val;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

// Function Prototypes
void inorder(Node* currentPtr);
Node* insert(Node* root, Node* element);
int add(Node* currentPtr);
int find(Node* currentPtr, int val);
Node* parent(Node* root, Node* node);
Node* minVal(Node* root);
Node* maxVal(Node* root);
int isLeaf(Node* node);
int hasOnlyLeftChild(Node* node);
int hasOnlyRightChild(Node* node);
Node* findNode(Node* currentPtr, int value);
Node* deleteNode(Node* root, int value);
int menu();
void elementsBetween(Node* root, int x, int y);
int sumBetween(Node* root, int x, int y);
Node* Next(Node* root, int value);
int ComputeHeight(Node* node);
Node* RotateRight(Node* root, Node* X);
Node* RotateLeft(Node* root, Node* Y);
int ComputeBF(Node* node);
Node* Rebalance(Node* root, Node* node);
void AdjustHeight(Node* node);
Node* RebalanceRight(Node* root, Node* Z);
Node* RebalanceLeft(Node* root, Node* Z);
Node* LeftDescendant(Node* node);
Node* RightAncestor(Node* root, Node* node);
int isUnbalanced(Node* root);



void inorder(Node *currentPtr) { // Print an in-order traversal of the subtree rooted by the node passed to the function.
  if (currentPtr != NULL) { // Only attempt to traverse a node if it's not null.
      inorder(currentPtr->left); // Print an in-order traversal of the left subtree (Left)
    cout << " " << currentPtr->data; // Print the root of the current subtree. (Visit)
      inorder(currentPtr->right); // Print an in-order traversal of the right subtree (Right)
  }
}

Node* insert(Node *root, Node *element) { // Perform a basic insert (without auto-balancing functionality) of an element with a tree rooted by a given node.
  if (root == NULL) { // If the root is null, we are inserting into an empty tree. The root is the node we're inserting.
    return element;
  }
  else {
    if (element->data > root->data) { // If the value we're looking to insert is larger than the root, insert to the right.
      if (root->right != NULL) // If the root has nodes to the right, call the function again with the right subtree.
        root->right = insert(root->right, element);
      else // If the root does not have right children, insert the node there.
        root->right = element;
    }
    else { // If the value we're looking to insert is smaller than the root, insert to the left.
      if (root->left != NULL) // If the root has nodes to the left, call the function again with the left subtree.
        root->left = insert(root->left, element);
      else // If the root does not have left children, insert the node there.
        root->left = element;
    }
    AdjustHeight(root); // Adjust the height of the root.
    return root; // Return the root pointer of the updated tree.
  }
}


int add(Node *currentPtr) { // Add the values of all of the nodes in the subtree rooted by the node passed to the function.
  if (currentPtr != NULL) // Only attempt to add nodes if the tree is not empty.
    return currentPtr->data + add(currentPtr->left) + add(currentPtr->right); // Return the sum of the values in the left and right subtrees.
  else // If the tree is empty, the sum of the values in its nodes will always be 0. Return as such.
    return 0;
}


int find(Node *currentPtr, int val) { // Check if a node with a given value exists in the tree rooted by currentPtr.
  // Check if there are nodes in the tree.
  if (currentPtr != NULL) {
    // Found the value at the root.
    if (currentPtr->data == val)
      return 1;
    // Search to the left.
    if (val < currentPtr->data)
      return find(currentPtr->left, val);
    // Or search to the right.
    else
      return find(currentPtr->right, val);
  }
  else
    return 0;
}


Node* parent(Node *root, Node *node) { // Returns the parent of the node in the subtree rooted at root.
  if (root == NULL || root == node) // If the tree is empty, or the node we'd like the parent of is the root of our subtree, return null.
    return NULL;
  if (root->left == node || root->right == node) // If the root is the direct parent of the node, return a pointer to the root node.
    return root;
  if (node->data < root->data) // If the node's value is less than the root's, search for its parent in the left subtree.
    return parent(root->left, node);
  else if (node->data > root->data) // If the node's value is greater than the root's search for its parent in the right subtree.
    return parent(root->right, node);
  return NULL; // Return null for any other case.
}


Node* minVal(Node *root) { // Returns a pointer to the node storing the minimum value in the tree.
  if (root->left == NULL) // If the node we're checking has no left child, it is the node with the minimum value. Return it.
    return root;
  else // If the node we're checking has a left child, call the function again with that left child node. Eventually we will reach the minimum value.
    return minVal(root->left);
}


Node* maxVal(Node *root) { // Returns a pointer to the node storing the maximum value in the tree.
  if (root->right == NULL) // If the node we're checking has no right child, it is the node with the maximum value. Return it.
    return root;
  else // If the node we're checking has a right child, call the function again with that right child node. Eventually we will reach the maximum value.
    return maxVal(root->right);
}


int isLeaf(Node *node) { // Returns 1 if the node is a leaf node, and 0 otherwise.
  return (node->left == NULL && node->right == NULL); // Checks whether the node has any child nodes. If it does, return 0. If not, return 1.
}


int hasOnlyLeftChild(Node *node) { // Returns 1 if and only if the node has a left child and no right child (0 otherwise.)
  return (node->left != NULL && node->right == NULL); // Checks whether the node has a left child and no right child. If true, return 1. If not, return 0.
}


int hasOnlyRightChild(Node *node) { // Returns 1 if and only if the node has a right child and no left child (0 otherwise.)
  return (node->left == NULL && node->right != NULL);
}


Node* findNode(Node *currentPtr, int value) { // Returns a pointer to the node that stores the desired value in a given subtree.
  if (currentPtr != NULL) { // Only attempt to find a node if the tree is not empty.
    if (currentPtr->data == value) // If the root node of our subtree contains the value we're looking for, return a pointer to it.
      return currentPtr;
    if (value < currentPtr->data) // If the value is less than the one stored in the root, search for the value within the left subtree.
      return findNode(currentPtr->left, value);
    else // If the value is greater than the one stored in the root, search for the value within the right subtree.
      return findNode(currentPtr->right, value);
  }
  else // If the tree is empty, return null. There are no nodes to search!
    return NULL;
}


Node* deleteNode(Node* root, int value) { // Deletes the node containing a specified value in the tree rooted at root. Returns a pointer to the root of resulting tree. (Value to delete must be present in the tree in order for this function to work.)
  Node *delnode, *newDelNode, *saveNode;
  Node *par;
  int saveVal;
  
  delnode = findNode(root, value); // Set the delnode pointer to the node containing the value we wish to delete.
  par = parent(root, delnode); // Set the par pointer to the parent of the node we wish to delete.
  
  if (isLeaf(delnode)) { // Case 1: The node we're deleting is a leaf node (at the bottom of the tree.)
    if (par == NULL) { // If the node we're going to delete is the only one in the tree, delete it and return null, as there will be no remaining tree after deletion.
      delete root; // free the memory for the node.
      return NULL;
    }
    
    if (value < par->data) { // If the node we're going to delete is the left child of its parent, delete it accordingly.
      delete par->left;
      par->left = NULL;
    }
    else { // If the node we're going to delete is the right child of its parent, delete it accordingly.
      delete par->right; // Free the memory for the node.
      par->right = NULL;
    }
    return root; // Return the root of the new tree after performing either the left or right child deletion.
  }
  
  if (hasOnlyLeftChild(delnode)) { // Case 2: The node we're deleting only has a left child.
    if (par == NULL) { // If the node we're going to delete is the root of the tree, delete it, and set the new root to be the deleted node's left child.
      saveNode = delnode->left;
      delete delnode;
      return saveNode;
    }

    if (value < par->data) { // If the node we're going to delete is a left child, adjust its parent's child pointers accordingly, then perform deletion.
      saveNode = par->left; // Store the node we're going to delete in saveNode.
      par->left = par->left->left; // Update the parent node's left child pointer to reference the left child of the node that is about to be deleted.
      delete saveNode; // Free the memory for the deleted node.
    }
    else { // If the node we're going to delete is a right child, adjust its parent's child pointers accordingly, then perform deletion.
      saveNode = par->right; // Store the node we're going to delete in saveNode.
      par->right = par->right->left; // Update the parent node's right child pointer to reference the left child of the node that is about to be deleted.
      delete saveNode; // Free the memory for the deleted node.
    }
    return root; // Return the root of the new tree after performing either the left or right child deletion.
  }
  
  if (hasOnlyRightChild(delnode)) { // Case 3: The node we're deleting only has a right child.
    if (par == NULL) { // If the node we're going to delete is the root of the tree, delete it, and set the new root to be the deleted node's right child.
      saveNode = delnode->right;
      delete delnode;
      return saveNode;
    }
    
    if (value < par->data) { // If the node we're going to delete is a left child, adjust its parent's child pointers accordingly, then perform deletion.
      saveNode = par->left; // Store the node we're going to delete in saveNode.
      par->left = par->left->right; // Update the parent node's left child pointer to reference the right child of the node that is about to be deleted.
      delete saveNode; // Free the memory for the deleted node.
    }
    else { // If the node we're going to delete is a right child, adjust its parent's child pointers accordingly, then perform deletion.
      saveNode = par->right; // Store the node we're going to delete in saveNode.
      par->right = par->right->right; // Update the parent node's right child pointer to reference the right child of the node that is about to be deleted.
      delete saveNode; // Free the memory for the deleted node.
    }
    return root; // Return the root of the new tree after performing either the left or right child deletion.
  }
  
  // Case 4: The node we're deleting has two children. (In this case, we must locate a new physical node to delete.)
  newDelNode = minVal(delnode->right); // Set the new physical node we wish to delete to the node with the minimum value in the original node's right subtree.
  saveVal = newDelNode->data; // Save the value of the physical node we wish to delete. We don't wish to delete this value, only this node!
  deleteNode(root, saveVal);  // Now, delete the proper value.
  delnode->data = saveVal; // Restore the data to the original node to be deleted.
  return root; // Return the root of the new tree after performing the above operations.
}

int menu() { // Prints out a menu of choices for the user, returning their choice.
  int ans;
  cout << "Here are your choices." << endl;
  cout << "1. Insert an item into your tree." << endl;
  cout << "2. Delete an item from your tree." << endl;
  cout << "3. Search for an item in your tree." << endl;
  cout << "4. Print the sum of the nodes in your tree." << endl;
  cout << "5. Print the next element of the node with key x." << endl;
  cout << "6. Print the elements between x and y." << endl;
  cout << "7. Print the height of the tree with root x." << endl;
  cout << "8. Print the sum of the list of elements between x and y." << endl;
  cout << "9. Print out the tree in an in-order traversal." << endl;
  cout << "10. Exit." << endl;
  cout << endl;
  cout << "Please input your selection: ";
  cin >> ans;
  cout << endl;
  return ans;
}

Node* Next(Node* root, int value) { // Find the next element of the node with a given key.
  Node* tempNode = findNode(root, value); // First, we must find the node with the given value in the tree.
  if(tempNode != NULL) { // If the node with the given value exists in the tree, attempt find the next element.
    if(tempNode->right != NULL)
      return LeftDescendant(tempNode->right);
    else if (parent(root, findNode(root, value)) != NULL) // If the node does not have a right child but DOES have a parent, return its right ancestor.
      return RightAncestor(root, tempNode);
    else // If the node does not have a right child or a parent node, it is the largest node in the tree. There is no next node after it.
      return NULL;
  }
  else // If the node with the given value doesn't exist in the tree, return NULL.
    return NULL;
}

Node* AVLInsert(Node* root, int value) { // Insert value while maintaining tree balance.
  Node* tempNode = new Node(value); // Create a new temporary node with the given value.
  root = insert(root, tempNode); // Perform a normal BST insert using this node.
  tempNode = findNode(root, value); // Find the node in the tree after insertion.
  root = Rebalance(root, tempNode); // Rebalance the node we've just inserted.
  return root;
}

int ComputeHeight(Node* node) { // Compute the height of a given node.
  if(node == NULL)
    return 0;
  if(node->left == NULL && node->right == NULL) // If the node has no children, its height is 1.
    return 1;
  else if(node->left == NULL) // If the node does not have a left child, its height is 1 + the height of its right subtree.
    return 1 + ComputeHeight(node->right);
  else if(node->right == NULL) // If the node does not have a right child, its height is 1 + the height of its left subtree.
    return 1 + ComputeHeight(node->left);
  else // If the node has two children, its height is 1 + the maximum height between the heights of its left and right subtrees.
    return 1 + max(ComputeHeight(node->left), ComputeHeight(node->right));
}

Node* RotateRight(Node* root, Node* X) { // Perform a right rotation on a given node in a tree rooted by root.
  Node* P = parent(root, X); // Assign P to be the parent of the node we've passed to the function. If X is the root, P will be null.
  Node* Y = X->left;
  Node* B = Y->right;
  
  if(P != NULL) { // If X has a parent, set its appropriate child to Y rather than X.
    if(P->right == X)
      P->right = Y;
    if(P->left == X)
      P->left = Y;
  } else { // If X is the root of the original tree (or in other words, P is null,) set the new root of the tree to Y.
    root = Y;
  }

  // Drop down X by assigning Y's right child pointer to X.
  Y->right = X;

  X->left = B;
  
  return root; // Return the root of the updated tree.
}

Node* RotateLeft(Node* root, Node* Y) { // Perform a left rotation on a given node in a tree rooted by root.
  Node* P = parent(root, Y); // Assign P to be the parent of the node we've passed to the function. If Y is the root, P will be null.
  Node* X = Y->right;
  Node* B = X->left;

  // Drop down Y by setting X's child pointer to Y.
  X->left = Y;

  Y->right = B;
  
  if(P != NULL) { // If Y has a parent, set its appropriate child to X rather than Y.
    if(P->left == Y)
      P->left = X;
    if(P->right == Y)
      P->right = X;
  } else { // If Y is the root of the original tree (or in other words, P is null,) set the new root of the tree to X.
    root = X;
  }
  
  return root;
}

int ComputeBF(Node* node) { // Compute the balance factor for a given node.
  if(node != NULL)
    return ComputeHeight(node->left) - ComputeHeight(node->right); // A node's balance factor is the height of the left subtree - the height of the right subtree. An AVL tree node should always have a balance factor of -1, 0, or 1.
  else
    return -10; // If passed a null node, attempting to access the left and right pointers will cause a segmentation fault. Return -10 instead, indicating an error.
}

Node* Rebalance(Node* root, Node* node) { // Rebalance a given node in a tree rooted by root.
  Node* P = parent(root, node); // Assign P to be the parent of the node we've passed to the function. If the node we've passed is the root, P will be null.

  // Assign leftHeight and rightHeight using the ComputeHeight function.
  int leftHeight = (node == NULL) ? 0 : ComputeHeight(node->left);
  int rightHeight = (node == NULL) ? 0 : ComputeHeight(node->right);

  // If the node is unbalanced, perform necessary rotations.
  if(leftHeight > rightHeight + 1)
    root = RebalanceRight(root, node);
  if(rightHeight > leftHeight + 1)
    root = RebalanceLeft(root, node);

  AdjustHeight(node); // Adjust the node's height after potentially performing a rebalance.
  
  if(P != NULL) // If the node we've passed has a parent, check if that node needs a rebalance as well.
    root = Rebalance(root, P);
  
  return root; // Return the root of the updated tree.
}

void AdjustHeight(Node* node) { // Update the height value of a given node.
  node->height = ComputeHeight(node);
}

Node* RebalanceRight(Node* root, Node* Z) { // Perform a right rebalance on a given node in a tree rooted by root.
  Node* Y = Z->left;

  int leftHeight = (Y == NULL) ? 0 : ComputeHeight(Y->left);
  int rightHeight = (Y == NULL) ? 0 : ComputeHeight(Y->right);

  if(rightHeight > leftHeight) // Left Right Case
    root = RotateLeft(root, Y);
  
  root = RotateRight(root, Z); // Left Left Case
  return root;
}

Node* RebalanceLeft(Node* root, Node* Z) { // Perform a left rebalance on a given node in a tree rooted by root.
  Node* Y = Z->right;

  int leftHeight = (Y == NULL) ? 0 : ComputeHeight(Y->left);
  int rightHeight = (Y == NULL) ? 0 : ComputeHeight(Y->right);

  if(leftHeight > rightHeight) // Right Left Case
    root = RotateRight(root, Y);
  root = RotateLeft(root, Z); // Right Right Case
  
  return root;
}

Node* LeftDescendant(Node* node) { // Returns the left descendant of a given node.
  if(node->left == NULL) // If the node doesn't have a left child, it is the left descendant.
    return node;
  else // If the node has a left child, call the function again with the left child node until we reach a leaf.
    return LeftDescendant(node->left);
}

Node* RightAncestor(Node* root, Node* node) { // Returns the right ancestor of a given node.
  if(parent(root, node)) { // If the node has a parent, perform these operations.
    if(node->data < parent(root, node)->data) // If the current node's key is less than that of its parent, return its parent node.
      return parent(root, node);
    else // If the current node's key is greater than that of its parent, call the function again with its parent.
      return RightAncestor(root, parent(root, node));
  } else { // If the node does not have a parent, it cannot have an ancestor.
    return NULL;
  }
}

void elementsBetween(Node* root, int x, int y) { // Print the elements between x and y.
    if (root == NULL) {
      return;
    }
    if (x < root->data) {
      elementsBetween(root->left, x, y);
    }
    if (x <= root->data && y >= root->data) {
      cout << root->data << " ";
    }
    if (y > root->data) {
      elementsBetween(root->right, x, y);
    }
}

int sumBetween(Node* root, int x, int y) { // Print the sum of the list of values between x and y.
    if (root == NULL) {
      return 0;
    }
    if (root->data >= x && root->data <= y) {
      return root->data + sumBetween(root->left, x, y) + sumBetween(root->right, x, y);
    }
    else if (root->data < x) {
      return sumBetween(root->right, x, y);
    }
    else {
      return sumBetween(root->left, x, y);
    }
}

int isUnbalanced(Node* root) { // Check whether the tree rooted at root is unbalanced.
  if(abs(ComputeHeight(root->left) - ComputeHeight(root->right)) <= 1) // If the balance factor of the root is -1, 0, or 1, the tree is balanced.
    return 0;
  else // Otherwise, the tree is unbalanced.
    return 1;
}

Node* AVLDelete(Node* root, int value) {
  if (root == NULL) { // If the tree is empty, simply return the root passed to the function.
    return root;
  }
    
  if (value < root->data) { // If the value to be deleted is in the left subtree, call AVLDelete recursively on the left subtree.
    root->left = AVLDelete(root->left, value);
  }
  else if (value > root->data) { // If the value to be deleted is in the right subtree, call AVLDelete recursively on the right subtree.
    root->right = AVLDelete(root->right, value);
  }
  else {
    if(root->left == NULL && root->right == NULL) // If the root has no children, the tree is empty after this deletion. Simply set the root pointer to NULL.
      root = NULL;
    else if (root->left == NULL || root->right == NULL) { // If the root only has one child, enter this conditional.
      Node* tempNode = root->left ? root->left : root->right; // If the left subtree exists, assign tempNode to the left subtree. Otherwise, assign it to the right subtree.
            
      if (tempNode == NULL) { // If the root has no children, simply delete the root node. The tree will be empty after this deletion.
        tempNode = root;
        root = NULL;
      }
      else { // If there is a single subtree, assign the root to the root of that subtree.
        *root = *tempNode;
      }
      
      delete tempNode; // Free the memory used by tempNode, thus deleting the node.
    }
    else { // If the root is being deleted and it has children, we need to find the proper node to replace it with.
      Node* tempNode = minVal(root->right); // The node we should replace the root with is the minimum node of the right subtree.
      root->data = tempNode->data; // Reassign the root's value to be the one we are replacing it with.
      root->right = AVLDelete(root->right, tempNode->data); // Delete the node we've essentially replaced the root with.
    }
  }
    
  if (root == NULL) { // If the tree is empty after the above deletion, no rebalancing is needed. Return a null root pointer.
    return root;
  }

  // Perform proper tree rebalancing.
  if (ComputeBF(root) > 1 && ComputeBF(root->left) >= 0) { // Left Left Case.
    root = RotateRight(root, root->left); // Rotate the root of the left subtree right.
  }
  else if (ComputeBF(root) > 1 && ComputeBF(root->left) < 0) { // Left Right Case.
    root->left = RotateLeft(root->left, root->left->right); // Reassign the root's left child to the subtree after performing a left rotation on the left child's right subtree.
    root = RotateRight(root, root->left); // Rotate the root of the left subtree right.
  }
  else if (ComputeBF(root) < -1 && ComputeBF(root->right) <= 0) { // Right Right Case.
    root = RotateLeft(root, root->right); // Rotate the root of the right subtree left.
  }
  else if (ComputeBF(root) < -1 && ComputeBF(root->right) > 0) { // Right Left Case.
    root->right = RotateRight(root->right, root->right->left); // Reassign the root's right child to the subtree after performing a right rotation on the right child's left subtree.
    root = RotateLeft(root, root->right); // Rotate the root of the right subtree left.
  }
    
  AdjustHeight(root); // Adjust the height of the root after deletion.
    
  return root; // Return the root of the updated tree.
}


int main() {
    Node* myRoot = NULL, * tempNode;
    int done = 0, ans = 1, val = 0, val2 = 0;

    ans = menu(); // Get user input using menu() function.
    do { // Insert an item into the tree.
        if (ans == 1) { 
          cout << "Please enter the value you'd like to insert: ";
          cin >> val;
          cout << endl;
          if (find(myRoot, val))
            cout << "That node already exists in the tree." << endl;
          else {
            myRoot = AVLInsert(myRoot, val);
            cout << "Successfully inserted " << val << " into the tree." << endl;
          } 
          cout << endl;
        }
        else if (ans == 2) { // Delete an item from the tree.
          cout << "Please enter the value you'd like to delete: ";
          cin >> val;
          cout << endl;
          if (!find(myRoot, val))
            cout << "Sorry, that value isn't in the tree to delete." << endl;
          else {
            myRoot = AVLDelete(myRoot, val);
            cout << "Successfully deleted " << val << " from the tree." << endl;
          }
          cout << endl;
        }
        else if (ans == 3) { // Search for an item in the tree.
          cout << "Please enter the value you'd like to search for: ";
          cin >> val;
          cout << endl;
          if (find(myRoot, val))
            cout << "Found " << val << " in the tree." << endl;
          else
            cout << "Did not find " << val << " in the tree." << endl;
          cout << endl;
        }
        else if (ans == 4)  // Print the sum of the nodes in the tree.
          cout << "The sum of the nodes in your tree is " << add(myRoot) << "." << endl << endl;
        else if (ans == 5) { // Print the next element of the node with a given key.
          cout << "Please enter the element you'd like to find the next element of: "; // Get and store user input.
          cin >> val;
          cout << endl;
          if (find(myRoot, val)) {
            tempNode = Next(myRoot, val); // Call "Next()" with the given value, and store the next element it returns in tempNode.
            if (tempNode != NULL) // Output the next value, given that one exists.
              cout << "The next element of the tree after the node with the value " << val << " is " << tempNode->data << "." << endl;
            else // If the next value doesn't exist in the tree, output as such.
              cout << "There is no next node. " << val << " is the largest value in your tree." << endl;
          }
          else 
            cout << "A node with the value " << val << " does not exist in your tree." << endl;
          cout << endl;
        }
        else if (ans == 6) { // Print the elements between x and y.
          cout << "Please enter a minimum value for the range you'd like to print the elements of: ";
          cin >> val;
          cout << endl;
          cout << "Please enter a maximum value for the range you'd like to print the elements of: ";
          cin >> val2;
          cout << endl;
          cout << "List of values in your tree between " << val << " and " << val2 << ": ";
          elementsBetween(myRoot, val, val2); 
          cout << endl << endl;
        }
        else if (ans == 7) { // Print the height of the tree with root x.
          cout << "Please enter the value you'd like to find the height for: ";
          cin >> val;
          cout << endl;
          tempNode = findNode(myRoot, val);
          if(tempNode != NULL)
            cout << "The height of the node with the value " << val << " is " << ComputeHeight(tempNode) << "." << endl;
          else
            cout << "The value " << val << " is not in your tree. Its height is not retrievable." << endl;
          cout << endl;
        }
        else if (ans == 8) { // Print the sum of the list of values between x and y.
          cout << "Please enter a minimum value for the range you'd like to sum the elements of: ";
          cin >> val;
          cout << endl;
          cout << "Please enter a maximum value for the range you'd like to sum the elements of: ";
          cin >> val2;
          cout << endl;
          int sum = sumBetween(myRoot, val, val2);
          cout << "The sum of the values in your tree between " << val << " and " << val2 << " is: " << sum << endl << endl;
        }
        else if (ans == 9) { // Print out the tree in an in-order traversal.
          cout << "The values in your tree, in order, are:";
          inorder(myRoot);
          cout << endl << endl;
        }
        else if (ans == 10) { // Exit.
          break;
        }
        else { // Input entered was not in the list of options.
          cout << "Not a valid option. Your input must be an integer between 1 and 10." << endl << endl;
        }
        ans = menu(); // Prompt user for next entry.
    } while (ans != 10); // Repeat input until input is 10, which corresponds to "exit."

    cout << "Exited program." << endl;
    return 0;
}