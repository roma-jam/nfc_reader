/*
 * pn532_config.h
 *
 *  Created on: 19 рту. 2017 у.
 *      Author: RomaJam
 */

#ifndef PN532_CONFIG_H_
#define PN532_CONFIG_H_

// =============================================================================
#define PN_DEBUG                        0
#define PN_DEBUG_DATA_EXCHANGE          0

// ================================ CONFIGURATION ==============================
#define PN_SPI                          SPI_1

#define PN_IRQ_PIN                      B1
#define PN_NSS_PIN                      B0
#define PN_RST_PIN                      A4
#define PN_SCK_PIN                      A5
#define PN_MISO_PIN                     A6
#define PN_MOSI_PIN                     A7

#define PN_MAX_CMD_SIZE                 274  // PN max data size: 264 + 8 (Prologue) + 2 (Epilogue)
#define PN_MAX_DATA_SIZE                262  // Max Data Lenght 262 byte um. page 29

// =================================== Constants ==============================
// Preamble command bytes
#define PN_CMD_TYPE_DATA_WRITE         (1 << 0)
#define PN_CMD_TYPE_STATUS_READ        (1 << 1)
#define PN_CMD_TYPE_DATA_READ          (3 << 0)
// Frame identifier
// Pn CMDs
#define PN_FRAME_PREAMBLE               0x00
#define PN_FRAME_TFI_TRANSMIT           0xD4
#define PN_FRAME_TFI_RECIEVE            0xD5
#define PN_FRAME_POSTAMBLE              0x00

// Pn CMD Length
#define PN_ACK_NACK_LENGTH              (uint8_t)6
#define PN_SERVICE_BYTES_IN_DATA_EX     (uint8_t)3
#define PN_RESPONSE_START_FRAME_LENGTH  (uint8_t)5
#define PN_RESPONSE_EPILOGUE_LENGTH     (uint8_t)2
// Command codes
// Miscellaneous
#define PN_CMD_DIAGNOSE                 0x00
#define PN_CMD_GET_FIRMWARE_VERSION     0x02
#define PN_CMD_GET_GENERAL_STATUS       0x04
#define PN_CMD_READ_REGISTER            0x06
#define PN_CMD_WRITE_REGISTER           0x08
#define PN_CMD_READ_GPIO                0x0C
#define PN_CMD_WRITE_GPIO               0x0E
#define PN_CMD_SET_SERIAL_BAUD_RATE     0x10
#define PN_CMD_SET_PARAMETERS           0x12
#define PN_CMD_SAM_CONFIGURATION        0x14
#define PN_CMD_POWER_DOWN               0x16
// RF communication
#define PN_CMD_RF_CONFIGURATION         0x32
#define PN_CMD_RF_REGULATION_TEST       0x58
// Initiatior
#define PN_CMD_IN_JUMP_FOR_DEP          0x56
#define PN_CMD_IN_JUMP_FOR_PSL          0x46
#define PN_CMD_IN_LIST_PASSIVE_TARGET   0x4A
#define PN_CMD_IN_ATR                   0x50
#define PN_CMD_IN_PSL                   0x4E
#define PN_CMD_IN_DATA_EXCHANGE         0x40
#define PN_CMD_IN_COMMUNICATE_THRU      0x42
#define PN_CMD_IN_DESELECT              0x44
#define PN_CMD_IN_RELEASE               0x52
#define PN_CMD_IN_SELECT                0x54
#define PN_CMD_IN_AUTO_POLL             0x60
// Target
#define PN_CMD_TG_INIT_AS_TARGET        0x8C
#define PN_CMD_TG_SET_GENERAL_BYTES     0x92
#define PN_CMD_TG_GET_DATA              0x86
#define PN_CMD_TG_SET_DATA              0x8E
#define PN_CMD_TG_SET_META_DATA         0x94
#define PN_CMD_TG_GET_INITIATOR_COMMAND 0x88
#define PN_CMD_TG_RESPONSE_TO_INITIATOR 0x90
#define PN_CMD_TG_GET_TARGET_STATUS     0x8A

// Replies
#define PN_RPL_DIAGNOSE                 0x01
#define PN_RPL_GET_FIRMWARE_VERSION     0x03
#define PN_RPL_GET_GENERAL_STATUS       0x05
#define PN_RPL_POWER_DOWN               0x17
#define PN_RPL_TG_INIT_AS_TARGET        0x8D
#define PN_RPL_TG_GET_DATA              0x87
#define PN_RPL_TG_SET_DATA              0x8F
#define PN_RPL_TG_GET_INITIATOR_COMMAND 0x89
#define PN_RPL_TG_RESPONSE_TO_INITIATOR 0x91
#define PN_RPL_TG_GET_TARGET_STATUS     0x8B

#define PN_RPL_READ_REGISTER            0x07
#define PN_RPL_WRITE_REGISTER           0x09
#define PN_RPL_IN_LIST_PASSIVE_TARGET   0x4B
#define PN_RPL_IN_DESELECT              0x45
#define PN_RPL_IN_SELECT                0x55

// Parameters bits for SetParameters function (p. 83)
#define PN_PARAM_NAD                        (1 << 0)
#define PN_PARAM_DID                        (1 << 1)
#define PN_PARAM_AUTO_ATR_RES               (1 << 2)
#define PN_PARAM_IRQ                        (1 << 3)
#define PN_PARAM_AUTO_RATS                  (1 << 4)
#define PN_PARAM_ISO14443_4_PICC            (1 << 5)
#define PN_PARAM_REMOVE_PREAMBULEPOSTAMBLE  (1 << 6)

// Mifare commands
#define MIFARE_CMD_READ                     0x30
#define MIFARE_CMD_WRITE                    0xA2

#pragma pack(push, 1)
typedef struct {
    uint8_t TFI;
    uint8_t PD0;
    // Tg - first byte in user data
} PN532_DATA;

typedef struct {
    uint8_t cmd_type;
    // preambule
    uint8_t start_byte;       // 0x00
    uint8_t sopCH;            // Start of Packet Code High - 0x00 always
    uint8_t sopCL;            // Start of Packet Code Low - 0xFF always
    uint8_t NPLC;             // Normal Packet Length Checksum - 0xFF always
    uint8_t NPL;              // Normal Packet Length - 0xFF always
    uint8_t data_size_hi;     // MSByte of Length
    uint8_t data_size_lo;     // LSByte of Length
    uint8_t LCS;              // Length Checksum
    // data
    PN532_DATA data;
} PN532_START_FRAME;

typedef struct {
    // postambule
    uint8_t DCS;
    uint8_t stop_byte;      // 0x00
} PN532_STOP_FRAME;
#pragma pack(pop)


#endif /* PN532_CONFIG_H_ */
