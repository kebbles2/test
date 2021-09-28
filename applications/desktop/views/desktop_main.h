#pragma once

#include <gui/gui_i.h>
#include <gui/view.h>
#include <gui/canvas.h>
#include <gui/elements.h>
#include <furi.h>

typedef enum {
    DesktopMainEventOpenMenu,
    DesktopMainEventOpenLockMenu,
    DesktopMainEventOpenDebug,
    DesktopMainEventUnlocked,
    DesktopMainEventOpenArchive,
    DesktopMainEventOpenFavorite,
<<<<<<< HEAD
    DesktopMainEventOpenFlipperScenes,
=======
>>>>>>> 0126b3aba474b84fc5dfe57bcd42c5b9fc05e634
} DesktopMainEvent;

typedef struct DesktopMainView DesktopMainView;

typedef void (*DesktopMainViewCallback)(DesktopMainEvent event, void* context);

struct DesktopMainView {
    View* view;
    DesktopMainViewCallback callback;
    void* context;
};

typedef struct {
    IconAnimation* animation;
    uint8_t scene_num;
    uint8_t hint_timeout;
    bool unlocked;
} DesktopMainViewModel;

void desktop_main_set_callback(
    DesktopMainView* main_view,
    DesktopMainViewCallback callback,
    void* context);

View* desktop_main_get_view(DesktopMainView* main_view);

DesktopMainView* desktop_main_alloc();
void desktop_main_free(DesktopMainView* main_view);
