#include<iostream>
#include "BTlibrary.hpp"
using namespace std;
int main(){
    TreeNode* t = createTree();
    inorderTree(t);
    return 0;
}