#include <furi.h>
#include "../dolphin_i.h"
#include "dolphin_lock_menu_view.h"

void dolphin_lock_menu_set_callback(
    DolphinLockMenuView* lock_menu,
    DolphinLockMenuViewCallback callback,
    void* context) {
    furi_assert(lock_menu);
    furi_assert(callback);
    lock_menu->callback = callback;
    lock_menu->context = context;
}

void dolphin_lock_menu_reset_idx(DolphinLockMenuView* lock_menu) {
    with_view_model(
        lock_menu->view, (DolphinLockMenuViewModel * model) {
            model->idx = 0;
            return true;
        });
}

static void lock_menu_callback(void* context, uint8_t index) {
    furi_assert(context);
    DolphinLockMenuView* lock_menu = context;
    switch(index) {
    case 0: // lock
        lock_menu->callback(DolphinLockMenuEventLock, lock_menu->context);
    default: // wip message
        with_view_model(
            lock_menu->view, (DolphinLockMenuViewModel * model) {
                model->hint_timeout = HINT_TIMEOUT_L;
                return true;
            });
        break;
    }
}

void dolphin_lock_menu_render(Canvas* canvas, void* model) {
    const char* Lockmenu_Items[3] = {"Lock", "Set PIN", "DUMB mode"};

    DolphinLockMenuViewModel* m = model;
    canvas_clear(canvas);
    canvas_set_color(canvas, ColorBlack);
    canvas_draw_icon(canvas, -57, 0, &I_DoorLeft_70x55);
    canvas_draw_icon(canvas, 115, 0, &I_DoorRight_70x55);
    canvas_set_font(canvas, FontSecondary);

    for(uint8_t i = 0; i < 3; ++i) {
        canvas_draw_str_aligned(
            canvas,
            64,
            13 + (i * 17),
            AlignCenter,
            AlignCenter,
            (m->hint_timeout && m->idx == i && m->idx) ? "Not implemented" : Lockmenu_Items[i]);
        if(m->idx == i) elements_frame(canvas, 15, 5 + (i * 17), 98, 15);
    }
}

View* dolphin_lock_menu_get_view(DolphinLockMenuView* lock_menu) {
    furi_assert(lock_menu);
    return lock_menu->view;
}

bool dolphin_lock_menu_input(InputEvent* event, void* context) {
    furi_assert(event);
    furi_assert(context);

    DolphinLockMenuView* lock_menu = context;
    uint8_t idx;

    if(event->type != InputTypeShort) return false;
    with_view_model(
        lock_menu->view, (DolphinLockMenuViewModel * model) {
            model->hint_timeout = 0; // clear hint timeout
            if(event->key == InputKeyUp) {
                model->idx = CLAMP(model->idx - 1, 2, 0);
            } else if(event->key == InputKeyDown) {
                model->idx = CLAMP(model->idx + 1, 2, 0);
            }
            idx = model->idx;
            return true;
        });

    if(event->key == InputKeyBack) {
        lock_menu->callback(DolphinLockMenuEventExit, lock_menu->context);
    } else if(event->key == InputKeyOk) {
        lock_menu_callback(lock_menu, idx);
    }

    return true;
}

DolphinLockMenuView* dolphin_lock_menu_alloc() {
    DolphinLockMenuView* lock_menu = furi_alloc(sizeof(DolphinLockMenuView));
    lock_menu->view = view_alloc();
    view_allocate_model(lock_menu->view, ViewModelTypeLocking, sizeof(DolphinLockMenuViewModel));
    view_set_context(lock_menu->view, lock_menu);
    view_set_draw_callback(lock_menu->view, (ViewDrawCallback)dolphin_lock_menu_render);
    view_set_input_callback(lock_menu->view, dolphin_lock_menu_input);

    return lock_menu;
}

void dolphin_lock_menu_free(DolphinLockMenuView* lock_menu_view) {
    furi_assert(lock_menu_view);

    view_free(lock_menu_view->view);
    free(lock_menu_view);
}
