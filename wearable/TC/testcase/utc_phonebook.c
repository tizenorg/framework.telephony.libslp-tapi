/*
 * libslp-tapi
 *
 * Copyright (c) 2013 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Anga Santhosh Kumar <santhosh.a@samsung.com>
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
#include <ITapiPhonebook.h>
#include <TapiUtility.h>

#include "util_common.h"

TapiHandle *handle;
enum async_state async_flag;

/**
 * tel_get_sim_pb_init_info
 *
 */
static void utc_tel_get_sim_pb_init_info(void)
{
	int ret;
	int init_completed = 0;
	TelSimPbList_t pb_list;

	memset(&pb_list, 0, sizeof(TelSimPbList_t));

	util_init_loop();

	ret = tel_get_sim_pb_init_info(handle, &init_completed, &pb_list);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_pb_init_info", "Unexpected return");
	}

	dts_pass("tel_get_sim_pb_init_info");
}

static void utc_fail_tel_get_sim_pb_init_info(void)
{
	int ret;
	int init_completed = 0;

	ret = tel_get_sim_pb_init_info(NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_pb_init_info", "Parameter check failed");
	}

	ret = tel_get_sim_pb_init_info(handle, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_pb_init_info", "Parameter check failed");
	}

	ret = tel_get_sim_pb_init_info(handle, &init_completed, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_pb_init_info", "Parameter check failed");
	}

	dts_pass("tel_get_sim_pb_init_info");
}

/**
 * tel_get_sim_pb_count
 *
 */
static void on_tel_get_sim_pb_count (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_get_sim_pb_count", "Callback userdata crashed");
	}
}

static void utc_tel_get_sim_pb_count (void)
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_get_sim_pb_count (handle, TAPI_SIM_PB_FDN,
			on_tel_get_sim_pb_count, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_pb_count", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_get_sim_pb_count", "Callback not invoked");
	}

	dts_pass("tel_get_sim_pb_count");
}

static void utc_fail_tel_get_sim_pb_count (void)
{
	int ret;

	ret = tel_get_sim_pb_count (NULL, TAPI_SIM_PB_FDN, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_pb_count", "Parameter check failed");
	}

	ret = tel_get_sim_pb_count (handle, TAPI_SIM_PB_FDN, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_pb_count", "Parameter check failed");
	}

	ret = tel_get_sim_pb_count (handle, TAPI_SIM_PB_UNKNOWNN, on_tel_get_sim_pb_count, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_pb_count", "Parameter check failed");
	}

	dts_pass("tel_get_sim_pb_count");
}

/**
 * tel_get_sim_pb_meta_info
 *
 */
static void on_tel_get_sim_pb_meta_info (TapiHandle *handle, int result, void *data,
		void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_get_sim_pb_meta_info", "Callback userdata crashed");
	}
}

static void utc_tel_get_sim_pb_meta_info (void)
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_get_sim_pb_meta_info (handle, TAPI_SIM_PB_FDN,
			on_tel_get_sim_pb_meta_info, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_pb_meta_info", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_get_sim_pb_meta_info", "Callback not invoked");
	}

	dts_pass("tel_get_sim_pb_meta_info");
}

static void utc_fail_tel_get_sim_pb_meta_info (void)
{
	int ret;

	ret = tel_get_sim_pb_meta_info (NULL, TAPI_SIM_PB_FDN, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_pb_meta_info", "Parameter check failed");
	}

	ret = tel_get_sim_pb_meta_info (handle, TAPI_SIM_PB_FDN, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_pb_meta_info", "Parameter check failed");
	}

	ret = tel_get_sim_pb_meta_info (handle, TAPI_SIM_PB_UNKNOWNN, on_tel_get_sim_pb_meta_info, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_pb_meta_info", "Parameter check failed");
	}

	dts_pass("tel_get_sim_pb_meta_info");
}

/**
 * tel_read_sim_pb_record
 *
 */
static void on_tel_read_sim_pb_record (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_read_sim_pb_record", "Callback userdata crashed");
	}
}

static void utc_tel_read_sim_pb_record (void)
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_read_sim_pb_record (handle, TAPI_SIM_PB_ADN,
			1, on_tel_read_sim_pb_record, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_read_sim_pb_record", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_read_sim_pb_record", "Callback not invoked");
	}

	dts_pass("tel_read_sim_pb_record");
}

