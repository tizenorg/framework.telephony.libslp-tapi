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

#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glib.h>
#include <gio/gio.h>

#include "tapi_common.h"
#include "TapiUtility.h"

//
#include "ITapiPS.h"
#include "TelNetwork.h"
#include "TelSms.h"
#include "TelSat.h"
#include "TelSs.h"
#include "TelCall.h"
#include "TelGps.h"

//
#include "common.h"
#include "tapi_log.h"

extern char *g_cookie_name;
extern int g_cookie_size;

TelSatEventDownloadType_t g_event_list[TAPI_SAT_EVENT_LIST_MAX_COUNT] = {-1};

/*static void _cookie_deinit(void)
{
	if (g_cookie_name)
		free(g_cookie_name);

	g_cookie_name = NULL;
	g_cookie_size = 0;
}*/

static void _process_sms_event(const gchar *sig, GVariant *param,
	TapiHandle *handle, char *noti_id, struct tapi_evt_cb *evt_cb_data)
{
	TAPI_RETURN_IF_FAIL(evt_cb_data);

	if (!g_strcmp0(sig, "IncommingMsg")) {
		struct tel_noti_sms_incomming_msg noti;

		GVariant *sca = 0, *tpdu = 0;
		int i = 0;
		GVariantIter *iter = 0;
		GVariant *inner_gv = 0;

		memset(&noti, 0, sizeof(struct tel_noti_sms_incomming_msg));

		g_variant_get(param, "(@vi@v)", &sca, &noti.MsgLength, &tpdu);

		inner_gv = g_variant_get_variant( sca );
		g_variant_get(inner_gv, "ay", &iter);
		while( g_variant_iter_loop( iter, "y", &noti.Sca[i] ) ) {
			 i++;
			 if( i >= TAPI_SIM_SMSP_ADDRESS_LEN )
				 break;
		}

		i = 0;
		inner_gv = g_variant_get_variant( tpdu );
		g_variant_get(inner_gv, "ay", &iter);
		while( g_variant_iter_loop( iter, "y", &noti.szData[i] ) ) {
			 i++;
			 if( i >= TAPI_NETTEXT_SMDATA_SIZE_MAX + 1 )
			 	break;
		}
		g_variant_iter_free(iter);
		g_variant_unref(inner_gv);

		CALLBACK_CALL(&noti);
	}
	else if (!g_strcmp0(sig, "IncommingCbMsg")) {
		struct tel_noti_sms_incomming_cb_msg noti;

		GVariant *cbMsg = NULL;
		int i = 0;
		GVariantIter *iter = 0;
		GVariant *inner_gv = 0;

		memset(&noti, 0, sizeof(struct tel_noti_sms_incomming_cb_msg));
		g_variant_get(param, "(ii@v)", &noti.CbMsgType, &noti.Length, &cbMsg);

		inner_gv = g_variant_get_variant( cbMsg );
		g_variant_get(inner_gv, "ay", &iter);
		while( g_variant_iter_loop( iter, "y", &noti.szMsgData[i] ) ) {
			 i++;
			 if( i >= TAPI_NETTEXT_CB_SIZE_MAX + 1 )
				 break;
		}
		g_variant_iter_free(iter);
		g_variant_unref(inner_gv);

		CALLBACK_CALL(&noti);
	}
	else if (!g_strcmp0(sig, "IncommingEtwsMsg")) {
		struct tel_noti_sms_incomming_etws_msg noti;

		GVariant *etwsMsg = NULL;
		int i = 0;
		GVariantIter *iter = 0;
		GVariant *inner_gv = 0;


		memset(&noti, 0, sizeof(struct tel_noti_sms_incomming_etws_msg));
		g_variant_get(param, "(ii@v)", &noti.EtwsMsgType, &noti.Length, &etwsMsg);

		inner_gv = g_variant_get_variant( etwsMsg );
		g_variant_get(inner_gv, "ay", &iter);
		while( g_variant_iter_loop( iter, "y", &noti.szMsgData[i] ) ) {
			 i++;
			 if( i >= TAPI_NETTEXT_ETWS_SIZE_MAX + 1 )
				 break;
		}
		g_variant_iter_free(iter);
		g_variant_unref(inner_gv);

		CALLBACK_CALL(&noti);
	}
	else if (!g_strcmp0(sig, "MemoryStatus")) {
		int noti = 0;

		g_variant_get(param, "(i)", &noti);
		CALLBACK_CALL(&noti);
	}
	else if (!g_strcmp0(sig, "SmsReady")) {
		gboolean noti = 0;

		g_variant_get(param, "(b)", &noti);
		CALLBACK_CALL(&noti);
	}
	else {
		dbg("not handled Sms noti[%s]", sig);
	}
}

static void _process_call_event(const gchar *sig, GVariant *param,
	TapiHandle *handle, char *noti_id, struct tapi_evt_cb *evt_cb_data)
{
	TAPI_RETURN_IF_FAIL(evt_cb_data);

	if (!g_strcmp0(sig, "VoiceCallStatusIdle") || !g_strcmp0(sig, "VideoCallStatusIdle") ) {
		TelCallStatusIdleNoti_t data;
		int start_time = 0, end_time = 0;
		g_variant_get(param, "(iiii)", &data.id, &data.cause, &start_time, &end_time);
		dbg("[ check ] %s : call_id(%d), end_cause(0x%x)", "Status Idle noti", data.id, data.cause);
		CALLBACK_CALL(&data);
	}
	else if (!g_strcmp0(sig, "VoiceCallStatusDialing") || !g_strcmp0(sig, "VideoCallStatusDialing")) {
		TelCallStatusDialingNoti_t data;
		g_variant_get(param, "(i)", &data.id);
		dbg("[ check ] %s : call_id(%d)", "Status Dialing noti", data.id);
		CALLBACK_CALL(&data);
	}
	else if (!g_strcmp0(sig, "VoiceCallStatusAlert") || !g_strcmp0(sig, "VideoCallStatusAlert")) {
		TelCallStatusAlertNoti_t data;
		g_variant_get(param, "(i)", &data.id);
		dbg("[ check ] %s : call_id(%d)", "Status Alert noti", data.id);
		CALLBACK_CALL(&data);
	}
	else if (!g_strcmp0(sig, "VoiceCallStatusActive") || !g_strcmp0(sig, "VideoCallStatusActive")) {
		TelCallStatusActiveNoti_t data;
		g_variant_get(param, "(i)", &data.id);
		dbg("[ check ] %s : call_id(%d)", "Status Active noti", data.id);
		CALLBACK_CALL(&data);
	}
	else if (!g_strcmp0(sig, "VoiceCallStatusHeld") ) {
		TelCallStatusHeldNoti_t data;
		g_variant_get(param, "(i)", &data.id);
		dbg("[ check ] %s : call_id(%d)", "Status Held noti", data.id);
		CALLBACK_CALL(&data);
	}
	else if (!g_strcmp0(sig, "VoiceCallStatusIncoming") || !g_strcmp0(sig, "VideoCallStatusIncoming")) {
		TelCallStatusIncomingNoti_t data;
		g_variant_get(param, "(i)", &data.id);
		dbg("[ check ] %s : call_id(%d)", "Status Incoming noti", data.id);
		CALLBACK_CALL(&data);
	}
	else if (!g_strcmp0(sig, "Waiting")) {
		TelCallInfoWaitingNoti_t data;
		g_variant_get(param, "(i)", &data.id);
		dbg("[ check ] %s : data.id(%d)", "Call Info Waiting noti", data.id);
		CALLBACK_CALL(&data.id);
	}
	else if (!g_strcmp0(sig, "Forwarded")) {
		TelCallInfoForwardedNoti_t data;
		g_variant_get(param, "(i)", &data.id);
		dbg("[ check ] %s : data.id(%d)", "Call Info Forwarded noti", data.id);
		CALLBACK_CALL(&data.id);
	}
	else if (!g_strcmp0(sig, "BarredIncoming")) {
		TelCallInfoBarredIncomingNoti_t data;
		g_variant_get(param, "(i)", &data.id);
		dbg("[ check ] %s : data.id(%d)", "Call Info Barred Incoming noti", data.id);
		CALLBACK_CALL(&data.id);
	}
	else if (!g_strcmp0(sig, "BarredOutgoing")) {
		TelCallInfoBarredOutgoingNoti_t data;
		g_variant_get(param, "(i)", &data.id);
		dbg("[ check ] %s : data.id(%d)", "Call Info Barred Outgoing noti", data.id);
		CALLBACK_CALL(&data.id);
	}
	else if (!g_strcmp0(sig, "ForwardConditional")) {
		TelCallInfoForwardConditionalNoti_t data;
		g_variant_get(param, "(i)", &data.id);
		dbg("[ check ] %s : data.id(%d)", "Call Info Forward Conditional noti", data.id);
		CALLBACK_CALL(&data.id);
	}
	else if (!g_strcmp0(sig, "ForwardUnconditional")) {
		TelCallInfoForwardUnconditionalNoti_t data;
		g_variant_get(param, "(i)", &data.id);
		dbg("[ check ] %s : data.id(%d)", "Call Info Forward Unconditional noti", data.id);
		CALLBACK_CALL(&data.id);
	}
	else if (!g_strcmp0(sig, "CallActive")) {
		TelCallInfoActiveNoti_t data;
		g_variant_get(param, "(i)", &data.id);
		dbg("[ check ] %s : data.id(%d)", "Call Info Call Active noti", data.id);
		CALLBACK_CALL(&data.id);
	}
	else if (!g_strcmp0(sig, "CallHeld")) {
		TelCallInfoHeldNoti_t data;
		g_variant_get(param, "(i)", &data.id);
		dbg("[ check ] %s : data.id(%d)", "Call Info Call Held noti", data.id);
		CALLBACK_CALL(&data.id);
	}
	else if (!g_strcmp0(sig, "CallJoined")) {
		TelCallInfoJoinedNoti_t data;
		g_variant_get(param, "(i)", &data.id);
		dbg("[ check ] %s : data.id(%d)", "Call Info Call Joined noti", data.id);
		CALLBACK_CALL(&data.id);
	}
	else if (!g_strcmp0(sig, "CallSoundPath")) {
		TelCallSoundPathNoti_t data;
		g_variant_get(param, "(i)", &data.path);
		dbg("[ check ] %s : path(%d)", "Call Sound Path noti", data.path);
		CALLBACK_CALL(&data);
	}
	else if (!g_strcmp0(sig, "CallSoundRingbackTone")) {
		TelCallSoundRingbackToneNoti_t status;
		g_variant_get(param, "(i)", &status);
		dbg("[ check ] %s : status(%d)", "Call Sound Ringbacktone noti", status);
		CALLBACK_CALL(&status);
	}
	else if (!g_strcmp0(sig, "CallSoundWbamr")) {
		TelCallSoundWbamrNoti_t status;
		g_variant_get(param, "(i)", &status);
		dbg("[ check ] %s : status(%d)", "Call Sound Wbamr noti", status);
		CALLBACK_CALL(&status);
	}
	else if (!g_strcmp0(sig, "CallSoundEqualization")) {
		TelCallSoundEqualizationNoti_t data;
		g_variant_get(param, "(ii)", &data.mode, &data.direction);
		dbg("[ check ] %s : mode(%d), direction(%d)", "Call Sound Equalization noti", data.mode, data.direction);
		CALLBACK_CALL(&data);
	}
	else if (!g_strcmp0(sig, "CallSoundNoiseReduction")) {
		TelCallSoundNoiseReductionNoti_t data;
		g_variant_get(param, "(i)", &data.status);
		dbg("[ check ] %s : status(%d)", "Call Sound Noise Reduction noti", data.status);
		CALLBACK_CALL(&data);
	}
	else if (!g_strcmp0(sig, "CallSoundClockStatus")) {
		gboolean data;
		g_variant_get(param, "(b)", &data);
		dbg("[ check ] %s : status(%d)", "Call Sound Clock Status noti", data);
		CALLBACK_CALL(&data);
	}
	else {
		dbg("not handled Call noti[%s]", sig);
	}
}

