void ledees(int lstate)
{
if(lockflag==1)
{
  digitalWrite(LED1,LOW);
 
  digitalWrite(LED2,HIGH);
}
else if(lockflag==0)
{
  
  digitalWrite(LED2,LOW);
 
  digitalWrite(LED1,HIGH);
}
}

