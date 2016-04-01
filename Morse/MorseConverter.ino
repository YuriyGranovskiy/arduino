void MorseMessage(String message)
{
  for (int i = 0; i < message.length(); i++)
  {
    byte letter =  message[i];
    if(letter == ' ')
    {
        delay(dotLength * 3);
        continue;
    }
    
    int index = letter <= 90 && letter >= 65 
                ? letter - 65
                : letter <= 122 && letter >= 97 
                  ? letter - 97
                  : -1;
    if( index < 0)
    {
      continue;
    }
    
    int code = codes[index];
    int codeParts[5];
    int codePartsHandle = 0;
    while (code > 0)
    {
      int codePart = code % 10;
      code = code / 10;
      codeParts[codePartsHandle++] = codePart;
    }
    
    for( int j = codePartsHandle - 1; j >= 0; j--)
    {
      Blink(codeParts[j] * dotLength);
            
      delay(dotLength);
    }
    
    delay(dotLength * 2);
  }
}

void Blink(int blinkDuration)
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(blinkDuration);
  digitalWrite(LED_BUILTIN, LOW);  
}


