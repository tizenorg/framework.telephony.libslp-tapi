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
#include <ITapiSs.h>
#include <TapiUtility.h>

#include "util_common.h"

TapiHandle *handle;
enum async_state async_flag;

static char data_ss_set_barring_password[TAPI_SS_GSM_BARR_PW_LEN_MAX+1] = "0000";

TelSsClass_t  class = 0x10;

TelSsBarringType_t barring_type[9] = {
	TAPI_SS_CB_TYPE_BAOC,
	TAPI_SS_CB_TYPE_BOIC,
	TAPI_SS_CB_TYPE_BOIC_NOT_HC,
	TAPI_SS_CB_TYPE_BAIC,
	TAPI_SS_CB_TYPE_BIC_ROAM,
	TAPI_SS_CB_TYPE_AB,
	TAPI_SS_CB_TYPE_AOB,
	TAPI_SS_CB_TYPE_AIB,
	TAPI_SS_CB_TYPE_BIC_NOT_SIM
} ;

TelSsBarringMode_t barring_mode [2] = {
	TAPI_SS_CB_MODE_ACTIVATE,
	TAPI_SS_CB_MODE_DEACTIVATE
};

TelSsForwardWhen_t forwarding_type[7] = {
	TAPI_SS_CF_WHEN_CFU,
	TAPI_SS_CF_WHEN_CFB,
	TAPI_SS_CF_WHEN_CFNRy,
	TAPI_SS_CF_WHEN_CFNRc,
	TAPI_SS_CF_WHEN_CF_ALL,
	TAPI_SS_CF_WHEN_CFC
};

TelSsForwardMode_t forwarding_mode[4] = {
	TAPI_SS_CF_MODE_DISABLE_EV,
	TAPI_SS_CF_MODE_ENABLE_EV,
	TAPI_SS_CF_MODE_REGISTRATION_EV,
	TAPI_SS_CF_MODE_ERASURE_EV
};

TelSsCallWaitingMode_t waiting_mode [2] = {
	TAPI_SS_CW_MODE_ACTIVATE,
	TAPI_SS_CW_MODE_DEACTIVATE
};

TelSsCliType_t cli_type[6] = {
	TAPI_SS_CLI_CLIP,
	TAPI_SS_CLI_CLIR,
	TAPI_SS_CLI_COLP,
	TAPI_SS_CLI_COLR,
	TAPI_SS_CLI_CDIP,
	TAPI_SS_CLI_CNAP
};

TelSsCliStatus_t cli_mode[6] = {
	TAPI_CLI_STATUS_NOT_PROVISONED,
	TAPI_CLI_STATUS_PROVISIONED,
	TAPI_CLI_STATUS_ACTIVATED,
	TAPI_CLI_STATUS_UNKOWN,
	TAPI_CLI_STATUS_TEMP_RESTRICTED,
	TAPI_CLI_STATUS_TEMP_ALLOWED
};

