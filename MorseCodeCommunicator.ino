
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

AsyncWebServer server(80);

const char* ssid = "P 802"; // Your WiFi SSID. This is our WiFi SSID and PW, when using this code pls change it to your WiFi!
const char* password = "123456789"; // Your WiFi Password

//pin for button, led and buzzer
const int buttonPin = D3;   
const int led = D4;
const int buz = D5;

int ledState = HIGH;       
int buttonState = LOW;               
int lastButtonState = LOW;  

int pause_value = 200;  // change this value according to your button-pushing speed
long signal_length = 0;
long pause = 0;

// morse code, dash and dot for sending data from arduino to webserver
String serialMorse = "";
String serialDash = "-";
String serialDot = "*";

boolean cheker = false;


long lastDebounceTime = 0;  
long debounceDelay = 50; // Debounce between button push

String webCode = ""; // morse code for sending from webserver to arduino

int len = 0;
char ch;
char new_char;
int unit_delay = 100;

/* Message callback of WebSerial */
void recvMsg(uint8_t *data, size_t len){
  WebSerial.println();
  WebSerial.println("Sending data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
  }
  webCode = d; // Asign the sent data to webCode to encode
  WebSerial.println(d);
}

// Function for dot, dash LED + buzzer
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

void error(){
  Serial.println("Unknown character!");
  digitalWrite(buz, HIGH);
  delay(unit_delay*5);
  digitalWrite(buz, LOW);
  delay(unit_delay);
}
// Function for dot and dash of each letter and number
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

void period(){
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}

