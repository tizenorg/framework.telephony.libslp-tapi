/*
 * libslp-tapi
 *
 * Copyright (c) 2013 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Shaik Alimulla <alimulla.s@samsung.com>
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
#include <ITapiSat.h>
#include <TapiUtility.h>

#include "util_common.h"

TapiHandle *handle;
enum async_state async_flag;
TelSatSetupMenuInfo_t main_menu;

/**
 * tel_get_sat_main_menu_info
 * Synchronous call
 *
 */

static void utc_tel_get_sat_main_menu_info (void)
{
	int ret;

	ret = tel_get_sat_main_menu_info (handle, &main_menu);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_get_sat_main_menu_info", "Unexpected return");
	}

	dts_pass("tel_get_sat_main_menu_info");
}

static void utc_fail_tel_get_sat_main_menu_info (void)
{
	int ret;

	ret = tel_get_sat_main_menu_info (NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sat_main_menu_info", "Parameter check failed");
	}

	ret = tel_get_sat_main_menu_info (handle, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sat_main_menu_info", "Parameter check failed");
	}

	dts_pass("tel_get_sat_main_menu_info");
}

/**
 * tel_select_sat_menu
 *
 */
static void on_tel_select_sat_menu (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_select_sat_menu", "Callback userdata crashed");
	}
}

static void utc_tel_select_sat_menu (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSatMenuSelectionReqInfo_t selected_menu;

	selected_menu.bIsHelpRequested = 0;
	selected_menu.itemIdentifier = 0x01;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_select_sat_menu (handle, &selected_menu,	on_tel_select_sat_menu, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_select_sat_menu", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_select_sat_menu", "Callback not invoked");
	}

	dts_pass("tel_select_sat_menu");
}

static void utc_fail_tel_select_sat_menu (void)
{
	int ret;

	ret = tel_select_sat_menu (NULL, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_select_sat_menu", "Parameter check failed");
	}

	ret = tel_select_sat_menu (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_select_sat_menu", "Parameter check failed");
	}

	dts_pass("tel_select_sat_menu");
}

/**
 * tel_download_sat_event
 *
 */
static void on_tel_download_sat_event (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_download_sat_event", "Callback userdata crashed");
	}
}

static void utc_tel_download_sat_event (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSatEventDownloadReqInfo_t event_data;

	event_data.eventDownloadType = TAPI_EVENT_SAT_DW_TYPE_CALL_CONNECTED;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_download_sat_event (handle, &event_data, on_tel_download_sat_event, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_download_sat_event", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_download_sat_event", "Callback not invoked");
	}

	dts_pass("tel_download_sat_event");
}

static void utc_fail_tel_download_sat_event (void)
{
	int ret;

	ret = tel_download_sat_event (NULL, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_download_sat_event", "Parameter check failed");
	}

	ret = tel_download_sat_event (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_download_sat_event", "Parameter check failed");
	}

	dts_pass("tel_download_sat_event");
}

/**
 * tel_send_sat_ui_display_status
 *
 */
static void utc_tel_send_sat_ui_display_status (void)
{
	int ret;
	TelSatUiDisplayStatusType_t status;

	status = TAPI_SAT_DISPLAY_SUCCESS;

	ret = tel_send_sat_ui_display_status (handle, 0, status);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_send_sat_ui_display_status", "Unexpected return");
	}

	dts_pass("tel_send_sat_ui_display_status");
}

static void utc_fail_tel_send_sat_ui_display_status (void)
{
	int ret;

	ret = tel_send_sat_ui_display_status (NULL, 0, 0);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_send_sat_ui_display_status", "Parameter check failed");
	}

	dts_pass("tel_send_sat_ui_display_status");
}

/**
 * tel_send_sat_ui_user_confirm
 *
 */
static void utc_tel_send_sat_ui_user_confirm (void)
{
	int ret;
	TelSatUiUserConfirmInfo_t user_confirm_data;

	user_confirm_data.commandId = 0;
	user_confirm_data.commandType = TAPI_SAT_CMD_TYPE_DISPLAY_TEXT;
	user_confirm_data.keyType = TAPI_SAT_USER_CONFIRM_YES;
	user_confirm_data.dataLen = 0;
	user_confirm_data.pAdditionalData = NULL;


	ret = tel_send_sat_ui_user_confirm (handle, &user_confirm_data);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_send_sat_ui_user_confirm", "Unexpected return");
	}

	dts_pass("tel_send_sat_ui_user_confirm");
}

static void utc_fail_tel_send_sat_ui_user_confirm (void)
{
	int ret;

	ret = tel_send_sat_ui_user_confirm (NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_send_sat_ui_user_confirm", "Parameter check failed");
	}

	ret = tel_send_sat_ui_user_confirm (handle, NULL );
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_send_sat_ui_user_confirm", "Parameter check failed");
	}

	dts_pass("tel_send_sat_ui_user_confirm");
}

/**
 * tel_send_sat_app_exec_result
 *
 */
static void utc_tel_send_sat_app_exec_result (void)
{
	int ret;
	TelSatAppsRetInfo_t app_ret_info;

	app_ret_info.commandId = 0;
	app_ret_info.commandType = TAPI_SAT_CMD_TYPE_DISPLAY_TEXT;
	app_ret_info.appsRet.displayText.resp = TAPI_SAT_R_SUCCESS;
	app_ret_info.appsRet.displayText.meProblem = TAPI_SAT_ME_PROBLEM_NO_SPECIFIC_CAUSE;

	ret = tel_send_sat_app_exec_result (handle, &app_ret_info);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_send_sat_app_exec_result", "Unexpected return");
	}

	dts_pass("tel_send_sat_app_exec_result");
}

static void utc_fail_tel_send_sat_app_exec_result (void)
{
	int ret;

	ret = tel_send_sat_app_exec_result (NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_send_sat_app_exec_result", "Parameter check failed");
	}

	ret = tel_send_sat_app_exec_result (handle, NULL );
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_send_sat_app_exec_result", "Parameter check failed");
	}

	dts_pass("tel_send_sat_app_exec_result");
}

struct tet_testlist tet_testlist[] = {
	/* generated TC */
	{ utc_tel_get_sat_main_menu_info, 1 },
	{ utc_fail_tel_get_sat_main_menu_info, 2 },
	{ utc_tel_select_sat_menu, 1 },
	{ utc_fail_tel_select_sat_menu, 2 },
	{ utc_tel_download_sat_event, 1 },
	{ utc_fail_tel_download_sat_event, 2 },
	{ utc_tel_send_sat_ui_display_status, 1 },
	{ utc_fail_tel_send_sat_ui_display_status, 2 },
	{ utc_tel_send_sat_ui_user_confirm, 1 },
	{ utc_fail_tel_send_sat_ui_user_confirm, 2 },
	{ utc_tel_send_sat_app_exec_result, 1 },
	{ utc_fail_tel_send_sat_app_exec_result, 2 },
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
