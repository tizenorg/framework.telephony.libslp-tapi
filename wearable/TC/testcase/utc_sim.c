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
#include <ITapiSim.h>
#include <TapiUtility.h>

#include "util_common.h"

TapiHandle *handle;
enum async_state async_flag;


/**
 * tel_get_sim_init_info
 *
 */
static void utc_tel_get_sim_init_info (void)
{
	int ret;
	TelSimCardStatus_t sim_status;
	int card_changed;

	util_init_loop ();

	ret = tel_get_sim_init_info (handle, &sim_status, &card_changed);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_init_info", "Unexpected return");
	}

	dts_pass("tel_get_sim_init_info");
}

static void utc_fail_tel_get_sim_init_info (void)
{
	int ret;
	TelSimCardStatus_t sim_status;
	int card_changed;

	ret = tel_get_sim_init_info (NULL, &sim_status, &card_changed);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_init_info", "Parameter check failed");
	}

	ret = tel_get_sim_init_info (handle, NULL, &card_changed);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_init_info", "Parameter check failed");
	}

	ret = tel_get_sim_init_info (handle, &sim_status, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_init_info", "Parameter check failed");
	}

	ret = tel_get_sim_init_info (handle, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_init_info", "Parameter check failed");
	}

	dts_pass("tel_get_sim_init_info");
}

/**
 * tel_get_sim_type
 *
 */
static void utc_tel_get_sim_type (void)
{
	int ret;
	TelSimCardType_t card_type;

	util_init_loop ();

	ret = tel_get_sim_type (handle, &card_type);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_type", "Unexpected return");
	}

	dts_pass("tel_get_sim_type");
}

static void utc_fail_tel_get_sim_type (void)
{
	int ret;
	TelSimCardType_t card_type;

	ret = tel_get_sim_type (NULL, &card_type);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_type", "Parameter check failed");
	}

	ret = tel_get_sim_type (handle, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_type", "Parameter check failed");
	}

	dts_pass("tel_get_sim_type");
}

/**
 * tel_get_sim_imsi
 *
 */
static void utc_tel_get_sim_imsi (void)
{
	int ret;
	TelSimImsiInfo_t imsi;

	util_init_loop ();

	ret = tel_get_sim_imsi (handle, &imsi);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_imsi", "Unexpected return");
	}

	dts_pass("tel_get_sim_imsi");
}

static void utc_fail_tel_get_sim_imsi (void)
{
	int ret;
	TelSimImsiInfo_t imsi;

	ret = tel_get_sim_imsi (NULL, &imsi);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_imsi", "Parameter check failed");
	}

	ret = tel_get_sim_imsi (handle, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_imsi", "Parameter check failed");
	}

	dts_pass("tel_get_sim_imsi");
}

/**
 * tel_get_sim_ecc
 *
 */
static void utc_tel_get_sim_ecc (void)
{
	int ret;
	TelSimEccList_t ecc;

	util_init_loop ();

	ret = tel_get_sim_ecc (handle, &ecc);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_ecc", "Unexpected return");
	}

	dts_pass("tel_get_sim_ecc");
}

static void utc_fail_tel_get_sim_ecc (void)
{
	int ret;
	TelSimEccList_t ecc;

	ret = tel_get_sim_ecc (NULL, &ecc);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_ecc", "Parameter check failed");
	}

	ret = tel_get_sim_ecc (handle, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_ecc", "Parameter check failed");
	}

	dts_pass("tel_get_sim_ecc");
}

/**
 * tel_set_sim_language
 *
 */
static void on_tel_set_sim_language (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_sim_language", "Callback userdata crashed");
	}
}

static void utc_tel_set_sim_language (void)
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_sim_language (handle, 2, on_tel_set_sim_language, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_sim_language", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_sim_language", "Callback not invoked");
	}

	dts_pass("tel_set_sim_language");
}

static void utc_fail_tel_set_sim_language (void)
{
	int ret;

	ret = tel_set_sim_language (NULL, 0, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sim_language", "Parameter check failed");
	}

	dts_pass("tel_set_sim_language");
}

/**
 * tel_set_sim_callforwarding_info
 *
 */
