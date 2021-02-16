
#include "Instrument_Cluster.h"

const unsigned long RUN_TIME = 500UL;                   // Ignition Run Time, in mS. Used to heavily debounce the start switch.
const unsigned long START_TIME = 90000UL;               // Ignition Start Time, in mS. Start Sw idle lapse time.

// ============================================================================================================================

// isNumeric(): Return true if the string is all numeric.
bool isNumeric(String str)
{
    for(byte i=0;i<str.length();i++) {
        if(!isDigit(str.charAt(i))) return false;
    }
    return true;
}

// ============================================================================================================================

// PrintHex(): Print number in hex format.
// The bytecnt is the byte size of the hex value. Set lf to true for linefeed.
// One and two bytecnt values are formatted with a leading 0x. All others omit it.
void PrintHex(unsigned long dec, byte bytecnt, bool lf)
{
    String Str;
    byte Value;

    if(bytecnt == 1 && dec <= 0xffff) {                 // One Hex Byte to print.
        dec = (unsigned int)(dec);
        Value = lowByte(dec);                           // Use Only Low Byte.
        if(Value == 0) {
            Str = "0x00";
        }
        else if(Value <= 0x0f){
            Str = "0x0" + String(Value,HEX);
        }
        else {
            Str = "0x" + String(Value,HEX);
        }
        serial_manager.print(Str);
    }
    else if(bytecnt == 2 && dec <= 0xffff) {            // Two Hex bytes to print.
        dec = (unsigned int)(dec);
        Value = highByte(dec);                          // High Byte.
        if(Value == 0) {
            Str = "0x00";
        }
        else if(Value <= 0x0f) {
            Str = "0x0" + String(Value,HEX);
        }
        else {
            Str = "0x" + String(Value,HEX);
        }
        serial_manager.print(Str);

        Value = lowByte(dec);                           // Low Byte.
        if(Value == 0) {
            Str = "00";
        }
        else if(Value <= 0x0f) {
            Str = "0" + String(Value,HEX);
        }
        else {
            Str = String(Value,HEX);
        }
        serial_manager.print(Str);
    }
    else {                                              // Print unformatted hex value.
        Str = String(dec,HEX);
        serial_manager.print(Str);
    }
    
    if(lf) serial_manager.println("");                  // New line.

    return;
}

// ============================================================================================================================