static void _process_sat_event(const gchar *sig, GVariant *param,
	TapiHandle *handle, char *noti_id, struct tapi_evt_cb *evt_cb_data)
{
	TAPI_RETURN_IF_FAIL(evt_cb_data);

	if (!g_strcmp0(sig, "SetupMenu")) {
		TelSatSetupMenuInfo_t setup_menu;

		gchar *title;
		gint command_id, item_cnt;
		gboolean b_present, b_helpinfo, b_updated;
		GVariant *items = NULL;

#if defined(TIZEN_SUPPORT_SAT_ICON)
		GVariant *icon_id = NULL;
		GVariant *icon_list = NULL;
		int index = 0, icon_index = 0;
		GVariantIter *iter, *iter2;
		GVariant *unbox = NULL;
		/* Used to get icon data */
		gboolean is_exist;
		gint icon_quali, icon_identifier, width, height, ics, icon_data_len;
		gchar *icon_data = NULL;
		/* Used to get icon list data */
		GVariant *unbox_list, *unbox_list_info ;
		GVariant *icon_list_info;
		gboolean is_list_exist;
		gint icon_list_quali, list_cnt, icon_list_identifier, list_width, list_height, list_ics, icon_list_data_len;
		gchar *icon_list_data = NULL;
#else
		int index = 0;
		GVariant *unbox;
		GVariantIter *iter;
#endif
		memset(&setup_menu, 0, sizeof(TelSatSetupMenuInfo_t));

#if defined(TIZEN_SUPPORT_SAT_ICON)
		g_variant_get(param, "(ibs@vibb@v@v)", &command_id, &b_present, &title, &items, &item_cnt,
					&b_helpinfo, &b_updated, &icon_id, &icon_list);
#else
		g_variant_get(param, "(ibs@vibb)", &command_id, &b_present, &title, &items, &item_cnt,
			&b_helpinfo, &b_updated);
#endif

		setup_menu.commandId = command_id;
		setup_menu.bIsMainMenuPresent = (b_present ? 1 : 0);
		memcpy(setup_menu.satMainTitle, title, TAPI_SAT_DEF_TITLE_LEN_MAX+1);
		setup_menu.satMainMenuNum = item_cnt;
		if(items && item_cnt > 0){
			gchar *item_str;
			gint item_id;
			unbox = g_variant_get_variant(items);
			dbg("items(%p) items type_format(%s)", items, g_variant_get_type_string(unbox));

			g_variant_get(unbox, "a(si)", &iter);
			while(g_variant_iter_loop(iter,"(si)",&item_str, &item_id)){
				setup_menu.satMainMenuItem[index].itemId = item_id;
				memcpy(setup_menu.satMainMenuItem[index].itemString, item_str, TAPI_SAT_DEF_ITEM_STR_LEN_MAX + 6);
				dbg("item index(%d) id(%d) str(%s)",index, setup_menu.satMainMenuItem[index].itemId, setup_menu.satMainMenuItem[index].itemString);
				//dbg("item index(%d) id(%d) str(%s)",index, item_id, item_str);
				index++;
			}
			g_variant_iter_free(iter);
		}
		setup_menu.bIsSatMainMenuHelpInfo = (b_helpinfo ? 1 : 0);
		setup_menu.bIsUpdatedSatMainMenu = (b_updated ? 1 : 0);

#if defined(TIZEN_SUPPORT_SAT_ICON)
		if(icon_id) {
			unbox = g_variant_get_variant(icon_id);
			g_variant_get(unbox, "a(biiiiiis)", &iter);

			while(g_variant_iter_loop(iter,"(biiiiiis)", &is_exist, &icon_quali, &icon_identifier, &width, &height, &ics, &icon_data_len, &icon_data)){
				if(!is_exist)
					break;
				setup_menu.iconId.bIsPresent = is_exist;
				setup_menu.iconId.iconQualifier = icon_quali;
				setup_menu.iconId.iconIdentifier = icon_identifier;
				setup_menu.iconId.iconInfo.width = width;
				setup_menu.iconId.iconInfo.height = height;
				setup_menu.iconId.iconInfo.ics = ics;
				if(icon_data_len > 0) {
					setup_menu.iconId.iconInfo.iconDataLen = icon_data_len;
					memcpy(setup_menu.iconId.iconInfo.iconFile, icon_data, icon_data_len);
				}
				dbg("icon exist(%d), icon_quali: (%d), icon_id: (%d), width: (%d), height: (%d), ics: (%d), icon_data_len: (%d)", setup_menu.iconId.bIsPresent, setup_menu.iconId.iconQualifier, setup_menu.iconId.iconIdentifier, setup_menu.iconId.iconInfo.width,
					setup_menu.iconId.iconInfo.height, setup_menu.iconId.iconInfo.ics, setup_menu.iconId.iconInfo.iconDataLen);
			}
			g_variant_iter_free(iter);
		}

		if(icon_list){
			unbox_list = g_variant_get_variant(icon_list);
			g_variant_get(unbox_list, "a(biiv)", &iter);

			while(g_variant_iter_loop(iter,"(biiv)", &is_list_exist, &icon_list_quali, &list_cnt, &icon_list_info)){
				if(!is_list_exist)
					break;
				setup_menu.iconIdList.bIsPresent = is_list_exist;
				setup_menu.iconIdList.iconListQualifier = icon_list_quali;
				setup_menu.iconIdList.iconCount = list_cnt;

				unbox_list_info = g_variant_get_variant(icon_list_info);
				g_variant_get(unbox_list_info, "a(iiiiis)", &iter2);

				while(g_variant_iter_loop(iter2,"(iiiiis)",&icon_list_identifier, &list_width, &list_height, &list_ics, &icon_list_data_len, &icon_list_data)){
					setup_menu.iconIdList.iconIdentifierList[icon_index]= icon_identifier;
					setup_menu.iconIdList.iconInfo[icon_index].width = list_width;
					setup_menu.iconIdList.iconInfo[icon_index].height = list_height;
					setup_menu.iconIdList.iconInfo[icon_index].ics = list_ics;
					if(icon_list_data_len > 0) {
						setup_menu.iconIdList.iconInfo[icon_index].iconDataLen = icon_list_data_len;
						memcpy(setup_menu.iconIdList.iconInfo[icon_index].iconFile, icon_list_data, icon_list_data_len);
					}
					icon_index++;
				}
				g_variant_iter_free(iter2);
			}
			g_variant_iter_free(iter);
		}
#endif
		dbg("command id (%d)", setup_menu.commandId);
		dbg("menu present (%d)", setup_menu.bIsMainMenuPresent);
		dbg("menu title (%s)", setup_menu.satMainTitle);
		dbg("item cnt (%d)", setup_menu.satMainMenuNum);
		dbg("menu help info (%d)", setup_menu.bIsSatMainMenuHelpInfo);
		dbg("menu updated (%d)", setup_menu.bIsUpdatedSatMainMenu);

		dbg("icon exist(%d), icon_quali: (%d), icon_id: (%d), width: (%d), height: (%d), ics: (%d), icon_data_len: (%d)", setup_menu.iconId.bIsPresent, setup_menu.iconId.iconQualifier, setup_menu.iconId.iconIdentifier, setup_menu.iconId.iconInfo.width,
			setup_menu.iconId.iconInfo.height, setup_menu.iconId.iconInfo.ics, setup_menu.iconId.iconInfo.iconDataLen);

		CALLBACK_CALL(&setup_menu);
	}
	else if (!g_strcmp0(sig, "DisplayText")) {
		TelSatDisplayTextInd_t display_text;
		gchar* text;
		gint command_id, text_len, duration;
		gboolean high_priority, user_rsp_required, immediately_rsp;

#if defined(TIZEN_SUPPORT_SAT_ICON)
		GVariant *unbox = NULL;
		gboolean is_exist;
		gint icon_quali, icon_identifier, width, height, ics, icon_data_len;
		gchar *icon_data = NULL;
		GVariant *icon_id = NULL;
		GVariantIter *iter;
#endif
		memset(&display_text, 0, sizeof(TelSatDisplayTextInd_t));

#if defined(TIZEN_SUPPORT_SAT_ICON)
		g_variant_get(param, "(isiibbb@v)", &command_id, &text, &text_len, &duration,
			&high_priority, &user_rsp_required, &immediately_rsp, &icon_id);
#else
		g_variant_get(param, "(isiibbb)", &command_id, &text, &text_len, &duration,
			&high_priority, &user_rsp_required, &immediately_rsp);
#endif
		display_text.commandId = command_id;
		memcpy(display_text.text.string, text, TAPI_SAT_DEF_TEXT_STRING_LEN_MAX+1);
		display_text.text.stringLen = text_len;
		display_text.duration = duration;
		display_text.bIsPriorityHigh = (high_priority ? 1 : 0);
		display_text.bIsUserRespRequired = (user_rsp_required ? 1 : 0);
		display_text.b_immediately_resp = (immediately_rsp ? 1 : 0);

#if defined(TIZEN_SUPPORT_SAT_ICON)
		if(icon_id) {
			unbox = g_variant_get_variant(icon_id);
			g_variant_get(unbox, "a(biiiiiis)", &iter);

			while(g_variant_iter_loop(iter,"(biiiiiis)", &is_exist, &icon_quali, &icon_identifier, &width, &height, &ics, &icon_data_len, &icon_data)) {
				if(!is_exist)
					break;
				display_text.iconId.bIsPresent = is_exist;
				display_text.iconId.iconQualifier = icon_quali;
				display_text.iconId.iconIdentifier = icon_identifier;
				display_text.iconId.iconInfo.width = width;
				display_text.iconId.iconInfo.height = height;
				display_text.iconId.iconInfo.ics = ics;
				if(icon_data_len > 0) {
					display_text.iconId.iconInfo.iconDataLen = icon_data_len;
					memcpy(display_text.iconId.iconInfo.iconFile, icon_data, icon_data_len);
				}
				dbg("icon exist(%d), icon_quali: (%d), icon_id: (%d), width: (%d), height: (%d), ics: (%d), icon_data_len: (%d)", display_text.iconId.bIsPresent, display_text.iconId.iconQualifier, display_text.iconId.iconIdentifier, display_text.iconId.iconInfo.width,
					display_text.iconId.iconInfo.height, display_text.iconId.iconInfo.ics, display_text.iconId.iconInfo.iconDataLen);
			}
			g_variant_iter_free(iter);
		}
#endif
		dbg("command id (%d)", display_text.commandId);
		dbg("display text (%s)", display_text.text.string);
		dbg("string len(%d)", display_text.text.stringLen);
		dbg("duration (%d)", display_text.duration);
		dbg("high priority (%d)", display_text.bIsPriorityHigh);
		dbg("user response required(%d)", display_text.bIsUserRespRequired);
		dbg("immediately response (%d)", display_text.b_immediately_resp);

		CALLBACK_CALL(&display_text);
	}
	else if (!g_strcmp0(sig, "SelectItem")) {
		TelSatSelectItemInd_t select_item;

		gboolean help_info ;
		gchar *selected_text;
		gint command_id, default_item_id, menu_cnt, text_len =0;
		GVariant *menu_items;
#if defined(TIZEN_SUPPORT_SAT_ICON)
		GVariantIter *iter, *iter2;
		GVariant *unbox = NULL;
		gboolean is_exist;
		gint icon_quali, icon_identifier, width, height, ics, icon_data_len;
		gchar *icon_data = NULL;
		GVariant *icon_id = NULL;
		GVariant *icon_list = NULL;
		int index = 0, icon_index = 0;
		/* Used to get icon list data */
		GVariant *unbox_list, *unbox_list_info ;
		GVariant *icon_list_info;
		gboolean is_list_exist;
		gint icon_list_quali, list_cnt, icon_list_identifier, list_width, list_height, list_ics, icon_list_data_len;
		gchar *icon_list_data = NULL;
#else
		int index = 0;
		GVariant *unbox;
		GVariantIter *iter;
#endif
		memset(&select_item, 0, sizeof(TelSatSelectItemInd_t));

#if defined(TIZEN_SUPPORT_SAT_ICON)
		g_variant_get(param, "(ibsiii@v@v@v)", &command_id, &help_info, &selected_text,
			&text_len, &default_item_id, &menu_cnt, &menu_items, &icon_id, &icon_list);
#else
		g_variant_get(param, "(ibsiii@v)", &command_id, &help_info, &selected_text,
			&text_len, &default_item_id, &menu_cnt, &menu_items);
#endif
		select_item.commandId = command_id;
		select_item.bIsHelpInfoAvailable = (help_info ? 1 : 0);
		memcpy(select_item.text.string, selected_text, TAPI_SAT_DEF_TITLE_LEN_MAX+1);
		select_item.text.stringLen = text_len;
		select_item.defaultItemIndex = default_item_id;
		select_item.menuItemCount = menu_cnt;
		if(menu_items && menu_cnt > 0){
			gchar *item_str;
			gint item_id, item_len;
			unbox = g_variant_get_variant(menu_items);
			dbg("items(%p) items type_format(%s)", menu_items, g_variant_get_type_string(unbox));

			g_variant_get(unbox, "a(iis)", &iter);
			while(g_variant_iter_loop(iter,"(iis)",&item_id, &item_len, &item_str)){
				select_item.menuItem[index].itemId = item_id;
				select_item.menuItem[index].textLen = item_len;
				memcpy(select_item.menuItem[index].text, item_str, TAPI_SAT_ITEM_TEXT_LEN_MAX + 1);
				dbg("item index(%d) id(%d) len(%d) str(%s)", index,
						select_item.menuItem[index].itemId, select_item.menuItem[index].textLen, select_item.menuItem[index].text);
				index++;
			}
			g_variant_iter_free(iter);
		}

#if defined(TIZEN_SUPPORT_SAT_ICON)
		if(icon_id) {
			unbox = g_variant_get_variant(icon_id);
			g_variant_get(unbox, "a(biiiiiis)", &iter);

			while(g_variant_iter_loop(iter,"(biiiiiis)", &is_exist, &icon_quali, &icon_identifier, &width, &height, &ics, &icon_data_len, &icon_data)) {
				if(!is_exist)
					break;
				select_item.iconId.bIsPresent = is_exist;
				select_item.iconId.iconQualifier = icon_quali;
				select_item.iconId.iconIdentifier = icon_identifier;
				select_item.iconId.iconInfo.width = width;
				select_item.iconId.iconInfo.height = height;
				select_item.iconId.iconInfo.ics = ics;
				if(icon_data_len > 0) {
					select_item.iconId.iconInfo.iconDataLen = icon_data_len;
					memcpy(select_item.iconId.iconInfo.iconFile, icon_data, icon_data_len);
				}
				dbg("icon exist(%d), icon_quali: (%d), icon_id: (%d), width: (%d), height: (%d), ics: (%d), icon_data_len: (%d)", select_item.iconId.bIsPresent, select_item.iconId.iconQualifier, select_item.iconId.iconIdentifier, select_item.iconId.iconInfo.width,
						select_item.iconId.iconInfo.height, select_item.iconId.iconInfo.ics, select_item.iconId.iconInfo.iconDataLen);
			}
			g_variant_iter_free(iter);
		}

		if(icon_list){
			unbox_list = g_variant_get_variant(icon_list);
			g_variant_get(unbox_list, "a(biiv)", &iter);

			while(g_variant_iter_loop(iter,"(biiv)", &is_list_exist, &icon_list_quali, &list_cnt, &icon_list_info)) {
				if(!is_list_exist)
					break;
				select_item.iconIdList.bIsPresent = is_list_exist;
				select_item.iconIdList.iconListQualifier = icon_list_quali;
				select_item.iconIdList.iconCount = list_cnt;

				unbox_list_info = g_variant_get_variant(icon_list_info);
				g_variant_get(unbox_list_info, "a(iiiiis)", &iter2);

				while(g_variant_iter_loop(iter2,"(iiiiis)",&icon_list_identifier, &list_width, &list_height, &list_ics, &icon_list_data_len, &icon_list_data)){
					select_item.iconIdList.iconIdentifierList[icon_index]= icon_identifier;
					select_item.iconIdList.iconInfo[icon_index].width = list_width;
					select_item.iconIdList.iconInfo[icon_index].height = list_height;
					select_item.iconIdList.iconInfo[icon_index].ics = list_ics;
					if(icon_list_data_len > 0) {
						select_item.iconIdList.iconInfo[icon_index].iconDataLen = icon_list_data_len;
						memcpy(select_item.iconIdList.iconInfo[icon_index].iconFile, icon_list_data, icon_list_data_len);
					}
					icon_index++;
				}
				g_variant_iter_free(iter2);
			}
			g_variant_iter_free(iter);
		}
#endif
		dbg("command id (%d)", select_item.commandId);
		dbg("help info(%d)", select_item.bIsHelpInfoAvailable);
		dbg("selected item string(%s)", select_item.text.string);
		dbg("string len(%d)", select_item.text.stringLen);
		dbg("default item index(%d)", select_item.defaultItemIndex);
		dbg("item count(%d)", select_item.menuItemCount);

		CALLBACK_CALL(&select_item);
	}
	else if (!g_strcmp0(sig, "GetInkey")) {
		TelSatGetInkeyInd_t get_inkey;

		gint command_id, key_type, input_character_mode;
		gint text_len, duration;
		gboolean b_numeric, b_help_info;
		gchar *text;
#if defined(TIZEN_SUPPORT_SAT_ICON)
		GVariant *unbox = NULL;
		gboolean is_exist;
		gint icon_quali, icon_identifier, width, height, ics, icon_data_len;
		gchar *icon_data = NULL;
		GVariant *icon_id = NULL;
		GVariantIter *iter;
#endif
		memset(&get_inkey, 0, sizeof(TelSatGetInkeyInd_t));

#if defined(TIZEN_SUPPORT_SAT_ICON)
		g_variant_get(param, "(iiibbsii@v)", &command_id, &key_type, &input_character_mode,
			&b_numeric,&b_help_info, &text, &text_len, &duration, &icon_id);
#else
		g_variant_get(param, "(iiibbsii)", &command_id, &key_type, &input_character_mode,
			&b_numeric,&b_help_info, &text, &text_len, &duration);
#endif
		get_inkey.commandId = command_id;
		get_inkey.keyType = key_type;
		get_inkey.inputCharMode = input_character_mode;
		get_inkey.bIsNumeric = (b_numeric ? 1 : 0);
		get_inkey.bIsHelpInfoAvailable = (b_help_info ? 1 : 0);
		memcpy(get_inkey.text.string, text, TAPI_SAT_DEF_TEXT_STRING_LEN_MAX+1);
		get_inkey.text.stringLen = text_len;
		get_inkey.duration = duration;

#if defined(TIZEN_SUPPORT_SAT_ICON)
		if(icon_id) {
			unbox = g_variant_get_variant(icon_id);
			g_variant_get(unbox, "a(biiiiiis)", &iter);

			while(g_variant_iter_loop(iter,"(biiiiiis)", &is_exist, &icon_quali, &icon_identifier, &width, &height, &ics, &icon_data_len, &icon_data)) {
				if(!is_exist)
					break;
				get_inkey.iconId.bIsPresent = is_exist;
				get_inkey.iconId.iconQualifier = icon_quali;
				get_inkey.iconId.iconIdentifier = icon_identifier;
				get_inkey.iconId.iconInfo.width = width;
				get_inkey.iconId.iconInfo.height = height;
				get_inkey.iconId.iconInfo.ics = ics;
				if(icon_data_len > 0) {
					get_inkey.iconId.iconInfo.iconDataLen = icon_data_len;
					memcpy(get_inkey.iconId.iconInfo.iconFile, icon_data, icon_data_len);
				}
				dbg("icon exist(%d), icon_quali: (%d), icon_id: (%d), width: (%d), height: (%d), ics: (%d), icon_data_len: (%d)", get_inkey.iconId.bIsPresent, get_inkey.iconId.iconQualifier, get_inkey.iconId.iconIdentifier, get_inkey.iconId.iconInfo.width,
					get_inkey.iconId.iconInfo.height, get_inkey.iconId.iconInfo.ics, get_inkey.iconId.iconInfo.iconDataLen);
			}
			g_variant_iter_free(iter);
		}
#endif
		dbg("command id(%d)", get_inkey.commandId);
		dbg("key type(%d)", get_inkey.keyType);
		dbg("input character mode(%d)", get_inkey.inputCharMode);
		dbg("numeric(%d)", get_inkey.bIsNumeric);
		dbg("help info available(%d)", get_inkey.bIsHelpInfoAvailable);
		dbg("text (%s)", get_inkey.text.string);
		dbg("text length", get_inkey.text.stringLen);
		dbg("duration", get_inkey.duration);

		CALLBACK_CALL(&get_inkey);
	}
	else if (!g_strcmp0(sig, "GetInput")) {
		TelSatGetInputInd_t get_input;

		gint command_id, input_character_mode;
		gint text_len, def_text_len, rsp_len_min, rsp_len_max;
		gboolean b_numeric, b_help_info, b_echo_input;
		gchar *text, *def_text;
#if defined(TIZEN_SUPPORT_SAT_ICON)
		GVariant *unbox = NULL;
		gboolean is_exist;
		gint icon_quali, icon_identifier, width, height, ics, icon_data_len;
		gchar *icon_data = NULL;
		GVariant *icon_id = NULL;
		GVariantIter *iter;
#endif
		memset(&get_input, 0, sizeof(TelSatGetInputInd_t));

#if defined(TIZEN_SUPPORT_SAT_ICON)
		g_variant_get(param, "(iibbbsiiisi@v)", &command_id, &input_character_mode, &b_numeric, &b_help_info, &b_echo_input,
			&text, &text_len, &rsp_len_max, &rsp_len_min, &def_text, &def_text_len, &icon_id);
#else
		g_variant_get(param, "(iibbbsiiisi)", &command_id, &input_character_mode, &b_numeric, &b_help_info, &b_echo_input,
			&text, &text_len, &rsp_len_max, &rsp_len_min, &def_text, &def_text_len);
#endif
		get_input.commandId = command_id;
		get_input.inputCharMode = input_character_mode;
		get_input.bIsNumeric = (b_numeric ? 1 : 0);
		get_input.bIsHelpInfoAvailable = (b_help_info ? 1 : 0);
		get_input.bIsEchoInput = (b_echo_input ? 1 : 0);
		memcpy(get_input.text.string, text, TAPI_SAT_DEF_TEXT_STRING_LEN_MAX+1);
		get_input.text.stringLen = text_len;
		get_input.respLen.max = rsp_len_max;
		get_input.respLen.min = rsp_len_min;
		memcpy(get_input.defaultText.string, def_text, TAPI_SAT_DEF_TEXT_STRING_LEN_MAX+1);
		get_input.defaultText.stringLen = def_text_len;

#if defined(TIZEN_SUPPORT_SAT_ICON)
		if(icon_id) {
			unbox = g_variant_get_variant(icon_id);
			g_variant_get(unbox, "a(biiiiiis)", &iter);

			while(g_variant_iter_loop(iter,"(biiiiiis)", &is_exist, &icon_quali, &icon_identifier, &width, &height, &ics, &icon_data_len, &icon_data)) {
				if(!is_exist)
					break;
				get_input.iconId.bIsPresent = is_exist;
				get_input.iconId.iconQualifier = icon_quali;
				get_input.iconId.iconIdentifier = icon_identifier;
				get_input.iconId.iconInfo.width = width;
				get_input.iconId.iconInfo.height = height;
				get_input.iconId.iconInfo.ics = ics;
				if(icon_data_len > 0) {
					get_input.iconId.iconInfo.iconDataLen = icon_data_len;
					memcpy(get_input.iconId.iconInfo.iconFile, icon_data, icon_data_len);
				}
				dbg("icon exist(%d), icon_quali: (%d), icon_id: (%d), width: (%d), height: (%d), ics: (%d), icon_data_len: (%d)", get_input.iconId.bIsPresent, get_input.iconId.iconQualifier, get_input.iconId.iconIdentifier, get_input.iconId.iconInfo.width,
					get_input.iconId.iconInfo.height, get_input.iconId.iconInfo.ics, get_input.iconId.iconInfo.iconDataLen);
			}
			g_variant_iter_free(iter);
		}
#endif
		dbg("command id(%d)", get_input.commandId);
		dbg("input character mode(%d)", get_input.inputCharMode);
		dbg("numeric(%d)", get_input.bIsNumeric);
		dbg("help info avaiable(%d)", get_input.bIsHelpInfoAvailable);
		dbg("echo input(%d)", get_input.bIsEchoInput);
		dbg("text(%s)", get_input.text.string);
		dbg("text length(%d)", get_input.text.stringLen);
		dbg("response length max(%d)", get_input.respLen.max);
		dbg("response length min(%d)", get_input.respLen.min);
		dbg("default text(%s)", get_input.defaultText.string);
		dbg("default text length(%d)", get_input.defaultText.stringLen);

		CALLBACK_CALL(&get_input);
	}
	else if (!g_strcmp0(sig, "SendSMS")) {
		TelSatSendSmsIndSmsData_t send_sms;

		gint command_id, ton, npi, tpdu_type;
		gboolean b_packing_required;
		gint text_len, number_len, tpdu_data_len;
		gchar* text, *dialling_number;
		GVariant *tpdu_data;

		memset(&send_sms, 0, sizeof(TelSatSendSmsIndSmsData_t));

		g_variant_get(param, "(isibiisii@vi)", &command_id, &text, &text_len, &b_packing_required, &ton, &npi,
					&dialling_number, &number_len, &tpdu_type, &tpdu_data, &tpdu_data_len);

		send_sms.commandId = command_id;
		send_sms.bIsPackingRequired = (b_packing_required ? 1 : 0);

		send_sms.address.ton = ton;
		send_sms.address.npi = npi;
		send_sms.address.diallingNumberLen = number_len;
		memcpy(send_sms.address.diallingNumber, dialling_number, TAPI_SAT_DIALLING_NUMBER_LEN_MAX);

		send_sms.smsTpdu.tpduType = tpdu_type;
		send_sms.smsTpdu.dataLen = tpdu_data_len;

		if(tpdu_data){
			int index = 0;
			guchar data;
			GVariantIter *iter = NULL;
			GVariant *inner_gv = NULL;

			inner_gv = g_variant_get_variant(tpdu_data);
			dbg("tpdu data exist type_format(%s)", g_variant_get_type_string(inner_gv));

			g_variant_get(inner_gv, "ay", &iter);
			while( g_variant_iter_loop (iter, "y", &data)){
				dbg("index(%d) data(%c)", index, data);
				send_sms.smsTpdu.data[index] = data;
				index++;
			}
			g_variant_iter_free(iter);
			g_variant_unref(inner_gv);
		}

		dbg("command id(%d)", send_sms.commandId);
		dbg("packing required(%d)", send_sms.bIsPackingRequired);
		dbg("address ton(%d)", send_sms.address.ton);
		dbg("address npi(%d)", send_sms.address.npi);
		dbg("address dialing number (%s)", send_sms.address.diallingNumber);
		dbg("address number length (%d)", send_sms.address.diallingNumberLen);
		dbg("tpdu type (%d)", send_sms.smsTpdu.tpduType);
		dbg("tpdu length (%d)", send_sms.smsTpdu.dataLen);

		CALLBACK_CALL(&send_sms);
	}
	else if (!g_strcmp0(sig, "SetupEventList")) {
		int g_index = 0;
		gint event_cnt;
		GVariant *evt_list;
		TelSatEventListData_t event_list;

		memset(&event_list, 0, sizeof(TelSatEventListData_t));

		g_variant_get(param, "(i@v)", &event_cnt, &evt_list);

		if(evt_list){
			guchar data;
			GVariantIter *iter = NULL;
			GVariant *inner_gv = NULL;

			inner_gv = g_variant_get_variant(evt_list);
			dbg("event list exist type_format(%s)", g_variant_get_type_string(inner_gv));

			g_variant_get(inner_gv, "ai", &iter);
			while( g_variant_iter_loop (iter, "i", &data)){
				dbg("g_index(%d) event(%d)", g_index, data);
				g_event_list[g_index] = data;

				if(data == TAPI_EVENT_SAT_DW_TYPE_IDLE_SCREEN_AVAILABLE){
					event_list.bIsIdleScreenAvailable = 1;
				}
				else if(data == TAPI_EVENT_SAT_DW_TYPE_LANGUAGE_SELECTION){
					event_list.bIsLanguageSelection = 1;
				}
				else if(data == TAPI_EVENT_SAT_DW_TYPE_BROWSER_TERMINATION){
					event_list.bIsBrowserTermination = 1;
				}
				else if(data == TAPI_EVENT_SAT_DW_TYPE_DATA_AVAILABLE){
					event_list.bIsDataAvailable = 1;
				}
				else if(data == TAPI_EVENT_SAT_DW_TYPE_CHANNEL_STATUS){
					event_list.bIsChannelStatus = 1;
				}

				g_index++;
			}
			//while end
			g_variant_iter_free(iter);
			g_variant_unref(inner_gv);
		}

		dbg("event list cnt(%d)", event_cnt);

		CALLBACK_CALL(&event_list);
	}
	else if (!g_strcmp0(sig, "Refresh")) {
		TelSatRefreshInd_t refresh_info;

		gint command_id = 0;
		gint refresh_type =0;
		gint file_cnt = 0;
		GVariant *file_list = NULL;

		memset(&refresh_info, 0, sizeof(TelSatRefreshInd_t));

		g_variant_get(param, "(ii@v)", &command_id, &refresh_type, &file_list);

		refresh_info.commandId = command_id;
		refresh_info.refreshMode = refresh_type;

		if(file_list){
			int g_index = 0;
			guchar data;
			GVariantIter *iter = NULL;
			GVariant *inner_gv = NULL;

			inner_gv = g_variant_get_variant(file_list);
			dbg("file list exist type_format(%s)", g_variant_get_type_string(inner_gv));

			g_variant_get(inner_gv, "ai", &iter);
			while( g_variant_iter_loop (iter, "i", &data)){
				dbg("g_index(%d) file id(%d)", g_index, data);
				refresh_info.fileId[g_index] = data;
				g_index++;
			}
			file_cnt = g_index;

			//while end
			g_variant_iter_free(iter);
			g_variant_unref(inner_gv);
		}
		refresh_info.fileCount = file_cnt;

		dbg("refresh event/file cnt(%d)", refresh_info.fileCount);

		CALLBACK_CALL(&refresh_info);
	}
	else if (!g_strcmp0(sig, "SendDtmf")) {
		TelSatSendDtmfIndDtmfData_t send_dtmf;

		gint command_id = 0;
		gint text_len = 0, dtmf_str_len = 0;
		gchar *text = NULL;
		gchar *dtmf_str = NULL;

		memset(&send_dtmf, 0, sizeof(TelSatSendDtmfIndDtmfData_t));

		g_variant_get(param, "(isisi)", &command_id, &text, &text_len, &dtmf_str, &dtmf_str_len);

		send_dtmf.commandId = command_id;
		send_dtmf.bIsHiddenMode = 1;

		send_dtmf.dtmfString.stringLen = dtmf_str_len;
		memcpy(send_dtmf.dtmfString.string, dtmf_str, TAPI_SAT_DEF_TEXT_STRING_LEN_MAX+1);

		dbg("dtmf event command id(%d)", send_dtmf.commandId);
		dbg("dtmf event dtmf(%s)", send_dtmf.dtmfString.string);

		CALLBACK_CALL(&send_dtmf);
	}
	else if (!g_strcmp0(sig, "EndProactiveSession")) {
		int command_type = 0;

		g_variant_get(param, "(i)", &command_type);
		dbg("end session evt : command type(%d)", command_type);
		CALLBACK_CALL(&command_type);
	}
	else if (!g_strcmp0(sig, "CallControlResult")) {
		TelSatCallCtrlIndData_t call_ctrl_result_ind;
		gint call_ctrl_result = 0, disp_len = 0;
		gint bc_repeat_indicator = 0, ton = 0x0F, npi=0X0F;
		gchar *text = NULL, *call_num = NULL, *ss_string = NULL, *sub_addr = NULL, *ccp1 = NULL, *ccp2 = NULL;

		memset(&call_ctrl_result_ind, 0x00, sizeof(TelSatCallCtrlIndData_t));

		g_variant_get(param, "(isiisssssi)", &call_ctrl_result, &text, &ton, &npi, &call_num,
			&ss_string, &sub_addr, &ccp1, &ccp2, &bc_repeat_indicator);

		call_ctrl_result_ind.callCtrlResult = call_ctrl_result;
		disp_len = strlen(text); //alpha id
		if(disp_len >1) {
			call_ctrl_result_ind.dispData.stringLen = disp_len;
			memcpy(&call_ctrl_result_ind.dispData.string, text, disp_len);
			call_ctrl_result_ind.bIsUserInfoDisplayEnabled = 1;
		}

		if(strlen(call_num) > 1 && (g_strcmp0(call_num,"") != 0) ){
			call_ctrl_result_ind.callCtrlCnfType = TAPI_SAT_CALL_TYPE_MO_VOICE;
			call_ctrl_result_ind.u.callCtrlCnfCallData.address.stringLen = strlen(call_num);
			memcpy(&call_ctrl_result_ind.u.callCtrlCnfCallData.address.string, call_num, strlen(call_num));
			call_ctrl_result_ind.u.callCtrlCnfCallData.subAddress.stringLen = strlen(sub_addr);
			memcpy(&call_ctrl_result_ind.u.callCtrlCnfCallData.subAddress.string, sub_addr, strlen(sub_addr));
			call_ctrl_result_ind.u.callCtrlCnfCallData.ccp1.stringLen = strlen(ccp1);
			memcpy(&call_ctrl_result_ind.u.callCtrlCnfCallData.ccp1.string, ccp1, strlen(ccp1));
			call_ctrl_result_ind.u.callCtrlCnfCallData.ccp1.stringLen = strlen(ccp2);
			memcpy(&call_ctrl_result_ind.u.callCtrlCnfCallData.ccp1.string, ccp2, strlen(ccp2));
			call_ctrl_result_ind.u.callCtrlCnfCallData.bcRepeatIndicator = bc_repeat_indicator;
		}//call number exist
		else if( strlen(ss_string) > 1 && (g_strcmp0(ss_string,"") != 0) ){
			call_ctrl_result_ind.callCtrlCnfType = TAPI_SAT_CALL_TYPE_SS;
			call_ctrl_result_ind.u.callCtrlCnfSsData.ssString.stringLen = strlen(ss_string);
			memcpy(&call_ctrl_result_ind.u.callCtrlCnfSsData.ssString.string, ss_string, strlen(ss_string));
			call_ctrl_result_ind.u.callCtrlCnfSsData.subAddress.stringLen = strlen(sub_addr);
			memcpy(&call_ctrl_result_ind.u.callCtrlCnfSsData.subAddress.string, sub_addr, strlen(sub_addr));
			call_ctrl_result_ind.u.callCtrlCnfSsData.ccp1.stringLen = strlen(ccp1);
			memcpy(&call_ctrl_result_ind.u.callCtrlCnfSsData.ccp1.string, ccp1, strlen(ccp1));
			call_ctrl_result_ind.u.callCtrlCnfSsData.ccp1.stringLen = strlen(ccp2);
			memcpy(&call_ctrl_result_ind.u.callCtrlCnfSsData.ccp1.string, ccp2, strlen(ccp2));
			call_ctrl_result_ind.u.callCtrlCnfSsData.bcRepeatIndicator = bc_repeat_indicator;
		}//ss string exist
		else{
			dbg("not matched call control");
			return;
		}

		CALLBACK_CALL(&call_ctrl_result_ind);
	}
	else if (!g_strcmp0(sig, "MoSmControlResult")) {
		TelSatMoSmCtrlIndData_t mo_sm_ctrl_result_ind;
		gint call_ctrl_result = 0 ,disp_len = 0;
		gint rp_dst_ton = 0x0F, rp_dst_npi = 0X0F, tp_dst_ton = 0x0F, tp_dst_npi = 0X0F;
		gchar *text = NULL, *rp_dst_call_num = NULL, *tp_dst_call_num = NULL;

		memset(&mo_sm_ctrl_result_ind, 0x00, sizeof(TelSatMoSmCtrlIndData_t));

		g_variant_get(param, "(isiisiis)", &call_ctrl_result, &text,
			&rp_dst_ton, &rp_dst_npi, &rp_dst_call_num, &tp_dst_ton, &tp_dst_npi, &tp_dst_call_num);

		mo_sm_ctrl_result_ind.moSmsCtrlResult= call_ctrl_result;
		disp_len = strlen(text); //alpha id
		if(disp_len >1) {
			mo_sm_ctrl_result_ind.dispData.stringLen = disp_len;
			memcpy(&mo_sm_ctrl_result_ind.dispData.string, text, disp_len);
			mo_sm_ctrl_result_ind.bIsUserInfoDisplayEnabled = 1;
		}

		if(strlen(rp_dst_call_num) > 1 && (g_strcmp0(rp_dst_call_num,"") != 0) ){
			mo_sm_ctrl_result_ind.tpDestAddr.bIsDigitOnly = 1;
			mo_sm_ctrl_result_ind.rpDestAddr.stringLen = strlen(rp_dst_call_num);
			memcpy(&mo_sm_ctrl_result_ind.rpDestAddr.string, rp_dst_call_num, strlen(rp_dst_call_num));
		}// rp dst call number exist
		else if( strlen(tp_dst_call_num) > 1 && (g_strcmp0(tp_dst_call_num,"") != 0) ){
			mo_sm_ctrl_result_ind.tpDestAddr.bIsDigitOnly = 1;
			mo_sm_ctrl_result_ind.tpDestAddr.stringLen = strlen(tp_dst_call_num);
			memcpy(&mo_sm_ctrl_result_ind.tpDestAddr.string, tp_dst_call_num, strlen(tp_dst_call_num));
		}//tp dst call number exist
		else{
			dbg("Any destination address are not provided, use default one.");
		}

		CALLBACK_CALL(&mo_sm_ctrl_result_ind);
	}
	else {
		dbg("not handled Sat noti[%s]", sig);
	}
}

