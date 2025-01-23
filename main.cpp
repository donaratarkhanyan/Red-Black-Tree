#include "RBTree.h"

int main() {
    RBTree<int> tree;

    tree.insert(11);
    tree.insert(2);
    tree.insert(30);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);

    std::cout << "Preorder traversal: ";
    tree.preorder();

    // std::cout << "Inorder traversal: ";
    // tree.inorder();

    // std::cout << "Postorder traversal: ";
    // tree.postorder();

    // int searchValue = 25;
    // if (tree.search(searchValue)) {
    //     std::cout << "Value " << searchValue << " found in the tree." << std::endl;
    // } else {
    //     std::cout << "Value " << searchValue << " not found in the tree." << std::endl;
    // }

    // std::cout << "Size of Nodes: " << tree.getSize() << std::endl;

    // int blackHeight = tree.getBlackHeight(tree.getRoot());
    // std::cout << "Black height of the tree: " << blackHeight << std::endl;
    return 0;
}
