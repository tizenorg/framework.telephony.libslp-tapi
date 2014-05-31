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
#include <ITapiCall.h>
#include <TapiUtility.h>

#include "util_common.h"

TapiHandle *handle;
enum async_state async_flag;

char szNumber[TAPI_CALL_DIALDIGIT_LEN_MAX + 1] = "+919535009683";
char emer_num[4] = "911";
unsigned call_id = 1;
unsigned call_id2 = 2;

TelCallType_t call_type[3] = {
	TAPI_CALL_TYPE_VOICE,
	TAPI_CALL_TYPE_DATA,
	TAPI_CALL_TYPE_E911
} ;

TelCallEmergencyCategory_t emergency_category[9] = {
	TAPI_CALL_ECC_DEFAULT,
	TAPI_CALL_ECC_POLICE,
	TAPI_CALL_ECC_AMBULANCE,
	TAPI_CALL_ECC_FIREBRIGADE,
	TAPI_CALL_ECC_MARINEGUARD,
	TAPI_CALL_ECC_MOUNTAINRESCUE,
	TAPI_CALL_ECC_MANUAL_ECALL,
	TAPI_CALL_ECC_AUTO_ECALL,
	TAPI_CALL_ECC_NONE
};

TelCallAnswerType_t answer_type[4] = {
	TAPI_CALL_ANSWER_ACCEPT,
	TAPI_CALL_ANSWER_REJECT,
	TAPI_CALL_ANSWER_REPLACE,
	TAPI_CALL_ANSWER_HOLD_AND_ACCEPT
} ;

TelCallEndType_t  end_type[4] = {
	TAPI_CALL_END,
	TAPI_CALL_END_ALL,
	TAPI_CALL_END_ACTIVE_ALL,
	TAPI_CALL_END_HOLD_ALL
} ;

TelSoundVolume_t sound_volume[10] ={
	TAPI_SOUND_MUTE,		    
	TAPI_SOUND_VOLUME_LEVEL_1,
	TAPI_SOUND_VOLUME_LEVEL_2,
	TAPI_SOUND_VOLUME_LEVEL_3,
	TAPI_SOUND_VOLUME_LEVEL_4,
	TAPI_SOUND_VOLUME_LEVEL_5,
	TAPI_SOUND_VOLUME_LEVEL_6,
	TAPI_SOUND_VOLUME_LEVEL_7,
	TAPI_SOUND_VOLUME_LEVEL_8,
	TAPI_SOUND_VOLUME_LEVEL_9
} ;

TelSoundRecording_t sound_recording[2] = {
	TAPI_SOUND_RECORDING_OFF,
	TAPI_SOUND_RECORDING_ON
} ;

TelSoundDevice_t sound_device[6]  = {
	TAPI_SOUND_DEVICE_RECEIVER,
	TAPI_SOUND_DEVICE_SPEAKER_PHONE,
	TAPI_SOUND_DEVICE_HFK,
	TAPI_SOUND_DEVICE_HEADSET,
	TAPI_SOUND_DEVICE_BLUETOOTH, 
	TAPI_SOUND_DEVICE_EC
} ;

TelSoundType_t sound_type [6] = {
	TAPI_SOUND_TYPE_VOICE, 
	TAPI_SOUND_TYPE_KEYTONE, 
	TAPI_SOUND_TYPE_BELL,
	TAPI_SOUND_TYPE_MESSAGE,
	TAPI_SOUND_TYPE_ALARM, 
	TAPI_SOUND_TYPE_PDA_MISC
} ;

TelSoundPath_t sound_path[11] = {
	TAPI_SOUND_PATH_HANDSET,
	TAPI_SOUND_PATH_HEADSET,
	TAPI_SOUND_PATH_HANDSFREE,
	TAPI_SOUND_PATH_BLUETOOTH,
	TAPI_SOUND_PATH_STEREO_BLUETOOTH,
	TAPI_SOUND_PATH_SPK_PHONE,
	TAPI_SOUND_PATH_HEADSET_3_5PI,
	TAPI_SOUND_PATH_BT_NSEC_OFF,
	TAPI_SOUND_PATH_MIC1, 
	TAPI_SOUND_PATH_MIC2,
	TAPI_SOUND_PATH_HEADSET_HAC
} ;

unsigned int extra_vol[2] = { 0, 1 };
unsigned int clock_status[2] = { 0, 1 };


TelSoundMuteStatus_t mute_status [2] = {
	TAPI_SOUND_MUTE_STATUS_OFF,
	TAPI_SOUND_MUTE_STATUS_ON
} ;

TelSoundNoiseReduction_t sound_noise[2] = {
	TAPI_SOUND_NOISE_REDUCTION_OFF,
	TAPI_SOUND_NOISE_REDUCTION_ON
} ;