static void _process_sim_event(const gchar *sig, GVariant *param,
	TapiHandle *handle, char *noti_id, struct tapi_evt_cb *evt_cb_data)
{
	TAPI_RETURN_IF_FAIL(evt_cb_data);

	if (!g_strcmp0(sig, "Status")) {
		int status = 0;
		g_variant_get(param, "(i)", &status);
		CALLBACK_CALL(&status);
	} else if (!g_strcmp0(sig, "Refreshed")) {
		int type = 0;
		g_variant_get(param, "(i)", &type);
		CALLBACK_CALL(&type);
	} else {
		dbg("not handled SIM noti[%s]",sig );
	}
}

static void _process_pb_event(const gchar *sig, GVariant *param,
	TapiHandle *handle, char *noti_id, struct tapi_evt_cb *evt_cb_data)
{
	TAPI_RETURN_IF_FAIL(evt_cb_data);

	if (!g_strcmp0(sig, "Status")) {
		TelSimPbStatus_t status;
		g_variant_get(param, "(ibbbbbb)",
			&status.init_completed,
			&status.pb_list.b_fdn,
			&status.pb_list.b_adn,
			&status.pb_list.b_sdn,
			&status.pb_list.b_3g,
			&status.pb_list.b_aas,
			&status.pb_list.b_gas);

		dbg("init[%d] fdn[%d] adn[%d] sdn[%d] usim[%d] aas[%d] gas[%d]",
			status.init_completed, status.pb_list.b_fdn,status.pb_list.b_adn,status.pb_list.b_sdn,status.pb_list.b_3g,status.pb_list.b_aas,status.pb_list.b_gas);
		CALLBACK_CALL(&status);
	} else {
		dbg("not handled Phonebook noti[%s]",sig );
	}
}

