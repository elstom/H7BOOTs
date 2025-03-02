#include <bootloader.h>

#include "fatfs.h"
#include "usb_host.h"


#define APPCheckID "Like"
#define APPCheckNAME "check.cck"

extern USBH_HandleTypeDef hUsbHostHS;

typedef enum
{
    FILE_READY = 0,
    FILE_UPDATED,
    FILE_JUMP
} fileSystemStatus;

bool CheckUDiskID(void)
{
    FIL file;

    if (f_mount(&USBHFatFS, (TCHAR const*)USBHPath, 0) == FR_OK)
    {
        if (f_open(&file, APPCheckNAME, 0) == FR_OK)
        {
            uint8_t buffer[10];
            UINT bytesRead;
            if (f_read(&file, buffer, sizeof(buffer), &bytesRead) == FR_OK)
            {
                if (bytesRead == 4)
                {
                    uint32_t temp = (hUsbHostHS.device.DevDesc.idProduct << 16) | hUsbHostHS.device.DevDesc.idVendor;
                    temp ^= *(uint32_t*)APPCheckID;
                    if (~temp == *(uint32_t*)buffer)
                    {
                        return HAL_OK;
                    }
                }
            }
            f_close(&file);
        }
        f_mount(NULL, (TCHAR const*)USBHPath, 1);
    }
    return HAL_ERROR;
}

void UpdateProgramProcess(void)
{
    static fileSystemStatus status = FILE_READY;

    switch (status)
    {
    case FILE_READY:
        if (f_mount(&USBHFatFS, USBHPath, 0) == FR_OK)
        {
            
        }
        break;
    case FILE_UPDATED:
        break;
    case FILE_JUMP:
    default:
        break;
    }
}

























