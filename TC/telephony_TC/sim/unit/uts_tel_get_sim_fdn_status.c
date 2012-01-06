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


/**
* @ingroup TELEPHONY_API
* @addtogroup TAPI_API_SIM_SAT SIM/SAT
*/

/**
* @ingroup  TAPI_API_SIM_SAT
* @addtogroup UTS_SIM_SAT Unit
*/

/**
* @ingroup  UTS_SIM_SAT
* @addtogroup UTS_TAPI_SIM_GET_FDN_STATUS tel_get_sim_fdn_status
*
* @brief Unit test code for tel_get_sim_fdn_status()
* @par Test function Prototype:
* 	TapiResult_t tel_get_sim_fdn_status(BOOL *pFdnStatus);
* @par Test function description:
* 	This function is a synchronous API gets the current FDN status.
* @par Important Notes:
* 	None
* @param [out] pFdnStatus
*   This parameter returns the current fdn status whether enabled or disabled.
* @par Async Response Message:
* 	None
* @pre
*	None
* @post
*	None
* @return
* Return Type : (TapiResult_t)
* - TAPI_API_SUCCESS - indicating that the operation has completed successfully.
* - Otherwise it provides an error code (Refer #TapiResult_t)
* @{
*/

/**
* @file		uts_tel_get_sim_fdn_status.c
* @brief	Test for the tel_get_sim_fdn_status() API that is used to get fdn status
* @author	
* @version	Initial Creation V0.1
* @date		2008.07.30
*/

#include <tet_api.h>
#include <ITapiSim.h>
#include <TapiCommon.h>

#include "tet_tapi_util.h"
#include "uts_tel_get_sim_fdn_status.h"
#include "sim_common.h"

/* Initialize TCM data structures */
static void startup();
static void cleanup();
void (*tet_startup) () = startup;
void (*tet_cleanup) () = cleanup;
struct tet_testlist tet_testlist[] = {
	{utc_tel_get_sim_fdn_status_01, 1},
	{utc_tel_get_sim_fdn_status_02, 2},
	{NULL, 0}
};

/* Startup & Clean function : It is not test code, only for
   initialize and finalize test module
*/
static void startup()
{
	tet_infoline("utc_tel_get_sim_fdn_status Test Start\n");
	if (tel_init() != TAPI_API_SUCCESS)
	{
		tet_infoline("startup fail. tel_init() failed");
	}
	return;
}


static void cleanup()
{
	tet_infoline("utc_tel_get_sim_fdn_status Test Finished\n");
	if (tel_deinit() != TAPI_API_SUCCESS)
	{
		tet_infoline("startup fail. tel_deinit() failed");
	}
	return;
}



/*
  Unit Test Case functions
*/

/**
* @brief tel_get_sim_fdn_status() API : Positive condition(Get FDN Status)
* @par ID: UTC_TEL_GET_SIM_FDN_STATUS_01
* @param [out] &fdn_status
* @return TAPI_API_SUCCESS
*/
void utc_tel_get_sim_fdn_status_01()
{
    BOOL fdn_status = 0;

    TET_STAMP_START("all valid input parameter test");
    TET_CHECK(TAPI_API_SUCCESS, tel_get_sim_fdn_status(&fdn_status));
    tet_printf(" FDN status is %d", fdn_status);
    TET_STAMP_PASS();
    return;
}

/**
* @brief tel_get_sim_fdn_status() API : Negative condition(Parameter is Null)
* @par ID: UTC_TEL_GET_SIM_FDN_STATUS_02
* @param [out] &fdn_status = NULL
* @return TAPI_API_SUCCESS
*/
void utc_tel_get_sim_fdn_status_02()
{
    TET_STAMP_START("NULL parameter test");

    TET_CHECK(TAPI_API_INVALID_PTR, tel_get_sim_fdn_status(NULL));
    TET_STAMP_PASS();
    return;
}

/** @} */
