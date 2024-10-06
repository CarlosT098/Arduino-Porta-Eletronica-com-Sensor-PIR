#include <Servo.h>

const int pinoServo = 10;   // Pino digital utilizado pelo servo
const int pinoLedVerm = 8;  // Pino ligado ao LED vermelho
const int pinoLedAzul = 9;  // Pino ligado ao LED azul
const int pinoPIR = 5;      // Pino ligado ao sensor PIR

Servo servoMotor; // Objeto do tipo Servo
int posicaoAtual = 90; // Posição inicial do servo (90 graus)
int sensorPIRValor;   // Variável para guardar valor do sensor

void setup() {
  Serial.begin(9600);              // Inicia a comunicação serial
  servoMotor.attach(pinoServo);    // Anexa o servo ao pino
  pinMode(pinoLedVerm, OUTPUT);    // Configura o LED vermelho como saída
  pinMode(pinoLedAzul, OUTPUT);    // Configura o LED azul como saída
  pinMode(pinoPIR, INPUT);         // Configura o sensor PIR como entrada
  servoMotor.write(90);            // Define posição inicial do servo (90 graus)
}

void loop() {
  sensorPIRValor = digitalRead(pinoPIR); // Lê o valor do sensor PIR

  if (sensorPIRValor == HIGH) {
    // Movimento detectado
    digitalWrite(pinoLedVerm, HIGH);  // Acende o LED vermelho
    digitalWrite(pinoLedAzul, LOW);   // Apaga o LED azul
    Serial.println("Movimento detectado!");

    if (posicaoAtual != 180) {        // Move o servo apenas se ele não estiver na posição correta
      servoMotor.write(180);          // Gira o servo para 180 graus
      posicaoAtual = 180;             // Atualiza a posição atual do servo
      Serial.print("Posição do servo: ");
      Serial.println(posicaoAtual);
      delay(15000);
    }

  } else {
    // Sem movimento
    digitalWrite(pinoLedVerm, LOW);   // Apaga o LED vermelho
    digitalWrite(pinoLedAzul, HIGH);  // Acende o LED azul
    
    if (posicaoAtual != 90) {          // Move o servo de volta apenas se ele não estiver na posição inicial
      servoMotor.write(90);            // Gira o servo de volta para 90 graus
      posicaoAtual = 90;               // Atualiza a posição atual do servo
      Serial.print("Posição do servo: ");
      Serial.println(posicaoAtual);
      delay(5000);
    }
  }

  delay(500); // Pequeno atraso para evitar leituras muito rápidas
}
