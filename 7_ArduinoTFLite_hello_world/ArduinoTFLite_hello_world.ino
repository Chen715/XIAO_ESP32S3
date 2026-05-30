/* Copyright 2024 johnos, TensorFlow Authors. All Rights Reserved.

This sketch is derived from the classic Hello World example of the general
TensorFlow Lite Micro library.
It was adapted and simplified by (based on original work by Chirale)
to conform to the typical style of Arduino sketches.
It has been tested on an ESP32 Dev Board.
The sketch implements a Deep Neural Network pre-trained on calculating
the function sin(x).
By sending a value between 0 and 2*Pi via the Serial Monitor,
both the value inferred by the DNN model and the actual value
calculated using the Arduino math library are displayed.

It shows how to use MicroTFLite Library to run a TensorFlow Lite model.

For more information read the library documentation
at: https://github.com/johnosbb/MicroTFLite

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

// include main library header file
#include <MicroTFLite.h>

// include static array definition of pre-trained model
#include "model.h"

// The Tensor Arena memory area is used by TensorFlow Lite to store input, output and intermediate tensors
constexpr int kTensorArenaSize = 2000;
alignas(16) uint8_t tensor_arena[kTensorArenaSize];

void setup()
{
    // Initialize serial communications and wait for Serial Monitor to be opened
    Serial.begin(115200);
    while (!Serial)
        ;

    Serial.println("Sine(x) function inference example.");
    Serial.println("Initializing TensorFlow Lite Micro Interpreter...");

    // Initialize the model
    if (!ModelInit(model, tensor_arena, kTensorArenaSize))
    {
        Serial.println("Model initialization failed!");
        while (true)
            ;
    }
    Serial.println("Model initialization done.");

    // Optional: Print model metadata
    ModelPrintMetadata();

    // Optional: Print input and output tensor dimensions
    ModelPrintInputTensorDimensions();
    ModelPrintOutputTensorDimensions();

    Serial.println("");
    Serial.println("Please, input a float number between 0 and 6.28");
}
 float x = 0.0;
void loop()
{
    // 设置模型输入张量
    if (!ModelSetInput(x, 0, true))
    {
        Serial.println("设置输入失败！");
        return;
    }
        // 运行推理
    if (!ModelRunInference())
    {
        Serial.println("运行推理失败！");
        return;
    }

    // 获取输出结果（推理得到的 sin 值）
    float inferred_y = ModelGetOutput(0);
    // 计算实际 sin 值
    float actual_y = sin(x);


    // 适配 Arduino 串口绘图仪，用空格分隔
    Serial.print(x);//输入的x
    Serial.print(" ");
    Serial.print(inferred_y);//推理的值
    Serial.print(" ");
    Serial.println(actual_y);//sin函数的值


    
    // 更新 x 的值，每次增加 0.01
    x += 0.05;
    // 如果超过上限 6.28，则重置为 0，实现循环
    if (x > 6.28)
    {
        x = 0.0;
    }

    // 添加适当延时
    delay(100);

}
