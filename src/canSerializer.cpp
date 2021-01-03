/**
 * @file canSerializer.c
 * @author Zain Ahmed
*/

#include "canSerializer.h"

// Calcuates a checksum
uint8_t calculateChecksum(CANFrame *pFrame)
{
    uint8_t computedChecksum = 0;                                           // will hold our checksum as we calculate
    uint8_t bytesToSum = sizeof(*pFrame) - sizeof(pFrame->checksum);        // do not include the checksum when calculating the checksum

    uint8_t *bytePtr = (uint8_t *)pFrame;                                   // get a pointer to struct so we can access individual bytes

    for (int i = 0; i < bytesToSum; i++) {
      computedChecksum += *(bytePtr + i);                                   // dereference and sum each byte
    }

    return computedChecksum;
}

/**
 * @brief adds checksum and syncWord to packet. 
 * @param pFrame: Pointer to a CAN frame.
 * @note: Ensure all other data of frame is filled before calling fillChecksum().
*/
void fillChecksum(CANFrame *pFrame)
{
    pFrame->syncWord = 0xA55A;                                              // set the sync word before summing
    pFrame->checksum = calculateChecksum(pFrame);                           // append the checksum to the packet
}

/**
 * @param pFrame: Pointer to a CAN frame.
 * Returns true if the pFrame struct is valid, false if it is invalid.
*/
bool validateChecksum(CANFrame *pFrame)
{
    if (pFrame->checksum == calculateChecksum(pFrame))
    {
        return true;
    }
    else
    {
        return false;
    }
}
