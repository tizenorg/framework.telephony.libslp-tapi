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
 * @addtogroup	Network_TAPI	NETWORK
 * @{
 *
 * @file ITapiNetwork.h

 @brief This file serves as a "C" header file defines functions for Tapi Network\n
 It contains a sample set of function prototypes that would be required by applications.
 */

#ifndef _ITAPI_NETWORK_H_
#define _ITAPI_NETWORK_H_

#include <tapi_common.h>
#include <TelErr.h>
#include <TelDefines.h>
#include <TelNetwork.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief  This function requests the lower layers to select the network automatically
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
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
 * Asynchronous return status is indicated by #TelNetworkOperationCause_t.
 * There is no data associated with the response.
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
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetwork.h>
 *
 * int ret_status;
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * //SET NETWORK SELECTION AUTOMATIC MODE
 * ret_status = tel_select_network_automatic(handle, callback, user_data);
 * @endcode
 *
 * @see
 *  - None.
 *
 * @remarks
 *  - None.
 *
 *
 */
/*================================================================================================*/
int tel_select_network_automatic(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This function requests the lower layers to select the network (PLMN) which has been selected by the user from the Network List
 *           displayed to the User.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
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
 * @param[in] plmn
 * - User selected PLMN.

 * @param [in] act
 * - User selected Access Technology.

 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * Asynchronous return status is indicated by #TelNetworkOperationCause_t.
 * There is no data associated with the response.
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
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetwork.h>
 *
 * int ret_status;
 * unsigned int plmn = 0;
 * TapiHandle *handle;
 * const char *plmn;
 * int act;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * //SET NETWORK SELECTION MANUAL MODE
 * plmn = 45454;
 * act = 0x1; //For GSM.
 * ret_status = tel_select_network_manual(handle, plmn, act, callback, user_data);
 * @endcode
 *
 * @see
 *  - None.
 *
 * @remarks
 *  - None.
 *
 *
 */
/*================================================================================================*/
int tel_select_network_manual(TapiHandle *handle, const char *plmn, int act, tapi_response_cb callback, void *user_data);

/**
 * @brief  This function sends a request to do manual network search for the available networks and provide the
 *           Network List to the User/Application.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
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
 * Asynchronous return status is indicated by #TelNetworkOperationCause_t.
 * Data associated with the response is #TelNetworkPlmnList_t.
 *
 * @pre
 *  - A dbus connection is established with #tel_init
 *  - The application name is registered with #tel_register_app_name
 *  - The application is registered events to listen asynchronous response with #tel_register_event
 *  - A event loop is running to listen events
 *
 * @post
 *  - In the available network list, user can select one of the networks successfully.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetwork.h>
 *
 * int ret_status;
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * // NETWORK SEARCH
 * ret_status = tel_search_network(handle, callback, user_data);
 * @endcode
 *
 * @see
 *  - None.
 *
 * @remarks
 *  - None.
 *
 *
 */
/*================================================================================================*/
int tel_search_network(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This function requests for the present network selection mode i.e. automatic or manual.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
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
 * Asynchronous return status is indicated by #TelNetworkOperationCause_t.
 * Data associated with the response is #TelNetworkSelectionMode_t.
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
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetwork.h>
 *
 * int ret_status;
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * // GET NETWORK SELECTION MODE
 * ret_status = tel_get_network_selection_mode (handle, callback, user_data);
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
int tel_get_network_selection_mode(struct tapi_handle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This function is called when User/application wants to configure the service domain to only CS or only PS or Both.
 * This API triggers the underlying protocol stack to do register with Network for only CS services or only PS services
 * or both based on the option set using this API.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
 *
 * @par Important Notes:
 * - None.
 *
 * @warning
 * - None.
 *
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param[in] ServiceDomain
 * - Specifies the type of Service domain (Packet switch, Circuit switch or both)
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * The event associated is TAPI_EVENT_NETWORK_SET_SVC_DOMAIN_CNF and there is no event data associated with this event
 * and asynchronous return status is indicated by #TelNetworkOperationCause_t.
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
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetwork.h>
 *
 * int ret_status;
 * TapiHandle *handle;
 * TelNetworkServiceDomain_t domain;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * // SET NETWORK SERVICE DOMAIN
 * domain = TAPI_NETWORK_SERVICE_DOMAIN_AUTOMATIC;
 *
 * ret_status = tel_set_network_service_domain (handle, domain, callback, user_data);
 * @endcode
 *
 * @see
 *  - None.
 *
 * @remarks
 *  - None.
 *
 *
 */
/*================================================================================================*/
int tel_set_network_service_domain(TapiHandle *handle, TelNetworkServiceDomain_t domain,
		tapi_response_cb callback, void *user_data);

/**
 * @brief  This function requests for the present network service domain i.e. CS or PS or both or automatic.
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * This function makes Dbus method call to Telephony Sever and returns immediate value.
 * However it just means that the API request has been transfered to the CP successfully.
 * The actual operation result is being delivered in the corresponding event asynchronously.
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
 * Asynchronous return status is indicated by #TelNetworkOperationCause_t.
 * Data associated with the response is #TelNetworkServiceDomain_t.
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
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetwork.h>
 *
 * int ret_status;
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * // GET NETWORK SERVICE DOMAIN
 * ret_status = tel_get_network_service_domain (handle, callback, user_data);
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
 */
/*================================================================================================*/
int tel_get_network_service_domain(TapiHandle *handle, tapi_response_cb callback, void *user_data);


/**
 * @brief  This function is invoked to set the network band and allows the underlying OEM provider to scan the set band.
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
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param[in]  mode
 * - Band preference indicates the band provided to be preferred or selected band.
 *
 * @param[in]  band
 * - This enumeration defines different network bands that user can choose.
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * The event associated is TAPI_EVENT_NETWORK_SETNWBAND_CNF and there is no event data associated with this event and asynchronous
 * return status is indicated by #TelNetworkOperationCause_t.
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
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetwork.h>
 *
 * int ret_status;
 * TapiHandle *handle;
 * TelNetworkBandPreferred_t mode;
 * TelNetworkBand_t band;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * mode = TAPI_NETWORK_BAND_MODE_PREFERRED;
 * band = TAPI_NETWORK_BAND_TYPE_GSM_900_1800;
 *
 * // SET NETWORK BAND
 * ret_status = tel_set_network_band (handle, mode, band, callback, user_data);
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
int tel_set_network_band(TapiHandle *handle, TelNetworkBandPreferred_t mode,
		TelNetworkBand_t band, tapi_response_cb callback, void *user_data);

/**
 * @brief  This function requests for the present network band.
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
 * Asynchronous return status is indicated by #TelNetworkOperationCause_t.
 * Data associated with the response is #TelNetworkBand_t.
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
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetwork.h>
 *
 * int ret_status;
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * // GET NETWORK BAND
 * ret_status = tel_get_network_band(handle, callback, user_data);
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
int tel_get_network_band(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This function is invoked to set the network preferred plmn
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
 *
 * @param [in] handle
 * - handle from tel_init().
 *
 * @param[in]  operation
 * - Operation indicates the operation to be done on preferred plmn .
 *
 * @param[in]  info
 * - This gives the plmn Info.
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * The event associated is TAPI_EVENT_NETWORK_SETPREFFPLMN_CNF and there is no event data associated with this event and asynchronous
 * return status is indicated by #TelNetworkOperationCause_t.
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
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetwork.h>
 *
 * int ret_status;
 * TapiHandle *handle;
 * TelNetworkPreferredPlmnOp_t operation;
 * TelNetworkPreferredPlmnInfo_t info;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * unsigned char *plmn = "45454";
 *
 * operation = TAPI_NETWORK_PREF_PLMN_ADD;
 * memset(&info, 0, sizeof(TelNetworkPreferredPlmnInfo_t));
 * info.Index = 0;
 * info.SystemType = TAPI_NETWORK_SYSTEM_GSM;
 * memcpy(info.Plmn, plmn, strlen(plmn));
 *
 * // SET NETWORK PREFERRED PLMN
 * ret_status = tel_set_network_preferred_plmn(handle, operation, &info, callback, user_data);
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
int tel_set_network_preferred_plmn(TapiHandle *handle, TelNetworkPreferredPlmnOp_t operation,
		TelNetworkPreferredPlmnInfo_t *info, tapi_response_cb callback, void *user_data);

/**
 * @brief  This function is invoked to get the preferred plmn list
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
 *
 * @par Async Response Message:
 * Asynchronous return status is indicated by #TelNetworkOperationCause_t.
 * Data associated with the response is #TelNetworkPreferredPlmnList_t.
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
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetwork.h>
 *
 * int ret_status;
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * // GET NETWORK PREFERRED PLMN
 * ret_status = tel_get_network_preferred_plmn(handle, callback, user_data);
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
int tel_get_network_preferred_plmn(TapiHandle *handle, tapi_response_cb callback, void *user_data);


/**
 * @brief  This function is called to cancel the triggered manual network search.
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
 * Asynchronous return status is indicated by #TelNetworkOperationCause_t.
 * There is no data associated with the response.
 *
 * @pre
 *  - Manual network search is already triggered.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetwork.h>
 *
 * int ret_status;
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * // CANCEL NETWORK MANUAL SEARCH
 * ret_status = tel_cancel_network_manual_search(handle, callback, user_data);
 *
 * @endcode
 *
 * @see
 *  - None.
 *
 * @remarks
 *  - None.
 *
 */
/*================================================================================================*/
int tel_cancel_network_manual_search(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This function is called to get network serving information
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
 * Asynchronous return status is indicated by #TelNetworkOperationCause_t.
 * Data associated with the response is #TelNetworkServing_t.
 *
 * @pre
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetwork.h>
 *
 * int ret_status;
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * // GET NETWORK SERVING
 * ret_status = tel_get_network_serving(handle, callback, user_data);
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
 */
/*================================================================================================*/
int tel_get_network_serving(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This function is called to set network mode.
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
 * @param [in] mode
 * - Specifies the network mode (GSM only or WCDMA only or Automatic etc)
 *
 * @param [in] callback
 * - To register callback function for result.
 *
 * @param [in] user_data
 * - user_data for user specification.
 *
 * @par Async Response Message:
 * Asynchronous return status is indicated by #TelNetworkOperationCause_t.
 * There is no data associated with the response.
 *
 * @pre
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetwork.h>
 *
 * int ret_status;
 * TapiHandle *handle;
 * int mode;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * mode = 0x01; //GSM mode
 * // SET NETWORK MODE
 * ret_status = tel_set_network_mode(handle, mode, callback, user_data);
 *
 * @endcode
 *
 * @see
 *  - None.
 *
 * @remarks
 *  - None.
 *
 */
/*================================================================================================*/
int tel_set_network_mode(TapiHandle *handle, int mode, tapi_response_cb callback, void *user_data);

/**
 * @brief  This function is called to get network mode.
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
 * Asynchronous return status is indicated by #TelNetworkOperationCause_t.
 * Data associated with the response is GSM only or WCDMA only or Automatic etc.
 *
 * @pre
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetwork.h>
 *
 * int ret_status;
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * // GET NETWORK MODE
 * ret_status = tel_get_network_mode(handle, callback, user_data);
 *
 * @endcode
 *
 * @see
 *  - None.
 *
 * @remarks
 *  - None.
 *
 */
/*================================================================================================*/
int tel_get_network_mode(TapiHandle *handle, tapi_response_cb callback, void *user_data);

/**
 * @brief  This function is called to get neighboring cell info.
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
 * Asynchronous return status is indicated by #TelNetworkOperationCause_t.
 * Data associated with the response is #TelNetworkNeighboringCellInfo_t.
 *
 * @pre
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Refer #TapiResult_t for failure and error code
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetwork.h>
 *
 * int ret_status;
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void *user_data;
 *
 * // GET NETWORK NEIGHBORING CELL INFO
 * ret_status = tel_get_network_neighboring_cell_info(handle, callback, user_data);
 *
 * @endcode
 *
 * @see
 *  - None.
 *
 * @remarks
 *  - None.
 *
 */
/*================================================================================================*/
int tel_get_network_neighboring_cell_info(TapiHandle *handle, tapi_response_cb callback, void *user_data);

#ifdef __cplusplus
}
#endif

#endif	/* _ITAPI_NETWORK_H_ */

/**
 * @}
 */
