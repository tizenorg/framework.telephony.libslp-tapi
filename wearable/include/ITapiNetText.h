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
* @addtogroup	NetText_TAPI    NetText(SMS)
* @{
 *
* @file ITapiNettext.h

     @brief This file serves as a "C" header file defines functions for Tapi Nettext\n
      It contains a sample set of function prototypes that would be required by applications.

 */

#ifndef _ITAPI_NETTEXT_H_
#define _ITAPI_NETTEXT_H_

#include <tapi_common.h>
#include <TelSms.h>
#include <TelDefines.h>

#ifdef __cplusplus
extern "C"
{
#endif

 /**
 * @brief  This API is used to send an SMS message to the network.  This API interface allows transmitting SMS PDU as defined by
 *		3GPP TS 23.040 (SMS-SUBMIT, SMS-COMMAND) to lower layers. This API allows keeping the dedicated link at lower layers
 *		by passing information as more messages to send in parameters. This will enable not to release if a dedicated connection is
 *		used for transmission. Access to this API is limited to in-house application and we recommend you use Message Framework API(MAPI).
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
 * - handle from tel_init()
 *
 * @param [in] pDataPackage
 *   - Contains SMS-SUBMIT TPDU
 *
 * @param [in] bMoreMsgToSend
 *   - will be set to TRUE when there are more than one message to be send or Multiple segmented concatenated
 *      message to be send, otherwise FALSE. This flag indicates OEM that more messages to send.
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification
 *
 * @par Async Response Message:
 *  Asynchronous return status is indicated by #TelSmsResponse_t.
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetText.h>
 *
 * TelSmsDatapackageInfo_t *pDataPackage;
 * int ret_status = TAPI_API_SUCCESS;
 * TapiHandle *handle;
 * tapi_response_cb callback;
 * void* user_data;
 *
 *
 * pDataPackage = (TelSmsDatapackageInfo_t*) malloc(sizeof(TelSmsDatapackageInfo_t));

 * pDataPackage  fill the structure appropriately/
 * Sca parameter is optional. If you don't provide Service center address, you should fill "00" in sca array.
 * MsgLength is length of szData
 * fill the szData in TelSmsDatapackageInfo_t with SMS-SUBMIT or SMS-COMMAND TPDU.

 * ret_status = tel_send_sms(handle, pDataPackage, bMoreMsgToSend, callback, user_data);
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
int tel_send_sms(TapiHandle *handle, const TelSmsDatapackageInfo_t *pDataPackage, int bMoreMsgToSend, tapi_response_cb callback, void* user_data);

  /**
 * @brief  This function reads a message from SIM card storage. SIM index (index used when storing the SMS) number to be passed to in order
 *		to read particular SMS message. Total number of messages can be retrieved by #TelTapiSmsGetCount function.
  *		Access to this API is limited to in-house application and  we recommend you use Message Framework API(MAPI).
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
 * - handle from tel_init()
 *
 * @param [in] index
 *  -  Index number of the message to be read
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification
 *
 * @par Async Response Message:
 *  Asynchronous return status is indicated by #TelSmsResponse_t.
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetText.h>
 * int ret_status = TAPI_API_SUCCESS;
 * TapiHandle *handle;//Obtained from tel_init();
 * tapi_response_cb callback;
 * void* user_data;
 * int index;
 *
 * ret_status = tel_read_sms_in_sim(handle, index, callback, user_data);
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
 int tel_read_sms_in_sim(TapiHandle *handle, int index, tapi_response_cb callback, void* user_data);

 /**
 * @brief  This function writes a message to SIM storage area.
 *           Access to this API is limited to in-house application and  we recommend you use Message Framework API(MAPI).
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
 * - handle from tel_init()
 *
 * @param [in] pWriteData
 *  - SMS message structure.
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification
 *
 * @par Async Response Message:
 * Asynchronous return status is indicated by #TelSmsResponse_t.
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 *
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetText.h>
 *
 * int ret_status = TAPI_API_SUCCESS;
 * TapiHandle *handle;//Obtained from tel_init();
 * tapi_response_cb callback;
 * void* user_data;

 * TelSmsData_t *pWriteData;
 * char *msg = "This is an Test SMS";
 * char *SCA = "821091";
 *
 * pWriteData =(TelSmsData_t *)malloc(sizeof(TelSmsData_t));
 *
 * conv_service_center_address(pWriteData->SmsData.Sca, SCA); //convert service center address
 * conv_msg_into_tpdu(pWriteData->SmsData.szData, pWriteData->SmsData.MsgLength, msg); // convert message into TPDU
 * pWrite->MsgStatus = TAPI_NETTEXT_STATUS_READ;
 * pWrite->SimIndex = -1;
 *
 * ret_status = tel_write_sms_in_sim(handle, pWriteData, callback, user_data);
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
int tel_write_sms_in_sim(TapiHandle *handle, const TelSmsData_t *pWriteData, tapi_response_cb callback, void* user_data);

 /**
 * @brief  This function deletes a message specified by index (SIM index used when storing the SMS)
 *           number from the SIM storage area. Access to this API is limited to in-house application and we recommend you use Message Framework API(MAPI).
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
 * - handle from tel_init()
 *
 * @param [in] Index
 *  - Message index to delete.
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification
 *
 * @par Async Response Message:
 * Asynchronous return status is indicated by #TelSmsResponse_t.
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t).\n
 * @par Prospective Clients:
 *  External Apps.
 *
 * @code
 * #include <ITapiNetText.h>
 *
 * int ret_status = TAPI_API_SUCCESS;
 * TapiHandle *handle;//Obtained from tel_init();
 * tapi_response_cb callback;
 * void* user_data;
 * int index;
 *
 * ret_status = tel_delete_sms_in_sim(handle, index, callback, user_data);
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
int tel_delete_sms_in_sim(TapiHandle *handle, int index, tapi_response_cb callback, void* user_data);

 /**
 * @brief  This function is used to retrieve message count information like Total record count,
 *  used record count and the indices list for SIM Storage. This is an asynchronous function and
 *  the response will be sent back in the callback function. Access to this API is limited, we recommend you use Message Framework API(MAPI) besides.
 *  Access to this API is limited to in-house application.
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
 * - handle from tel_init()
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification

 *
 * @par Async Response Message:
 * Asynchronous return status is indicated by #TelSmsResponse_t.
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 * @par Prospective Clients:
 * - External Apps.\n
 *
 * @code
 * #include <ITapiNetText.h>
 *
 * int ret_status = TAPI_API_SUCCESS;
 * TapiHandle *handle;//Obtained from tel_init();
 * tapi_response_cb callback;
 * void* user_data;
 *
 * ret_status = tel_get_sms_count(handle, callback, user_data);
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
int tel_get_sms_count(TapiHandle *handle, tapi_response_cb callback, void* user_data);


 /**
 * @brief  This function is used to set SMS CB Message Identifiers in the appropriate EF-CBMI/EF-CBMIR file in (U)SIM.
 *		This function also indicates underlying provider to enable or disable CB Channel on which CB messages are received.
 *		Access to this API is limited to in-house application and we recommend you use Message Framework API(MAPI) besides.
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
 * - handle from tel_init()
 *
 * @param [in] pCBConfig
 *  - This structure contains parameters to set SMS CB configuration \n
 *      (i)  Cell broadcast service state. (Enabled/disabled.) \n
 *      (ii) Cell broadcast message identifier, which denotes whether all cell broadcast message identifiers are selected or only
 *           some of those.\n
 *	  (iii) The list count of message identifiers to be set.\n
 *	  (iv) The actual list of message identifiers to be set. Each identifier occupies 2 bytes. And the list ranges from 0x00 to 0xff. \n
 *    These message identifiers denote the source and type of the CB message. Based on the message identifiers set in the SIM,
 *    the ME receives CB messages with selected message identifiers.
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification
 *
 * @par Async Response Message:
 * Asynchronous return status is indicated by #TelSmsResponse_t.
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 *
 * @par Prospective Clients:
 * External Apps.\n
 *
 * @code
 * #include <ITapiNetText.h>
 *
 * int ret_status = TAPI_API_SUCCESS;
 * TapiHandle *handle;//Obtained from tel_init();
 * tapi_response_cb callback;
 * void* user_data;
 * TelSmsCbConfig_t *pCBConfig = NULL;
 *
 * pCBConfig = (TelSmsCbConfig_t *)malloc(sizeof(TelSmsCbConfig_t));
 * pCBConfig->bCBEnabled = 1; //fill structure appropriately
 * pCBConfig->SelectedId = 0x01;
 * pCBConfig->MsgIdCount = 0x02;
 *
 * pCBConfig->MsgIDs[0] = 0x0c;
 * pCBConfig->MsgIDs[1] = 0x0c;
 * pCBConfig->MsgIDs[2] = 0xdf;
 * pCBConfig->MsgIDs[3] = 0x00;
 *
 * ret_status = tel_set_sms_cb_config(handle, pCBConfig, callback, user_data);
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
int tel_set_sms_cb_config(TapiHandle *handle, const TelSmsCbConfig_t *pCBConfig, tapi_response_cb callback, void* user_data);

 /**
 * @brief  This function is used to retrieve SMS CB configuration parameters from EFcbmi file in the SIM.
 *		Access to this API is limited to in-house application and we recommend you use Message Framework API(MAPI).
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
 * - handle from tel_init()
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification
 *
 * @par Async Response Message:
 * Asynchronous return status is indicated by #TelSmsResponse_t.
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 * @par Prospective Clients:
 * - External Apps.\n
 *
 * @code
 * #include <ITapiNetText.h>
 *
 * int ret_status = TAPI_API_SUCCESS;
 * TapiHandle *handle;//Obtained from tel_init();
 * tapi_response_cb callback;
 * void* user_data;
 *
 * ret_status = tel_get_sms_cb_config(handle, callback, user_data);
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
int tel_get_sms_cb_config(TapiHandle *handle, tapi_response_cb callback, void* user_data);


 /**
 * @brief This function is used to set SMS preferred bearer on which SMS has to be transmitted.
 *	      Access to this API is limited to in-house application and we recommend you use Message Framework API(MAPI).
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
 * - handle from tel_init()
 *
 * @param [in] BearerType
 *  - Specifies the bearer type.
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification
 *
 * @par Async Response Message:
 * Asynchronous return status is indicated by #TelSmsResponse_t
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetText.h>
 * int ret_status = TAPI_API_SUCCESS;
 * TapiHandle *handle;//Obtained from tel_init();
 * tapi_response_cb callback;
 * void* user_data;
 * TelSmsBearerType_t BearerType = TAPI_NETTEXT_BEARER_PS_ONLY;
 *
 * ret_status = tel_set_sms_preferred_bearer(handle, BearerType, callback, user_data);
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
int tel_set_sms_preferred_bearer(TapiHandle *handle, TelSmsBearerType_t BearerType, tapi_response_cb callback, void* user_data);

 /**
 * @brief  This function is used to get SMS preferred bearer on which SMS has to be transmitted.
 *  This is an asynchronous function. Access to this API is limited to in-house application and , we recommend you use Message Framework API(MAPI).
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
 * - handle from tel_init()
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification
 *
 * @par Async Response Message:
 * Asynchronous return status is indicated by #TelSmsResponse_t.
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetText.h>
 *
 * int ret_status = TAPI_API_SUCCESS;
 * TapiHandle *handle;//Obtained from tel_init();
 * tapi_response_cb callback;
 * void* user_data;
 *
 * ret_status = tel_get_sms_preferred_bearer(handle, callback, user_data);
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
int tel_get_sms_preferred_bearer(TapiHandle *handle, tapi_response_cb callback, void* user_data);

 /**
 * @brief This function is used to get the SMS parameters for a particular SMS (sent/received)
 *  based on the SIM index where it is stored. This is an asynchronous function. Access to this API is limited to in-house application and we recommend you use Message Framework API(MAPI).
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
 * - handle from tel_init()
 *
 * @param [in] index
 *  - SIM index where the SMS is stored
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification
 *
 * @par Async Response Message:
 * Asynchronous return status is indicated by #TelSmsResponse_t
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetText.h>
 *
 * int ret_status = TAPI_API_SUCCESS;
 * TapiHandle *handle;//Obtained from tel_init();
 * tapi_response_cb callback;
 * void* user_data;
 * int index;
 *
 * ret_status = tel_get_sms_parameters(handle, index, callback, user_data);
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
int tel_get_sms_parameters(TapiHandle *handle, int index, tapi_response_cb callback, void* user_data);

 /**
 * @brief  This function is used to set the short message service header parameters which are
 *  used in the origination of MO messages. Access to this API is limited to in-house application and we recommend you use Message Framework API(MAPI).
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - This API updates/sets SMS Parameters in EFsmsp file in the SIM storage
 *
 * @warning
 * - None.
 *
 *
 * @param [in] handle
 * - handle from tel_init()
 *
 * @param [in] pSmsSetParameters
 *  - Contains SMS header Parameter information like service center address, destination address, validity period, protocol identifier,
 *     data coding scheme.
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification
 *
 * @par Async Response Message:
 * Asynchronous return status is indicated by #TelSmsResponse_t
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetText.h>
 *
 * int ret_status = TAPI_API_SUCCESS;
 * TapiHandle *handle;//Obtained from tel_init();
 * tapi_response_cb callback;
 * void* user_data;
 *
 * TelSmsParams_t SmsSetParameters = {0,};//fill the structure appropriately
 *
 * SmsSetParameters.RecordIndex = 0x01;
 * SmsSetParameters.RecordLen = 28;
 * memcpy(SmsSetParameters.TpDestAddr.szDiallingNum, "9986529874", 10);
 * printf("\ndial no is %s\n", SmsSetParameters.TpDestAddr.szDiallingNum);
 * SmsSetParameters.TpDestAddr.DialNumLen = 10;
 * SmsSetParameters.TpDestAddr.Ton = TAPI_SIM_TON_NATIONAL;//national no
 * SmsSetParameters.TpDestAddr.Npi = TAPI_SIM_NPI_NATIONAL;
 *
 * ret_status = tel_set_sms_parameters(handle, pSmsSetParameters, callback, user_data);
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
int tel_set_sms_parameters(TapiHandle *handle, const TelSmsParams_t *pSmsSetParameters, tapi_response_cb callback, void* user_data);

 /**
 * @brief This function is used to send a deliver report for the received incoming SMS to the network.
 *          Access to this API is limited to in-house application.
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
 * - handle from tel_init()
 *
 * @param [in] pDataPackage
 *  - Contains SMS Data package..
 *
 * @param [in] RPCause
 *  - Indicates the reason for SMS-DELIVER failure
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification
 *
 * @par Async Response Message:
 * Asynchronous return status is indicated by #TelSmsResponse_t
 *
 * @pre
 *  - SMS-DELIVER-REPORT message structure should be in TPDU format as specified by 3GPP TS 23.040 SMS TPDU.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetText.h>
 *
 * int ret_status = 0;
 * Int requestId = -1;
 * TelSmsResponse_t RPCause;
 * TelSmsDatapackageInfo_t *del_report = NULL;
 *
 * del_report = (TelSmsDatapackageInfo_t *)malloc(sizeof(TelSmsDatapackageInfo_t));
 * memset(del_report, 0, sizeof(TelSmsDatapackageInfo_t));
 * TelSmsDatapackageInfo_t //fill the structure appropriately
 * //Encode Send Delivery Report here
 * //EncodeSmsDeliveryReportTpdu();
 * Sca parameter is optional. If you don't provide Service center address, you should fill "00" in sca array.
 * MsgLength is length of szData
 * fill the szData in TelSmsDatapackageInfo_t .
 *
 * RPCause = TAPI_NETTEXT_SENDSMS_SUCCESS;
 * printf("***receive message (Api:SendDeliverreport)****\n");
 *
 * ret_status = tel_send_sms_deliver_report(handle, pDataPackage, RPCause, callback, user_data);
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
int tel_send_sms_deliver_report(TapiHandle *handle, const TelSmsDatapackageInfo_t *pDataPackage, TelSmsResponse_t RPCause, tapi_response_cb callback, void* user_data);

 /**
 * @brief  This function is used to set SMS Service Centre Address information in order to send the SMS.
 *           Access to this API is limited to in-house application and we recommend you use Message Framework API(MAPI).
 *
 * @par Sync (or) Async:
 * This is an Asynchronous API.
 *
 * @par Important Notes:
 * - This API updates/sets service center address in EFsmsp file in the SIM storage.
 *
 * @warning
 * - None.
 *
 * @param [in] handle
 * - handle from tel_init()
 *
 * @param [in] pSCA
 * - Contains the service centre address informations.
 *
 * @param [in] Index
 * - Contains the record index of the Service center address information in the EF.
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification
 *
 * @par Async Response Message:
 * Asynchronous return status is indicated by #TelSmsResponse_t.
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t).
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetText.h>
 *
 * int ret_status;
 * TapiHandle *handle;//Obtained from tel_init();
 * tapi_response_cb callback;
 * void* user_data;
 * int index;
 *
 * TelSmsAddressInfo_t *sc_addr = NULL;
 *
 *
 * printf("***Setting the SCA(Api:SetSCA)****\n");
 * sca = (TelSmsAddressInfo_t *)malloc(sizeof(TelSmsAddressInfo_t));
 * TelSmsAddressInfo_t // fill the structure appropriately
 * memset(sca, 0, sizeof(sca));
 * sca.DialNumLen = 0x5;
 * sca.Npi = TAPI_SIM_NPI_ISDN_TEL;
 * sca.Ton = TAPI_SIM_TON_INTERNATIONAL;
 * sca.szDiallingNum[0] = 0x28;
 * sca.szDiallingNum[1] = 0x01;
 * sca.szDiallingNum[2] = 0x19;
 * sca.szDiallingNum[3] = 0x11;
 * sca.szDiallingNum[4] = 0x11;
 *
 * ret_status = tel_set_sms_sca(handle, pSCA, index, callback, user_data);
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
int tel_set_sms_sca(TapiHandle *handle, const TelSmsAddressInfo_t *pSCA, int index, tapi_response_cb callback, void* user_data);

 /**
 * @brief  This function is used to get current SMS Service Centre Address information.
 *           Access to this API is limited to in-house application and we recommend you use Message Framework API(MAPI).
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
 * - handle from tel_init()
 *
 * @param [in] Index
 * - Contains the record index of the Service center address information in the SIM EF.
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification
 *
 * @par Async Response Message:
 * Asynchronous return status is indicated by #TelSmsResponse_t.
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetText.h>
 *
 * int ret_status = TAPI_API_SUCCESS;
 * TapiHandle *handle;//Obtained from tel_init();
 * tapi_response_cb callback;
 * void* user_data;
 * int index;
 *
 * ret_status = tel_get_sms_sca(handle, index, callback, user_data);
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
int tel_get_sms_sca(TapiHandle *handle, int index, tapi_response_cb callback, void* user_data);

 /**
 * @brief This function is used by the applications to inform modem about  the memory status of PDA (whether FULL or AVAILABLE) so that modem can inform network .
 *           Access to this API is limited to in-house application.
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
 * - handle from tel_init()
 *
 * @param [in] memoryStatus
 *  - Contains Memory Status
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification
 *
 * @par Async Response Message:
 *  Asynchronous return status is indicated by #TelSmsResponse_t
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetText.h>
 *
 * int ret_status = TAPI_API_SUCCESS;
 * TapiHandle *handle;//Obtained from tel_init();
 * tapi_response_cb callback;
 * void* user_data;
 * int MemoryStatus = TAPI_NETTEXT_PDA_MEMORY_STATUS_AVAILABLE;
 *
 * ret_status = tel_set_sms_memory_status(handle, memoryStatus, callback, user_data);
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
int tel_set_sms_memory_status(TapiHandle *handle, int memoryStatus, tapi_response_cb callback, void* user_data);

 /**
 * @brief  This function is used by the applications to set the message status in the SIM EF.
 *           Access to this API is limited to in-house application and we recommend you use Message Framework API(MAPI).
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
 * - handle from tel_init()
 *
 * @param [in] Index
 *  - Index of the message whose status has to be set.
 *
 * @param [in] msgStatus
 *  - Status of the message to be set.
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification
 *
 * @par Async Response Message:
 *  Asynchronous return status is indicated by #TelSmsResponse_t
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetText.h>
 *
 * int ret_status = TAPI_API_SUCCESS;
 * TapiHandle *handle;//Obtained from tel_init();
 * tapi_response_cb callback;
 * void* user_data;
 * int index = 1;
 * int MemoryStatus = TAPI_NETTEXT_PDA_MEMORY_STATUS_AVAILABLE;
 *
 * ret_status = tel_set_sms_message_status(handle, index, msgStatus, callback, user_data);
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
int tel_set_sms_message_status(TapiHandle *handle, int index, TelSmsMsgStatus_t msgStatus, tapi_response_cb callback, void* user_data);

 /**
 * @brief This function is used by the applications to get the count of SMS parameter records stored in SIM EF.
 *           Access to this API is limited to in-house application.
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
 * - handle from tel_init()
 *
 * @param [in] callback
 *   - To register callback function for result of this function.
 *
 * @param [in] user_data
 *   - user data for user specification
 *
 * @par Async Response Message:
 *  Asynchronous return status is indicated by #TelSmsResponse_t
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 * @par Prospective Clients:
 * External Apps.
 *
 * @code
 * #include <ITapiNetText.h>
 *
 * int ret_status = TAPI_API_SUCCESS;
 * TapiHandle *handle;//Obtained from tel_init();
 * tapi_response_cb callback;
 * void* user_data;
 *
 * ret_status = tel_get_sms_parameter_count(handle, callback, user_data);
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
int tel_get_sms_parameter_count(TapiHandle *handle, tapi_response_cb callback, void* user_data);


/**
 * @brief This function is used by the applications to check the sms ready status (whether ready or not) .
 *
 * @par Sync (or) Async:
 * This is a Synchronous API.
 *
 * @par Important Notes:
 * - None.
 *
 * @warning
 * - None.
 *
 *
 * @param [in] handle
 * - handle from tel_init()
 *
 * @param [out] pReadyStatus
 * - Contains Ready Status
 *
 * @par Async Response Message:
 *  None.
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 * @par Prospective Clients:
 * External Apps.
 *
 */
int tel_check_sms_device_status(TapiHandle *handle, int *pReadyStatus);

/**
 * @brief This function is used by the applications to inform modem about the PDA status(whether PDA is ready to
 * recieve messages from network or not).
 *
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
 * @param [in]
 *  - None
 *
 * @param [out]
 *  - None
 *
 * @par Async Response Message:
 *  None.
 *
 * @pre
 *  - None.
 *
 * @post
 *  - None.
 *
 * @return Return Type (int) \n
 * - TAPI_API_SUCCESS - indicating that the operation has completed successfully. \n
 * - Else it will return failure and error code (Refer #TapiResult_t)
 * @par Prospective Clients:
 * External Apps.
 *
 */
int tel_set_sms_device_status(void);

#ifdef __cplusplus
}
#endif

#endif	/* _ITAPI_NETTEXT_H_ */

/**
* @}
*/
