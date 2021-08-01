//
//  Huffman.hpp
//  hufCompress
//
//  Created by jieying zhuang on 2021/7/15.
//

#ifndef Huffman_hpp
#define Huffman_hpp

#include <iostream>
#include <cstring>
#include <string>

#define CHAR_NUM 256

using namespace std;

struct Node {
    int weight;
    Node *lchild;
    Node *rchild;
    //属于原生节点还是通过合成的节点
    bool isKeyNode;
    unsigned char ch;
};
struct cmp {
    bool operator() (Node *a, Node *b) {
        return a->weight > b->weight;
    }
};


class Huffman {
public:
    //根据各字符出现频率，构建哈夫曼树
    Huffman(int *charNum);
    //利用哈夫曼树重新给字符编码
    void compile();
    //获取编码信息
    string getCode(unsigned char ch);
    //状态机,当移动到keyNode时，返回值有效
    unsigned char move(int bit, bool &isKeyNode);
    virtual ~Huffman();
private:
    //根结点
    Node* rootNode;
    //状态机当前位置
    Node* curStateNode;
    //各点对应编码
    string code[CHAR_NUM];
    //哈夫曼编码
    void compile(Node* node, string s);
};

#endif /* Huffman_hpp */
