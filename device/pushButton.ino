#include <Bounce2.h>

Bounce debouncer = Bounce(); // สร้าง debouncer object
long nowTime = 0; 
long lastTime = 0; 
void pushButtonSetup() { 

  // debouncer.attach(BUTTON_PIN, INPUT_PULLUP);
  // debouncer.interval(25); // กำหนดเวลาการเปลี่ยนสถานะให้กับ debouncer object ที่ 25 มิลลิวินาที


  pinMode(BUTTON_PIN, INPUT_PULLUP);

}



void pushButtonLoop() {
  // debouncer.update(); // อัปเดตสถานะให้กับ debouncer object

  // กำหนดเงื่อนไขให้โค้ดโปรแกรมในวงเล็บปีกกาทำงานเมื่อสถานะปุ่มกดเปลี่ยนจาก HIGH เป็น LOW โดยเช็คจากฟังก์ชั่น fell()
  // หากต้องการเช็คสถานะจาก LOW เป็น HIGH ให้แทนที่ฟังก์ชั่น fell() ด้วยฟังก์ชั่น rose()
  // if ( debouncer.fell() ) {
    nowTime = millis();

    int value = digitalRead(BUTTON_PIN);
    if(value == LOW){
      if(nowTime -lastTime > 3000){
        pushButtonState = !pushButtonState; // สลับสถานะติด/ดับของ LED
        String value = "";
        // if(pushButtonState == 1){
        //   value = "on";
        // }else{
        //   value = "off";
        // }
  
        mqtt_client.publish((valve_topic).c_str(), String(pushButtonState).c_str(), true);
        lastTime = nowTime;
      Serial.println("\r\npushButtonLoop:" + value);
      }

    }
//  Serial.println(ledState);
//  digitalWrite(LED_STATUS, ledState);
  // }
}