static void _process_sap_event(const gchar *sig, GVariant *param,
	TapiHandle *handle, char *noti_id, struct tapi_evt_cb *evt_cb_data)
{
	TAPI_RETURN_IF_FAIL(evt_cb_data);

	if (!g_strcmp0(sig, "Status")) {
		int noti = 0;
		g_variant_get(param, "(i)", &noti);
		CALLBACK_CALL(&noti);
	} else if (!g_strcmp0(sig, "Disconnect")) {
		int disconnect = 0;
		g_variant_get(param, "(i)", &disconnect);
		CALLBACK_CALL(&disconnect);
	} else {
		dbg("not handled SAP noti[%s]",sig );
	}
}

static void _process_modem_event(const gchar *sig, GVariant *param,
	TapiHandle *handle, char *noti_id, struct tapi_evt_cb *evt_cb_data)
{
	TAPI_RETURN_IF_FAIL(evt_cb_data);

	if (!g_strcmp0(sig, "Power")) {
		int noti = 0;

		g_variant_get(param, "(i)", &noti);

		CALLBACK_CALL(&noti);
	}
	else if (!g_strcmp0(sig, "DunPinCtrl")) {
		tapi_ps_btdun_pincontrol pin_ctrl;
		int signal = 0, status = 0;

		memset(&pin_ctrl, 0, sizeof(tapi_ps_btdun_pincontrol));
		g_variant_get(param, "(ib)", &signal, &status);
		pin_ctrl.signal = signal;
		pin_ctrl.status = status;

		CALLBACK_CALL(&pin_ctrl);
	}
	else if (!g_strcmp0(sig, "DunExternalCall")) {
		gboolean external_call;

		g_variant_get(param, "(b)", &external_call);

		CALLBACK_CALL(&external_call);
	}
	else {
		dbg("not handled Modem noti[%s]", sig);
	}

	return;
}

