/*
 * oled.h
 *
 *  Created on: Aug 1, 2017
 *      Author: jose
 */

#ifndef GRAPHICS_GUI_OLED_H_
#define GRAPHICS_GUI_OLED_H_

#include "screen.h"

screen_t *oled_addScreen(uint8_t index);
void oled_draw(void);
void oled_init(RE_Rotation_t (*Rotation)(RE_State_t*), RE_State_t *State);
void oled_processInput(void);
void oled_update(void);
void oled_handle(void);
#endif /* GRAPHICS_GUI_OLED_H_ */
