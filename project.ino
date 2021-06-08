// initialising pins
int photoresistor = A4;
int detectPin = A1;

int led1 = D4;
int led2 = D5;

// initialising variables
int lightlevel = 0;
int analogMoisture = 0;
int timeCount = 0;
int i = 1;
int lightCount = 0;

// Setup the Argon
void setup()
{
    // Configure Pins
    pinMode(photoresistor, INPUT);
    pinMode(detectPin, INPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
}

// Main loop
void loop()
{
    // read light level every loop
    lightlevel = analogRead(photoresistor);
    Particle.publish("light", String(lightlevel), PRIVATE);
    
    // check if lightlevel is enough and add to counter. This reps the time during a day plant gets sunlight
    if (lightlevel > 100)
    {
        lightCount = lightCount + 1;
    }
    
    // check if it is the end of the day
    if (timeCount == 30)
    {
        // read soil mosidture level
        analogMoisture = analogRead(detectPin);
        // compare values and take action accordingly
	    if (lightCount >= 15)
	    {
	        if (analogMoisture >= 300)
	        {
	            Particle.publish("Plant_Condition","Great", PRIVATE);
	            digitalWrite(led1, LOW);
	            digitalWrite(led2, LOW);
	        }
	        else
	        {
	            Particle.publish("Plant_Condition","NeedWater", PRIVATE);
	            digitalWrite(led2, HIGH);
	            digitalWrite(led1, LOW);
	        }
	    }
	    else
	    {
	        if (analogMoisture >= 300)
	        {
	            Particle.publish("Plant_Condition","NeedLight", PRIVATE);
	            digitalWrite(led1, HIGH);
	            digitalWrite(led2, LOW);
	        }
	        else
	        {
	            Particle.publish("Plant_Condition","NeedBoth", PRIVATE);
	            digitalWrite(led1, HIGH);
	            digitalWrite(led2, HIGH);
	        }
	    }
	    // reset timer and light amount at the end of the day
	    timeCount = 0;
	    lightCount = 0;
    }
    
    delay(1000);
    timeCount = timeCount + 1;
}