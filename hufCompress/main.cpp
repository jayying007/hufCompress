//
//  main.cpp
//  hufCompress
//
//  Created by jieying zhuang on 2021/7/15.
//

#include <iostream>
#include "Compress.hpp"
#include "Decompress.hpp"
#include <string>

using namespace std;

void showMenu() {
    cout<<"------------"<<endl;
    cout<<"1.压缩文件."<<endl;
    cout<<"2.解压文件."<<endl;
    cout<<"------------"<<endl;
}


int main() {
    int choice = 0;
    do {
        showMenu();
        scanf("%d", &choice);
        string inputFileName;
        string outputFileName;
        printf("输入文件位置（绝对路径）：");
        cin >> inputFileName;
        printf("输出文件位置（绝对路径）：");
        cin >> outputFileName;

        if (choice == 1) {
            Compress compress(inputFileName, outputFileName);
            compress.start();
        } else if(choice == 2) {
            Decompress decompress(inputFileName, outputFileName);
            decompress.start();
        }
    } while (choice == 1 || choice == 2);
    
    return 0;
}
