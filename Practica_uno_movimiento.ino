class Ultrasonico {
  private:
    int trigPin;
    int echoPin;

  public:
    Ultrasonico(int trig, int echo) 
      : trigPin(trig), echoPin(echo) {
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }

    long medirDistancia() {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      long duracion = pulseIn(echoPin, HIGH);

      long distancia = duracion * 0.034 / 2;

      return distancia;
    }
};

class LED {
  private:
    int pin;
    bool estado;
    unsigned long ultimoCambio;
    int intervaloParpadeo;

  public:
    LED(int pinLed) 
      : pin(pinLed), estado(false), ultimoCambio(0), intervaloParpadeo(0) {
      pinMode(pin, OUTPUT);
      apagar();
    }

    void encender() {
      estado = true;
      digitalWrite(pin, HIGH);
    }

    void apagar() {
      estado = false;
      digitalWrite(pin, LOW);
    }

    void parpadear(int intervalo) {
      intervaloParpadeo = intervalo;
      unsigned long tiempoActual = millis();
      if (tiempoActual - ultimoCambio >= intervaloParpadeo) {
        estado = !estado;
        digitalWrite(pin, estado ? HIGH : LOW);
        ultimoCambio = tiempoActual;
      }
    }
};

// Definición de pines
#define TRIG_PIN 32
#define ECHO_PIN 33
#define LED_ROJO_PIN 25
#define LED_NARANJA_PIN 26
#define LED_VERDE_PIN 27

// Creación de objetos para el sensor y los LEDs
Ultrasonico sensor(TRIG_PIN, ECHO_PIN);
LED ledRojo(LED_ROJO_PIN);
LED ledNaranja(LED_NARANJA_PIN);
LED ledVerde(LED_VERDE_PIN);

void setup() {
  Serial.begin(115200);
}

void loop() {
  long distancia = sensor.medirDistancia();
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  ledRojo.apagar();
  ledNaranja.apagar();
  ledVerde.apagar();

  if (distancia < 50) {
    ledRojo.parpadear(500);
  } else if (distancia >= 50 && distancia < 150) {
    ledNaranja.parpadear(500);
  } else if (distancia >= 150 && distancia < 300) {
    ledNaranja.encender();
  } else if (distancia >= 300) {
    ledVerde.encender();
  }

}