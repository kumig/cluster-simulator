
#include "Instrument_Cluster.h"

// ============================================================================================================================
// A bit of interesting information:
// Refresh rate for MS & HS CAN-Bus boards is set to 50mS (CYCLE_TIME).
// HS data rate is 500KBPS, transmit update period is ~0.8mS (o-scope measurement).
// MS data rate is 125KBPS, transmit update period is ~6.9mS (o-scope measurement).

// ============================================================================================================================

// Print_HSCAN_Data(): Display one HS CAN-Bus Data Record (if available). Tab formatted.
void Print_HSCAN_Data(void)
{
    byte len = 0;
    byte buf[8];
    unsigned long ArbID =0x0000;

// If CAN-Bus Data available, print the packet.
    while (CAN_MSGAVAIL == CAN_HS.checkReceive()) {
        CAN_HS.readMsgBufID(&ArbID, &len, buf);
        serial_manager.print("HS ArbID:");
        PrintHex(ArbID, 2, false);
        serial_manager.print(" = ");
        if(len > 8) len = 8;
        for(int i = 0; i<len; i++) {
            PrintHex(buf[i],1,false);
            serial_manager.print("\t");
        }
        serial_manager.println("");
    }

    return;
}

// ============================================================================================================================

// Print_MSCAN_Data(): Display one MS CAN-Bus Data Record (if available). Tab formatted.
void Print_MSCAN_Data(void)
{
    byte len = 0;
    byte buf[8];
    unsigned long ArbID =0x0000;

// If CAN-Bus Data available, print the packet.
    while (CAN_MSGAVAIL == CAN_MS.checkReceive()) {
        CAN_MS.readMsgBufID(&ArbID, &len, buf);
        serial_manager.print("MS ArbID:");
        PrintHex(ArbID, 2, false);
        serial_manager.print(" = ");
        if(len > 8) len = 8;
        for(int i = 0; i<len; i++) {
            PrintHex(buf[i],1,false);
            serial_manager.print("\t");
        }
        serial_manager.println("");
    }

    return;
}

// ============================================================================================================================ 

// HSCAN_online() : Check to see if HS CAN-Bus is receiving data from cluster.
bool HSCAN_Online(void)
{
    byte len = 0;
    byte buf[8];
    unsigned long ArbID =0x0000;
    bool status = false;
    
    while (CAN_MSGAVAIL == CAN_HS.checkReceive()) {     // Data Available.
        CAN_HS.readMsgBufID(&ArbID, &len, buf);         // Flush.
        if(ArbID >= 0x0000) status = true;
    }
    
    return status;
}

// ============================================================================================================================ 

// MSCAN_online() : Check to see if MS CAN-Bus is receiving data from cluster.
bool MSCAN_Online(void)
{
    byte len = 0;
    byte buf[8];
    unsigned long ArbID =0x0000;
    bool status = false;
    
    while (CAN_MSGAVAIL == CAN_MS.checkReceive()) {     // Data Available.
        CAN_MS.readMsgBufID(&ArbID, &len, buf);         // Flush.
        if(ArbID >= 0x0000) status = true;
    }
    
    return status;
}


// ============================================================================================================================ 


// SendCanBus(): Periodically transmit all MS & HS CAN-Bus data to the cluster. Both are sent at the same refresh rate.
void SendCanBus(void)
{
    unsigned int SpeedX;                                // Temp var, holds Speedometer Value.
    static unsigned long FuelResetTime = 0;             // Initialize Fuel Reset Timer.
    static bool LocalFuelRstFlag = false;               // Fuel Reset Flag for local use.
    
     if(micros() < CycleTime) {                          // Is it CAN-Bus Refresh Cycle Time?
        return;                                         // No, exit.
    }

    CycleTime = micros() + CYCLE_TIME;                  // Reset uS timer.
    
//    if(ClusterPwr == ClusterRlyOff) {                   // Is cluster's Power Off?
//        return;                                         // Off, Exit.
//    }
//    
//
//// **************************************
//// *       DEBUG CAN-BUS SECTION        *
//// *    UNCOMMENT TO TEST NEW ARBIDs    *
//// **************************************
//
    for(unsigned int PID = 0x000; PID <= 0x7FF; PID++) {
      ProcessCommands();                                  // Process User Commands (via CLI).
      if (Stop == true) {return;}
      for (int count = 0; count < 100; count++) {Serial.println("");}
     
        CAN_data[0] = 0x7f;
        CAN_data[1] = 0xff;
        CAN_data[2] = 0xff;
        CAN_data[3] = 0xff;
        CAN_data[4] = 0xff;
        CAN_data[5] = 0xff;
        CAN_data[6] = 0xff;
        CAN_data[7] = 0xff;
//        
//        if(PID!=ARB_SPD_RPM && PID!=ARB_TEMP_OD_CEL) {
            CAN_HS.sendMsgBuf(PID,0,8,CAN_data); 
//        }
//        
//        if(PID!=ARB_BEEP && PID!=ARB_LIGHTS && PID!=ARB_TURNSIG && PID!=ARB_TPM && PID!=ARB_DOORS && 
//          PID!=ARB_BEEP && PID!=ARB_HBEAM && PID!=ARB_Pk_Brk && PID!=ARB_FUEL && PID!=ARB_OIL) {
//            CAN_MS.sendMsgBuf(PID,0,8,CAN_data); 
//        }
   
    
    //     String PIDStr = "PID ";
    //    PIDStr = PIDStr +  PID;
    //   Serial.println(PIDStr);
    //   serial_manager.println(PIDStr);
    
    }

    return;
}  
