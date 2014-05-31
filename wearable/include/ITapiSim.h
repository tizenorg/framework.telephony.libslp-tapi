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

/*
 * @open
 * @ingroup		TelephonyAPI
 * @addtogroup	SIM_TAPI	SIM
 * @{
 *
 * @file ITapiSim.h
 *
 * @brief This file serves as a "C" header file defines functions for Tapi SIM Services.
 * It contains a sample set of function prototypes that would be required by applications.
 */

#ifndef _ITAPI_SIM_H_
#define _ITAPI_SIM_H_

#include <tapi_common.h>
#include <TelErr.h>
#include <TelSim.h>
#include <TelDefines.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * @brief  This API is used to get SIM Card Initialization status and SIM Card Identification.
 * Most of modules which require SIM data should check SIM status before using it definitely.
 *
 * @par Sync (or) Async:
 * This is a Synchronous API.
 *
 * @par Important Notes:
 * - Card Identification value is available in TAPI_SIM_STATUS_SIM_INIT_COMPLETED case only.
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param [out] sim_status
 * - This parameter returns SIM initialization status from Telephony server boot up time.
 * First, You can find sim existance if returned value are not in TAPI_SIM_STATUS_CARD_NOT_PRESENT and TAPI_SIM_STATUS_CARD_REMOVED.
 *
 * @param [out] card_changed
 * - This parameter returns sim card identification value when sim_status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED.
 * - card_changed value just present whether current inserted SIM card differs with previous SIM or not.
 *
 * @par Async Response Message:
 * - None
 *
 * @pre
 * - None.
 *
 * @post
 * - None.
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 *
 * int err_code = TAPI_API_SUCCESS;
 * TelSimCardStatus_t status = 0x00;
 * int b_card_changed = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 *
 * // GET SIM INIT INFORMATION
 * err_code = tel_get_sim_init_info(handle, &status, &b_card_changed);
 *
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_init_info(TapiHandle *handle, TelSimCardStatus_t *sim_status, int *card_changed);

