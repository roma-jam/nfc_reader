/*
    RExOS - embedded RTOS
    Copyright (c) 2011-2016, Alexey Kramarenko
    All rights reserved.
*/

#ifndef SYS_CONFIG_H
#define SYS_CONFIG_H

/*
    config.h - userspace config
 */

//----------------------------- objects ----------------------------------------------
//make sure, you know what are you doing, before change
#define SYS_OBJ_STDOUT                                      0
#define SYS_OBJ_CORE                                        1
#define SYS_OBJ_ETH                                         2

#define SYS_OBJ_ADC                                         INVALID_HANDLE
#define SYS_OBJ_DAC                                         INVALID_HANDLE
#define SYS_OBJ_STDIN                                       INVALID_HANDLE
//------------------------------ POWER -----------------------------------------------
//depends on hardware implementation
#define POWER_MANAGEMENT                                    1
//------------------------------- UART -----------------------------------------------
//disable for some memory saving if not blocking IO is required
#define UART_IO_MODE_SUPPORT                                0
//values for IO mode
#define UART_CHAR_TIMEOUT_MS                                10000
#define UART_INTERLEAVED_TIMEOUT_MS                         4
//size of every uart internal buf. Increasing this you will get less irq ans ipc calls, but faster processing
#define UART_BUF_SIZE                                       16
//generally UART is used as stdout/stdio, so fine-tuning is required only on hi load
#define UART_STREAM_SIZE                                    32

// ------------------------------- SPI -----------------------------------------------
#define SPI_DEBUG_ERRORS                                    0

//-------------------------------- USB -----------------------------------------------
#define USB_EP_COUNT_MAX                                    4
//low-level USB debug. Turn on only in case of IO problems
#define USB_DEBUG_ERRORS                                    0
#define USB_TEST_MODE_SUPPORT                               0

//----------------------------- USB device--------------------------------------------
//all other device-related debug depends on this
#define USBD_DEBUG                                          1
#define USBD_DEBUG_ERRORS                                   1
#define USBD_DEBUG_REQUESTS                                 0
//enable only for USB driver development
#define USBD_DEBUG_FLOW                                     0

//vendor-specific requests support
#define USBD_VSR                                            0

#define USBD_IO_SIZE                                        128

#define USBD_CDC_ACM_CLASS                                  0
#define USBD_RNDIS_CLASS                                    0
#define USBD_HID_KBD_CLASS                                  0
#define USBD_CCID_CLASS                                     1
#define USBD_MSC_CLASS                                      0

//----------------------- CDC ACM Device class ----------------------------------------
//At least EP size required, or data will be lost. Double EP size is recommended
#define USBD_CDC_ACM_TX_STREAM_SIZE                         32
#define USBD_CDC_ACM_RX_STREAM_SIZE                         32
#define USBD_CDC_ACM_FLOW_CONTROL                           1

#define USBD_CDC_ACM_DEBUG                                  0
#define USBD_CDC_ACM_DEBUG_FLOW                             0

//------------------------ RNDIS Device class -----------------------------------------
#define USBD_RNDIS_DEBUG                                    1
#define USBD_RNDIS_DEBUG_REQUESTS                           0
#define USBD_RNDIS_DEBUG_FLOW                               0

//must be more than MTU + MAC. And fully fit in EP size
#define USBD_RNDIS_MAX_PACKET_SIZE                          2048

//------------------------------ HIDD class -------------------------------------------
#define USBD_HID_DEBUG_ERRORS                               0
#define USBD_HID_DEBUG_REQUESTS                             0
#define USBD_HID_DEBUG_IO                                   0

//----------------------------- CCIDD class -------------------------------------------
#define USBD_CCID_REMOVABLE_CARD                            1
#define USBD_CCID_WTX_TIMEOUT_MS                            2000

#define USBD_CCID_DEBUG_ERRORS                              1
#define USBD_CCID_DEBUG_REQUESTS                            0
#define USBD_CCID_DEBUG_IO                                  0

//------------------------------ MSCD class -------------------------------------------
#define USBD_MSC_DEBUG_ERRORS                               0
#define USBD_MSC_DEBUG_REQUESTS                             0
#define USBD_MSC_DEBUG_IO                                   0

//only one LUN supported for now
#define USBD_MSC_LUN_COUNT                                  1
//-------------------------------- SCSI ----------------------------------------------
#define SCSI_SENSE_DEPTH                                    10
//can be disabled for flash memory saving
#define SCSI_LONG_LBA                                       0
#define SCSI_VERIFY_SUPPORTED                               0
//send PASS before data was written
#define SCSI_WRITE_CACHE                                    1
//SATA over SCSI. Just stub for more verbose error processing
//Found on some linux recent kernels
#define SCSI_SAT                                            0
//exclude SCSI stack. Generally sector_size * num_sectors
#define SCSI_IO_SIZE                                        512