TelSoundEqualizationMode_t sound_equalization[6] = {
	TAPI_SOUND_EQUALIZATION_MODE_OFF,
	TAPI_SOUND_EQUALIZATION_MODE_ON,
	TAPI_SOUND_EQUALIZATION_MODE_FLAG_OFF,
	TAPI_SOUND_EQUALIZATION_MODE_FLAG_ON,
	TAPI_SOUND_EQUALIZATION_MODE_SOFT1,
	TAPI_SOUND_EQUALIZATION_MODE_SOFT2,
} ;

TelSoundDirection_t sound_direction[2] = {
	TAPI_SOUND_DIRECTION_LEFT,
	TAPI_SOUND_DIRECTION_RIGHT,
} ;


TelSoundMutePath_t mute_path[3] = {
	TAPI_SOUND_MUTE_PATH_TX,
	TAPI_SOUND_MUTE_PATH_RX,
	TAPI_SOUND_MUTE_PATH_ALL
} ;

/* Dial Call Macro */
#define DO_DIAL_CALL(func, param1, param2, param3) \
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
	} \
\
	static void utc_##func (TelCallType_t  param1, TelCallEmergencyCategory_t param2, char *param3) \
	{ \
		TelCallDial_t info; \
		int ret; \
		int len;\
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		memset(&info, 0, sizeof(TelCallDial_t)); \
		len = strlen(param3); \
		info.CallType =param1; \
		info.Ecc = param2; \
		memcpy(info.szNumber, param3, len); \
		ret = tel_dial_call (handle, &info, on_##func, &value); \
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
	static void utc_fail_##func (TelCallType_t  param1, TelCallEmergencyCategory_t param2, char *param3) \
	{ \
		int ret; \
\
		ret = tel_dial_call (NULL, NULL, NULL,NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}

/* Answer Call Macro */
#define DO_ANSWER_CALL(func, param1, param2) \
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
	static void utc_##func (unsigned int  param1, TelCallAnswerType_t param2) \
	{ \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		ret = tel_answer_call (handle, param1, param2, on_##func, &value); \
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
	static void utc_fail_##func (unsigned int  param1, TelCallAnswerType_t param2) \
	{ \
		int ret; \
\
		ret = tel_answer_call (NULL, 0, 0,NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}


/* End Call Macro */
#define DO_END_CALL(func, param1, param2) \
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
	} \
\
	static void utc_##func (unsigned int  param1, TelCallEndType_t param2) \
	{ \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		ret = tel_end_call (handle, param1, param2, on_##func, &value); \
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
	static void utc_fail_##func (unsigned int  param1, TelCallEndType_t param2) \
	{ \
		int ret; \
\
		ret = tel_end_call (NULL, 0, 0, NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}

/* Manage Call Macro (hold/active/spit/transfer */
#define DO_MANAGE_CALL(func, param1) \
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
	} \
\
	static void utc_##func (unsigned int  param1) \
	{ \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		ret = func (handle, param1, on_##func, &value); \
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
	static void utc_fail_##func (unsigned int  param1) \
	{ \
		int ret; \
\
		ret = func (NULL, 0, NULL,NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}

/* Swap/join Call Macro */
#define DO_SWAP_JOIN_CALL(func, param1, param2) \
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
	} \
\
	static void utc_##func (unsigned int  param1, unsigned int  param2) \
	{ \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		ret = func (handle, param1, param2, on_##func, &value); \
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
	static void utc_fail_##func (unsigned int  param1, unsigned int  param2) \
	{ \
		int ret; \
\
		ret = func (NULL, 0, 0, NULL,NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}


/* Get  Call Volume info Macro */
#define DO_GET_CALL_VOLUME_INFO(func, param1, param2) \
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
	} \
\
	static void utc_##func (TelSoundDevice_t param1, TelSoundType_t param2) \
	{ \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		ret = tel_get_call_volume_info (handle, param1, param2, on_##func, &value); \
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
	static void utc_fail_##func (TelSoundDevice_t param1, TelSoundType_t param2) \
	{ \
		int ret; \
\
		ret = tel_get_call_volume_info (NULL, 0, 0, NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}


/* Set  Call Volume info Macro */
#define DO_SET_CALL_VOLUME_INFO(func, param1, param2, param3) \
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
	} \
\
	static void utc_##func (TelSoundDevice_t param1, TelSoundType_t param2, TelSoundVolume_t param3) \
	{ \
		TelCallVolumeInfo_t info; \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		memset(&info, 0x0, sizeof(TelCallVolumeInfo_t)); \
		info.device = param1; \
		info.type = param2; \
		info.volume = param3; \
		ret = tel_set_call_volume_info (handle, &info, on_##func, &value); \
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
	static void utc_fail_##func (TelSoundDevice_t param1, TelSoundType_t param2, TelSoundVolume_t param3) \
	{ \
		int ret; \
\
		ret = tel_set_call_volume_info (NULL, NULL, NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}

/* Set  Call sound path Macro */
#define DO_SET_CALL_SOUND_PATH(func, param1, param2) \
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
	} \
\
	static void utc_##func (TelSoundPath_t param1, unsigned int param2) \
	{ \
		TelCallSoundPathInfo_t info; \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		memset(&info, 0x0, sizeof(TelCallSoundPathInfo_t)); \
		info.path = param1; \
		info.ex_volume = param2; \
		ret = tel_set_call_sound_path (handle, &info, on_##func, &value); \
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
	static void utc_fail_##func (TelSoundPath_t param1, unsigned int param2) \
	{ \
		int ret; \
\
		ret = tel_set_call_sound_path (NULL, NULL, NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}

/* Set  Call mute status Macro */
#define DO_SET_CALL_MUTE_STATUS(func, param1, param2) \
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
	} \
\
	static void utc_##func (TelSoundMuteStatus_t param1, TelSoundMutePath_t param2) \
	{ \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		ret = tel_set_call_mute_status (handle, param1, param2, on_##func, &value); \
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
	static void utc_fail_##func (TelSoundMuteStatus_t param1, TelSoundMutePath_t param2) \
	{ \
		int ret; \
\
		ret = tel_set_call_mute_status (NULL, 0, 0, NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}

/* Set  Call Sound Recording Macro */
#define DO_SET_CALL_SOUND_RECORDING(func, param1) \
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
	} \
\
	static void utc_##func (TelSoundRecording_t param1) \
	{ \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		ret = tel_set_call_sound_recording (handle, &param1, on_##func, &value); \
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
	static void utc_fail_##func (TelSoundRecording_t param1) \
	{ \
		int ret; \
\
		ret = tel_set_call_sound_recording (NULL, NULL, NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}


/* Set  Call Sound Equalization Macro */
#define DO_SET_CALL_SOUND_EQUALIZATION(func, param1, param2) \
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
	} \
\
	static void utc_##func (TelSoundEqualizationMode_t param1, TelSoundDirection_t param2) \
	{ \
		TelCallSoundEqualization_t info; \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		memset(&info, 0x0, sizeof(TelCallSoundEqualization_t)); \
		info.mode = param1; \
		info.direction = param2 ; \
		ret = tel_set_call_sound_equalization (handle, &info, on_##func, &value); \
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
	static void utc_fail_##func (TelSoundEqualizationMode_t param1, TelSoundDirection_t param2) \
	{ \
		int ret; \
\
		ret = tel_set_call_sound_equalization (NULL, NULL, NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}


/* Set  Call Sound Noise Reduction Macro */
#define DO_SET_CALL_SOUND_NOISE_REDUCTION(func, param1) \
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
	} \
\
	static void utc_##func (TelSoundNoiseReduction_t param1) \
	{ \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		ret = tel_set_call_sound_noise_reduction (handle, param1, on_##func, &value); \
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
	static void utc_fail_##func (TelSoundNoiseReduction_t param1) \
	{ \
		int ret; \
\
		ret = tel_set_call_sound_noise_reduction (NULL, 0, NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}

/* Set  Call Sound Clock Status Macro */
#define DO_SET_CALL_SOUND_CLOCK_STATUS(func, param1) \
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
	} \
\
	static void utc_##func (gboolean param1) \
	{ \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		ret = tel_set_call_sound_clock_status (handle, param1, on_##func, &value); \
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
	static void utc_fail_##func (gboolean param1) \
	{ \
		int ret; \
\
		ret = tel_set_call_sound_clock_status (NULL, 0, NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}


/**
 * tel_call_dtmf
 *
 */
static void on_tel_call_dtmf (TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_call_dtmf", "Callback userdata crashed");
	}
}

static void utc_tel_call_dtmf ()
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_call_dtmf (handle, "1",
			on_tel_call_dtmf, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_call_dtmf", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_call_dtmf", "Callback not invoked");
	}

	dts_pass("tel_call_dtmf");
}

static void utc_fail_tel_call_dtmf (void)
{
	int ret;

	ret = tel_call_dtmf (NULL, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_call_dtmf", "Parameter check failed");
	}

	ret = tel_call_dtmf (handle, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_call_dtmf", "Parameter check failed");
	}

	dts_pass("tel_call_dtmf");
}

/**
 * tel_deflect_call
 *
 */
static void on_tel_deflect_call(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_deflect_call", "Callback userdata crashed");
	}
}

static void utc_tel_deflect_call()
{
	TelCallDeflectDstInfo_t info;
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	memset(&info, 0x0, sizeof(info));
	strcpy(info.number, (unsigned char *)"+919535099681");

	ret = tel_deflect_call (handle, call_id, &info,
			on_tel_deflect_call, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_deflect_call", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_deflect_call", "Callback not invoked");
	}

	dts_pass("tel_deflect_call");
}

static void utc_fail_tel_deflect_call (void)
{
	int ret;

	ret = tel_deflect_call (NULL, 0, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_deflect_call", "Parameter check failed");
	}

	ret = tel_deflect_call (handle, 0, NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_deflect_call", "Parameter check failed");
	}

	dts_pass("tel_deflect_call");
}

/**
 * tel_call_status
 *
 */

static void utc_tel_call_status ()
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_get_call_status (handle, call_id,
			value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_call_status", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_call_status", "Callback not invoked");
	}

	dts_pass("tel_call_status");
}

static void utc_fail_tel_call_status(void)
{
	int ret;

	ret = tel_get_call_status (NULL, 0, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_call_status", "Parameter check failed");
	}

	ret = tel_get_call_status (handle, 0, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_call_status", "Parameter check failed");
	}

	dts_pass("tel_call_status");
}

/**
 * tel_call_status_all
 *
 */
static void on_tel_call_status_all(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_call_status_all", "Callback userdata crashed");
	}
}

static void utc_tel_call_status_all()
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;

	ret = tel_get_call_status_all (handle,
			on_tel_call_status_all, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_call_status_all", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_call_status_all", "Callback not invoked");
	}

	dts_pass("tel_call_status_all");
}

static void utc_fail_tel_call_status_all (void)
{
	int ret;

	ret = tel_get_call_status_all (NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_deflect_call", "Parameter check failed");
	}

	ret = tel_get_call_status_all (handle, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_call_status_all", "Parameter check failed");
	}

	dts_pass("tel_call_status_all");
}

/**
 * tel_get_call_mute_status
 *
 */
static void on_tel_get_call_mute_status (TapiHandle *handle, int result, void *data, void *user_data)
{
	int *value = user_data;

	async_flag = ASYNC_DONE;
	util_stop_loop ();

	if (*value != 0xC0FFEE) {
		dts_fail("tel_get_call_mute_status", "Callback userdata crashed");
	}
}

static void utc_tel_get_call_mute_status ()
{
	int ret;
	int value = 0xC0FFEE;

	util_init_loop ();

	async_flag = ASYNC_READY;
	ret = tel_get_call_mute_status (handle, 
			on_tel_get_call_mute_status, &value);
	if (ret != TAPI_API_SUCCESS) {
		dts_fail("tel_get_call_mute_status", "Unexpected return");
	}

	util_start_loop ();
	util_free_loop ();

	if (async_flag != ASYNC_DONE) {
		dts_fail("tel_get_call_mute_status", "Callback not invoked");
	}

	dts_pass("tel_get_call_mute_status");
}

static void utc_fail_tel_get_call_mute_status (void)
{
	int ret;

	ret = tel_get_call_mute_status (NULL, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_call_mute_status", "Parameter check failed");
	}

	ret = tel_get_call_mute_status (handle, NULL, NULL);
	if (ret == TAPI_API_SUCCESS) {
		dts_fail("tel_get_call_mute_status", "Parameter check failed");
	}

	dts_pass("tel_get_call_mute_status");
}



/* Dial auto generated functions */

DO_DIAL_CALL(tel_dial_voice_call, call_type[0], emergency_category[8], szNumber)
DO_DIAL_CALL(tel_dial_video_call, call_type[1], emergency_category[8], szNumber)
DO_DIAL_CALL(tel_dial_emergency_call, call_type[2], emergency_category[0], emer_num)

/* Answer auto generated functions */

DO_ANSWER_CALL(tel_answer_accept_call, call_id, answer_type[0])
DO_ANSWER_CALL(tel_answer_reject_call, call_id, answer_type[1])
DO_ANSWER_CALL(tel_answer_replace_call, call_id, answer_type[2])
DO_ANSWER_CALL(tel_answer_hold_and_accept_call, call_id, answer_type[3])

/* End auto generated functions */

DO_END_CALL(tel_end_call, call_id, end_type[0])
DO_END_CALL(tel_end_all_call, call_id, end_type[1])
DO_END_CALL(tel_end_active_all_call, call_id, end_type[2])
DO_END_CALL(tel_end_hold_all_call, call_id, end_type[3])

/* Hold/Active/Split/Transfer auto generated functions */

DO_MANAGE_CALL(tel_hold_call, call_id)
DO_MANAGE_CALL(tel_active_call, call_id)
DO_MANAGE_CALL(tel_split_call, call_id)
DO_MANAGE_CALL(tel_transfer_call, call_id)

/* Swap/Join auto generated functions */

DO_SWAP_JOIN_CALL(tel_swap_call, call_id, call_id2)
DO_SWAP_JOIN_CALL(tel_join_call, call_id, call_id2)


DO_GET_CALL_VOLUME_INFO(tel_get_call_volume_info_receiver, sound_device[0], sound_type[0])
DO_GET_CALL_VOLUME_INFO(tel_get_call_volume_info_speaker_phone, sound_device[1], sound_type[0])
DO_GET_CALL_VOLUME_INFO(tel_get_call_volume_info_hfk, sound_device[2], sound_type[0])
DO_GET_CALL_VOLUME_INFO(tel_get_call_volume_info_headset, sound_device[3], sound_type[0])
DO_GET_CALL_VOLUME_INFO(tel_get_call_volume_info_bluetooth, sound_device[4], sound_type[0])
DO_GET_CALL_VOLUME_INFO(tel_get_call_volume_info_ec, sound_device[5], sound_type[0])

DO_SET_CALL_VOLUME_INFO(tel_set_call_volume_info_receiver_low, sound_device[0], sound_type[0], sound_volume[0])
DO_SET_CALL_VOLUME_INFO(tel_set_call_volume_info_receiver_medium, sound_device[0], sound_type[0], sound_volume[4])
DO_SET_CALL_VOLUME_INFO(tel_set_call_volume_info_receiver_high, sound_device[0], sound_type[0], sound_volume[9])
DO_SET_CALL_VOLUME_INFO(tel_set_call_volume_info_headset_low, sound_device[3], sound_type[0], sound_volume[0])
DO_SET_CALL_VOLUME_INFO(tel_set_call_volume_info_headset_medium, sound_device[3], sound_type[0], sound_volume[4])
DO_SET_CALL_VOLUME_INFO(tel_set_call_volume_info_headset_high, sound_device[3], sound_type[0], sound_volume[9])
DO_SET_CALL_VOLUME_INFO(tel_set_call_volume_info_bluetooth_low, sound_device[4], sound_type[0], sound_volume[0])
DO_SET_CALL_VOLUME_INFO(tel_set_call_volume_info_bluetooth_medium, sound_device[4], sound_type[0], sound_volume[4])
DO_SET_CALL_VOLUME_INFO(tel_set_call_volume_info_bluetooth_high, sound_device[4], sound_type[0], sound_volume[9])

DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_handset_extra_vol_off, sound_path[0], extra_vol[0])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_handset_extra_vol_on, sound_path[0], extra_vol[1])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_headset_extra_vol_off, sound_path[1], extra_vol[0])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_headset_extra_vol_on, sound_path[1], extra_vol[1])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_handsfree_extra_vol_off, sound_path[2], extra_vol[0])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_handsfree_extra_vol_on, sound_path[2], extra_vol[1])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_bluetooth_extra_vol_off, sound_path[3], extra_vol[0])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_bluetooth_extra_vol_on, sound_path[3], extra_vol[1])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_spk_phone_extra_vol_off, sound_path[5], extra_vol[0])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_spk_phone_extra_vol_on, sound_path[5], extra_vol[1])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_headset_3_5pi_extra_vol_off, sound_path[6], extra_vol[0])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_headset_3_5pi_extra_vol_on, sound_path[6], extra_vol[1])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_bt_nsec_off_extra_vol_off, sound_path[7], extra_vol[0])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_bt_nsec_off_extra_vol_on, sound_path[7], extra_vol[1])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_mic1_extra_vol_off, sound_path[8], extra_vol[0])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_mic1_bluetooth_extra_vol_on, sound_path[8], extra_vol[1])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_mic2_extra_vol_off, sound_path[9], extra_vol[0])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_mic2_extra_vol_on, sound_path[9], extra_vol[1])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_headset_hac_extra_vol_off, sound_path[10], extra_vol[0])
DO_SET_CALL_SOUND_PATH(tel_set_call_sound_path_headset_hac_extra_vol_on, sound_path[10], extra_vol[1])


