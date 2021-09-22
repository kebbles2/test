#include "desktop_i.h"
#include "applications/dolphin/dolphin.h"

static void lock_icon_callback(Canvas* canvas, void* context) {
    furi_assert(context);
    Desktop* desktop = (Desktop*)context;
    canvas_draw_icon_animation(canvas, 0, 0, desktop->lock_icon);
}

bool desktop_custom_event_callback(void* context, uint32_t event) {
    furi_assert(context);
    Desktop* desktop = (Desktop*)context;
    return scene_manager_handle_custom_event(desktop->scene_manager, event);
}

bool desktop_back_event_callback(void* context) {
    furi_assert(context);
    Desktop* desktop = (Desktop*)context;
    return scene_manager_handle_back_event(desktop->scene_manager);
}

Desktop* desktop_alloc() {
    Desktop* desktop = furi_alloc(sizeof(Desktop));

    desktop->menu_vm = furi_record_open("menu");
    desktop->gui = furi_record_open("gui");
    desktop->scene_thread = furi_thread_alloc();
    desktop->view_dispatcher = view_dispatcher_alloc();
    desktop->scene_manager = scene_manager_alloc(&desktop_scene_handlers, desktop);

    view_dispatcher_enable_queue(desktop->view_dispatcher);
    view_dispatcher_attach_to_gui(
        desktop->view_dispatcher, desktop->gui, ViewDispatcherTypeWindow);

    view_dispatcher_set_event_callback_context(desktop->view_dispatcher, desktop);
    view_dispatcher_set_custom_event_callback(
        desktop->view_dispatcher, desktop_custom_event_callback);
    view_dispatcher_set_navigation_event_callback(
        desktop->view_dispatcher, desktop_back_event_callback);

    desktop->main_view = desktop_main_alloc();
    desktop->lock_menu = desktop_lock_menu_alloc();
    desktop->locked_view = desktop_locked_alloc();
    desktop->debug_view = desktop_debug_alloc();
    desktop->first_start_view = desktop_first_start_alloc();
    desktop->hw_mismatch_view = desktop_hw_mismatch_alloc();

    view_dispatcher_add_view(
        desktop->view_dispatcher, DesktopViewMain, desktop_main_get_view(desktop->main_view));
    view_dispatcher_add_view(
        desktop->view_dispatcher,
        DesktopViewLockMenu,
        desktop_lock_menu_get_view(desktop->lock_menu));
    view_dispatcher_add_view(
        desktop->view_dispatcher, DesktopViewDebug, desktop_debug_get_view(desktop->debug_view));
    view_dispatcher_add_view(
        desktop->view_dispatcher,
        DesktopViewLocked,
        desktop_locked_get_view(desktop->locked_view));
    view_dispatcher_add_view(
        desktop->view_dispatcher,
        DesktopViewFirstStart,
        desktop_first_start_get_view(desktop->first_start_view));
    view_dispatcher_add_view(
        desktop->view_dispatcher,
        DesktopViewHwMismatch,
        desktop_hw_mismatch_get_view(desktop->hw_mismatch_view));

    // Lock icon
    desktop->lock_icon = icon_animation_alloc(&I_Lock_8x8);
    desktop->lock_viewport = view_port_alloc();
    view_port_set_width(desktop->lock_viewport, icon_animation_get_width(desktop->lock_icon));
    view_port_draw_callback_set(desktop->lock_viewport, lock_icon_callback, desktop);
    view_port_enabled_set(desktop->lock_viewport, false);
    gui_add_view_port(desktop->gui, desktop->lock_viewport, GuiLayerStatusBarLeft);

    return desktop;
}

void desktop_free(Desktop* desktop) {
    furi_assert(desktop);

    view_dispatcher_remove_view(desktop->view_dispatcher, DesktopViewMain);
    view_dispatcher_remove_view(desktop->view_dispatcher, DesktopViewLockMenu);
    view_dispatcher_remove_view(desktop->view_dispatcher, DesktopViewLocked);
    view_dispatcher_remove_view(desktop->view_dispatcher, DesktopViewDebug);
    view_dispatcher_remove_view(desktop->view_dispatcher, DesktopViewFirstStart);
    view_dispatcher_remove_view(desktop->view_dispatcher, DesktopViewHwMismatch);

    view_dispatcher_free(desktop->view_dispatcher);
    scene_manager_free(desktop->scene_manager);

    desktop_main_free(desktop->main_view);
    desktop_lock_menu_free(desktop->lock_menu);
    desktop_locked_free(desktop->locked_view);
    desktop_debug_free(desktop->debug_view);
    desktop_first_start_free(desktop->first_start_view);
    desktop_hw_mismatch_free(desktop->hw_mismatch_view);

    furi_record_close("gui");
    desktop->gui = NULL;

    furi_thread_free(desktop->scene_thread);

    furi_record_close("menu");
    desktop->menu_vm = NULL;

    free(desktop);
}

int32_t desktop_app(void* p) {
    Desktop* desktop = desktop_alloc();
    Dolphin* dolphin = furi_record_open("dolphin");

    desktop_settings_load(&desktop->settings);

    if(dolphin_load(dolphin)) {
        scene_manager_next_scene(desktop->scene_manager, DesktopSceneMain);
    } else {
        scene_manager_next_scene(desktop->scene_manager, DesktopSceneFirstStart);
    }
    furi_record_close("dolphin");

    if(!furi_hal_version_do_i_belong_here()) {
        scene_manager_next_scene(desktop->scene_manager, DesktopSceneHwMismatch);
    }

    view_dispatcher_run(desktop->view_dispatcher);
    desktop_free(desktop);

    return 0;
}
