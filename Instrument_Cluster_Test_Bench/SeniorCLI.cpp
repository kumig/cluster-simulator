
#include "Instrument_Cluster.h"

// ============================================================================================================================
// ProcessCommands(): Process the commands sent through the serial port.
// This is the Command Line Interface (CLI).
void ProcessCommands(void)
{
    unsigned int Value = 0;                             // General Purpose variable.
    String StrValue;                                    // General Purpose message string.
    
    if(serial_manager.onReceive()) {                    // Process any serial commands from user (CLI).
//     StrValue = "Raw CLI Data: ";                     // Debug message.
//     StrValue += serial_manager.getValue();
//     serial_manager.println(StrValue);

        UserCmd = serial_manager.getCmd();              // Get Command.
        UserCmd.toUpperCase();
        if(UserCmd == "?" || UserCmd == "H" || UserCmd == "HELP") {
            serial_manager.println("");
            serial_manager.println(F("COMMAND LINE INTERFACE HELP SUMMARY"));
           
            serial_manager.println(F(" -----------------------------------------------------------------"));
            serial_manager.println(F("       ** DIAGNOSTIC COMMANDS **"));
            serial_manager.println(F(" CAN-Bus Info:  CBINF,[0-2] -> HS/MS/HS-MS"));
            serial_manager.println(F(" HS CAN Data:   HSCAN,[0-1] -> off/on"));
            serial_manager.println(F(" MS CAN Data:   MSCAN,[0-1] -> off/on"));
            
            serial_manager.println(F(" Stop Program:    STOP        -> Exit while loop and stop program"));
           
            serial_manager.println(F(" -----------------------------------------------------------------"));
            serial_manager.println("");       
        }
       
 
        else if(UserCmd == "HSCAN") {                   // Display HS CAN-Bus Data.
            String StrValue = serial_manager.getParam();
            StrValue.toUpperCase();
            if(StrValue=="0") {
                if(HS_Print_Flag == true) StrValue = F("Quit");
                else StrValue = F("Quit, But Wasn't Running");
                HS_Print_Flag = false;
            }
            else if(StrValue=="1") {
                HS_Print_Flag = true;
            }
            else if(StrValue=="OFF") {
                if(HS_Print_Flag == true) StrValue = F("Quit");
                else StrValue = F("Quit, But Wasn't Running");
                HS_Print_Flag = false;
            }
            else if(StrValue=="ON") {
                HS_Print_Flag = true;
            }
            else {
                if(StrValue == "") StrValue = "?";
                StrValue = "(" + StrValue + F(" is Unknown Parameter)");
            }
            serial_manager.print(F("HS CAN DATA: "));
            serial_manager.println(StrValue);
        }
        else if(UserCmd == "MSCAN") {                   // Display MS CAN-Bus Data.
            String StrValue = serial_manager.getParam();
            StrValue.toUpperCase();
            if(StrValue=="0") {
                if(MS_Print_Flag == true) StrValue = F("Quit");
                else StrValue = F("Quit, But Wasn't Running");
                MS_Print_Flag = false;
            }
            else if(StrValue=="1") {
                MS_Print_Flag = true;
            }
            else if(StrValue=="OFF") {
                if(MS_Print_Flag == true) StrValue = F("Quit");
                else StrValue = F("Quit, But Wasn't Running");
                MS_Print_Flag = false;
            }
            else if(StrValue=="ON") {
                MS_Print_Flag = true;
            }
            else {
                if(StrValue == "") StrValue = "?";
                StrValue = "(" + StrValue + F(" is Unknown Parameter)");
            }
            serial_manager.print(F("MS CAN DATA: "));
            serial_manager.println(StrValue);
        }
        else if(UserCmd == "CBINF") {                   // CAN-Bus Information (Online Status)
            String StrValue = serial_manager.getParam();
            StrValue.toUpperCase();
            if(StrValue=="0") {
                StrValue = F("HS CAN-Bus ");
                if(HSCAN_Online() == true) {
                    StrValue += F("Online");
                }
                else {
                    StrValue += F("Offline");
                }
            }
            else if(StrValue=="1") {
                StrValue = F("MS CAN-Bus ");
                if(MSCAN_Online() == true) {
                    StrValue += F("Online");
                }
                else {
                    StrValue += F("Offline");
                }
            }
            else if(StrValue=="2") {
                StrValue = F("HS CAN-Bus ");
                if(HSCAN_Online() == true) {
                    StrValue += F("Online, ");
                }
                else {
                    StrValue = F("Offline, ");
                }
                StrValue += F("MS CAN-Bus ");
                if(MSCAN_Online() == true) {
                    StrValue += F("Online");
                }
                else {
                    StrValue += F("Offline");
                }
            }
            else {
                StrValue = F("(Error, Invalid Parameter)");
            }
            serial_manager.print(F("CAN-BUS INFO: "));
            serial_manager.println(StrValue);
        }
        
      
        else if(UserCmd == "STOP") {                    // Stop program.
          
            serial_manager.println(F("Stopping DATA: Program Exiting"));
            Stop = true;
        }
        
        else if(UserCmd == "START") {                    // Start program.
       
            serial_manager.println(F("Starting DATA: Program Starting"));
            Stop = false;
        }
        
        else {
            if(serial_manager.getValue() != "") {
                StrValue = (F("UNKNOWN CMD: "));
                StrValue += serial_manager.getValue();
                serial_manager.println(StrValue);
            }
            else {
                serial_manager.println("-> CLI Ready. Enter ? for help.");
            }
        }

    }

    return;
}
