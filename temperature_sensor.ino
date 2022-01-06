#define DEBOUNCE_SECONDS 10

int lastStateSwitchTime = 0;

double temperatureC = 0.0;
double temperatureF = 0.0;


void setup()
{
  // Register a Spark variable here
  Spark.variable("temperatureC", &temperatureC, DOUBLE);
  Spark.variable("temperatureF", &temperatureF, DOUBLE);

  // Connect the temperature sensor to A7 and configure it
  // to be an input
  pinMode(A0, INPUT);

}


void loop()
{
  int now = Time.now();

  if (now - lastStateSwitchTime > DEBOUNCE_SECONDS)
  {
    int readingTemp = 0;
    double voltage = 0.0;

    // Keep reading the sensor value so when we make an API
    // call to read its value, we have the latest one
    readingTemp = analogRead(A0);
    // The returned value from the Core is going to be in the range from 0 to 4095
    // Calculate the voltage from the sensor reading
    voltage = (readingTemp * 3.3) / 4095;
    // Calculate the temperature and update our static variable
    temperatureC = (voltage - 0.5) * 100;

    temperatureF = (temperatureC * 9)/5 + 32;
  }

}
