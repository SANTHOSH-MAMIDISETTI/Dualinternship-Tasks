#include <iostream>

struct TreeNode 
{
    int data;
    TreeNode* left;
    TreeNode* right;
};

// Function to create a new tree node
TreeNode* createNode(int data) 
{
    TreeNode* newNode = new TreeNode();
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Function to insert a node in the binary tree
TreeNode* insertNode(TreeNode* root, int data) 
{
    if (root == nullptr) 
    {
        root = createNode(data);
    } 
    else if (data <= root->data) 
    {
        TreeNode* leftChild = insertNode(root->left, data);
        root->left = leftChild;
    } 
    else 
    {
        TreeNode* rightChild = insertNode(root->right, data);
        root->right = rightChild;
    }
    return root;
}

// Function to swap two tree nodes
void swapNodes(TreeNode* a, TreeNode* b) 
{
    TreeNode* temp = a;
    a = b;
    b = temp;
}

// Function to deallocate memory of a tree
void deallocateTree(TreeNode* root) 
{
    if (root == nullptr)
        return;

    deallocateTree(root->left);
    deallocateTree(root->right);
    delete root;
}

// Function to perform an in-order traversal of the tree
void inorderTraversal(TreeNode* root) 
{
    if (root == nullptr)
        return;

    inorderTraversal(root->left);
    std::cout << root->data << " ";
    inorderTraversal(root->right);
}

int main() 
{
    TreeNode* root = nullptr;
    root = insertNode(root, -10);
    // root = insertNode(root, -10);
    root = insertNode(root, 5);
    root = insertNode(root, 15);
    root = insertNode(root, 3);
    root = insertNode(root, 8);
    root = insertNode(root, 8100);

    std::cout << "In-order traversal of the binary tree: ";
    inorderTraversal(root);
    std::cout << std::endl;

    // Swapping two nodes (assuming they exist in the tree)
    TreeNode* node1 = root->left; // Node with data 5
    TreeNode* node2 = root->right; // Node with data 15
    swapNodes(node1, node2);

    std::cout << "In-order traversal after swapping nodes: ";
    inorderTraversal(root);
    std::cout << std::endl;

    deallocateTree(root);

    return 0;
}