static void on_tel_set_sim_callforwarding_info (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_sim_callforwarding_info", "Callback userdata crashed");
	}
}

static void utc_tel_set_sim_callforwarding_info (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSimCallForwardingReq_t req_cphs_cf;

	memset (&req_cphs_cf, 0, sizeof(TelSimCallForwardingReq_t));

	req_cphs_cf.b_cphs = 1;
	req_cphs_cf.cf_data_u.cphs_cf.b_line1 = 1;
	req_cphs_cf.cf_data_u.cphs_cf.b_line2 = 0;
	req_cphs_cf.cf_data_u.cphs_cf.b_fax = 1;
	req_cphs_cf.cf_data_u.cphs_cf.b_data = 0;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_sim_callforwarding_info (handle, &req_cphs_cf, on_tel_set_sim_callforwarding_info, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_sim_callforwarding_info", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_sim_callforwarding_info", "Callback not invoked");
	}

	dts_pass("tel_set_sim_callforwarding_info");
}

static void utc_fail_tel_set_sim_callforwarding_info (void)
{
	int ret;
	TelSimCallForwardingReq_t req_cphs_cf;

	memset (&req_cphs_cf, 0, sizeof(TelSimCallForwardingReq_t));

	req_cphs_cf.b_cphs = 1;
	req_cphs_cf.cf_data_u.cphs_cf.b_line1 = 1;
	req_cphs_cf.cf_data_u.cphs_cf.b_line2 = 0;
	req_cphs_cf.cf_data_u.cphs_cf.b_fax = 1;
	req_cphs_cf.cf_data_u.cphs_cf.b_data = 0;

	ret = tel_set_sim_callforwarding_info (NULL, &req_cphs_cf, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sim_callforwarding_info", "Parameter check failed");
	}

	ret = tel_set_sim_callforwarding_info (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sim_callforwarding_info", "Parameter check failed");
	}

	dts_pass("tel_set_sim_callforwarding_info");
}

/**
 * tel_set_sim_messagewaiting_info
 *
 */
static void on_tel_set_sim_messagewaiting_info (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_sim_messagewaiting_info", "Callback userdata crashed");
	}
}

static void utc_tel_set_sim_messagewaiting_info (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSimMessageWaitingReq_t req_mw;

	memset (&req_mw, 0, sizeof(TelSimMessageWaitingReq_t));

	req_mw.b_cphs = 1;
	req_mw.mw_data_u.cphs_mw.b_voice1 = 1;
	req_mw.mw_data_u.cphs_mw.b_voice2 = 0;
	req_mw.mw_data_u.cphs_mw.b_fax = 1;
	req_mw.mw_data_u.cphs_mw.b_data = 0;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_sim_messagewaiting_info (handle, &req_mw, on_tel_set_sim_messagewaiting_info, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_sim_messagewaiting_info", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_sim_messagewaiting_info", "Callback not invoked");
	}

	dts_pass("tel_set_sim_callforwarding_info");
}

static void utc_fail_tel_set_sim_messagewaiting_info (void)
{
	int ret;
	TelSimMessageWaitingReq_t req_mw;

	memset (&req_mw, 0, sizeof(TelSimMessageWaitingReq_t));

	req_mw.b_cphs = 1;
	req_mw.mw_data_u.cphs_mw.b_voice1 = 1;
	req_mw.mw_data_u.cphs_mw.b_voice2 = 0;
	req_mw.mw_data_u.cphs_mw.b_fax = 1;
	req_mw.mw_data_u.cphs_mw.b_data = 0;

	ret = tel_set_sim_messagewaiting_info (NULL, &req_mw, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sim_messagewaiting_info", "Parameter check failed");
	}

	ret = tel_set_sim_messagewaiting_info (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sim_messagewaiting_info", "Parameter check failed");
	}

	dts_pass("tel_set_sim_messagewaiting_info");
}

/**
 * tel_set_sim_mailbox_info
 *
 */
static void on_tel_set_sim_mailbox_info (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_sim_mailbox_info", "Callback userdata crashed");
	}
}

