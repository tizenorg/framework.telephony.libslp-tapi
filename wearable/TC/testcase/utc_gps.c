/*
 * libslp-tapi
 *
 * Copyright (c) 2013 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Ankit Jogi <ankit.jogi@samsung.com>
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
#include <ITapiGps.h>
#include <TapiUtility.h>

#include "util_common.h"

TapiHandle *handle;
enum async_state async_flag;

/**
 * tel_set_gps_frequency_aiding
 *
 */
static void on_tel_set_gps_frequency_aiding (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_gps_frequency_aiding", "Callback userdata crashed");
	}
}

static void utc_tel_set_gps_frequency_aiding (void)
{
	int ret;
	int value = 0xC0FFEE;
	unsigned char state = 'a';

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_gps_frequency_aiding (handle, state, on_tel_set_gps_frequency_aiding, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_gps_frequency_aiding", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_gps_frequency_aiding", "Callback not invoked");
	}

	dts_pass("tel_set_gps_frequency_aiding");
}

static void utc_fail_tel_set_gps_frequency_aiding (void)
{
	int ret;
	unsigned char state = 'a';

	ret = tel_set_gps_frequency_aiding (NULL, state, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_gps_frequency_aiding", "Parameter check failed");
	}

	dts_pass("tel_set_gps_frequency_aiding");
}

/**
 * tel_confirm_gps_measure_pos
 *
 */
static void utc_tel_confirm_gps_measure_pos (void)
{
	int ret;

	util_init_loop ();

	ret = tel_confirm_gps_measure_pos (handle, (unsigned char *)"abc1234", 7);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_confirm_gps_measure_pos", "Unexpected return");
	}

	dts_pass("tel_confirm_gps_measure_pos");
}

static void utc_fail_tel_confirm_gps_measure_pos (void)
{
	int ret;

	ret = tel_confirm_gps_measure_pos (NULL, (unsigned char *)"abc1234", 7);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_confirm_gps_measure_pos", "Parameter check failed");
	}

	ret = tel_confirm_gps_measure_pos (handle, NULL, 7);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_confirm_gps_measure_pos", "Parameter check failed");
	}

	dts_pass("tel_confirm_gps_measure_pos");
}

/**
 * tel_sync_smart_assistant_area_list
 *
 */
static void on_tel_sync_smart_assistant_area_list (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_sync_smart_assistant_area_list", "Callback userdata crashed");
	}
}

static void utc_tel_sync_smart_assistant_area_list (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSmartAssistantAreaList_t area_list;

	memset (&area_list, 0, sizeof(TelSmartAssistantAreaList_t));

	area_list.count = 1;
	area_list.area->index = 1;
	area_list.area->mode_state = TAPI_SMART_ASSISTANT_MODE_STATE_START;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_sync_smart_assistant_area_list (handle, &area_list, on_tel_sync_smart_assistant_area_list, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_sync_smart_assistant_area_list", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_sync_smart_assistant_area_list", "Callback not invoked");
	}

	dts_pass("tel_sync_smart_assistant_area_list");
}

static void utc_fail_tel_sync_smart_assistant_area_list (void)
{
	int ret;
	TelSmartAssistantAreaList_t area_list;

	memset (&area_list, 0, sizeof(TelSmartAssistantAreaList_t));

	area_list.count = 1;
	area_list.area->index = 1;
	area_list.area->mode_state = TAPI_SMART_ASSISTANT_MODE_STATE_START;

	ret = tel_sync_smart_assistant_area_list (NULL, &area_list, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_sync_smart_assistant_area_list", "Parameter check failed");
	}

	ret = tel_sync_smart_assistant_area_list (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_sync_smart_assistant_area_list", "Parameter check failed");
	}

	dts_pass("tel_sync_smart_assistant_area_list");
}

/**
 * tel_del_smart_assistant_area_list
 *
 */
static void on_tel_del_smart_assistant_area_list (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_del_smart_assistant_area_list", "Callback userdata crashed");
	}
}

static void utc_tel_del_smart_assistant_area_list (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSmartAssistantAreaList_t area_list;

	memset (&area_list, 0, sizeof(TelSmartAssistantAreaList_t));

	area_list.count = 1;
	area_list.area->index = 1;
	area_list.area->mode_state = TAPI_SMART_ASSISTANT_MODE_STATE_STOP;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_del_smart_assistant_area_list (handle, &area_list, on_tel_del_smart_assistant_area_list, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_del_smart_assistant_area_list", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_del_smart_assistant_area_list", "Callback not invoked");
	}

	dts_pass("tel_del_smart_assistant_area_list");
}

static void utc_fail_tel_del_smart_assistant_area_list (void)
{
	int ret;
	TelSmartAssistantAreaList_t area_list;

	memset (&area_list, 0, sizeof(TelSmartAssistantAreaList_t));

	area_list.count = 1;
	area_list.area->index = 1;
	area_list.area->mode_state = TAPI_SMART_ASSISTANT_MODE_STATE_STOP;

	ret = tel_del_smart_assistant_area_list (NULL, &area_list, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_del_smart_assistant_area_list", "Parameter check failed");
	}

	ret = tel_del_smart_assistant_area_list (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_del_smart_assistant_area_list", "Parameter check failed");
	}

	dts_pass("tel_del_smart_assistant_area_list");
}

/**
 * tel_add_smart_assistant_area
 *
 */
