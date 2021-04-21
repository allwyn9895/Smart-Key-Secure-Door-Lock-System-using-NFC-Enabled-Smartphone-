
///SendTextMessage()
///this function is to send a sms
void locktextmessage()
{
  Serial.println("locktextmessage function");
 /*
  mySerial.println("AT+CMGF=1");    //Because we want to send the SMS in text mode
  delay(200);
  mySerial.println("AT+CMGS=\"+918105922180\"\r");// change to the phone number you using 
  delay(200);
  mySerial.println("DOOR LOCKED");//the content of the message
  delay(300);
  mySerial.println((char)26);//the ASCII code of the ctrl+z is 26
  delay(200);
  */
}

void unlocktextmessage()
{
  Serial.println("unlocktextmessage function");
  /*
 mySerial.println("AT+CMGF=1");    //Because we want to send the SMS in text mode
  delay(200);
  mySerial.println("AT+CMGS=\"+918105922180\"\r");// change to the phone number you using 
  delay(200);
  mySerial.println("DOOR UNLOCKED");//the content of the message
  delay(300);
  mySerial.println((char)26);//the ASCII code of the ctrl+z is 26
  delay(200);
  */
}

void wrongtextmessage()
{
  Serial.println("Unauthorizationmessage function");
  /*
  mySerial.println("AT+CMGF=1");    //Because we want to send the SMS in text mode
  delay(200);
  mySerial.println("AT+CMGS=\"+918105922180\"\r");// change to the phone number you using 
  delay(200);
  mySerial.println("Unauthorized user");//the content of the message
  delay(300);
  mySerial.println((char)26);//the ASCII code of the ctrl+z is 26
  delay(200);
 */ 
}