DO_SET_CALL_MUTE_STATUS(tel_set_call_mute_status_off_tx, mute_status[0], mute_path[0])
DO_SET_CALL_MUTE_STATUS(tel_set_call_mute_status_off_rx, mute_status[0], mute_path[1])
DO_SET_CALL_MUTE_STATUS(tel_set_call_mute_status_off_all, mute_status[0], mute_path[2])
DO_SET_CALL_MUTE_STATUS(tel_set_call_mute_status_on_tx, mute_status[1], mute_path[0])
DO_SET_CALL_MUTE_STATUS(tel_set_call_mute_status_on_rx, mute_status[1], mute_path[1])
DO_SET_CALL_MUTE_STATUS(tel_set_call_mute_status_on_all, mute_status[1], mute_path[2])

DO_SET_CALL_SOUND_RECORDING(tel_set_call_sound_recording_off, sound_recording[0])
DO_SET_CALL_SOUND_RECORDING(tel_set_call_sound_recording_on, sound_recording[1])

DO_SET_CALL_SOUND_EQUALIZATION(tel_set_call_sound_equalization_mode_off_left, sound_equalization [0], sound_direction[0])
DO_SET_CALL_SOUND_EQUALIZATION(tel_set_call_sound_equalization_mode_off_right, sound_equalization [0], sound_direction[1])
DO_SET_CALL_SOUND_EQUALIZATION(tel_set_call_sound_equalization_mode_on_left, sound_equalization [1], sound_direction[0])
DO_SET_CALL_SOUND_EQUALIZATION(tel_set_call_sound_equalization_mode_on_right, sound_equalization [1], sound_direction[1])
DO_SET_CALL_SOUND_EQUALIZATION(tel_set_call_sound_equalization_mode_flag_off_left, sound_equalization [2], sound_direction[0])
DO_SET_CALL_SOUND_EQUALIZATION(tel_set_call_sound_equalization_mode_flag_off_right, sound_equalization [2], sound_direction[1])
DO_SET_CALL_SOUND_EQUALIZATION(tel_set_call_sound_equalization_mode_flag_on_left, sound_equalization [3], sound_direction[0])
DO_SET_CALL_SOUND_EQUALIZATION(tel_set_call_sound_equalization_mode_flag_on_right, sound_equalization [3], sound_direction[1])
DO_SET_CALL_SOUND_EQUALIZATION(tel_set_call_sound_equalization_mode_soft1_left, sound_equalization [4], sound_direction[0])
DO_SET_CALL_SOUND_EQUALIZATION(tel_set_call_sound_equalization_mode_soft1_right, sound_equalization [4], sound_direction[1])
DO_SET_CALL_SOUND_EQUALIZATION(tel_set_call_sound_equalization_mode_soft2_left, sound_equalization [5], sound_direction[0])
DO_SET_CALL_SOUND_EQUALIZATION(tel_set_call_sound_equalization_mode_soft2_right, sound_equalization [5], sound_direction[1])

