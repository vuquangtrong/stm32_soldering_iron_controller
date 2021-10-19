/*
 * boot_screen.c
 *
 *  Created on: Jan 12, 2021
 *      Author: David    Original work by Jose Barros (PTDreamer), 2017
 */

#include "boot_screen.h"
#include "screen_common.h"
#define SPLASH_TIMEOUT 1000


//-------------------------------------------------------------------------------------------------------------------------------
// Boot Screen variables
//-------------------------------------------------------------------------------------------------------------------------------
screen_t Screen_boot;
static widget_t *Widget_profile;
static widget_t *Widget_lang;
static widget_t *Widget_ok;
static uint8_t boot_step=0;

// Credits: Jesus Vallejo  https://github.com/jesusvallejo/
const uint8_t splashXBM[] = {
  128, 64,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x54, 0x55, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x0F, 0x00, 0x00, 0xF2, 0x03,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF,
  0x00, 0xC0, 0xF3, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xFE, 0xFF, 0x0F, 0x00, 0xF0, 0xF3, 0xFF, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xC0, 0x83, 0x20, 0x39, 0x00, 0xFC, 0xF3, 0xFF,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFA, 0x3B, 0x09,
  0x00, 0xCC, 0xF3, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xF8, 0x83, 0xBB, 0xFA, 0x00, 0x87, 0xF3, 0xFF, 0x0F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xBE, 0xBB, 0x0B, 0x80, 0x03, 0x00, 0xF8,
  0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x83, 0xBB, 0x1B,
  0xC0, 0x07, 0x00, 0xF0, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xFE, 0xFF, 0x0F, 0xC0, 0xCF, 0xFF, 0xE3, 0x3F, 0xF0, 0x33, 0xF3,
  0x03, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x3F, 0xE0, 0xFF, 0xFF, 0x07,
  0x00, 0xF0, 0x33, 0xF3, 0x03, 0x00, 0x00, 0x00, 0x00, 0x7E, 0xCC, 0x0F,
  0xF0, 0xFF, 0x07, 0x0C, 0x00, 0xC0, 0x30, 0x33, 0x00, 0x00, 0x00, 0x00,
  0xE0, 0xFF, 0xBB, 0xFF, 0xF0, 0xFF, 0x00, 0xF8, 0xFF, 0xC0, 0xF0, 0xF3,
  0x01, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xDC, 0x0F, 0xF0, 0x7F, 0x00, 0xE0,
  0xF9, 0xC0, 0xF0, 0xF3, 0x01, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xEB, 0xFF,
  0xF8, 0x3F, 0x00, 0xC0, 0xF0, 0xC1, 0x30, 0x33, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x7E, 0x8C, 0x0F, 0xF8, 0x3F, 0x00, 0x40, 0xE0, 0xC1, 0x30, 0xF3,
  0x03, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x7F, 0x00, 0x1E, 0x60, 0x80,
  0xF0, 0xC1, 0x30, 0xF3, 0x03, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x0F,
  0x00, 0x1E, 0xF8, 0x81, 0xF9, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x54, 0x55, 0x05, 0x7C, 0x0E, 0xF8, 0x01, 0xF9, 0x03, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x54, 0x01, 0x7C, 0x0E, 0xFC, 0x03,
  0xF9, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x01,
  0x7C, 0x0E, 0xFC, 0x03, 0xF9, 0xF3, 0xF3, 0x33, 0xF0, 0xF3, 0xF3, 0xF3,
  0x33, 0xF3, 0x43, 0x00, 0x7C, 0x0E, 0xF8, 0x01, 0xF9, 0xF3, 0xF3, 0x33,
  0x70, 0xF2, 0xF3, 0xF3, 0x73, 0xF3, 0x43, 0x00, 0x7C, 0x1E, 0xF8, 0x81,
  0x19, 0x33, 0x30, 0x33, 0x70, 0x32, 0x30, 0xC2, 0xF0, 0x33, 0x00, 0x00,
  0x7C, 0x1E, 0x60, 0x80, 0x09, 0xF0, 0x33, 0x33, 0x70, 0xF2, 0xF1, 0xC3,
  0xF0, 0xB3, 0x03, 0x00, 0x7C, 0x1E, 0x00, 0x80, 0x09, 0xF0, 0x33, 0x33,
  0x70, 0xF2, 0xB1, 0xC0, 0xB0, 0xB3, 0x03, 0x00, 0x7C, 0x1E, 0x60, 0x80,
  0x19, 0x03, 0x33, 0x33, 0x70, 0x32, 0xB0, 0xC1, 0x30, 0x33, 0x03, 0x00,
  0x3C, 0x3C, 0x60, 0xC0, 0xF9, 0xF3, 0xF3, 0xF3, 0x73, 0xF2, 0x33, 0xF3,
  0x33, 0xF3, 0x03, 0x00, 0x18, 0x78, 0x60, 0x00, 0xF8, 0xF1, 0xF3, 0xF3,
  0xF3, 0xF3, 0x33, 0xF3, 0x33, 0xF3, 0x03, 0x00, 0x18, 0xF8, 0x60, 0x00,
  0xF8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x30, 0xFC, 0x60, 0xF8, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x70, 0xFE, 0x60, 0xF8, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x7F, 0x60, 0xF0,
  0x7F, 0xF0, 0xF3, 0xF3, 0xF3, 0xF3, 0xF3, 0x33, 0x03, 0x00, 0x00, 0x00,
  0xC0, 0x3F, 0x60, 0xE0, 0x3F, 0xF0, 0xF3, 0xF3, 0xF3, 0xF3, 0xF3, 0x73,
  0x03, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x60, 0xC0, 0x1F, 0x30, 0xC0, 0x30,
  0xC3, 0xC0, 0x30, 0xF3, 0x03, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x60, 0xC0,
  0x0F, 0xF0, 0xC3, 0xF0, 0xC3, 0xC0, 0x30, 0xB3, 0x03, 0x00, 0x00, 0x00,
  0x00, 0x1E, 0x60, 0x80, 0x07, 0xF0, 0xC3, 0xF0, 0xC3, 0xC0, 0x30, 0x33,
  0x03, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x60, 0x00, 0x03, 0x00, 0xC3, 0x30,
  0xC3, 0xC0, 0x30, 0x33, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
  0x00, 0xF0, 0xC3, 0x30, 0xC3, 0xF0, 0xF3, 0x33, 0x03, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x60, 0x00, 0x00, 0xF0, 0xC3, 0x30, 0xC3, 0xF0, 0xF3, 0x33,
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01,
  0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0x1D, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0x03, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1D, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xEF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xDD, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E,
  0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDD, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1D, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF,
  0xFF, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, };

