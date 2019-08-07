int inByte;

void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
}

void loop() { // run over and over
    Serial.print("10,60");
    if (Serial.available() > 0) {
        inByte = Serial.read();
        inByte=inByte-48;     //converts it to ASCII
    
        if (inByte==0)
        {
        //no input
        }
        if (inByte==1)
        {
        //1 is forward
        }
        if (inByte==2)
        {
        //2 is left  
        }
        if (inByte==3)
        {
        //3 is right
        }
        if (inByte==4)
        {
        //4 is reverse  
        }
    }
}
