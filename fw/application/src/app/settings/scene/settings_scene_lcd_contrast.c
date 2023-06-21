#include "app_settings.h"
#include "mini_app_launcher.h"
#include "nrf_log.h"
#include "nrf_pwr_mgmt.h"
#include "settings.h"
#include "settings_scene.h"
#include "utils.h"
#include "version2.h"

#include "mui_u8g2.h"

static void settings_scene_lcd_contrast_event_cb(mui_progress_bar_event_t event, mui_progress_bar_t *p_progress_bar) {
    app_settings_t *app = p_progress_bar->user_data;
    settings_data_t *p_settings = settings_get_data();
    mui_t *p_mui = mui();

    if (event == MUI_PROGRESS_BAR_EVENT_DECREMENT || event == MUI_PROGRESS_BAR_EVENT_INCREMENT) {
        uint8_t value = mui_progress_bar_get_current_value(p_progress_bar);
        u8g2_SetContrast(&p_mui->u8g2, value);
        //mui_u8g2_set_backlight_level(value);
    } else {
        uint8_t value = mui_progress_bar_get_current_value(p_progress_bar);
        //mui_u8g2_set_backlight_level(value);
        p_settings->lcd_contrast = value;
        mui_scene_dispatcher_previous_scene(app->p_scene_dispatcher);
    }
}

void settings_scene_lcd_contrast_on_enter(void *user_data) {
    app_settings_t *app = user_data;
    settings_data_t *p_settings = settings_get_data();
    mui_progress_bar_set_header(app->p_progress_bar, "对比度");
    mui_progress_bar_set_min_value(app->p_progress_bar, 30);
    mui_progress_bar_set_max_value(app->p_progress_bar, 255);
    mui_progress_bar_set_current_value(app->p_progress_bar, p_settings->lcd_contrast);
    mui_progress_bar_set_event_cb(app->p_progress_bar, settings_scene_lcd_contrast_event_cb);
    mui_view_dispatcher_switch_to_view(app->p_view_dispatcher, SETTINGS_VIEW_ID_PROGRESS_BAR);
}

void settings_scene_lcd_contrast_on_exit(void *user_data) {
    app_settings_t *app = user_data;
    mui_progress_bar_reset(app->p_progress_bar);
}