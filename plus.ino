#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h> 
#include <time.h>
#include <ArduinoJson.h>
#include "ASCFont.h"  //영어폰트  
#include "KSFont.h"   //한글폰트

const char *ssid = "iPhone (253)";  // 와이파이 이름
const char *pass = "km0218**";      // 와이파이 비밀번호
//const char *ssid = "U+Net2071";  // 와이파이 이름
//const char *pass = "27316182M#";      // 와이파이 비밀번호
const char *thingId = "tft_lcd";          // 사물 이름 (thing ID) 
const char *host = "a1yxvsjof87e7l-ats.iot.ap-northeast-2.amazonaws.com"; // AWS IoT Core 주소

String value1;
String value4;
String value6;
String One = "1";
String Clear = "clear";
int lcdNum =0;

//한글 출력 변수 
byte HANFontImage[32] = {0, };
String inputString;
String inputString2;
String inputString3;


// 사물 인증서 (파일 이름: xxxxxxxxxx-certificate.pem.crt)
const char cert_str[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUKN2ANXsijXszmog42nLReVdvv4QwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIzMDUwODA0NTEz
NFoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMk/+t7fPI0Z1rIOJSDw
Q1S3wwVCQauNIYzbHkD2aa4rkk3d+9NKWCWbahqOTUD+cMqefA8shf2yZozhX26d
phh3hkTYCnUL43za4fV4y30R8RQDecDuw9zl9Brsvfe4N+bytt9fsZh65qQ3s8eW
mTn8/SbLXBnZT+L9Z5KYEQLgJGfMrwbYedL9usl501FMCVLyndSLOIVu5KMlR2TT
7NH4bNMJ67cdbwimQ9CmYTrnzL7OsL/JVooCKJmMBe/BZo2uZdVr3HUwYfHHIHsi
ZV8u7XrjVilC20SkjnXrh5b8SNBhFbK3YQngEqdebMKYz99seh/vAIPoHk6h22f0
DwkCAwEAAaNgMF4wHwYDVR0jBBgwFoAUqU33QXf4ioWQYQj2R0QZbGPrumswHQYD
VR0OBBYEFD9SG51eiT6KEeqRKeVjwuj/lHkbMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCwciErS7Ltr94VVm3V7E1g9yr5
vs7ieLIL5euGO1RQ8tHGU/7JBAWRFvpOYBk5Af1bPXamnpAlvz4UteQ2oQo8CL08
QIW18kOcbYNL/+QSOK6MQlg7OeQOqT2X0Rh0oZF+CPU6S4wXKmZpozBknOZiAJGK
Dnwx6bmz+a5MGYJuN5dYEbVx7dc9ELMyd3jenP0vJRBbxrreQho37jJsp2Twj97a
qbVROyDSoruuU8UjwRloBwTmQvC44PtOHBNBWkzlTh3J2w9YxBS8yeXCJ16Juqqr
LeG/kSA3DpHuFCSS0LmyBU+xEnbp677YimhFtsq5RzdhVjo02buOWTtq1wtx
-----END CERTIFICATE-----
)EOF";
// 사물 인증서 프라이빗 키 (파일 이름: xxxxxxxxxx-private.pem.key)
const char key_str[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAyT/63t88jRnWsg4lIPBDVLfDBUJBq40hjNseQPZpriuSTd37
00pYJZtqGo5NQP5wyp58DyyF/bJmjOFfbp2mGHeGRNgKdQvjfNrh9XjLfRHxFAN5
wO7D3OX0Guy997g35vK231+xmHrmpDezx5aZOfz9JstcGdlP4v1nkpgRAuAkZ8yv
Bth50v26yXnTUUwJUvKd1Is4hW7koyVHZNPs0fhs0wnrtx1vCKZD0KZhOufMvs6w
v8lWigIomYwF78Fmja5l1WvcdTBh8ccgeyJlXy7teuNWKULbRKSOdeuHlvxI0GEV
srdhCeASp15swpjP32x6H+8Ag+geTqHbZ/QPCQIDAQABAoIBAQCCstx4Vb57XKaE
KI+QXrk7kcRD7A2+HgAF/GAfjGiBxqZTj7D2PbgVZGN6L6SYayZRUK/9Iss6Qdw7
7joOGrA9/5Hhr/TKoxfwhC5vPy3YYgiRGNi/pdDp6yWnPsz4zljv0f1WAE3UWyzi
xZIqMvH8KQM3aKa92tX48t2K5NtXY5Y2MJrNAf4cSe3bQ0AMzMb7x2hE5F8XO/WW
hF5eOCMm4Krpmb1VdqgQOHh97JtivRs27hX8Vn6ydFT412PyC5qmxRrgYJLjIJO6
CXvqoeWF/5Zgim+M78l4m6LuUhB9nZBTxTaKAQQd+sPHngJbNI4PZKOEr2LrohnA
o2qmXOWhAoGBAPYpIhv7LSrC+OKkP4q+RTxnQFSdoX87yHylchnVPXGHIoX62YEV
9b8PEfmE3dJrmTtefdmYjhrvf1NzcJnRetGiPg1Elmnb7VW0osV1hXXyDySlix5c
Z7zXy4JQ4QdGRMYyG8ejTwr54Y+O5OAbRg0IAf3nxZom+EYmhy1/zM8FAoGBANFL
StmBN354HCstjrXyQlwg78rnISG+B3q66Y7dMv1D3Am9kFu3vAawvMPmZGFXmSnE
DoEUXcBU2qCe9yYMvUjkFAib1QHJqOur16Gx0QvRCNqfzvLc5S9iaV5FOdtFuLap
cutBJvqoAXwdvrgiCvkw7F/YiKC5XZG4LLQs8Nc1AoGACbK5K00MDIE9+P/rmPXC
GI0g1bSYJkEetvp1slraXtyqGYk2hIVu9yYK2T/I1X9zvAkPAEGoZ5tD8u+7YfQE
2LmBpFgtbOJDSXsiZpEovurYeeMjxgBx/diqpem10+mK0BwtSAJBHPeXUWaZ0dKB
QgYsveohuN8MLQdbkAlW8lkCgYEAkOF1DAIGH1cX8M/VpZ/xTgNC24uKBOieFtiC
y3HWVTn/fQKrhsI2t87qrRW00Smpjh75B2PIzlYvDdddMQrKkUXJlHgDSPyHIbVQ
TM9h7bMjVOwhfz9oq5eNZ0O2nFK0XkYIllAAoq1gccHJf3+ZZwz15Bdp5RDMdA4x
a/xcMC0CgYEA7/T2Cg3yxPmVgJobob3mcV9F60aY0SNaObpzZYmoj3lfgKhXqvpt
X3dcAFAnB6/7a7BXMEyPMa/7NrK1A194iqiFBH/c1/qxcuhkyT+ayj6hk7lsj6Q+
QyR/1BcNVVJnpcS6RXH842lMKC0XZqvmWPTsAvkcnE/KH01HMYaHWbM= 
-----END RSA PRIVATE KEY-----
)EOF";
// Amazon Trust Services(ATS) 엔드포인트 CA 인증서 (서버인증 > "RSA 2048비트 키: Amazon Root CA 1" 다운로드)
const char ca_str[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5

-----END CERTIFICATE-----
)EOF";


// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     D1
#define TFT_RST    D0  // you can also connect this to the Arduino reset
                       // in which case, set this #define pin to -1!
#define TFT_DC     D2


// For 1.44" and 1.8" TFT with ST7735 use
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);


String prev_value_1;
String prev_value_4;



byte *getHAN_font(byte HAN1, byte HAN2, byte HAN3){

  const byte cho[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 1, 2, 4, 4, 4, 2, 1, 3, 0 };
  const byte cho2[] = { 0, 5, 5, 5, 5, 5, 5, 5, 5, 6, 7, 7, 7, 6, 6, 7, 7, 7, 6, 6, 7, 5 };
  const byte jong[] = { 0, 0, 2, 0, 2, 1, 2, 1, 2, 3, 0, 2, 1, 3, 3, 1, 2, 1, 3, 3, 1, 1 };

  uint16_t utf16;
  byte first, mid, last;
  byte firstType, midType, lastType;
  byte i;
  byte *pB, *pF;

  /*------------------------------
    UTF-8 을 UTF-16으로 변환한다.

    UTF-8 1110xxxx 10xxxxxx 10xxxxxx
  */------------------------------
  utf16 = (HAN1 & 0x0f) << 12 | (HAN2 & 0x3f) << 6 | HAN3 & 0x3f;

  /*------------------------------
    초,중,종성 코드를 분리해 낸다.

    unicode = {[(초성 * 21) + 중성] * 28}+ 종성 + 0xAC00

          0   1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 
    초성 ㄱ   ㄲ ㄴ ㄷ ㄸ ㄹ ㅁ ㅂ ㅃ ㅅ ㅆ ㅇ ㅈ ㅉ ㅊ ㅋ ㅌ ㅍ ㅎ
    중성 ㅏ   ㅐ ㅑ ㅒ ㅓ ㅔ ㅕ ㅖ ㅗ ㅘ ㅙ ㅚ ㅛ ㅜ ㅝ ㅞ ㅟ ㅠ ㅡ ㅢ ㅣ  
    종성 없음 ㄱ ㄲ ㄳ ㄴ ㄵ ㄶ ㄷ ㄹ ㄺ ㄻ ㄼ ㄽ ㄾ ㄿ ㅀ ㅁ ㅂ ㅄ ㅅ ㅆ ㅇ ㅈ ㅊ ㅋ ㅌ ㅍ ㅎ
  ------------------------------*/
  utf16 -= 0xac00;
  last = utf16 % 28;
  utf16 /= 28;
  mid = utf16 % 21;
  first = utf16 / 21;

  first++;
  mid++;

  /*------------------------------
    초,중,종성 해당 폰트 타입(벌)을 결정한다.
  ------------------------------*/

  /*
   초성 19자:ㄱㄲㄴㄷㄸㄹㅁㅂㅃㅅㅆㅇㅈㅉㅊㅋㅌㅍㅎ
   중성 21자:ㅏㅐㅑㅒㅓㅔㅕㅖㅗㅘㅙㅚㅛㅜㅝㅞㅟㅠㅡㅢㅣ
   종성 27자:ㄱㄲㄳㄴㄵㄶㄷㄹㄺㄻㄼㄽㄾㄿㅀㅁㅂㅄㅆㅇㅈㅊㅋㅌㅍㅎ

   초성
      초성 1벌 : 받침없는 'ㅏㅐㅑㅒㅓㅔㅕㅖㅣ' 와 결합
      초성 2벌 : 받침없는 'ㅗㅛㅡ'
      초성 3벌 : 받침없는 'ㅜㅠ'
      초성 4벌 : 받침없는 'ㅘㅙㅚㅢ'
      초성 5벌 : 받침없는 'ㅝㅞㅟ'
      초성 6벌 : 받침있는 'ㅏㅐㅑㅒㅓㅔㅕㅖㅣ' 와 결합
      초성 7벌 : 받침있는 'ㅗㅛㅜㅠㅡ'
      초성 8벌 : 받침있는 'ㅘㅙㅚㅢㅝㅞㅟ'

   중성
      중성 1벌 : 받침없는 'ㄱㅋ' 와 결합
      중성 2벌 : 받침없는 'ㄱㅋ' 이외의 자음
      중성 3벌 : 받침있는 'ㄱㅋ' 와 결합
      중성 4벌 : 받침있는 'ㄱㅋ' 이외의 자음

   종성
      종성 1벌 : 중성 'ㅏㅑㅘ' 와 결합
      종성 2벌 : 중성 'ㅓㅕㅚㅝㅟㅢㅣ'
      종성 3벌 : 중성 'ㅐㅒㅔㅖㅙㅞ'
      종성 4벌 : 중성 'ㅗㅛㅜㅠㅡ'

  */
  if(!last){  //받침 없는 경우
    firstType = cho[mid];
    if(first == 1 || first == 24) midType = 0;
    else midType = 1;
  }
  else{       //받침 있는 경우
    firstType = cho2[mid];
    if(first == 1 || first == 24) midType = 2;
    else midType = 3;
    lastType = jong[mid];
  }
  memset(HANFontImage, 0, 32);

  //초성 
  pB = HANFontImage;
  pF = (byte*)KSFont + (firstType*20 + first)*32;

  i = 32;
  while(i--) *pB++ = pgm_read_byte(pF++); 

  //중성
  pB = HANFontImage;
  pF = (byte*)KSFont + (8*20 + midType*22 + mid)*32;

  i = 32;
  while(i--) *pB++ |= pgm_read_byte(pF++); 

  //종성
  if(last){
    pB = HANFontImage;
    pF = (byte*)KSFont + (8*20 + 4*22 + lastType*28 + last)*32;

    i = 32;
    while(i--) *pB++ |= pgm_read_byte(pF++); 
  }

  return HANFontImage;
}


