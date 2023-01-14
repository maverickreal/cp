class splayTree {
    class node {
    public:
        int key;
        node *left, *right, *parent;
        node(int nd){
            key=nd;
        }
    };
public:
    node *root;
    void leftRotate(node *x) {
        node *y = x->right;
        if (y) {
          x->right = y->left;
          if (y->left){
            y->left->parent = x;
          }
          y->parent = x->parent;
        }
        if (!x->parent){
          root = y;
        }
        else if (x == x->parent->left){
          x->parent->left = y;
        }
        else {
          x->parent->right = y;
        }
        if (y){
          y->left = x;
        }
        x->parent = y;
    }
    void rightRotate(node *x) {
        node *y = x->left;
        if (y) {
          x->left = y->right;
          if (y->right){
            y->right->parent = x;
          }
          y->parent = x->parent;
        }
        if (!x->parent){
          root = y;
        }
        else if (x == x->parent->left){
          x->parent->left = y;
        }
        else {
          x->parent->right = y;
        }
        if (y){
          y->right = x;
        }
        x->parent = y;
    }
    void splay(node *x) {
        while (x->parent){
          if (!x->parent->parent) {
            if (x->parent->left == x){ 
              rightRotate(x->parent);
            }
            else{
              leftRotate(x->parent);
            }
          }
          else if (x->parent->left == x && x->parent->parent->left == x->parent) {
            rightRotate(x->parent->parent);
            rightRotate(x->parent);  
          } else if (x->parent->right == x && x->parent->parent->right == x->parent) {
            leftRotate(x->parent->parent);
            leftRotate(x->parent);
          } 
          else if (x->parent->left == x && x->parent->parent->right == x->parent) {
            rightRotate(x->parent);
            leftRotate(x->parent);
          } 
          else {
            leftRotate(x->parent);
            rightRotate(x->parent);
          }
        }
    }
    node* find(int key) {
        node *z = root;
        while (z) {
          if (z->key < key) {
            z = z->right;
          }
          else if (key < z->key){
            z = z->left;
          }
          else {
            splay(z);
            return z;
          }
        }
        return nullptr;
    }
    void insert(int key) {
        node *z = root, *p = nullptr;
        while (z) {
          p = z;
          if (z->key < key) {
            z = z->right;
          }
          else {
            z = z->left;
          }
        }
        z = new node(key);
        z->parent = p;    
        if (!p) {
          root = z;
        }
        else if (p->key < z->key){
          p->right = z;
        }
        else {
          p->left = z;
        }
        splay(z);
    }
};