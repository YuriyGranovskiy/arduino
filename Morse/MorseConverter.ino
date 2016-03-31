void MorseMessage(String message)
{
  for (int i = 0; i < message.length(); i++)
  {
    String codeString = String(hashMap.getValueOf(message[i]));
    for( int j = 0; j < codeString.length(); j++)
    {
      byte codeLetter = codeString[j];
      if(codeLetter == ' ')
      {
        delay(dotLength);
      }
      else
      {
        Blink((codeLetter - '0') * dotLength);
      }
      
      delay(dotLength);
    }
    
    delay(dotLength * 2);
  }
}

void Blink(int blinkDuration)
{
  Serial.println(String(blinkDuration));
  digitalWrite(LED_BUILTIN, HIGH);
  delay(blinkDuration);
  digitalWrite(LED_BUILTIN, LOW);  
}