static void utc_tel_set_sim_mailbox_info (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSimMailBoxNumber_t req_mb;

	memset (&req_mb, 0, sizeof(TelSimMailBoxNumber_t));

	req_mb.b_cphs = 1;
	req_mb.rec_index = 1;
	req_mb.profile_num = 1;
	req_mb.mb_type = 1;
	req_mb.alpha_id_max_len = 10;
	strcpy (req_mb.alpha_id, "123456");
	req_mb.ton = 2;
	req_mb.npi = 8;
	strcpy (req_mb.num, "9988776655");

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_sim_mailbox_info (handle, &req_mb, on_tel_set_sim_mailbox_info, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_sim_mailbox_info", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_sim_mailbox_info", "Callback not invoked");
	}

	dts_pass("tel_set_sim_mailbox_info");
}

static void utc_fail_tel_set_sim_mailbox_info (void)
{
	int ret;
	TelSimMailBoxNumber_t req_mb;

	memset (&req_mb, 0, sizeof(TelSimMailBoxNumber_t));

	req_mb.b_cphs = 1;
	req_mb.rec_index = 1;
	req_mb.profile_num = 1;
	req_mb.mb_type = 1;
	req_mb.alpha_id_max_len = 10;
	strcpy (req_mb.alpha_id, "123456");
	req_mb.ton = 2;
	req_mb.npi = 8;
	strcpy (req_mb.num, "9988776655");

	ret = tel_set_sim_mailbox_info (NULL, &req_mb, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sim_mailbox_info", "Parameter check failed");
	}

	ret = tel_set_sim_mailbox_info (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sim_mailbox_info", "Parameter check failed");
	}

	dts_pass("tel_set_sim_mailbox_info");
}

/**
 * tel_req_sim_authentication
 *
 */
static void on_tel_req_sim_authentication (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_sim_mailbox_info", "Callback userdata crashed");
	}
}

static void utc_tel_req_sim_authentication (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSimAuthenticationData_t authentication_data;

	memset (&authentication_data, 0, sizeof(TelSimAuthenticationData_t));

 	authentication_data.auth_type = 1;
	authentication_data.rand_length = 16;
	authentication_data.autn_length = 16;
	strcpy (authentication_data.rand_data, "AAAAAAAAAAAAAAAA");
	strcpy (authentication_data.autn_data, "AAAAAAAAAAAAAAAA");

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_req_sim_authentication (handle, &authentication_data, on_tel_req_sim_authentication, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_req_sim_authentication", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_req_sim_authentication", "Callback not invoked");
	}

	dts_pass("tel_req_sim_authentication");
}

static void utc_fail_tel_req_sim_authentication (void)
{
	int ret;
	TelSimAuthenticationData_t authentication_data;

	memset (&authentication_data, 0, sizeof(TelSimAuthenticationData_t));

 	authentication_data.auth_type = 1;
	authentication_data.rand_length = 16;
	authentication_data.autn_length = 16;
	strcpy (authentication_data.rand_data, "AAAAAAAAAAAAAAAA");
	strcpy (authentication_data.autn_data, "AAAAAAAAAAAAAAAA");

	ret = tel_req_sim_authentication (NULL, &authentication_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_req_sim_authentication", "Parameter check failed");
	}

	ret = tel_req_sim_authentication (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_req_sim_authentication", "Parameter check failed");
	}

	dts_pass("tel_req_sim_authentication");
}

/**
 * tel_verifiy_sim_pins
 *
 */
static void on_tel_verifiy_sim_pins (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_verifiy_sim_pins", "Callback userdata crashed");
	}
}

static void utc_tel_verifiy_sim_pins (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSimSecPw_t pin_data;

	memset (&pin_data, 0, sizeof(TelSimSecPw_t));

	pin_data.type = 0;
	pin_data.pw_len = 4;
	pin_data.pw = calloc(1, pin_data.pw_len);
	strcpy ((char *)pin_data.pw, "1234");

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_verifiy_sim_pins (handle, &pin_data, on_tel_verifiy_sim_pins, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_verifiy_sim_pins", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_verifiy_sim_pins", "Callback not invoked");
	}

	dts_pass("tel_verifiy_sim_pins");
	free(pin_data.pw);
}

