#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#define lock 1
#define unlock 2

SoftwareSerial mySerial(10,11);
int angle=0;
int lockflag=0;
Servo servo;
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
int LED1 = 4;
int LED2 = 5;
int flag=0;
int tempflag=0;
String readmsg;
String onemsg;

void motorstate(int state) ;
void unlocktextmessage();
void locktextmessage();
//void unlocktextmessage();
void wrongtextmessage();
void ledees(int lstate);


void setup(void) {
  
  servo.attach(8);
  servo.write(angle);
  pinMode(LED2,OUTPUT);
  pinMode(LED1,OUTPUT);
  //pinMode(LED3,OUTPUT);
  mySerial.begin(9600);
  Serial.begin(9600);
 //test code to check gsm is fine or not
  mySerial.println("AT+CMGF=1");
  delay(100);
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(100);
  ledees(lockflag);
   //Serial.begin(9600);
  Serial.println("NDEF Reader");
  nfc.begin();
} 


void loop(void) {
  //ledees(lockflag);
  delay(1000);
  String msg = mySerial.readString();
  delay(1000);
  Serial.print(msg.substring(51, 56)); 
  delay(1000);
  Serial.print(msg);
 if(msg.substring(51, 52)=="1")
  {
      onemsg=msg;
  }
  if(msg.substring(51, 52)=="2")
  {
      readmsg=msg;
  }
   if(msg.substring(51, 52)=="3")
   { 
    readmsg="b";
    }
    if(msg.substring(51, 57)=="Allwyn")
   { 
    if(lockflag==0)
          {
            Serial.println("Locked");
          motorstate(lock);
          
          lockflag=1;
          ledees(lockflag);
          Serial.print(readmsg);
         
          
          delay(4000);
          
          }
          else if(lockflag==1)
          {
            Serial.println("Unlocked");
            motorstate(unlock);
          
            lockflag=0;
            ledees(lockflag);

            Serial.print(readmsg);
            delay(4000);
            
            }
  
  }
    
   
  if (mySerial.available()>0)
   Serial.write(mySerial.read());
  Serial.println("\nScan a NFC tag\n");

   delay(1000);
  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    //Serial.println(tag.getTagType());
    //Serial.print("UID: ");Serial.println(tag.getUidString());
  ledees(lockflag);
    if (tag.hasNdefMessage()) // every tag won't have a message
    {

      NdefMessage message = tag.getNdefMessage();
      Serial.print("\nThis NFC Tag contains an NDEF Message with ");
      Serial.print(message.getRecordCount());
      Serial.print(" NDEF Record");
      if (message.getRecordCount() != 1) 
      {
        Serial.print("s");
      }
      Serial.println(".");

      // cycle through the records, printing some info from each
      int recordCount = message.getRecordCount();
      for (int i = 0; i < recordCount; i++)
      {
        Serial.print("\nNDEF Record ");Serial.println(i+1);
        NdefRecord record = message.getRecord(i);
        // NdefRecord record = message[i]; // alternate syntax

        Serial.print("  TNF: ");Serial.println(record.getTnf());
        Serial.print("  Type: ");Serial.println(record.getType()); // will be "" for TNF_EMPTY

        // The TNF and Type should be used to determine how your application processes the payload
        // There's no generic processing for the payload, it's returned as a byte[]
        int payloadLength = record.getPayloadLength();
        byte payload[payloadLength];
        record.getPayload(payload);

        // Print the Hex and Printable Characters
        Serial.print("  Payload (HEX): ");
        PrintHexChar(payload, payloadLength);

        // Force the data into a String (might work depending on the content)
        // Real code should use smarter processing
        String payloadAsString = "";
        for (int c = 0; c < payloadLength; c++) 
        {
          payloadAsString += (char)payload[c];
        }
        Serial.print("  Payload (as String): ");
        Serial.println(payloadAsString);
      

if(onemsg.substring(51, 52)=="1")
{ 
  if(onemsg.substring(52, 56)==payloadAsString)
  {
  if(lockflag==0)
          {
            Serial.println("Locked");
          motorstate(lock);
          
          lockflag=1;
          ledees(lockflag);
          Serial.print(readmsg);
         
          
          delay(4000);
          
          }
          else if(lockflag==1)
          {
            Serial.println("Unlocked");
            motorstate(unlock);
          
            lockflag=0;
            ledees(lockflag);

            Serial.print(readmsg);
            delay(4000);
            
            }
   onemsg="a";
  
  }
}
  
 else 
 if(readmsg.substring(52, 56)==payloadAsString||msg.substring(51, 52)=="2")
  {
  //Serial.print(readmsg.substring(51, 56)); 
    Serial.print("gone to 2"); 
  if(readmsg.substring(52, 56)==payloadAsString||msg.substring(52, 56)==payloadAsString)
  {
      //readmsg=msg;
  if(lockflag==0)
          {
            //readmsg=msg;
            Serial.println("Locked");
          motorstate(lock);
          
          lockflag=1;
          ledees(lockflag);
          
      Serial.print(readmsg);   
          delay(4000);
          
          }
          else if(lockflag==1)
          {
            Serial.println("Unlocked");
            motorstate(unlock);
       Serial.print(readmsg);   
            lockflag=0;
            ledees(lockflag);

           
            delay(4000);
            
            }
          
  }

}

 
/*else if(msg.substring(51, 52)=="3")
 {
  Serial.print("Readmsg has been cleared");
    Serial.print("gone to 3"); 
     readmsg="b";
  }

  */
 else 
 if(payloadAsString=="2438"||payloadAsString=="5678"||payloadAsString=="9012")   //add another tag using or 
        {
          if(lockflag==0)
          {
            Serial.println("Locked");
          motorstate(lock);
          
          lockflag=1;
          ledees(lockflag);
          delay(4000);
          }
          else if(lockflag==1)
          {
            Serial.println("Unlocked");
            motorstate(unlock);
           
            lockflag=0;
            ledees(lockflag);
            delay(4000);
           
            }
        }

     else 
     if(tag.getUidString()=="D0 35 A3 7C")
        {  delay(100); 
          Serial.print(" Waiting for next tag to be read");
            
            delay(100); 
        }
       
        
        else 
       if(payloadAsString!="0000")
        {
           delay(100); 
          Serial.println("You dont have access!!");
          wrongtextmessage();
           delay(100); 
          }
        
        
      }
        // id is probably blank and will return ""
      // String uid = record.getId();
        //if (uid != "") {
        // Serial.print("  ID: ");Serial.println(uid);
        
      }
    
}
  delay(1000);
}




