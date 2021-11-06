#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    iButtonKeyDS1990,
    iButtonKeyCyfral,
    iButtonKeyMetakom,
} iButtonKeyType;

typedef struct iButtonKey iButtonKey;

/**
 * Allocate key
 * @return iButtonKey* 
 */
iButtonKey* ibutton_key_alloc();

/**
 * Free key
 * @param key 
 */
void ibutton_key_free(iButtonKey* key);

/**
 * Set key data
 * @param key 
 * @param data 
 * @param data_count 
 */
void ibutton_key_set_data(iButtonKey* key, uint8_t* data, uint8_t data_count);

/**
 * Clear key data
 * @param key 
 */
void ibutton_key_clear_data(iButtonKey* key);

/**
 * Get pointer to key data
 * @param key 
 * @return const uint8_t* 
 */
const uint8_t* ibutton_key_get_data_p(iButtonKey* key);

/**
 * Get key data size
 * @param key 
 * @return uint8_t 
 */
uint8_t ibutton_key_get_data_size(iButtonKey* key);

/**
 * Set key name
 * @param key 
 * @param name 
 */
void ibutton_key_set_name(iButtonKey* key, const char* name);

/**
 * Get pointer to key name
 * @param key 
 * @return const char* 
 */
const char* ibutton_key_get_name_p(iButtonKey* key);

/**
 * Set key type
 * @param key 
 * @param key_type 
 */
void ibutton_key_set_type(iButtonKey* key, iButtonKeyType key_type);

/**
 * Get key type
 * @param key 
 * @return iButtonKeyType 
 */
iButtonKeyType ibutton_key_get_type(iButtonKey* key);

/**
 * Get type string from key type
 * @param key_type 
 * @return const char* 
 */
const char* ibutton_key_get_string_by_type(iButtonKeyType key_type);

/**
 * Get key type from string
 * @param type_string 
 * @param key_type 
 * @return bool 
 */
bool ibutton_key_get_type_by_string(const char* type_string, iButtonKeyType* key_type);

/**
 * Get key data size from type
 * @param key_type 
 * @return uint8_t 
 */
uint8_t ibutton_key_get_size_by_type(iButtonKeyType key_type);

/**
 * Get max key size
 * @return uint8_t 
 */
uint8_t ibutton_key_get_max_size();

#ifdef __cplusplus
}
#endif