void matrixPrint(int XPOS,int YPOS,char *pChar){
  byte rg = 3;   //<b1> red, <b0> green
  byte *pFs;
  byte i, b;
  byte c, c2, c3;

  while(*pChar){ 
    c = *(byte*)pChar++;

    // /r 개행 문자인지 확인
    if(c == 0x2F && *(byte*)pChar++ == 0x72){
      XPOS = 0;
      YPOS = YPOS+16;
    }
    //---------- 한글 ---------
    else if(c >= 0x80){
      c2 = *(byte*)pChar++;
      c3 = *(byte*)pChar++;
      
      pFs = getHAN_font(c, c2, c3);
      tft.drawBitmap(XPOS, YPOS,  pFs, 16, 16, 1);
      XPOS = XPOS+16;
      if(XPOS > 240){
        XPOS = 0;
        YPOS = YPOS+16;
      }
    }
    //---------- ASCII ---------
    else{
      pFs = (byte*)ASCfontSet + ((byte)c - 0x20) * 16;
      tft.drawBitmap(XPOS, YPOS,  pFs, 8, 16, 1);
      XPOS = XPOS+8;
      if(XPOS > 240){
        XPOS = 0;
        YPOS = YPOS+16;
      }   
    }   
  }  
} 
bool mqttMessageReceived = false;  // MQTT 메시지 수신 여부를 저장하는 변수


