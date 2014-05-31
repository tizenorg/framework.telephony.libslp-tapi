/*
 * libslp-tapi
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd. All rights reserved.
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

#include "TelCall.h"
#include "tapi_common.h"
#include "TapiUtility.h"

#include "common.h"
#include "tapi_log.h"
#include "ITapiCall.h"

static void on_response_call_dial(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(i)", &result);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, 0, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_call_answer(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;
	TelCallAnswerCnf_t data;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(ii)", &result, &data.id);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, &data, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_call_end(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;
	TelCallEndCnf_t data;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(iii)", &result, &data.id, &data.type);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, &data, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_call_hold(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;
	TelCallHoldCnf_t data;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(ii)", &result, &data.id);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, &data, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_call_active(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;
	TelCallActiveCnf_t data;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(ii)", &result, &data.id);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, &data, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_call_swap(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;
	TelCallSwapCnf_t data;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(ii)", &result, &data.id);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, &data, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_call_join(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;
	TelCallJoinCnf_t data;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(ii)", &result, &data.id);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, &data, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_call_split(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;
	TelCallSplitCnf_t data;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(ii)", &result, &data.id);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, &data, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_call_transfer(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;
	TelCallTransferCnf_t data;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(ii)", &result, &data.id);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, &data, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_call_dtmf(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(i)", &result);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, 0, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_call_deflect(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(i)", &result);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, 0, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_get_call_volume_info(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1, i = 0;
	TelCallGetVolumeInfoResp_t resp;

	GVariant *dbus_result = 0, *value = 0;
	GVariantIter *iter = 0;
	GVariantIter *iter_row = 0;
	const gchar *key = 0;

	memset(&resp, '\0', sizeof(TelCallGetVolumeInfoResp_t));

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(aa{sv}i)", &iter, &result);

	resp.record_num = g_variant_iter_n_children(iter);

	while ( g_variant_iter_next(iter, "a{sv}", &iter_row ) ) {
		while ( g_variant_iter_loop( iter_row, "{sv}", &key, &value ) ) {

			if ( !g_strcmp0(key, "type") ) {
				int type = g_variant_get_int32(value);

				resp.record[i].device = (type & 0xf0);
				resp.record[i].type = (type & 0x0f);
			}

			if ( !g_strcmp0(key, "level") ) {
				resp.record[i].volume = g_variant_get_int32(value);
			}
		}
		i++;
		g_variant_iter_free(iter_row);
	}
	g_variant_iter_free(iter);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, &resp, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_set_call_volume_info(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(i)", &result);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, 0, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_set_call_sound_path(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(i)", &result);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, 0, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_set_call_mute_status(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(i)", &result);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, 0, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_get_call_mute_status(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;
	TelCallGetMuteStatusResp_t resp;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(iii)", &result, &resp.path, &resp.status);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, &resp, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_set_call_sound_recording(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(i)", &result);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, 0, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_set_call_sound_equalization(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(i)", &result);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, 0, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_set_call_sound_noise_reduction(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(i)", &result);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, 0, evt_cb_data->user_data);

	g_free(evt_cb_data);
}

static void on_response_set_call_sound_clock_status(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = 0;
	GDBusConnection *conn = 0;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn)
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}

	g_variant_get (dbus_result, "(i)", &result);

	if (evt_cb_data->cb_fn)
		evt_cb_data->cb_fn(evt_cb_data->handle, result, 0, evt_cb_data->user_data);

	g_free(evt_cb_data);
}


EXPORT_API int tel_dial_call(TapiHandle *handle, const TelCallDial_t *pParams, tapi_response_cb callback, void *user_data)
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);
	TAPI_RET_ERR_NUM_IF_FAIL(pParams, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(iis)", pParams->CallType, pParams->Ecc, pParams->szNumber);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"Dial", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_call_dial, evt_cb_data );

	return TAPI_API_SUCCESS;
}


EXPORT_API int tel_answer_call(TapiHandle *handle, unsigned int CallHandle, TelCallAnswerType_t AnsType, tapi_response_cb callback, void *user_data )
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	if (AnsType > TAPI_CALL_ANSWER_HOLD_AND_ACCEPT)
		return TAPI_API_INVALID_INPUT;

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(ii)", CallHandle, AnsType);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"Answer", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_call_answer, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_end_call(TapiHandle *handle, unsigned int CallHandle, TelCallEndType_t EndType, tapi_response_cb callback, void *user_data)
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	if (EndType > TAPI_CALL_END_HOLD_ALL)
		return TAPI_API_INVALID_INPUT;

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(ii)", CallHandle, EndType);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"End", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_call_end, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_hold_call(TapiHandle *handle, unsigned int CallHandle, tapi_response_cb callback, void *user_data )
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(i)", CallHandle);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"Hold", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_call_hold, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_active_call(TapiHandle *handle, unsigned int CallHandle, tapi_response_cb callback, void *user_data )
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(i)", CallHandle);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"Active", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_call_active, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_swap_call(TapiHandle *handle, unsigned int CallHandle1, unsigned int CallHandle2, tapi_response_cb callback, void *user_data )
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(i)", CallHandle1);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"Swap", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_call_swap, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_join_call(TapiHandle *handle, unsigned int CallHandle1, unsigned int CallHandle2, tapi_response_cb callback, void *user_data )
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(i)", CallHandle1);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"Join", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_call_join, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_split_call(TapiHandle *handle, unsigned int CallHandle, tapi_response_cb callback, void *user_data )
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(i)", CallHandle);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"Split", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_call_split, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_transfer_call(TapiHandle *handle, unsigned int CallHandle, tapi_response_cb callback, void *user_data )
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(i)", CallHandle);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"Transfer", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_call_transfer, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_activate_call_ccbs(TapiHandle *handle, unsigned int CallHandle, tapi_response_cb callback, void *user_data )
{
	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_call_dtmf(TapiHandle *handle, const char *pDtmfString, tapi_response_cb callback, void *user_data )
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);
	TAPI_RET_ERR_NUM_IF_FAIL(pDtmfString, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(s)", pDtmfString);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"Dtmf", param, 0,
			G_DBUS_CALL_FLAGS_NONE, G_MAXINT, handle->ca,
			on_response_call_dtmf, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_deflect_call(TapiHandle *handle, unsigned int CallHandle, const TelCallDeflectDstInfo_t *pInfo, tapi_response_cb callback, void *user_data )
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);
	TAPI_RET_ERR_NUM_IF_FAIL(pInfo, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(is)", CallHandle, pInfo->number);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"Deflect", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_call_deflect, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_get_call_status(TapiHandle *handle, int call_id, TelCallStatus_t *out )
{
	GVariant *gv = 0;
	GVariant *param = 0;

	GError *gerr = 0;

	gchar *call_number;
	gint call_type = 0;
	gboolean call_direction = FALSE;
	gint call_state = 0;
	gboolean call_multiparty_state = FALSE;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);
	TAPI_RET_ERR_NUM_IF_FAIL(out, TAPI_API_INVALID_PTR);

	param = g_variant_new("(i)", call_id);

	gv = g_dbus_connection_call_sync(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE , handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"GetStatus", param, 0, G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca, &gerr);

	if ( gv ) {
		g_variant_get(gv, "(isibib)", &call_id, &call_number, &call_type, &call_direction, &call_state, &call_multiparty_state);

		out->CallHandle = (int)call_id;
		out->bMoCall = (int)call_direction;
		strncpy( out->pNumber, call_number, TAPI_CALL_DIALDIGIT_LEN_MAX );

		dbg("[ check ] call_number : %s", call_number);
		dbg("[ check ] out->pNumber : %s", out->pNumber);

		out->CallType = (TelCallType_t)call_type;
		out->CallState = (TelCallStates_t)call_state;
		out->bConferenceState = (int)call_multiparty_state;

		g_free( call_number );

	} else {
		dbg("[ error ] fail to get call status : (0x%x)", call_id);
		g_error_free(gerr);
		return TAPI_API_OPERATION_FAILED;
	}

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_get_call_status_all( TapiHandle *handle, TelCallStatusCallback cb, void *user_data )
{
	GVariant *gv = 0;
	GVariantIter *iter = 0, *iter_row = 0;
	GError *gerr = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);
	TAPI_RET_ERR_NUM_IF_FAIL(cb, TAPI_API_INVALID_PTR);

	gv = g_dbus_connection_call_sync(handle->dbus_connection,
									DBUS_TELEPHONY_SERVICE , handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
									"GetStatusAll", 0, 0, G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca, &gerr);

	if ( gv ) {

		TelCallStatus_t data;
		gchar *key = 0;
		GVariant *value = 0;

		g_variant_get(gv, "(aa{sv})", &iter);

		while (g_variant_iter_next(iter, "a{sv}", &iter_row)) {

			while (g_variant_iter_loop(iter_row, "{sv}", &key, &value)) {

				if (!g_strcmp0(key, "call_id")) {
					data.CallHandle = g_variant_get_int32(value);
				}
				if (!g_strcmp0(key, "call_number")) {
					strncpy(data.pNumber, g_variant_get_string(value, 0), TAPI_CALL_DIALDIGIT_LEN_MAX);
				}
				if (!g_strcmp0(key, "call_type")) {
					data.CallType = (int)g_variant_get_int32(value);
				}
				if (!g_strcmp0(key, "call_direction")) {
					data.bMoCall = (int)g_variant_get_boolean(value);
				}
				if (!g_strcmp0(key, "call_state")) {
					data.CallState = (int)g_variant_get_int32(value);
				}
				if (!g_strcmp0(key, "call_multiparty_state")) {
					data.bConferenceState = (int)g_variant_get_boolean(value);
				}

			}

			g_variant_iter_free(iter_row);

			cb( &data, user_data );
		}
		g_variant_iter_free(iter);
	} else {

		dbg("[ error ] fail to get call status");
		return TAPI_API_OPERATION_FAILED;

	}

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_get_call_act_line(TapiHandle *handle, tapi_response_cb callback, void *user_data )
{
	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_set_call_act_line(TapiHandle *handle, TelCallActiveLine_t active_line, tapi_response_cb callback, void *user_data )
{
	return TAPI_API_SUCCESS;
}

/*================================================================================================*/