static void _process_ss_event(const gchar *sig, GVariant *param,
	TapiHandle *handle, char *noti_id, struct tapi_evt_cb *evt_cb_data)
{
	GVariant *value = 0;
	GVariantIter *iter = 0;
	GVariantIter *iter_row = 0;
	const gchar *key = 0;
	int i = 0;

	TAPI_RETURN_IF_FAIL(evt_cb_data);

	if (!g_strcmp0(sig, "NotifyUSSD")) {
		TelSsUssdMsgInfo_t noti;
		char *str = NULL;
		memset(&noti, 0, sizeof(TelSsUssdMsgInfo_t));

		g_variant_get(param, "(iiis)", &noti.Type, &noti.Dcs, &noti.Length, &str);

		if (str) {
			g_strlcpy((char*)noti.szString, str, TAPI_SS_USSD_DATA_SIZE_MAX);
			g_free(str);
		}

		CALLBACK_CALL(&noti);

	} else if (!g_strcmp0(sig, "NotifySsInfo")) {
			TelSsInfo_t noti;
			memset(&noti, 0, sizeof(TelSsInfo_t));

			g_variant_get(param, "(ii)", &noti.Cause, &noti.SsType);

			CALLBACK_CALL(&noti);
	}

	else if (!g_strcmp0(sig, "ReleaseComplete")) {
		TelSsRelCompMsgInfo_t noti;
		GVariant *msg = 0;
		int len = 0;

		memset ( &noti, 0, sizeof( TelSsRelCompMsgInfo_t ));

		g_variant_get(param, "(i@v)", &len, &msg);

		noti.RelCompMsgLen = (unsigned char)len;

		if(msg){
			int i = 0;
			guchar data;
			GVariantIter *iter = NULL;
			GVariant *inner_gv = NULL;

			inner_gv = g_variant_get_variant(msg);
			dbg("[ check ] data exist type_format(%s)", g_variant_get_type_string(inner_gv));

			g_variant_get(inner_gv, "ay", &iter);
			while( g_variant_iter_loop (iter, "y", &data)){
				dbg("index(%d) data(%c)", index, data);
				noti.szRelCompMsg[i] = data;
				i++;
			}
			g_variant_iter_free(iter);
			g_variant_unref(inner_gv);
		}

		CALLBACK_CALL(&noti);

	} else if ( !g_strcmp0(sig, "NotifyForwarding") ) {

		TelSsForwardNoti_t noti;
		memset(&noti, 0, sizeof(TelSsForwardNoti_t));

		g_variant_get (param, "(aa{sv})", &iter);

		noti.record_num = g_variant_iter_n_children(iter);

		while ( g_variant_iter_next(iter, "a{sv}", &iter_row ) ) {
			while ( g_variant_iter_loop( iter_row, "{sv}", &key, &value ) ) {

				if ( !g_strcmp0(key, "ss_class") ) {
					noti.record[i].Class = g_variant_get_int32(value);
				}

				if ( !g_strcmp0(key, "ss_status") ) {
					noti.record[i].Status = g_variant_get_int32(value);
				}

				if ( !g_strcmp0(key, "forwarding_mode") ) {
					noti.record[i].ForwardCondition = g_variant_get_int32(value);
				}

				if ( !g_strcmp0(key, "number_present") ) {
					noti.record[i].bCallForwardingNumberPresent = g_variant_get_int32(value);
				}

				if ( !g_strcmp0(key, "no_reply_time") ) {
					noti.record[i].NoReplyWaitTime = g_variant_get_int32(value);
				}

				if ( !g_strcmp0(key, "type_of_number") ) {
					noti.record[i].Ton = g_variant_get_int32(value);
				}

				if ( !g_strcmp0(key, "number_plan_identity") ) {
					noti.record[i].Npi = g_variant_get_int32(value);
				}

				if ( !g_strcmp0(key, "forwarding_number") ) {
					strncpy((char *)noti.record[i].szCallForwardingNumber, g_variant_get_string(value, 0), TAPI_CALL_DIALDIGIT_LEN_MAX );
				}

			}
			i++;
			g_variant_iter_free(iter_row);
		}
		g_variant_iter_free(iter);

		CALLBACK_CALL(&noti);

	} else if ( !g_strcmp0(sig, "NotifyWaiting") ) {

		TelSsWaitingNoti_t noti;
		memset(&noti, '\0', sizeof(TelSsWaitingNoti_t));

		g_variant_get (param, "(aa{sv})", &iter);

		noti.record_num = g_variant_iter_n_children(iter);

		while ( g_variant_iter_next(iter, "a{sv}", &iter_row ) ) {
			while ( g_variant_iter_loop( iter_row, "{sv}", &key, &value ) ) {

				if ( !g_strcmp0(key, "ss_class") ) {
					noti.record[i].Class = g_variant_get_int32(value);
				}

				if ( !g_strcmp0(key, "ss_status") ) {
					noti.record[i].Status = g_variant_get_int32(value);
				}
			}
			i++;
			g_variant_iter_free(iter_row);
		}
		g_variant_iter_free(iter);

		CALLBACK_CALL(&noti);

	} else if ( !g_strcmp0(sig, "NotifyBarring") ) {

		TelSsBarringNoti_t noti;
		memset(&noti, '\0', sizeof(TelSsBarringNoti_t));

		g_variant_get (param, "(aa{sv})", &iter);

		noti.record_num = g_variant_iter_n_children(iter);

		while ( g_variant_iter_next(iter, "a{sv}", &iter_row ) ) {
			while ( g_variant_iter_loop( iter_row, "{sv}", &key, &value ) ) {

				if ( !g_strcmp0(key, "ss_class") ) {
					noti.record[i].Class = g_variant_get_int32(value);
				}

				if ( !g_strcmp0(key, "ss_status") ) {
					noti.record[i].Status = g_variant_get_int32(value);
				}

				if ( !g_strcmp0(key, "barring_mode") ) {
					noti.record[i].Flavour = g_variant_get_int32(value);
				}

			}
			i++;
			g_variant_iter_free(iter_row);
		}
		g_variant_iter_free(iter);

		CALLBACK_CALL(&noti);

	} else {
		dbg("not handled SS noti[%s]", sig);
	}

	return;
}

