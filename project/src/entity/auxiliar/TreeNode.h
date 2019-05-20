//
// Created by Christian nahuel Rivera on 15/5/19.
//

#ifndef AED3_2019_1C_TP2_TREENODE_H
#define AED3_2019_1C_TP2_TREENODE_H


class TreeNode {
public:
    TreeNode(int vertexIndex);
    TreeNode * getFather();
    void setFather(TreeNode *father, int fatherComponent);
    int getVertexIndex();
    int getComponentIndex();
    void setComponentIndex(int newComponent);

private:
    int vertexIndex;
    int componentIndex;
    TreeNode* father;
};


#endif //AED3_2019_1C_TP2_TREENODE_H