void question(){
  dot();
  delay(unit_delay);
  dot();
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

void comma(){
  dash();
  delay(unit_delay);
  dash();
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

void exclamation(){
  dash();
  delay(unit_delay);  
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dot();
  delay(unit_delay);
  dash();
  delay(unit_delay);
  dash();
  delay(unit_delay*3);
}

void unknown(){
  error();
}

// Morse function: this func will call the equivalent function for each letter, number or special symbols

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
  else if (ch == '.')
  {
    period();
    Serial.print(" ");
  }
  else if (ch == '?')
  {
    question();
    Serial.print(" ");
  }
  else if (ch == ',')
  {
    comma();
    Serial.print(" ");
  }
  else if (ch == '!')
  {
    exclamation();
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
    unknown();
  }
}

// This function will iter through each letter of a msg and call morse for each of them
void String2Morse() {
  len = webCode.length();
  for (int i = 0; i < len; i++) {
    ch = webCode.charAt(i);
    morse();
  }
}

void printMorse(String morsecode)   
{                                 //compare morse string to known morse values and print out the letter or a number 
                                  //the code is written based on the international morse code. However, we added special pattern for space and newline.
  if (morsecode=="*-"){
    Serial.print("A");
    WebSerial.print("A");
  }
  else if (morsecode=="-***")  
    {Serial.print("B");
    WebSerial.print("B");}
  else if (morsecode=="-*-*")  
    {Serial.print("C");
    WebSerial.print("C");}
  else if (morsecode=="-**")  
    {Serial.print("D");
    WebSerial.print("D");}
  else if (morsecode=="*")  
    {Serial.print("E");
    WebSerial.print("E");}  
  else if (morsecode=="**-*")  
    {Serial.print("F");
    WebSerial.print("F");}
  else if (morsecode=="--*")  
    {Serial.print("G");
    WebSerial.print("G");}
  else if (morsecode=="****")  
    {Serial.print("H");
    WebSerial.print("H");}
  else if (morsecode=="**")  
    {Serial.print("I");
    WebSerial.print("I");}
  else if (morsecode=="*---")  
    {Serial.print("J");
    WebSerial.print("J");}
  else if (morsecode=="-*-")  
    {Serial.print("K");
    WebSerial.print("K");}
  else if (morsecode=="*-**")  
    {Serial.print("L");
    WebSerial.print("L");}
  else if (morsecode=="--")  
    {Serial.print("M");
    WebSerial.print("M");}
  else if (morsecode=="-*")  
    {Serial.print("N");
    WebSerial.print("N");}
  else if (morsecode=="---")  
    {Serial.print("O");
    WebSerial.print("O");}
  else if (morsecode=="*--*")  
    {Serial.print("P");
    WebSerial.print("P");}
  else if (morsecode=="--*-")  
    {Serial.print("Q");
    WebSerial.print("Q");}
  else if (morsecode=="*-*")  
    {Serial.print("R");
    WebSerial.print("R");}
  else if (morsecode=="***")  
    {Serial.print("S");
    WebSerial.print("S");}
  else if (morsecode=="-")  
    {Serial.print("T");
    WebSerial.print("T");}
  else if (morsecode=="**-")  
    {Serial.print("U");
    WebSerial.print("U");}
  else if (morsecode=="***-")  
    {Serial.print("V");
    WebSerial.print("V");}
  else if (morsecode=="*--")  
    {Serial.print("W");
    WebSerial.print("W");}
  else if (morsecode=="-**-")  
    {Serial.print("X");
    WebSerial.print("X");}
  else if (morsecode=="-*--")  
    {Serial.print("Y");
    WebSerial.print("Y");}
  else if (morsecode=="--**")  
    {Serial.print("Z");
    WebSerial.print("Z");}

  else if (morsecode=="*----")  
    {Serial.print("1");
    WebSerial.print("1");}
  else if (morsecode=="**---")  
    {Serial.print("2");
    WebSerial.print("2");}
  else if (morsecode=="***--")  
    {Serial.print("3");
    WebSerial.print("3");}
  else if (morsecode=="****-")  
    {Serial.print("4");
    WebSerial.print("4");}
  else if (morsecode=="*****")  
    {Serial.print("5");
    WebSerial.print("5");}
  else if (morsecode=="-****")
    {Serial.print("6");
    WebSerial.print("6");}
  else if (morsecode=="--***")  
    {Serial.print("7");
    WebSerial.print("7");}
  else if (morsecode=="---**")  
    {Serial.print("8");
    WebSerial.print("8");}
  else if (morsecode=="----*")  
    {Serial.print("9");
    WebSerial.print("9");}
  else if (morsecode=="-----")  
    {Serial.print("0");
    WebSerial.print("0");}
  else if (morsecode=="******")
    {Serial.print("_");
    WebSerial.print(" ");}
  else if (morsecode=="*-*-*-")
    {Serial.print(".");
    WebSerial.print(".");}
  else if (morsecode=="**--**")
    {Serial.print("?");
    WebSerial.print("?");}
  else if (morsecode=="--**--")
    {Serial.print(",");
    WebSerial.print(",");}
  else if (morsecode=="-*-*--")
    {Serial.print("!");
    WebSerial.print("!");}
  else if (morsecode=="*******")
    {Serial.println();
    Serial.println("New Line: ");
    WebSerial.println();
    WebSerial.println("New Line: ");}
    
  morsecode=""; 
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

  
  
  if (buttonState && lastButtonState)       //This happen when the button is held. 
  {
    ++signal_length;       
    if (signal_length<2*pause_value)        //this help to notice that there is a change in the signal length => its not a dot anymore but a dash
    {                                       
    tone(buz, 1500) ;
    }
    else
    {
      tone(buz, 1000) ;
      }
  }
  else if(!buttonState && lastButtonState)          //this part of the code happens when the button is released and it send either * or - into serialMorse
  {
     if (signal_length>50 && signal_length<2*pause_value )
     {
       serialMorse =  serialMorse + serialDot;
     } 
      else if (signal_length>2*pause_value)
      {
        serialMorse = serialMorse +  serialDash;
      }
    signal_length=0; // reset signal length for next use 
    noTone(buz); 
  }
  else if(buttonState && !lastButtonState)      // this part happens when the button is pressed. Reset pause and checker value for next use.
  {
    pause=0;
    cheker = true;
  }
  else if (!buttonState && !lastButtonState)        // this part happens after the button is released. 
  {  
    ++pause;
    if (( pause>3*pause_value ) && (cheker))
    { 
      printMorse(serialMorse);
      cheker = false;
      serialMorse = "";
    }
  }
  lastButtonState=buttonState;
  delay(1);
}
