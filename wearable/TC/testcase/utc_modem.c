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
#include <ITapiModem.h>
#include <TapiUtility.h>

#include "util_common.h"

TapiHandle *handle;
enum async_state async_flag;

/**
 * tel_process_power_command
 *
 */
static void on_tel_process_power_command (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_process_power_command", "Callback userdata crashed");
	}
}

static void utc_tel_process_power_command (void)
{
	int ret;
	int value = 0xC0FFEE;
	tapi_power_phone_cmd_t cmd;

	cmd = 1;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_process_power_command (handle, cmd, on_tel_process_power_command, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_process_power_command", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_process_power_command", "Callback not invoked");
	}

	dts_pass("tel_process_power_command");
}

static void utc_fail_tel_process_power_command (void)
{
	int ret;

	ret = tel_process_power_command (NULL, 1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_process_power_command", "Parameter check failed");
	}

	ret = tel_process_power_command (handle, 3, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_process_power_command", "Parameter check failed");
	}

	dts_pass("tel_process_power_command");
}

/**
 * tel_set_flight_mode
 *
 */
static void on_tel_set_flight_mode (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_flight_mode", "Callback userdata crashed");
	}
}

static void utc_tel_set_flight_mode (void)
{
	int ret;
	int value = 0xC0FFEE;
	tapi_power_flight_mode_type_t mode;

	mode = 1;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_flight_mode (handle, mode, on_tel_set_flight_mode, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_flight_mode", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_flight_mode", "Callback not invoked");
	}

	dts_pass("tel_set_flight_mode");
}

static void utc_fail_tel_set_flight_mode (void)
{
	int ret;

	ret = tel_set_flight_mode (NULL, 1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_flight_mode", "Parameter check failed");
	}

	ret = tel_set_flight_mode (handle, 3, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_flight_mode", "Parameter check failed");
	}

	dts_pass("tel_set_flight_mode");
}

/**
 * tel_get_misc_me_version_sync
 *
 */
static void utc_tel_get_misc_me_version_sync (void)
{
	TelMiscVersionInformation *ret = NULL;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_get_misc_me_version_sync (handle);
	if (ret == NULL) {
		dts_fail("tel_get_misc_me_version_sync", "Unexpected return");
	}

	dts_pass("tel_get_misc_me_version_sync");
}

static void utc_fail_tel_get_misc_me_version_sync (void)
{
	TelMiscVersionInformation *ret = NULL;

	ret = tel_get_misc_me_version_sync (NULL);
	if (ret != NULL) {
		dts_fail("tel_get_misc_me_version_sync", "Unexpected return");
	}

	dts_pass("tel_get_misc_me_version_sync");
}

/**
 * tel_get_misc_me_sn_sync
 *
 */
static void utc_tel_get_misc_me_sn_sync (void)
{
	char *ret = NULL;

	util_init_loop ();

	ret = tel_get_misc_me_sn_sync (handle);
	if (ret == NULL) {
		dts_fail("tel_get_misc_me_sn_sync", "Unexpected return");
	}

	dts_pass("tel_get_misc_me_sn_sync");
}

static void utc_fail_tel_get_misc_me_sn_sync (void)
{
	char *ret = NULL;

	ret = tel_get_misc_me_sn_sync (NULL);
	if (ret != NULL) {
		dts_fail("tel_get_misc_me_sn_sync", "Unexpected return");
	}

	dts_pass("tel_get_misc_me_sn_sync");
}

/**
 * tel_get_misc_me_sn_sync
 *
 */
static void utc_tel_get_misc_me_imei_sync (void)
{
	char *ret = NULL;

	util_init_loop ();

	ret = tel_get_misc_me_imei_sync (handle);
	if (ret == NULL) {
		dts_fail("tel_get_misc_me_imei_sync", "Unexpected return");
	}

	dts_pass("tel_get_misc_me_imei_sync");
}

