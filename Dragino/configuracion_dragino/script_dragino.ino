#include <LoRaWan.h>

char txBuffer[256]; //Buffer transmissió

void setup(void) {
  Serial.begin(115200);  

  lora.init(); 
  lora.setId("", "DEVEUI", "");
  lora.setKey("", "", "APPKEY");
              
  lora.setDeciveMode(LWOTAA); 
  lora.setDataRate(DR0, EU868);
  lora.setAdaptiveDataRate(false);
  lora.setClassType(CLASS_A);  

  // Intentar realizar el join cada 10 segons
  while (!lora.setOTAAJoin(JOIN, 10));
  
}

void loop() {
  int len;
  // Verificar si hi ha dades a enviar
  if (Serial.available() > 0) {
      //Llegir dades del port serie
      len = Serial.readBytesUntil('\n', txBuffer, sizeof(txBuffer) - 1); 
      
      //Assegura que si les dades són una cadena no lleguesqui de mes
      txBuffer[len] = '\0';
  
      delay(200);

      if (len > 0) {
        
          // Ennviar dades loRa sense confirmació
          lora.transferPacket(txBuffer, len);

          delay(1000);  // Espera de 1 segón per rebre

          len = 0;
      }
  }

  memset(txBuffer, 0, sizeof(txBuffer));  // Netetjar buffer tx
  Serial.flush();  
  delay(2000);  // 2 segons abas de la seguent iteració
}
