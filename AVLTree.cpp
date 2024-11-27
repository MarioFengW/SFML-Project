#include "AVLTree.h"

using namespace std;
using namespace sf;

AVLTree::AVLTree(RenderWindow &window, Font &font) : window(window), font(font), root(nullptr) {}

int AVLTree::height(AVLNode *node)
{
    return node ? node->height : 0;
}

int AVLTree::getBalance(AVLNode *node)
{
    return node ? height(node->left) - height(node->right) : 0;
}

// Right rotation function
AVLNode *AVLTree::rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

// Left rotation function
AVLNode *AVLTree::leftRotate(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

// Function to insert a key into the AVL tree
AVLNode *AVLTree::insert(AVLNode *node, int key)
{
    // Perform the normal BST insertion
    if (!node)
        return new AVLNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Function to delete a key from the AVL tree
AVLNode *AVLTree::deleteNode(AVLNode *root, int key)
{
    // Perform the normal BST deletion
    if (!root)
        return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        // Node with only one child or no child
        if (!root->left || !root->right)
        {
            AVLNode *temp = root->left ? root->left : root->right;
            if (!temp)
            {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;
            delete temp;
        }
        else
        {
            AVLNode *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (!root)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

AVLNode *AVLTree::minValueNode(AVLNode *node)
{
    AVLNode *current = node;
    while (current->left)
        current = current->left;
    return current;
}

void AVLTree::insert(int key)
{
    root = insert(root, key);
}

void AVLTree::deleteKey(int key)
{
    root = deleteNode(root, key);
}

void AVLTree::drawNode(AVLNode *node, float x, float y, float xOffset)
{
    if (!node)
        return;

    CircleShape circle(20);
    circle.setFillColor(Color(173, 216, 230));
    circle.setPosition(x, y);
    window.draw(circle);

    Text text;
    text.setFont(font);
    text.setString(to_string(node->key));
    text.setCharacterSize(20);
    text.setFillColor(Color::Black);
    text.setPosition(x + 10, y + 10);
    window.draw(text);

    // Draw the left child
    if (node->left)
    {
        Vertex line[] = {
            Vertex(Vector2f(x + 20, y + 20)),
            Vertex(Vector2f(x - xOffset + 20, y + 80))};
        window.draw(line, 2, Lines);
        drawNode(node->left, x - xOffset, y + 80, xOffset / 2);
    }

    // Draw the right child
    if (node->right)
    {
        Vertex line[] = {
            Vertex(Vector2f(x + 20, y + 20)),
            Vertex(Vector2f(x + xOffset + 20, y + 80))};
        window.draw(line, 2, Lines);
        drawNode(node->right, x + xOffset, y + 80, xOffset / 2);
    }
}

void AVLTree::draw()
{
    drawNode(root, window.getSize().x / 2, 175, window.getSize().x / 4);
}

void AVLTree::reset()
{
    root = nullptr;
}