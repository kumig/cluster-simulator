// File: Instrument_Cluster_Test_Bench.ino
// Project: Universal Instrument Cluster Test Bench.
// Author: A. Bell
// Created: Dec-02-2019

// ****************************************************************************************************************************

// INCLUDE SECTION
#include "Instrument_Cluster.h"                      

// ****************************************************************************************************************************


// GLOBAL SYSTEM VARIABLES
byte CAN_data[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//byte CoolantTemperature = COLD_TEMP;                    // Coolant Temperature.
bool HS_Print_Flag = false;                             // HS CAN-Bus Data Display Mode.
bool MS_Print_Flag = false;                             // MS CAN-Bus Data Display Mode.
bool SeqRunOnce = true;                                 // Sequencer Run Once Flag.
bool Stop = false;                                              // Stop Flag.
//unsigned int Fuel = FUEL0;                              // Fuel Level.
unsigned int LED_PWM_Level = PWM_Min;                   // Message Center & Speaker LED Brightness Level, 0-255.
unsigned int OdomPhase = 0;                             // Odometer 3-Phase Cycle Cam.
unsigned int Speed = 0;                                 // Speedometer.
unsigned int TachRPM = 0;                               // Tachometer.
unsigned long CycleTime = 0;                            // Timer for CAN-Bus refresh.
unsigned long OdoTime = 0;                              // Timer for Odometer.
unsigned long SeqHoldTimer = 0;                         // Timer for Pausing Animation Sequencer.
String UserCmd;                                         // Serial Port Commands from user (CLI).


// ****************************************************************************************************************************

// ** LIBRARY MODULE SECTION **

// CAN-Bus Communication
MCP_CAN CAN_MS(SPI_CS_PIN_MS);                          // Set MS CAN-BUS Shield's CS pin.
MCP_CAN CAN_HS(SPI_CS_PIN_HS);                          // Set HS CAN-BUS Shield's CS pin.

// Serial Control Line Interface (CLI)
RBD::SerialManager serial_manager;                      // Command Line Serial Interface.

// ****************************************************************************************************************************

// ** SYSTEM CONSTANTS SECTION **

const byte PWM_Max = 0xff;                              // Maximum PWM Value for MOSFET controlled Lighting (Full-On).
const byte PWM_Min = 0x00;                              // Minimum PWM Value for MOSFET controlled Lighting (Off).
const unsigned long BLINKER_TIME = 500;                 // Blinker Timer Delay, in mS.
const unsigned long CYCLE_TIME   = 50000UL;           // Main Loop Cycle Time, in uS.
const unsigned long FUEL_RST_TIME= 1100;                // Fuel Gauge Reset Timer, in mS.

// ****************************************************************************************************************************

// ** HARDWARE CONSTANTS SECTION **

const unsigned int CAN_XTAL    = CAN_FREQ;              // CAN-Bus Shield XTAL Frequency.
const unsigned int LED_Pin     = LED_BUILTIN;           // Arduino's Board Mounted LED (D13).


// ****************************************************************************************************************************

// ** CAN-BUS HARDWARE CONSTANTS **

const unsigned int SPI_CS_PIN_MS = MS_CAN_CS;           // MS CAN-Bus CS pin. 
const unsigned int SPI_CS_PIN_HS = HS_CAN_CS;           // HS CAN-Bus CS pin.


// ****************************************************************************************************************************

void setup() {
  // put your setup code here, to run once:
  static unsigned int RetryCnt = 0;

  pinMode(LED_Pin, OUTPUT);
  digitalWrite(LED_Pin, LOW);
  
  Serial.begin(SERIAL_BAUD,SERIAL_CONFIG);            // USB Serial Baud & Config for serial port.
  serial_manager.println(F("Start of System Initialization")); 

  Serial.println(F("Initializing HS CAN-Bus ..."));
    while (CAN_OK != CAN_HS.begin(CAN_500KBPS,CAN_XTAL)) { // Initialize HS CAN-Bus.
        digitalWrite(LED_Pin,!(digitalRead(LED_Pin)));  // Toggle LED.
        Serial.println(F("  HS CAN-Bus Shield init has failed"));  
        delay(250);
        String InitStr = F("->Init HS CAN-Bus Shield, retry #");
        InitStr = InitStr + RetryCnt++;
        Serial.println(InitStr);
    }

    Serial.println(F("HS CAN-Bus Shield Has Been Initialized"));
    Serial.flush();
    Serial.end();
    
    serial_manager.start();                             // Start Command Line Processor.
    serial_manager.setFlag(CMD_EOL_TERM);               // Set EOL Termination character.
    serial_manager.println(F("Serial Manager CLI is Enabled")); // We're alive!

    digitalWrite(LED_Pin, HIGH);                        // LED On.
    delay(1500);                                        // Allow Cluster to Power-Up & Initialize.

    serial_manager.println(F("Instrument Cluster Ready"));

    CycleTime = micros();                               // Initialize CAN-Bus Cycle (refresh) Timer.

    serial_manager.println(F("End of System Initialization\r\n"));    
    
    return;
}

void loop() {
  // put your main code here, to run repeatedly:


    if(HS_Print_Flag) Print_HSCAN_Data();               // Display HS CAN-Bus Data (CLI diagnostic feature).
   // if(MS_Print_Flag) Print_MSCAN_Data();               // Display MS CAN-Bus Data (CLI diagnostic feature).

   ProcessCommands();                                  // Process User Commands (via CLI).
   SendCanBus();                                       // Periodically Transmit CAN-Bus Data.
   if (Stop == true) {while(Stop == true){ProcessCommands();}}

}
