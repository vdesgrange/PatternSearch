#include "../../include/SuffixTree.hpp"

SuffixTree::SuffixTree () {
    sentence = vector<MatItem>(0);
    root = nullptr;
    lastNewNode = nullptr;
    ActivePoint activePoint;
    remainder = 0;
    end = 0;
    rootEnd = nullptr;
    splitEnd = nullptr;
    size = 0;
}

SuffixTree::SuffixTree (vector<MatItem> items) {
    sentence = items;
    root = nullptr;
    lastNewNode = nullptr;
    ActivePoint activePoint;
    remainder = 0;
    end = 0;
    rootEnd = nullptr;
    splitEnd = nullptr;
    size = 0;
}

SuffixTree::~SuffixTree() {
    //freeSuffixTreeByPostOrder(root);
}
/**
 * getRoot
 * @brief root node getter
 */
Node* SuffixTree::getRoot() {
    return this->root;
}

/**
 * getSentence
 * @brief sentence getter
 * @return {vector<MatItem>} list of item in sentence
 */
vector<MatItem> SuffixTree::getSentence() {
    return this->sentence;
}

/**
 * getLastNewNode
 * @brief lastNewNode getter
 */
const Node* SuffixTree::getLastNewNode() {
    return this->lastNewNode;
}

/**
 * getRemainder
 * @brief remainder getter
 */
int SuffixTree::getRemainder() {
    return this->remainder;
}

/**
 * getEnd
 * @brief End leaf index getter
 */
int SuffixTree::getEnd() {
    return this->end;
}

/**
 * getActivePoint
 * @brief activePoint getter
 * @return {ActivePoint} activePoint
 */
ActivePoint SuffixTree::getActivePoint() {
    return this->activePoint;
}

/**
 * getRootEnd
 * @brief RootEnd getter
 * @return {int*}
 */
const int* SuffixTree::getRootEnd() {
    return this->rootEnd;
}

/**
 * getSplitEnd
 * @brief SplitEnd getter
 * @return {int*}
 */
const int* SuffixTree::getSplitEnd() {
    return this->splitEnd;
}

/**
 * getSize
 * @brief Size getter
 * @return {int*}
 */
int SuffixTree::getSize() {
    return this->size;
}


/**
 * setRoot
 * @brief root node setter
 */
void SuffixTree::setRoot(Node *node) {
    this->root = node;
}

/**
 * setSentence
 * @brief sentence setter
 * @param {vector<MatItem>} text - items used to set sentence
 */
void SuffixTree::setSentence(vector<MatItem> items) {
    this->sentence = items;
}

/**
 * setLastNewNode
 * @brief lastNewNode setter
 */
void SuffixTree::setLastNewNode(Node *node) {
    this->lastNewNode = node;
}

/**
 * setRemainder
 * @brief remainder setter
 */
void SuffixTree::setRemainder(int i) {
    this->remainder = i;
}

/**
 * setEnd
 * @brief End leaf index setter
 */