static void utc_fail_tel_read_sim_pb_record (void)
{
	int ret;

	ret = tel_read_sim_pb_record (NULL, TAPI_SIM_PB_ADN, 1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_read_sim_pb_record", "Parameter check failed");
	}

	ret = tel_read_sim_pb_record (handle, TAPI_SIM_PB_ADN, 1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_read_sim_pb_record", "Parameter check failed");
	}

	ret = tel_read_sim_pb_record (handle, TAPI_SIM_PB_ADN, 0, on_tel_read_sim_pb_record, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_read_sim_pb_record", "Parameter check failed");
	}

	ret = tel_read_sim_pb_record (handle, TAPI_SIM_PB_UNKNOWNN, 1, on_tel_read_sim_pb_record, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_read_sim_pb_record", "Parameter check failed");
	}

	dts_pass("tel_read_sim_pb_record");
}

/**
 * tel_update_sim_pb_record
 *
 */
static void on_tel_update_sim_pb_record (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_update_sim_pb_record", "Callback userdata crashed");
	}
}

static void utc_tel_update_sim_pb_record (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSimPbRecord_t req_data;

	memset(&req_data, 0, sizeof(TelSimPbRecord_t));
	req_data.phonebook_type = TAPI_SIM_PB_ADN;
	req_data.index = 1;
	strncpy(req_data.name, 6, "aaaaa");
	req_data.dcs = TAPI_SIM_TEXT_ENC_ASCII;
	strncpy(req_data.number, 11, "8884266646");
	req_data.ton = TAPI_SIM_TON_NATIONAL;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_update_sim_pb_record (handle, &req_data,
		on_tel_update_sim_pb_record, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_update_sim_pb_record", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_update_sim_pb_record", "Callback not invoked");
	}

	dts_pass("tel_update_sim_pb_record");
}

static void utc_fail_tel_update_sim_pb_record (void)
{
	int ret;
	TelSimPbRecord_t req_data;

	memset(&req_data, 0, sizeof(TelSimPbRecord_t));

	ret = tel_update_sim_pb_record (NULL, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_update_sim_pb_record", "Parameter check failed");
	}

	ret = tel_update_sim_pb_record (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_update_sim_pb_record", "Parameter check failed");
	}

	req_data.index = 0;
	ret = tel_update_sim_pb_record (handle, &req_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_update_sim_pb_record", "Parameter check failed");
	}

	req_data.index = 1;
	req_data.phonebook_type = TAPI_SIM_PB_UNKNOWNN;
	ret = tel_update_sim_pb_record (handle, &req_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_update_sim_pb_record", "Parameter check failed");
	}

	dts_pass("tel_update_sim_pb_record");
}

/**
 * tel_delete_sim_pb_record
 *
 */
static void on_tel_delete_sim_pb_record (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_delete_sim_pb_record", "Callback userdata crashed");
	}
}

static void utc_tel_delete_sim_pb_record (void)
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_delete_sim_pb_record (handle, TAPI_SIM_PB_ADN,
			1, on_tel_delete_sim_pb_record, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_delete_sim_pb_record", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_delete_sim_pb_record", "Callback not invoked");
	}

	dts_pass("tel_delete_sim_pb_record");
}

static void utc_fail_tel_delete_sim_pb_record (void)
{
	int ret;

	ret = tel_delete_sim_pb_record (NULL, TAPI_SIM_PB_ADN, 1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_delete_sim_pb_record", "Parameter check failed");
	}

	ret = tel_delete_sim_pb_record (handle, TAPI_SIM_PB_ADN, 0, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_delete_sim_pb_record", "Parameter check failed");
	}

	ret = tel_delete_sim_pb_record (handle, TAPI_SIM_PB_UNKNOWNN, 1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_delete_sim_pb_record", "Parameter check failed");
	}

	dts_pass("tel_delete_sim_pb_record");
}



/**
 * Generate default TC for no-additional-parameter type API
 *
 */
DO(tel_get_sim_pb_usim_meta_info)

struct tet_testlist tet_testlist[] = {
	/* generated TC */
	{ utc_tel_get_sim_pb_usim_meta_info, 1 },
	{ utc_fail_tel_get_sim_pb_usim_meta_info, 2 },

	/* custom TC */
	{ utc_tel_get_sim_pb_init_info, 1 },
	{ utc_fail_tel_get_sim_pb_init_info, 2 },
	{ utc_tel_get_sim_pb_count, 1 },
	{ utc_fail_tel_get_sim_pb_count, 2 },
	{ utc_tel_get_sim_pb_meta_info, 1 },
	{ utc_fail_tel_get_sim_pb_meta_info, 2 },
	{ utc_tel_read_sim_pb_record, 1 },
	{ utc_fail_tel_read_sim_pb_record, 2 },
	{ utc_tel_update_sim_pb_record, 1 },
	{ utc_fail_tel_update_sim_pb_record, 2 },
	{ utc_tel_delete_sim_pb_record, 1 },
	{ utc_fail_tel_delete_sim_pb_record, 2 },
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
