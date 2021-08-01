//
//  Unpack.cpp
//  hufCompress
//
//  Created by jieying zhuang on 2021/7/15.
//

#include "Decompress.hpp"
#include<iostream>

using namespace std;

void Decompress::debugCode() {
    cout << "====char count====" << endl;
    for (int i = 0; i < CHAR_NUM; i++) {
        if(charNum[i] > 0) {
            cout << "ascii:" << i << "|" << (char)i << ":" << charNum[i] << endl;
        }
    }
    cout << "====char code====" << endl;
    for(int i = 0; i < CHAR_NUM; i++) {
        if(charNum[i] > 0) {
            string code = tree->getCode(i);
            cout << (char)i << ":" << tree->getCode(i) << endl;
        }
    }
}

Decompress::Decompress(string inputName, string outputName) {
    //ctor
    inputFileName = inputName;
    outputFileName = outputName;
    charNum = new int[CHAR_NUM];
    memset(charNum, 0, sizeof(int) * CHAR_NUM);
    
    if ((readPointer = fopen(inputFileName.data(), "rb")) == NULL) {
        cout<<"open input file error!"<<endl;
        exit(0);
    }
}

void Decompress::start() {
    cout<<"-------解压中-------"<<endl;
    buildTree();
    writeToOutputFile();
    cout<<"------解压完成------"<<endl;
}

void Decompress::buildTree() {
    //源文件大小
    fileSize = (fgetc(readPointer) << 24) + (fgetc(readPointer) << 16) + (fgetc(readPointer) << 8) + fgetc(readPointer);
    //编码字符数
    int count = (fgetc(readPointer) << 8) + fgetc(readPointer);
    //读取编码信息
    for (int i = 0; i < count; i++) {
        unsigned char ch = fgetc(readPointer);
        int value = (fgetc(readPointer) << 24) + (fgetc(readPointer) << 16) + (fgetc(readPointer) << 8) + fgetc(readPointer);
        charNum[ch] = value;
    }
    tree = new Huffman(charNum);
    tree->compile();
    debugCode();
}

void Decompress::writeToOutputFile() {
    FILE *writePointer;
    if ((writePointer = fopen(outputFileName.data(), "wb")) == NULL) {
        cout<<"open output file error!"<<endl;
        exit(0);
    }
    int size = 0;
    while (!feof(readPointer) && size != fileSize) {
        int bit = fgetc(readPointer);
        bool isKeyNode = false;
        for (int i = 7; i >= 0; i--) {
            unsigned char ch = tree->move((bit >> i) & 1, isKeyNode);
            if (isKeyNode) {
                fputc(ch, writePointer);
                size++;
            }
            if (size == fileSize) {
                break;
            }
        }
    }
    
    fclose(readPointer);
    fclose(writePointer);
}

Decompress::~Decompress() {
    //dtor
}