static void utc_fail_tel_verifiy_sim_pins (void)
{
	int ret;

	TelSimSecPw_t pin_data;

	memset (&pin_data, 0, sizeof(TelSimSecPw_t));

	pin_data.type = 0;
	pin_data.pw_len = 4;
	pin_data.pw = calloc(1, pin_data.pw_len);
	strcpy ((char *)pin_data.pw, "1234");

	ret = tel_verifiy_sim_pins (NULL, &pin_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verifiy_sim_pins", "Parameter check failed");
	}

	pin_data.type = 2;
	ret = tel_verifiy_sim_pins (handle, &pin_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verifiy_sim_pins", "Parameter check failed");
	}

	pin_data.type = 0;
	pin_data.pw_len = 3;
	ret = tel_verifiy_sim_pins (handle, &pin_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verifiy_sim_pins", "Parameter check failed");
	}

	pin_data.pw_len = 9;
	ret = tel_verifiy_sim_pins (handle, &pin_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verifiy_sim_pins", "Parameter check failed");
	}

	ret = tel_verifiy_sim_pins (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verifiy_sim_pins", "Parameter check failed");
	}

	dts_pass("tel_verifiy_sim_pins");
	free(pin_data.pw);
}

/**
 * tel_verify_sim_puks
 *
 */
static void on_tel_verify_sim_puks (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_verify_sim_puks", "Callback userdata crashed");
	}
}

static void utc_tel_verify_sim_puks (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSimSecPw_t puk_data;
	TelSimSecPw_t new_pin_data;

	memset (&puk_data, 0, sizeof(TelSimSecPw_t));
	memset (&new_pin_data, 0, sizeof(TelSimSecPw_t));

	puk_data.type = 2;
	puk_data.pw_len = 5;
	puk_data.pw = calloc(1, puk_data.pw_len);
	strcpy ((char *)puk_data.pw, "22222");

	new_pin_data.type = 0;
	new_pin_data.pw_len = 4;
	new_pin_data.pw = calloc(1, new_pin_data.pw_len);
	strcpy ((char *)new_pin_data.pw, "1111");

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_verify_sim_puks (handle, &puk_data, &new_pin_data, on_tel_verify_sim_puks, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_verify_sim_puks", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_verify_sim_puks", "Callback not invoked");
	}

	dts_pass("tel_verify_sim_puks");
	free(puk_data.pw);
	free(new_pin_data.pw);
}

static void utc_fail_tel_verify_sim_puks (void)
{
	int ret;
	TelSimSecPw_t puk_data;
	TelSimSecPw_t new_pin_data;

	memset (&puk_data, 0, sizeof(TelSimSecPw_t));
	memset (&new_pin_data, 0, sizeof(TelSimSecPw_t));

	puk_data.type = 2;
	puk_data.pw_len = 5;
	puk_data.pw = calloc(1, puk_data.pw_len);
	strcpy ((char *)puk_data.pw, "22222");

	new_pin_data.type = 0;
	new_pin_data.pw_len = 4;
	new_pin_data.pw = calloc(1, new_pin_data.pw_len);
	strcpy ((char *)new_pin_data.pw, "1111");

	ret = tel_verify_sim_puks (NULL, &puk_data, &new_pin_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verify_sim_puks", "Parameter check failed");
	}
	ret = tel_verify_sim_puks (NULL, NULL , &new_pin_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verify_sim_puks", "Parameter check failed");
	}
	ret = tel_verify_sim_puks (NULL, &puk_data, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verify_sim_puks", "Parameter check failed");
	}
	ret = tel_verify_sim_puks (NULL, NULL, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verify_sim_puks", "Parameter check failed");
	}
	puk_data.type = 0;
	ret = tel_verify_sim_puks (NULL, &puk_data, &new_pin_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verify_sim_puks", "Parameter check failed");
	}
	puk_data.type = 2;
	new_pin_data.type = 2;
	ret = tel_verify_sim_puks (NULL, &puk_data, &new_pin_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verify_sim_puks", "Parameter check failed");
	}
	puk_data.type = 2;
	new_pin_data.type = 0;
	puk_data.pw_len = 3;
	ret = tel_verify_sim_puks (NULL, &puk_data, &new_pin_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verify_sim_puks", "Parameter check failed");
	}
	puk_data.pw_len = 9;
	ret = tel_verify_sim_puks (NULL, &puk_data, &new_pin_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verify_sim_puks", "Parameter check failed");
	}
	new_pin_data.pw_len = 3;
	ret = tel_verify_sim_puks (NULL, &puk_data, &new_pin_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verify_sim_puks", "Parameter check failed");
	}
	new_pin_data.pw_len = 9;
	ret = tel_verify_sim_puks (NULL, &puk_data, &new_pin_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verify_sim_puks", "Parameter check failed");
	}
	puk_data.pw_len = 5;
	new_pin_data.pw_len = 5;
	puk_data.pw = NULL;
	ret = tel_verify_sim_puks (NULL, &puk_data, &new_pin_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verify_sim_puks", "Parameter check failed");
	}
	new_pin_data.pw = NULL;
	ret = tel_verify_sim_puks (NULL, &puk_data, &new_pin_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_verify_sim_puks", "Parameter check failed");
	}

	dts_pass("tel_verify_sim_puks");
	free(puk_data.pw);
	free(new_pin_data.pw);
}

