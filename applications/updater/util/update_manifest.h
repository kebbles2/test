#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <m-string.h>

typedef struct {
    uint32_t target;
    string_t staged_loader_file;
    string_t firmware_dfu_image;
    string_t radio_image;
    bool valid;
} UpdateManifest;

UpdateManifest* update_manifest_alloc();

void update_manifest_free(UpdateManifest* update_manifest);

bool update_manifest_init(UpdateManifest* update_manifest, const char* manifest_filename);

#ifdef __cplusplus
}
#endif