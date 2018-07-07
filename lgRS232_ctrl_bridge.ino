#include <IRremote.h>

const uint8_t lencodes = 45;

uint32_t IRcodes[] = {551489775, //power
                      551528790, //green
                      551488755, //av mode
                      551538735, //input
                      551546895, //tv
                      551520375, //1
                      551504055, //2
                      551536695, //3
                      551495895, //4
                      551528535, //5
                      551512215, //6
                      551544855, //7
                      551491815, //8
                      551524455, //9
                      551498445, //-
                      551487735, //0
                      551508135, //qview
                      551502015, //vol+
                      551534655, //vol-
                      551516295, //fav
                      551525985, //ratio
                      551522415, //mute
                      551485695, //ch+
                      551518335, //ch-
                      551540010, //guide
                      551535165, //home
                      551527005, //qmenu
                      551486205, //up
                      551542815, //left
                      551494365, //center
                      551510175, //right
                      551518845, //down
                      551490795, //back
                      551507370, //info
                      551541285, //exit
                      551505585, //red
                      551521905, //green
                      551536185, //yellow
                      551519865, //blue
                      551521650, //stop
                      551489010, //play
                      551509410, //pause
                      551547150, //rew
                      551514510, //fwd
                      551517825
                     }; //simplink
const String ctrlWords[] =    {"mc 00 08",
                               "mc 00 95",
                               "mc 00 98",
                               "mc 00 0B",
                               "mc 00 0F",
                               "mc 00 11",
                               "mc 00 12",
                               "mc 00 13",
                               "mc 00 14",
                               "mc 00 15",
                               "mc 00 16",
                               "mc 00 17",
                               "mc 00 18",
                               "mc 00 19",
                               "mc 00 4C",
                               "mc 00 10",
                               "mc 00 00",
                               "mc 00 02",
                               "mc 00 03",
                               "mc 00 1E",
                               "mc 00 79",
                               "mc 00 09",
                               "mc 00 00",
                               "mc 00 01",
                               "mc 00 AB",
                               "mc 00 43",
                               "mc 00 45",
                               "mc 00 40",
                               "mc 00 07",
                               "mc 00 44",
                               "mc 00 06",
                               "mc 00 41",
                               "mc 00 28",
                               "mc 00 0A",
                               "mc 00 5B",
                               "mc 00 72",
                               "mc 00 71",
                               "mc 00 63",
                               "mc 00 61",
                               "mc 00 B1",
                               "mc 00 B0",
                               "mc 00 BA",
                               "mc 00 8F",
                               "mc 00 8E",
                               "mc 00 7E"
                              };


int RECV_PIN = 11;
int BUTTON_PIN = 12;
int STATUS_PIN = 13;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;
const uint8_t ledPin = 13;
bool flag = true;
void blk(uint16_t del) {
  digitalWrite(ledPin, HIGH);
  delay(del);
  digitalWrite(ledPin, LOW);
  delay(del);
}

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(ledPin, OUTPUT);
}
bool powerStatus = false;
uint32_t lcode;
uint32_t lcodeTimeout;
uint8_t timeoutAvailableFlag = false;
uint8_t preValid = false;
void loop() {
  if (irrecv.decode(&results) & results.decode_type != 65535) {
    if (results.value != REPEAT)
    {
      lcode = results.value;
    }
    if (results.value == REPEAT && preValid)
    {
      lcodeTimeout = millis() + 600;
      timeoutAvailableFlag = true;
    }
    int i = 0;
    for (; i < lencodes; i++) {
      if (IRcodes[i] == lcode) {
        preValid = true;
        if (lcode == 551489775) { //If it's a turn on code
          powerStatus = !powerStatus;
          powerStatus ? Serial.print("ka 00 01") : Serial.print("ka 00 00");
          Serial.write(0x0D);
          delay(1000);
          break;
        } else { //another invalid code
          Serial.print(ctrlWords[i]);
          Serial.write(0x0D);
          if (lcode == 551502015 || lcode == 551534655) {
            break;
          }
          else {
            delay(150);
          }
          if (results.value == REPEAT)
          {
            delay(150);
          }
          break;
        }
      }
    }
    irrecv.resume(); // resume receiver
  }
  if (millis() > lcodeTimeout && timeoutAvailableFlag)
  {
    Serial.println("timeout");
    timeoutAvailableFlag = false;
    preValid = false;
    lcode = 0;
  }
}