/**
 * tel_change_sim_pins
 *
 */
static void on_tel_change_sim_pins (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_change_sim_pins", "Callback userdata crashed");
	}
}

static void utc_tel_change_sim_pins (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSimSecPw_t old_pin;
	TelSimSecPw_t new_pin;

	memset (&old_pin, 0, sizeof(TelSimSecPw_t));
	memset (&new_pin, 0, sizeof(TelSimSecPw_t));

	old_pin.type = 0;
	old_pin.pw_len = 4;
	old_pin.pw = calloc(1, old_pin.pw_len);
	strcpy ((char *)old_pin.pw, "1111");

	new_pin.type = 0;
	new_pin.pw_len = 4;
	new_pin.pw = calloc(1, new_pin.pw_len);
	strcpy ((char *)new_pin.pw, "2222");

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_change_sim_pins (handle, &old_pin, &new_pin, on_tel_change_sim_pins, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_change_sim_pins", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_change_sim_pins", "Callback not invoked");
	}

	dts_pass("tel_change_sim_pins");
	free(old_pin.pw);
	free(new_pin.pw);
}

static void utc_fail_tel_change_sim_pins (void)
{
	int ret;
	TelSimSecPw_t old_pin;
	TelSimSecPw_t new_pin;

	memset (&old_pin, 0, sizeof(TelSimSecPw_t));
	memset (&new_pin, 0, sizeof(TelSimSecPw_t));

	old_pin.type = 0;
	old_pin.pw_len = 4;
	old_pin.pw = calloc(1, old_pin.pw_len);
	strcpy ((char *)old_pin.pw, "1111");

	new_pin.type = 0;
	new_pin.pw_len = 4;
	new_pin.pw = calloc(1, new_pin.pw_len);
	strcpy ((char *)new_pin.pw, "2222");

	ret = tel_change_sim_pins (NULL, &old_pin, &new_pin, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_change_sim_pins", "Parameter check failed");
	}
	ret = tel_change_sim_pins (NULL, NULL , &new_pin, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_change_sim_pins", "Parameter check failed");
	}
	ret = tel_change_sim_pins (NULL, &old_pin, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_change_sim_pins", "Parameter check failed");
	}
	ret = tel_change_sim_pins (NULL, NULL, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_change_sim_pins", "Parameter check failed");
	}
	old_pin.type = 2;
	ret = tel_change_sim_pins (NULL, &old_pin, &new_pin, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_change_sim_pins", "Parameter check failed");
	}
	old_pin.type = 0;
	new_pin.type = 2;
	ret = tel_change_sim_pins (NULL, &old_pin, &new_pin, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_change_sim_pins", "Parameter check failed");
	}
	old_pin.type = 0;
	new_pin.type = 0;
	old_pin.pw_len = 3;
	ret = tel_change_sim_pins (NULL, &old_pin, &new_pin, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_change_sim_pins", "Parameter check failed");
	}
	old_pin.pw_len = 9;
	ret = tel_change_sim_pins (NULL, &old_pin, &new_pin, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_change_sim_pins", "Parameter check failed");
	}
	new_pin.pw_len = 3;
	ret = tel_change_sim_pins (NULL, &old_pin, &new_pin, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_change_sim_pins", "Parameter check failed");
	}
	new_pin.pw_len = 9;
	ret = tel_change_sim_pins (NULL, &old_pin, &new_pin, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_change_sim_pins", "Parameter check failed");
	}
	old_pin.pw_len = 4;
	new_pin.pw_len = 4;
	old_pin.pw = NULL;
	ret = tel_change_sim_pins (NULL, &old_pin, &new_pin, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_change_sim_pins", "Parameter check failed");
	}
	new_pin.pw = NULL;
	ret = tel_change_sim_pins (NULL, &old_pin, &new_pin, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_change_sim_pins", "Parameter check failed");
	}

	dts_pass("tel_change_sim_pins");
	free(old_pin.pw);
	free(new_pin.pw);
}

