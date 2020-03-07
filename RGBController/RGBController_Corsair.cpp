/*-----------------------------------------*\
|  RGBController_Corsair.cpp                |
|                                           |
|  Generic RGB Interface for OpenAuraSDK    |
|  Corsair Vengeance RGB driver             |
|                                           |
|  Adam Honse (CalcProgrammer1) 6/13/2019   |
\*-----------------------------------------*/

#include "RGBController_Corsair.h"

RGBController_Corsair::RGBController_Corsair(CorsairController* corsair_ptr)
{
    corsair = corsair_ptr;

    name = corsair->GetDeviceName();
    location = corsair->GetDeviceLocation();

    type = DEVICE_TYPE_DRAM;

    mode Static;
    Static.name       = "Static";
    Static.value      = CORSAIR_VENGEANCE_RGB_MODE_SINGLE;
    Static.flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    Static.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(Static);

    mode Fade;
    Fade.name       = "Fade";
    Fade.value      = CORSAIR_VENGEANCE_RGB_MODE_FADE;
    Fade.flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    Fade.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(Fade);

    mode Pulse;
    Pulse.name       = "Pulse";
    Pulse.value      = CORSAIR_VENGEANCE_RGB_MODE_PULSE;
    Pulse.flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    Pulse.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(Pulse);

    SetupZones();
}

void RGBController_Corsair::SetupZones()
{
    /*---------------------------------------------------------*\
    | Create a single zone                                      |
    \*---------------------------------------------------------*/
    zone new_zone;
    new_zone.name       = "Corsair Zone";
    new_zone.type       = ZONE_TYPE_SINGLE;
    new_zone.leds_min   = corsair->GetLEDCount();
    new_zone.leds_max   = corsair->GetLEDCount();
    new_zone.leds_count = corsair->GetLEDCount();
    zones.push_back(new_zone);

    /*---------------------------------------------------------*\
    | Set up LEDs                                               |
    \*---------------------------------------------------------*/
    for(std::size_t led_idx = 0; led_idx < zones[0].leds_count; led_idx++)
    {
        led* new_led = new led();
        new_led->name = "Corsair LED";
        leds.push_back(*new_led);
    }

    SetupColors();
}

void RGBController_Corsair::ResizeZone(int zone, int new_size)
{
    /*---------------------------------------------------------*\
    | This device does not support resizing zones               |
    \*---------------------------------------------------------*/
}

void RGBController_Corsair::UpdateLEDs()
{
    RGBColor      color = colors[0];
    unsigned char red   = RGBGetRValue(color);
    unsigned char grn   = RGBGetGValue(color);
    unsigned char blu   = RGBGetBValue(color);

    corsair->SetLEDColor(red, grn, blu);
}

void RGBController_Corsair::UpdateZoneLEDs(int zone)
{
    UpdateLEDs();
}

void RGBController_Corsair::UpdateSingleLED(int led)
{
    UpdateLEDs();
}

void RGBController_Corsair::SetCustomMode()
{
    active_mode = 0;
}

void RGBController_Corsair::UpdateMode()
{
    corsair->SetMode(modes[active_mode].value);
}
