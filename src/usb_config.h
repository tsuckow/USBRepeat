/*
********************************************************************************
                                                                                
Software License Agreement                                                      
                                                                                
Copyright © 2007-2008 Microchip Technology Inc.  All rights reserved.           
                                                                                
Microchip licenses to you the right to use, modify, copy and distribute Software
only when embedded on a Microchip microcontroller or digital signal controller  
that is integrated into your product or third party product (pursuant to the    
sublicense terms in the accompanying license agreement).                        
                                                                                
You should refer to the license agreement accompanying this Software for        
additional information regarding your rights and obligations.                   
                                                                                
SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,   
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF        
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.  
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER       
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR    
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES         
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR     
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF        
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES          
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.     
                                                                                
********************************************************************************
*/

// Created by the Microchip USBConfig Utility, Version 2.7.1.0, 5/25/2012, 22:18:45

#ifndef _usb_config_h_
#define _usb_config_h_

#if defined(__PIC24F__)
    #include <p24fxxxx.h>
#elif defined(__18CXX)
    #include <p18cxxx.h>
#elif defined(__PIC32MX__)
    #include <p32xxxx.h>
    #include "plib.h"
#else
    #error No processor header file.
#endif

#define _USB_CONFIG_VERSION_MAJOR 2
#define _USB_CONFIG_VERSION_MINOR 7
#define _USB_CONFIG_VERSION_DOT   1
#define _USB_CONFIG_VERSION_BUILD 0

// Supported USB Configurations

#define USB_SUPPORT_DEVICE

// Hardware Configuration

#define USB_PING_PONG_MODE  USB_PING_PONG__FULL_PING_PONG

#define USB_SPEED_OPTION USB_FULL_SPEED

//FIXME: Should not need this?
#define USB_ENABLE_STATUS_STAGE_TIMEOUTS    //Comment this out to disable this feature.
#define USB_STATUS_STAGE_TIMEOUT     (BYTE)45

// Peripheral Configuration

#define MY_VID            0x04D8
#define MY_PID            0x0098
#define USB_INTERRUPT
#define USB_PULLUP_OPTION      USB_PULLUP_ENABLE
#define USB_TRANSCEIVER_OPTION USB_INTERNAL_TRANSCEIVER
#define USB_EP0_BUFF_SIZE     8
#define USB_MAX_NUM_INT       (0+1+1)
#define USB_MAX_EP_NUMBER 3
#define USB_NUM_STRING_DESCRIPTORS 5

//#define USB_DISABLE_SOF_HANDLER                 
//#define USB_DISABLE_ERROR_HANDLER               
//#define USB_DISABLE_SET_DESCRIPTOR_HANDLER      

#define USB_USE_CDC
#define CDC_COMM_INTF_ID        0x0
#define CDC_COMM_EP             1
#define CDC_COMM_IN_EP_SIZE     10

#define CDC_DATA_INTF_ID        0x00
#define CDC_DATA_EP             2
#define CDC_DATA_OUT_EP_SIZE    64
#define CDC_DATA_IN_EP_SIZE     64

//#define USB_CDC_SUPPORT_DSR_REPORTING   //Signal from UART peripheral device, to CDC/USB host.  Indicates UART peripheral is ready to receive data and/or commands.
//#define USB_CDC_SUPPORT_DTR_SIGNALING   //Signal sent from the USB/CDC host, down to the UART peripheral device
//#define USB_CDC_SUPPORT_HARDWARE_FLOW_CONTROL   //Implements RTS/CTS UART flow control.
//Define the logic level for the "active" state.  Setting is only relevant if
//the respective function is enabled.  Allowed options are:
//1 = active state logic level is Vdd
//0 = active state logic level is Vss
#define USB_CDC_CTS_ACTIVE_LEVEL    0
#define USB_CDC_RTS_ACTIVE_LEVEL    0
#define USB_CDC_DSR_ACTIVE_LEVEL    0
#define USB_CDC_DTR_ACTIVE_LEVEL    0
#define USB_CDC_SUPPORT_ABSTRACT_CONTROL_MANAGEMENT_CAPABILITIES_D1 //Set_Line_Coding, Set_Control_Line_State, Get_Line_Coding, and Serial_State commands

// HID Function Configuration

#define USB_USE_HID
#define HID_INTF_ID             0x01
#define HID_EP 			3
#define HID_INT_IN_EP_SIZE      8
#define HID_INT_OUT_EP_SIZE     1
#define HID_NUM_OF_DSC          1
#define HID_RPT01_SIZE          (63+50+4)

//#define USER_SET_REPORT_HANDLER USBHIDCBSetReportHandler

#endif

