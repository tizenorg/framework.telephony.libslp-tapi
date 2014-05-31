/*
 * libslp-tapi
 *
 * Copyright (c) 2013 Samsung Electronics Co., Ltd. All rights reserved.
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

#include <tet_api.h>
#include <stdlib.h>

#include <tapi_common.h>
#include <TapiUtility.h>

#include "util_common.h"

TapiHandle *handle;
enum async_state async_flag;


/**
 * tel_get_cp_name_list
 *
 */
static void utc_tel_get_cp_name_list (void)
{
	char **result;

	result = tel_get_cp_name_list ();
	if (result == NULL) {
		dts_fail("tel_get_cp_name_list");
		return;
	}

	dts_pass("tel_get_cp_name_list");
}

/**
 * tel_init / tel_deinit
 *
 */
static void utc_tel_init_deinit (void)
{
	TapiHandle *h;
	int ret;

	h = tel_init (NULL);
	if (h == NULL) {
		dts_fail("tel_init", "Fail to initialization");
		return;
	}

	ret = tel_deinit (h);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_deinit", "Fail to deinitialization");
		return;
	}

	h = tel_init ("invalid_name");
	if (h == NULL) {
		dts_fail("tel_init", "Fail to initialization (invalid name should success)");
		return;
	}

	ret = tel_deinit (h);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_deinit", "Fail to deinitialization");
		return;
	}

	dts_pass("tel_init");
}


static void utc_fail_tel_init_deinit (void)
{
	int ret;

	ret = tel_deinit (NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_deinit", "Fail to parameter check");
		return;
	}

	dts_pass("tel_deinit");
}

/**
 * tel_register_noti_event / tel_deregister_noti_event
 *
 */
static void on_noti (TapiHandle *h, const char *noti_id, void *data, void *user_data)
{
}

static void utc_tel_register_noti_event (void)
{
	int ret;

	ret = tel_register_noti_event (handle, TAPI_NOTI_NETWORK_REGISTRATION_STATUS, on_noti, NULL);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_register_noti_event");
		return;
	}

	ret = tel_deregister_noti_event (handle, TAPI_NOTI_NETWORK_REGISTRATION_STATUS);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_deregister_noti_event");
		return;
	}

	dts_pass("tel_register_noti_event");
}

static void utc_fail_tel_register_noti_event (void)
{
	int ret;

	ret = tel_register_noti_event (handle, TAPI_NOTI_NETWORK_REGISTRATION_STATUS, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_register_noti_event");
		return;
	}

	ret = tel_register_noti_event (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_register_noti_event");
		return;
	}

	ret = tel_register_noti_event (NULL, TAPI_NOTI_NETWORK_REGISTRATION_STATUS, on_noti, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_register_noti_event");
		return;
	}

	/* deregister the unregistered event */
	ret = tel_deregister_noti_event (handle, TAPI_NOTI_NETWORK_CHANGE);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_deregister_noti_event");
		return;
	}

	dts_pass("tel_register_noti_event");
}


/**
 * tel_get_property_int
 *
 */
static void utc_tel_get_property_int (void)
{
	int ret;
	int act = 0;

	ret = tel_get_property_int (handle, TAPI_PROP_NETWORK_ACT, &act);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_get_property_int");
		return;
	}

	dts_pass("tel_get_property_int");
}

static void utc_fail_tel_get_property_int (void)
{
	int ret;
	int act = 0;

	ret = tel_get_property_int (handle, TAPI_PROP_NETWORK_ACT, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_property_int");
		return;
	}

	ret = tel_get_property_int (handle, NULL, &act);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_property_int");
		return;
	}


	ret = tel_get_property_int (NULL, TAPI_PROP_NETWORK_ACT, &act);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_property_int");
		return;
	}

	dts_pass("tel_get_property_int");
}


/**
 * tel_get_property_string
 *
 */
static void utc_tel_get_property_string (void)
{
	int ret;
	char *plmn = NULL;

	ret = tel_get_property_string (handle, TAPI_PROP_NETWORK_PLMN, &plmn);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_get_property_string");
		return;
	}

	if (plmn)
		free (plmn);

	dts_pass("tel_get_property_string");
}

static void utc_fail_tel_get_property_string (void)
{
	int ret;
	char *plmn = NULL;

	ret = tel_get_property_string (handle, TAPI_PROP_NETWORK_PLMN, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_property_string");
		return;
	}

	ret = tel_get_property_string (handle, NULL, &plmn);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_property_string");
		return;
	}

	ret = tel_get_property_string (NULL, TAPI_PROP_NETWORK_PLMN, &plmn);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_property_string");
		return;
	}

	dts_pass("tel_get_property_string");
}


struct tet_testlist tet_testlist[] = {
	{ utc_tel_get_cp_name_list, 1 },
	{ utc_tel_init_deinit, 1 },
	{ utc_fail_tel_init_deinit, 2 },
	{ utc_tel_register_noti_event, 1 },
	{ utc_fail_tel_register_noti_event, 2 },
	{ utc_tel_get_property_int, 1 },
	{ utc_fail_tel_get_property_int, 2 },
	{ utc_tel_get_property_string, 1 },
	{ utc_fail_tel_get_property_string, 2 },
	{ NULL, 0 },
};

static void startup (void)
{
	/* start of TC */
	tet_printf ("\n TC start");

	handle = tel_init (NULL);
}

static void cleanup (void)
{
	tel_deinit (handle);

	/* end of TC */
	tet_printf ("\n TC end");
}

void (*tet_startup) (void) = startup;
void (*tet_cleanup) (void) = cleanup;
