/*
 * pn532_config.h
 *
 *  Created on: 19 рту. 2017 у.
 *      Author: RomaJam
 */

#ifndef PN532_CONFIG_H_
#define PN532_CONFIG_H_

// ================================
#define PN_DEBUG                1

// ================================ CONFIGURATION ==============================
#define PN_SPI                  SPI_1

#define PN_IRQ_PIN              B1
#define PN_NSS_PIN              B0
#define PN_RST_PIN              A4
#define PN_SCK_PIN              A5
#define PN_MISO_PIN             A6
#define PN_MOSI_PIN             A7

#define PN_MAX_CMD_SIZE         274  // PN max data size: 264 + 8 (Prologue) + 2 (Epilogue)
#define PN_MAX_DATA_SIZE        262  // Max Data Lenght 262 byte um. page 29

#pragma pack(push, 1)
typedef struct {
    uint8_t Preamble;       // 0x00
    uint8_t SoPCH;          // Start of Packet Code Low - 0x00 always
    uint8_t SoPCL;          // Start of Packet Code High - 0xFF always
    uint8_t NPLC;           // Normal Packet Length Checksum - 0xFF always
    uint8_t NPL;            // Normal Packet Length - 0xFF always
    uint8_t LengthHi;       // MSByte of Length
    uint8_t LengthLo;       // LSByte of Length
    uint8_t LCS;            // Length Checksum
} PN532_PREAMBULA;

typedef struct {
    uint8_t TFI;
    uint8_t PD0;
    uint8_t Tg;
    uint8_t Buf[PN_MAX_DATA_SIZE - 1];
} PN532_DATA;

typedef struct {
    uint8_t DCS;
    uint8_t Postamble;      // 0x00
} PN532_POSTAMBULA;

typedef struct {
    uint8_t seq;
    PN532_PREAMBULA preamb;
    PN532_DATA data;
    PN532_POSTAMBULA post;
} PN532_FRAME;
#pragma pack(pop)


#endif /* PN532_CONFIG_H_ */
