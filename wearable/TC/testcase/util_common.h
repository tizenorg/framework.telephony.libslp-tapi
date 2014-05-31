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

#ifndef __UTIL_COMMON_H__
#define __UTIL_COMMON_H__

/**
 * Generate default TC for no-additional-parameter type API
 *
 * - positive case ('utc_' prefix)
 *   - valid handle
 *   - with callback
 *     check user_data validation in callback
 *     not check result and data (modem state dependancy)
 *   - without callback
 *
 * - negative case ('utc_fail_' prefix)
 *   - invalid handle (NULL)
 *
 * Usage:
 *   DO(tel_get_network_band)
 *
 *   struct tet_testlist tet_testlist[] = {
 *       { ... },
 *       { utc_tel_get_network_band, 1 },
 *       { utc_fail_tel_get_network_band, 1 },
 *       { ... },
 *   };
 *
 */
#define DO(func) \
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
\
	} \
\
	static void utc_##func (void) \
	{ \
		int ret; \
		int value = 0xC0FFEE; \
\
		/* with callback */ \
		util_init_loop(); \
\
		async_flag = ASYNC_READY; \
		ret = func (handle, on_##func, &value); \
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
		/* without callback */ \
		ret = func (handle, NULL, NULL); \
		if (ret != TAPI_API_SUCCESS) { \
			dts_fail(#func, "Unexpected return"); \
			return; \
		} \
\
		dts_pass(#func); \
	} \
\
	static void utc_fail_##func (void) \
	{ \
		int ret; \
\
		ret = func (NULL, NULL, NULL); \
		dts_check_ne(#func, ret, TAPI_API_SUCCESS, "Unexpected return"); \
	}

enum async_state {
	ASYNC_READY,
	ASYNC_DONE
};

void util_init_loop ();
void util_free_loop ();

void util_start_loop ();
void util_stop_loop ();

#endif
