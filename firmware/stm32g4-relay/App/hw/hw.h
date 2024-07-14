#ifndef HW_H_
#define HW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hw_def.h"

//============== COMMON ===============
#include "qbuffer.h"
#include "util.h"
//==============   HW   ===============
#include "led.h"
#include "uart.h"
#include "cli.h"
#include "log.h"
#include "swtimer.h"
#include "button.h"
#include "gpio.h"
#include "i2c.h"
#include "eeprom.h"
#include "spi.h"
#include "spi_flash.h"
#include "can.h"
#include "usb.h"
#include "cdc.h"





bool hwInit(void);


#ifdef __cplusplus
}
#endif

#endif
