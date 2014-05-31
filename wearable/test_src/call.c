/*
 * Telephony test application
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd. All rights reserved.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <glib.h>

#include <tapi_common.h>
#include <TelCall.h>
#include <ITapiCall.h>
#include <TapiUtility.h>

#include "menu.h"
#include "call.h"

static char data_call_id[MENU_DATA_SIZE + 1] = "1";
static char data_call_id2[MENU_DATA_SIZE + 1] = "2";
static char data_call_type[MENU_DATA_SIZE + 1] = "0";
static char data_dtmf_string[MENU_DATA_SIZE + 1] = "1";
static char data_call_number[MENU_DATA_SIZE + 1] = "+821099777347";
static char data_answer_type[MENU_DATA_SIZE + 1] = "1";
static char data_end_type[MENU_DATA_SIZE + 1] = "1";
static char data_clock_status[MENU_DATA_SIZE + 1] = "1";
static char data_mute_path[MENU_DATA_SIZE + 1] = "0";
static char data_mute_status[MENU_DATA_SIZE + 1] = "0";
static char data_vol_device[MENU_DATA_SIZE + 1] = "0";
static char data_vol_type[MENU_DATA_SIZE + 1] = "1";
static char data_vol_level[MENU_DATA_SIZE + 1] = "1";
static char data_sound_path[MENU_DATA_SIZE + 1] = "1";
static char data_extra_volume_status[MENU_DATA_SIZE + 1] = "0";
static char data_sound_recording[MENU_DATA_SIZE + 1] = "0";
static char data_sound_equalization_mode[MENU_DATA_SIZE + 1] = "0";
static char data_sound_direction[MENU_DATA_SIZE + 1] = "0";
static char data_sound_noise_reduction[MENU_DATA_SIZE + 1] = "0";

static void on_noti_call_status_idle(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	TelCallStatusIdleNoti_t *noti_data = (TelCallStatusIdleNoti_t*)data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_VOICE_CALL_STATUS_IDLE);

	if (!noti_data)
		return;

	msg(" - id = %d", noti_data->id);
	msg(" - cause = 0x%x", noti_data->cause);
}

static void on_noti_call_status_active(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	TelCallStatusActiveNoti_t *noti_data = (TelCallStatusActiveNoti_t*)data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_VOICE_CALL_STATUS_ACTIVE);

	if (!noti_data)
		return;

	msg(" - id = %d", noti_data->id);
}

static void on_noti_call_status_held(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	TelCallStatusHeldNoti_t *noti_data = (TelCallStatusHeldNoti_t*)data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_VOICE_CALL_STATUS_HELD);

	if (!noti_data)
		return;

	msg(" - id = %d", noti_data->id);
}

static void on_noti_call_status_dialing(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	TelCallStatusDialingNoti_t *noti_data = (TelCallStatusDialingNoti_t*)data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_VOICE_CALL_STATUS_DIALING);

	if (!noti_data)
		return;

	msg(" - id = %d", noti_data->id);
}

static void on_noti_call_status_alert(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	TelCallStatusAlertNoti_t *noti_data = (TelCallStatusAlertNoti_t*)data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_VOICE_CALL_STATUS_ALERT);

	if (!noti_data)
		return;

	msg(" - id = %d", noti_data->id);
}

static void on_noti_call_status_incoming(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	TelCallStatusIncomingNoti_t *noti_data = (TelCallStatusIncomingNoti_t*)data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_VOICE_CALL_STATUS_INCOMING);

	if (!noti_data)
		return;

	msg(" - id = %d", noti_data->id);
}

static void on_noti_call_sound_clock_status(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	gboolean *noti_data = (gboolean*)data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_CALL_SOUND_CLOCK_STATUS);

	if (!noti_data)
		return;

	msg(" - status = 0x%x", *noti_data);
}

static void on_noti_call_sound_ringback_tone(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	TelCallSoundRingbackToneNoti_t *noti_data = (TelCallSoundRingbackToneNoti_t*)data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_CALL_SOUND_RINGBACK_TONE);

	if (!noti_data)
		return;

	msg(" - Ringback tone status = 0x%x", *noti_data);
}

static void on_noti_call_sound_wbamr(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	gboolean *noti_data = (gboolean*)data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_CALL_SOUND_WBAMR);

	if (!noti_data)
		return;

	msg(" - status = 0x%x", *noti_data);
}

static void on_noti_call_sound_noise_reduction(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	gboolean *noti_data = (gboolean*)data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_CALL_SOUND_NOISE_REDUCTION);

	if (!noti_data)
		return;

	msg(" - status = 0x%x", *noti_data);
}

static void on_noti_call_sound_equalization(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	TelCallSoundEqualizationNoti_t *noti_data = (TelCallSoundEqualizationNoti_t *)data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_CALL_SOUND_EQUALIZATION);

	if (!noti_data)
		return;

	msg(" - Mode = 0x%x  Direction = 0x%x", noti_data->mode, noti_data->direction);
}

static void on_noti_call_sound_path(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	TelSoundPath_t *noti_data = (TelSoundPath_t *)data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_CALL_SOUND_PATH);

	if (!noti_data)
		return;

	msg(" - Sound path = 0x%x", *noti_data);
}

static void on_noti_call_on_hold(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	unsigned int *noti_data = (unsigned int*)data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_CALL_INFO_HELD);

	if (!noti_data)
		return;

	msg(" - ID = %d", *noti_data);
}

static void on_noti_call_active(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	unsigned int *noti_data = (unsigned int*)data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_CALL_INFO_ACTIVE);

	if (!noti_data)
		return;

	msg(" - ID = %d", *noti_data);
}

static void on_noti_call_joined(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	unsigned int *noti_data = (unsigned int*)data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_CALL_INFO_JOINED);

	if (!noti_data)
		return;

	msg(" - ID = %d", *noti_data);
}


static void on_dial_call(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg("on_dial_call() - result : 0x%x", result);
}

static void on_answer_call(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelCallAnswerCnf_t *cnf_data = (TelCallAnswerCnf_t*)data;

	msg("on_answer_call() - cnf_data->id : %d", cnf_data->id);
}

static void on_end_call(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelCallEndCnf_t *cnf_data = (TelCallEndCnf_t*)data;

	msg("on_end_call() - cnf_data->id : %d result : 0x%x", cnf_data->id, result);
}

static void on_hold_call(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelCallHoldCnf_t *cnf_data = (TelCallHoldCnf_t*)data;

	msg("on_hold_call() - cnf_data->id : %d result : 0x%x", cnf_data->id, result);
}

static void on_active_call(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelCallActiveCnf_t *cnf_data = (TelCallActiveCnf_t*)data;

	msg("on_active_call() - cnf_data->id : %d result : 0x%x", cnf_data->id, result);
}

static void on_swap_call(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelCallSwapCnf_t *cnf_data = (TelCallSwapCnf_t*)data;

	msg("on_swap_call() - cnf_data->id : %d result : 0x%x", cnf_data->id, result);
}

static void on_join_call(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelCallJoinCnf_t *cnf_data = (TelCallJoinCnf_t*)data;

	msg("on_join_call() - cnf_data->id : %d result : 0x%x", cnf_data->id, result);
}

static void on_split_call(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelCallSplitCnf_t *cnf_data = (TelCallSplitCnf_t*)data;

	msg("on_split_call() - cnf_data->id : %d result : 0x%x", cnf_data->id, result);
}

static void on_transfer_call(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelCallTransferCnf_t *cnf_data = (TelCallTransferCnf_t*)data;

	msg("on_transfer_call() - cnf_data->id : %d result : 0x%x", cnf_data->id, result);
}

static void on_dtmf_call(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg("on_dtmf_call() result : 0x%x", result);
}


static void on_call_sound_clock_status(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg("on_call_sound_clock_status() - result : 0x%x", result);
}

static void on_call_set_mute_status(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg("on_call_set_mute_status() - result : 0x%x", result);
}

static void on_call_get_mute_status(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelCallGetMuteStatusResp_t *resp = (TelCallGetMuteStatusResp_t *)data;

	msg("on_call_get_mute_status() - result : 0x%x", result);
	msg("on_call_get_mute_status() - path : 0x%x", resp->path);
	msg("on_call_get_mute_status() - status : 0x%x", resp->status);
}

static void on_call_set_volume_info(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg("on_call_set_volume_info() - result : 0x%x", result);
}

static void on_call_get_volume_info(TapiHandle *handle, int result, void *data, void *user_data)
{
	unsigned int i = 0;
	TelCallGetVolumeInfoResp_t *resp = (TelCallGetVolumeInfoResp_t *)data;

	msg("on_call_get_volume_info() - result : 0x%x", result);
	msg("on_call_get_volume_info() - record_num : 0x%x", resp->record_num);

	for ( i=0; i<resp->record_num; i++ ) {
		msg("on_call_get_volume_info() - record[%d].device : 0x%x", (i+1), resp->record[i].device);
		msg("on_call_get_volume_info() - record[%d].type : 0x%x", (i+1), resp->record[i].device);
		msg("on_call_get_volume_info() - record[%d].volume : 0x%x", (i+1), resp->record[i].volume);

	}
}

static void on_call_set_sound_path(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg("on_call_set_sound_path() - result : 0x%x", result);
}

static void on_call_set_sound_recording(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg("on_call_set_sound_recording() - result : 0x%x", result);
}

static void on_call_set_sound_equalization(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg("on_call_set_sound_equalization() - result : 0x%x", result);
}

static void on_call_set_sound_noise_reduction(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg("on_call_set_sound_noise_reduction() - result : 0x%x", result);
}

static int run_call_dial(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	TelCallDial_t data;
	int result;
	int len;

	memset(&data, 0, sizeof(TelCallDial_t));

	data.CallType = atoi(data_call_type);
	len = strlen(data_call_number);
	if (len > TAPI_CALL_DIALDIGIT_LEN_MAX) {
		msg("number too long");
		return 0;
	}

	memcpy(data.szNumber, data_call_number, len);

	msg("call tel_dail_call()");

	result = tel_dial_call(handle, &data, on_dial_call, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}

static int run_call_answer(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;
	unsigned int call_id;
	TelCallAnswerType_t answer_type;


	msg("call tel_answer_call()");

	call_id = atoi(data_call_id);
	answer_type = atoi(data_answer_type);

	result = tel_answer_call(handle, call_id, answer_type, on_answer_call, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}

static int run_call_end(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;
	unsigned int call_id;
	TelCallEndType_t end_type;

	msg("call tel_end_call()");

	call_id = atoi(data_call_id);
	end_type = atoi(data_end_type);

	result = tel_end_call(handle, call_id, end_type, on_end_call, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}

static int run_call_hold(MManager *mm, struct menu_data *menu)
{
        TapiHandle *handle = menu_manager_ref_user_data(mm);
        int result;
        unsigned int call_id;

        msg("call tel_hold_call()");

        call_id = atoi(data_call_id);
        result = tel_hold_call(handle, call_id, on_hold_call, NULL);

        if (result != TAPI_API_SUCCESS) {
                msg("failed. (result = %d)", result);
        }

        return result;
}

static int run_call_join(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;
	unsigned int call_id;

	msg("call tel_join_call()");

	call_id = atoi(data_call_id);

	result = tel_join_call(handle, call_id, 0, on_join_call, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}

static int run_call_active(MManager *mm, struct menu_data *menu)
{
        TapiHandle *handle = menu_manager_ref_user_data(mm);
        int result;
        unsigned int call_id;

        msg("call tel_active_call()");

        call_id = atoi(data_call_id);
        result = tel_active_call(handle, call_id, on_active_call, NULL);
        if (result != TAPI_API_SUCCESS) {
                msg("failed. (result = %d)", result);
        }

        return result;
}


static int run_call_split(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;
	unsigned int call_id;

	msg("call tel_split_call()");

	call_id = atoi(data_call_id);

	result = tel_split_call(handle, call_id, on_split_call, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}

static int run_call_swap(MManager *mm, struct menu_data *menu)
{
        TapiHandle *handle = menu_manager_ref_user_data(mm);
        int result;
        unsigned int call_id;
        unsigned int call_id2;

        msg("call tel_swap_call()");

        call_id = atoi(data_call_id);
        call_id2 = atoi(data_call_id2);
        result = tel_swap_call(handle, call_id, call_id2, on_swap_call, NULL);

        if (result != TAPI_API_SUCCESS) {
                msg("failed. (result = %d)", result);
        }

        return result;
}


static int run_call_transfer(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;
	unsigned int call_id;


	msg("call tel_transfer_call()");

	call_id = atoi(data_call_id);

	result = tel_transfer_call(handle, call_id, on_transfer_call, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}

static int run_call_dtmf(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;

	msg("call tel_dtmf_call()");

	result = tel_call_dtmf(handle, data_dtmf_string, on_dtmf_call, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}

static void call_status_callback( TelCallStatus_t *status, void *user_data )
{

	msg(" - id = %d", status->CallHandle);
	msg(" - direction = %d", status->bMoCall);
	msg(" - number = %s", status->pNumber);
	msg(" - type = %d", status->CallType);
	msg(" - state = %d", status->CallState);
	msg(" - multiparty = %d", status->bConferenceState);

}

static int run_call_get_status(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;
	unsigned int call_id = 0;
	TelCallStatus_t info;

	msg("call tel_get_call_status()");

	call_id = atoi(data_call_id);

	result = tel_get_call_status(handle, call_id, &info);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
		return result ;
	}

	msg(" - id = %d", info.CallHandle);
	msg(" - direction = %d", info.bMoCall);
	msg(" - number = %s", info.pNumber);
	msg(" - type = %d", info.CallType);
	msg(" - state = %d", info.CallState);
	msg(" - multiparty = %d", info.bConferenceState);

	return result;
}

static int run_call_get_status_all(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result = 0;

	msg("call tel_get_call_status_all()");

	result = tel_get_call_status_all(handle, call_status_callback, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}

static int run_call_set_sound_clock_status(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result = 0;
	int status = 0;

	msg("call tel_set_call_sound_clock_status()");

	status = atoi(data_clock_status);

	msg("status : (%d)", status);

	result = tel_set_call_sound_clock_status(handle, (gboolean)status, on_call_sound_clock_status, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}

static int run_call_set_mute_status(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result = 0;
	TelSoundMutePath_t path = 0;
	TelSoundMuteStatus_t status = 0;

	msg("call tel_set_call_mute_status()");

	path = (TelSoundMutePath_t)atoi(data_mute_path);
	status = (TelSoundMuteStatus_t)atoi(data_mute_status);

	msg("path : (%d)", path);
	msg("status : (%d)", status);

	result = tel_set_call_mute_status(handle, status, path, on_call_set_mute_status, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}

static int run_call_get_mute_status(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result = 0;

	msg("call tel_get_call_mute_status()");

	result = tel_get_call_mute_status(handle, on_call_get_mute_status, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}

static int run_call_set_volume_info(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result = 0;
	TelCallVolumeInfo_t data;

	msg("call tel_set_call_volume_info()");

	data.device = (TelSoundDevice_t)atoi(data_vol_device);
	data.type = (TelSoundType_t)atoi(data_vol_type);
	data.volume = (TelSoundVolume_t)atoi(data_vol_level);

	msg("device : (%d)", data.device);
	msg("type : (%d)", data.type);
	msg("volume : (%d)", data.volume);

	result = tel_set_call_volume_info(handle, &data, on_call_set_volume_info, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}

static int run_call_get_volume_info(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result = 0;
	TelSoundDevice_t device;
	TelSoundType_t type;

	msg("call tel_get_call_volume_info()");

	device = (TelSoundDevice_t)atoi(data_vol_device);
	type = (TelSoundType_t)atoi(data_vol_type);

	msg("device : (%d)", device);
	msg("type : (%d)", type);

	result = tel_get_call_volume_info(handle, device, type, on_call_get_volume_info, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}

static int run_call_set_sound_path(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result = 0;
	TelCallSoundPathInfo_t sound_path ;

	msg("call tel_set_sound_path()");

	sound_path.path = (TelSoundPath_t)atoi(data_sound_path);
	sound_path.ex_volume = atoi(data_extra_volume_status);

	msg("sound_path.path : (0x%x)", sound_path.path);
	msg("sound_path.ex_volume : (0x%x)", sound_path.ex_volume);

	result = tel_set_call_sound_path(handle, &sound_path, on_call_set_sound_path, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}

static int run_call_set_sound_recording(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result = 0;
	TelSoundRecording_t sound_recording ;

	msg("call tel_set_sound_recording()");

	sound_recording = (TelSoundRecording_t)atoi(data_sound_recording);

	msg("sound_recording : (0x%x)", sound_recording);

	result = tel_set_call_sound_recording(handle, &sound_recording, on_call_set_sound_recording, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}

static int run_call_set_sound_equalization(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result = 0;
	TelCallSoundEqualization_t sound_equalization ;

	msg("call tel_set_sound_equalization()");
	memset(&sound_equalization,0,sizeof(sound_equalization));

	sound_equalization.mode = (TelSoundEqualizationMode_t)atoi(data_sound_equalization_mode);
	sound_equalization.direction = (TelSoundDirection_t)atoi(data_sound_direction);

	msg("sound_equalization.mode: (0x%x)", sound_equalization.mode);
	msg("sound_equalization.direction: (0x%x)", sound_equalization.direction);

	result = tel_set_call_sound_equalization(handle, &sound_equalization, on_call_set_sound_equalization, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}

static int run_call_set_sound_noise_reduction(MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result = 0;
	TelSoundNoiseReduction_t sound_noise_reduction ;

	msg("call tel_set_sound_noise_reduction()");

	sound_noise_reduction = (TelSoundNoiseReduction_t)atoi(data_sound_noise_reduction);

	msg("sound_noise_reduction : (0x%x)", sound_noise_reduction);

	result = tel_set_call_sound_noise_reduction(handle, sound_noise_reduction, on_call_set_sound_noise_reduction, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return result;
}




static struct menu_data menu_call_dial[] = {
	{ "1", "type (0=VOICE, 1=VIDEO, 2=Emergency)", 0, 0, data_call_type},
	{ "2", "number", 0, 0, data_call_number},
	{ "3", "run", 0, run_call_dial, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_answer[] = {
	{ "1", "id", 0, 0, data_call_id},
	{ "2", "type (0=ACCEPT, 1=REJECT, 2=REPLACE, 3=HOLD&ACCEPT)", 0, 0, data_answer_type},
	{ "3", "run", 0, run_call_answer, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_end[] = {
	{ "1", "id", 0, 0, data_call_id},
	{ "2", "type (0=END, 1=END ALL, 2=END ACTIVE ALL, 3=END HOLD ALL)", 0, 0, data_end_type},
	{ "3", "run", 0, run_call_end, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_hold[] = {
	{ "1", "id", 0, 0, data_call_id},
	{ "2", "run", 0, run_call_hold, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_active[] = {
	{ "1", "id", 0, 0, data_call_id},
	{ "2", "run", 0, run_call_active, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_swap[] = {
	{ "1", "id", 0, 0, data_call_id},
	{ "2", "id2", 0, 0, data_call_id2},
	{ "3", "run", 0, run_call_swap, 0},
};

static struct menu_data menu_call_join[] = {
	{ "1", "id", 0, 0, data_call_id},
	{ "2", "run", 0, run_call_join, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_split[] = {
	{ "1", "id", 0, 0, data_call_id},
	{ "2", "run", 0, run_call_split, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_transfer[] = {
	{ "1", "id", 0, 0, data_call_id},
	{ "2", "run", 0, run_call_transfer, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_dtmf[] = {
	{ "1", "Dtmf Charater(0-9, A-D, ' * ' and ' # ') one character at a time ", 0, 0, data_dtmf_string},
	{ "2", "run", 0, run_call_dtmf, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_get_status[] = {
	{ "1", "id", 0, 0, data_call_id},
	{ "2", "run", 0, run_call_get_status, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_get_status_all[] = {
	{ "1", "id", 0, 0, data_call_id},
	{ "2", "run", 0, run_call_get_status_all, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_set_sound_clock_status[] = {
	{ "1", "status", 0, 0, data_clock_status},
	{ "2", "run", 0, run_call_set_sound_clock_status, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_set_mute_status[] = {
	{ "1", "status", 0, 0, data_mute_status},
	{ "2", "path", 0, 0, data_mute_path},
	{ "3", "run", 0, run_call_set_mute_status, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_get_mute_status[] = {
	{ "1", "run", 0, run_call_get_mute_status, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_set_volume_info[] = {
	{ "1", "device", 0, 0, data_vol_device},
	{ "2", "type", 0, 0, data_vol_type},
	{ "3", "volume", 0, 0, data_vol_level},
	{ "4", "run", 0, run_call_set_volume_info, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_get_volume_info[] = {
	{ "1", "device", 0, 0, data_vol_device},
	{ "2", "type", 0, 0, data_vol_type},
	{ "3", "run", 0, run_call_get_volume_info, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_set_sound_path[] = {
	{ "1", "Sound path(1= HANDSET, 2= HEADSET, 3= HANDSFREE, 4=BUETOOTH, 5=STEREO_BLUETOOTH, 6=SPK_PHONE, 7=HEADSET_5_PI, 8=BT_NSCE_OFF, 9=MIC1, 10=MIC2, 11=HEADSET_HAC)", 0, 0, data_sound_path},
	{ "2", "Extra Volume Status( 0=OFF, 1=ON)", 0, 0, data_extra_volume_status},
	{ "3", "run", 0, run_call_set_sound_path, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_set_sound_recording[] = {
	{ "1", "Sound Recording(0=OFF, 1=ON) ", 0, 0, data_sound_recording},
	{ "2", "run", 0, run_call_set_sound_recording, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_set_sound_equalization[] = {
	{ "1", "Sound Equalization Mode (0=OFF, 1=ON, 2=FLAG_OFF, 3=FLAG_ON, 4=SOFT1, 5=SOFT2)", 0, 0, data_sound_equalization_mode},
	{ "2", "Sound direction (0=LEFT, 1=RIGHT)", 0, 0, data_sound_direction},	
	{ "3", "run", 0, run_call_set_sound_equalization, 0},
	{ 0, 0, },
};

static struct menu_data menu_call_set_sound_noise_reduction[] = {
	{ "1", "Sound Noise reduction (0=OFF, 1=ON)", 0, 0, data_sound_noise_reduction},
	{ "2", "run", 0, run_call_set_sound_noise_reduction, 0},
	{ 0, 0, },
};


struct menu_data menu_call[] = {
	{ "1", "tel_dial_call", menu_call_dial, 0, 0},
	{ "2", "tel_answer_call", menu_call_answer, 0, 0},
	{ "3", "tel_end_call", menu_call_end, 0, 0},
	{ "4", "tel_hold_call", menu_call_hold, 0, 0},
	{ "5", "tel_active_call", menu_call_active, 0, 0},
	{ "6", "tel_swap_call", menu_call_swap, 0, 0},
	{ "7", "tel_join_call", menu_call_join, 0, 0},
	{ "8", "tel_split_call", menu_call_split, 0, 0},
	{ "9", "tel_transfer_call", menu_call_transfer, 0, 0},
	{ "10", "tel_dtmf_call", menu_call_dtmf, 0, 0},
	{ "11", "tel_get_call_status", menu_call_get_status, 0, 0},
	{ "12", "tel_get_call_status_all", menu_call_get_status_all, 0, 0},
	{ "13", "tel_set_call_sound_clock_status", menu_call_set_sound_clock_status, 0, 0},
	{ "14", "tel_set_call_mute_status", menu_call_set_mute_status, 0, 0},
	{ "15", "tel_get_call_mute_status", menu_call_get_mute_status, 0, 0},
	{ "16", "tel_set_call_volume_info", menu_call_set_volume_info, 0, 0},
	{ "17", "tel_get_call_volume_info", menu_call_get_volume_info, 0, 0},
	{ "18", "tel_set_call_sound_path", menu_call_set_sound_path, 0, 0},
	{ "19", "tel_set_call_sound_recording", menu_call_set_sound_recording, 0, 0},
	{ "20", "tel_set_call_sound_equalization", menu_call_set_sound_equalization, 0, 0},
	{ "21", "tel_set_call_sound_noise_reduction", menu_call_set_sound_noise_reduction, 0, 0},
	{ 0, 0, },
};

void register_call_event(TapiHandle *handle)
{
	int ret;

	ret = tel_register_noti_event(handle, TAPI_NOTI_VOICE_CALL_STATUS_IDLE, on_noti_call_status_idle, 0);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event(handle, TAPI_NOTI_VOICE_CALL_STATUS_ACTIVE, on_noti_call_status_active, 0);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event(handle, TAPI_NOTI_VOICE_CALL_STATUS_HELD, on_noti_call_status_held, 0);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event(handle, TAPI_NOTI_VOICE_CALL_STATUS_DIALING, on_noti_call_status_dialing, 0);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event(handle, TAPI_NOTI_VOICE_CALL_STATUS_ALERT, on_noti_call_status_alert, 0);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event(handle, TAPI_NOTI_VOICE_CALL_STATUS_INCOMING, on_noti_call_status_incoming, 0);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event(handle, TAPI_NOTI_CALL_SOUND_CLOCK_STATUS, on_noti_call_sound_clock_status, 0);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event(handle, TAPI_NOTI_CALL_INFO_HELD, on_noti_call_on_hold, 0);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event(handle, TAPI_NOTI_CALL_INFO_ACTIVE, on_noti_call_active, 0);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event(handle, TAPI_NOTI_CALL_INFO_JOINED, on_noti_call_joined, 0);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event(handle, TAPI_NOTI_CALL_SOUND_RINGBACK_TONE, on_noti_call_sound_ringback_tone, 0);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event(handle, TAPI_NOTI_CALL_SOUND_WBAMR, on_noti_call_sound_wbamr, 0);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event(handle, TAPI_NOTI_CALL_SOUND_EQUALIZATION, on_noti_call_sound_equalization, 0);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event(handle, TAPI_NOTI_CALL_SOUND_PATH, on_noti_call_sound_path, 0);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event(handle, TAPI_NOTI_CALL_SOUND_NOISE_REDUCTION, on_noti_call_sound_noise_reduction, 0);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}
}

