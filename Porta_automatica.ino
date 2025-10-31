// Inclui a biblioteca Servo.h para controle do servo motor
#include <Servo.h>

// --- Definição dos Pinos ---
// Pinos do Sensor Ultrassônico HC-SR04
const int trigPin = 5; // Pino Trigger (ENVIA o pulso ultrassônico)
const int echoPin = 4; // Pino Echo (RECEBE o pulso ultrassônico refletido)

// Pinos dos LEDs
const int ledVermelho = 13; // Pino para o LED Vermelho
const int ledVerde = 12;    // Pino para o LED Verde

// Pino do Servo Motor (MUDANÇA: RECOMENDADO USAR UM PINO PWM, ex: 9)
const int servoPin = 9; // Pino onde o servo motor está conectado (no Arduino UNO: 3, 5, 6, 9, 10, 11)


// --- Variáveis Globais ---
Servo minhaPorta;    // Cria um objeto Servo para controlar o servo motor

long duracao;        // Variável para armazenar a duração do pulso (tempo que o som leva para ir e voltar)
int distanciaCm;     // Variável para armazenar a distância em centímetros


// --- Constantes de Funcionamento ---
// Distância em cm para acionar a porta.
// A porta ABRE quando a distância for MENOR que este valor.
const int DISTANCIA_MINIMA_PORTA = 20;


// --- Função setup() ---
// Executada uma única vez quando o Arduino é ligado ou resetado
void setup() {
  // Configura os pinos do sensor ultrassônico
  pinMode(trigPin, OUTPUT); // O pino Trig é uma SAÍDA
  pinMode(echoPin, INPUT);  // O pino Echo é uma ENTRADA

  // Configura os pinos dos LEDs
  pinMode(ledVermelho, OUTPUT); // LED Vermelho é uma SAÍDA
  pinMode(ledVerde, OUTPUT);    // LED Verde é uma SAÍDA

  // Anexa o objeto servo ao pino correto
  minhaPorta.attach(servoPin);

  // Inicia a comunicação serial para depuração (ver a distância no Monitor Serial)
  Serial.begin(9600);//Arduino inicia a comunicação serial com a taxa de transmissão de 9600 bits por segundo.

  // Estado inicial: porta fechada e LED vermelho aceso
  minhaPorta.write(0);           // Servo na posição 0 graus (representando "porta fechada")
  digitalWrite(ledVermelho, HIGH); // Liga o LED Vermelho
  digitalWrite(ledVerde, LOW);     // Garante que o LED Verde esteja desligado
}


// --- Função loop() ---
// Executada repetidamente após a função setup()
void loop() {
  // 1. MEDIÇÃO DA DISTÂNCIA USANDO O SENSOR ULTRASSÔNICO
  // Limpa o pino Trig (garante que não haja pulso anterior)
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); // Pequeno atraso

  // Envia um pulso de 10 microssegundos no pino Trig (emite o som)
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Mede a duração do pulso no pino Echo (tempo que o som levou para ir e voltar)
  // pulseIn() espera pelo pulso e mede sua duração em microssegundos.
  duracao = pulseIn(echoPin, HIGH);

  // Calcula a distância em centímetros
  // Fórmula: distância = (duração do pulso em microssegundos * velocidade do som) / 2
  // Velocidade do som no ar é aproximadamente 0.0343 cm/microsegundo (ou 343 metros/segundo)
  // Dividimos por 2 porque o som viaja de ida e volta
  distanciaCm = duracao * 0.0343 / 2;

  // Imprime a distância no Monitor Serial para depuração
  Serial.print("Distancia: ");
  Serial.print(distanciaCm);
  Serial.println(" cm");
  
  
  // 2. LÓGICA DE CONTROLE DA PORTA E LEDs
  // SE a distância for MENOR que a DISTANCIA_MINIMA_PORTA (20 cm)
  if (distanciaCm < DISTANCIA_MINIMA_PORTA) {
    // CASO: Alguém se aproximou (distância menor que 20 cm)

    digitalWrite(ledVermelho, LOW); // Desliga o LED vermelho (porta não está mais fechada)

    // O LED verde pisca duas vezes como aviso de abertura
    for (int i = 0; i < 2; i++) {
      digitalWrite(ledVerde, HIGH); // Liga o LED Verde
      delay(200);                   // Permanece ligado por 200ms
      digitalWrite(ledVerde, LOW);  // Desliga o LED Verde
      delay(200);                   // Permanece desligado por 200ms
    }

    // A porta ABRE: move o servo para 90 graus
    minhaPorta.write(90); // Servo na posição 90 graus (representando "porta aberta")

    // O LED verde permanece aceso enquanto a "porta" estiver aberta (ou alguém próximo)
    digitalWrite(ledVerde, HIGH);

    // Pequeno atraso para dar tempo da porta abrir e para não ficar lendo muito rápido
    delay(1000); // Espera 1 segundo com a "porta" aberta antes de verificar novamente
  }
  
  
  // SE a distância for MAIOR OU IGUAL à DISTANCIA_MINIMA_PORTA (20 cm)
  else {
    // CASO: Ninguém próximo (distância maior ou igual a 20 cm)

    // A "porta" FECHA: move o servo para 0 graus
    minhaPorta.write(0); // Servo na posição 0 graus (representando "porta fechada")

    // O LED vermelho deve permanecer aceso (indicando "porta fechada")
    digitalWrite(ledVermelho, HIGH);

    // Garante que o LED verde esteja desligado
    digitalWrite(ledVerde, LOW);
  }

  
  // Pequeno atraso entre as leituras do sensor para estabilidade
  delay(50);
}