/* Barring Activate/De-activate Macro */
#define DO_BARRING(func, param1, param2, param3) \
	static void on_##func(TapiHandle *handle, int result, void *data, void *user_data) \
	{ \
		int *value = user_data; \
\
		async_flag = ASYNC_DONE; \
		util_stop_loop(); \
\
		if (*value != 0xC0FFEE) { \
			dts_fail(#func, "Callback userdata crashed"); \
		} \
		if (result != 0x0) { \
			dts_fail(#func, "Operation failed"); \
		} \
	} \
\
	static void utc_##func (TelSsClass_t  param1, TelSsBarringType_t param2, TelSsBarringMode_t param3) \
	{ \
		TelSsBarringInfo_t info; \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		memset(&info, 0, sizeof(TelSsBarringInfo_t)); \
		info.Class =param1; \
		info.Type = param2; \
		info.Mode = param3; \
		g_strlcpy(info.szPassword, data_ss_set_barring_password, TAPI_SS_GSM_BARR_PW_LEN_MAX); \
		ret = tel_set_ss_barring (handle, &info, on_##func, &value); \
		if (ret != TAPI_API_SUCCESS) { \
			dts_fail(#func, "Unexpected return"); \
		} \
\
		util_start_loop(); \
		util_free_loop(); \
\
		if (async_flag != ASYNC_DONE) { \
			dts_fail(#func, "Callback not invoked"); \
		} \
\
		dts_pass(#func); \
	} \
\
	static void utc_fail_##func (TelSsClass_t  param1, TelSsBarringType_t param2, TelSsBarringMode_t param3) \
	{ \
		int ret; \
\
		ret = tel_set_ss_barring (NULL, NULL, NULL,NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}

/* Barring Status Macro */
#define DO_BARRING_STATUS(func, param1, param2) \
	static void on_##func (TapiHandle *handle, int result, void *data, void *user_data) \
	{ \
		int *value = user_data; \
\
		async_flag = ASYNC_DONE; \
		util_stop_loop(); \
\
		if (*value != 0xC0FFEE) { \
			dts_fail(#func, "Callback userdata crashed"); \
		} \
		if (result != 0x0) { \
			dts_fail(#func, "Operation failed"); \
		} \
	} \
\
	static void utc_##func (TelSsClass_t  param1, TelSsBarringType_t param2) \
	{ \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		ret = tel_get_ss_barring_status (handle, param1, param2, on_##func, &value); \
		if (ret != TAPI_API_SUCCESS) { \
			dts_fail(#func, "Unexpected return"); \
		} \
\
		util_start_loop(); \
		util_free_loop(); \
\
		if (async_flag != ASYNC_DONE) { \
			dts_fail(#func, "Callback not invoked"); \
		} \
\
		dts_pass(#func); \
	} \
\
	static void utc_fail_##func (TelSsClass_t  param1, TelSsBarringType_t param2) \
	{ \
		int ret; \
\
		ret = tel_get_ss_barring_status (NULL, 0, 0, NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}

/* Forwarding Register/Erasure Macro*/
#define DO_FORWARDING(func, param1, param2, param3) \
	static void on_##func (TapiHandle *handle, int result, void *data, void *user_data) \
	{ \
		int *value = user_data; \
\
		async_flag = ASYNC_DONE; \
		util_stop_loop(); \
\
		if (*value != 0xC0FFEE) { \
			dts_fail(#func, "Callback userdata crashed"); \
		} \
		if (result != 0x0) { \
			dts_fail(#func, "Operation failed"); \
		} \
	} \
\
	static void utc_##func (TelSsClass_t  param1, TelSsForwardWhen_t param2, TelSsForwardMode_t param3) \
	{ \
		TelSsForwardInfo_t info;\
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		memset(&info, 0, sizeof(TelSsForwardInfo_t)); \
		info.Class = param1; \
		info.Condition = param2; \
		info.NoReplyConditionTimer = 0x05;\
		info.Mode = param3;\
		info.Ton = 0x01;\
		info.Npi = 0x01;\
		strncpy((char*)info.szPhoneNumber, "+919535099681", 13);\
		info.szPhoneNumber[13] = '\0';\
		ret = tel_set_ss_forward (handle, &info, on_##func, &value); \
		if (ret != TAPI_API_SUCCESS) { \
			dts_fail(#func, "Unexpected return"); \
		} \
\
		util_start_loop(); \
		util_free_loop(); \
\
		if (async_flag != ASYNC_DONE) { \
			dts_fail(#func, "Callback not invoked"); \
		} \
\
		dts_pass(#func); \
	} \
\
	static void utc_fail_##func (TelSsClass_t  param1, TelSsForwardWhen_t param2, TelSsForwardMode_t param3) \
	{ \
		int ret; \
\
		ret = tel_set_ss_forward (NULL, NULL, NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}

/* Forwarding Get Status Macro*/
#define DO_FORWARDING_STATUS(func, param1, param2) \
	static void on_##func (TapiHandle *handle, int result, void *data, void *user_data) \
	{ \
		int *value = user_data; \
\
		async_flag = ASYNC_DONE; \
		util_stop_loop(); \
\
		if (*value != 0xC0FFEE) { \
			dts_fail(#func, "Callback userdata crashed"); \
		} \
		if (result != 0x0) { \
			dts_fail(#func, "Operation failed"); \
		} \
	} \
\
	static void utc_##func (TelSsClass_t  param1, TelSsForwardWhen_t param2) \
	{ \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		ret = tel_get_ss_forward_status (handle, param1, param2, on_##func, &value); \
		if (ret != TAPI_API_SUCCESS) { \
			dts_fail(#func, "Unexpected return"); \
		} \
\
		util_start_loop(); \
		util_free_loop(); \
\
		if (async_flag != ASYNC_DONE) { \
			dts_fail(#func, "Callback not invoked"); \
		} \
\
		dts_pass(#func); \
	} \
\
	static void utc_fail_##func (TelSsClass_t  param1, TelSsForwardWhen_t param2) \
	{ \
		int ret; \
\
		ret = tel_get_ss_forward_status (NULL, 0, 0, NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}

/* Waiting Activate/De-activate Macro*/
#define DO_WAITING(func, param1, param2) \
	static void on_##func (TapiHandle *handle, int result, void *data, void *user_data) \
	{ \
		int *value = user_data; \
\
		async_flag = ASYNC_DONE; \
		util_stop_loop(); \
\
		if (*value != 0xC0FFEE) { \
			dts_fail(#func, "Callback userdata crashed"); \
		} \
		if (result != 0x0) { \
			dts_fail(#func, "Operation failed"); \
		} \
	} \
\
	static void utc_##func (TelSsClass_t param1, TelSsCallWaitingMode_t param2) \
	{ \
		TelSsWaitingInfo_t info; \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
		memset(&info, 0, sizeof(TelSsWaitingInfo_t)); \
		async_flag = ASYNC_READY; \
		info.Class = param1;\
		info.Mode = param2;\
		ret = tel_set_ss_waiting (handle, &info, on_##func, &value); \
		if (ret != TAPI_API_SUCCESS) { \
			dts_fail(#func, "Unexpected return"); \
		} \
\
		util_start_loop(); \
		util_free_loop(); \
\
		if (async_flag != ASYNC_DONE) { \
			dts_fail(#func, "Callback not invoked"); \
		} \
\
		dts_pass(#func); \
	} \
\
	static void utc_fail_##func (TelSsClass_t param1, TelSsCallWaitingMode_t param2) \
	{ \
		int ret; \
\
		ret = tel_set_ss_waiting (NULL, NULL, NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}

/* Set CLI Status Macro */
#define DO_CLI(func, param1, param2) \
	static void on_##func (TapiHandle *handle, int result, void *data, void *user_data) \
	{ \
		int *value = user_data; \
\
		async_flag = ASYNC_DONE; \
		util_stop_loop(); \
\
		if (*value != 0xC0FFEE) { \
			dts_fail(#func, "Callback userdata crashed"); \
		} \
		if (result != 0x0) { \
			dts_fail(#func, "Operation failed"); \
		} \
	} \
\
	static void utc_##func (TelSsCliType_t param1, TelSsCliStatus_t param2) \
	{ \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		ret = tel_set_ss_cli_status(handle, param1, param2, on_##func, &value); \
		if (ret != TAPI_API_SUCCESS) { \
			dts_fail(#func, "Unexpected return"); \
		} \
\
		util_start_loop(); \
		util_free_loop(); \
\
		if (async_flag != ASYNC_DONE) { \
			dts_fail(#func, "Callback not invoked"); \
		} \
\
		dts_pass(#func); \
	} \
\
	static void utc_fail_##func (TelSsCliType_t param1) \
	{ \
		int ret; \
\
		ret = tel_set_ss_cli_status (NULL, 0, 0, NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}

/* CLI Interrogation Macro */
#define DO_CLI_STATUS(func, param1) \
	static void on_##func (TapiHandle *handle, int result, void *data, void *user_data) \
	{ \
		int *value = user_data; \
\
		async_flag = ASYNC_DONE; \
		util_stop_loop(); \
\
		if (*value != 0xC0FFEE) { \
			dts_fail(#func, "Callback userdata crashed"); \
		} \
		if (result != 0x0) { \
			dts_fail(#func, "Operation failed"); \
		} \
	} \
\
	static void utc_##func (TelSsCliType_t param1) \
	{ \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		ret = tel_get_ss_cli_status(handle, param1, on_##func, &value); \
		if (ret != TAPI_API_SUCCESS) { \
			dts_fail(#func, "Unexpected return"); \
		} \
\
		util_start_loop(); \
		util_free_loop(); \
\
		if (async_flag != ASYNC_DONE) { \
			dts_fail(#func, "Callback not invoked"); \
		} \
\
		dts_pass(#func); \
	} \
\
	static void utc_fail_##func (TelSsCliType_t param1) \
	{ \
		int ret; \
\
		ret = tel_get_ss_cli_status (NULL, 0, NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}


/**
 * tel_change_ss_barring_password
 *
 */
static void on_tel_change_ss_barring_password (TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_change_ss_barring_password", "Callback userdata crashed");
	}
	if (result != 0x0) {
		dts_fail("tel_change_ss_barring_password", "Operation failed");
	}
}

static void utc_tel_change_ss_barring_password (void)
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_change_ss_barring_password (handle, "0000","1111", "1111",
			on_tel_change_ss_barring_password, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_change_ss_barring_password", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_change_ss_barring_password", "Callback not invoked");
	}

	dts_pass("tel_change_ss_barring_password");
}

static void utc_fail_tel_change_ss_barring_password (void)
{
	int ret;

	ret = tel_change_ss_barring_password (NULL, NULL, 0, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_change_ss_barring_password", "Parameter check failed");
	}

	ret = tel_change_ss_barring_password (handle, NULL, 0, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_change_ss_barring_password", "Parameter check failed");
	}

	dts_pass("tel_change_ss_barring_password");
}


/**
 * tel_ss_waiting_status
 *
 */
static void on_tel_ss_waiting_status (TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_ss_waiting_status", "Callback userdata crashed");
	}
	if (result != 0x0) {
		dts_fail("tel_ss_waiting_status", "Operation failed");
	}
}

static void utc_tel_ss_waiting_status (void)
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_get_ss_waiting_status (handle, 0x10,
			on_tel_ss_waiting_status, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_ss_waiting_status", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_ss_waiting_status", "Callback not invoked");
	}

	dts_pass("tel_ss_waiting_status");
}

static void utc_fail_tel_ss_waiting_status (void)
{
	int ret;

	ret = tel_get_ss_waiting_status (NULL, 0, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("el_ss_waiting_status", "Parameter check failed");
	}

	ret = tel_get_ss_waiting_status (handle, 0, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("el_ss_waiting_status", "Parameter check failed");
	}

	dts_pass("el_ss_waiting_status");
}


/**
 * tel_ss_init_ussd
 *
 */
static void on_tel_ss_init_ussd (TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_ss_init_ussd", "Callback userdata crashed");
	}
	if (result != 0x0) {
		dts_fail("tel_ss_init_ussd", "Operation failed");
	}
}

static void utc_tel_ss_init_ussd (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSsUssdMsgInfo_t info;

	util_init_loop ();

	async_flag = ASYNC_READY;
	memset(&info, 0, sizeof(TelSsUssdMsgInfo_t));
	info.Type = 0x01;
	info.Length = 0x05;
	strncpy(info.szString, "*121#", 5);
	ret = tel_send_ss_ussd_request (handle, &info,
			on_tel_ss_init_ussd, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_ss_init_ussd", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_ss_init_ussd", "Callback not invoked");
	}

	dts_pass("tel_ss_init_ussd");
}

static void utc_fail_tel_ss_init_ussd (void)
{
	int ret;

	ret = tel_send_ss_ussd_request (NULL, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_ss_init_ussd", "Parameter check failed");
	}

	ret = tel_send_ss_ussd_request (handle, NULL, 0, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_ss_init_ussd", "Parameter check failed");
	}

	dts_pass("tel_ss_init_ussd");
}

/**
 * tel_ss_cancel_ussd
 *
 */
static void on_tel_ss_cancel_ussd (TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_ss_cancel_ussd", "Callback userdata crashed");
	}
	if (result != 0x0) {
		dts_fail("tel_ss_cancel_ussd", "Operation failed");
	}
}

static void utc_tel_ss_cancel_ussd (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSsUssdMsgInfo_t info;

	util_init_loop ();

	async_flag = ASYNC_READY;
	memset(&info, 0, sizeof(TelSsUssdMsgInfo_t));
	info.Type = 0x03;
	info.Length = 0x05;
	strncpy(info.szString, "*121#", 5);
	ret = tel_send_ss_ussd_request (handle, &info,
			on_tel_ss_cancel_ussd, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_ss_cancel_ussd", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_ss_cancel_ussd", "Callback not invoked");
	}

	dts_pass("tel_ss_cancel_ussd");
}

static void utc_fail_tel_ss_cancel_ussd (void)
{
	int ret;

	ret = tel_send_ss_ussd_request (NULL, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_ss_cancel_ussd", "Parameter check failed");
	}

	ret = tel_send_ss_ussd_request (handle, NULL, 0, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_ss_cancel_ussd", "Parameter check failed");
	}

	dts_pass("tel_ss_cancel_ussd");
}

/* Barring activate and De-activate auto generated functions */

DO_BARRING(tel_barring_baoc_activate, class, barring_type[0], barring_mode[0])
DO_BARRING(tel_barring_baoc_deactivate, class, barring_type[0], barring_mode[1])
DO_BARRING(tel_barring_boic_activate, class, barring_type[1], barring_mode[0])
DO_BARRING(tel_barring_boic_deactivate, class, barring_type[1], barring_mode[1])
DO_BARRING(tel_barring_boic_not_hc_activate, class, barring_type[2], barring_mode[0])
DO_BARRING(tel_barring_boic_not_hc_deactivate, class, barring_type[2], barring_mode[1])
DO_BARRING(tel_barring_baic_activate, class,  barring_type[3], barring_mode[0])
DO_BARRING(tel_barring_baic_deactivate, class,  barring_type[3], barring_mode[1])
DO_BARRING(tel_barring_bic_roam_activate, class,  barring_type[4], barring_mode[0])
DO_BARRING(tel_barring_bic_roam_deactivate, class,  barring_type[4], barring_mode[1])
DO_BARRING(tel_barring_ab_activate, class,  barring_type[5], barring_mode[0])
DO_BARRING(tel_barring_ab_deactivate, class,  barring_type[5], barring_mode[1])
DO_BARRING(tel_barring_aob_activate, class,  barring_type[6], barring_mode[0])
DO_BARRING(tel_barring_aob_deactivate, class,  barring_type[6], barring_mode[1])
DO_BARRING(tel_barring_aib_activate, class,  barring_type[7], barring_mode[0])
DO_BARRING(tel_barring_aib_deactivate, class,  barring_type[7], barring_mode[1])
DO_BARRING(tel_barring_bic_not_sim_activate, class,  barring_type[8], barring_mode[0])
DO_BARRING(tel_barring_bic_not_sim_deactivate, class,  barring_type[8], barring_mode[1])

/* Barring get status auto generated functions */

DO_BARRING_STATUS(tel_barring_baoc_status, class,  barring_type[0])
DO_BARRING_STATUS(tel_barring_boic_status, class,  barring_type[1])
DO_BARRING_STATUS(tel_barring_boic_not_hc_status, class,  barring_type[2])
DO_BARRING_STATUS(tel_barring_baic_status, class,  barring_type[3])
DO_BARRING_STATUS(tel_barring_bic_roam_status, class,  barring_type[4])
DO_BARRING_STATUS(tel_barring_ab_status, class,  barring_type[5])
DO_BARRING_STATUS(tel_barring_aob_status, class,  barring_type[6])
DO_BARRING_STATUS(tel_barring_aib_status, class,  barring_type[7])
DO_BARRING_STATUS(tel_barring_bic_not_sim_status, class,  barring_type[8])

/* Forwarding register and erasure auto generated functions */

DO_FORWARDING(tel_forwarding_cfu_register, class, forwarding_type[0], forwarding_mode[2])
DO_FORWARDING(tel_forwarding_cfu_erasure, class, forwarding_type[0], forwarding_mode[3])
DO_FORWARDING(tel_forwarding_cfb_register, class, forwarding_type[1], forwarding_mode[2])
DO_FORWARDING(tel_forwarding_cfb_erasure, class, forwarding_type[1], forwarding_mode[3])
DO_FORWARDING(tel_forwarding_cfnry_register, class, forwarding_type[2], forwarding_mode[2])
DO_FORWARDING(tel_forwarding_cfnry_erasure, class, forwarding_type[2], forwarding_mode[3])
DO_FORWARDING(tel_forwarding_cfnrc_register, class, forwarding_type[3], forwarding_mode[2])
DO_FORWARDING(tel_forwarding_cfunrc_erasure, class, forwarding_type[3], forwarding_mode[3])
DO_FORWARDING(tel_forwarding_cf_all_register, class, forwarding_type[4], forwarding_mode[2])
DO_FORWARDING(tel_forwarding_cf_all_erasure, class, forwarding_type[4], forwarding_mode[3])
DO_FORWARDING(tel_forwarding_cfc_register, class, forwarding_type[5], forwarding_mode[2])
DO_FORWARDING(tel_forwarding_cfc_erasure, class, forwarding_type[5], forwarding_mode[3])


/* Forwarding get status auto generated functions */

DO_FORWARDING_STATUS(tel_forwarding_cfu_status, class, forwarding_type[0])
DO_FORWARDING_STATUS(tel_forwarding_cfb_status, class, forwarding_type[1])
DO_FORWARDING_STATUS(tel_forwarding_cfnry_status, class, forwarding_type[2])
DO_FORWARDING_STATUS(tel_forwarding_cfnrc_status, class, forwarding_type[3])
DO_FORWARDING_STATUS(tel_forwarding_cf_all_status, class, forwarding_type[4])
DO_FORWARDING_STATUS(tel_forwarding_cfc_status, class, forwarding_type[5])


/* Waiting activate/de-activate Macro */

DO_WAITING(tel_waiting_activate, class, waiting_mode[0])
DO_WAITING(tel_waiting_deactivate, class, waiting_mode[1])

/* CLI set status auto generated functions */

DO_CLI(tel_CLIP_activate, cli_type[0], cli_mode[2])
DO_CLI(tel_CLIP_deactivate, cli_type[0], cli_mode[0])
DO_CLI(tel_CLIR_activate, cli_type[1], cli_mode[2])
DO_CLI(tel_CLIR_deactivate, cli_type[1], cli_mode[0])
DO_CLI(tel_COLP_activate, cli_type[2], cli_mode[2])
DO_CLI(tel_COLP_deactivate, cli_type[2], cli_mode[0])
DO_CLI(tel_COLR_activate, cli_type[3], cli_mode[2])
DO_CLI(tel_COLR_deactivate, cli_type[3], cli_mode[0])
DO_CLI(tel_CDIP_activate, cli_type[4], cli_mode[2])
DO_CLI(tel_CDIP_deactivate, cli_type[4], cli_mode[0])
DO_CLI(tel_CNAP_activate, cli_type[5], cli_mode[2])
DO_CLI(tel_CNAP_deactivate, cli_type[5], cli_mode[0])

/* CLI get status auto generated functions */

DO_CLI_STATUS(tel_CLIP_status, cli_type[0])
DO_CLI_STATUS(tel_CLIR_status, cli_type[1])
DO_CLI_STATUS(tel_COLP_status, cli_type[2])
DO_CLI_STATUS(tel_COLR_status, cli_type[3])
DO_CLI_STATUS(tel_CDIP_status, cli_type[4])
DO_CLI_STATUS(tel_CNAP_status, cli_type[5])


struct tet_testlist tet_testlist[] = {
	/* generated TC */
	{ utc_tel_barring_baoc_activate, 1 },
	{ utc_fail_tel_barring_baoc_activate, 2 },
	{ utc_tel_barring_baoc_deactivate, 1 },
	{ utc_fail_tel_barring_baoc_deactivate, 2 },
	{ utc_tel_barring_boic_activate, 1 },
	{ utc_fail_tel_barring_boic_activate, 2 },
	{ utc_tel_barring_boic_deactivate, 1 },
	{ utc_fail_tel_barring_boic_deactivate, 2 },
	{ utc_tel_barring_boic_not_hc_activate, 1 },
	{ utc_fail_tel_barring_boic_not_hc_activate, 2 },
	{ utc_tel_barring_boic_not_hc_deactivate, 1 },
	{ utc_fail_tel_barring_boic_not_hc_deactivate, 2 },
	{ utc_tel_barring_baic_activate, 1 },
	{ utc_fail_tel_barring_baic_activate, 2 },
	{ utc_tel_barring_baic_deactivate, 1 },
	{ utc_fail_tel_barring_baic_deactivate, 2 },
	{ utc_tel_barring_bic_roam_activate, 1 },
	{ utc_fail_tel_barring_bic_roam_activate, 2 },
	{ utc_tel_barring_bic_roam_deactivate, 1 },
	{ utc_fail_tel_barring_bic_roam_deactivate, 2 },
	{ utc_tel_barring_ab_activate, 1 },
	{ utc_fail_tel_barring_ab_activate, 2 },
	{ utc_tel_barring_ab_deactivate, 1 },
	{ utc_fail_tel_barring_ab_deactivate, 2 },
	{ utc_tel_barring_aob_activate, 1 },
	{ utc_fail_tel_barring_aob_activate, 2 },
	{ utc_tel_barring_aob_deactivate, 1 },
	{ utc_fail_tel_barring_aob_deactivate, 2 },
	{ utc_tel_barring_aib_activate, 1 },
	{ utc_fail_tel_barring_aib_activate, 2 },
	{ utc_tel_barring_aib_deactivate, 1 },
	{ utc_fail_tel_barring_aib_deactivate, 2 },
	{ utc_tel_barring_bic_not_sim_activate, 1 },
	{ utc_fail_tel_barring_bic_not_sim_activate, 2 },
	{ utc_tel_barring_bic_not_sim_deactivate, 1 },
	{ utc_fail_tel_barring_bic_not_sim_deactivate, 2 },

	{ utc_tel_barring_baoc_status, 1 },
	{ utc_fail_tel_barring_baoc_status, 2 },
	{ utc_tel_barring_boic_status, 1 },
	{ utc_fail_tel_barring_boic_status, 2 },
	{ utc_tel_barring_boic_not_hc_status, 1 },
	{ utc_fail_tel_barring_boic_not_hc_status, 2 },
	{ utc_tel_barring_baic_status, 1 },
	{ utc_fail_tel_barring_baic_status, 2 },
	{ utc_tel_barring_ab_status, 1 },
	{ utc_fail_tel_barring_ab_status, 2 },
	{ utc_tel_barring_bic_roam_status, 1 },
	{ utc_fail_tel_barring_bic_roam_status, 2 },
	{ utc_tel_barring_ab_status, 1 },
	{ utc_fail_tel_barring_ab_status, 2 },
	{ utc_tel_barring_aob_status, 1 },
	{ utc_fail_tel_barring_aob_status, 2 },
	{ utc_tel_barring_aib_status, 1 },
	{ utc_fail_tel_barring_aib_status, 2 },
	{ utc_tel_barring_bic_not_sim_status, 1 },
	{ utc_fail_tel_barring_bic_not_sim_status, 2 },

	{ utc_tel_forwarding_cfu_register, 1 },
	{ utc_fail_tel_forwarding_cfu_register, 2 },
	{ utc_tel_forwarding_cfu_erasure, 1 },
	{ utc_fail_tel_forwarding_cfu_erasure, 2 },
	{ utc_tel_forwarding_cfb_register, 1 },
	{ utc_fail_tel_forwarding_cfb_register, 2 },
	{ utc_tel_forwarding_cfb_erasure, 1 },
	{ utc_fail_tel_forwarding_cfb_erasure, 2 },
	{ utc_tel_forwarding_cfnry_register, 1 },
	{ utc_fail_tel_forwarding_cfnry_register, 2 },
	{ utc_tel_forwarding_cfnry_erasure, 1 },
	{ utc_fail_tel_forwarding_cfnry_erasure, 2 },
	{ utc_tel_forwarding_cfnrc_register, 1 },
	{ utc_fail_tel_forwarding_cfnrc_register, 2 },
	{ utc_tel_forwarding_cfunrc_erasure, 1 },
	{ utc_fail_tel_forwarding_cfunrc_erasure, 2 },
	{ utc_tel_forwarding_cf_all_register, 1 },
	{ utc_fail_tel_forwarding_cf_all_register, 2 },
	{ utc_tel_forwarding_cf_all_erasure, 1 },
	{ utc_fail_tel_forwarding_cf_all_erasure, 2 },
	{ utc_tel_forwarding_cfc_register, 1 },
	{ utc_fail_tel_forwarding_cfc_register, 2 },
	{ utc_tel_forwarding_cfc_erasure, 1 },
	{ utc_fail_tel_forwarding_cfc_erasure, 2 },

	{ utc_tel_forwarding_cfu_status, 1 },
	{ utc_fail_tel_forwarding_cfu_status, 2 },
	{ utc_tel_forwarding_cfb_status, 1 },
	{ utc_fail_tel_forwarding_cfb_status, 2 },
	{ utc_tel_forwarding_cfnry_status, 1 },
	{ utc_fail_tel_forwarding_cfnry_status, 2 },
	{ utc_tel_forwarding_cfnrc_status, 1 },
	{ utc_fail_tel_forwarding_cfnrc_status, 2 },
	{ utc_tel_forwarding_cf_all_status, 1 },
	{ utc_fail_tel_forwarding_cf_all_status, 2 },
	{ utc_tel_forwarding_cfc_status, 1 },
	{ utc_fail_tel_forwarding_cfc_status, 2 },


	{ utc_tel_waiting_activate, 1 },
	{ utc_fail_tel_waiting_activate, 2 },
	{ utc_tel_waiting_deactivate, 1 },
	{ utc_fail_tel_waiting_deactivate, 2 },

	{ utc_tel_CLIP_status, 1 },
	{ utc_fail_tel_CLIP_status, 2 },
	{ utc_tel_CLIR_status, 1 },
	{ utc_fail_tel_CLIR_status, 2 },
	{ utc_tel_COLP_status, 1 },
	{ utc_fail_tel_COLP_status, 2 },
	{ utc_tel_COLR_status, 1 },
	{ utc_fail_tel_COLR_status, 2 },
	{ utc_tel_CDIP_status, 1 },
	{ utc_fail_tel_CDIP_status, 2 },
	{ utc_tel_CNAP_status, 1 },
	{ utc_fail_tel_CNAP_status, 2 },

	{ utc_tel_CLIP_activate, 1 },
	{ utc_fail_tel_CLIP_activate, 2 },
	{ utc_tel_CLIP_deactivate, 1 },
	{ utc_fail_tel_CLIP_deactivate, 2 },
	{ utc_tel_CLIR_activate, 1 },
	{ utc_fail_tel_CLIR_activate, 2 },
	{ utc_tel_CLIR_deactivate, 1 },
	{ utc_fail_tel_CLIR_deactivate, 2 },
	{ utc_tel_COLP_activate, 1 },
	{ utc_fail_tel_COLP_activate, 2 },
	{ utc_tel_COLP_deactivate, 1 },
	{ utc_fail_tel_COLP_deactivate, 2 },
	{ utc_tel_COLR_activate, 1 },
	{ utc_fail_tel_COLR_activate, 2 },
	{ utc_tel_COLR_deactivate, 1 },
	{ utc_fail_tel_COLR_deactivate, 2 },	
	{ utc_tel_CDIP_activate, 1 },
	{ utc_fail_tel_CDIP_activate, 2 },
	{ utc_tel_CDIP_deactivate, 1 },
	{ utc_fail_tel_CDIP_deactivate, 2 },
	{ utc_tel_CNAP_activate, 1 },
	{ utc_fail_tel_CNAP_activate, 2 },
	{ utc_tel_CNAP_deactivate, 1 },
	{ utc_fail_tel_CNAP_deactivate, 2 },

	/* custom TC */
	{ utc_tel_change_ss_barring_password, 1 },
	{ utc_fail_tel_change_ss_barring_password, 2 },
	{ utc_tel_ss_waiting_status, 1 },
	{ utc_fail_tel_ss_waiting_status, 2 },
	{ utc_tel_ss_init_ussd, 1 },
	{ utc_fail_tel_ss_init_ussd, 2 },
	{ utc_tel_ss_cancel_ussd, 1 },
	{ utc_fail_tel_ss_cancel_ussd, 2 },

	{ NULL, 0 },
};

static void startup (void)
{
	/* start of TC */
	tet_printf ("\n SS TC start");

	handle = tel_init (NULL);
}

static void cleanup (void)
{
	tel_deinit (handle);

	/* end of TC */
	tet_printf ("\n SS TC end");
}

void (*tet_startup) (void) = startup;
void (*tet_cleanup) (void) = cleanup;