#define SCSI_DEBUG_REQUESTS                                 1
#define SCSI_DEBUG_ERRORS                                   1

//------------------------------ PIN board -------------------------------------------
#define PINBOARD_PROCESS_SIZE                               500
#define PINBOARD_POLL_TIME_MS                               100
//--------------------------------- DAC ----------------------------------------------
#define SAMPLE                                              uint16_t
//disable for some flash saving
#define WAVEGEN_SQUARE                                      1
#define WAVEGEN_TRIANGLE                                    0
#define WAVEGEN_SINE                                        0
//--------------------------------- ETH ----------------------------------------------
#define ETH_AUTO_NEGOTIATION_TIME                           5000

#define ETH_DOUBLE_BUFFERING                                1
//------------------------------- TCP/IP ---------------------------------------------
#define TCPIP_DEBUG                                         1
#define TCPIP_DEBUG_ERRORS                                  1

#define TCPIP_MTU                                           1500
#define TCPIP_MAX_FRAMES_COUNT                              10

//----------------------------- TCP/IP MAC --------------------------------------------
//software MAC filter. Turn on in case of hardware is not supporting
#define MAC_FILTER                                          0
#define MAC_FIREWALL                                        1
#define TCPIP_MAC_DEBUG                                     0

//----------------------------- TCP/IP ARP --------------------------------------------
#define ARP_DEBUG                                           1
#define ARP_DEBUG_FLOW                                      1

#define ARP_CACHE_SIZE_MAX                                  10
//in seconds
#define ARP_CACHE_INCOMPLETE_TIMEOUT                        5
#define ARP_CACHE_TIMEOUT                                   600

//----------------------------- TCP/IP IP ---------------------------------------------
#define IP_DEBUG                                            1
#define IP_DEBUG_FLOW                                       0

//set, if not supported by hardware
#define IP_CHECKSUM                                         1

#define IP_FRAGMENTATION                                    1
#define IP_FRAGMENTATION_ASSEMBLY_TIMEOUT                   10
//must be less TCPIP_MTU * TCPIP_MAX_FRAMES_COUNT
#define IP_MAX_LONG_SIZE                                    5000
#define IP_MAX_LONG_PACKETS                                 2

#define IP_FIREWALL                                         1

//---------------------------- TCP/IP ICMP --------------------------------------------
#define ICMP                                                1
#define ICMP_DEBUG                                          1

#define ICMP_ECHO_TIMEOUT                                   5
//reply on ICMP echo and echo request
#define ICMP_ECHO                                           1

//----------------------------- TCP/IP UDP --------------------------------------------
#define UDP                                                 0
#define UDP_DEBUG                                           0
#define UDP_DEBUG_FLOW                                      0

//----------------------------- TCP/IP TCP --------------------------------------------
#define TCP_DEBUG                                           1
#define TCP_RETRY_COUNT                                     3
#define TCP_KEEP_ALIVE                                      0
#define TCP_TIMEOUT                                         30000
//0 - don't limit
#define TCP_HANDLES_LIMIT                                   10
//Low-level debug. only for development
#define TCP_DEBUG_FLOW                                      0
#define TCP_DEBUG_PACKETS                                   0

//---------------------------- HTTP server---------------------------------------------
#define HS_PROCESS_SIZE                                     900
#define HS_PROCESS_PRIORITY                                 161

#define HS_DEBUG                                            0
#define HS_DEBUG_HEAD                                       0
//URL and header must fit completely in IO. Default to MSS
#define HS_IO_SIZE                                          1460

//---------------------------- TLS server---------------------------------------------
//cryptography can take much space.
#define TLS_PROCESS_SIZE                                    3048
#define TLS_PROCESS_PRIORITY                                160

#define TLS_DEBUG                                           1
#define TLS_DEBUG_REQUESTS                                  1
#define TLS_DEBUG_FLOW                                      0
//DON'T FORGET TO REMOVE IN PRODUCTION!!!
#define TLS_DEBUG_SECRETS                                   0
#define TLS_IO_SIZE                                         1460
//--------------------------------- SDMMC ---------------------------------------------
#define SDMMC_DEBUG                                         1

//---------------------------------- VFS ----------------------------------------------
#define VFS_DEBUG_INFO                                      1
#define VFS_DEBUG_ERRORS                                    1
#define VFS_MAX_FILE_PATH                                   256
#define VFS_MAX_HANDLES                                     5
//enable BER support
#define VFS_BER                                             1
#define VFS_BER_DEBUG_INFO                                  1
#define VFS_BER_DEBUG_ERRORS                                1

//align data sectors by cluster start offset (recommended to enable for flash storage)
#define VFS_CLUSTER_ALIGN                                   1
//update modify/access time (recommended to disable for flash storage)
#define VFS_FILE_ATTRIBUTES_UPDATE                          0

//01.09.2016 as default if not rtc used
#define VFS_BASE_DATE                                       736207

#endif // SYS_CONFIG_H
