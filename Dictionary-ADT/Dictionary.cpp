/*********************************************************************************
 * Raymond Huang, rhuang43
 * 2022 Spring CSE101 PA6
 * Dictionary.cpp
 * Source file for Dictionary ADT
 *********************************************************************************/
#include <iostream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"
using namespace std;

Dictionary::Node::Node(keyType k, valType x)
{
    key = k;
    val = x;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}
// Creates new Dictionary in the empty state.
Dictionary::Dictionary()
{
    nil = new Node("", -1);
    root = nil;
    current = nil;
    num_pairs = 0;
    root->parent = nil;
    root->left = nil;
    root->right = nil;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary &D)
{
    nil = new Node("", -1);
    root = nil;
    current = nil;
    num_pairs = 0;
    root->parent = nil;
    root->left = nil;
    root->right = nil;
    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary()
{
    clear();
    delete nil;
}
// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string &s, Node *R) const
{
    // below is the pseudo code provided
    // InOrderTreeWalk(x)
    //    if x != NIL
    //       InOrderTreeWalk(x.left)
    //       print(x.key)
    //       InOrderTreeWalk(x.right)
    if (R != nil)
    {
        inOrderString(s, R->left);
        s.append(R->key );
        s.append(" : ");
        s.append(std::to_string(R->val));
        s.append("\n");
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string &s, Node *R) const
{
    // below is the pseudocode provided
    // PreOrderTreeWalk(x)
    //    if x != NIL
    //       print(x.key)
    //       PreOrderTreeWalk(x.left)
    //       PreOrderTreeWalk(x.right)
    if (R != nil)
    {
        s.append(R->key);
        s.append("\n");
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node *R, Node *N)
{
    if (R != N)
    {
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node *R)
{
    // checks if something is on the left
    if (R != nil)
    {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        if (R == root)
        {
            root = nil;
        }
        if(R == current){
            current = nil;
        }
        num_pairs -= 1;
        delete R;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node *Dictionary::search(Node *R, keyType k) const
{
    // below is the pseudocode provided
    // TreeSearch(x, k)
    //    if x == NIL or k == x.key
    //       return x
    //    else if k < x.key
    //       return TreeSearch(x.left, k)
    //    else // k > x.key
    //       return TreeSearch(x.right, k)
    if (R == nil || R->key == k)
    {
        return R;
    }
    else if (R->key < k)
    {
        return search(R->right, k);
    }
    else
    {
        return search(R->left, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMin(Node *R)
{
    // below is the pseudocode provided
    //  TreeMinimum(x) Pre: x != NIL
    //    while x.left != NIL
    //       x = x.left
    //    return x
    while (R->left != nil)
    {
        R = R->left;
    }
    return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMax(Node *R)
{
    // below is the pseudocode provided
    //  TreeMaximum(x) Pre: x != NIL
    //    while x.right != NIL
    //       x = x.right
    //    return x
    while (R->right != nil)
    {
        R = R->right;
    }
    return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost
// Node, or is nil, returns nil.
Dictionary::Node *Dictionary::findNext(Node *N)
{
    if (N == nil)
    {
        return N;
    }
    else if (N->right != nil)
    {
        return findMin(N->right);
    }
    else
    {
        Node *Holder = N->parent;
        while (N == Holder->right && Holder != nil)
        {
            N = Holder;
            Holder = Holder->parent;
        }
        return Holder;
    }
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost
// Node, or is nil, returns nil.
Dictionary::Node *Dictionary::findPrev(Node *N)
{
    if (N->left != nil)
    {
        return findMin(N->left);
    }
    else if (N == nil)
    {
        return N;
    }
    else
    {
        Node *Holder = N->parent;
        while (N == Holder->left && Holder != nil)
        {
            N= Holder;
            Holder = Holder->parent;
        }
        return Holder;
    }
}
// changes nodes
// transplant()
void Dictionary::Transplant(Node *U, Node *V)
{
    // below is the pseudo code provided
    // Transplant(T, u, v)
    //    if u.parent == NIL
    //       T.root = v
    //    else if u == u.parent.left
    //       u.parent.left = v
    //    else
    //       u.parent.right = v
    //    if v != NIL
    //       v.parent = u.parent
    if (U->parent == nil)
    {
        root = V;
    }
    else if (U == U->parent->left)
    {
        U->parent->left = V;
    }
    else
    {
        U->parent->right = V;
    }
    if (V != nil)
    {
        V->parent = U->parent;
    }
}
// deletes nodes
void Dictionary::DDelete(Node *z)
{

    // below is the psuedocode provided
    // Delete(T, z)
    //    if z.left == NIL               // case 1  or case 2.1 (right only)
    //       Transplant(T, z, z.right)
    //    else if z.right == NIL         // case 2.2 (left only)
    //       Transplant(T, z, z.left)
    //    else                           // case 3
    //       y = TreeMinimum(z.right)
    //       if y.parent != z
    //          Transplant(T, y, y.right)
    //          y.right = z.right
    //          y.right.parent = y
    //       Transplant(T, z, y)
    //       y.left = z.left
    //       y.left.parent = y
    if (z->left == nil)
    {
        Transplant(z, z->right);
    }
    else if (z->right == nil)
    {
        Transplant(z, z->left);
    }
    else
    {
        Node *y = findMin(z->right);
        if (y->parent != z)
        {
            Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}
//  Access functions --------------------------------------------------------

// Returns the size of this Dictionary.
int Dictionary::size() const
{
    return num_pairs;
}
// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const
{
    if (search(root, k) != nil)
    {
        return true;
    }
    return false;
}
// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType &Dictionary::getValue(keyType k) const
{
    Node *Holder = search(root, k);
    if (Holder == nil)
    {
        throw std::logic_error("Dictionary ERROR: getVal");
        exit(EXIT_FAILURE);
    }
    return Holder->val;
}
// hasCurrent()
// Returns true if the current iterator is defined, and returns false
// otherwise.
bool Dictionary::hasCurrent() const
{
    if (current == nil)
    {
        return false;
    }
    return true;
}
// currentKey()
// Returns the current key.
// Pre: hasCurrent()
keyType Dictionary::currentKey() const
{
    if (hasCurrent() == false)
    {
        throw std::logic_error("Dictionary ERROR: currentKey");
        exit(EXIT_FAILURE);
    }
    return current->key;
}
// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType &Dictionary::currentVal() const
{
    if (hasCurrent() == false)
    {
        throw std::logic_error("Dictionary ERROR: currentVal");
        exit(EXIT_FAILURE);
    }
    return current->val;
}
// Manipulation procedures -------------------------------------------------

// clear()
//  Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear()
{
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}
// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v,
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v)
{
    // below is the pseudocode provided
    //  TreeInsert(T, z)
    //    y = NIL
    //    x = T.root
    //    while x != NIL
    //       y = x
    //       if z.key < x.key
    //          x = x.left
    //       else
    //          x = x.right
    //    z.parent = y
    //    if y == NIL
    //       T.root = z    // tree T was empty
    //    else if z.key < y.key
    //       y.left = z
    //    else
    //       y.right = z
    Node *Holder = new Node(k, v);
    Node *r = root;
    Node *n = nil;
    Holder->right = nil;
    Holder->left = nil;
    while (r != nil)
    {
        n = r;
        if (Holder->key < r->key)
        {
            r = r->left;
        }
        else
        {
            r = r->right;
        }
    }
    Holder->parent = n;
    if (n == nil)
    {
        num_pairs += 1;
        root = Holder;
    }
    else if (Holder->key < n->key)
    {
        n->left = Holder;
        num_pairs += 1;
    }
    else if (Holder->key > n->key)
    {
        n->right = Holder;
        num_pairs += 1;
    }
    else
    {
        n->val = v;
        delete Holder;
    }
}
// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k)
{
    Node *Holder = search(root, k);
    if (Holder == current)
    {
        current = nil;
    }
    if (Holder != nil)
    {
        DDelete(Holder);
    }
    delete Holder;
    num_pairs -= 1;
}
// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin()
{
    if (root != nil)
    {
        current = findMin(root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end()
{
    if (root != nil)
    {
        current = findMax(root);
    }
}

// next()
// If the current iterator is not at the last pair, advances current
// to the next pair (as defined by the order operator < on keys). If
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next()
{
    // Node *Holder = current;
    // end();
    // if (Holder == current)
    // {
    //     current = nil;
    // }
    // else
    if (hasCurrent())
    {
        current = findNext(current);
        // current = Holder;
    }
    else
    {
        throw std::logic_error("Dictionary ERROR: next");
        exit(EXIT_FAILURE);
    }
    // delete Holder;
}

// prev()
// If the current iterator is not at the first pair, moves current to
// the previous pair (as defined by the order operator < on keys). If
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev()
{
    // Node *Holder = current;
    // begin();
    // if (Holder == current)
    // {
    //     current = nil;
    // }
    // else
    if (hasCurrent())
    {
        current = findPrev(current);
    }
    else
    {
        throw std::logic_error("Dictionary ERROR: prev");
        exit(EXIT_FAILURE);
    }
    // delete Holder;
}
// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value
// are separated by the sequence space-colon-space " : ". The pairs are arranged
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const
{
    std::string Holder = "";
    inOrderString(Holder, root);
    return Holder;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const
{
    std::string Holder = "";
    preOrderString(Holder, root);
    return Holder;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary &D) const
{
    std::string Holder = "";
    std::string Hold = "";
    inOrderString(Holder, this->root);
    D.inOrderString(Hold, D.root);
    if (Holder == Hold)
    {
        return true;
    }
    return false; // returning false because return statement in if return doo doo
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream &operator<<(std::ostream &stream, Dictionary &D)
{
    return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals().
bool operator==(const Dictionary &A, const Dictionary &B)
{
    if (A.equals(B))
    {
        return true;
    }
    return false;
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary &Dictionary::operator=(const Dictionary &D)
{
    if (&D != this)
    {
        Dictionary Holder = D;
        std::swap(current, Holder.current);
        std::swap(root, Holder.root);
        std::swap(nil, Holder.nil);
        std::swap(num_pairs, Holder.num_pairs);
    }
    return *this;
}
