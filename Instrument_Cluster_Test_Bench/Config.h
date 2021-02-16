// File: Config.h. Used in Can2Cluster.ino project.


// ****************************************************************************************************************************

// INSTRUCTIONS: USER DEFINES MAY BE CHANGED TO SUIT THE PROJECT REQUIREMENTS.


// CAN-BUS SECTION
// Change these defines to match your CAN-Bus Boards.
// The CAN-Bus module used in this project is the NiRen MCP2515 + TJA1050 Chinese clone board.
#define HS_CAN_CS       8                               // Chip Select Digital Pin for HS CAN-Bus Module.
#define MS_CAN_CS       9                               // Chip Select Digital Pin for MS CAN-Bus Module.
#define CAN_FREQ        MCP_8MHz                        // CAN-Bus Module Xtal Frequency. 
// ****************************************************************************************************************************
// USB SERIAL/CLI PORT SECTION
#define SERIAL_BAUD        115200                       // Serial Baud Rate.
#define SERIAL_CONFIG      SERIAL_8N1                   // Serial Configuration.
// ****************************************************************************************************************************
// COMMAND LINE INTERFACE SECTION (USES SERIAL USB PORT)
// Change CMD_EOL_TERM if your serial console cannot send a Carriage Return <CR> when [ENTER] is pressed.
// For example, change to  '\n' if your terminal sends a NEWLINE <LF> when [ENTER] is pressed.
#define CMD_EOL_TERM    '\r'                            // Serial Manager EOL termination character.
// ****************************************************************************************************************************

// EOF
