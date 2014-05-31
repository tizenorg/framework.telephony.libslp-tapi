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

#ifndef __TAPI_TYPE_H__
#define __TAPI_TYPE_H__

/**
*  @addtogroup TAPI_COMMON
*  @{
*
*  @file tapi_type.h
*  @brief TAPI type
*/

#ifdef __cplusplus
extern "C" {
#endif

/** Telephony service name */
#define DBUS_TELEPHONY_SERVICE      "org.tizen.telephony"

/** Telephony object path */
#define DBUS_TELEPHONY_DEFAULT_PATH "/org/tizen/telephony"

/**
 * TAPI Handle
 */
typedef struct tapi_handle TapiHandle;

/**
 * TAPI Notification Callback Type
 * @param handle #TapiHandle obtained from tel_init()
 * @param noti_id Notification ID for which this callback has to be invoked
 * @param data Notification Data
 * @param user_data User Data
 */
typedef void (*tapi_notification_cb)(TapiHandle *handle, const char *noti_id, void *data, void *user_data);

/**
 * TAPI Response Callback Type
 * @param handle #TapiHandle obtained from tel_init()
 * @param result Result of operation
 * @param data Response Data from operation
 * @param user_data User Data
 */
typedef void (*tapi_response_cb)(TapiHandle *handle, int result, void *data, void *user_data);

#ifdef __cplusplus
}
#endif

/** @}*/

#endif /* __TAPI_TYPE_H__ */
