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
#include <TelSms.h>

#include <tapi_common.h>
#include <ITapiNetText.h>
#include <TapiUtility.h>

#include "util_common.h"

TapiHandle *handle;
enum async_state async_flag;

/**
 * tel_send_sms
 *
 */
static void on_tel_send_sms(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_send_sms", "Callback userdata crashed");
	}
}

static void utc_tel_send_sms(void)
{
	int ret;
	int value = 0xC0FFEE;

	TelSmsDatapackageInfo_t *pDataPackage = NULL;

	char *tpdu = "TEST SMS";
	unsigned char sca[TAPI_SIM_SMSP_ADDRESS_LEN];
	int sca_length;

	pDataPackage = malloc(sizeof(TelSmsDatapackageInfo_t));
	memset (pDataPackage, 0x0, sizeof(TelSmsDatapackageInfo_t));

	sca_length = 0x05;
	sca[0] = 0x89;
	sca[1] = 0x54;
	sca[2] = 0x80;
	sca[3] = 0x07;
	sca[4] = 0x10;

	memcpy(pDataPackage->Sca, sca, sca_length);
	pDataPackage->MsgLength = strlen(tpdu);
	memcpy(pDataPackage->szData, tpdu, pDataPackage->MsgLength);

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_send_sms(handle, pDataPackage, 0, on_tel_send_sms, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_send_sms", "Unexpected return");
	}

	free(tpdu);
	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_send_sms", "Callback not invoked");
	}

	dts_pass("tel_send_sms");
}

static void utc_fail_tel_send_sms(void)
{
	int ret;

	ret = tel_send_sms (NULL, NULL, 0, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_send_sms", "Parameter check failed");
	}

	ret = tel_send_sms (handle, NULL, 0, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_send_sms", "Parameter check failed");
	}

	dts_pass("tel_send_sms");
}

/**
 * tel_read_sms_in_sim
 *
 */
static void on_tel_read_sms_in_sim(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_read_sms_in_sim", "Callback userdata crashed");
	}
}

static void utc_tel_read_sms_in_sim(void)
{
	int ret;
	int value = 0xC0FFEE;
	int index = 1;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_read_sms_in_sim (handle, index, on_tel_read_sms_in_sim, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_read_sms_in_sim", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_read_sms_in_sim", "Callback not invoked");
	}

	dts_pass("tel_read_sms_in_sim");
}

static void utc_fail_tel_read_sms_in_sim(void)
{
	int ret;

	ret = tel_read_sms_in_sim(NULL, -1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_read_sms_in_sim", "Parameter check failed");
	}

	ret = tel_read_sms_in_sim(handle, 256, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_read_sms_in_sim", "Parameter check failed");
	}

	dts_pass("tel_read_sms_in_sim");
}

/**
 * tel_write_sms_in_sim
 *
 */
static void on_tel_write_sms_in_sim(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_write_sms_in_sim", "Callback userdata crashed");
	}
}

static void utc_tel_write_sms_in_sim(void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSmsData_t *pWriteData;
	unsigned char sca[TAPI_SIM_SMSP_ADDRESS_LEN];
	char *tpdu = "WRITE SMS";
	int sca_length;
	pWriteData->SimIndex = 1;
	pWriteData->MsgStatus = TAPI_NETTEXT_STATUS_READ;

	sca_length = 0x05;
	sca[0] = 0x89;
	sca[1] = 0x54;
	sca[2] = 0x80;
	sca[3] = 0x07;
	sca[4] = 0x10;

	pWriteData->SmsData.MsgLength = strlen(tpdu);

	memcpy(pWriteData->SmsData.Sca, sca, sca_length);
	memcpy(pWriteData->SmsData.szData, tpdu, pWriteData->SmsData.MsgLength);

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_write_sms_in_sim(handle, pWriteData, on_tel_write_sms_in_sim, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_write_sms_in_sim", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_write_sms_in_sim", "Callback not invoked");
	}

	dts_pass("tel_write_sms_in_sim");
}