static void _process_gps_event(const gchar *sig, GVariant *param,
		TapiHandle *handle, char *noti_id, struct tapi_evt_cb *evt_cb_data)
{
	gboolean b_decode_data = FALSE;
	guchar *decoded_data = NULL;

	TAPI_RETURN_IF_FAIL(evt_cb_data);

	if (!g_strcmp0(sig, "AssistData")) {
		b_decode_data = TRUE;
	}
	else if (!g_strcmp0(sig, "MeasurePosition")) {
		b_decode_data = TRUE;
	}
	else if (!g_strcmp0(sig, "ResetAssistData")) {
		/* noting to decode */
	}
	else if (!g_strcmp0(sig, "FrequencyAiding")) {
		b_decode_data = TRUE;
	}
	else if (!g_strcmp0(sig, "AreaStatus")) {
		struct tel_noti_smart_assistant_area_status noti;
		int area_status = 0, index = 0;

		memset(&noti, 0, sizeof(struct tel_noti_smart_assistant_area_status));
		g_variant_get(param, "(ii)", &area_status, &index);
		noti.area_status = area_status;
		noti.index = index;

		CALLBACK_CALL(&noti);
	}
	else if (!g_strcmp0(sig, "SyncStatus")) {
		struct tel_noti_smart_assistant_sync_status noti;
		int init_status = 0, init_fail_cause = 0;

		memset(&noti, 0, sizeof(struct tel_noti_smart_assistant_sync_status));
		g_variant_get(param, "(ii)", &init_status, &init_fail_cause);
		noti.init_status = init_status;
		noti.init_fail_cause = init_fail_cause;

		CALLBACK_CALL(&noti);
	}
	else {
		dbg("not handled Gps noti[%s]", sig);
	}

	/* decoding data */
	if(b_decode_data) {
		gchar *data = NULL;
		gsize length;
		dbg("[%s] decoding start", sig);

		g_variant_get(param, "(s)", &data);
		decoded_data = g_base64_decode((const gchar *)data, &length);
		if (decoded_data) {
			CALLBACK_CALL(decoded_data);
		}

		dbg("length=%d", length);
	}

	if (decoded_data)
		g_free(decoded_data);
}


