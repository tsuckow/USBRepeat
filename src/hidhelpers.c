
#include "USB/usb.h"
#include "USB/usb_function_hid.h"

extern USB_HANDLE lastINTransmission;
extern USB_HANDLE lastOUTTransmission;

BYTE const MouseButtonLeft = 0x4;
BYTE const MouseButtonMiddle = 0x2;
BYTE const MouseButtonRight = 0x1;
#define MouseButtonNone 0x0

#define KeyboardModNone        0
BYTE const KeyboardModLeftCtrl  = 1 << 0;
BYTE const KeyboardModLeftShift = 1 << 1;
BYTE const KeyboardModLeftAlt   = 1 << 2;
BYTE const KeyboardModLeftGui   = 1 << 3;
BYTE const KeyboardModRightCtrl = 1 << 4;
BYTE const KeyboardModRightShift= 1 << 5;
BYTE const KeyboardModRightAlt  = 1 << 6;
BYTE const KeyboardModRightGui  = 1 << 7;

#define KeyboardKCNone          0x00
#define KeyboardKCErrorRollOver 0x01

void TxMouseData(CHAR xaxis, CHAR yaxis) {

    BYTE buttons = MouseButtonNone;

    //CHAR xaxis = 1;
    //CHAR yaxis = 1;

    static BYTE hid_report[5] = {HID_MOUSE_ID,MouseButtonNone,0,0,0};

    if( !HIDTxHandleBusy(lastINTransmission) )
    {
        hid_report[1] = buttons;
        hid_report[2] = xaxis;
        hid_report[3] = yaxis;
        hid_report[4] = 0; //Mouse Wheel

        lastINTransmission = HIDTxPacket(HID_EP, (BYTE*)hid_report, 0x05);
    }
}

//Keyboard Stuff

BYTE keyboardModifiers = KeyboardModNone;
BYTE keyboardkc[6] = {KeyboardKCNone,KeyboardKCNone,KeyboardKCNone,KeyboardKCNone,KeyboardKCNone,KeyboardKCNone};

void KeyboardReset() {
    keyboardModifiers = KeyboardModNone;
    int i;
    for(i = 0; i < 6; ++i)
        keyboardkc[i] = KeyboardKCNone;
}

void KeyboardPressKey( BYTE key ) {
    int empty = -1;

    int i;
    for(i = 5; i >= 0; --i) {
        if( keyboardkc[i] == key )
        {
            return;
        }

        if( keyboardkc[i] == KeyboardKCNone )
        {
            empty = i;
        }
    }

    if( empty < 0 )
    {
        int i;
        for(i = 0; i < 6; ++i)
            keyboardkc[i] = KeyboardKCErrorRollOver;
    }
    else
    {
        keyboardkc[empty] = key;
    }
}

void KeyboardReleaseKey( BYTE key ) {

    if( keyboardkc[0] == KeyboardKCErrorRollOver )
    {
        int i;
        for(i = 0; i < 6; ++i)
            keyboardkc[i] = KeyboardKCNone;
    }
    else
    {
        int i;
        for(i = 0; i < 6; ++i) {
            if( keyboardkc[i] == key )
            {
                keyboardkc[i] = KeyboardKCNone;
            }
        }
    }
}



void KeyboardTxData() {
    static BYTE hid_report[9] = {HID_KEYBOARD_ID,KeyboardModNone,0x00/*RESERVED*/,KeyboardKCNone,KeyboardKCNone,KeyboardKCNone,KeyboardKCNone,KeyboardKCNone,KeyboardKCNone};

    if( !HIDTxHandleBusy(lastINTransmission) )
    {
        hid_report[1] = keyboardModifiers;
        int i;
        for(i = 0; i < 6; ++i)
            hid_report[3 + i] = keyboardkc[i];

        lastINTransmission = HIDTxPacket(HID_EP, (BYTE*)hid_report, 0x09);
    }
}