//
//  Compress.cpp
//  hufCompress
//
//  Created by jieying zhuang on 2021/7/15.
//

#include "Compress.hpp"
#include <string>
#include <cstring>
#include <queue>

using namespace std;

void Compress::debugCode() {
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

Compress::Compress(string inputName, string outputName) {
    inputFileName = inputName;
    outputFileName = outputName;
    charNum = new int[CHAR_NUM];
    memset(charNum, 0, sizeof(int) * CHAR_NUM);
}

void Compress::start() {
    cout<<"-------压缩中-------"<<endl;
    //1.读取文件，统计各字符出现的个数
    readFile();
    //2.1构建哈夫曼树
    tree = new Huffman(charNum);
    //2.2生成新的编码
    tree->compile();
    debugCode();
    //输出文件
    writeToOutputFile();
    cout<<"------压缩完成------"<<endl;
}

void Compress::readFile() {
    //文件指针
    FILE* fp;
    //以二进制方式打开文件
    if ((fp = fopen(inputFileName.data(), "rb")) == NULL) {
        cout<<"Open file failed!"<<endl;
        exit(0);
    }
    //获取数据总长度
    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    rewind(fp);
    unsigned char ch;
    while(!feof(fp)) {
        ch = fgetc(fp);
        charNum[ch]++;
    }
}

void Compress::writeToOutputFile() {
    FILE *writePointer;
    if ((writePointer = fopen(outputFileName.data(), "wb")) == NULL) {
        cout<<"open output file error!"<<endl;
        exit(0);
    }
    //1.写入原文件大小
    fputc(fileSize >> 24, writePointer);
    fputc(fileSize >> 16, writePointer);
    fputc(fileSize >> 8, writePointer);
    fputc(fileSize, writePointer);
    //2.1统计出现的字符
    int count = 0;
    for(int i = 0; i < CHAR_NUM; i++) {
        if(charNum[i] != 0) {
            count++;
        }
    }
    fputc(count >> 8, writePointer);
    fputc(count, writePointer);
    //2.2写入各字符数量 ASCII值---空格---权值---回车
    for(int i = 0; i < CHAR_NUM; i++) {
        if(charNum[i] != 0) {
            fputc(i, writePointer);
            fputc(charNum[i] >> 24, writePointer);
            fputc(charNum[i] >> 16, writePointer);
            fputc(charNum[i] >> 8, writePointer);
            fputc(charNum[i], writePointer);
        }
    }
    //3.读取输入字节流，根据code信息，重新组装，然后写到输出文件
    FILE *readPointer;
    if ((readPointer = fopen(inputFileName.data(), "rb")) == NULL) {
        cout << "open input file error!" << endl;
        exit(0);
    }
    
    unsigned char inputChar;
    queue<char> outputQueue;
    while(!feof(readPointer)) {
        //3.1读取一个字符，翻译为新的编码
        inputChar = fgetc(readPointer);
        string code = tree->getCode(inputChar);
        //3.2将新编码暂时存到队列
        for(int i = 0; i < code.length(); i++) {
            outputQueue.push(code[i]);
        }
        //3.3如果积累了8个，则可以组成一个字节了，输出
        while (outputQueue.size() >= 8) {
            int value = 0;
            for(int i = 0; i < 8; i++) {
                char ch = outputQueue.front();
                outputQueue.pop();
                value = value << 1;
                if(ch == '1') {
                    value |= 1;
                }
            }
            fputc(value, writePointer);
        }
    }
    //4.出现残留bit，凑足8个后写入
    if (!outputQueue.empty()) {
        int value = 0;
        int size = outputQueue.size();
        while (!outputQueue.empty()) {
            char ch = outputQueue.front();
            outputQueue.pop();
            value = value << 1;
            if(ch == '1') {
                value |= 1;
            }
        }
        value = value << (8 - size);
        fputc(value, writePointer);
    }
    
    fclose(readPointer);
    fclose(writePointer);
}

Compress::~Compress() {
    //dtor
    delete charNum;
}
