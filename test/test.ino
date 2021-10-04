const u_int16_t SENSOR_ONE = 1;
const u_int16_t SENSOR_TWO = 2;

void setup() {
    pinMode(SENSOR_ONE, INPUT);
    pinMode(SENSOR_TWO, INPUT);
    Serial.begin(9600);
}

void loop() {
    Serial.println("SENSOR 1: " + String(digitalRead(SENSOR_ONE)));
    Serial.println("SENSOR 2: " + String(digitalRead(SENSOR_TWO)));
}