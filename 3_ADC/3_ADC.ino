void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200); // 初始化串口
   analogReadResolution(12);// 初始化ADC 与位数 ，最大16位
}

void loop() {
  // put your main code here, to run repeatedly:
  //读取ADC
  int analogValue = analogRead(1);
  int analogVolts = analogReadMilliVolts(1);

  //打印ADC值
  Serial.printf("ADC analog value = %d\n", analogValue);
  Serial.printf("ADC millivolts value = %d\n", analogVolts);
  delay(100); 
}
