## Descrição
Sistema de porta automática utilizando Arduino Uno e protoboard.  
Quando alguém se aproxima do sensor ultrassônico (< 20 cm), a porta abre automaticamente (servo motor) e há sinalização visual com LEDs:

- LED verde: aviso de aproximação e porta aberta  
- LED vermelho: porta fechada

---

## Funcionamento Esperado

### Quando não houver ninguém próximo (≥ 20 cm)
- Servo motor: 0° (porta fechada)  
- LED vermelho: aceso  
- LED verde: apagado

### Quando alguém se aproximar (< 20 cm)
1. LED verde pisca duas vezes  
2. Servo motor gira para 90° (porta aberta)  
3. LED verde permanece aceso

---

## Materiais Necessários
- 1 Arduino Uno  
- 1 Sensor ultrassônico HC-SR04  
- 1 Servo motor SG90  
- 2 LEDs (verde e vermelho)  
- 2 resistores de 220Ω  
- Protoboard  
- Jumpers

---

## Esquema de Montagem

### 1️⃣ Conexão do Sensor Ultrassônico

   VCC → 5V Arduino
   GND → GND Arduino
   Trig → Pino 9 Arduino
   Echo → Pino 10 Arduino
---

### 2️⃣ Conexão do Servo Motor


   Fio vermelho → 5V Arduino
   Fio marrom → GND Arduino
   Fio amarelo → Pino 6 Arduino
---

### 3️⃣ Conexão dos LEDs
- LED verde → resistor 220Ω → Pino 3 Arduino  
- LED vermelho → resistor 220Ω → Pino 4 Arduino  
- Anodos dos LEDs conectados aos resistores  
- Catodos conectados ao GND
---

### 4️⃣ Protoboard
- Todos os componentes conectados à protoboard  
- Jumpers para ligação com Arduino
---

Exemplo simplificado do loop principal:

```cpp
if(distancia < 20){
    piscarLEDverde(2);
    servo.write(90);
    digitalWrite(LEDverde, HIGH);
    digitalWrite(LEDvermelho, LOW);
} else {
    servo.write(0);
    digitalWrite(LEDverde, LOW);
    digitalWrite(LEDvermelho, HIGH);
}
