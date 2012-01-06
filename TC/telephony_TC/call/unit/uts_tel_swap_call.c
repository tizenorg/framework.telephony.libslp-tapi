/*
 * libslp-tapi
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Kyeongchul Kim <kyeongchul.kim@samsung.com>
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



#include "uts_tel_swap_call.h"
#include "ITapiSs.h"


/* Initialize TCM data structures */


/*
*  TapiResult_t tel_swap_call( unsigned int active_call, unsigned int held_call  ,int *pRequestId);
*/

void (*tet_startup) () = startup;
void (*tet_cleanup) () = cleanup;

extern int expected_event;

static void startup()
{
	TapiResult_t  ret_status ;
	tapi_dbus_connection_name dname;
	int bStatus;

	ret_status = tel_init();

	if(ret_status != TAPI_API_SUCCESS)
	{
		printf("tel_init() Failed ret_status = %d \n",ret_status);
	}

	register_all_events();
	tel_register_app_name("org.samsung.test");
	if(tel_get_app_name(&dname))
		printf("Dbus Get app name error\n");
	else 
		printf("Dbus Name is %s\n",dname.name);
		
	tel_check_service_ready(&bStatus);
	printf("Telephpny service  %d\n",bStatus);

	TelSsWaitingInfo_t waitInfo;

	int request_id=0;
	waitInfo.CallType = TAPI_CALL_TYPE_VOICE_EV;
	waitInfo.Mode =(TelSsCallWaitOperationMode_t)TAPI_SS_CW_ACTIVATE;

	ret_status = tel_set_ss_waiting(&waitInfo, &request_id);
	expected_event = TAPI_EVENT_SS_WAITING_CNF;
	printf("call waiting\n");
	gmain_loop_for_tapi_events(TIME_DELAY1);


	g_CallHandle = -1;
}

static void cleanup()
{
	int  RequestId = -1;

	tel_release_call_all(&RequestId);
	expected_event = TAPI_EVENT_CALL_END_IND;
	gmain_loop_for_tapi_events(TIME_DELAY1);

	deregister_all();

	tel_deinit();

}


/**
 * @brief This tests tel_swap_call() API in normal conditions
 * @par ID:
 * UTC_TEL_SWAP_CALL_01
 * @param [in] active_call = callhandle[1]
 * @param [in] held_call = callhandle[0]
 * @param [out] pRequestId = &RequestId
* @return TAPI_API_SUCCESS
*/
// Sunghyuk Lee
void utc_tel_swap_call_01()
{
	CALL_TEST_DEBUG("\n################     TEST START    ################\n");
	TapiResult_t  ret_status ;
	unsigned int call_handle_01 = -1;
	unsigned int call_handle_02 = -1;
	TelCallSetupParams_t setup_call_info_01;
	TelCallSetupParams_t setup_call_info_02;
	int  RequestId = -1;
	char normal1[16] = MOB_NUM1;
	char normal2[16] = MOB_NUM2;

	memset(&setup_call_info_01, 0, sizeof(TelCallSetupParams_t));
	setup_call_info_01.CallType = TAPI_CALL_TYPE_VOICE;
	strncpy(setup_call_info_01.szNumber, normal1, 13);
	tet_printf("called number = %s\n", setup_call_info_01.szNumber);

	//setup_call_info_01.IdentityMode = TAPI_CALL_IDENTITY_SHOW;	//preet: TelCallSetupParams_t donot have these memebers
	//setup_call_info_01.pCugInfo = NULL;
	//setup_call_info_01.pUusInfo = NULL;

	memset(&setup_call_info_02, 0, sizeof(TelCallSetupParams_t));
	setup_call_info_02.CallType = TAPI_CALL_TYPE_VOICE;
	strncpy(setup_call_info_02.szNumber, normal2, 13);
	tet_printf("called number = %s\n", setup_call_info_02.szNumber);

	//setup_call_info_02.IdentityMode = TAPI_CALL_IDENTITY_SHOW; 	//preet: TelCallSetupParams_t donot have these memebers
       	//setup_call_info_02.pCugInfo = NULL;
	//setup_call_info_02.pUusInfo = NULL;


	CALL_TEST_DEBUG("MAKE A 1ST MO CALL TO %s\n",setup_call_info_01.szNumber);
	ret_status =  tel_exe_call_mo(&setup_call_info_01, &call_handle_01, &RequestId);
	TET_CHECK(TAPI_API_SUCCESS, ret_status);
	expected_event = TAPI_EVENT_CALL_CONNECTED_IND;
	gmain_loop_for_tapi_events(TIME_DELAY2);

	CALL_TEST_DEBUG("HOLD THE ACTIVE CALL\n");
	ret_status = tel_hold_call (call_handle_01 , &RequestId);
	TET_CHECK(TAPI_API_SUCCESS, ret_status);
//	expected_event = TAPI_EVENT_CALL_HOLD_CNF;
	gmain_loop_for_tapi_events(TIME_DELAY2);

	CALL_TEST_DEBUG("MAKE 2ND MO CALL TO %s\n",setup_call_info_02.szNumber);
	ret_status =  tel_exe_call_mo(&setup_call_info_02, &call_handle_02, &RequestId);
	TET_CHECK(TAPI_API_SUCCESS, ret_status);
	expected_event = TAPI_EVENT_CALL_CONNECTED_IND;
	gmain_loop_for_tapi_events(TIME_DELAY2);

	CALL_TEST_DEBUG("SWAP TWO CALLS\n");
	ret_status = tel_swap_call (call_handle_02, call_handle_01, &RequestId);
	TET_CHECK(TAPI_API_SUCCESS, ret_status);
	expected_event = TAPI_EVENT_CALL_SWAP_CNF;
	gmain_loop_for_tapi_events(TIME_DELAY2);

	CALL_TEST_DEBUG("RELEASE ALL CALLS\n");
	tel_release_call_all(&RequestId);
	expected_event = TAPI_EVENT_CALL_END_IND;
	gmain_loop_for_tapi_events(TIME_DELAY2);

	tet_result(TET_PASS);

	return;

}