static void utc_fail_tel_write_sms_in_sim(void)
{
	int ret;

	ret = tel_write_sms_in_sim(NULL, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_write_sms_in_sim", "Parameter check failed");
	}

	ret = tel_write_sms_in_sim(handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_write_sms_in_sim", "Parameter check failed");
	}

	dts_pass("tel_write_sms_in_sim");
}

/**
 * tel_delete_sms_in_sim
 *
 */
static void on_tel_delete_sms_in_sim(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_delete_sms_in_sim", "Callback userdata crashed");
	}
}

static void utc_tel_delete_sms_in_sim(void)
{
	int ret;
	int value = 0xC0FFEE;
	int index = 1;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_delete_sms_in_sim(handle, index, on_tel_delete_sms_in_sim, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_delete_sms_in_sim", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_delete_sms_in_sim", "Callback not invoked");
	}

	dts_pass("tel_delete_sms_in_sim");
}

static void utc_fail_tel_delete_sms_in_sim(void)
{
	int ret;

	ret = tel_delete_sms_in_sim (NULL, -2, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_delete_sms_in_sim", "Parameter check failed");
	}

	ret = tel_delete_sms_in_sim (handle, 256, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_delete_sms_in_sim", "Parameter check failed");
	}

	dts_pass("tel_delete_sms_in_sim");
}

/**
 * tel_get_sms_sca
 *
 */
static void on_tel_get_sms_sca(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_get_sms_sca", "Callback userdata crashed");
	}
}

static void utc_tel_get_sms_sca(void)
{
	int ret;
	int value = 0xC0FFEE;
	int index = 1;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_get_sms_sca(handle, index, on_tel_get_sms_sca, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_get_sms_sca", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_get_sms_sca", "Callback not invoked");
	}

	dts_pass("tel_get_sms_sca");
}

static void utc_fail_tel_get_sms_sca(void)
{
	int ret;

	ret = tel_get_sms_sca(NULL, -1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sms_sca", "Parameter check failed");
	}

	ret = tel_get_sms_sca(handle, 256, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sms_sca", "Parameter check failed");
	}


	dts_pass("tel_get_sms_sca");
}

/**
 * tel_set_sms_sca
 *
 */
static void on_tel_set_sms_sca(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_sms_sca", "Callback userdata crashed");
	}
}

static void utc_tel_set_sms_sca(void)
{
	int ret;
	int value = 0xC0FFEE;
	int index = 1;
	TelSmsAddressInfo_t *sca = NULL;

	sca->DialNumLen = 0x5;
	sca->Npi = TAPI_SIM_NPI_ISDN_TEL;
	sca->Ton = TAPI_SIM_TON_INTERNATIONAL;
	sca->szDiallingNum[0] = 0x89;
	sca->szDiallingNum[1] = 0x54;
	sca->szDiallingNum[2] = 0x80;
	sca->szDiallingNum[3] = 0x07;
	sca->szDiallingNum[4] = 0x10;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_sms_sca(handle, sca, index, on_tel_set_sms_sca, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_sca", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_sms_sca", "Callback not invoked");
	}

	dts_pass("tel_set_sms_sca");
}

static void utc_fail_tel_set_sms_sca(void)
{
	int ret;

	ret = tel_set_sms_sca(NULL, NULL, -1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_sca", "Parameter check failed");
	}

	ret = tel_set_sms_sca(handle, NULL, -1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_sca", "Parameter check failed");
	}

	dts_pass("tel_set_sms_sca");
}

/**
 * tel_set_sms_cb_config
 *
 */
static void on_tel_set_sms_cb_config(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_sms_cb_config", "Callback userdata crashed");
	}
}

