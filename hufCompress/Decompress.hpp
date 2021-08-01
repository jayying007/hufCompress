//
//  Unpack.hpp
//  hufCompress
//
//  Created by jieying zhuang on 2021/7/15.
//

#ifndef Unpack_hpp
#define Unpack_hpp

#include <stdio.h>
#include"Huffman.hpp"
#include<fstream>
#include<assert.h>
#include<cstring>
#include<cstdlib>

#define CHAR_NUM 256

class Decompress {
public:
    Decompress(string inputName, string outputName);
    //执行解压
    void start();
    virtual ~Decompress();
protected:

private:
    FILE *readPointer;
    string inputFileName;
    string outputFileName;
    Huffman *tree;
    //每种字符个数
    int *charNum;
    int fileSize;
    //哈夫曼编码
    void buildTree();
    //输出压缩的文件
    void writeToOutputFile();
    void debugCode();
};
#endif /* Unpack_hpp */