/**
 * tel_disable_sim_facility
 *
 */
static void on_tel_disable_sim_facility (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_disable_sim_facility", "Callback userdata crashed");
	}
}

static void utc_tel_disable_sim_facility (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSimFacilityPw_t pw;

	memset (&pw, 0, sizeof(TelSimFacilityPw_t));

 	pw.lock_type = 1;
	pw.pw_len = 5;
	pw.pw = calloc(1, pw.pw_len);
	strcpy ((char *)pw.pw, "12345");

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_disable_sim_facility (handle, &pw, on_tel_disable_sim_facility, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_disable_sim_facility", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_disable_sim_facility", "Callback not invoked");
	}

	dts_pass("tel_disable_sim_facility");
	free(pw.pw);
}

static void utc_fail_tel_disable_sim_facility (void)
{
	int ret;
	TelSimFacilityPw_t pw;

	memset (&pw, 0, sizeof(TelSimFacilityPw_t));

 	pw.lock_type = 1;
	pw.pw_len = 5;
	pw.pw = calloc(1, pw.pw_len);
	strcpy ((char *)pw.pw, "12345");

	ret = tel_disable_sim_facility (NULL, &pw, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_disable_sim_facility", "Parameter check failed");
	}

	ret = tel_disable_sim_facility (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_disable_sim_facility", "Parameter check failed");
	}

	pw.lock_type = 0;
	ret = tel_disable_sim_facility (handle, &pw, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_disable_sim_facility", "Parameter check failed");
	}

	pw.lock_type = 9;
	ret = tel_disable_sim_facility (handle, &pw, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_disable_sim_facility", "Parameter check failed");
	}

	pw.lock_type = 1;
	pw.pw = NULL;
	ret = tel_disable_sim_facility (handle, &pw, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_disable_sim_facility", "Parameter check failed");
	}

	dts_pass("tel_disable_sim_facility");
	free(pw.pw);
}

/**
 * tel_enable_sim_facility
 *
 */
static void on_tel_enable_sim_facility (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_enable_sim_facility", "Callback userdata crashed");
	}
}

static void utc_tel_enable_sim_facility (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSimFacilityPw_t pw;

	memset (&pw, 0, sizeof(TelSimFacilityPw_t));

 	pw.lock_type = 1;
	pw.pw_len = 5;
	pw.pw = calloc(1, pw.pw_len);
	strcpy ((char *)pw.pw, "12345");

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_enable_sim_facility (handle, &pw, on_tel_enable_sim_facility, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_enable_sim_facility", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_enable_sim_facility", "Callback not invoked");
	}

	dts_pass("tel_enable_sim_facility");
	free(pw.pw);
}

static void utc_fail_tel_enable_sim_facility (void)
{
	int ret;
	TelSimFacilityPw_t pw;

	memset (&pw, 0, sizeof(TelSimFacilityPw_t));

 	pw.lock_type = 1;
	pw.pw_len = 5;
	pw.pw = calloc(1, pw.pw_len);
	strcpy ((char *)pw.pw, "12345");

	ret = tel_enable_sim_facility (NULL, &pw, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_enable_sim_facility", "Parameter check failed");
	}

	ret = tel_enable_sim_facility (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_enable_sim_facility", "Parameter check failed");
	}

	pw.lock_type = 0;
	ret = tel_enable_sim_facility (handle, &pw, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_enable_sim_facility", "Parameter check failed");
	}

	pw.lock_type = 9;
	ret = tel_enable_sim_facility (handle, &pw, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_enable_sim_facility", "Parameter check failed");
	}

	pw.lock_type = 1;
	pw.pw = NULL;
	ret = tel_enable_sim_facility (handle, &pw, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_enable_sim_facility", "Parameter check failed");
	}

	dts_pass("tel_enable_sim_facility");
	free(pw.pw);
}

