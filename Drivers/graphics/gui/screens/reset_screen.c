/*
 * reset_screen.c
 *
 *  Created on: Jul 30, 2021
 *      Author: David
 */

#include "reset_screen.h"
#include "screen_common.h"

screen_t Screen_reset;
screen_t Screen_reset_confirmation;
static uint8_t reset_mode;

static int cancelReset(widget_t *w) {
  reset_mode = 0;
  return last_scr;
}
static int doReset(widget_t *w) {
  return screen_main;
}
static int doSettingsReset(widget_t *w, RE_Rotation_t input) {
  reset_mode=reset_settings;
  return screen_reset_confirmation;
}
static int doProfileReset(widget_t *w, RE_Rotation_t input) {
  reset_mode=reset_profile;
  return screen_reset_confirmation;
}
static int doProfilesReset(widget_t *w, RE_Rotation_t input) {
  reset_mode=reset_profiles;
  return screen_reset_confirmation;
}
static int doFactoryReset(widget_t *w, RE_Rotation_t input) {
  reset_mode=reset_all;
  return screen_reset_confirmation;
}

static void reset_onEnter(screen_t *scr){
  if(scr==&Screen_system)
    comboResetIndex(Screen_reset.current_widget);
}

static void reset_confirmation_onExit(screen_t *scr){
  if( !isScreenTimerExpired() && reset_mode)            // Not exiting due timeout
    saveSettings(reset_mode, do_reboot);                // If we have pending save/reset, save now we have all heap free
}

static void reset_create(screen_t *scr){
  widget_t* w;
  comboBox_item_t *item;

  //  [ RESET OPTIONS COMBO ]
  //
  newWidget(&w,widget_combo,scr,NULL);

  newComboAction(w, strings[lang].RESET_Reset_Settings, &doSettingsReset, &item);
  item->dispAlign=align_left;
  newComboAction(w, strings[lang].RESET_Reset_Profile, &doProfileReset, &item);
  item->dispAlign=align_left;
  newComboAction(w, strings[lang].RESET_Reset_Profiles, &doProfilesReset, &item);
  item->dispAlign=align_left;
  newComboAction(w, strings[lang].RESET_Reset_All, &doFactoryReset, &item);
  item->dispAlign=align_left;
  newComboScreen(w, strings[lang]._BACK, screen_system, NULL);
}


static void reset_confirmation_init(screen_t *scr){
  default_init(scr);
  u8g2_SetFont(&u8g2,u8g2_font_menu);
  u8g2_SetDrawColor(&u8g2, WHITE);

  switch(reset_mode){
    case reset_settings:
      putStrAligned(strings[lang].RESET_Reset_msg_settings_1, 0, align_center);
      putStrAligned(strings[lang].RESET_Reset_msg_settings_2, 16, align_center);
      break;
    case reset_profile:
      putStrAligned(strings[lang].RESET_Reset_msg_profile_1, 0 , align_center);
      putStrAligned(strings[lang].RESET_Reset_msg_profile_2, 16, align_center);
      break;
    case reset_profiles:
      putStrAligned(strings[lang].RESET_Reset_msg_profiles_1,0 , align_center);
      putStrAligned(strings[lang].RESET_Reset_msg_profiles_2, 16, align_center);
      break;
    case reset_all:
      putStrAligned(strings[lang].RESET_Reset_msg_all_1, 0, align_center);
      putStrAligned(strings[lang].RESET_Reset_msg_all_2, 16, align_center);
      break;
  }
}


static void reset_confirmation_create(screen_t *scr){
  widget_t *w;
  button_widget_t *button;

  //  [ RESET Button Widget ]
  //
  newWidget(&w,widget_button,scr,(void*)&button);
  button->displayString=strings[lang]._RESET;
  button->selectable.tab = 1;
  button->action = &doReset;
  button->font=u8g2_font_menu;
  button->dispAlign=align_left;
  w->posY = 48;

  //  [ CANCEL Button Widget ]
  //
  newWidget(&w,widget_button,&Screen_reset_confirmation,(void*)&button);
  button->displayString=strings[lang]._CANCEL;
  button->selectable.tab = 0;
  button->action = &cancelReset;
  button->font=u8g2_font_menu;
  button->dispAlign=align_right;
  w->posY = 48;
}


void reset_screen_setup(screen_t *scr){
  scr->onEnter = &reset_onEnter;
  scr->processInput=&autoReturn_ProcessInput;
  scr->create = &reset_create;

  scr=&Screen_reset_confirmation;
  oled_addScreen(scr, screen_reset_confirmation);
  scr->init = &reset_confirmation_init;
  scr->onExit = &reset_confirmation_onExit;
  scr->processInput=&autoReturn_ProcessInput;
  scr->create = &reset_confirmation_create;
}