void boot_screen_create(screen_t *scr);

//=========================================================
static void * getProfile() {
  temp = profile;
  return &temp;
}
static void setProfile(uint32_t *val) {
  profile=*val;
}
//=========================================================
static void * getLanguage() {
  temp = systemSettings.settings.language;
  return &temp;
}
static void setLanguage(uint32_t *val) {
  lang = *val;
  systemSettings.settings.language=*val;
}
//=========================================================

static int SaveSetup(widget_t* w) {
  loadProfile(profile);
  saveSettingsFromMenu(save_Settings);
  boot_step++;
  return -1;
}
//=========================================================
void draw_boot_strings(void){
  u8g2_SetFont(&u8g2, u8g2_font_menu );
  u8g2_SetDrawColor(&u8g2, WHITE);
  putStrAligned(strings[lang].boot_firstBoot, 0, align_center);
  u8g2_DrawHLine(&u8g2, 0, 13, OledWidth);
  u8g2_DrawUTF8(&u8g2, 0, 18, strings[lang].boot_Profile);
  u8g2_DrawUTF8(&u8g2, 0, 34, strings[lang]._Language);
}

static uint8_t boot_screen_draw(screen_t *scr){
  uint8_t refresh = scr->refresh;                 // Save refresh state. If screen set to be erased, default_screenDraw will erase it.
  uint8_t ret = default_screenDraw(scr);          // So we need to run screenDraw first and save the return value

  if(refresh!=screen_Idle && boot_step==1){       // If screen not idle (erased) and boot_step=1 (Setup screen)
    draw_boot_strings();                          // Redraw strings
  }

  return (ret);                                   // return the ret value from screenDraw
}