static void utc_fail_tel_get_misc_me_imei_sync (void)
{
	char *ret = NULL;

	ret = tel_get_misc_me_imei_sync (NULL);
	if (ret != NULL) {
		dts_fail("tel_get_misc_me_imei_sync", "Unexpected return");
	}

	dts_pass("tel_get_misc_me_imei_sync");
}

/**
 * tel_check_modem_power_status
 *
 */
static void utc_tel_check_modem_power_status (void)
{
	int ret;
	int result;

	util_init_loop ();

	ret = tel_check_modem_power_status (handle, &result);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_check_modem_power_status", "Unexpected return");
	}

	dts_pass("tel_check_modem_power_status");
}

static void utc_fail_tel_check_modem_power_status (void)
{
	int ret;
	int result;

	ret = tel_check_modem_power_status (NULL, &result);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_check_modem_power_status", "Unexpected return");
	}

	ret = tel_check_modem_power_status (handle, NULL);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_check_modem_power_status", "Unexpected return");
	}

	dts_pass("tel_check_modem_power_status");
}

/**
 * tel_control_modem_dun_pin_ctrl
 *
 */
static void on_tel_control_modem_dun_pin_ctrl (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_control_modem_dun_pin_ctrl", "Callback userdata crashed");
	}
}

static void utc_tel_control_modem_dun_pin_ctrl (void)
{
	int ret;
	int value = 0xC0FFEE;
	tapi_ps_btdun_pincontrol pincontrol;

	pincontrol.signal = GPRS_SIGNAL_DCD;
	pincontrol.status = GPRS_SIGNAL_STATUS_ON;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_control_modem_dun_pin_ctrl (handle, &pincontrol, on_tel_control_modem_dun_pin_ctrl, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_control_modem_dun_pin_ctrl", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_control_modem_dun_pin_ctrl", "Callback not invoked");
	}

	dts_pass("tel_control_modem_dun_pin_ctrl");
}

static void utc_fail_tel_control_modem_dun_pin_ctrl (void)
{
	int ret;

	ret = tel_control_modem_dun_pin_ctrl (NULL, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_control_modem_dun_pin_ctrl", "Parameter check failed");
	}

	ret = tel_control_modem_dun_pin_ctrl (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_control_modem_dun_pin_ctrl", "Parameter check failed");
	}

	dts_pass("tel_control_modem_dun_pin_ctrl");
}

/**
 * Generate default TC for no-additional-parameter type API
 *
 */
DO(tel_get_flight_mode)
DO(tel_get_misc_me_version)
DO(tel_get_misc_me_sn)
DO(tel_get_misc_me_imei)

struct tet_testlist tet_testlist[] = {
	/* generated TC */
	{ utc_tel_get_flight_mode, 1 },
	{ utc_fail_tel_get_flight_mode, 2 },
	{ utc_tel_get_misc_me_version, 1 },
	{ utc_fail_tel_get_misc_me_version, 2 },
	{ utc_tel_get_misc_me_sn, 1 },
	{ utc_fail_tel_get_misc_me_sn, 2 },
	{ utc_tel_get_misc_me_imei, 1 },
	{ utc_fail_tel_get_misc_me_imei, 2 },
	/* custom TC */
	{ utc_tel_process_power_command, 1 },
	{ utc_fail_tel_process_power_command, 2 },
	{ utc_tel_set_flight_mode, 1 },
	{ utc_fail_tel_set_flight_mode, 2 },
	{ utc_tel_get_misc_me_version_sync, 1 },////
	{ utc_fail_tel_get_misc_me_version_sync, 2 },////
	{ utc_tel_get_misc_me_sn_sync, 1 },////
	{ utc_fail_tel_get_misc_me_sn_sync, 2 },////
	{ utc_tel_get_misc_me_imei_sync, 1 },/////////
	{ utc_fail_tel_get_misc_me_imei_sync, 2 },//////////
	{ utc_tel_check_modem_power_status, 1 },
	{ utc_fail_tel_check_modem_power_status, 2 },
	{ utc_tel_control_modem_dun_pin_ctrl, 1 },
	{ utc_fail_tel_control_modem_dun_pin_ctrl, 2 },
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