void SuffixTree::setEnd(int i) {
    this->end = i;
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
 * setSplitEnd
 * @brief SplitEnd setter
 */
void SuffixTree::setSplitEnd(int i) {
    this->splitEnd = &i;
}

/**
 * setSize
 * @brief size setter
 */
void SuffixTree::setSize(int i) {
    this->size = i;
}

/**
 * setRootEnd
 * @brief RootEnd setter
 */
void SuffixTree::setRootEnd(int i) {
    this->rootEnd = &i;
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
    node->suffixLink = this->root;
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
    if (this->getActivePoint().activeLength >= getEdgeLength(currNode)) {
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
void SuffixTree::extendSuffixTree(int pos, vector<MatItem> sentence) {
    end = pos; // End leaf index
    remainder++; // Need to insert + 1 suffix.
    lastNewNode = nullptr;

    while (remainder > 0) { // While suffix to insert > 0
        // Active length zero. Active edge value set to caractere currently processed.
        // Case with one ( and last ) suffix to process or insert.
        if (this->getActivePoint().activeLength == 0)
            activePoint.activeEdge = pos;

        // If no child for active item, create a child.
        if (activePoint.activeNode->children.count(sentence[activePoint.activeEdge]) == 0) {
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

            // Item currently processed is already into the tree.
            if (
                    (sentence[next->start + activePoint.activeLength].v == sentence[pos].v) &&
                    (sentence[next->start + activePoint.activeLength].isSeparator == sentence[pos].isSeparator)
               ) {
                if (lastNewNode != nullptr && activePoint.activeNode != root) {
                    lastNewNode->suffixLink = activePoint.activeNode;
                    lastNewNode = nullptr;
                }
                // Item matched on path represented by ActivePoint.
                // Increase activeLength by 1 to represente this matching.
                activePoint.activeLength++;
                break;
            }

            // Processing into an edge of a tree with new item.
            // Adding new intermediate node to the branch.
            // Compute interne node end index.
            splitEnd = new int();
            *splitEnd = next->start + activePoint.activeLength - 1;
            // Create splitting node.
            Node *split = createNewNode(next->start, splitEnd);
            activePoint.activeNode->children[sentence[activePoint.activeEdge]] = split;
            // Add branch for current item.
            split->children[sentence[pos]] = createNewNode(pos, &end);
            // Add branch for  sub-sequence of the past edge.
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
        } else if ( activePoint.activeNode != root && activePoint.activeNode->suffixLink != nullptr) {
            activePoint.activeNode = activePoint.activeNode->suffixLink;
        }
    }
}

/**
 * setSuffixIndex
 * @brief Set suffix tree leaf index and clean the suffix trie.
 * It will set the suffix tree leaf with the suffix index.
 * It will clean the suffix tree from unwanted sentence by finding separators.
 * @param {Node*} node - step node in the tree
 * @param {int} labelHeight - current index
 */
void SuffixTree::setSuffixIndex(Node *node, int labelHeight) {
    // If node is a nullptr. Stop progress and return.
    if (node == nullptr) {
        return;
    }

    int leaf = 1;
    map<MatItem, SuffixTreeNode*>::iterator it;
    for (it = node->children.begin(); it != node->children.end(); it++) {
        // Check there is no issue in children address.
        if (it->second != nullptr) {
            leaf = 0; // There is at least one child, so edge is not a leaf.
            setSuffixIndex(it->second, labelHeight + getEdgeLength(it->second));
        }
    }

    // If edge is a leaf, we check if there is a separator of sub-sentences.
    if (leaf == 1) {
        for (int i(node->start); i <= *(node->end); i++) {
            if (sentence[i].isSeparator) { // Separator of the next sub-sentence.
                node->end = new int(); // We remove the end of the edge.
                *(node->end) = i;
            }
        }
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
    auto print = [] (int start, int end, vector<MatItem> sentence) {
        cout << "└";
        for (int i(start); i <= end; i++ ) {
            if (sentence[i].isSeparator)
                cout << "$";
            cout << sentence[i].v << ".";
        }
        cout << "-ø";
    };

    // Space to visualise graph branch
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
    map<MatItem, SuffixTreeNode*>::iterator it;
    for (it = node->children.begin(); it != node->children.end(); it++) {
        if (it->second != nullptr) {
            if (leaf == 1 && node->start != -1) {
                cout << node->suffixIndex << "\n";
            }

            leaf = 0;
            printSuffixTree(it->second, depth + 1);
        }
    }

    if (leaf == 1) {
        cout << node->suffixIndex << endl;
    }
}

/**
 * freeSuffixTreeByPostOrder
 * @brief Delete every node of the suffix trie.
 * Usage of a recursive method.
 * @param {Node*} node - root node of the current sub-trie
 */
void SuffixTree::freeSuffixTreeByPostOrder(Node *node)
{
    if (node == nullptr)
        return;

    map<MatItem, SuffixTreeNode*>::iterator it;
    for (it = node->children.begin(); it != node->children.end(); it++) {
        if (it->second != nullptr) {
            freeSuffixTreeByPostOrder(it->second);
        }
    }

    if (node->suffixIndex == -1)
        delete node->end;

    delete node;
}

/**
 * buildSuffixTree
 * @brief Construction of a generalized suffix tree.
 * Usage of Ukkonen algorithm - construction in O(nLogn) (Log n for non-constant alphabet).
 * @param {string} sentence - text used to construct suffix tree.
 * @return {Node*} Pointer to root node
 */
Node* SuffixTree::buildSuffixTree() {
    rootEnd = new int();
    *rootEnd = -1;

    root = createNewNode(-1, rootEnd);
    SuffixTree::setActivePoint(root, 0, 0);
    for (int i(0); i < sentence.size(); i++) {
        extendSuffixTree(i, sentence);
    }
    int labelHeight = 0;
    setSuffixIndex(root, labelHeight);

    return root;
}

int main(int argc, const char * argv[]) {
    vector<MatItem> vec;
    vec.push_back({120, false});
    vec.push_back({97, false});
    vec.push_back({98, false});
    vec.push_back({120, false});
    vec.push_back({97, false});
    vec.push_back({0, true});
    vec.push_back({98, false});
    vec.push_back({97, false});
    vec.push_back({98, false});
    vec.push_back({120, false});
    vec.push_back({98, false});
    vec.push_back({97, false});
    vec.push_back({1, true});

    SuffixTree tree (vec);
    tree.buildSuffixTree();
    tree.printSuffixTree(tree.getRoot(), 0);
    return 0;
}