/**
 * @brief  This API is used to get the Card Type whether Card is a SIM or a USIM.
 *
 * @par Sync (or) Async:
 * This is a Synchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param [out] card_type
 * This parameter returns the SIM card type information like whether it is GSM SIM card or USIM or it is of unknown type.
 *
 * - TAPI_SIM_CARD_TYPE_UNKNOWN
 * - TAPI_SIM_CARD_TYPE_GSM
 * - TAPI_SIM_CARD_TYPE_USIM
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
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * int err_code = 0;
 * TelSimCardType_t cardInfo; //unkwon, sim(normally gsm), usim(normally umts)
 * TapiHandle *handle;  // Handle given by tel_init()
 *
 * err_code = tel_get_sim_type(handle, &cardInfo);
 *
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_type(TapiHandle *handle, TelSimCardType_t *card_type);

/**
 * @brief  This API is used to get the IMSI information.
 *
 * @par Sync (or) Async:
 * This is a Synchronous API.
 *
 * @par Important Notes:
 * - IMSI value is the value that security needs.
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param [out] imsi
 * This parameter returns the IMSI information. Refer #TelSimImsiInfo_t
 *
 * @par Async Response Message:
 * - None
 *
 * @pre
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * int err_code = 0;
 * TelSimImsiInfo_t sim_imsi_info; // mcc, mnc, msisdn
 * err_code = tel_get_sim_imsi(handle, &sim_imsi_info);
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_imsi(TapiHandle *handle, TelSimImsiInfo_t *imsi);

/**
 * @brief  This API is used to get ECC(SIM) or UECC(USIM) data.
 *
 * @par Sync (or) Async:
 * This is a Synchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param [out] ecc
 * - This parameter returns
 *  *  * the SIM emergency call code information like ecc length, service type etc
 * *  * and number of ECC records.
 *
 * @par Async Response Message:
 * - None
 *
 * @pre
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * int err_code = 0;
 * TelSimEccList_t ecc_info = {0}; // Get ECC list info and ecc_count
 * err_code = tel_get_sim_ecc(handle, &ecc_info);
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_ecc(TapiHandle *handle, TelSimEccList_t *ecc);

/**
 * @brief  This API is used to get Unique identification number of the (U)ICC.
 * ICC means Integrated Circuit Card.
 *
 * @par Sync (or) Async:
 * This is a Asynchronous API.
 *
 * @par Important Notes:
 * - IC Card number value is the value that security needs.
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
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * int err_code = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = tel_get_sim_iccid(handle, callback, user_data);
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_iccid(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to get the language preference(indication) information.
 *
 * @par Sync (or) Async:
 * This is a Asynchronous API.
 *
 * @par Important Notes:
 * - None
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
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * int err_code = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = tel_get_sim_language(handle, callback, user_data);
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_language(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to update the language preference information to SIM card.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
 *
 * @par Sync (or) Async:
 * This is a Asynchronous API.
 *
 * @par Important Notes:
 * - This function update SIM Language information directly and can effect device language setting. Use carefully.
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param [in] language
 * This parameter returns the language preference information.
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * The event associated is TAPI_EVENT_SIM_SET_LANGUAGE_CNF.
 * Asynchronous return status is indicated by #TelSimAccessResult_t.
 *
 * @pre
 *  - A dbus connection is established with #tel_init
 *  - The application name is registered with #tel_register_app_name
 *  - The application is registered events to listen asynchronous response with #tel_register_event
 *  - A event loop is running to listen events
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * int err_code = 0;
 * TelSimLanguagePreferenceCode_t language = 0x00; //init
 * language = TAPI_SIM_LP_ENGLISH; //language value
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = tel_set_sim_language(handle, language, callback, user_data);
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_set_sim_language(TapiHandle *handle, TelSimLanguagePreferenceCode_t language, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to get the SIM Call forwarding indication related data(EF-CFIS and CPHS case).
 * this data is required for Call forwarding related functionality in handset.
 *
 * @par Sync (or) Async:
 * This is a Asynchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None
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
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *  - None
 *
 * @post
 *  - None
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
  * int err_code = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = tel_get_sim_callforwarding_info(handle, callback, user_data);
 * if(err_code == TAPI_API_SUCCESS) {
 *   if(cf_data.b_cphs) { //b_cphs means current SIM is for CPHS or not.
 *     printf("Current SIM is CPHS");
 *   } else {
 *     printf("Current SIM is not CPHS but 3GPP");
 *   }
 * } else {
 *   printf("TAPI API FAIL: Error Code [0x%x]",err_code);
 * }
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_callforwarding_info(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to set the SIM Call forwarding indication related data(EF-CFIS and CPHS case).
 * this data is required for Call forwarding related functionality in handset.
 *
 * @par Sync (or) Async:
 * This is a Asynchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None
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
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *  - None
 *
 * @post
 *  - None
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * int err_code = 0;
 * TelSimCallForwardingReq_t *req_cf;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = tel_set_sim_callforwarding_info(handle, &req_cf, callback, user_data);
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_set_sim_callforwarding_info(TapiHandle *handle, TelSimCallForwardingReq_t *req_cf, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to get the SIM message waiting indication related data(EF-MWIS and CPHS case).
 * this data is required for Message waiting related functionality in handset.
 *
 * @par Sync (or) Async:
 * This is a Asynchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None
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
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *  - None
 *
 * @post
 *  - None
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * TelSimMessageWaiting_s mw_data;
 * int err_code = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = tel_get_sim_messagewaiting_info(handle, callback, user_data);
 * if(err_code == TAPI_API_SUCCESS) {
 *   if(mw_data.b_cphs) { //b_cphs means current SIM is for CPHS or not.
 *     printf("Current SIM is CPHS");
 *   } else {
 *     printf("Current SIM is not CPHS but 3GPP");
 *   }
 * } else {
 *   printf("TAPI API FAIL: Error Code [0x%x]",err_code);
 * }
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_messagewaiting_info(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to set the SIM message waiting indication related data(EF-MWIS and CPHS case).
 * this data is required for Message waiting related functionality in handset.
 *
 * @par Sync (or) Async:
 * This is a Asynchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None
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
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *  - None
 *
 * @post
 *  - None
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * TelSimMessageWaiting_s mw_data;
 * int err_code = 0;
 * TelSimMessageWaitingReq_t *req_mw; // Get message waiting info
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = tel_set_sim_messagewaiting_info(handle, &req_mw, callback, user_data);
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_set_sim_messagewaiting_info(TapiHandle *handle, TelSimMessageWaitingReq_t *req_mw, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to get the SIM mailbox related data(EF-MBDN, MBDI and CPHS case).
 * this data is required for Mailbox related functionality in handset.
 *
 * @par Sync (or) Async:
 * This is a Asynchronous API.
 *
 * @par Important Notes:
 * - None
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
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * int err_code = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = tel_get_sim_mailbox_info(handle, callback, user_data);
 * if(err_code == TAPI_API_SUCCESS) {
 *   if(mbox.b_cphs) { //b_cphs means current SIM is for CPHS or not.
 *     printf("Current SIM is CPHS");
 *   } else {
 *     printf("Current SIM is not CPHS but 3GPP");
 *   }
 * } else {
 *   printf("TAPI API FAIL: Error Code [0x%x]",err_code);
 * }
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_mailbox_info(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to set the SIM mailbox related data(EF-MBDN, MBDI and CPHS case).
 * this data is required for Mailbox related functionality in handset.
 *
 * @par Sync (or) Async:
 * This is a Asynchronous API.
 *
 * @par Important Notes:
 * - None
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
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * int err_code = 0;
 * TelSimMailBoxNumber_t *req_mb; // Get SIM mail box number info
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = tel_set_sim_mailbox_info(handle, &req_mb, callback, user_data);
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_set_sim_mailbox_info(TapiHandle *handle, TelSimMailBoxNumber_t *req_mb, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to get the SIM CPHS specific data.
 * this data is required for CPHS related functionality in handset.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None
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
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *
 * @post
 *  - None
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * int err_code = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = tel_get_sim_cphs_info(handle, callback, user_data);
 * if(err_code == TAPI_API_SUCCESS) {
 *   if(cphs_data.b_used) { //b_used means current SIM is for CPHS or not.
 *     printf("Current SIM is CPHS");
 *   } else {
 *     printf("Current SIM is not CPHS but 3GPP");
 *   }
 * } else {
 *   printf("TAPI API FAIL: Error Code [0x%x]",err_code);
 * }
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_cphs_info(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to get the SIM Service Table.
 * this data is required to know which SIM services are enabled or disabled.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None
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
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *
 * @post
 *  - None
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * int err_code = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = tel_get_sim_service_table(handle, callback, user_data);
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_service_table(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to get the SIM MSISDN data. Regarding 3GPP specification, Current value is optional.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None
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
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *
 * @post
 *  - None
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * int err_code = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * err_code = tel_get_sim_msisdn(handle, callback, user_data);
 * if(err_code == TAPI_API_SUCCESS)
 * {
 * *  printf(" ============================================");
 * *  printf("name[%s]",msisdn.name);
 * *  printf("num[%s]",msisdn.num);
 * *  if(msisdn.name == '\0';) //If current SIM does not have, Null string will be returned.
 * *  *  printf("name is null string");
 *
 * *  if(msisdn.num == '\0';) //If current SIM does not have, Null string will be returned.
 * *  *  printf("number is null string");
 * }
 * else
 * {
 * *  printf("TAPI API FAIL: Error Code [0x%x]",err_code);
 * }
 *
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_msisdn(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to get the SIM OPLMNWACT(Operator controlled PLMN Selector with Access Technology) data. Regarding 3GPP specification, Current value is optional.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None
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
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *
 * @post
 *  - None
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps
 *
 * @see None
 *
 * @code
 * int err_code = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = tel_get_sim_oplmnwact(handle, callback, user_data);
 *
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_oplmnwact(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to get the SIM SPN data. Regarding 3GPP specification, Current value is optional.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None
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
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *
 * @post
 *  - None
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps
 *
 * @see None
 *
 * @code
 * int err_code = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = tel_get_sim_spn(handle, callback, user_data);
 *
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_spn(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to get the SIM CPHS NETNAME data.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None
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
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *
 * @post
 *  - None
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps
 *
 * @see None
 *
 * @code
 * int err_code = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = tel_get_sim_cphs_netname(handle, callback, user_data);
 *
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_cphs_netname(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to execute the authentication procedure by using SIM.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
 * This function supports IMS, 3G and GSM authentication.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * -NONE
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param[in] authentication_data
 * - This input has the authentication code to be validated by ISIM,3G and GSM application in the SIM card. #TelSimAuthenticationData_t
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * -The event associated is TAPI_SIM_EVENT_AUTHENTICATION_CNF  and the event data is #TelSimAuthenticationResponse_t.
 * Asynchronous return status is indicated by #TelSimAccessResult_t.
 *
 * @pre
 *  - A dbus connection is established with #tel_init
 *  - The application name is registered with #tel_register_app_name
 *  - The application is registered events to listen asynchronous response with #tel_register_event
 *  - A event loop is running to listen events
 *
 * @post
 *  - None.
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * int err_code = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * TelSimAuthenticationData_t pAuthenticationData;
 * strcpy((char*)pAuthenticationData.rand_data, "username@operator.com"); //access data
 * pAuthenticationData.rand_length= strlen("username@operator.com");
 * strcpy((char*)pAuthenticationData.autn_data,  "+1-212-555-12345"); // auth data
 * pAuthenticationData.autn_length = strlen("+1-212-555-12345");
 * err_code = tel_req_sim_authentication(handle, &pAuthenticationData, callback, user_data);
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_req_sim_authentication(TapiHandle *handle, TelSimAuthenticationData_t *authentication_data, tapi_response_cb callback, void *user_data);



/**
 * @brief  This API performs PIN1/PIN2/SIM LOCK verification. This function performs PIN verification based on the pin type passed along with pin data.
 * PIN1 code : The SIM card has its own password is to check access permissions
 * SIM Lock code : Between Device and the SIM card using a SIM password is only available on certain handsets to be used to authorize.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - Based on Pin status (PIN/PUK/SIM LOCK) is blocked, an unsolicited event TAPI_EVENT_SIM_STATUS_IND is published to Applications on Device boot time.
 * - if pin status is PUK, you should use #tel_verify_sim_puks instead of this API.
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param[in] pin_data
 * -PIN code, entered by the user. you should make all parameters.
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * The event associated is TAPI_EVENT_SIM_VERIFY_SEC_CNF  and the event data is #TelSimSecResult_t.
 * Asynchronous return status is indicated by #TelSimPinOperationResult_t.
 * If returned status is TAPI_SIM_PIN_OPERATION_SUCCESS, Verification successes.
 * If returned status is TAPI_SIM_PIN_INCORRECT_PASSWORD, Verification fails and you can check retry count by using event data  #TelSimSecResult_t.
 *
 * @pre
 *  - Initialize Dbus connection with #tel_init
 *  - Register caller's application name with #tel_register_app_name
 *  - Register telephony events to listen
 *  - A event loop is running to listen events
 * - This API is used when #TelSimCardStatus_t is TAPI_SIM_STATUS_SIM_PIN_REQUIRED or TAPI_SIM_STATUS_SIM_LOCK_REQUIRED on boot time.
 * - Currently there`s no proper scenario for PIN2 verification by using this API.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = TAPI_API_SUCCESS; // 0
 * int length = TAPI_SIM_PIN_LENGTH+1;
 * char init_pin_val[length] ;
 *
 * strcpy(init_pin_val, PIN1_NORMAL);
 *
 * TelSimSecPw_t pin_data = {0,};
 *
 * pin_data.type = TAPI_SIM_PTYPE_PIN1;
 * pin_data.pw_len = strlen(init_pin_val);
 *
 * printf("pw_len[%d]", pin_data.pw_len);
 *
 * pin_data.pw = (char*)malloc(length);
 * memcpy(pin_data.pw,init_pin_val,length);
 *
 * err_code = tel_verifiy_sim_pins(handle, &pin_data, callback, user_data);
 *
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_verifiy_sim_pins(TapiHandle *handle, const TelSimSecPw_t *pin_data, tapi_response_cb callback, void *user_data);

/**
 * @brief  This function performs unblock PIN1/PIN2 operation based on PUK information passed along with
 * unblock information entered by the user.
 * If you get sim card status(TAPI_SIM_STATUS_SIM_PUK_REQUIRED) by using #tel_get_sim_init_info on boot time
 * or (TAPI_SIM_PIN_STATUS_BLOCKED) by using #tel_get_sim_facility after normal initialization for specific operation,
 * you may unblock PIN1/PIN2.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - Based on Pin status (PIN1/PIN2) is blocked, an unsolicited event TAPI_EVENT_SIM_STATUS_IND
 * is published to Applications on boot time also.
 *
 * @warning
 * - If you fail to unblock PIN til given retry count, Your SIM card be permanent block status.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param[in] puk_data
 * -Specifies unblocking PIN password #TelSimSecPw_t
 *
 * @param[in] new_pin_data
 * -Specifies PIN password which you want to use after unblocking operation #TelSimSecPw_t
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * The event associated is TAPI_EVENT_SIM_VERIFY_PUK_CNF  and the event data is #TelSimSecResult_t.
 * Asynchronous return status is indicated by #TelSimPinOperationResult_t.
 * If returned status is TAPI_SIM_PIN_OPERATION_SUCCESS, Verification successes.
 * If returned status is TAPI_SIM_PUK_INCORRECT_PASSWORD, Verification fails and you can check retry count by using event data  #TelSimSecResult_t.
 *
 * @pre
 *  - Initialize Dbus connection with #tel_init
 *  - Register caller's application name with #tel_register_app_name
 *  - Register telephony events to listen
 *  - A event loop is running to listen events
 *  - PIN1 or PIN2 status should be TAPI_SIM_PIN_STATUS_BLOCKED and Card status should be TAPI_SIM_STATUS_SIM_PUK_REQUIRED on boot time.
 *
 * @post
 *  - After Success on unblocking for PIN1 or PIN2, each pin check facility is enabled even if previous facility is disabled.
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 *
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = TAPI_API_SUCCESS; // 0
 * int length = TAPI_SIM_PIN_LENGTH+1;
 *
 * char init_pin_val[length];
 * char init_puk_val[length];
 *
 * strcpy(init_pin_val, PIN1_NORMAL);
 * strcpy(init_puk_val, PUK1_NORMAL);
 *
 * TelSimSecPw_t puk_data = {0,};
 * TelSimSecPw_t new_pin_data = {0,};
 *
 * puk_data.type = TAPI_SIM_PTYPE_PUK1;   // 0x00
 * puk_data.pw_len = length;
 * puk_data.pw_len = strlen(init_puk_val);
 * printf("pw_len[%d]", puk_data.pw_len);
 * memcpy(puk_data.pw,init_pin_val,length);
 *
 * new_pin_data.type = TAPI_SIM_PTYPE_PIN1;   // 0x00
 * new_pin_data.pw_len = strlen(init_pin_val);
 * printf("pw_len[%d]", new_pin_data.pw_len);
 * new_pin_data.pw = (char*)malloc(length);
 * memcpy(new_pin_data.pw,init_pin_val,length);
 *
 * err_code = tel_verify_sim_puks(handle, &puk_data, &new_pin_data, callback, user_data);
 *
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_verify_sim_puks(TapiHandle *handle, const TelSimSecPw_t *puk_data, const TelSimSecPw_t *new_pin_data, tapi_response_cb callback, void *user_data);


/**
 * @brief  This function changes PIN1/PIN2 code based on the pin type passed along with old pin data and new pin data.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - User should fill up pin type equally both old_pin and new_pin.
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param[in] old_pin
 * -Old pin code, entered by the user. #TelSimSecPw_t
 *
 * @param[in] new_pin
 * -New pin code, entered by the user. #TelSimSecPw_t
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * The event associated is TAPI_EVENT_SIM_CHANGE_PINS_CNF  and the event data is #TelSimSecResult_t.
 * Asynchronous return status is indicated by #TelSimPinOperationResult_t.
 * If returned status is TAPI_SIM_PIN_OPERATION_SUCCESS, Change operation finish successfully.
 * If returned status is TAPI_SIM_PIN_INCORRECT_PASSWORD, Change operation fails and you can check retry count by using event data  #TelSimSecResult_t.
 *
 * @pre
 *  - Initialize Dbus connection with #tel_init
 *  - Register caller's application name with #tel_register_app_name
 *  - Register telephony events to listen
 *  - A event loop is running to listen events
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *  - PIN which user want to change check facility should be enabled.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 *
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * err_code = TAPI_API_SUCCESS; // 0
 * int length = TAPI_SIM_PIN_LENGTH+1;
 * char init_old_pin_val[length] ;
 * char init_new_pin_val[length];
 *
 * memset(&init_old_pin_val, 0 , length);
 * memset(&init_new_pin_val, 0 , length);
 *
 * TelSimSecPw_t old_pin = {0,};
 * TelSimSecPw_t new_pin = {0,};
 *
 * strcpy(init_old_pin_val, PIN1_ORG);
 *
 * old_pin.type = TAPI_SIM_PTYPE_PIN1;
 * old_pin.pw_len = strlen(init_old_pin_val);
 * printf("pw_len[%d]", old_pin.pw_len);
 * old_pin.pw = (char*)malloc(length);
 * memcpy(old_pin.pw,init_old_pin_val,length);
 *
 * strcpy(init_new_pin_val, PIN1_NEW);
 *
 * new_pin.type = TAPI_SIM_PTYPE_PIN1;
 * new_pin.pw_len = strlen(init_new_pin_val);
 * printf("pw_len[%d]", new_pin.pw_len);
 * new_pin.pw = (char*)malloc(length);
 * memcpy(new_pin.pw,init_new_pin_val,length);
 *
 * err_code = tel_change_sim_pins(handle, &old_pin, &new_pin, callback, user_data);
 *
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_change_sim_pins(TapiHandle *handle, const TelSimSecPw_t *old_pin, const TelSimSecPw_t *new_pin, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to disable the SIM facility.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param[in] pw
 *  - a structure which contains facility type and password.
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par
 *
 * @pre
 *
 * @post
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * int err_code = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * TelSimFacilityPw_t *fc_pw;
 * int length = TAPI_SIM_PIN_LENGTH+1;
 * char init_pin_val[length] ;
 *
 * strcpy(init_pin_val, PIN1_NORMAL);
 *
 * fc_pw.lock_type = TAPI_SIM_LOCK_SC; // Set locktype for which facility should be disabled;
 * fc_pw.pw_len = strlen(init_pin_val);
 *
 * printf("pw_len[%d]", fc_pw.pw_len);
 *
 * fc_pw.pw = (char*)malloc(length);
 * memcpy(fc_pw.pw,init_pin_val,length);
 * err_code = tel_disable_sim_facility(handle, fc_pw, callback, user_data);
 *
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_disable_sim_facility(TapiHandle *handle, TelSimFacilityPw_t *pw, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to enable the SIM facility.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param[in] pw
 *  - a structure which contains facility type and password.
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par
 *
 * @pre
 *
 * @post
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * int err_code = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * TelSimFacilityPw_t *fc_pw;
 * int length = TAPI_SIM_PIN_LENGTH+1;
 * char init_pin_val[length] ;
 *
 * strcpy(init_pin_val, PIN1_NORMAL);
 *
 * fc_pw.lock_type = TAPI_SIM_LOCK_SC; // Set locktype for which facility should be disabled;
 * fc_pw.pw_len = strlen(init_pin_val);
 *
 * printf("pw_len[%d]", fc_pw.pw_len);
 *
 * fc_pw.pw = (char*)malloc(length);
 * memcpy(fc_pw.pw,init_pin_val,length);
 * err_code = tel_enable_sim_facility(handle, fc_pw, callback, user_data);
 *
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_enable_sim_facility(TapiHandle *handle, TelSimFacilityPw_t *pw, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to get the SIM facility.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param[in] type
 *  - type of security lock type enum values.
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par
 *
 * @pre
 *
 * @post
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * int err_code = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * TelSimLockType_t type = TAPI_SIM_LOCK_SC; // Set locktype for which facility should be disabled;
 * err_code = tel_get_sim_facility(handle, type, callback, user_data);
 *
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_facility(TapiHandle *handle, TelSimLockType_t type, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API is used to get the SIM LOCK TYPE info.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param[in] type
 *  - type of security lock type enum values.
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par
 *
 * @pre
 *
 * @post
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * int err_code = 0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * TelSimLockType_t type = TAPI_SIM_LOCK_SC; // Set locktype for which facility should be disabled;
 * err_code = tel_get_sim_lock_info(handle, type, callback, user_data);
 *
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_get_sim_lock_info(TapiHandle *handle, TelSimLockType_t type, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API provides common interface for accessing SIM data based on USIM generic command in ETSI TS 102 221
 * and 3GPP TS 31.102 Characteristics of the Universal Subscriber Identity Module (USIM) application.
 * This API provides only interface to send APDU. User should know well APDU usage.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param[in] apdu_data
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * The event associated is TAPI_EVENT_SIM_APDU_CNF  and the event data is #TelSimApduResp_t.
 * Asynchronous return status is indicated by #TelSimAccessResult_t.
 *
 * @pre
 *  - A dbus connection is established with #tel_init
 *  - The application name is registered with #tel_register_app_name
 *  - The application is registered events to listen asynchronous response with #tel_register_event
 *  - A event loop is running to listen events
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * int err_code =0;
 * TapiHandle *handle;  // Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 * TelSimApdu_t apdu = {0,};
 * int tmp_apdu[5] = {0xa,5,6,7,8};
 * apdu.apdu_len = 5; //user should check
 * apdu.apdu = apdu;
 *
 * err_code = tel_req_sim_apdu(handle, apdu, callback, user_data);
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_req_sim_apdu(TapiHandle *handle, TelSimApdu_t* apdu_data, tapi_response_cb callback, void *user_data);

/**
 * @brief  This API provides common interface to get SIM ATR(Answer To Reset) value.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None
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
 * The event associated is TAPI_EVENT_SIM_ATR_CNF  and the event data is #TelSimAtrResp_t.
 * Asynchronous return status is indicated by #TelSimAccessResult_t.
 *
 * @pre
 *  - A dbus connection is established with #tel_init
 *  - The application name is registered with #tel_register_app_name
 *  - The application is registered events to listen asynchronous response with #tel_register_event
 *  - A event loop is running to listen events
 *  - User can get valid return value or make operations after SIM init complete(card status is TAPI_SIM_STATUS_SIM_INIT_COMPLETED).
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code
 * #include <ITapiSim.h>
 * int err_code =0;
 * TapiHandle *handle;	// Handle given by tel_init()
 * tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
 * void *user_data; // Set User data
 *
 * // REQUEST SIM ATR
 * err_code = tel_req_sim_atr(handle, callback, user_data);
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_req_sim_atr(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/*
 * @brief  This API provides synchronous call interface over some operations (refer to @param [in] op_type)
 *
 * @par Sync (or) Async:
 * This is an Synchronous API.
 *
  * @par Important Notes:
 * - None
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param [in] op_type
 * operation type to do what caller want.
 * - TAPI_SIM_GET_INIT_STATUS
 * - TAPI_SIM_GET_CARD_TYPE
 * - TAPI_SIM_GET_IMSI
 * - TAPI_SIM_GET_ECC
 * - TAPI_SIM_GET_ICCID
 * - TAPI_SIM_GET_SPN
 * - TAPI_SIM_GET_CPHS_NET_NAME
 * - TAPI_SIM_TRANSFER_APDU
 * - TAPI_SIM_GET_ATR
 * - ( below are not supported. )
 * - TAPI_SIM_GET_LANGUAGE
 * - TAPI_SIM_SET_LANGUAGE
 * - TAPI_SIM_GET_CALL_FORWARDING
 * - TAPI_SIM_SET_CALL_FORWARDING
 * - TAPI_SIM_GET_MESSAGE_WAITING
 * - TAPI_SIM_SET_MESSAGE_WAITING
 * - TAPI_SIM_GET_MAILBOX
 * - TAPI_SIM_SET_MAILBOX
 * - TAPI_SIM_GET_CPHS_INFO
 * - TAPI_SIM_GET_SVCT
 * - TAPI_SIM_GET_MSISDN
 * - TAPI_SIM_GET_OPLMWACT
 * - TAPI_SIM_AUTHENTICATION
 * - TAPI_SIM_VERIFY_SEC
 * - TAPI_SIM_VERIFY_PUK
 * - TAPI_SIM_CHANGE_PIN
 * - TAPI_SIM_DISABLE_FACILITY
 * - TAPI_SIM_ENABLE_FACILITY
 * - TAPI_SIM_GET_FACILITY
 * - TAPI_SIM_GET_LOCK_INFO
 *
 * @param [in] inparam
 * input parameter of union type. caller should fill when it is needed as below.
 * - TAPI_SIM_GET_INIT_STATUS	: (not needed)
 * - TAPI_SIM_GET_CARD_TYPE		: (not needed)
 * - TAPI_SIM_GET_IMSI			: (not needed)
 * - TAPI_SIM_GET_ECC			: (not needed)
 * - TAPI_SIM_GET_ICCID			: (not needed)
 * - TAPI_SIM_GET_SPN			: (not needed)
 * - TAPI_SIM_GET_CPHS_NET_NAME	: (not needed)
 * - TAPI_SIM_TRANSFER_APDU		: TelSimApdu_t
 * - TAPI_SIM_GET_ATR			: (not needed)
 *
 * @param [out] outparam
 * output parameter of union type. TAPI returns a value as caller want.
 * - TAPI_SIM_GET_INIT_STATUS	: TelSimInitInfo_t
 * - TAPI_SIM_GET_CARD_TYPE		: TelSimCardType_t
 * - TAPI_SIM_GET_IMSI			: TelSimImsiInfo_t
 * - TAPI_SIM_GET_ECC			: TelSimEccList_t
 * - TAPI_SIM_GET_ICCID			: TelSimIccIdInfo_t
 * - TAPI_SIM_GET_SPN			: TelSimSpn_t
 * - TAPI_SIM_GET_CPHS_NET_NAME	: TelSimCphsNetName_t
 * - TAPI_SIM_TRANSFER_APDU		: TelSimApduResp_t
 * - TAPI_SIM_GET_ATR			: TelSimAtrResp_t
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
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code (for example, tel_req_sim_apdu())
 * #include <ITapiSim.h>
 * int rt = 0;
 * TelResponseData_t outparam;
 * TelRequestData_t inparam;
 * TapiHandle *handle;  // Handle given by tel_init()
 * unsigned char apdu[5] = { 0x00, 0x70, 0x00, 0x00, 0x00};
 * memset (&outparam, 0, sizeof(TelResponseData_t));
 * memset (&inparam, 0, sizeof(TelRequestData_t));
 *
 * inparam.apdu.apdu_len = strlen(apdu);
 * inparam.apdu.apdu = (unsigned char*)malloc(5);
 * memcpy (inparam.apdu.apdu, apdu, inparam.apdu.apdu_len);
 *
 * rt = tel_request_sim_sync(handle, TAPI_SIM_TRANSFER_APDU, &inparam, &outparam);
 *
 * if(inparam.apdu.apdu)
 * 	free(inparam.apdu.apdu);
 *
 * msg("rt = [%d]", rt);
 * if (rt == 0) {
 * 	msg("outparam.apdu_resp.apdu_resp_len[%d]", outparam.apdu_resp.apdu_resp_len);
 * 	if (outparam.apdu_resp.apdu_resp_len) {
 * 		for (i = 0; i < outparam.apdu_resp.apdu_resp_len; i++)
 * 			msg("[%d]`s byte is [0x%x]", i, outparam.apdu_resp.apdu_resp[i]);
 * 	}
 * }
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_request_sim_sync(TapiHandle *handle, TelSimTapiOperation_t op_type, TelSimRequestData_t *inparam, TelSimResponseData_t *outparam);

/*
 * @brief  This API provides asynchronous call interface over some operations (refer to @param [in] op_type)
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - None
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param [in] op_type
 * operation type to do what caller want.
 * - TAPI_SIM_GET_INIT_STATUS
 * - TAPI_SIM_GET_CARD_TYPE
 * - TAPI_SIM_GET_IMSI
 * - TAPI_SIM_GET_ECC
 * - TAPI_SIM_GET_ICCID
 * - TAPI_SIM_GET_SPN
 * - TAPI_SIM_GET_CPHS_NET_NAME
 * - TAPI_SIM_TRANSFER_APDU
 * - TAPI_SIM_GET_ATR
 * - ( below are not supported. )
 * - TAPI_SIM_GET_LANGUAGE
 * - TAPI_SIM_SET_LANGUAGE
 * - TAPI_SIM_GET_CALL_FORWARDING
 * - TAPI_SIM_SET_CALL_FORWARDING
 * - TAPI_SIM_GET_MESSAGE_WAITING
 * - TAPI_SIM_SET_MESSAGE_WAITING
 * - TAPI_SIM_GET_MAILBOX
 * - TAPI_SIM_SET_MAILBOX
 * - TAPI_SIM_GET_CPHS_INFO
 * - TAPI_SIM_GET_SVCT
 * - TAPI_SIM_GET_MSISDN
 * - TAPI_SIM_GET_OPLMWACT
 * - TAPI_SIM_AUTHENTICATION
 * - TAPI_SIM_VERIFY_SEC
 * - TAPI_SIM_VERIFY_PUK
 * - TAPI_SIM_CHANGE_PIN
 * - TAPI_SIM_DISABLE_FACILITY
 * - TAPI_SIM_ENABLE_FACILITY
 * - TAPI_SIM_GET_FACILITY
 * - TAPI_SIM_GET_LOCK_INFO
 *
 * @param [in] inparam
 * input parameter of union type. caller should fill when it is needed as below.
 * - TAPI_SIM_GET_INIT_STATUS	: (not needed)
 * - TAPI_SIM_GET_CARD_TYPE		: (not needed)
 * - TAPI_SIM_GET_IMSI			: (not needed)
 * - TAPI_SIM_GET_ECC			: (not needed)
 * - TAPI_SIM_GET_ICCID			: (not needed)
 * - TAPI_SIM_GET_SPN			: (not needed)
 * - TAPI_SIM_GET_CPHS_NET_NAME	: (not needed)
 * - TAPI_SIM_TRANSFER_APDU		: TelSimApdu_t
 * - TAPI_SIM_GET_ATR			: (not needed)

 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message: *
 * Asynchronous return status is indicated by #TelSimAccessResult_t.
 * Asynchronous response data is #TelSimResponseData_t union type. TAPI returns what caller want.
 * - TAPI_SIM_GET_INIT_STATUS	: TelSimInitInfo_t
 * - TAPI_SIM_GET_CARD_TYPE		: TelSimCardType_t
 * - TAPI_SIM_GET_IMSI			: TelSimImsiInfo_t
 * - TAPI_SIM_GET_ECC			: TelSimEccList_t
 * - TAPI_SIM_GET_ICCID			: TelSimIccIdInfo_t
 * - TAPI_SIM_GET_SPN			: TelSimSpn_t
 * - TAPI_SIM_GET_CPHS_NET_NAME	: TelSimCphsNetName_t
 * - TAPI_SIM_TRANSFER_APDU		: TelSimApduResp_t
 * - TAPI_SIM_GET_ATR			: TelSimAtrResp_t
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int)
 * - Integer '0' ( same with TAPI_API_SUCCESS & TAPI_SIM_ACCESS_SUCCESS )  - indicating that the operation has completed successfully.
 * - Negative integer : it provides an error code before actual operations. (Refer #TapiResult_t)
 * - Positive integer : it provides an error code while actual operations. (Refer to #TelSimAccessResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @see None
 *
 * @code (for example, tel_req_sim_apdu())
 * #include <ITapiSim.h>
 * int rt = 0;
 * TelRequestData_t inparam;
 * TapiHandle *handle;  // Handle given by tel_init()
 * unsigned char apdu[5] = { 0x00, 0x70, 0x00, 0x00, 0x00};
 * memset (&inparam, 0, sizeof(TelRequestData_t));
 *
 * inparam.apdu.apdu_len = 5;
 * inparam.apdu.apdu = (unsigned char*)malloc(5);
 * memcpy (inparam.apdu.apdu, apdu, inparam.apdu.apdu_len);
 *
 * rt = tel_request_sim_async(handle, TAPI_SIM_TRANSFER_APDU, &inparam, on_sim_call_async, NULL);
 * if(inparam.apdu.apdu)
 * 	free(inparam.apdu.apdu);
 * 	}
 * }
 *
 * void on_sim_call_async (TapiHandle *handle, int result, void *data,
 * 		void *user_data)
 * {
 * 		TelSimAccessResult_t access_rt = result;
 * 		TelSimResponseData_t *resp = data;
 * 		int i = 0;
 *
 * 		msg("tel_request_sim_async() response received");
 * 		msg("access_rt[%d]", access_rt);
 *
 * 		if (access_rt == 0) {
 * 			msg("apdu_resp_len[%d]", resp->apdu_resp.apdu_resp_len);
 * 			if (resp->apdu_resp.apdu_resp_len) {
 * 				for (i = 0; i < resp->apdu_resp.apdu_resp_len; i++)
 * 					msg("[%d]`s byte is [0x%x]", i, resp->apdu_resp.apdu_resp[i]);
 * 			}
 * 		}
 * }
 *
 * @endcode
 *
 * @remarks None
 *
 */
/*================================================================================================*/
int tel_request_sim_async(TapiHandle *handle, TelSimTapiOperation_t op_type, TelSimRequestData_t *inparam, tapi_response_cb callback, void *user_data);

#ifdef __cplusplus
}
#endif

#endif /* _ITAPI_SIM_H_ */

/**
* @}
*/
