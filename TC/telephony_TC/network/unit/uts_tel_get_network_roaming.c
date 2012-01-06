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


#include <tet_api.h>
#include <ITapiNetwork.h>

#include "tel_tapi_nw_common.h"
#include "uts_tel_get_network_roaming.h"

TS_UINT subscription_id = 0, subscription_id1 = 0;

/* Initialize TCM data structures */
static void startup();
static void cleanup();
void (*tet_startup) () = startup;
void (*tet_cleanup) () = cleanup;
struct tet_testlist tet_testlist[] = {
	{utc_tel_get_network_roaming_01, 1},
	{utc_tel_get_network_roaming_02, 2},
	{NULL, 0}
};

void callback(TelTapiEvent_t *event)
{
	if (event->EventClass != TAPI_EVENT_CLASS_NETWORK)
		return;

	if (event->EventType == TAPI_EVENT_NETWORK_GET_ROAMING_MODE_CNF) {
		printf("\n$$$$$$ TAPI_EVENT_NETWORK_GET_ROAMING_MODE_CNF $$$$$$ \n");
	}

}

/* Startup & Clean function : It is not test code, only for
 initialize and finalize test module
 */
static void startup()
{
	TapiResult_t api_err = TAPI_API_SUCCESS;
	tet_infoline("utc_tel_tapi_nw_get_network_mode_func, Test Start\n");

	api_err = tel_init();
	if (api_err != TAPI_API_SUCCESS) {
		printf("tel_init Failed api_err = %d \n", api_err);
	}
	api_err = tel_register_event(TAPI_EVENT_NETWORK_GET_ROAMING_MODE_CNF, &subscription_id1, (TelAppCallback) &callback, NULL);
	if (api_err != TAPI_API_SUCCESS) {
		printf("TapiCommonRegisterEvent Failed api_err = %d \n", api_err);
	}
	printf("after TapiCommonRegisterEvent sub id is %d api_err is %d\n", subscription_id1, api_err);

	tel_register_app_name("org.samsung.test");
	return;
}

static void cleanup()
{
	tet_infoline("utc_tel_get_network_roaming, Test Finished\n");
	tel_deregister_event(subscription_id1);
	tel_deinit();
	return;
}


/*
  Unit Test Case functions
*/

/**
 * @brief This tests tel_get_network_roaming() API in normal conditions
 * @par ID:
 * utc_tel_get_network_roaming_01
 * @code

		RoamingMode = TAPI_NETWORK_MODE_EMERGENCY;
		pRequestId = -1;

* @endcode
* @param [out] pRequestId
* @return TAPI_API_SUCCESS - indicating that the operation has completed successfully.
*/
void utc_tel_get_network_roaming_01()
{
	TapiResult_t ret_val = TAPI_API_SUCCESS;

	int pRequestId;

	pRequestId = -1;

	tet_infoline("utc_tel_get_network_roaming_01 Test\n");
	/*Setting of roaming Mode*/
	ret_val = tel_get_network_roaming(&pRequestId);
	/*************************/

	TET_CHECK(TAPI_API_SUCCESS, ret_val);

	tet_infoline("utc_tel_get_network_roaming_01 is passed\n");
	tet_result(TET_PASS);

	return;
}

/**
 * @brief This tests tel_get_network_roaming() API in abnormal conditions
 * @par ID:
 * utc_tel_get_network_roaming_02
 * @code

		pRequestId = NULL;

* @endcode
* @param [out] pRequestId
* @return TAPI_API_INVALID_PTR
*/

void utc_tel_get_network_roaming_02()
{
	TapiResult_t ret_val = TAPI_API_SUCCESS;

	tet_infoline("utc_tel_get_network_roaming_02 Test\n");

	ret_val = tel_get_network_roaming(NULL);
	TET_CHECK(TAPI_API_INVALID_PTR, ret_val);

	tet_infoline("utc_tel_get_network_roaming_02 is passed\n");
	tet_result(TET_PASS);

	return;
}

/** @} */
