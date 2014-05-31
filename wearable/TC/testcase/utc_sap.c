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
#include <ITapiSap.h>
#include <TapiUtility.h>

#include "util_common.h"

TapiHandle *handle;
enum async_state async_flag;

/**
 * tel_req_sap_connect
 *
 */
static void on_tel_req_sap_connect (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_req_sap_connect", "Callback userdata crashed");
	}
}

static void utc_tel_req_sap_connect (void)
{
	int ret;
	int value = 0xC0FFEE;
	int max_msg_size;

	max_msg_size = 255;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_req_sap_connect (handle, max_msg_size, on_tel_req_sap_connect, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_req_sap_connect", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_req_sap_connect", "Callback not invoked");
	}

	dts_pass("tel_req_sap_connect");
}

static void utc_fail_tel_req_sap_connect (void)
{
	int ret;

	ret = tel_req_sap_connect (NULL, 0, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_req_sap_connect", "Parameter check failed");
	}

	dts_pass("tel_req_sap_connect");
}

/**
 * tel_req_sap_transfer_apdu
 *
 */
static void on_tel_req_sap_transfer_apdu (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_req_sap_transfer_apdu", "Callback userdata crashed");
	}
}

static void utc_tel_req_sap_transfer_apdu (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSapApduData_t apdu;

	memset (&apdu, 0, sizeof(TelSimApdu_t));

	apdu.apdu_len = 7;
	strcpy ((char *)apdu.apdu_data, "a0a40000026f02");

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_req_sap_transfer_apdu (handle, &apdu, on_tel_req_sap_transfer_apdu, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_req_sap_transfer_apdu", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_req_sap_transfer_apdu", "Callback not invoked");
	}

	dts_pass("tel_req_sap_transfer_apdu");
}

static void utc_fail_tel_req_sap_transfer_apdu (void)
{
	int ret;

	ret = tel_req_sap_transfer_apdu (NULL, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_req_sap_transfer_apdu", "Parameter check failed");
	}

	ret = tel_req_sap_transfer_apdu (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_req_sap_transfer_apdu", "Parameter check failed");
	}

	dts_pass("tel_req_sap_transfer_apdu");
}

/**
 * tel_req_sap_transport_protocol
 *
 */
static void on_tel_req_sap_transport_protocol (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_req_sap_transport_protocol", "Callback userdata crashed");
	}
}

static void utc_tel_req_sap_transport_protocol (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSimSapProtocol_t protocol;

	protocol = 0;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_req_sap_transport_protocol (handle, protocol, on_tel_req_sap_transport_protocol, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_req_sap_transport_protocol", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_req_sap_transport_protocol", "Callback not invoked");
	}

	dts_pass("tel_req_sap_transport_protocol");
}

static void utc_fail_tel_req_sap_transport_protocol (void)
{
	int ret;

	ret = tel_req_sap_transport_protocol (NULL, 0, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_req_sap_transport_protocol", "Parameter check failed");
	}

	dts_pass("tel_req_sap_transport_protocol");
}

/**
 * tel_req_sap_power_operation
 *
 */
static void on_tel_req_sap_power_operation (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_req_sap_power_operation", "Callback userdata crashed");
	}
}

static void utc_tel_req_sap_power_operation (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSimSapPowerMode_t power_mode;

	power_mode = 0;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_req_sap_power_operation (handle, power_mode, on_tel_req_sap_power_operation, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_req_sap_power_operation", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_req_sap_power_operation", "Callback not invoked");
	}

	dts_pass("tel_req_sap_power_operation");
}

static void utc_fail_tel_req_sap_power_operation (void)
{
	int ret;

	ret = tel_req_sap_power_operation (NULL, 0, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_req_sap_power_operation", "Parameter check failed");
	}

	dts_pass("tel_req_sap_power_operation");
}

/**
 * Generate default TC for no-additional-parameter type API
 *
 */
DO(tel_req_sap_disconnect)
DO(tel_req_sap_connection_status)
DO(tel_req_sap_transfer_atr)
DO(tel_req_sap_cardreader_status)

struct tet_testlist tet_testlist[] = {
	/* generated TC */
	{ utc_tel_req_sap_disconnect, 1 },
	{ utc_fail_tel_req_sap_disconnect, 2 },
	{ utc_tel_req_sap_connection_status, 1 },
	{ utc_fail_tel_req_sap_connection_status, 2 },
	{ utc_tel_req_sap_transfer_atr, 1 },
	{ utc_fail_tel_req_sap_transfer_atr, 2 },
	{ utc_tel_req_sap_cardreader_status, 1 },
	{ utc_fail_tel_req_sap_cardreader_status, 2 },
	/* custom TC */
	{ utc_tel_req_sap_connect, 1 },
	{ utc_fail_tel_req_sap_connect, 2 },
	{ utc_tel_req_sap_transfer_apdu, 1 },
	{ utc_fail_tel_req_sap_transfer_apdu, 2 },
	{ utc_tel_req_sap_transport_protocol, 1 },
	{ utc_fail_tel_req_sap_transport_protocol, 2 },
	{ utc_tel_req_sap_power_operation, 1 },
	{ utc_fail_tel_req_sap_power_operation, 2 },
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
