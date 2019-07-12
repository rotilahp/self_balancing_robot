#include <BluetoothSerial.h> //Header File for Serial Bluetooth, will be added by default into Arduino

BluetoothSerial ESP_BT; //Object for Bluetooth

int incoming;
int LED_BUILTIN = 2;

void setup() {
  Serial.begin(115200); //Start Serial monitor in 9600
  ESP_BT.begin("Daniel's ESP32 MC"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");

  pinMode (LED_BUILTIN, OUTPUT);//Specify that LED pin is output
}

void loop() {
  
  if (ESP_BT.available()) //Check if we receive anything from Bluetooth
  {
    incoming = ESP_BT.read(); //Read what we recevive 
    incoming=incoming-48;
    Serial.print("Received:"); Serial.println(incoming);
        if (incoming==0)
        {
        digitalWrite(LED_BUILTIN, LOW);
        }
        if (incoming==1)
        {
        digitalWrite(LED_BUILTIN, HIGH);
        }
        if (incoming==2)
        {
        digitalWrite(LED_BUILTIN, HIGH);  
        }
        if (incoming==3)
        {
        digitalWrite(LED_BUILTIN, HIGH);   
        }
        if (incoming==4)
        {
        digitalWrite(LED_BUILTIN, HIGH);   
        }
    }
    ESP_BT.print("60,10");  
    
  
  delay(20);
}