EXPORT_API int tel_get_call_duration(TapiHandle *handle, unsigned int CallHandle, unsigned int *pDurationInSecs)
{
	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_get_call_conf_list(TapiHandle *handle, unsigned int CallHandle, unsigned int *pCallList, int *pNoOfCalls)
{
	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_get_call_privacy_mode(TapiHandle *handle, TelCallPrivacyType_t PrivacyType, tapi_response_cb callback, void *user_data )
{
	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_set_call_privacy_mode(TapiHandle *handle, TelCallVoicePrivacyInfo_t PrivacyInfo, tapi_response_cb callback, void *user_data )
{
	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_exe_call_flash_info(TapiHandle *handle, const char *pDialNumber, tapi_response_cb callback, void *user_data )
{
	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_exit_call_emergency_mode(TapiHandle *handle, tapi_response_cb callback, void *user_data )
{
	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_get_call_time(TapiHandle *handle, unsigned short req_mask, tapi_response_cb callback, void *user_data )
{
	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_get_call_volume_info(TapiHandle *handle, TelSoundDevice_t device, TelSoundType_t type, tapi_response_cb callback, void *user_data )
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(ii)", device, type);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"GetSoundVolumeLevel", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_get_call_volume_info, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_set_call_volume_info(TapiHandle *handle, TelCallVolumeInfo_t *info, tapi_response_cb callback, void *user_data )
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);
	TAPI_RET_ERR_NUM_IF_FAIL(info, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(iii)", info->device, info->type, info->volume);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"SetSoundVolumeLevel", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_set_call_volume_info, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_set_call_sound_path(TapiHandle *handle, TelCallSoundPathInfo_t *info, tapi_response_cb callback, void *user_data )
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);
	TAPI_RET_ERR_NUM_IF_FAIL(info, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(ib)", info->path, info->ex_volume);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"SetSoundPath", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_set_call_sound_path, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_set_call_mute_status(TapiHandle *handle, TelSoundMuteStatus_t mute, TelSoundMutePath_t path, tapi_response_cb callback, void *user_data )
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(ii)", mute, path);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"SetSoundMuteStatus", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_set_call_mute_status, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_get_call_mute_status(TapiHandle *handle, tapi_response_cb callback, void *user_data )
{
	struct tapi_resp_data *evt_cb_data = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);
	TAPI_RET_ERR_NUM_IF_FAIL(callback, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"GetSoundMuteStatus", 0, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_get_call_mute_status, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API  int tel_set_call_sound_recording(TapiHandle *handle, TelSoundRecording_t *on, tapi_response_cb callback, void *user_data)
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	param = g_variant_new("(i)", *on);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"SetSoundRecording", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_set_call_sound_recording, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API  int tel_set_call_sound_equalization(TapiHandle *handle, TelCallSoundEqualization_t *eq, tapi_response_cb callback, void *user_data)
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;
	char *eq_param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);
	TAPI_RET_ERR_NUM_IF_FAIL(eq, TAPI_API_INVALID_PTR);

	eq_param = (char*)eq->parameter;

	param = g_variant_new("(iis)", eq->mode, eq->direction, eq_param);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"SetSoundEqualization", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_set_call_sound_equalization, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API  int tel_set_call_sound_noise_reduction(TapiHandle *handle, TelSoundNoiseReduction_t noise, tapi_response_cb callback, void *user_data)
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance ");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	param = g_variant_new("(i)", noise);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"SetSoundNoiseReduction", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_set_call_sound_noise_reduction, evt_cb_data );

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_set_call_sound_clock_status(TapiHandle *handle, gboolean status, tapi_response_cb callback, void *user_data )
{
	struct tapi_resp_data *evt_cb_data = 0;
	GVariant *param = 0;

	dbg("Func Entrance");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(b)", status);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path, DBUS_TELEPHONY_CALL_INTERFACE,
			"SetSoundClockStatus", param, 0,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_set_call_sound_clock_status, evt_cb_data );

	return TAPI_API_SUCCESS;
}

/*	EOF  */
