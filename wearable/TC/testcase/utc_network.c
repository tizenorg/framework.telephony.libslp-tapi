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
#include <ITapiNetwork.h>
#include <TapiUtility.h>

#include "util_common.h"

TapiHandle *handle;
enum async_state async_flag;

/**
 * tel_select_network_manual
 *
 */
static void on_tel_select_network_manual (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_select_network_manual", "Callback userdata crashed");
	}
}

static void utc_tel_select_network_manual (void)
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_select_network_manual (handle, "45001", TAPI_NETWORK_SYSTEM_LTE,
			on_tel_select_network_manual, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_select_network_manual", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_select_network_manual", "Callback not invoked");
	}

	dts_pass("tel_select_network_manual");
}

static void utc_fail_tel_select_network_manual (void)
{
	int ret;

	ret = tel_select_network_manual (NULL, NULL, 0, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_select_network_manual", "Parameter check failed");
	}

	ret = tel_select_network_manual (handle, NULL, 0, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_select_network_manual", "Parameter check failed");
	}

	dts_pass("tel_select_network_manual");
}

/**
 * tel_set_network_band
 *
 */
static void on_tel_set_network_band (TapiHandle *handle, int result, void *data,
		void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_network_band", "Callback userdata crashed");
	}
}

static void utc_tel_set_network_band (void)
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_network_band (handle, TAPI_NETWORK_BAND_MODE_ONLY,
			TAPI_NETWORK_BAND_TYPE_ANY, on_tel_set_network_band, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_network_band", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_network_band", "Callback not invoked");
	}

	dts_pass("tel_set_network_band");
}

static void utc_fail_tel_set_network_band (void)
{
	int ret;

	ret = tel_set_network_band (NULL, 0, 0, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_network_band", "Parameter check failed");
	}

	dts_pass("tel_set_network_band");
}

/**
 * tel_set_network_mode
 *
 */
static void on_tel_set_network_mode (TapiHandle *handle, int result, void *data,
		void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_network_mode", "Callback userdata crashed");
	}
}

static void utc_tel_set_network_mode (void)
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_network_mode (handle, TAPI_NETWORK_MODE_AUTO,
			on_tel_set_network_mode, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_network_mode", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_network_mode", "Callback not invoked");
	}

	dts_pass("tel_set_network_mode");
}

static void utc_fail_tel_set_network_mode (void)
{
	int ret;

	ret = tel_set_network_mode (NULL, 0, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_network_mode", "Parameter check failed");
	}

	dts_pass("tel_set_network_mode");
}

/**
 * tel_set_network_preferred_plmn
 *
 */
static void on_tel_set_network_preferred_plmn (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_network_preferred_plmn", "Callback userdata crashed");
	}
}

static void utc_tel_set_network_preferred_plmn (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelNetworkPreferredPlmnInfo_t info;

	memset (&info, 0, sizeof(TelNetworkPreferredPlmnInfo_t));
	info.SystemType = TAPI_NETWORK_SYSTEM_GSM;
	info.Index = 1;
	strncpy (info.Plmn, TAPI_NETWORK_PLMN_LEN_MAX, "45001");

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_network_preferred_plmn (handle, TAPI_NETWORK_PREF_PLMN_ADD,
			&info, on_tel_set_network_preferred_plmn, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_network_preferred_plmn", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_network_preferred_plmn", "Callback not invoked");
	}

	dts_pass("tel_set_network_preferred_plmn");
}

static void utc_fail_tel_set_network_preferred_plmn (void)
{
	int ret;

	ret = tel_set_network_preferred_plmn (NULL, 0, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_network_preferred_plmn", "Parameter check failed");
	}

	dts_pass("tel_set_network_preferred_plmn");
}

/**
 * tel_set_network_service_domain
 *
 */
static void on_tel_set_network_service_domain (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_network_service_domain", "Callback userdata crashed");
	}
}

static void utc_tel_set_network_service_domain (void)
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_network_service_domain (handle,
			TAPI_NETWORK_SERVICE_DOMAIN_COMBINED,
			on_tel_set_network_service_domain, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_network_service_domain", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_network_service_domain", "Callback not invoked");
	}

	dts_pass("tel_set_network_service_domain");
}

static void utc_fail_tel_set_network_service_domain (void)
{
	int ret;

	ret = tel_set_network_service_domain (NULL, 0, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_network_service_domain", "Parameter check failed");
	}

	dts_pass("tel_set_network_service_domain");
}


/**
 * Generate default TC for no-additional-parameter type API
 *
 */
DO(tel_search_network)
DO(tel_cancel_network_manual_search)
DO(tel_get_network_band)
DO(tel_get_network_mode)
DO(tel_get_network_neighboring_cell_info)
DO(tel_get_network_preferred_plmn)
DO(tel_get_network_selection_mode)
DO(tel_get_network_service_domain)
DO(tel_get_network_serving)
DO(tel_select_network_automatic)

struct tet_testlist tet_testlist[] = {
	/* generated TC */
//	{ utc_tel_search_network, 1 },
//	{ utc_fail_tel_search_network, 2 },
	{ utc_tel_cancel_network_manual_search, 1 },
	{ utc_fail_tel_cancel_network_manual_search, 2 },
	{ utc_tel_get_network_band, 1 },
	{ utc_fail_tel_get_network_band, 2 },
	{ utc_tel_get_network_mode, 1 },
	{ utc_fail_tel_get_network_mode, 2 },
	{ utc_tel_get_network_neighboring_cell_info, 1 },
	{ utc_fail_tel_get_network_neighboring_cell_info, 2 },
	{ utc_tel_get_network_preferred_plmn, 1 },
	{ utc_fail_tel_get_network_preferred_plmn, 2 },
	{ utc_tel_get_network_selection_mode, 1 },
	{ utc_fail_tel_get_network_selection_mode, 2 },
	{ utc_tel_get_network_service_domain, 1 },
	{ utc_fail_tel_get_network_service_domain, 2 },
	{ utc_tel_get_network_serving, 1 },
	{ utc_fail_tel_get_network_serving, 2 },
	{ utc_tel_select_network_automatic, 1 },
	{ utc_fail_tel_select_network_automatic, 2 },

	/* custom TC */
	{ utc_tel_select_network_manual, 1 },
	{ utc_fail_tel_select_network_manual, 2 },
	{ utc_tel_set_network_band, 1 },
	{ utc_fail_tel_set_network_band, 2 },
	{ utc_tel_set_network_mode, 1 },
	{ utc_fail_tel_set_network_mode, 2 },
	{ utc_tel_set_network_preferred_plmn, 1 },
	{ utc_fail_tel_set_network_preferred_plmn, 2 },
	{ utc_tel_set_network_service_domain, 1 },
	{ utc_fail_tel_set_network_service_domain, 2 },
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