static void utc_tel_set_sms_cb_config(void)
{
	int ret;
	int value = 0xC0FFEE;
	int i;
	TelSmsCbConfig_t *pCBConfig = NULL;
	pCBConfig->CBEnabled = 0x01;
	pCBConfig->Net3gppType = 0x01;
	pCBConfig->MsgIdMaxCount = 0x10;
	pCBConfig->MsgIdRangeCount = 0x05;

	for (i = 0; i < pCBConfig->MsgIdRangeCount; i++) {
		pCBConfig->MsgIDs[i].Net3gpp.FromMsgId = 0x01;
		pCBConfig->MsgIDs[i].Net3gpp.ToMsgId = 0x02;
		pCBConfig->MsgIDs[i].Net3gpp.Selected = 0x01;
	}
	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_sms_cb_config(handle, pCBConfig, on_tel_set_sms_cb_config, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_cb_config", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_sms_cb_config", "Callback not invoked");
	}

	dts_pass("tel_set_sms_cb_config");
}

static void utc_fail_tel_set_sms_cb_config(void)
{
	int ret;

	ret = tel_set_sms_cb_config(NULL, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_cb_config", "Parameter check failed");
	}

	ret = tel_set_sms_cb_config(handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_cb_config", "Parameter check failed");
	}

	dts_pass("tel_set_sms_cb_config");
}

/**
 * tel_set_sms_memory_status
 *
 */
static void on_tel_set_sms_memory_status(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_sms_memory_status", "Callback userdata crashed");
	}
}

static void utc_tel_set_sms_memory_status(void)
{
	int ret;
	int value = 0xC0FFEE;
	int memory_available = 2;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_sms_memory_status(handle, memory_available, on_tel_set_sms_memory_status, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_memory_status", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_sms_memory_status", "Callback not invoked");
	}

	dts_pass("tel_set_sms_memory_status");
}

static void utc_fail_tel_set_sms_memory_status(void)
{
	int ret;

	ret = tel_set_sms_memory_status(NULL, -1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_memory_status", "Parameter check failed");
	}

	ret = tel_set_sms_memory_status(handle, -1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_memory_status", "Parameter check failed");
	}

	ret = tel_set_sms_memory_status(handle, 4, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_memory_status", "Parameter check failed");
	}

	dts_pass("tel_set_sms_memory_status");
}

/**
 * tel_set_sms_preferred_bearer
 *
 */
static void on_tel_set_sms_preferred_bearer(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_sms_preferred_bearer", "Callback userdata crashed");
	}
}

static void utc_tel_set_sms_preferred_bearer(void)
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_sms_preferred_bearer(handle, TAPI_NETTEXT_BEARER_PS_ONLY, on_tel_set_sms_preferred_bearer, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_preferred_bearer", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_sms_preferred_bearer", "Callback not invoked");
	}

	dts_pass("tel_set_sms_preferred_bearer");
}

static void utc_fail_tel_set_sms_preferred_bearer(void)
{
	int ret;

	ret = tel_set_sms_preferred_bearer(NULL, -1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_preferred_bearer", "Parameter check failed");
	}

	ret = tel_set_sms_preferred_bearer(handle, -1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_preferred_bearer", "Parameter check failed");
	}
	dts_pass("tel_set_sms_preferred_bearer");
}

/**
 * tel_send_sms_deliver_report
 *
 */
static void on_tel_send_sms_deliver_report(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_send_sms_deliver_report", "Callback userdata crashed");
	}
}

