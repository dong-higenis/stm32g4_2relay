#ifndef AP_MODULE_RELAY_H_
#define AP_MODULE_RELAY_H_

#include "ap_def.h"

typedef enum
{
  RELAY_CH1,
  RELAY_CH2,
  RELAY_CH_MAX
}RelayChannel_t;




bool relayInit(void);
void relayOn(uint8_t ch);
void relayOff(uint8_t ch);
void relayToggle(uint8_t ch);
uint8_t relayGetState(uint8_t ch);


#endif /* AP_MODULE_RELAY_H_ */