static void on_tel_add_smart_assistant_area (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_add_smart_assistant_area", "Callback userdata crashed");
	}
}

static void utc_tel_add_smart_assistant_area (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSmartAssistantArea_t area;

	memset (&area, 0, sizeof(TelSmartAssistantArea_t));

	area.index = 1;
	area.mode_state = TAPI_SMART_ASSISTANT_MODE_STATE_STOP;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_add_smart_assistant_area (handle, &area, on_tel_add_smart_assistant_area, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_add_smart_assistant_area", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_add_smart_assistant_area", "Callback not invoked");
	}

	dts_pass("tel_add_smart_assistant_area");
}

static void utc_fail_tel_add_smart_assistant_area (void)
{
	int ret;
	TelSmartAssistantArea_t area;

	memset (&area, 0, sizeof(TelSmartAssistantArea_t));

	area.index = 1;
	area.mode_state = TAPI_SMART_ASSISTANT_MODE_STATE_STOP;

	ret = tel_add_smart_assistant_area (NULL, &area, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_add_smart_assistant_area", "Parameter check failed");
	}

	ret = tel_add_smart_assistant_area (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_add_smart_assistant_area", "Parameter check failed");
	}

	dts_pass("tel_add_smart_assistant_area");
}

/**
 * tel_modify_smart_assistant_area
 *
 */
static void on_tel_modify_smart_assistant_area (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_modify_smart_assistant_area", "Callback userdata crashed");
	}
}

static void utc_tel_modify_smart_assistant_area (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSmartAssistantArea_t area;

	memset (&area, 0, sizeof(TelSmartAssistantArea_t));

	area.index = 1;
	area.mode_state = TAPI_SMART_ASSISTANT_MODE_STATE_START;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_modify_smart_assistant_area (handle, &area, on_tel_modify_smart_assistant_area, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_modify_smart_assistant_area", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_modify_smart_assistant_area", "Callback not invoked");
	}

	dts_pass("tel_modify_smart_assistant_area");
}

static void utc_fail_tel_modify_smart_assistant_area (void)
{
	int ret;
	TelSmartAssistantArea_t area;

	memset (&area, 0, sizeof(TelSmartAssistantArea_t));

	area.index = 1;
	area.mode_state = TAPI_SMART_ASSISTANT_MODE_STATE_START;

	ret = tel_modify_smart_assistant_area (NULL, &area, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_modify_smart_assistant_area", "Parameter check failed");
	}

	ret = tel_modify_smart_assistant_area (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_modify_smart_assistant_area", "Parameter check failed");
	}

	dts_pass("tel_modify_smart_assistant_area");
}

/**
 * tel_set_smart_assistant_info
 *
 */
static void on_tel_set_smart_assistant_info (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_smart_assistant_info", "Callback userdata crashed");
	}
}

static void utc_tel_set_smart_assistant_info (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSmartAssistantInfo_t info;

	memset (&info, 0, sizeof(TelSmartAssistantInfo_t));

	info.index = 1;
	info.lpp_state = TAPI_SMART_ASSISTANT_LPP_STATE_START;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_smart_assistant_info (handle, &info, on_tel_set_smart_assistant_info, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_smart_assistant_info", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_smart_assistant_info", "Callback not invoked");
	}

	dts_pass("tel_set_smart_assistant_info");
}

static void utc_fail_tel_set_smart_assistant_info (void)
{
	int ret;
	TelSmartAssistantInfo_t info;

	memset (&info, 0, sizeof(TelSmartAssistantInfo_t));

	info.index = 1;
	info.lpp_state = TAPI_SMART_ASSISTANT_MODE_STATE_START;

	ret = tel_set_smart_assistant_info (NULL, &info, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_smart_assistant_info", "Parameter check failed");
	}

	ret = tel_set_smart_assistant_info (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_smart_assistant_info", "Parameter check failed");
	}

	dts_pass("tel_set_smart_assistant_info");
}

/**
 * Generate default TC for no-additional-parameter type API
 *
 */
DO(tel_enable_smart_assistant)
DO(tel_disable_smart_assistant)

struct tet_testlist tet_testlist[] = {
	/* generated TC */
	{ utc_tel_enable_smart_assistant, 1 },
	{ utc_fail_tel_enable_smart_assistant, 2 },
	{ utc_tel_disable_smart_assistant, 1 },
	{ utc_fail_tel_disable_smart_assistant, 2 },
	/* custom TC */
	{ utc_tel_set_gps_frequency_aiding, 1 },
	{ utc_fail_tel_set_gps_frequency_aiding, 2 },
	{ utc_tel_confirm_gps_measure_pos, 1 },
	{ utc_fail_tel_confirm_gps_measure_pos, 2 },
	{ utc_tel_sync_smart_assistant_area_list, 1 },
	{ utc_fail_tel_sync_smart_assistant_area_list, 2 },
	{ utc_tel_del_smart_assistant_area_list, 1 },
	{ utc_fail_tel_del_smart_assistant_area_list, 2 },
	{ utc_tel_add_smart_assistant_area, 1 },
	{ utc_fail_tel_add_smart_assistant_area, 2 },
	{ utc_tel_modify_smart_assistant_area, 1 },
	{ utc_fail_tel_modify_smart_assistant_area, 2 },
	{ utc_tel_set_smart_assistant_info, 1 },
	{ utc_fail_tel_set_smart_assistant_info, 2 },
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