static void utc_tel_send_sms_deliver_report(void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSmsDatapackageInfo_t *pDataPackage = NULL;

	char *tpdu = "TEST SMS";
	unsigned char sca[TAPI_SIM_SMSP_ADDRESS_LEN];
	int sca_length;

	pDataPackage = malloc(sizeof(TelSmsDatapackageInfo_t));
	memset (pDataPackage, 0x0, sizeof(TelSmsDatapackageInfo_t));

	sca_length = 0x05;
	sca[0] = 0x89;
	sca[1] = 0x54;
	sca[2] = 0x80;
	sca[3] = 0x07;
	sca[4] = 0x10;

	memcpy(pDataPackage->Sca, sca, sca_length);
	pDataPackage->MsgLength = strlen(tpdu);
	memcpy(pDataPackage->szData, tpdu, pDataPackage->MsgLength);


	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_send_sms_deliver_report(handle, pDataPackage, TAPI_NETTEXT_SENDSMS_SUCCESS, on_tel_send_sms_deliver_report, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_send_sms_deliver_report", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_send_sms_deliver_report", "Callback not invoked");
	}

	dts_pass("tel_send_sms_deliver_report");
}

static void utc_fail_tel_send_sms_deliver_report(void)
{
	int ret;

	ret = tel_send_sms_deliver_report(NULL, NULL, -1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_send_sms_deliver_report", "Parameter check failed");
	}

	dts_pass("tel_send_sms_deliver_report");
}

/**
 * tel_set_sms_message_status
 *
 */
static void on_tel_set_sms_message_status(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_sms_message_status", "Callback userdata crashed");
	}
}

static void utc_tel_set_sms_message_status(void)
{
	int ret;
	int value = 0xC0FFEE;
	int index = 1;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_sms_message_status(handle, index, TAPI_NETTEXT_STATUS_READ, on_tel_set_sms_message_status, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_message_status", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_sms_message_status", "Callback not invoked");
	}

	dts_pass("tel_set_sms_message_status");
}

static void utc_fail_tel_set_sms_message_status(void)
{
	int ret;

	ret = tel_set_sms_message_status(NULL, -2, -1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_message_status", "Parameter check failed");
	}

	dts_pass("tel_set_sms_message_status");
}

/**
 * tel_get_sms_parameters
 *
 */
static void on_tel_get_sms_parameters(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_get_sms_parameters", "Callback userdata crashed");
	}
}

static void utc_tel_get_sms_parameters(void)
{
	int ret;
	int value = 0xC0FFEE;
	int index = 1;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_get_sms_parameters(handle, index, on_tel_get_sms_parameters, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_get_sms_parameters", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_get_sms_parameters", "Callback not invoked");
	}

	dts_pass("tel_get_sms_parameters");
}

static void utc_fail_tel_get_sms_parameters(void)
{
	int ret;

	ret = tel_get_sms_parameters(NULL, -1, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sms_parameters", "Parameter check failed");
	}

	ret = tel_get_sms_parameters(handle, 256, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_sms_parameters", "Parameter check failed");
	}

	dts_pass("tel_get_sms_parameters");
}

/**
 * tel_set_sms_parameters
 *
 */
static void on_tel_set_sms_parameters(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_set_sms_parameters", "Callback userdata crashed");
	}
}

static void utc_tel_set_sms_parameters(void)
{
	int ret;
	int value = 0xC0FFEE;
	TelSmsParams_t *pSmsSetParameters = NULL;

	char* name = "airtel";
	char* num = "0103001408";
	char* sca = "9845087001";

	pSmsSetParameters->RecordIndex = 0x00;
	pSmsSetParameters->RecordLen = 31;
	pSmsSetParameters->AlphaIdLen = 3;
	memcpy (&pSmsSetParameters->szAlphaId, name, strlen (name));

	pSmsSetParameters->ParamIndicator = 0xe0;
	pSmsSetParameters->TpDestAddr.DialNumLen = 10;
	pSmsSetParameters->TpDestAddr.Ton = 1;
	pSmsSetParameters->TpDestAddr.Npi = 1;

	pSmsSetParameters->TpSvcCntrAddr.DialNumLen = 10;
	pSmsSetParameters->TpSvcCntrAddr.Ton = 1;
	pSmsSetParameters->TpSvcCntrAddr.Npi = 1;

	memcpy (pSmsSetParameters->TpDestAddr.szDiallingNum, num, strlen (num));
	memcpy (pSmsSetParameters->TpSvcCntrAddr.szDiallingNum, sca, strlen (sca));
	pSmsSetParameters->TpProtocolId = 3;
	pSmsSetParameters->TpDataCodingScheme = 2;
	pSmsSetParameters->TpValidityPeriod = 1;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_set_sms_parameters(handle, pSmsSetParameters, on_tel_set_sms_parameters, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_parameters", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_set_sms_parameters", "Callback not invoked");
	}

	dts_pass("tel_set_sms_parameters");
}

