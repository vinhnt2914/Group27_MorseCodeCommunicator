
#include <Arduino.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <AsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

AsyncWebServer server(80);

const char* ssid = "P 802"; // Your WiFi SSID
const char* password = "123456789"; // Your WiFi Password

//Variables for morse webCode
const int buttonPin = D3;   
const int led = D4;
const int buz = D5;

int ledState = HIGH;       
int buttonState = LOW;             
int lastButtonState = LOW;  
int doesitwork = LOW;  // variable used for debuging early versions of the code

int pause_value = 250;  // depending on your skill and how fast your fingers are you can change this value to make typing a message faster or slower
long signal_length = 0;
long pause = 0;

String serialMorse = "";
String serialDash = "-";
String serialDot = "*";

boolean cheker = false;
boolean linecheker = false;

long lastDebounceTime = 0;  
long debounceDelay = 50;   

String webCode = "";
int len = 0;
char ch;
char new_char;
int unit_delay = 100;

/* Message callback of WebSerial */
void recvMsg(uint8_t *data, size_t len){
  WebSerial.println("Sending data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
  }
  webCode = d;
  WebSerial.println(d);

}
void dot() {
  Serial.print(".");
  digitalWrite(led, HIGH);
  digitalWrite(buz, HIGH);
  delay(unit_delay);
  digitalWrite(led, LOW);
  digitalWrite(buz, LOW);
  delay(unit_delay);
}

void dash() {
  Serial.print("-");
  digitalWrite(led, HIGH);
  digitalWrite(buz, HIGH);
  delay(unit_delay * 3);
  digitalWrite(led, LOW);
  digitalWrite(buz, LOW);
  delay(unit_delay);
}

void A() {
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}

