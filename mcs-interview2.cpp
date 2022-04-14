void MorrisTraversalInorder(Node* root){
    if(!root)return;
    Node* curr= root, *prev;
    while(curr){

        if(!curr->left){
            //process curr
            curr = curr->right;
        }

        else {
            prev = curr->left;
            while(prev->right && prev->right != curr)
                prev=prev->right;

            if(!prev->right){
                prev->right = curr;
                curr=curr->left;
            }
            else {
                prev->right = nullptr;
                //process curr
                curr=curr->right;
            }
        }
    }
}


Node* copyList(Node* first){
    // prvo kopiramo listu
    Node* curr = first;
    Node* newFirst;
    while(curr){
        Node* newNode = new Node(curr->data);
        curr->next = newNode;
        curr=curr->next;
    }

    Node* curr1 = first, *curr2 = newFirst;
    while(first){

        Node* pom = curr1;
        curr1=curr1->next;

        pom->next = curr2;
        curr2->rand = pom->rand;

        curr2 = curr2->next;
    }

    Node* curr = newFirst;
    while(curr){
        curr->rand = curr->rand->next;

        curr=curr->next;
    }

    return newFirst;

}

//rotated sorted array
int binarySearch(int arr[], int low, int high, int key){
    if(high<low)
        return -1;
    
    int mid = (low+high)/2;
    if(key == arr[mid]) return mid;
    if(key>arr[mid]) return binarySearch(arr, mid+1, high, key);
    if(key<arr[mid]) return binarySearch(arr, low, mid-1, key);
}
int binarySearchIterative(int arr[], int n, int key){
    int low = 0, high = n - 1;
    while(low<=high){
        int mid = (low+high) / 2;

        if(key==arr[mid]) return mid;
        if(key>arr[mid]) low=mid+1;
        else if (key<arr[mid]) high = mid-1;
    }
    return -1;
}

int findPivot(int arr[], int low, int high){
    if(high<low) return -1;
    if(high==low) return low;

    int mid = (high+low) /2;
    if(arr[mid] > arr[mid+1])return mid;

    if(arr[low] >= arr[mid]) return findPivot(arr, low, mid-1);
    else return findPivot(arr, mid+1, high);
}

int pivotedBinarySearch(int arr[], int n, int key){

    int pivot = findPivot(arr,0, n-1);
    if(pivot==-1) return binarySearch(arr, 0, n-1, key);

    if(arr[pivot] == key) return pivot;
    if(arr[0] <= key) return binarySearch(arr, 0, pivot-1, key);
    return binarySearch(arr, pivot+1, n-1, key);
}


vector<int> intersection_arrays(vector<int> a, vector<int> b){
    vector<int> ret;
    int i = 0, j = 0;
    int an = a.size();
    int bn = b.size();
    while(i<an && j<bn){
        if(a[i] < b[j])
            i++;
        else if(a[i]>b[j])
            j++;
        else {
            ret.push_back(a[i]);
            i++;
            j++;

        }
    }

    return ret;
}

vector<int> intersection_trees(Node* root1, Node* root2){
    vector<int> ret;
    stack<Node*> stack1, s1, s2;

    while(true){
        if(root1){
            s1.push(root1);
            root1->left;
        }
        else if(root2){
            s2.push(root2);
            root2 = root2->left;
        }

        else if(!s1.empty() && !s2.empty()){
            root1 = s1.top();
            root2 = s2.top();

            if(root1->key == root2->key){
                ret.push_back(root1->key);
                s1.pop();s2.pop();
                root1=root1->right;
                root2=root2->right;
            }
            else if(root1->key < root2->key){
                s1.pop();
                root1=root1->right;
                root2 = nullptr;
            }
            else if(root1->key > root2->key){
                s2.pop();
                root2=root->right;
                root1=nullptr;
            }
        }
        else break;
    }
    return ret;
}