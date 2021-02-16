

// ============================================================================================================================

// CAN-BUS STRUCTS & UNIONS

/* union arb10AX1 {                                        // ArbID 0x10A, byte 1. Headlight
  struct
  {
    byte Spare1: 7;                                     // Bits D0-D6 unused.
    bool Headlights:1;                                  // Headlights (Night time).
  } ctrl;
  byte all;                                             // Bits D0-D7.
};
 */
