// File: Instrument_Cluster.h. Used in Instrument_Cluster_Test_Bench.ino project.
// Author: A. Bell
// Created: Dec-02-2019


// ****************************************************************************************************************************
// Global Required Include Files.
#include <arduino.h>                                    // Main Arduino Include File for Type Defs.
#include <SPI.h>                                        // Default SPI library, V1.0.0, https://www.arduino.cc/en/Reference/SPI
#include <mcp_can.h>                                    // Seeedstudio CAN-BUS V1.0.0, https://github.com/Seeed-Studio/CAN_BUS_Shield
#include <RBD_SerialManager.h>                          // Serial CLI, V1.0.0-alpha.3, http://robotsbigdata.com/docs-arduino-serial-manager.html
#include "SeniorCanBus.h"                               // Project CAN-Bus data packet Structs.
#include "Config.h"                                     // Project Master Configuration parameters.
//#include "GaugeLUT.h"                                   // Project Gauge Scaling Correction Maps.
//#include "ClusterDefs.h"
//#include "Sequencer.h"                                  // Project Event Sequence Animator.

// ****************************************************************************************************************************
// PROTOTYPES

bool isNumeric(String);
bool HSCAN_Online(void);
bool MSCAN_Online(void);
void PrintHex(unsigned long val, byte bytecnt, bool lf);
void Print_HSCAN_Data(void);
void Print_MSCAN_Data(void);
void ProcessCommands(void);
void SendCanBus(void);

// ****************************************************************************************************************************

// Global Variables

extern bool HS_Print_Flag;                              // HS CAN-Bus Data Display Mode.
extern bool MS_Print_Flag;                              // MS CAN-Bus Data Display Mode.
extern bool SeqRunOnce;                                 // Sequencer Run Once Flag.
extern bool Stop;                                       // Stop Flag.
extern byte CAN_data[];                                 // CAN-Bus Data Packet.
extern byte CoolantTemperature;                         // Temperature Gauge.
extern unsigned int Fuel;                               // Fuel Gauge.
extern unsigned int LED_PWM_Level;                      // Message Center & Speaker LED Brightness Level.
extern unsigned int OdomPhase;                          // Odometer 3-Phase Cycle Cam.
extern unsigned int Speed;                              // Speedometer.
extern unsigned int TachRPM;                            // Tachometer.

extern unsigned long CycleTime;                         // CAN-Bus Refresh Timer.
extern unsigned long OdoTime;                           // Odometer Phase Timer.
extern unsigned long SeqHoldTimer;                      // Timer for Pausing Animation Sequencer.
extern String UserCmd;                                  // Serial Manager (CLI) User command parameter.

// ****************************************************************************************************************************

// ** HARDWARE CONSTANTS SECTION **

extern const unsigned int LED_Pin;                      // Arduino's Board Mounted LED (D13).

// ****************************************************************************************************************************

// ** LIBRARY MODULE SECTION **

// CAN-Bus Communication

extern MCP_CAN CAN_MS;                                  // Set MS CAN-BUS Shield's CS pin.
extern MCP_CAN CAN_HS;                                  // Set HS CAN-BUS Shield's CS pin.

// Serial Control Line Interface (CLI)
extern RBD::SerialManager serial_manager;


// ****************************************************************************************************************************

// ** SYSTEM CONSTANTS **


extern const byte PWM_Max;                              // Maximum PWM Value (On). For MOSFET controlled lighting.
extern const byte PWM_Min;                              // Minimum PWM Value (Off). For MOSFET controlled lighting.
extern const unsigned long CYCLE_TIME;                  // Main Loop Cycle Time, in uSecs.

// ****************************************************************************************************************************

// ** CAN-BUS HARDWARE CONSTANTS **

extern const unsigned int SPI_CS_PIN_MS;                // MS CAN-Bus CS pin. 
extern const unsigned int SPI_CS_PIN_HS;                // HS CAN-Bus CS pin.



// ****************************************************************************************************************************
// ** CAN-BUS CONTROL DATA CONSTANTS SECTION **

// COOLANT TEMPERATURE CONSTANTS
extern const byte COLDTEMP;                             // Below Zero Temperature Gauge.


// ****************************************************************************************************************************
