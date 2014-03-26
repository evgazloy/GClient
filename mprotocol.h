#ifndef MPROTOCOL_H
#define MPROTOCOL_H

enum
{
    LIGHT_ON = 1,
    TEN_ON = 2,
    PIPE_ON = 4,
    AUTO_ON = 8
};

enum
{
    USB_TIME_R = 0xD0,
    USB_TIME_W,
    USB_TEMP_R,
    USB_VENT_R,
    USB_VENT_W,
    USB_STATE_R,
    USB_STATE_W,
    USB_OPT_R,
    USB_OPT_W,
    USB_SAVE_W,
    USB_LOAD_W,
    USB_LOAD_DEFAULT_W,
    USB_RESET_W,
    USB_START_R,
    USB_CRITICAL_W,
    USB_CRITICAL_R
};

#pragma pack(1)
struct MTime
{
    quint8 day;
    quint8 hour;
    quint8 minute;
    quint8 second;
};

struct MOptions
{
    quint16 secondTick;
    quint16 minuteTick;
    quint8 tempTimeout;
    quint8 dayLenght;
    quint8 lightVentMin;
    quint8 lightVentMax;
    quint8 nightVentMin;
    quint8 nightVentMax;
    quint8 ventMin;
    quint8 ventMax;
    float tenTempOn;
    float tenTempOff;
    float ventTempMin;
    float ventTempMax;
    float pipeTempOn;
    float pipeTempOff;
    float criticalTempMin;
    float criticalTempMax;
    float criticalBuffer;
};

struct MMVent
{
    quint8 isAuto;
    quint8 v1;
    quint8 v2;
};
#pragma pack()

#endif // MPROTOCOL_H
