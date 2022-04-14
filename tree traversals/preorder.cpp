void preorderIterative(Node* root)
{
     if (root == nullptr) {
        return;
    }
 
    // create an empty stack and push the root node
    stack<Node*> stack;
    stack.push(root);
 
    // start from the root node (set current node to the root node)
    Node* curr = root;
 
    // loop till stack is empty
    while (!stack.empty())
    {
        // if the current node exists, print it and push its right child
        // to the stack before moving to its left child
        if (curr != nullptr)
        {
            cout << curr->data << " ";
 
            if (curr->right) {
                stack.push(curr->right);
            }
 
            curr = curr->left;
        }
        // if the current node is null, pop a node from the stack
        // set the current node to the popped node
        else {
            curr = stack.top();
            stack.pop();
        }
    }
}