void callback(char* topic, byte* payload, unsigned int length) {
 
/////////////////////////////////////////////////////////////////////////////////////////////
// 받은 MQTT 메시지를 문자열로 변환
  String message1 = "";
  for (int i = 0; i < length; i++) {
    message1 += (char)payload[i];
  }

  // JSON 데이터 파싱
  DynamicJsonDocument jsonDoc(200);
  DeserializationError error = deserializeJson(jsonDoc, message1);
  if (error) {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.c_str());
    return;
  }


  // 수신된 주제(topic)에 따라 메시지 처리
  if (strcmp(topic, "intopic1") == 0) {
    const char* value2 = jsonDoc["message2"];//이름
    const char* value3 = jsonDoc["message3"];//가격
    value1= String(value2);//이름 
    value4= String(value3);//가격

    tft.fillScreen(ST77XX_BLACK);//초기화  

    displayString(value1 ,value4);  // 문자열을 TFT LCD에 출력합니다.
    delay(1000);  // 1초 동안 대기합니다.
  
    // 여기에서 필요한 로직을 구현합니다.

    
  } else if (strcmp(topic, "topic/Rec") == 0) {
    const char* value5 = jsonDoc["message"];//위치
    
    value6= String(value5);//가격
    clear_play(value5);
    delay(1000);  // 1초 동안 대기합니다.
  

  }
}


X509List ca(ca_str);
X509List cert(cert_str);
PrivateKey key(key_str);
WiFiClientSecure wifiClient;
PubSubClient client(host, 8883, callback, wifiClient); //set  MQTT port number to 8883 as per //standard

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(thingId)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("intopic1");
      client.subscribe("topic/Rec");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      char buf[512];
      wifiClient.getLastSSLError(buf,512);
      Serial.print("WiFiClientSecure SSL error: ");
      Serial.println(buf);

      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// Set time via NTP, as required for x.509 validation
void setClock() {
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
}

//// For the breakout, you can use any 2 or 3 pins
//// These pins will also work for the 1.8" TFT shield
//#define TFT_CS     D1
//#define TFT_RST    D0  // you can also connect this to the Arduino reset
//                       // in which case, set this #define pin to -1!
//#define TFT_DC     D2
//
//
//// For 1.44" and 1.8" TFT with ST7735 use
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

float p = 3.1415926;