/**
 * tel_get_sim_facility
 *
 */
static void on_tel_get_sim_facility (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_get_sim_facility", "Callback userdata crashed");
	}
}

static void utc_tel_get_sim_facility (void)
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_get_sim_facility (handle, 3, on_tel_get_sim_facility, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_facility", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_get_sim_facility", "Callback not invoked");
	}

	dts_pass("tel_get_sim_facility");
}

static void utc_fail_tel_get_sim_facility (void)
{
	int ret;

	ret = tel_get_sim_facility (NULL, 3, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_facility", "Parameter check failed");
	}

	ret = tel_get_sim_facility (handle, 0, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_facility", "Parameter check failed");
	}

	ret = tel_get_sim_facility (handle, 9, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_facility", "Parameter check failed");
	}

	dts_pass("tel_get_sim_facility");
}

/**
 * tel_get_sim_lock_info
 *
 */
static void on_tel_get_sim_lock_info (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_get_sim_lock_info", "Callback userdata crashed");
	}
}

static void utc_tel_get_sim_lock_info (void)
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_get_sim_lock_info (handle, 3, on_tel_get_sim_lock_info, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_lock_info", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_get_sim_lock_info", "Callback not invoked");
	}

	dts_pass("tel_get_sim_lock_info");
}

static void utc_fail_tel_get_sim_lock_info (void)
{
	int ret;

	ret = tel_get_sim_lock_info (NULL, 3, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_facility", "Parameter check failed");
	}

	ret = tel_get_sim_lock_info (handle, 0, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_lock_info", "Parameter check failed");
	}

	ret = tel_get_sim_lock_info (handle, 9, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sim_lock_info", "Parameter check failed");
	}

	dts_pass("tel_get_sim_lock_info");
}

/**
 * tel_req_sim_apdu
 *
 */
static void on_tel_req_sim_apdu (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_req_sim_apdu", "Callback userdata crashed");
	}
}

static void utc_tel_req_sim_apdu (void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSimApdu_t apdu_data;

	memset (&apdu_data, 0, sizeof(TelSimApdu_t));

	apdu_data.apdu_len = 7;
	apdu_data.apdu = calloc(1, apdu_data.apdu_len);
	strcpy ((char *)apdu_data.apdu, "a0a40000026f02");

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_req_sim_apdu (handle, &apdu_data, on_tel_req_sim_apdu, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_req_sim_apdu", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_req_sim_apdu", "Callback not invoked");
	}

	dts_pass("tel_req_sim_apdu");
	free(apdu_data.apdu);
}

static void utc_fail_tel_req_sim_apdu (void)
{
	int ret;
	TelSimApdu_t apdu_data;

	memset (&apdu_data, 0, sizeof(TelSimApdu_t));

	apdu_data.apdu_len = 7;
	apdu_data.apdu = calloc(1, apdu_data.apdu_len);
	strcpy ((char *)apdu_data.apdu, "a0a40000026f02");

	ret = tel_req_sim_apdu (NULL, &apdu_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_req_sim_apdu", "Parameter check failed");
	}

	ret = tel_req_sim_apdu (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_req_sim_apdu", "Parameter check failed");
	}

	apdu_data.apdu = NULL;
	ret = tel_req_sim_apdu (handle, &apdu_data, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_req_sim_apdu", "Parameter check failed");
	}

	dts_pass("tel_req_sim_apdu");
	free(apdu_data.apdu);
}

/**
 * Generate default TC for no-additional-parameter type API
 *
 */