DO_SET_CALL_SOUND_NOISE_REDUCTION(tel_set_call_sound_reduction_off, sound_noise[0])
DO_SET_CALL_SOUND_NOISE_REDUCTION(tel_set_call_sound_reduction_on, sound_noise[1])

DO_SET_CALL_SOUND_CLOCK_STATUS(tel_set_call_sound_clock_status_off, clock_status[0])
DO_SET_CALL_SOUND_CLOCK_STATUS(tel_set_call_sound_clock_status_on, clock_status[1])


struct tet_testlist tet_testlist[] = {
	/* generated TC */
	{ utc_tel_dial_voice_call, 1 },
	{ utc_fail_tel_dial_voice_call, 2 },
	{ utc_tel_dial_video_call, 1 },
	{ utc_fail_tel_dial_video_call, 2 },
	{ utc_tel_dial_emergency_call, 1 },
	{ utc_fail_tel_dial_emergency_call, 2 },
	{ utc_tel_answer_accept_call, 1 },
	{ utc_fail_tel_answer_accept_call, 2 },
	{ utc_tel_answer_reject_call, 1 },
	{ utc_fail_tel_answer_reject_call, 2 },
	{ utc_tel_answer_replace_call, 1 },
	{ utc_fail_tel_answer_replace_call, 2 },
	{ utc_tel_answer_hold_and_accept_call, 1 },
	{ utc_fail_tel_answer_hold_and_accept_call, 2 },
	{ utc_tel_end_call, 1 },
	{ utc_fail_tel_end_call, 2 },
	{ utc_tel_end_all_call, 1 },
	{ utc_fail_tel_end_all_call, 2 },
	{ utc_tel_end_active_all_call, 1 },
	{ utc_fail_tel_end_active_all_call, 2 },
	{ utc_tel_end_hold_all_call, 1 },
	{ utc_fail_tel_end_hold_all_call, 2 },
	{ utc_tel_hold_call, 1 },
	{ utc_fail_tel_hold_call, 2 },
	{ utc_tel_active_call, 1 },
	{ utc_fail_tel_active_call, 2 },
	{ utc_tel_split_call, 1 },
	{ utc_fail_tel_split_call, 2 },
	{ utc_tel_transfer_call, 1 },
	{ utc_fail_tel_transfer_call, 2 },
	{ utc_tel_swap_call, 1 },
	{ utc_fail_tel_swap_call, 2 },
	{ utc_tel_join_call, 1 },
	{ utc_fail_tel_join_call, 2 },

