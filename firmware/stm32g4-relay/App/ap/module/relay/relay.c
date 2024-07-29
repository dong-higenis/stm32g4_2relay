#include "hw/include/gpio.h"
#include "relay.h"

#ifdef _USE_HW_CLI
static void cliRelay(cli_args_t *args);
#endif

typedef struct
{
  GPIO_TypeDef *port;
  uint32_t      pin;
  uint8_t       mode;
  GPIO_PinState on_state;
  GPIO_PinState off_state;
  bool          init_value;
  const char   *p_name;
}relay_hw_info_t;



static relay_hw_info_t relay_tbl[RELAY_CH_MAX] =
{
  {GPIOB, GPIO_PIN_5,   _DEF_OUTPUT, GPIO_PIN_SET, GPIO_PIN_RESET,   _DEF_LOW , "RELAY1" },
  {GPIOB, GPIO_PIN_15,  _DEF_OUTPUT, GPIO_PIN_SET, GPIO_PIN_RESET,   _DEF_LOW , "RELAY2" }
};

bool relayInit(void)
{
  bool ret = true;

  for (uint8_t i=RELAY_CH1; i<RELAY_CH_MAX; i++)
  {
    relayOff(i);
  }

#ifdef _USE_HW_CLI
  cliAdd("relay", cliRelay);
#endif

  return ret;
}

void relayOn(uint8_t ch)
{
  if (ch >= RELAY_CH_MAX)
  {
    return;
  }

  HAL_GPIO_WritePin(relay_tbl[ch].port, relay_tbl[ch].pin, relay_tbl[ch].on_state);
}

void relayOff(uint8_t ch)
{
  if (ch >= RELAY_CH_MAX)
  {
    return;
  }

  HAL_GPIO_WritePin(relay_tbl[ch].port, relay_tbl[ch].pin, relay_tbl[ch].off_state);
}

void relayToggle(uint8_t ch)
{
  if (ch >= RELAY_CH_MAX)
  {
    return;
  }

  HAL_GPIO_TogglePin(relay_tbl[ch].port, relay_tbl[ch].pin);
}

uint8_t relayGetState(uint8_t ch)
{
  if (ch >= RELAY_CH_MAX)
  {
    return 0xFF;
  }

  bool ret = HAL_GPIO_ReadPin(relay_tbl[ch].port, relay_tbl[ch].pin);

  return ret;
}

#ifdef _USE_HW_CLI
void cliRelay(cli_args_t *args)
{
  bool ret = false;


  if (args->argc == 1 && args->isStr(0, "info") == true)
  {
    for (int i=RELAY_CH1; i<RELAY_CH_MAX; i++)
    {
      cliPrintf("%d %-16s - %d\n", i, relay_tbl[i].p_name, relayGetState(i));
    }
    ret = true;
  }

  if (args->argc == 2 && args->isStr(0, "read") == true)
  {
    uint8_t ch;

    ch = (uint8_t)args->getData(1);

    while(cliKeepLoop())
    {
      cliPrintf("relay ch[%d] state : %s\n", ch, relayGetState(ch) == relay_tbl[ch].on_state ? "ON" : "OFF");
      delay(100);
    }

    ret = true;
  }

  if (args->argc == 3 && args->isStr(0, "write") == true &&
      (args->isStr(2, "on") == true ||
       args->isStr(2, "off") == true))
  {
    uint8_t ch;

    ch   = (uint8_t)args->getData(1);
    const char* set_state = args->getStr(2);
    bool on_state = (strcmp(set_state, "on") == 0);
    bool off_state = (strcmp(set_state, "off") == 0);

    if (on_state)
    {
      relayOn(ch);
    }
    else if (off_state)
    {
      relayOff(ch);
    }
    else
    {
      ret = false;
    }

    cliPrintf("relay ch%d %s\n", ch, on_state ? "on" : off_state ? "off" : "undefined cmd");
    ret = true;
  }

  if (args->argc == 2 && args->isStr(0, "toggle") == true)
  {
    uint8_t ch;

    ch   = (uint8_t)args->getData(1);

    bool pre_state;
    bool cur_state;

    pre_state = relayGetState(ch);

    relayToggle(ch);

    cur_state = relayGetState(ch);

    cliPrintf("relay ch%d  %s -> %s\n", ch, pre_state ? "ON" : "OFF", cur_state ? "ON" : "OFF");


    ret = true;
  }

  if (ret != true)
  {
    cliPrintf("relay info\n");
    cliPrintf("relay read   ch[0~%d]\n", RELAY_CH_MAX-1);
    cliPrintf("relay write  ch[0~%d] on:off\n", RELAY_CH_MAX-1);
    cliPrintf("relay toggle ch[0~%d] \n", RELAY_CH_MAX-1);
  }
}
#endif