DO(tel_get_sim_iccid)
DO(tel_get_sim_language)
DO(tel_get_sim_callforwarding_info)
DO(tel_get_sim_messagewaiting_info)
DO(tel_get_sim_mailbox_info)
DO(tel_get_sim_cphs_info)
DO(tel_get_sim_service_table)
DO(tel_get_sim_msisdn)
DO(tel_get_sim_oplmnwact)
DO(tel_get_sim_spn)
DO(tel_get_sim_cphs_netname)
DO(tel_req_sim_atr)

struct tet_testlist tet_testlist[] = {
	/* generated TC */
	{ utc_tel_get_sim_iccid, 1 },
	{ utc_fail_tel_get_sim_iccid, 2 },
	{ utc_tel_get_sim_language, 1 },
	{ utc_fail_tel_get_sim_language, 2 },
	{ utc_tel_get_sim_callforwarding_info, 1 },
	{ utc_fail_tel_get_sim_callforwarding_info, 2 },
	{ utc_tel_get_sim_messagewaiting_info, 1 },
	{ utc_fail_tel_get_sim_messagewaiting_info, 2 },
	{ utc_tel_get_sim_mailbox_info, 1 },
	{ utc_fail_tel_get_sim_mailbox_info, 2 },
	{ utc_tel_get_sim_cphs_info, 1 },
	{ utc_fail_tel_get_sim_cphs_info, 2 },
	{ utc_tel_get_sim_service_table, 1 },
	{ utc_fail_tel_get_sim_service_table, 2 },
	{ utc_tel_get_sim_msisdn, 1 },
	{ utc_fail_tel_get_sim_msisdn, 2 },
	{ utc_tel_get_sim_oplmnwact, 1 },
	{ utc_fail_tel_get_sim_oplmnwact, 2 },
	{ utc_tel_get_sim_spn, 1 },
	{ utc_fail_tel_get_sim_spn, 2 },
	{ utc_tel_get_sim_cphs_netname, 1 },
	{ utc_fail_tel_get_sim_cphs_netname, 2 },
	{ utc_tel_req_sim_atr, 1 },
	{ utc_fail_tel_req_sim_atr, 2 },
	/* custom TC */
	{ utc_tel_get_sim_init_info, 1 },
	{ utc_fail_tel_get_sim_init_info, 2 },
	{ utc_tel_get_sim_type, 1 },
	{ utc_fail_tel_get_sim_type, 2 },
	{ utc_tel_get_sim_imsi, 1 },
	{ utc_fail_tel_get_sim_imsi, 2 },
	{ utc_tel_get_sim_ecc, 1 },
	{ utc_fail_tel_get_sim_ecc, 2 },
	{ utc_tel_set_sim_language, 1 },
	{ utc_fail_tel_set_sim_language, 2 },
	{ utc_tel_set_sim_callforwarding_info, 1 },
	{ utc_fail_tel_set_sim_callforwarding_info, 2 },
	{ utc_tel_set_sim_messagewaiting_info, 1 },
	{ utc_fail_tel_set_sim_messagewaiting_info, 2 },
	{ utc_tel_set_sim_mailbox_info, 1 },
	{ utc_fail_tel_set_sim_mailbox_info, 2 },
	{ utc_tel_req_sim_authentication, 1 },
	{ utc_fail_tel_req_sim_authentication, 2 },
	{ utc_tel_verifiy_sim_pins, 1 },
	{ utc_fail_tel_verifiy_sim_pins, 2 },
	{ utc_tel_verify_sim_puks, 1 },
	{ utc_fail_tel_verify_sim_puks, 2 },
	{ utc_tel_change_sim_pins, 1 },
	{ utc_fail_tel_change_sim_pins, 2 },
	{ utc_tel_disable_sim_facility, 1 },
	{ utc_fail_tel_disable_sim_facility, 2 },
	{ utc_tel_enable_sim_facility, 1 },
	{ utc_fail_tel_enable_sim_facility, 2 },
	{ utc_tel_get_sim_facility, 1 },
	{ utc_fail_tel_get_sim_facility, 2 },
	{ utc_tel_get_sim_lock_info, 1 },
	{ utc_fail_tel_get_sim_lock_info, 2 },
	{ utc_tel_req_sim_apdu, 1 },
	{ utc_fail_tel_req_sim_apdu, 2 },
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
