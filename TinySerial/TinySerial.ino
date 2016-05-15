#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ***
// *** RX, TX
// ***
#define RX    3
#define TX    4

// ***
// *** Define the software based serial port. Using the
// *** name Serial so that code can be used on other
// *** platforms that support hardware based serial. On
// *** chips that support the hardware serial, just comment
// *** this line.
// ***
SoftwareSerial Serial(RX, TX);

// ***
// *** Pinout ATtiny25/45/85:
// *** PDIP/SOIC/TSSOP
// *** =============================================================================================
// ***
// ***        (PCINT5/RESET/ADC0/dW) PB5   [1]*  [8]   VCC
// *** (PCINT3/XTAL1/CLKI/OC1B/ADC3) PB3   [2]   [7]   PB2 (SCK/USCK/SCL/ADC1/T0/INT0/PCINT2)
// *** (PCINT4/XTAL2/CLKO/OC1B/ADC2) PB4   [3]   [6]   PB1 (MISO/DO/AIN1/OC0B/OC1A/PCINT1)
// ***                               GND   [4]   [5]   PB0 (MOSI/DI/SDA/AIN0/OC0A/OC1A/AREF/PCINT0)
// ***

// *********************************
// ***
// *** For FTDI/232 Cale:
// *** Connect 3V (red)    to Pin 8
// *** Connect GND (black) to Pin 4
// *** Connect RX (yellow) to Pin 3
// *** Connect TX (orange) to Pin 2
// ***
// *********************************

// ***
// *** Pin on which the OneWire data
// *** wire is connected.
// ***
#define ONE_WIRE_BUS 1

// ***
// *** Setup a oneWire instance to communicate with any OneWire
// *** devices (not just Maxim/Dallas temperature ICs).
// ***
OneWire _oneWire(ONE_WIRE_BUS);

// ***
// *** Pass our oneWire reference to Dallas Temperature.
// ***
DallasTemperature _sensors(&_oneWire);

void setup()
{
  // ***
  // *** Initialize the Serial port
  // ***
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Initializing...");

  // ***
  // *** Start up the library.
  // ***
  _sensors.begin();

  // ***
  // *** Show a message that setup has completed.
  // ***
  Serial.println("Initialization complete.");
}

void loop()
{
  // ***
  // *** Keep track of the loop.
  // ***
  static uint32_t counter = 0;

  // ***
  // *** Get the current temperature and display it.
  // ***
  _sensors.requestTemperatures();
  double tempC = _sensors.getTempCByIndex(0);
  double tempF = _sensors.getTempFByIndex(0);
  Serial.print(counter); Serial.print(": "); Serial.print(tempC, 1); Serial.print("C, "); Serial.print(tempF, 1); Serial.println("F");

  // ***
  // *** Delay 2 seconds.
  // ***
  delay(2000);

  // ***
  // *** Increment the counter.
  // ***
  counter++;
}
