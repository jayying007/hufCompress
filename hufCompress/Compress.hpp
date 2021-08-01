//
//  Compress.hpp
//  hufCompress
//
//  Created by jieying zhuang on 2021/7/15.
//

#ifndef Compress_hpp
#define Compress_hpp

#include <stdio.h>
#include "Huffman.hpp"
#include <fstream>
#include <assert.h>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdlib>


#define CHAR_NUM 256

class Compress {
public:
    Compress(string inputName, string outputName);
    //执行压缩
    void start();
    virtual ~Compress();
protected:

private:
    string inputFileName;
    string outputFileName;
    Huffman *tree;
    //每种字符个数
    int *charNum;
    int fileSize;
void readFile();
    //统计各种字符数
    void CountNum();
    //二进制转十进制
    char TranToNum(string data);
    //哈夫曼编码
    void BuildCode();
    //输出压缩的文件
    void writeToOutputFile();
    void debugCode();
    int binSearch(int k,int a[],int l,int d);
};

#endif /* Compress_hpp */