void B()
{
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void C()
{
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void D()
{
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void E()
{
  dot();
  delay(unit_delay*3);
}
void f()
{
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void G()
{
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void H()
{
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void I()
{
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void J()
{
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}
void K()
{
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}
void L()
{
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void M()
{
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}
void N()
{
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void O()
{
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}
void P()
{
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void Q()
{
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}
void R()
{
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void S()
{
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void T()
{
  dash();
  delay(unit_delay*3);
}
void U()
{
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}
void V()
{
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}
void W()
{
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}
void X()
{
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}
void Y()
{
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}
void Z()
{
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void one()
{
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}
void two()
{
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}
void three()
{
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}
void four()
{
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}
void five()
{
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void six()
{
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void seven()
{
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void eight()
{
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void nine()
{
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay*3);
}
void zero()
{
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}

void morse() {
  if (ch == 'A' || ch == 'a') {
    A();
    Serial.print(" ");
  }
  else if (ch == 'B' || ch == 'b')
  {
    B();
    Serial.print(" ");
  }
  else if (ch == 'C' || ch == 'c')
  {
    C();
    Serial.print(" ");
  }
  else if (ch == 'D' || ch == 'd')
  {
    D();
    Serial.print(" ");
  }
  else if (ch == 'E' || ch == 'e')
  {
    E();
    Serial.print(" ");
  }
  else if (ch == 'f' || ch == 'f')
  {
    f();
    Serial.print(" ");
  }
  else if (ch == 'G' || ch == 'g')
  {
    G();
    Serial.print(" ");
  }
  else if (ch == 'H' || ch == 'h')
  {
    H();
    Serial.print(" ");
  }
  else if (ch == 'I' || ch == 'i')
  {
    I();
    Serial.print(" ");
  }
  else if (ch == 'J' || ch == 'j')
  {
    J();
    Serial.print(" ");
  }
  else if (ch == 'K' || ch == 'k')
  {
    K();
    Serial.print(" ");
  }
  else if (ch == 'L' || ch == 'l')
  {
    L();
    Serial.print(" ");
  }
  else if (ch == 'M' || ch == 'm')
  {
    M();
    Serial.print(" ");
  }
  else if (ch == 'N' || ch == 'n')
  {
    N();
    Serial.print(" ");
  }
  else if (ch == 'O' || ch == 'o')
  {
    O();
    Serial.print(" ");
  }
  else if (ch == 'P' || ch == 'p')
  {
    P();
    Serial.print(" ");
  }
  else if (ch == 'Q' || ch == 'q')
  {
    Q();
    Serial.print(" ");
  }
  else if (ch == 'R' || ch == 'r')
  {
    R();
    Serial.print(" ");
  }
  else if (ch == 'S' || ch == 's')
  {
    S();
    Serial.print(" ");
  }
  else if (ch == 'T' || ch == 't')
  {
    T();
    Serial.print(" ");
  }
  else if (ch == 'U' || ch == 'u')
  {
    U();
    Serial.print(" ");
  }
  else if (ch == 'V' || ch == 'v')
  {
    V();
    Serial.print(" ");
  }
  else if (ch == 'W' || ch == 'w')
  {
    W();
    Serial.print(" ");
  }
  else if (ch == 'X' || ch == 'x')
  {
    X();
    Serial.print(" ");
  }
  else if (ch == 'Y' || ch == 'y')
  {
    Y();
    Serial.print(" ");
  }
  else if (ch == 'Z' || ch == 'z')
  {
    Z();
    Serial.print(" ");
  }
  else if (ch == '0')
  {
    zero();
    Serial.print(" ");
  }
  else if (ch == '1')
  {
    one();
    Serial.print(" ");
  }
  else if (ch == '2')
  {
    two();
    Serial.print(" ");
  }
  else if (ch == '3')
  {
    three();
    Serial.print(" ");
  }
  else if (ch == '4')
  {
    four();
    Serial.print(" ");
  }
  else if (ch == '5')
  {
    five();
    Serial.print(" ");
  }
  else if (ch == '6')
  {
    six();
    Serial.print(" ");
  }
  else if (ch == '7')
  {
    seven();
    Serial.print(" ");
  }
  else if (ch == '8')
  {
    eight();
    Serial.print(" ");
  }
  else if (ch == '9')
  {
    nine();
    Serial.print(" ");
  }

  else if (ch == ' ') {
    delay(unit_delay * 7);
    Serial.print("/ ");
  }
  else if (ch == '\n'){
    Serial.println("");
  }

  else {
    Serial.println("Unknown Character!");
  }
}

void String2Morse() {
  len = webCode.length();
  for (int i = 0; i < len; i++) {
    ch = webCode.charAt(i);
    morse();
  }
}

void printaj(String prevodilac)   //ugly part of the code but it works fine
{                                 //compare morse string to known morse values and print out the letter or a number 
                                  //the code is written based on the international morse code, one thing i changed is that insted of typing a special string to end the line it happens with enough delay  
  if (prevodilac=="*-"){
    Serial.print("A");
    WebSerial.print("A");
  }
  else if (prevodilac=="-***")  
    {Serial.print("B");
    WebSerial.print("B");}
  else if (prevodilac=="-*-*")  
    {Serial.print("C");
    WebSerial.print("C");}
  else if (prevodilac=="-**")  
    {Serial.print("D");
    WebSerial.print("D");}
  else if (prevodilac=="*")  
    {Serial.print("E");
    WebSerial.print("E");}  
  else if (prevodilac=="**-*")  
    {Serial.print("F");
    WebSerial.print("F");}
  else if (prevodilac=="--*")  
    {Serial.print("G");
    WebSerial.print("G");}
  else if (prevodilac=="****")  
    {Serial.print("H");
    WebSerial.print("H");}
  else if (prevodilac=="**")  
    {Serial.print("I");
    WebSerial.print("I");}
  else if (prevodilac=="*---")  
    {Serial.print("J");
    WebSerial.print("J");}
  else if (prevodilac=="-*-")  
    {Serial.print("K");
    WebSerial.print("K");}
  else if (prevodilac=="*-**")  
    {Serial.print("L");
    WebSerial.print("L");}
  else if (prevodilac=="--")  
    {Serial.print("M");
    WebSerial.print("M");}
  else if (prevodilac=="-*")  
    {Serial.print("N");
    WebSerial.print("N");}
  else if (prevodilac=="---")  
    {Serial.print("O");
    WebSerial.print("O");}
  else if (prevodilac=="*--*")  
    {Serial.print("P");
    WebSerial.print("P");}
  else if (prevodilac=="--*-")  
    {Serial.print("Q");
    WebSerial.print("Q");}
  else if (prevodilac=="*-*")  
    {Serial.print("R");
    WebSerial.print("R");}
  else if (prevodilac=="***")  
    {Serial.print("S");
    WebSerial.print("S");}
  else if (prevodilac=="-")  
    {Serial.print("T");
    WebSerial.print("T");}
  else if (prevodilac=="**-")  
    {Serial.print("U");
    WebSerial.print("U");}
  else if (prevodilac=="***-")  
    {Serial.print("V");
    WebSerial.print("V");}
  else if (prevodilac=="*--")  
    {Serial.print("W");
    WebSerial.print("W");}
  else if (prevodilac=="-**-")  
    {Serial.print("X");
    WebSerial.print("X");}
  else if (prevodilac=="-*--")  
    {Serial.print("Y");
    WebSerial.print("Y");}
  else if (prevodilac=="--**")  
    {Serial.print("Z");
    WebSerial.print("Z");}

  else if (prevodilac=="*----")  
    {Serial.print("1");
    WebSerial.print("1");}
  else if (prevodilac=="**---")  
    {Serial.print("2");
    WebSerial.print("2");}
  else if (prevodilac=="***--")  
    {Serial.print("3");
    WebSerial.print("3");}
  else if (prevodilac=="****-")  
    {Serial.print("4");
    WebSerial.print("4");}
  else if (prevodilac=="*****")  
    {Serial.print("5");
    WebSerial.print("5");}
  else if (prevodilac=="-****")
    {Serial.print("6");
    WebSerial.print("6");}
  else if (prevodilac=="--***")  
    {Serial.print("7");
    WebSerial.print("7");}
  else if (prevodilac=="---**")  
    {Serial.print("8");
    WebSerial.print("8");}
  else if (prevodilac=="----*")  
    {Serial.print("9");
    WebSerial.print("9");}
  else if (prevodilac=="-----")  
    {Serial.print("0");
    WebSerial.print("0");}
  else if (prevodilac=="******")
    {Serial.print("_");
    WebSerial.print(" ");}
    
  prevodilac=""; 
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    pinMode(buttonPin, INPUT);
    pinMode(led, OUTPUT);
    pinMode(buz, OUTPUT);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    // WebSerial is accessible at "<IP Address>/webserial" in browser
    WebSerial.begin(&server);
    /* Attach Message Callback */
    WebSerial.msgCallback(recvMsg);
    server.begin();
}

void loop() {
  if (!webCode.isEmpty()){
    String2Morse();
    webCode = "";
    Serial.println();
  }

    buttonState = digitalRead(buttonPin);

  
  
  if (buttonState && lastButtonState)       // basic state machine depending on the state of the signal from the button
  {
    ++signal_length;       
    if (signal_length<2*pause_value)        //this help to notice that there is a change in the signal length aka that its not a dot anymore but a dash
    {                                       // best use for the measuring of signal_length would be use of the millis() but this was used  for simplicity 
    tone(buz, 1500) ;
    }
    else
    {
      tone(buz, 1000) ;
      }
  }
  else if(!buttonState && lastButtonState)          //this part of the code happens when the button is released and it send either * or - into the buffer
  {
     
     if (signal_length>50 && signal_length<2*pause_value )
     {
       serialMorse =  serialMorse + serialDot;
     } 
      else if (signal_length>2*pause_value)
      {
        serialMorse = serialMorse +  serialDash;
      }
    signal_length=0; 
    digitalWrite(13, LOW); 
    noTone(buz); 
  }
  else if(buttonState && !lastButtonState)          // this part happens when the button is pressed and its use to reset several values
  {
    pause=0;
    digitalWrite(13, HIGH);  
    cheker = true;
    linecheker = true;
  }
  else if (!buttonState && !lastButtonState)
  {  
    ++pause;
    if (( pause>3*pause_value ) && (cheker))
    { 
      printaj(serialMorse);
      cheker = false;
      serialMorse = "";
    }
    // if ((pause>15*pause_value) && (linecheker))
    // {
    //   Serial.println();
    //   linecheker = false;
    // }
  }
  lastButtonState=buttonState;
  delay(1);
}
