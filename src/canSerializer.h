/**
 * @file canSerializer.h
 *
 * @brief Helper tool for serializing CAN messages into uniformaly sized packets for tranmission over a non CAN bus transport layer.
 *
 * @author Zain Ahmed
*/

#ifndef CANSERIALIZER_H
#define CANSERIALIZER_H

#include <stdint.h>
#include <stdbool.h>

// a library independant way of inputting and outputting CAN data.
// input all values other than the checksum.
// use a pointer to an instance of this struct to send data.
// struct is packed to ensure no padding bytes are added by GCC.
typedef struct __attribute__((__packed__))
{
  uint16_t syncWord;        // useful when using non framed transport layer
  bool extended;            // true if 29 bit ID, false if 11 bit
  uint32_t id;              // CAN frame ID
  uint8_t dlc;              // CAN frame data length code (0 - 8).
  uint8_t data[8];          // CAN frame data array.
  uint8_t checksum;         // DO NOT EDIT. This is filled by fillChecksum()
} CANFrame;

// Prototypes
void fillChecksum(CANFrame *pFrame);
bool validateChecksum(CANFrame *pFrame);

#endif // CANSERIALIZER_H