static void on_prop_callback(GDBusConnection *conn, const gchar *name, const gchar *path, const gchar *interface,
		const gchar *sig, GVariant *param, gpointer user_data)
{
	TapiHandle *handle = user_data;
	struct tapi_evt_cb *evt_cb_data = NULL;
	const gchar *interface_name_for_signal;
	GVariant *changed_properties = NULL;
	gchar **invalidated_properties = NULL;
	GVariantIter iter;
	gchar *key;
	GVariant *value;
	gchar *prev_value;
	char noti_id[256];
	char *data;

	TAPI_RETURN_IF_FAIL(handle);

	if (!g_variant_is_of_type (param, G_VARIANT_TYPE ("(sa{sv}as)"))) {
		err("PropertiesChanged parameter type mismatch ('%s')", g_variant_get_type_string(param));
		return;
	}

	g_variant_get (param, "(&s@a{sv}^a&s)", &interface_name_for_signal,
			&changed_properties, &invalidated_properties);

	if (!changed_properties) {
		err("Cannot get changed_properties");
		goto fail;
	}

	g_variant_iter_init (&iter, changed_properties);
	while (g_variant_iter_next (&iter, "{sv}", &key, &value)) {
		if (g_variant_is_of_type (value, G_VARIANT_TYPE_STRING )) {
			data = g_try_malloc0 (g_variant_get_size (value) + 3);
			if (!data) {
				warn ("g_try_malloc0 failed");
				g_variant_unref (value);
				continue;
			}
			data[0] = 's';
			data[1] = ':';
			memcpy (data + 2, g_variant_get_data (value),
					g_variant_get_size (value));
		}
		else if (g_variant_is_of_type (value, G_VARIANT_TYPE_BOOLEAN )) {
			data = g_strdup_printf ("b:%d",
					*(guchar *) g_variant_get_data (value));
		}
		else {
			data = g_strdup_printf ("i:%d", *(int *) g_variant_get_data (value));
		}

		g_variant_unref (value);

		memset(noti_id, 0, 256);
		snprintf (noti_id, 255, "%s:%s", interface_name_for_signal, key);

		evt_cb_data = g_hash_table_lookup (handle->evt_list, noti_id);
		if (!evt_cb_data) {
			/* ignore un-registered property change callback */
			continue;
		}

		prev_value = g_hash_table_lookup (handle->cache_property, noti_id);
		if (prev_value) {
			if (g_strcmp0 (data, prev_value) == 0) {
				g_free (data);
				continue;
			}
		}

		dbg("save prop: [%s] - [%s]", noti_id, data);
		g_hash_table_replace (handle->cache_property, g_strdup(noti_id), data);

		{
			int param_i = 0;
			if (data[0] == 's') {
				CALLBACK_CALL((void * ) (data + 2));
			}
			else {
				param_i = atoi (data + 2);
				CALLBACK_CALL((void * )&param_i);
			}
		}
	}

	if (changed_properties != NULL )
		g_variant_unref (changed_properties);

fail:
	if (invalidated_properties)
		g_free (invalidated_properties);
}

static void on_signal_callback(GDBusConnection *conn, const gchar *name, const gchar *path, const gchar *interface,
		const gchar *sig, GVariant *param, gpointer user_data)
{
	TapiHandle *handle = user_data;
	struct tapi_evt_cb *evt_cb_data = NULL;
	char *noti_id;

	TAPI_RETURN_IF_FAIL(handle);

	noti_id = g_strdup_printf("%s:%s", interface, sig);

	evt_cb_data = g_hash_table_lookup(handle->evt_list, noti_id);
	if (!evt_cb_data) {
		dbg("can't find noti_id(%s) callback info", noti_id);
		g_free(noti_id);
		return;
	}

	if (!g_strcmp0(interface, DBUS_TELEPHONY_SMS_INTERFACE)) {
		_process_sms_event(sig, param, handle, noti_id, evt_cb_data);
	}
	else if (!g_strcmp0(interface, DBUS_TELEPHONY_CALL_INTERFACE)) {
		_process_call_event(sig, param, handle, noti_id, evt_cb_data);
	}
	else if (!g_strcmp0(interface, DBUS_TELEPHONY_SAT_INTERFACE)) {
		_process_sat_event(sig, param, handle, noti_id, evt_cb_data);
	}
	else if (!g_strcmp0(interface, DBUS_TELEPHONY_SIM_INTERFACE)) {
		_process_sim_event(sig, param, handle, noti_id, evt_cb_data);
	}
	else if (!g_strcmp0(interface, DBUS_TELEPHONY_PB_INTERFACE)) {
		_process_pb_event(sig, param, handle, noti_id, evt_cb_data);
	}
	else if (!g_strcmp0(interface, DBUS_TELEPHONY_SAP_INTERFACE)) {
		_process_sap_event(sig, param, handle, noti_id, evt_cb_data);
	}
	else if (!g_strcmp0(interface, DBUS_TELEPHONY_MODEM_INTERFACE)) {
		_process_modem_event(sig, param, handle, noti_id, evt_cb_data);
	}
	else if (!g_strcmp0(interface, DBUS_TELEPHONY_SS_INTERFACE)) {
		_process_ss_event(sig, param, handle, noti_id, evt_cb_data);
	}
	else if (!g_strcmp0(interface, DBUS_TELEPHONY_GPS_INTERFACE)) {
		_process_gps_event(sig, param, handle, noti_id, evt_cb_data);
	}
	else if (!g_strcmp0(interface, DBUS_TELEPHONY_NETWORK_INTERFACE)) {
		_process_network_event(sig, param, handle, noti_id, evt_cb_data);
	}
	else {
	}
	g_free(noti_id);
}

EXPORT_API char** tel_get_cp_name_list(void)
{
	gpointer d_conn = NULL;
	GError *error = NULL;

	GVariantIter *iter = NULL;
	GVariant *rst = NULL;

	gchar *modem_path = NULL;
	GSList *list = NULL;
	GSList *l = NULL;

	int i = 0, element_cnt = 0;
	gchar **cp_list = NULL;

	d_conn = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
	if (!d_conn) {
		err("Error creating dbus connection: %s\n", error->message);
		g_error_free (error);
		return NULL;
	}

	rst = g_dbus_connection_call_sync(d_conn, DBUS_TELEPHONY_SERVICE , "/org/tizen/telephony",
			"org.tizen.telephony.Manager", "GetModems", NULL, NULL,
			G_DBUS_CALL_FLAGS_NONE, TAPI_DEFAULT_TIMEOUT, NULL, &error);

	if (!rst) {
		dbg( "GetModems() failed. (%s)", error->message);
		g_error_free (error);
		goto OUT;
	}

	g_variant_get (rst, "(as)", &iter);
	while (g_variant_iter_next(iter, "s", &modem_path)){
		list = g_slist_append(list, modem_path);
	}
	g_variant_iter_free (iter);

	if (!list) {
		dbg( "No CP name");
		goto OUT;
	}

	element_cnt = g_slist_length(list);
	cp_list = g_new0(char*, element_cnt + 1);
	if (!cp_list) {
		goto OUT;
	}

	for (l = list; l; l = l->next, i++) {
		cp_list[i] = g_strdup(l->data);
		g_free (l->data);

		dbg("cp name[%d] = %s", i, cp_list[i]);
	}
	cp_list[element_cnt] = NULL;

	g_slist_free(list);

OUT:
	if(d_conn)
		g_object_unref(d_conn);

	if (rst)
		g_variant_unref(rst);

	return cp_list;
}

