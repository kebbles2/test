#pragma once

#include "types.h"
#include "environment.h"
#include "protocols/base.h"

typedef struct SubGhzTransmitter SubGhzTransmitter;

struct SubGhzTransmitter {
    const SubGhzProtocol* protocol;
    SubGhzProtocolEncoderBase* protocol_instance;
};

/**
 * Allocate and init SubGhzTransmitter.
 * @param environment Pointer to a SubGhzEnvironment instance
 * @return SubGhzTransmitter* pointer to a SubGhzTransmitter instance
 */
SubGhzTransmitter*
    subghz_transmitter_alloc_init(SubGhzEnvironment* environment, const char* protocol_name);

/**
 * Free SubGhzTransmitter.
 * @param instance Pointer to a SubGhzTransmitter instance
 */
void subghz_transmitter_free(SubGhzTransmitter* instance);

/**
 * Forced transmission stop.
 * @param instance Pointer to a SubGhzTransmitter instance
 */
bool subghz_transmitter_stop(SubGhzTransmitter* instance);

/**
 * Deserialize and generating an upload to send.
 * @param instance Pointer to a SubGhzTransmitter instance
 * @param flipper_format Pointer to a FlipperFormat instance
 * @return true On success
 */
bool subghz_transmitter_deserialize(SubGhzTransmitter* instance, FlipperFormat* flipper_format);

/**
 * Getting the level and duration of the upload to be loaded into DMA.
 * @param context Pointer to a SubGhzTransmitter instance
 * @return LevelDuration 
 */
LevelDuration subghz_transmitter_yield(void* context);
