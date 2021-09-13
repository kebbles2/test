#pragma once

#include <furi.h>
#include <furi-hal.h>
#include <menu/menu.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <assets_icons.h>

#include "dolphin.h"
#include "helpers/dolphin_state.h"

#include "views/dolphin_main_view.h"
#include "views/dolphin_first_start_view.h"
#include "views/dolphin_hw_mismatch_view.h"
#include "views/dolphin_lock_menu_view.h"
#include "views/dolphin_locked_view.h"
#include "views/dolphin_debug_view.h"
#include "scenes/dolphin_scene.h"

#define UNLOCK_RST_TIMEOUT 200
#define HINT_TIMEOUT 2

typedef enum {
    DolphinViewMain,
    DolphinViewLockMenu,
    DolphinViewLocked,
    DolphinViewDebug,
    DolphinViewFirstStart,
    DolphinViewHwMismatch,
    DolphinViewTotal,
} DolphinViewEnum;

typedef enum {
    DolphinEventTypeDeed,
    DolphinEventTypeSave,
    DolphinEventTypeTick,
} DolphinEventType;

typedef struct {
    DolphinEventType type;
    union {
        DolphinDeed deed;
    };
} DolphinEvent;

struct Dolphin {
    // Internal message queue
    osMessageQueueId_t event_queue;
    // State
    DolphinState* state;
    // Menu
    ValueMutex* menu_vm;
    // Scene
    FuriThread* scene_thread;
    // GUI
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    SceneManager* scene_manager;

    DolphinFirstStartView* first_start_view;
    DolphinHwMismatchView* hw_mismatch_view;
    DolphinMainView* main_view;
    DolphinLockMenuView* lock_menu;
    DolphinLockedView* locked_view;
    DolphinDebugView* debug_view;

    ViewPort* lock_viewport;
    IconAnimation* lock_icon;
};

Dolphin* dolphin_alloc();

void dolphin_free(Dolphin* dolphin);

/* Save Dolphin state (write to permanent memory)
 * Thread safe
 */
void dolphin_save(Dolphin* dolphin);
