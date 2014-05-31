/*
 * libslp-tapi
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

#include "tapi_common.h"
#include "TapiUtility.h"

#include "common.h"
#include "tapi_log.h"
#include "ITapiGps.h"

static void on_response_default_set(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	GError *error = NULL;
	GDBusConnection *conn = NULL;
	struct tapi_resp_data *evt_cb_data = user_data;
	int result = -1;

	GVariant *dbus_result;

	conn = G_DBUS_CONNECTION (source_object);
	dbus_result = g_dbus_connection_call_finish(conn, res, &error);
	CHECK_DEINIT(error);

	if (!dbus_result) {
		if (evt_cb_data->cb_fn) {
			evt_cb_data->cb_fn(evt_cb_data->handle, -1, NULL, evt_cb_data->user_data);
		}

		if (error)
			g_error_free(error);

		g_free(evt_cb_data);
		return;
	}


	g_variant_get (dbus_result, "(i)", &result);

	if (evt_cb_data->cb_fn) {
		evt_cb_data->cb_fn(evt_cb_data->handle, result, NULL, evt_cb_data->user_data);
	}

	g_free(evt_cb_data);
}


EXPORT_API int tel_set_gps_frequency_aiding(TapiHandle *handle, unsigned char state, tapi_response_cb callback, void *user_data)
{
	struct tapi_resp_data *evt_cb_data = NULL;
	GVariant *param;

	dbg("Func Entrance");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(y)", state);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE , handle->path, DBUS_TELEPHONY_GPS_INTERFACE,
			"SetFrequencyAiding", param, NULL,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_default_set, evt_cb_data);

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_confirm_gps_measure_pos(TapiHandle *handle, unsigned char *data, unsigned int data_len)
{
	GVariant *param = NULL;
	GVariant *rst = NULL;
	GError *gerr = 0;
	gchar *encoded_data = NULL;
	gint result;

	dbg("Func Entrance");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);
	TAPI_RET_ERR_NUM_IF_FAIL(handle->dbus_connection, TAPI_API_INVALID_INPUT);
	TAPI_RET_ERR_NUM_IF_FAIL(data, TAPI_API_INVALID_PTR);

	msg("call tel_confirm_gps_measure_pos(). data_len=%d", data_len);
	encoded_data = g_base64_encode((const guchar*)data, data_len);

	param = g_variant_new("(s)", encoded_data);

	rst = g_dbus_connection_call_sync(handle->dbus_connection, DBUS_TELEPHONY_SERVICE , handle->path,
			DBUS_TELEPHONY_GPS_INTERFACE, "ConfirmMeasurePos", param, NULL, G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca, &gerr);

	g_free(encoded_data);

	if(!rst){
		dbg( "error to gps measure pos confirm(%s)", gerr->message);
		g_error_free (gerr);
		return TAPI_API_OPERATION_FAILED;
	}
	dbg("send gps user confirm format(%s)", g_variant_get_type_string(rst));

	g_variant_get(rst, "(i)", &result);
	dbg("result (%d)", result);

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_enable_smart_assistant(TapiHandle *handle, tapi_response_cb callback, void *user_data)
{
	struct tapi_resp_data *evt_cb_data = NULL;

	dbg("Func Entrance");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE , handle->path, DBUS_TELEPHONY_GPS_INTERFACE,
			"EnableSmartAssistant", NULL, NULL,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_default_set, evt_cb_data);

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_disable_smart_assistant(TapiHandle *handle, tapi_response_cb callback, void *user_data)
{
	struct tapi_resp_data *evt_cb_data = NULL;

	dbg("Func Entrance");

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE , handle->path, DBUS_TELEPHONY_GPS_INTERFACE,
			"DisableSmartAssistant", NULL, NULL,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_default_set, evt_cb_data);

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_sync_smart_assistant_area_list(TapiHandle *handle, TelSmartAssistantAreaList_t *area_list, tapi_response_cb callback, void *user_data)
{
	struct tapi_resp_data *evt_cb_data = NULL;
	GVariant *param = NULL, *inparam = NULL;
	GVariantBuilder *b;
	unsigned int i;

	TAPI_RET_ERR_NUM_IF_FAIL(area_list, TAPI_API_INVALID_PTR);
	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);
	dbg("count:%d", area_list->count);

	b = g_variant_builder_new(G_VARIANT_TYPE ("a(ii)"));

	for (i = 0; i < area_list->count; i++) {
		g_variant_builder_add(b, "(ii)", area_list->area[i].index, area_list->area[i].mode_state);
	}

	inparam = g_variant_builder_end(b);
	param = g_variant_new("(iv)", area_list->count, inparam);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE , handle->path, DBUS_TELEPHONY_GPS_INTERFACE,
			"SyncSmartAssistantAreaList", param, NULL,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_default_set, evt_cb_data);

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_del_smart_assistant_area_list(TapiHandle *handle, TelSmartAssistantAreaList_t *area_list, tapi_response_cb callback, void *user_data)
{
	struct tapi_resp_data *evt_cb_data = NULL;
	GVariant *param = NULL, *inparam = NULL;
	GVariantBuilder *b;
	unsigned int i;

	TAPI_RET_ERR_NUM_IF_FAIL(area_list, TAPI_API_INVALID_PTR);
	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);
	dbg("count:%d", area_list->count);

	b = g_variant_builder_new(G_VARIANT_TYPE ("a(ii)"));

	for (i = 0; i < area_list->count; i++) {
		g_variant_builder_add(b, "(ii)", area_list->area[i].index, area_list->area[i].mode_state);
	}

	inparam = g_variant_builder_end(b);
	param = g_variant_new("(iv)", area_list->count, inparam);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE , handle->path, DBUS_TELEPHONY_GPS_INTERFACE,
			"DelSmartAssistantAreaList", param, NULL,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_default_set, evt_cb_data);

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_add_smart_assistant_area(TapiHandle *handle, TelSmartAssistantArea_t *area, tapi_response_cb callback, void *user_data)
{
	struct tapi_resp_data *evt_cb_data = NULL;
	GVariant *param;

	TAPI_RET_ERR_NUM_IF_FAIL(area, TAPI_API_INVALID_PTR);
	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(ii)",
			area->index,
			area->mode_state);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE , handle->path, DBUS_TELEPHONY_GPS_INTERFACE,
			"AddSmartAssistantArea", param, NULL,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_default_set, evt_cb_data);

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_modify_smart_assistant_area(TapiHandle *handle, TelSmartAssistantArea_t *area, tapi_response_cb callback, void *user_data)
{
	struct tapi_resp_data *evt_cb_data = NULL;
	GVariant *param;

	TAPI_RET_ERR_NUM_IF_FAIL(area, TAPI_API_INVALID_PTR);
	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	dbg("index:%d, mode_state:%d", area->index, area->mode_state);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(ii)",
			area->index,
			area->mode_state);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE , handle->path, DBUS_TELEPHONY_GPS_INTERFACE,
			"ModifySmartAssistantArea", param, NULL,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_default_set, evt_cb_data);

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_set_smart_assistant_info(TapiHandle *handle, TelSmartAssistantInfo_t *info, tapi_response_cb callback, void *user_data)
{
	struct tapi_resp_data *evt_cb_data = NULL;
	GVariant *param;

	TAPI_RET_ERR_NUM_IF_FAIL(info, TAPI_API_INVALID_PTR);
	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_PTR);

	dbg("index:%d, lpp_state:%d", info->index, info->lpp_state);

	MAKE_RESP_CB_DATA(evt_cb_data, handle, callback, user_data);

	param = g_variant_new("(ii)",
			info->index,
			info->lpp_state);

	g_dbus_connection_call(handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE , handle->path, DBUS_TELEPHONY_GPS_INTERFACE,
			"SetSmartAssistantInfo", param, NULL,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, handle->ca,
			on_response_default_set, evt_cb_data);

	return TAPI_API_SUCCESS;
}

