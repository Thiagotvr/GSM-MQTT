const char apn[] = "vivo.com.br";  // APN da Vivo
const char gprsUser[] = "";
const char gprsPass[] = "";
const char simPIN[]   = ""; 

#define SerialMon Serial
#define SerialAT Serial1


#define TINY_GSM_MODEM_SIM800     
#define TINY_GSM_RX_BUFFER   1024

#define MODEM_RST            5
#define MODEM_PWKEY          4
#define MODEM_POWER_ON       23
#define MODEM_TX             27
#define MODEM_RX             26

#include <Wire.h>
#include <TinyGsmClient.h>

TinyGsm modem(SerialAT);
TinyGsmClient gsmClient;

void GSM_Setup(){
  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);

  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);

  SerialMon.println("Inicializando o modem...");
  modem.init();

  if (strlen(simPIN) && modem.getSimStatus() != 3 ) {
    modem.simUnlock(simPIN);
  }

  delay(3000);

  SerialMon.print("Conctando ao GPRS: ");
  SerialMon.print(apn);
  if(!modem.gprsConnect(apn, gprsUser, gprsPass)){
    SerialMon.println(" Falhou");
  } else {
    SerialMon.print(" Conectado ao GPRS.");
  }  
}