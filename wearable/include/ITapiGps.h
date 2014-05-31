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
 * @ingroup		TelephonyAPI
 * @addtogroup	GPS_TAPI		GPS
 * @{
 *
 * @file ITapiGps.h

 @brief This file serves as a "C" header file defines functions for Tapi GPS\n
 It contains a sample set of function prototypes that would be required by applications.
 * GPS APIs allow an application to accomplish the following services: @n
 * - Confirm gps measure position information. @n
 */


#ifndef _ITAPI_GPS_H_
#define _ITAPI_GPS_H_

#include <tapi_common.h>
#include <TelErr.h>
#include <TelDefines.h>
#include <TelGps.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief  This function sends the confirmation data for measure position message.
 *
 * @par Sync (or) Async:
 * This is an Synchronous API.
 *
 * @par Important Notes:
 * - None.
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param [in] data
 * -#user confirmation data for each vender.
 *
 * @param [in] data_len
 * - data length
 *
 * @pre
 * - TAPI_EVENT_GPS_MEASURE_POSITION_IND should be sent to application by Telephony Server.
 *
 * @post
 * - none
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 *
 * @par Prospective Clients:
 * GPS Deamon
 *
 *
 * @code
 *
 *	int result;
 *	gps_measure_position_confirm_t data;
 *	result = tel_confirm_gps_measure_pos(handle, (unsigned char *)&data, sizeof(gps_measure_position_confirm_t));
 *
 *
 */
/*================================================================================================*/
int tel_confirm_gps_measure_pos(TapiHandle *handle, unsigned char *data, unsigned int data_len);

/**
 * @brief  This function is invoked to set the gps frequency aiding.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None.
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param [in] state
 * - enable / disable state.
 *
 * @param [in] data_len
 * - data length

 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * - None
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 *
 * @par Prospective Clients:
 * GPS daemon.
 *
 * @code
 *
 *	unsigned char state = true;
 *
 *	result = tel_set_gps_frequency_aiding(handle, state, on_gps_set_frequency_aiding, NULL);
 *
 * @endcode
 *
 * @see
 *  - None.
 *
 * @remarks
 *  - None.
 *
 *
 *
 */
/*================================================================================================*/

int tel_set_gps_frequency_aiding(TapiHandle *handle, unsigned char state, tapi_response_cb callback, void *user_data);

/**
 * @brief  This function is invoked to enable smart assistant.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None.
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * - None
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 *
 * @par Prospective Clients:
 * Location Manager.
 *
 * @code
 * #include <ITapiGps.h>
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * result = tel_enable_smart_assistant(handle, callback, user_data);
 *
 * @endcode
 *
 * @see
 *  - None.
 *
 * @remarks
 *  - None.
 *
 *
 *
 */
/*================================================================================================*/
int tel_enable_smart_assistant(TapiHandle *handle, tapi_response_cb callback, void* user_data);

/**
 * @brief  This function is invoked to disable smart assistant.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None.
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * - None
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 *
 * @par Prospective Clients:
 * Location Manager.
 *
 * @code
 * #include <ITapiGps.h>
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * result = tel_disable_smart_assistant(handle, callback, user_data);
 *
 * @endcode
 *
 * @see
 *  - None.
 *
 * @remarks
 *  - None.
 *
 *
 *
 */
/*================================================================================================*/

int tel_disable_smart_assistant(TapiHandle *handle, tapi_response_cb callback, void* user_data);

/**
 * @brief  This function is invoked to sync smart assistant area list.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None.
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * - None
 *
 * @pre
 * - Smart Assistant should be enabled.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 *
 * @par Prospective Clients:
 * Location Manager.
 *
 * @code
 * #include <ITapiGps.h>
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 * TelSmartAssistantAreaList_t area_list;
 *
 * area_list.count = 2;
 * area_list.area[0].index = 1;
 * area_list.area[0].mode_state = TAPI_SMART_ASSISTANT_MODE_STATE_START;
 * area_list.area[1].index = 2;
 * area_list.area[1].mode_state = TAPI_SMART_ASSISTANT_MODE_STATE_STOP;
 *
 * result = tel_sync_smart_assistant_area_list(handle, &area_list, callback, user_data);
 *
 * @endcode
 *
 * @see
 *  - None.
 *
 * @remarks
 *  - None.
 *
 *
 *
 */
/*================================================================================================*/
int tel_sync_smart_assistant_area_list(TapiHandle *handle, TelSmartAssistantAreaList_t *area_list, tapi_response_cb callback, void* user_data);

/**
 * @brief  This function is invoked to delete smart assistant area list.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None.
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * - None
 *
 * @pre
 * - Smart Assistant should be enabled.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 *
 * @par Prospective Clients:
 * Location Manager.
 *
 * @code
 * #include <ITapiGps.h>
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 * TelSmartAssistantAreaList_t area_list;
 *
 * area_list.count = 2;
 * area_list.area[0].index = 1;
 * area_list.area[1].index = 2;
 *
 * result = tel_del_smart_assistant_area_list(handle, &area_list, callback, user_data);
 *
 * @endcode
 *
 * @see
 *  - None.
 *
 * @remarks
 *  - None.
 *
 *
 *
 */
/*================================================================================================*/
int tel_del_smart_assistant_area_list(TapiHandle *handle, TelSmartAssistantAreaList_t *area_list, tapi_response_cb callback, void* user_data);

/**
 * @brief  This function is invoked to add smart assistant area.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None.
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * - None
 *
 * @pre
 *  - Smart Assistant should be enabled.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 *
 * @par Prospective Clients:
 * Location Manager.
 *
 * @code
 * #include <ITapiGps.h>
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 * TelSmartAssistantArea_t area;
 *
 * area.index = 1;
 * area.mode_state = TAPI_SMART_ASSISTANT_MODE_STATE_START;
 *
 * result = tel_add_smart_assistant_area(handle, &area, callback, user_data);
 *
 * @endcode
 *
 * @see
 *  - None.
 *
 * @remarks
 *  - None.
 *
 *
 *
 */
/*================================================================================================*/
int tel_add_smart_assistant_area(TapiHandle *handle, TelSmartAssistantArea_t *area, tapi_response_cb callback, void* user_data);

/**
 * @brief  This function is invoked to modify smart assistant area.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None.
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * - None
 *
 * @pre
 *  - Smart Assistant should be enabled.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 *
 * @par Prospective Clients:
 * Location Manager.
 *
 * @code
 * #include <ITapiGps.h>
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 * TelSmartAssistantArea_t area;
 *
 * area.index = 1;
 * area.mode_state = TAPI_SMART_ASSISTANT_MODE_STATE_START;
 *
 * result = tel_modify_smart_assistant_area(handle, &area, callback, user_data);
 *
 * @endcode
 *
 * @see
 *  - None.
 *
 * @remarks
 *  - None.
 *
 *
 *
 */
/*================================================================================================*/
int tel_modify_smart_assistant_area(TapiHandle *handle, TelSmartAssistantArea_t *area, tapi_response_cb callback, void* user_data);

/**
 * @brief  This function is invoked to send smart assistant aiding information to CP.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None.
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * - None
 *
 * @pre
 *  - Smart Assistant should be enabled.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 *
 * @par Prospective Clients:
 * Location Manager.
 *
 * @code
 * #include <ITapiGps.h>
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 * TelSmartAssistantInfo_t info;
 *
 * info.index = 1;
 * info.lpp_state = TAPI_SMART_ASSISTANT_LPP_STATE_START;
 *
 * result = tel_set_smart_assistant_info(handle, &info, callback, user_data);
 *
 * @endcode
 *
 * @see
 *  - None.
 *
 * @remarks
 *  - None.
 *
 *
 *
 */
/*================================================================================================*/
int tel_set_smart_assistant_info(TapiHandle *handle, TelSmartAssistantInfo_t *info, tapi_response_cb callback, void* user_data);

#ifdef __cplusplus
}
#endif

#endif	/* _ITAPI_GPS_H_ */

/**
 * @}
 */