static char *get_property (TapiHandle *handle, const char *property,
		const GVariantType *type)
{
	char **dbus_info;
	GVariant *value = NULL;
	GVariant *value_container = NULL;
	GError *error = NULL;
	char *data = NULL;

	dbus_info = g_strsplit (property, ":", 2);
	if (!dbus_info) {
		dbg("invalid property");
		return NULL ;
	}

	if (!dbus_info[0] || !dbus_info[1]) {
		dbg("invalid property");
		goto OUT;
	}

	value_container = g_dbus_connection_call_sync (handle->dbus_connection,
			DBUS_TELEPHONY_SERVICE, handle->path,
			"org.freedesktop.DBus.Properties", "Get",
			g_variant_new ("(ss)", dbus_info[0], dbus_info[1]),
			G_VARIANT_TYPE ("(v)"), G_DBUS_CALL_FLAGS_NONE,
			TAPI_DEFAULT_TIMEOUT, handle->ca, &error);

	if (error) {
		warn("dbus error = %d (%s)", error->code, error->message);
		g_error_free (error);
	}

	if (!value_container)
		return NULL ;

	dbg("%s - type:[%s]", property, g_variant_get_type_string(value_container));
	g_variant_get (value_container, "(v)", &value);
	g_variant_unref (value_container);

	if (g_variant_is_of_type (value, G_VARIANT_TYPE_STRING )) {
		data = g_try_malloc0 (g_variant_get_size (value));
		if (!data) {
			warn ("calloc failed");
			g_variant_unref (value);
			goto OUT;
		}
		memcpy (data, g_variant_get_data (value), g_variant_get_size (value));
	}
	else if (g_variant_is_of_type (value, G_VARIANT_TYPE_BOOLEAN )) {
		data = g_strdup_printf ("%d", *(guchar *) g_variant_get_data (value));
	}
	else {
		data = g_strdup_printf ("%d", *(int *) g_variant_get_data (value));
	}

	g_variant_unref (value);

OUT:
	g_strfreev (dbus_info);

	return data;
}

EXPORT_API int tel_get_property_int (TapiHandle *handle,
		const char *property, int *result)
{
	char *data;

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_INPUT);
	TAPI_RET_ERR_NUM_IF_FAIL(property, TAPI_API_INVALID_INPUT);
	TAPI_RET_ERR_NUM_IF_FAIL(result, TAPI_API_INVALID_INPUT);

	data = get_property (handle, property, G_VARIANT_TYPE_INT32);
	if (!data)
		return TAPI_API_OPERATION_FAILED;

	*result = atoi(data);

	g_free (data);

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_get_property_string(TapiHandle *handle, const char *property, char **result)
{
	char *data;

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_INPUT);
	TAPI_RET_ERR_NUM_IF_FAIL(property, TAPI_API_INVALID_INPUT);
	TAPI_RET_ERR_NUM_IF_FAIL(result, TAPI_API_INVALID_INPUT);

	data = get_property (handle, property, G_VARIANT_TYPE_STRING);
	if (!data)
		return TAPI_API_OPERATION_FAILED;

	*result = data;

	return TAPI_API_SUCCESS;
}

EXPORT_API TapiHandle* tel_init(const char *cp_name)
{
	GError *error = NULL;
	struct tapi_handle *handle;

	g_type_init();

	handle = g_new0(struct tapi_handle, 1);
	if (!handle) {
		return NULL;
	}

	handle->dbus_connection = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
	if (!handle->dbus_connection) {
		err("Error creating dbus connection: %s\n", error->message);
		g_free(handle);
		g_error_free (error);
		return NULL;
	}

	dbg("unique_name:[%s] invocation:[%s]", g_dbus_connection_get_unique_name(
				handle->dbus_connection), program_invocation_name);

	handle->ca = g_cancellable_new();

	if (cp_name) {
		handle->cp_name = g_strdup(cp_name);
	}
	else {
		char **list = NULL;
		int i = 0;

		list = tel_get_cp_name_list();
		if (!list) {
			g_cancellable_cancel(handle->ca);
			g_object_unref(handle->ca);

			g_free(handle);
			return NULL;
		}

		if (!list[0]) {
			g_cancellable_cancel(handle->ca);
			g_object_unref(handle->ca);

			g_free(handle);
			g_free (list);
			return NULL;
		}

		handle->cp_name = g_strdup(list[0]);

		/* Free the list of CP names */
		while (list[i] != NULL) {
			g_free(list[i++]);
		}

		g_free (list);
	}

	handle->evt_list = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
	handle->cache_property = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

	handle->path = g_strdup_printf("%s/%s",
			DBUS_TELEPHONY_DEFAULT_PATH, handle->cp_name);

	return handle;
}

static gboolean _unregister_noti(gpointer key, gpointer value, gpointer user_data)
{
	struct tapi_evt_cb *evt_cb_data = value;
	TapiHandle *handle = user_data;

	g_dbus_connection_signal_unsubscribe(handle->dbus_connection, evt_cb_data->evt_id);

	return TRUE;
}

EXPORT_API int tel_deinit(TapiHandle* handle)
{
	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_INPUT);

	if (handle->cp_name)
		g_free(handle->cp_name);

	if (handle->path)
		g_free(handle->path);

	g_dbus_connection_signal_unsubscribe(handle->dbus_connection, handle->prop_callback_evt_id);
	g_hash_table_foreach_remove(handle->evt_list, _unregister_noti, handle);
	g_hash_table_destroy(handle->evt_list);
	g_hash_table_destroy(handle->cache_property);

	g_cancellable_cancel(handle->ca);
	g_object_unref(handle->ca);

	g_object_unref (handle->dbus_connection);

	memset(handle, 0, sizeof(struct tapi_handle));
	g_free(handle);

	dbg("done");

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_register_noti_event (TapiHandle *handle, const char *noti_id,
		tapi_notification_cb callback, void *user_data)
{
	gchar **dbus_str = NULL;
	gpointer tmp = NULL;
	struct tapi_evt_cb *evt_cb_data = NULL;

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_INPUT);
	TAPI_RET_ERR_NUM_IF_FAIL(handle->dbus_connection, TAPI_API_INVALID_INPUT);
	TAPI_RET_ERR_NUM_IF_FAIL(callback, TAPI_API_INVALID_INPUT);
	TAPI_RET_ERR_NUM_IF_FAIL(noti_id, TAPI_API_INVALID_INPUT);

	tmp = g_hash_table_lookup (handle->evt_list, noti_id);
	if (tmp != NULL ) {
		dbg("noti_id(%s) is already registered", noti_id);
		return TAPI_API_INVALID_INPUT;
	}

	dbus_str = g_strsplit (noti_id, ":", 2);
	if (!dbus_str) {
		dbg("invalid noti_id");
		return TAPI_API_INVALID_INPUT;
	}

	if (!dbus_str[0] || !dbus_str[1]) {
		g_strfreev (dbus_str);
		dbg("invalid noti_id");
		return TAPI_API_INVALID_INPUT;
	}

	evt_cb_data = g_new0(struct tapi_evt_cb, 1);
	evt_cb_data->cb_fn = callback;
	evt_cb_data->user_data = user_data;

	dbg("path(%s) interface (%s) signal (%s)", handle->path, dbus_str[0], dbus_str[1]);

	if (dbus_str[1][0] >= 'a' && dbus_str[1][0] <= 'z') {
		/* Property change callback - only one time */
		if (handle->prop_callback_evt_id == 0) {
			handle->prop_callback_evt_id = g_dbus_connection_signal_subscribe (
					handle->dbus_connection, DBUS_TELEPHONY_SERVICE, /* Sender */
					"org.freedesktop.DBus.Properties", /* Interface */
					"PropertiesChanged", /* Member */
					handle->path, /* Object path */
					NULL, /* arg0 */
					G_DBUS_SIGNAL_FLAGS_NONE, on_prop_callback, handle, NULL );
		}
	}
	else {
		/* Signal callback */
		evt_cb_data->evt_id = g_dbus_connection_signal_subscribe (
				handle->dbus_connection, DBUS_TELEPHONY_SERVICE, /* Sender */
				dbus_str[0], /* Interface */
				dbus_str[1], /* Member */
				handle->path, /* Object path */
				NULL, /* arg0 */
				G_DBUS_SIGNAL_FLAGS_NONE, on_signal_callback, handle, NULL );

	}

	g_hash_table_insert (handle->evt_list, g_strdup (noti_id), evt_cb_data);

	g_strfreev (dbus_str);

	return TAPI_API_SUCCESS;
}

EXPORT_API int tel_deregister_noti_event (TapiHandle *handle,
		const char *noti_id)
{
	struct tapi_evt_cb *evt_cb_data = NULL;
	gboolean rv = FALSE;

	TAPI_RET_ERR_NUM_IF_FAIL(handle, TAPI_API_INVALID_INPUT);
	TAPI_RET_ERR_NUM_IF_FAIL(handle->dbus_connection, TAPI_API_INVALID_INPUT);

	evt_cb_data = g_hash_table_lookup (handle->evt_list, noti_id);
	if (!evt_cb_data) {
		dbg("event does not registered");
		return TAPI_API_INVALID_INPUT;
	}

	g_dbus_connection_signal_unsubscribe (handle->dbus_connection,
			evt_cb_data->evt_id);

	rv = g_hash_table_remove (handle->evt_list, noti_id);
	if (!rv) {
		dbg("fail to deregister noti event(%s)", noti_id);
		return TAPI_API_OPERATION_FAILED;
	}

	return TAPI_API_SUCCESS;
}
/*	EOF	*/
