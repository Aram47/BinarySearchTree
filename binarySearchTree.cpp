#include "binarySearchTree.hpp"

template <typename T>
BST::Tree<T>::Tree() : m_root(nullptr){}

template <typename T>
BST::Tree<T>::~Tree()
{
    BST::Tree<T>::Clear();
}

// Էլեմենտի ավելացումը ծառի մեջ

template <typename T>
void BST::Tree<T>::Insert(const T& value)
{
    if (!m_root)
    {
        m_root = new Node();
        m_root->m_data = value;
        return;
    }
    BST::Tree<T>::privateInsert(value, m_root);
}

template <typename T>
void BST::Tree<T>::privateInsert(const T& value, Node* root)
{
    if (value == root->m_data) {
        return;
    } else if (value > root->m_data) {
        if (!(root->m_right)) {
            root->m_right = new Node();
            root->m_right->m_data = value;
            return;
        }
        BST::Tree<T>::privateInsert(value, root->m_right);
    } else if (value < root->m_data) {
        if (!(root->m_left)) {
            root->m_left = new Node();
            root->m_left->m_data = value;
            return;
        }
        BST::Tree<T>::privateInsert(value, root->m_left);
    }
}


// Էլեմենտի ջնջելը ծառի միջից

template <typename T>
void BST::Tree<T>::Delete(const T& value)
{
    if (!m_root)
        return;
    BST::Tree<T>::privateDelete(value, m_root);
}

template <typename T>
void BST::Tree<T>::privateDelete(const T& value, Node*& root)
{
    if (root) {
        if (value == root->m_data) {
            if (root->m_left && root->m_right) {
                T minValue = BST::Tree<T>::privateFindMin(root->m_left);
                root->m_data = minValue;
                BST::Tree<T>::privateDelete(minValue, root->m_left);
            } else {
                Node* temp = root;
                root = (root->m_left) ? root->m_left : root->m_right;
                delete temp;
            }
        } else if (value > root->m_data) {
            BST::Tree<T>::privateDelete(value, root->m_right);
        } else if (value < root->m_data) {
            BST::Tree<T>::privateDelete(value, root->m_left);
        }
    }
}

//  Էլեմենտի որոնումը ծառի մեջ

template <typename T>
bool BST::Tree<T>::Search(const T& value) const
{
    return Tree<T>::privateSearch(value, m_root);
}

template <typename T>
bool BST::Tree<T>::privateSearch(const T& value, Node* root) const
{
    if (root)
    {
        if (value == root->m_data)
            return true;
        else if (value > root->m_data) {
            if (!(root->m_right))
                return false;
            return BST::Tree<T>::privateSearch(value, root->m_right);
        } else if (value < root->m_data) {
            if (!(root->m_left))
                return false;
            return BST::Tree<T>::privateSearch(value, root->m_left);
        }
    }
    return false;
}

// Տպում է ձախից աջ

template <typename T>
void BST::Tree<T>::Inorder()
{
    BST::Tree<T>::privateInorder(m_root);
}

template <typename T>
void BST::Tree<T>::privateInorder(Node* root)
{
    if (root) {
        BST::Tree<T>::privateInorder(root->m_left);
        std::cout << root->m_data << " ";
        BST::Tree<T>::privateInorder(root->m_right);
    }
}

// Տպում է մեջտեղինը, ձախինը հետո նոր աջինը

template <typename T>
void BST::Tree<T>::Preorder()
{
    BST::Tree<T>::privatePreorder(m_root);
}

template <typename T>
void BST::Tree<T>::privatePreorder(Node* root)
{
    if (root) {
        std::cout << root->m_data << " ";
        BST::Tree<T>::privatePreorder(root->m_left);
        BST::Tree<T>::privatePreorder(root->m_right);
    }
}

// տպում է ձախինը, աջինը հետո կենտրոնինը

template <typename T>
void BST::Tree<T>::Postorder()
{
    BST::Tree<T>::privatePostorder(m_root);
}

template <typename T>
void BST::Tree<T>::privatePostorder(Node* root)
{
    if (root) {
        BST::Tree<T>::privatePostorder(root->m_left);
        BST::Tree<T>::privatePostorder(root->m_right);
        std::cout << root->m_data << " ";
    }
}

// գտնում և վերադարձնում է փոքրագույնը

template <typename T>
T BST::Tree<T>::FindMin() const
{
    if (!m_root)
    {
        std::cout << "Have not Nods " << std::endl;
        return 0;
    }
    return BST::Tree<T>::privateFindMin(m_root);
}

template <typename T>
T BST::Tree<T>::privateFindMin(Node* root) const
{
    if (!(root->m_left))
        return root->m_data;
    return BST::Tree<T>::privateFindMin(root->m_left);
}

// գտնում և վերադարձնում է մեծագույնը

