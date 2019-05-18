//
// Created by Christian nahuel Rivera on 15/5/19.
//

#include "../TreeNode.h"

TreeNode::TreeNode(int vertexIndex) {
    this->vertexIndex = vertexIndex;
    this->father = nullptr;
    this->componentIndex = vertexIndex;
}

void TreeNode::setFather(TreeNode *father, int fatherComponent) {
    this->componentIndex = fatherComponent;
    this->father = father;
}

TreeNode * TreeNode::getFather() {
    return this->father;
}

int TreeNode::getVertexIndex() {
    return this->vertexIndex;
}

int TreeNode::getComponentIndex() {
    return this->componentIndex;
}

void TreeNode::setComponentIndex(int newComponent) {
    this->componentIndex = newComponent;
}