/**
 * @brief This tests tel_swap_call() API in abnormal conditions
 * @par ID:
 * UTC_TEL_SWAP_CALL_02
 * @param [in] active_call = INVALID_CALL_HANDLE
 * @param [in] held_call = VALID_CALL_HANDLE
 * @param [out] pRequestId = &RequestId
* @return TAPI_API_INVALID_CALL_HANDLE
*/

void utc_tel_swap_call_02()
{
	CALL_TEST_DEBUG("\n########     TEST START    ###########\n");
	TapiResult_t  ret_status ;
	int  RequestId = -1;
	unsigned int call_handle = VALID_CALL_HANDLE;

	ret_status = tel_swap_call (INVALID_CALL_HANDLE, call_handle, &RequestId);

	TET_CHECK(TAPI_API_INVALID_CALL_HANDLE, ret_status);
	printf("utc_tel_swap_call_02 pass\n");
	tet_result(TET_PASS);

	return;
}

/**
 * @brief This tests tel_swap_call() API in abnormal conditions
 * @par ID:
 * UTC_TEL_SWAP_CALL_03
 * @param [in] active_call = VALID_CALL_HANDLE
 * @param [in] held_call = INVALID_CALL_HANDLE
 * @param [out] pRequestId = &RequestIdd
* @return TAPI_API_INVALID_CALL_HANDLE
*/

void utc_tel_swap_call_03()
{
	CALL_TEST_DEBUG("\n########     TEST START    ###########\n");
	TapiResult_t  ret_status ;
	int  RequestId = -1;
	unsigned int call_handle = VALID_CALL_HANDLE;

	ret_status = tel_swap_call (call_handle, INVALID_CALL_HANDLE, &RequestId);

	TET_CHECK(TAPI_API_INVALID_CALL_HANDLE, ret_status);
	printf("utc_tel_swap_call_03 pass\n");
	tet_result(TET_PASS);

	return;
}


/**
 * @brief This tests tel_swap_call() API in abnormal conditions
 * @par ID:
 * UTC_TEL_SWAP_CALL_04
 * @param [in] active_call = VALID_CALL_HANDLE
 * @param [in] held_call = VALID_CALL_HANDLE
 * @param [out] pRequestId = NULL
* @return TAPI_API_INVALID_PTR
*/

void utc_tel_swap_call_04()
{
	CALL_TEST_DEBUG("\n########     TEST START    ###########\n");
	TapiResult_t  ret_status ;
	unsigned int call_handle = VALID_CALL_HANDLE;

	ret_status = tel_swap_call (call_handle, call_handle, NULL);

	TET_CHECK(TAPI_API_INVALID_PTR, ret_status);
	printf("utc_tel_swap_call_04 pass\n");
	tet_result(TET_PASS);

	return;
}

