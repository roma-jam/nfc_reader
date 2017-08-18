/*
 * usb_desc.h
 *
 *  Created on: 23 мая 2017 г.
 *      Author: RLeonov
 */

#ifndef USB_DESC_H_
#define USB_DESC_H_


#include "../rexos/userspace/usb.h"
#include "../rexos/userspace/ccid.h"
#include "config.h"
#include "sys_config.h"

#pragma pack(push, 1)

const USB_DEVICE_DESCRIPTOR __DEVICE_DESCRIPTOR = {
    sizeof(USB_DEVICE_DESCRIPTOR),                                            /*bLength */
    USB_DEVICE_DESCRIPTOR_TYPE,                                               /*bDescriptorType*/
    0x0110,                                                                   /*bcdUSB */
    0x00,                                                                     /*bDeviceClass*/
    0x00,                                                                     /*bDeviceSubClass*/
    0x00,                                                                     /*bDeviceProtocol*/
    64,                                                                       /*bMaxPacketSize*/
    0x21BB,                                                                   /*idVendor: temporary*/
    0xF000,                                                                   /*idProduct*/
    0x0100,                                                                   /*bcdDevice release*/
    1,                                                                        /*Index of manufacturer  string*/
    2,                                                                        /*Index of product string*/
    3,                                                                        /*Index of serial number string*/
    1                                                                         /*bNumConfigurations*/
};

typedef struct {
    USB_CONFIGURATION_DESCRIPTOR configuration;
    //CCID
    USB_INTERFACE_DESCRIPTOR comm_interface;
    CCID_DESCRIPTOR ccid_descriptor;
    USB_ENDPOINT_DESCRIPTOR ccid_endpoints[3];
} CONFIGURATION;

const CONFIGURATION __CONFIGURATION_DESCRIPTOR = {
    //CONFIGURATION descriptor
    {
        sizeof(USB_CONFIGURATION_DESCRIPTOR),                               /*bLength*/
        USB_CONFIGURATION_DESCRIPTOR_TYPE,                                  /*bDescriptorType*/
        sizeof(CONFIGURATION),                                              /*wTotalLength*/
        1,                                                                  /*bNumInterfaces*/
        1,                                                                  /*bConfigurationValue*/
        0,                                                                  /*iConfiguration*/
        0x80,                                                               /*bmAttributes*/
        50                                                                  /*bMaxPower*/
    },
    //CCID INTERFACE descriptor
    {
        sizeof(USB_INTERFACE_DESCRIPTOR),                                   /*bLength*/
        USB_INTERFACE_DESCRIPTOR_TYPE,                                      /*bDescriptorType*/
        USB_CCID_INTERFACE,                                                 /*bInterfaceNumber*/
        0,                                                                  /*bAlternateSetting*/
        3,                                                                  /*bNumEndpoints*/
        CCID_INTERFACE_CLASS,                                               /*bInterfaceClass*/
        0,                                                                  /*bInterfaceSubClass*/
        0,                                                                  /*bInterfaceProtocol*/
        0                                                                   /*iInterface*/
    },

    //CCID descriptor
    {
        sizeof(CCID_DESCRIPTOR),                                            /* bLength */
        USB_FUNCTIONAL_DESCRIPTOR,                                          /* bDescriptorType */
        0x110,                                                              /* bcdCCID */
        0,                                                                  /* bMaxSlotIndex */
        CCID_VOLTAGE_5_0V,                                                  /* bVoltageSupport */
        CCID_PROTOCOL_T1,                                                   /* dwProtocols */
        4000,                                                               /* dwDefaultClock */
        4000,                                                               /* dwMaximumClock */
        0,                                                                  /* bNumClockSupported */
        672,                                                                /* dwDataRate */
        250000,                                                             /* dwMaxDataRate */
        0,                                                                  /* bNumDataRatesSupported */
        261,                                                                /* dwMaxIFSD */
        0,                                                                  /* dwSynchProtocol */
        0,                                                                  /* dwMechanical */
        CCID_FEATURE_AUTO_CONFIG | CCID_FEATURE_AUTO_ACTIVATE |
        CCID_FEATURE_AUTO_VOLTAGE | CCID_FEATURE_AUTO_CLOCK |
        CCID_FEATURE_AUTO_BAUD | CCID_FEATURE_AUTO_PPS_ACTIVE |
        CCID_FEATURE_AUTO_IFCD | CCID_FEATURE_APDU,                         /* dwFeatures */
        271,                                                                /* dwMaxCCIDMessageLength */
        0,                                                                  /* bClassGetResponse */
        0,                                                                  /* bClassEnvelope */
        0,                                                                  /* wLcdLayout */
        0,                                                                  /* bPINSupport */
        1                                                                   /* bMaxCCIDBusySlots */
    },
    {
        //INTERRUPT endpoint descriptor
        {
            sizeof(USB_ENDPOINT_DESCRIPTOR),                                /*bLength*/
            USB_ENDPOINT_DESCRIPTOR_TYPE,                                   /*bDescriptorType*/
            0x80 | 0x1,                                                     /*bEndpointAddress*/
            USB_EP_BM_ATTRIBUTES_INTERRUPT,                                 /*bmAttributes*/
            8,                                                              /*wMaxPacketSize*/
            5                                                               /*bInterval*/
        },
        //BULK endpoint descriptors
        {
            sizeof(USB_ENDPOINT_DESCRIPTOR),                                /*bLength*/
            USB_ENDPOINT_DESCRIPTOR_TYPE,                                   /*bDescriptorType*/
            0x00 | 0x2,                                                     /*bEndpointAddress*/
            USB_EP_BM_ATTRIBUTES_BULK,                                      /*bmAttributes*/
            64,                                                             /*wMaxPacketSize*/
            0                                                               /*bInterval*/
        },
        {
            sizeof(USB_ENDPOINT_DESCRIPTOR),                                /*bLength*/
            USB_ENDPOINT_DESCRIPTOR_TYPE,                                   /*bDescriptorType*/
            0x80 | 0x2,                                                     /*bEndpointAddress*/
            USB_EP_BM_ATTRIBUTES_BULK,                                      /*bmAttributes*/
            64,                                                             /*wMaxPacketSize*/
            0                                                               /*bInterval*/
        }
    }
};

const char __STRING_WLANGS[] = {
    1 * 2 + 2,                                                              /*bLength*/
    USB_STRING_DESCRIPTOR_TYPE,                                             /*bDescriptorType*/
    0x09, 0x04                                                              // 0x409 - English
};

const char __STRING_MANUFACTURER[] = {
    4 * 2 + 2,                                                             /*bLength*/
    USB_STRING_DESCRIPTOR_TYPE,                                             /*bDescriptorType*/
    'O', 0,
    'B', 0,
    'B', 0,
    'S', 0
};

const char __STRING_PRODUCT[] = {
    10 * 2 + 2,                                                              /*bLength*/
    USB_STRING_DESCRIPTOR_TYPE,                                             /*bDescriptorType*/
    'N', 0,
    'F', 0,
    'C', 0,
    ' ', 0,
    'R', 0,
    'e', 0,
    'a', 0,
    'd', 0,
    'e', 0,
    'r', 0
};

const char __STRING_SERIAL[] = {
    8 * 2 + 2,                                                             /*bLength*/
    USB_STRING_DESCRIPTOR_TYPE,                                             /*bDescriptorType*/
    '1', 0,
    '2', 0,
    '3', 0,
    '4', 0,
    'A', 0,
    'B', 0,
    'C', 0,
    'D', 0
};
#pragma pack(pop)


#endif /* USB_DESC_H_ */
