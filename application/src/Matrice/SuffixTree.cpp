#include "../../include/SuffixTree.hpp"

SuffixTree::SuffixTree () {
    sentence = "";
    root = nullptr;
    lastNewNode = nullptr;
    ActivePoint activePoint;
    remainder = 0;
    end = 0;
    rootEnd = nullptr;
    splitEnd = nullptr;
    size = 0;
}

SuffixTree::SuffixTree (string text) {
    sentence = text;
    root = nullptr;
    lastNewNode = nullptr;
    ActivePoint activePoint;
    remainder = 0;
    end = 0;
    rootEnd = nullptr;
    splitEnd = nullptr;
    size = 0;
}

/**
 * getRoot
 * @brief root node getter
 */
Node* SuffixTree::getRoot() {
    return this->root;
}

/**
 * setSentence
 * @brief sentence setter
 * @param {string} text - string used to set sentence
 */
void SuffixTree::setSentence(string text) {
    this->sentence = text;
}

/**
 * setActivePoint
 * @brief activePoint setter
 * @param {Node*} node - node used to set activeNode
 * @param {int} edge - edge used to set activeEdge
 * @param {int} length - length used to set activeLength
 */
void SuffixTree::setActivePoint(Node *node, int edge, int length) {
    this->activePoint.activeNode = node;
    this->activePoint.activeEdge = edge;
    this->activePoint.activeLength = length;
}

/**
 * createNewNode
 * @brief Create a new node for the suffix tree.
 * @param {int} start - starting index of the node in the suffix tree.
 * @param {end} end - end index of the node in the suffix tree.
 * @return {Node*} Newly created Node.
 */
Node* SuffixTree::createNewNode(int start, int *end) {
    Node *node = new Node();
    for (int i(0); i < MAXCHARS; i++) {
        node->children[i] = nullptr;
    }
    node->suffixLink = nullptr;
    node->start = start;
    node->end = end;
    node->suffixIndex = -1;

    return node;
}

/**
 * getEdgeLength
 * @brief Compute edge length of a node
 * @param {Node*} node - A node of the suffix tree.
 * @return {int} Edge length of a node.
 */
int SuffixTree::getEdgeLength(Node* node) {
    return *(node->end) - node->start + 1;
}

/**
 * @method walkDown
 * @brief Going down through suffix tree branch
 * If activeLength is greater than current node edge, we can walk down the tree branc,
 * update activePoint attributes, activeNode, activeLength and activeEdge,
 * to go to next node of the tree.
 * @param {Node*} currNode
 * @return {bool} True if walk down the tree, false if done nothing.
 */
bool SuffixTree::walkDown(Node *currNode) {
    if (this->activePoint.activeLength >= getEdgeLength(currNode)) {
        this->activePoint.activeEdge += getEdgeLength(currNode);
        this->activePoint.activeLength -= getEdgeLength(currNode);
        this->activePoint.activeNode = currNode;
        return true;
    }

    return false;
}

/**
 * @method extendSuffixTree
 * @brief Implementation of Ukkonen algorithm to construct a simple suffix array.
 * Implementation updated to handle non-constant alphabet (construction in O(nLogn).
 * @param {int} pos - current position in the string processed
 * @param {string} sentence - string processed
 */
