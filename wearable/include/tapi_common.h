/*
 * libslp-tapi
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Ja-young Gu <jygu@samsung.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _TAPI_COMMON_H_
#define _TAPI_COMMON_H_

/**
*  @addtogroup TAPI_COMMON
*  @{
*
*  @file tapi_common.h
*  @brief TAPI Common Interface
*/

#include <stdio.h>
#include <glib.h>

#include <tapi_type.h>
#include <tapi_event.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief Fetches the list of available CPs
 *
 *  @par Sync (or) Async:
 *  Synchronous API
 *
 *  @param[out] None.
 *
 *  @return #List of available CPs on SUCCESS and NULL on FAILURE.
 */
char** tel_get_cp_name_list(void);

/**
 *  @brief Acquires a TAPI Handle for specified CP name
 *
 *  @par Sync (or) Async:
 *  Synchronous API
 *
 *  @param[in] cp_name CP Name against which TAPI handle is required \n
 *  NULL CP Name will return TapiHandle bound to the first CP in the list of available CPs
 *
 *  @return #TapiHandle on SUCCESS and NULL on FAILURE.
 */
TapiHandle* tel_init(const char *cp_name);

/**
 *  @brief De-initializes the TAPI Handle
 *
 *  @par Sync (or) Async:
 *  Synchronous API
 *
 *  @param[in] handle #TapiHandle obtained from tel_init()
 *
 *  @return #TapiResult_t
 */
int tel_deinit(TapiHandle *handle);

/**
 *  @brief Registers Notification CallBack for events on DBus interface
 *
 *  @par Sync (or) Async:
 *  Synchronous API
 *
 *  @param[in] handle #TapiHandle obtained from tel_init()
 *
 *  @param[in] noti_id Notification Id for which callback has to be registered
 *
 *  @param[in] callback #tapi_notification_cb Notification callback which will be invoked on event
 *
 * @param user_data User Data
 *
 *  @return #TapiResult_t
 */
int tel_register_noti_event(TapiHandle *handle, const char *noti_id,
			tapi_notification_cb callback, void *user_data);

/**
 *  @brief De-Registers Notification CallBack for events on DBus interface
 *
 *  @par Sync (or) Async:
 *  Synchronous API
 *
 *  @param[in] handle #TapiHandle obtained from tel_init()
 *
 *  @param[in] noti_id Notification Id for which callback has to be de-registered
 *
 *  @return #TapiResult_t
 */
 int tel_deregister_noti_event(TapiHandle *handle, const char *noti_id);

/**
 *  @brief Gets  the property value in integer format for given property
 *
 *  @par Sync (or) Async:
 *  Synchronous API
 *
 *  @param[in] handle #TapiHandle obtained from tel_init()
 *
 *  @param[in] property Property which is to be retrieved from Dbus
 *
 *  @param[out] result Property value in integer format
 *
 *  @return #TapiResult_t
 */
int tel_get_property_int(TapiHandle *handle, const char *property, int *result);

/**
 *  @brief Gets  the property value in string format for given property
 *
 *  @par Sync (or) Async:
 *  Synchronous API
 *
 *  @param[in] handle #TapiHandle obtained from tel_init()
 *
 *  @param[in] property Property which is to be retrieved from Dbus
 *
 *  @param[out] result Property value in string format
 *
 *  @return #TapiResult_t
 */
int tel_get_property_string(TapiHandle *handle, const char *property, char **result);

#ifdef __cplusplus
}
#endif

/** @}*/

#endif /* _TAPI_COMMON_H_ */

