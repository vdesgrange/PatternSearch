#include "../../include/SuffixTree.hpp"

SuffixTree::SuffixTree () {
}

void SuffixTree::setActivePoint(Node *node, int edge, int length) {
    this->activePoint.activeNode = node;
    this->activePoint.activeEdge = edge;
    this->activePoint.activeLength = length;
}

ActivePoint SuffixTree::getActivePoint() {
    return this->activePoint;
}

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

int SuffixTree::getEdgeLength(Node* node) {
    return *(node->end) - node->start + 1;
}

/**
 * @method walkDown
 * @brief
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

void SuffixTree::extendSuffixTree(int pos, string sentence) {
    end = pos;
    remainder++;
    lastNewNode = nullptr;

    while (remainder > 0) {
        // Active length zero. Active edge value set to caractere currently processed.
        if (activePoint.activeLength == 0)
            activePoint.activeEdge = pos;

        if (activePoint.activeNode->children[sentence[activePoint.activeEdge]] == nullptr) {
            activePoint.activeNode->children[sentence[activePoint.activeEdge]] = createNewNode(pos, &end);
            if (lastNewNode != nullptr) {
                lastNewNode->suffixLink = activePoint.activeNode;
                lastNewNode = nullptr;
            }
        } else {
            Node *next = activePoint.activeNode->children[sentence[activePoint.activeEdge]];
            if (walkDown(next)) {
                continue;
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

            splitEnd = new int();
            *splitEnd = next->start + activePoint.activeLength - 1;
            Node *split = createNewNode(next->start, splitEnd);
            activePoint.activeNode->children[sentence[activePoint.activeEdge]] = split;
            split->children[sentence[pos]] = createNewNode(pos, &end);
            next->start += activePoint.activeLength;
            split->children[sentence[next->start]] = next;

            if (lastNewNode != nullptr) {
                lastNewNode->suffixLink = split;
            }

            lastNewNode = split;
        }

        remainder--;
        if (activePoint.activeNode == root && activePoint.activeLength > 0) {
            activePoint.activeLength--;
            activePoint.activeEdge = pos - remainder + 1;
        } else if ( activePoint.activeNode != root ) {
            activePoint.activeNode = activePoint.activeNode->suffixLink;
        }
    }
}

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

Node* SuffixTree::buildSuffixTree(string sentence) {
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