void SuffixTree::extendSuffixTree(int pos, string sentence) {
    end = pos; // End leaf index
    remainder++; // Need to insert + 1 suffix.
    lastNewNode = nullptr;

    while (remainder > 0) { // While suffix to insert > 0
        // Active length zero. Active edge value set to caractere currently processed.
        // Case with one ( and last ) suffix to process or insert.
        if (activePoint.activeLength == 0)
            activePoint.activeEdge = pos;

        // If no child for active caractere, create a child.
        if (activePoint.activeNode->children[sentence[activePoint.activeEdge]] == nullptr) {
            activePoint.activeNode->children[sentence[activePoint.activeEdge]] = createNewNode(pos, &end);
            if (lastNewNode != nullptr) {
                lastNewNode->suffixLink = activePoint.activeNode;
                lastNewNode = nullptr;
            }
        } else { // Process occur in currently selected edge.
            Node *next = activePoint.activeNode->children[sentence[activePoint.activeEdge]];
            if (walkDown(next)) {
                continue; // Restart from next active node.
            }

            // String caractere currently processed is already into the tree.
            if (sentence[next->start + activePoint.activeLength] == sentence[pos]) {
                if (lastNewNode != nullptr && activePoint.activeNode != root) {
                    lastNewNode->suffixLink = activePoint.activeNode;
                    lastNewNode = nullptr;
                }
                // Caractere from string matched on path represented by ActivePoint.
                // Increase activeLength by 1 to represente this matching.
                activePoint.activeLength++;
                break;
            }

            // Processing into an edge of a tree with new caractere.
            // Adding new intermediate node to the branch.
            // Compute interne node end index.
            splitEnd = new int();
            *splitEnd = next->start + activePoint.activeLength - 1;
            // Create splitting node.
            Node *split = createNewNode(next->start, splitEnd);
            activePoint.activeNode->children[sentence[activePoint.activeEdge]] = split;
            // Add branch for current caractere.
            split->children[sentence[pos]] = createNewNode(pos, &end);
            // Add branch for  substring of the past edge.
            next->start += activePoint.activeLength;
            split->children[sentence[next->start]] = next;

            if (lastNewNode != nullptr) {
                lastNewNode->suffixLink = split;
            }

            lastNewNode = split;
        }

        // One suffix have been added, decrease remainder suffix index by 1.
        remainder--;

        if (activePoint.activeNode == root && activePoint.activeLength > 0) {
            activePoint.activeLength--;
            activePoint.activeEdge = pos - remainder + 1;
        } else if ( activePoint.activeNode != root ) {
            activePoint.activeNode = activePoint.activeNode->suffixLink;
        }
    }
}

/**
 * setSuffixIndex
 * @brief Set suffix tree leaf index
 * @param {Node*} node - step node in the tree
 * @param {int} labelHeight - current index
 */
void SuffixTree::setSuffixIndex(Node *node, int labelHeight) {
    if (node == nullptr) {
        return;
    }

    int leaf = 1;
    for (int i(0); i < MAXCHARS; i++) {
        if (node->children[i] != nullptr) {
            leaf = 0;
            setSuffixIndex(node->children[i], labelHeight + getEdgeLength(node->children[i]));
        }
    }

    if (leaf == 1) {
        node->suffixIndex = size - labelHeight;
    }
}

/**
 * printSuffixTree
 * @brief Set suffix tree leaf index
 * @param {Node*} node - step node in the tree
 * @param {int} labelHeight - current index
 */
void SuffixTree::printSuffixTree(Node *node, int depth) {
    // Local printing function (closure)
    auto print = [] (int start, int end, string sentence) {
        cout << "└";
        for (int i(start); i <= end; i++ )
            cout << sentence[i];
        cout << "-ø";
    };

    for (int i(0); i < depth; i++)
        cout << " ";

    if (node == nullptr)
        return;

    // If node is not the Root print edge.
    if (node->start != -1)
        print(node->start, *(node->end), sentence);
    else
        cout << "ø\n";

    int leaf = 1;
    for (int j(0); j < MAXCHARS; j++) {
        if (node->children[j] != nullptr) {
            if (leaf == 1 && node->start != -1) {
                cout << node->suffixIndex << "\n";
            }

            leaf = 0;
            printSuffixTree(node->children[j], depth + 1);
        }
    }

    if (leaf == 1) {
        cout << node->suffixIndex << endl;
    }
}

/**
 * buildSuffixTree
 * @brief Construction of a simple suffix tree.
 * @param {string} sentence - text used to construct suffix tree.
 * @return {Node*} Pointer to root node
 */
Node* SuffixTree::buildSuffixTree() {
    rootEnd = new int();
    *rootEnd = -1;

    root = createNewNode(-1, rootEnd);
    SuffixTree::setActivePoint(root, 0, 0);
    for (int i(0); i < sentence.length(); i++) {
        extendSuffixTree(i, sentence);
    }
    int labelHeight = 0;
    setSuffixIndex(root, labelHeight);

    return root;
}

int main(int argc, const char * argv[]) {
    SuffixTree tree ("abcabxabcd");
    tree.buildSuffixTree();
    tree.printSuffixTree(tree.getRoot(), 0);
    return 0;
}