int boot_screen_processInput(screen_t * scr, RE_Rotation_t input, RE_State_t *state) {
  if(current_lang!=lang){                                                       // If language changed
    current_lang=lang;
    oled_destroy_screen(scr);                                                   // Destroy and create the screen
    boot_screen_create(scr);
    scr->current_widget = Widget_lang;
    scr->refresh = screen_Erase;
    ((editable_widget_t*)Widget_lang->content)->selectable.state=widget_edit;
    widgetEnable(Widget_lang);
    widgetEnable(Widget_profile);
    widgetEnable(Widget_ok);
  }

  if(input!=Rotate_Nothing){
    wakeOledDim();
  }
  handleOledDim();

  switch(boot_step){

    case 2:
      systemSettings.setupMode=disable;                                                               // Save button clicked, disable setup mode
      setSafeMode(disable);                                                                           // Disable safe mode and exit

    case 0:
      if(checkScreenTimer(SPLASH_TIMEOUT)){                                                           // After splash timeout
        if(!systemSettings.setupMode){                                                                // If not in setup mode
          ADC_Reset_measures();                                                                       // Reset the averages, show current values to avoid filtering delay at startup
          resetIronError();                                                                           // Force timeout of any error (This won't clear errors if still detected)
          return screen_main;                                                                         // Go to main screen
        }
        widgetEnable(Widget_lang);                                                                    // In setup mode, enable widgets
        widgetEnable(Widget_profile);
        widgetEnable(Widget_ok);
        scr->refresh = screen_Erase;                                                                  // Force screen wipe to clear the boot logo
        boot_step++;                                                                                  // Increase boot step
      }
      else{
        return -1;                                                                                    // Boot timeout not expired, do nothing
      }

    default:
       break;
  }

  return (default_screenProcessInput(scr, input, state));
}


void boot_screen_init(screen_t * scr){
  default_init(scr);
  profile=systemSettings.settings.currentProfile;
  if( (systemSettings.settings.state!=initialized) || (profile>profile_C210) ){
    profile=profile_T12;
    setSafeMode(enable);
    systemSettings.setupMode=enable;
  }
  u8g2_SetDrawColor(&u8g2,WHITE);
  u8g2_DrawXBMP(&u8g2, 0, 0, splashXBM[0], splashXBM[1], &splashXBM[2]);
  scr->refresh = screen_Erased;
  setContrast(0);
  wakeOledDim();
}


void boot_screen_create(screen_t *scr){
  widget_t *w;
  displayOnly_widget_t *dis;
  editable_widget_t *edit;
  lang = systemSettings.settings.language;
  if(lang>=LANGUAGE_COUNT){
    lang=lang_english;
  }
  current_lang = lang;

  //  [ Profile Select Widget ]
  //
  newWidget(&w, widget_multi_option, scr);
  Widget_profile = w;
  dis=extractDisplayPartFromWidget(w);
  edit=extractEditablePartFromWidget(w);
  dis->font = u8g2_font_menu;
  dis->reservedChars=4;
  dis->getData = &getProfile;
  edit->big_step = 1;
  edit->step = 1;
  edit->selectable.tab = 0;
  edit->setData = (void (*)(void *))&setProfile;
  edit->options = profileStr;
  edit->numberOfOptions = ProfileSize;
  w->posX = 74;
  w->posY = 16;
  w->width = 44;
  w->enabled=0;

  //  [ Language Select Widget ]
  //
  newWidget(&w, widget_multi_option, scr);
  Widget_lang = w;
  dis=extractDisplayPartFromWidget(w);
  edit=extractEditablePartFromWidget(w);
  dis->font = u8g2_font_menu;
  dis->reservedChars=2;
  dis->getData = &getLanguage;
  edit->big_step = 1;
  edit->step = 1;
  edit->selectable.tab = 1;
  edit->setData = (void (*)(void *))&setLanguage;
  edit->options = Langs;
  edit->numberOfOptions = LANGUAGE_COUNT;
  w->posX = 74;
  w->posY = 32;
  w->width = 44;
  w->enabled=0;

  //  [ OK button Widget ]
  //
  newWidget(&w, widget_button, scr);
  Widget_ok = w;
  button_widget_t* button=Widget_ok->content;
  button->displayString = strings[lang]._SAVE;
  button->font = u8g2_font_menu;
  button->selectable.tab = 2;
  button->action = &SaveSetup;
  w->posY = 48;
  w->width = 60;
  w->posX = (OledWidth-1) - w->width;
  w->enabled=0;
}


void boot_screen_setup(screen_t *scr) {
  scr->draw = &boot_screen_draw;
  scr->processInput = &boot_screen_processInput;
  scr->init = &boot_screen_init;
  scr->create = &boot_screen_create;
}
