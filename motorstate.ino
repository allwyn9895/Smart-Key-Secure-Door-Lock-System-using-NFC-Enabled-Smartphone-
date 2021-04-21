void motorstate(int state) 
{
 
   if(state==1)
   {
           Serial.println("locking: moving to 180");
           servo.attach(8) ; 
            if(angle==180)
                  servo.detach();
               else{
                  for(angle = 0; angle < 180; angle++)    
                {                                
                  servo.write(angle);           
                 delay(10);    
                 }    servo.detach();
                 
        }
        locktextmessage();
   }
  else if(state==2){
      
            Serial.println("unlocking: moving bACK TO 0");
            servo.attach(8); 
            if(angle==0)
                  servo.detach();
               else{
            for(angle = 180; angle > 0; angle--)    
          {                                
              servo.write(angle);           
             delay(10);    
          }
          servo.detach();
  }
  unlocktextmessage();
  }
}