template <typename T>
T BST::Tree<T>::FindMax() const
{
    if (!m_root)
    {
        std::cout << "Have not Nods " << std::endl;
        return 0;
    }
    return BST::Tree<T>::privateFindMax(m_root);
}

template <typename T>
T BST::Tree<T>::privateFindMax(Node* root) const
{
    if (!(root->m_right))
        return root->m_data;
    return BST::Tree<T>::privateFindMax(root->m_right);
}

// խոսքերն ավելորդ են ես դեմք եմ չկա իմ նմանը 

template <typename T>
T BST::Tree<T>::Successor(const T& value) const
{
    if (!(BST::Tree<T>::Search(value)))
        throw std::invalid_argument("Invalid Argument ");
    return BST::Tree<T>::privateSuccessor(value, m_root);
}

template <typename T>
T BST::Tree<T>::privateSuccessor(const T& value, Node* root) const
{
    if (value == root->m_data) {
        if (!(root->m_right))
            throw std::invalid_argument("Invalid Argument ");
        else if (root->m_right->m_left)
            return BST::Tree<T>::privateFindMin(root->m_right);
        else 
            return root->m_right->m_data;
    } else if (value > root->m_data)
            return BST::Tree<T>::privateSuccessor(value, root->m_right);
    else
            return BST::Tree<T>::privateSuccessor(value, root->m_left);

    throw std::invalid_argument("No Argument ");
}

// Էն որ վապշե դեմք եմ էլի 

template <typename T>
T BST::Tree<T>::Predecessor(const T& value) const
{
    if (!(BST::Tree<T>::Search(value)))
        throw std::invalid_argument("Invalid Argument ");
    return BST::Tree<T>::privatePredecessor(value, m_root);
}

template <typename T>
T BST::Tree<T>::privatePredecessor(const T& value, Node* root) const
{
    if (root->m_data == value) {
        if (!(root->m_left))
            throw std::invalid_argument("Invalid Argument ");
        else if (root->m_left->m_right)
            return BST::Tree<T>::privateFindMax(root->m_left);
        else 
            return root->m_left->m_data;
    }

    T tmp_f = value + 1;
    while (root) {
        if (root->m_data == value) {
            if (!(root->m_left))
                    return tmp_f;
            else if (!(root->m_left->m_right))
                if ((root->m_left->m_data > tmp_f))
                    return root->m_left->m_data;
            else
                return BST::Tree<T>::privateFindMax(root->m_left);
        } else if (root->m_data > value)
            root = root->m_left;
        else if (root->m_data < value) {
            tmp_f = root->m_data;
            root = root->m_right;
        }
    }
    throw std::invalid_argument("Invalid Argument ");
}

//  Վերադարձնում է ծառի խորությունը

template <typename T> 
unsigned long BST::Tree<T>::Height() const
{
    return BST::Tree<T>::privateHeight(m_root);
}

