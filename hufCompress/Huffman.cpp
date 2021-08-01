//
//  Huffman.cpp
//  hufCompress
//
//  Created by jieying zhuang on 2021/7/15.
//

#include "Huffman.hpp"
#include <queue>

void deleteNode(Node* node);

Huffman::Huffman(int *charNum) {
    priority_queue<Node *, vector<Node *>, cmp> queue;
    //遍历数组，生成Node结点，放到优先队列中
    for (int i = 0; i < CHAR_NUM; i++) {
        if(charNum[i] != 0) {
            Node* node = (Node *)malloc(sizeof(Node));
            node->ch = i;
            node->isKeyNode = true;
            node->lchild = NULL;
            node->rchild = NULL;
            node->weight = charNum[i];
            queue.push(node);
        }
    }
    //每次取出最小的两个，合成一个，重新放回去
    while (queue.size() > 1) {
        Node* node1 = queue.top();
        queue.pop();
        Node* node2 = queue.top();
        queue.pop();
        printf("choose %d and %d\n", node1->ch, node2->ch);
        //完成二叉树的构建
        Node* node = (Node *)malloc(sizeof(Node));
        node->isKeyNode = false;
        node->weight = node1->weight + node2->weight;
        node->lchild = node1;
        node->rchild = node2;
        queue.push(node);
    }
    if (queue.size() == 1) {
        rootNode = queue.top();
        curStateNode = rootNode;
    }
}

void Huffman::compile() {
    compile(rootNode, "");
}

void Huffman::compile(Node* node, string s) {
    if (node == NULL) {
        return;
    }
    if (node->isKeyNode == true) {
        code[node->ch] = s;
        return;
    }
    compile(node->lchild, s + "0");
    compile(node->rchild, s + "1");
}

string Huffman::getCode(unsigned char ch) {
    return code[ch];
}

unsigned char Huffman::move(int bit, bool &isKeyNode) {
    if(bit == 0) {
        curStateNode = curStateNode->lchild;
    } else {
        curStateNode = curStateNode->rchild;
    }
    isKeyNode = curStateNode->isKeyNode;
    unsigned char ch = curStateNode->ch;
    if (isKeyNode) {
        curStateNode = rootNode;
    }
    return ch;
}

Huffman::~Huffman() {
    //二叉树销毁
    deleteNode(rootNode);
}

void deleteNode(Node* node) {
    if(node == NULL) {
        return;
    }
    deleteNode(node->lchild);
    deleteNode(node->rchild);
    delete(node);
}
