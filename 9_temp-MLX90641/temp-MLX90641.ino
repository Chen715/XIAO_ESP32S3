/*
    输出所有像素的温度读数，供 Processing 可视化工具读取
*/

#include <Wire.h>
#include "MLX90641_API.h"
#include "MLX9064X_I2C_Driver.h"

#if defined(ARDUINO_ARCH_AVR)
    #define debug  Serial

#elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
    #define debug  Serial
#else
    #define debug  Serial
#endif

const byte MLX90641_address = 0x33; //MLX90641 的默认 7 位未移位地址
#define TA_SHIFT 8 //MLX90641 在开放空气中的默认移位

uint16_t eeMLX90641[832];
float MLX90641To[192];
uint16_t MLX90641Frame[242];
paramsMLX90641 MLX90641;
int errorno = 0;

void setup() {
    Wire.begin();
    Wire.setClock(400000); //将 I2C 时钟速度提高到 400kHz

    debug.begin(115200); //尽可能快的调试速度

    while (!debug); //等待用户打开终端
    //debug.println("MLX90640 IR Array Example");


    if (isConnected() == false) {
        debug.println("在默认 I2C 地址未检测到 MLX90641。请检查接线。程序冻结。");
        while (1);
    }
    //获取设备参数 - 我们只需要执行一次
    int status;
    status = MLX90641_DumpEE(MLX90641_address, eeMLX90641);
    errorno = status;//MLX90641_CheckEEPROMValid(eeMLX90641);//eeMLX90641[10] & 0x0040;//
    
    if (status != 0) {
        debug.println("加载系统参数失败");
       while(1);
    }

    status = MLX90641_ExtractParameters(eeMLX90641, &MLX90641);
    //errorno = status;
    if (status != 0) {
        debug.println("参数提取失败");
        while(1);
    }

    //参数提取完成后，我们可以释放 eeMLX90641 数组

    //MLX90641_SetRefreshRate(MLX90641_address, 0x02); //设置速率为 2Hz
    MLX90641_SetRefreshRate(MLX90641_address, 0x03); //设置速率为 4Hz
    //MLX90641_SetRefreshRate(MLX90641_address, 0x07); //设置速率为 64Hz    

}

void loop() {

    long startTime = millis();
    
    for (byte x = 0 ; x < 2 ; x++) {
        int status = MLX90641_GetFrameData(MLX90641_address, MLX90641Frame);

        float vdd = MLX90641_GetVdd(MLX90641Frame, &MLX90641);
        float Ta = MLX90641_GetTa(MLX90641Frame, &MLX90641);

        float tr = Ta - TA_SHIFT; //基于传感器环境温度的反射温度
        float emissivity = 0.95;

        MLX90641_CalculateTo(MLX90641Frame, &MLX90641, emissivity, tr, MLX90641To);
    }
    long stopTime = millis();
    for (int x = 0 ; x < 192 ; x++) {
        debug.print(MLX90641To[x], 2);
        debug.print(",");
    }
    debug.println("");   
}

//如果在 I2C 总线上检测到 MLX90641，则返回 true
boolean isConnected() {
    Wire.beginTransmission((uint8_t)MLX90641_address);
    if (Wire.endTransmission() != 0) {
        return (false);    //传感器未应答
    }
    return (true);
}