template <typename T>
unsigned long BST::Tree<T>::privateHeight(Node* root) const
{
    if (!root)
        return 0;
    else {
        int left_height = BST::Tree<T>::privateHeight(root->m_left);
        int right_height = BST::Tree<T>::privateHeight(root->m_right);
        if (left_height >= right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}

// Վերադարձնում է նոդերի քանակը

template <typename T>
unsigned long BST::Tree<T>::Size() const
{
    return BST::Tree<T>::privateSize(m_root) - 1;
}

template <typename T>
unsigned long BST::Tree<T>::privateSize(Node* root) const
{
    if (!root)
        return 1;
    else
        return BST::Tree<T>::privateSize(root->m_left) + Tree<T>::privateSize(root->m_right);
}

// Ստուգում է թե ծառը հավասարապես և ճիշտ է բացվում թե ոչ

template <typename T>
bool BST::Tree<T>::IsValidBST() const
{
    if (!m_root)
        return 0;
    return BST::Tree<T>::privateIsValidBST(m_root);
}

template <typename T>
bool BST::Tree<T>::privateIsValidBST(Node* root) const
{
    if (!root->m_left && !root->m_right)
        return 1;
    else if ((!root->m_left && root->m_right) || (root->m_left && !root->m_right))
        return 0;
    return BST::Tree<T>::privateIsValidBST(root->m_right) == Tree<T>::privateIsValidBST(root->m_left);
}

// Հարկ առ հարկ տպում է տվյալ հարկերի պարունակությունները

template <typename T>
void BST::Tree<T>::LevlOrder()
{
    if (!m_root)
        return;
    unsigned long height = BST::Tree<T>::Height();
    for (unsigned long level = 1; level <= height; ++level)
        BST::Tree<T>::privateLevlOrder(m_root, level);
}

template <typename T>
void BST::Tree<T>::privateLevlOrder(Node* root, unsigned long level)
{
    if (!root)
        return;
    if (level == 1)
        std::cout << root->m_data << " ";
    else if (level > 1) {
        BST::Tree<T>::privateLevlOrder(root->m_left, level - 1);
        BST::Tree<T>::privateLevlOrder(root->m_right, level - 1);
    }
}

// Ջնջում է ծառի ամբողջ պարունակությունը

template <typename T>
void BST::Tree<T>::Clear()
{
    if (!m_root)
        return;
    while (m_root)
        BST::Tree<T>::Delete(m_root->m_data);
}

// Վերադարձնում է ծառը միաչափ զանգվածի տեսքով

template <typename T>
T* BST::Tree<T>::Serialize() const
{
    if (!m_root)
        return nullptr;

    T* ptr = new T[BST::Tree<T>::Size()];
    static unsigned long i = 0;
    BST::Tree<T>::privateSerialize(m_root, ptr , i);
    i = 0;
    return ptr;
}

template <typename T>
void BST::Tree<T>::privateSerialize(Node* root, T*& arrResult,unsigned long& index) const
{
    if (root) {
        arrResult[index++] = root->m_data;
        BST::Tree<T>::privateSerialize(root->m_left, arrResult, index);
        BST::Tree<T>::privateSerialize(root->m_right, arrResult, index);
    }
}

// Ջնջում ա մի էլեմենտը ներմուծում մյուսը

template <typename T>
void BST::Tree<T>::Update(const T& oldValue, const T& newValue)
{
    if (!(BST::Tree<T>::Search(oldValue)))
        return;
    BST::Tree<T>::Delete(oldValue);
    BST::Tree<T>::Insert(newValue);
}

// Ստեղծում է նոր օբյեկտ քոփի անում պարունակությունը նորի մեջ և վերադարձնում նոր օբյոկտը

template <typename T>
BST::Tree<T> BST::Tree<T>::Copy() const
{
    if (!m_root)
        throw std::invalid_argument("Tree is empty ");

    T* ptr = BST::Tree<T>::Serialize();
    unsigned long size = BST::Tree<T>::Size();

    BST::Tree<T> obj;

    for (int i = 0; i < size; ++i)
        obj.Insert(ptr[i]);

    delete ptr;
    return obj;
}

// K-րդ փոքռագույն էլեմենտը

template <typename T>
T BST::Tree<T>::KthSmallest(unsigned long K) const
{
    if (K > BST::Tree<T>::Size() || K < 0)
        throw std::invalid_argument("Element is not valide ");
    T* ptr = BST::Tree<T>::Serialize();
    unsigned long size = BST::Tree<T>::Size();

    for (unsigned long i = 0; i < size; ++i) {
        for (unsigned long j = i + 1; j < size; ++j) {
            if (ptr[i] > ptr[j]) {
                T tmp = ptr[i];
                ptr[i] = ptr[j];
                ptr[j] = tmp;
            }
        }
    }

    for (unsigned long i = 0; i < size; ++i)
        if (i == (K - 1))
            return ptr[i];
    throw std::invalid_argument("Element is not valide ");
}

// K֊րդ մեծագույն էլեմենտը

template <typename T>
T BST::Tree<T>::KthLargest(unsigned long K) const
{
    if (K > BST::Tree<T>::Size() || K < 0)
        throw std::invalid_argument("Element is not valide ");
    T* ptr = BST::Tree<T>::Serialize();
    unsigned long size = BST::Tree<T>::Size();

    for (unsigned long i = 0; i < size; ++i) {
        for (unsigned long j = i + 1; j < size; ++j) {
            if (ptr[i] > ptr[j]) {
                T tmp = ptr[i];
                ptr[i] = ptr[j];
                ptr[j] = tmp;
            }
        }
    }

    for (unsigned long i = size; i >= size - K; --i)
        if ((i == size - K))
            return ptr[i];
    throw std::invalid_argument("Element is not valide ");
}

//-----------֊֊֊֊֊֊֊֊֊֊֊֊֊֊֊֊֊֊-------------------------------------------------

template <typename T>
void BST::Tree<T>::RangeQuery(const T& start,const T& end)
{
    if (start == end)
        std::cout << "Invalide Arguments " << std::endl;
    if (start > end) {
        T temp = start;
        start = end;
        end = temp;
    }
    
    T* TreeArr = BST::Tree<T>::Serialize();
    unsigned long size = BST::Tree<T>::Size();
    for (unsigned long i = 0; i < size; ++i) {
        for (unsigned long j = i + 1; j < size; ++j) {
            if (TreeArr[i] > TreeArr[j]) {
                T tmp = TreeArr[i];
                TreeArr[i] = TreeArr[j];
                TreeArr[j] = tmp;
            }
        }
    }
    for (unsigned long i = 0; i < size; ++i)
        if (TreeArr[i] >= start && TreeArr[i] <= end)
            std::cout << TreeArr[i] << " ";
}

