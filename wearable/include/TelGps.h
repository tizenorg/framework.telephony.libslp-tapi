/*
 * libslp-tapi
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd. All rights reserved.
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

/**
* @open
* @ingroup	TelephonyAPI
* @addtogroup	GPS_TAPI	GPS
* @{
*
* @file TelNetwork.h

     @brief This file serves as a "C" header file and defines structures for Tapi Network Services\n
      It contains a sample set of constants, enums, structs that would be required by applications.
 */

#ifndef _TEL_GPS_H_
#define _TEL_GPS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define TAPI_SMART_ASSISTANT_AREA_LIST_MAX	10		/**< Maximum smart assistant area list */

/**
 * @enum TelSmartAssistantMode_t
 *  This enumeration defines the smart assistant mode state.
 */
typedef enum {
	TAPI_SMART_ASSISTANT_SYNC = 1,
	TAPI_SMART_ASSISTANT_DELETE = 2,
	TAPI_SMART_ASSISTANT_ADD = 1,
	TAPI_SMART_ASSISTANT_MODIFY = 2
} TelSmartAssistantOperationType_t;

/**
 * @enum TelSmartAssistantMode_t
 *  This enumeration defines the smart assistant mode state.
 */
typedef enum {
	TAPI_SMART_ASSISTANT_MODE_STATE_START = 1,
	TAPI_SMART_ASSISTANT_MODE_STATE_STOP
} TelSmartAssistantModeState_t;

/**
 *
 * This structure defines the smart assistant area.
 */
typedef struct {
	unsigned int index; /**< Smart Assistant area ID */
	TelSmartAssistantModeState_t mode_state; /**< Smart Assistant mode state */
} TelSmartAssistantArea_t;

/**
 *
 * This structure defines the smart assistant area list.
 */
typedef struct {
	unsigned int count; /**< Smart Assistant area count  */
	TelSmartAssistantArea_t area[TAPI_SMART_ASSISTANT_AREA_LIST_MAX];
} TelSmartAssistantAreaList_t;


/**
 * @enum TelSmartAssistantLppState_t
 *  This enumeration defines the smart assistant mode state.
 */
typedef enum {
	TAPI_SMART_ASSISTANT_LPP_STATE_START = 1,
	TAPI_SMART_ASSISTANT_LPP_STATE_STOP
} TelSmartAssistantLppState_t;

/**
 *
 * This structure defines the smart assistant info.
 * AP(Application processor) let the CP(Modem) know the lpp state of Smart Assistant
 */
typedef struct {
	unsigned int index; /**< Smart Assistant area ID */
	TelSmartAssistantLppState_t lpp_state; /**< Smart Assistant lpp state */
} TelSmartAssistantInfo_t;


/**
 * @enum TelSmartAssistantInitStatus_t
 *  This enumeration defines the smart assistant init status.
 */
typedef enum {
	TAPI_SMART_ASSISTANT_INIT_SUCCESS = 1,
	TAPI_SMART_ASSISTANT_INIT_FAIL
} TelSmartAssistantInitStatus_t;

/**
 * @enum TelSmartAssistantAreaStatus_t
 *  This enumeration defines the smart assistant area status.
 */
typedef enum {
	TAPI_SMART_ASSISTANT_AREA_STATUS_IN = 1,
	TAPI_SMART_ASSISTANT_AREA_STATUS_OUT
} TelSmartAssistantAreaStatus_t;


struct tel_noti_smart_assistant_area_status {
	TelSmartAssistantAreaStatus_t area_status;
	unsigned int index; /**< Smart Assistant area ID */
};

struct tel_noti_smart_assistant_sync_status {
	TelSmartAssistantInitStatus_t init_status;
	int init_fail_cause;
};


#ifdef __cplusplus
}
#endif

#endif // _TEL_GPS_H_

/**
* @}
*/
