//
//  main.cpp
//  LLLog
//
//  Created by multimedia on 2018/9/14.
//  Copyright © 2018年 ___multiMedia___. All rights reserved.
//

#include <iostream>
#include <string>

int main(int argc, const char * argv[]) {
    // insert code here...
    
    std::string test = R"(\
    //attribute 关键字用来描述传入shader的变量
    attribute vec4 vertexPosition; // 需要从外部获取的4分量vector
    attribute vec4 pixelColor;
    //varying 关键字用来描述从vertex shader传递给fragment shader的变量
    //精度修饰符分为三种：highp, mediump, lowp
    varying mediump vec4 finalPixelColor; //mediumP修饰代表中等精度，提高效率。
    
    void main(void) {
        finalPixelColor = pixelColor; // 将pixelColor的值通过finalPixelColor传递给fragment shader
        gl_Position = vertexPosition; // gl_Position是vertex shader的内建变量，gl_Position中的顶点值最终输出到渲染管线中
    }
    )";
    
    std::cout << test;
    return 0;
}