void setup(void) {
  //tft 먼저 초기화 
  // Use this initializer if you're using a 1.8" TFT
  //tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  // large block of text
  //tft.fillScreen(ST77XX_BLACK);
  //delay(500);

  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  Serial.println();

   // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  wifiClient.setTrustAnchors(&ca);
  wifiClient.setClientRSACert(&cert, &key);
  Serial.println("Certifications and key are set");

  setClock();
  //client.setServer(host, 8883);
  client.setCallback(callback);

  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
   // 화면을 가로로 설정 (시계 방향으로 회전)
  tft.setRotation(3);
  // large block of text
  tft.fillScreen(ST77XX_WHITE);
  delay(500);
  String receivedString = "Hello, World!";  // 받은 문자열을 예시로 설정합니다.
}


long lastMsg = 0;
char msg[50];
int value = 0;

bool isBlink = false;

void loop() {
//  PrintHello();
//  delay(500);
  if (!client.connected()) {
    reconnect();
    delay(500);
  }
  //client.setCallback(callback);
  client.loop();
//  PrintHello();
//  delay(5000);
  long now = millis();
  if (now - lastMsg > 10000) {
    lastMsg = now;
    ++value;    //인덱스
    //snprintf (msg, 75, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    //client.publish("outTopic", msg);
    Serial.print("Heap: "); 
    Serial.println(ESP.getFreeHeap()); //Low heap can cause problems
//    String receivedString = "Hello, World!";  // 받은 문자열을 예시로 설정합니다.
//    displayString(value1,value4);  // 문자열을 TFT LCD에 출력합니다.
//    delay(1000);  // 1초 동안 대기합니다.
  }
  if(isBlink) {
    displayString(value1,value4);  // 문자열을 TFT LCD에 출력합니다.
    delay(1000);  // 1초 동안 대기합니다.
    displayString2(value1,value4);
    delay(1000);  // 1초 동안 대기합니다.
  }
  //PrintHello();
  //delay(5000);
  //yield();
}


void PrintHello()
{
  tft.drawRect(3, 6, 155, 120, 0xffff);
  tft.drawLine(3, 35, 155, 35, 0xffff);
  tft.fillRect(3, 6, 155, 35, ST77XX_GREEN);
}

void displayString(String str,String str2) {
  tft.setCursor(50, 15);  // 문자열을 출력할 위치를 설정합니다. 필요에 따라 조정하세요.
  inputString=str;
  //inputString2="왜이래";
  //tft.invertDisplay(true);
  tft.fillScreen(ST77XX_WHITE);
  tft.drawRect(3, 6, 155, 120, ST77XX_BLACK);
  tft.drawLine(3, 35, 155, 35, ST77XX_BLACK);
  char paramChar[inputString.length()+1];
  inputString.toCharArray(paramChar, inputString.length() + 1);
  matrixPrint(40, 15,paramChar);
  //tft.println(str);  // 문자열을 TFT LCD에 출력합니다.
 
  tft.setCursor(60, 50);
  tft.setTextColor(ST77XX_BLACK);
  tft.print(str2);
  inputString2="원";
  char paramChar2[inputString2.length()+1];
  inputString2.toCharArray(paramChar2, inputString2.length() + 1);
  matrixPrint(90, 50,paramChar2);

  //tft.print("  won");
}

void displayString2(String str,String str2) {
  tft.setCursor(50, 15);  // 문자열을 출력할 위치를 설정합니다. 필요에 따라 조정하세요.
  inputString=str;
  tft.fillScreen(ST77XX_GREEN);
  tft.drawRect(3, 6, 155, 120, ST77XX_BLACK);
  tft.drawLine(3, 35, 155, 35, ST77XX_BLACK);
  char paramChar[inputString.length()+1];
  inputString.toCharArray(paramChar, inputString.length() + 1);
  matrixPrint(40, 15,paramChar);
  //tft.println(str);  // 문자열을 TFT LCD에 출력합니다.
 
  tft.setCursor(60, 50);
  tft.setTextColor(ST77XX_BLACK);
  tft.print(str2);
  inputString2="원";
  char paramChar2[inputString2.length()+1];
  inputString2.toCharArray(paramChar2, inputString2.length() + 1);
  matrixPrint(90, 50,paramChar2);

  //tft.print("  won");
}

void clear_play(String str3)
{
  if (str3 == Clear) {
     displayString(value1,value4);
   // tft.fillScreen(ST77XX_BLACK);//초기화
    //delay(5000);  // 1초 동안 대기합니다.
    }

  if(str3 == One) {
    isBlink = true;
  } else {
    isBlink = false;
  }

}
