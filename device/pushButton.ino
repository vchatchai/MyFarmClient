#include <Bounce2.h>
#include <WiFiManager.h>          

Bounce debouncer = Bounce(); // สร้าง debouncer object
long nowTime = 0; 
long lastTime = 0; 
long resetTime = 0;

Ticker resetTicker;


void resetTick(){
  int state = digitalRead(LED_POWER);  // get the current state of GPIO1 pin
  digitalWrite(LED_POWER, !state);     // set pin to the opposite state
  digitalWrite(LED_STATUS, !state);     // set pin to the opposite state

}

void pushButtonSetup() { 

  // debouncer.attach(BUTTON_PIN, INPUT_PULLUP);
  // debouncer.interval(25); // กำหนดเวลาการเปลี่ยนสถานะให้กับ debouncer object ที่ 25 มิลลิวินาที


  pinMode(BUTTON_PIN, INPUT_PULLUP);

}

int typeCode;

void pushButtonLoop() {
  // debouncer.update(); // อัปเดตสถานะให้กับ debouncer object

  // กำหนดเงื่อนไขให้โค้ดโปรแกรมในวงเล็บปีกกาทำงานเมื่อสถานะปุ่มกดเปลี่ยนจาก HIGH เป็น LOW โดยเช็คจากฟังก์ชั่น fell()
  // หากต้องการเช็คสถานะจาก LOW เป็น HIGH ให้แทนที่ฟังก์ชั่น fell() ด้วยฟังก์ชั่น rose()
  // if ( debouncer.fell() ) {
    nowTime = millis();

    int value = digitalRead(BUTTON_PIN);
    if(value == LOW){
      
      if(nowTime - resetTime > 6000){
        if(typeCode != 3){
          resetTicker.attach(0.6, resetTick);
          typeCode = 3;
        }
      }else if(nowTime -lastTime > 3000){
        typeCode = 1;
      }

    }else{

        resetTime =  nowTime;

        switch (typeCode)
        {
        case 1:{
          pushButtonState = !pushButtonState; // สลับสถานะติด/ดับของ LED
          String value = "";
        //  powerTicker.attach(0.5, powerTick);
          mqtt_client.publish((valve_topic).c_str(), String(pushButtonState).c_str(), true);
          lastTime = nowTime;
          Serial.println("\r\npushButtonLoop:" + value);
        }
          break;
        case 2:
          break;
        case 3:{

          WiFiManager wifiManager;
          wifiManager.resetSettings();
          resetTicker.detach();
          ESP.reset();
        }
          break;
        
        
        default:
          break;
        }
        typeCode = 0;
    }
//  Serial.println(ledState);
//  digitalWrite(LED_STATUS, ledState);
  // }
}