static void utc_fail_tel_set_sms_parameters(void)
{
	int ret;

	ret = tel_set_sms_parameters(NULL, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_parameters", "Parameter check failed");
	}

	dts_pass("tel_set_sms_parameters");
}

static void utc_tel_check_sms_device_status(void)
{
	int ret;
	int readyStatus;
	
	ret = tel_check_sms_device_status(handle, &readyStatus);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_parameters", "Unexpected return");
	}

	dts_pass("tel_set_sms_parameters");
}

static void utc_fail_tel_check_sms_device_status(void)
{
	int ret;

	ret = tel_check_sms_device_status(NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_set_sms_parameters", "Parameter check failed");
	}

	dts_pass("tel_set_sms_parameters");
}


/**
 * Generate default TC for no-additional-parameter type API
 *
 */
DO(tel_get_sms_count)
DO(tel_get_sms_cb_config)
DO(tel_get_sms_preferred_bearer)
DO(tel_get_sms_parameter_count)

struct tet_testlist tet_testlist[] = {
	/* generated TC */
	{ utc_tel_get_sms_count, 1 },
	{ utc_fail_tel_get_sms_count, 2 },
	{ utc_tel_get_sms_cb_config, 1 },
	{ utc_fail_tel_get_sms_cb_config, 2 },
	{ utc_tel_get_sms_preferred_bearer, 1 },
	{ utc_fail_tel_get_sms_preferred_bearer, 2 },
	{ utc_tel_get_sms_parameter_count, 1 },
	{ utc_fail_tel_get_sms_parameter_count, 2 },

	/* custom TC */
	{ utc_tel_send_sms, 1 },
	{ utc_fail_tel_send_sms, 2 },
	{ utc_tel_read_sms_in_sim, 1 },
	{ utc_fail_tel_read_sms_in_sim, 2 },
	{ utc_tel_write_sms_in_sim, 1 },
	{ utc_fail_tel_write_sms_in_sim, 2 },
	{ utc_tel_delete_sms_in_sim, 1 },
	{ utc_fail_tel_delete_sms_in_sim, 2 },
	{ utc_tel_get_sms_sca, 1 },
	{ utc_fail_tel_get_sms_sca, 2 },
	{ utc_tel_set_sms_sca, 1 },
	{ utc_fail_tel_set_sms_sca, 2 },
	{ utc_tel_set_sms_cb_config, 1 },
	{ utc_fail_tel_set_sms_cb_config, 2 },
	{ utc_tel_set_sms_memory_status, 1 },
	{ utc_fail_tel_set_sms_memory_status, 2 },
	{ utc_tel_set_sms_preferred_bearer, 1 },
	{ utc_fail_tel_set_sms_preferred_bearer, 2 },
	{ utc_tel_send_sms_deliver_report, 1 },
	{ utc_fail_tel_send_sms_deliver_report, 2 },
	{ utc_tel_set_sms_message_status, 1 },
	{ utc_fail_tel_set_sms_message_status, 2 },
	{ utc_tel_get_sms_parameters, 1 },
	{ utc_fail_tel_get_sms_parameters, 2 },
	{ utc_tel_set_sms_parameters, 1 },
	{ utc_fail_tel_set_sms_parameters, 2 },
	{ utc_tel_check_sms_device_status, 1 },
	{ utc_fail_tel_check_sms_device_status, 2 },
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
