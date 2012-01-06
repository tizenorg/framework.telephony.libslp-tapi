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

#include <ITapiCall.h>
#include <ITapiSs.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>

#include <pthread.h>
#include "assert.h"
#include "glib.h"

#include "TapiCommon.h"
#include <tet_api.h>
#include "uts_tel_set_ss_aoc_info.h"
#include "tet_tapi_util.h"

/* Initialize TCM data structures */
static void startup();
static void cleanup();
void (*tet_startup) () = startup;
void (*tet_cleanup) () = cleanup;
struct tet_testlist tet_testlist[] = {
	{utc_tel_set_ss_aoc_info_01, 1},
	{utc_tel_set_ss_aoc_info_02, 2},
	{utc_tel_set_ss_aoc_info_03, 3},
	{utc_tel_set_ss_aoc_info_04, 4},
	{utc_tel_set_ss_aoc_info_05, 5},
	{NULL, 0}
};

/* Startup & Clean function : It is not test code, only for
   initialize and finalize test module
*/
static BOOL gStartupSuccess = FALSE;
static unsigned int subscription_id = 0;

static void startup()
{
	tapi_dbus_connection_name dname;
	int bStatus;
	
	gStartupSuccess = FALSE;
	if(tel_init() == TAPI_API_SUCCESS)
	{
		if(tel_register_event(TAPI_EVENT_SS_SET_AOC_CNF, &subscription_id, (TelAppCallback)ss_utc_callback,NULL) == TAPI_API_SUCCESS)
		{
			gStartupSuccess = TRUE;

			tel_register_app_name("org.samsung.test");
			if(tel_get_app_name(&dname))
				printf("Dbus Get app name error\n");
			else 
				printf("Dbus Name is %s\n",dname.name);
				
			tel_check_service_ready(&bStatus);
			printf("Telephony service  %d\n",bStatus);

		}
		else
			tet_infoline("startup fail. tel_register_event()");
	}else {
		tet_infoline("startup fail. tel_init() failed");
	}

	return;
}

static void cleanup()
{
	if(gStartupSuccess == TRUE)
		tel_deregister_event(subscription_id);
	tel_deinit();
	return;
}

/**
 * @brief This tests TelTapiReadAocInfoRequest() API in normal conditions
 * @par ID:
 * UTC_TAPI_SET_AOC_INFO_REQUEST_001
 * @param [in] aoc_type  TAPI_SS_AOC_TYPE_CCM
 * @param [out] RequestId
* @return TAPI_API_SUCCESS
*/

void utc_tel_set_ss_aoc_info_01()
{
	TET_STAMP_START("Positive Test");

	TapiResult_t ret_status = TAPI_API_SUCCESS;
	int request_id;
	TelCallAocInfo_t aocInfo;

	aocInfo.AocType=TAPI_SS_AOC_TYPE_MAXACM;
	aocInfo.MaxAcm=10;

	ret_status = tel_set_ss_aoc_info(&aocInfo,&request_id);

	TET_RESULT_IF_NOT_EQUAL_THEN_GOTO(TET_FAIL, exit, TAPI_API_SUCCESS, ret_status );
	G_MAIN_LOOP_RUN(5);

	tet_result(TET_PASS);
exit:
	return;
}


/**
 * @brief Lower boundary testing of the AoC type for TelTapiReadAocInfoRequest() API
 * @par ID:
 * UTC_TAPI_SET_AOC_INFO_REQUEST_002
 * @param [in] aoc_type  -1
 * @param [out] RequestId
* @return TAPI_API_INVALID_INPUT
*/
void utc_tel_set_ss_aoc_info_02()
{

	TET_STAMP_START("InvalidAocType -1");

        TapiResult_t ret_status = TAPI_API_SUCCESS;
        int request_id;
        TelCallAocInfo_t aocInfo;

	aocInfo.AocType=(TelSsAocType_t)-1;
        aocInfo.MaxAcm=10;

	ret_status = tel_set_ss_aoc_info(&aocInfo,&request_id);

	TET_RESULT_IF_NOT_EQUAL_THEN_GOTO(TET_PASS, exit, TAPI_API_INVALID_INPUT, ret_status );
        G_MAIN_LOOP_RUN(5);

        tet_result(TET_PASS);
exit:
         return;
}

void utc_tel_set_ss_aoc_info_03()
{
	TET_STAMP_START("Invalid AocType +1");
	TapiResult_t ret_status=TAPI_API_SUCCESS;
	int request_id;
	TelCallAocInfo_t aocInfo;
	aocInfo.AocType=(TelSsAocType_t)( TAPI_SS_AOC_TYPE_PUC+1);
	aocInfo.MaxAcm=10;
	ret_status = tel_set_ss_aoc_info(&aocInfo,&request_id);

	TET_RESULT_IF_NOT_EQUAL_THEN_GOTO(TET_PASS,exit,TAPI_API_INVALID_INPUT,ret_status);
	G_MAIN_LOOP_RUN(50);

	tet_result(TET_PASS);

exit:
	return;
}

void utc_tel_set_ss_aoc_info_04()
{
       TET_STAMP_START("NULL RequestId");
       TapiResult_t ret_status=TAPI_API_SUCCESS;
       TelCallAocInfo_t aocInfo;
       aocInfo.AocType=TAPI_SS_AOC_TYPE_MAXACM;
       aocInfo.MaxAcm=10;
       ret_status = tel_set_ss_aoc_info(&aocInfo,NULL);

       TET_RESULT_IF_NOT_EQUAL_THEN_GOTO(TET_PASS,exit,TAPI_API_INVALID_INPUT,ret_status);
       G_MAIN_LOOP_RUN(50);
       tet_result(TET_PASS);
exit:
       return;
}


void utc_tel_set_ss_aoc_info_05()
{
      TET_STAMP_START("NULL AocInfo");
      TapiResult_t ret_status=TAPI_API_SUCCESS;
      int request_id;
      ret_status = tel_set_ss_aoc_info(NULL,&request_id);

      TET_RESULT_IF_NOT_EQUAL_THEN_GOTO(TET_PASS,exit,TAPI_API_INVALID_INPUT,ret_status);
      G_MAIN_LOOP_RUN(50);
      tet_result(TET_PASS);
exit:
      return;
}