	/* Sound */
	
	{ utc_tel_get_call_volume_info_receiver, 1},
	{ utc_fail_tel_get_call_volume_info_receiver, 2},
	{ utc_tel_get_call_volume_info_speaker_phone, 1},
	{ utc_fail_tel_get_call_volume_info_speaker_phone, 2},
	{ utc_tel_get_call_volume_info_hfk, 1},
	{ utc_fail_tel_get_call_volume_info_hfk, 2},
	{ utc_tel_get_call_volume_info_headset, 1},
	{ utc_fail_tel_get_call_volume_info_headset, 2},
	{ utc_tel_get_call_volume_info_bluetooth, 1},
	{ utc_fail_tel_get_call_volume_info_bluetooth, 2},
	{ utc_tel_get_call_volume_info_ec, 1},
	{ utc_fail_tel_get_call_volume_info_ec, 2},
	{ utc_tel_set_call_volume_info_receiver_low, 1},
	{ utc_fail_tel_set_call_volume_info_receiver_low, 2},
	{ utc_tel_set_call_volume_info_receiver_medium, 1},
	{ utc_fail_tel_set_call_volume_info_receiver_medium, 2},
	{ utc_tel_set_call_volume_info_receiver_high, 1},
	{ utc_fail_tel_set_call_volume_info_receiver_high, 2},
	{ utc_tel_set_call_volume_info_headset_low, 1},
	{ utc_fail_tel_set_call_volume_info_headset_low, 2},
	{ utc_tel_set_call_volume_info_headset_medium, 1},
	{ utc_fail_tel_set_call_volume_info_headset_medium, 2},
	{ utc_tel_set_call_volume_info_headset_high, 1},
	{ utc_fail_tel_set_call_volume_info_headset_high, 2},
	{ utc_tel_set_call_volume_info_bluetooth_low, 1},
	{ utc_fail_tel_set_call_volume_info_bluetooth_low, 2},
	{ utc_tel_set_call_volume_info_bluetooth_medium, 1},
	{ utc_fail_tel_set_call_volume_info_bluetooth_medium, 2},
	{ utc_tel_set_call_volume_info_bluetooth_high, 1},
	{ utc_fail_tel_set_call_volume_info_bluetooth_high, 2},
	{ utc_tel_set_call_sound_path_handset_extra_vol_off, 1},
	{ utc_fail_tel_set_call_sound_path_handset_extra_vol_off, 2},
	{ utc_tel_set_call_sound_path_handset_extra_vol_on, 1},
	{ utc_fail_tel_set_call_sound_path_handset_extra_vol_on, 2},
	{ utc_tel_set_call_sound_path_headset_extra_vol_off, 1},
	{ utc_fail_tel_set_call_sound_path_headset_extra_vol_off, 2},
	{ utc_tel_set_call_sound_path_headset_extra_vol_on, 1},
	{ utc_fail_tel_set_call_sound_path_headset_extra_vol_on, 2},
	{ utc_tel_set_call_sound_path_handsfree_extra_vol_off, 1},
	{ utc_fail_tel_set_call_sound_path_handsfree_extra_vol_off, 2},
	{ utc_tel_set_call_sound_path_handsfree_extra_vol_on, 1},
	{ utc_fail_tel_set_call_sound_path_handsfree_extra_vol_on, 2},
	{ utc_tel_set_call_sound_path_bluetooth_extra_vol_off, 1},
	{ utc_fail_tel_set_call_sound_path_bluetooth_extra_vol_off, 2},
	{ utc_tel_set_call_sound_path_bluetooth_extra_vol_on, 1},
	{ utc_fail_tel_set_call_sound_path_bluetooth_extra_vol_on, 2},
	{ utc_tel_set_call_sound_path_spk_phone_extra_vol_off, 1},
	{ utc_fail_tel_set_call_sound_path_spk_phone_extra_vol_off, 2},
	{ utc_tel_set_call_sound_path_spk_phone_extra_vol_on, 1},
	{ utc_fail_tel_set_call_sound_path_spk_phone_extra_vol_on, 2},
	{ utc_tel_set_call_sound_path_headset_3_5pi_extra_vol_off, 1},
	{ utc_fail_tel_set_call_sound_path_headset_3_5pi_extra_vol_off, 2},
	{ utc_tel_set_call_sound_path_headset_3_5pi_extra_vol_on, 1},
	{ utc_fail_tel_set_call_sound_path_headset_3_5pi_extra_vol_on, 2},
	{ utc_tel_set_call_sound_path_bt_nsec_off_extra_vol_off, 1},
	{ utc_fail_tel_set_call_sound_path_bt_nsec_off_extra_vol_off, 2},
	{ utc_tel_set_call_sound_path_bt_nsec_off_extra_vol_on, 1},
	{ utc_fail_tel_set_call_sound_path_bt_nsec_off_extra_vol_on, 2},
	{ utc_tel_set_call_sound_path_mic1_extra_vol_off, 1},
	{ utc_fail_tel_set_call_sound_path_mic1_extra_vol_off, 2},
	{ utc_tel_set_call_sound_path_mic1_bluetooth_extra_vol_on, 1},
	{ utc_fail_tel_set_call_sound_path_mic1_bluetooth_extra_vol_on, 2},
	{ utc_tel_set_call_sound_path_mic2_extra_vol_off, 1},
	{ utc_fail_tel_set_call_sound_path_mic2_extra_vol_off, 2},
	{ utc_tel_set_call_sound_path_mic2_extra_vol_on, 1},
	{ utc_fail_tel_set_call_sound_path_mic2_extra_vol_on, 2},
	{ utc_tel_set_call_sound_path_headset_hac_extra_vol_off, 1},
	{ utc_fail_tel_set_call_sound_path_headset_hac_extra_vol_off, 2},
	{ utc_tel_set_call_sound_path_headset_hac_extra_vol_on, 1},
	{ utc_fail_tel_set_call_sound_path_headset_hac_extra_vol_on, 2},
	{ utc_tel_set_call_mute_status_off_tx, 1},
	{ utc_fail_tel_set_call_mute_status_off_tx, 2},
	{ utc_tel_set_call_mute_status_off_rx, 1},
	{ utc_fail_tel_set_call_mute_status_off_rx, 2},
	{ utc_tel_set_call_mute_status_off_all, 1},
	{ utc_fail_tel_set_call_mute_status_off_all, 2},
	{ utc_tel_set_call_mute_status_on_tx, 1},
	{ utc_fail_tel_set_call_mute_status_on_tx, 2},
	{ utc_tel_set_call_mute_status_on_rx, 1},
	{ utc_fail_tel_set_call_mute_status_on_rx, 2},
	{ utc_tel_set_call_mute_status_on_all, 1},
	{ utc_fail_tel_set_call_mute_status_on_all, 2},
	{ utc_tel_set_call_sound_recording_off, 1},
	{ utc_fail_tel_set_call_sound_recording_off, 2},
	{ utc_tel_set_call_sound_recording_on, 1},
	{ utc_fail_tel_set_call_sound_recording_on, 2},
	{ utc_tel_set_call_sound_equalization_mode_off_left, 1},
	{ utc_fail_tel_set_call_sound_equalization_mode_off_left, 2 },
	{ utc_tel_set_call_sound_equalization_mode_off_right, 1},
	{ utc_fail_tel_set_call_sound_equalization_mode_off_right, 2 },
	{ utc_tel_set_call_sound_equalization_mode_on_left, 1},
	{ utc_fail_tel_set_call_sound_equalization_mode_on_left, 2},
	{ utc_tel_set_call_sound_equalization_mode_on_right, 1},
	{ utc_fail_tel_set_call_sound_equalization_mode_on_right, 2},
	{ utc_tel_set_call_sound_equalization_mode_flag_off_left, 1},
	{ utc_fail_tel_set_call_sound_equalization_mode_flag_off_left, 2},
	{ utc_fail_tel_set_call_sound_equalization_mode_flag_off_left, 1},
	{ utc_tel_set_call_sound_equalization_mode_flag_off_right, 1},
	{ utc_fail_tel_set_call_sound_equalization_mode_flag_off_right, 2},
	{ utc_tel_set_call_sound_equalization_mode_flag_on_left, 1},
	{ utc_fail_tel_set_call_sound_equalization_mode_flag_on_left, 2},
	{ utc_tel_set_call_sound_equalization_mode_flag_on_right, 1},
	{ utc_fail_tel_set_call_sound_equalization_mode_flag_on_right, 2},
	{ utc_tel_set_call_sound_equalization_mode_soft1_left, 1},
	{ utc_fail_tel_set_call_sound_equalization_mode_soft1_left, 2},
	{ utc_tel_set_call_sound_equalization_mode_soft1_right, 1},
	{ utc_fail_tel_set_call_sound_equalization_mode_soft1_right, 2},
	{ utc_tel_set_call_sound_equalization_mode_soft2_left, 1},
	{ utc_fail_tel_set_call_sound_equalization_mode_soft2_left, 2},
	{ utc_tel_set_call_sound_equalization_mode_soft2_right, 1},
	{ utc_fail_tel_set_call_sound_equalization_mode_soft2_right, 2},
	{ utc_tel_set_call_sound_reduction_off, 1},
	{ utc_fail_tel_set_call_sound_reduction_off, 2},
	{ utc_tel_set_call_sound_reduction_on, 1},
	{ utc_fail_tel_set_call_sound_reduction_on, 2},
	{ utc_tel_set_call_sound_clock_status_off, 1},
	{ utc_fail_tel_set_call_sound_clock_status_off, 2},
	{ utc_tel_set_call_sound_clock_status_on, 1},
	{ utc_fail_tel_set_call_sound_clock_status_on, 2},


	/* custom TC */
	{ utc_tel_call_dtmf, 1 },
	{ utc_fail_tel_call_dtmf, 2 },
	{ utc_tel_deflect_call, 1 },
	{ utc_fail_tel_deflect_call, 2 },
	{ utc_tel_call_status, 1 },
	{ utc_fail_tel_call_status, 2 },
	{ utc_tel_call_status_all, 1 },
	{ utc_fail_tel_call_status_all, 2 },
	{ utc_tel_get_call_mute_status, 1},
	{ utc_fail_tel_get_call_mute_status, 2},

	{ NULL, 0 },
};

static void startup (void)
{
	/* start of TC */
	tet_printf ("\n Call TC start");

	handle = tel_init (NULL);
}

static void cleanup (void)
{
	tel_deinit (handle);

	/* end of TC */
	tet_printf ("\n Call TC end");
}

void (*tet_startup) (void) = startup;
void (*tet_cleanup) (void) = cleanup;

