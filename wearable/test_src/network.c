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
#include <ITapiNetwork.h>
#include <TapiUtility.h>

#include "menu.h"
#include "network.h"

static char data_net_set_plmn_mode_manual_act[MENU_DATA_SIZE + 1] = "4";
static char data_net_set_plmn_mode_manual_plmn[MENU_DATA_SIZE + 1] = "45001";

static char data_net_set_service_domain_domain[MENU_DATA_SIZE + 1] = "1";

static char data_net_set_band_mode[MENU_DATA_SIZE + 1] = "1";
static char data_net_set_band_band[MENU_DATA_SIZE + 1] = "5";

static char data_net_set_preferred_plmn_mode[MENU_DATA_SIZE + 1] = "1";
static char data_net_set_preferred_plmn_plmn[MENU_DATA_SIZE + 1] = "45001";
static char data_net_set_preferred_plmn_type[MENU_DATA_SIZE + 1] = "4";
static char data_net_set_preferred_plmn_ef_index[MENU_DATA_SIZE + 1] = "0";

static char data_net_set_mode_mode[MENU_DATA_SIZE + 1] = "3";

static void on_prop_signal_dbm (TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	int *sig_dbm = data;

	msg ("");
	msgp ("property(%s) receive !!", TAPI_PROP_NETWORK_SIGNALSTRENGTH_DBM);

	msg (" - sig_dbm = %d", *sig_dbm);
}

static void on_prop_signal_level (TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	int *sig_level = data;

	msg ("");
	msgp ("property(%s) receive !!", TAPI_PROP_NETWORK_SIGNALSTRENGTH_LEVEL);

	msg (" - sig_level = %d", *sig_level);
}

static void on_prop_lac (TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	int *lac = data;

	msg ("");
	msgp ("property(%s) receive !!", TAPI_PROP_NETWORK_LAC);

	msg (" - lac = %d", *lac);
}

static void on_prop_plmn (TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	msg ("");
	msgp ("property(%s) receive !!", TAPI_PROP_NETWORK_PLMN);

	msg (" - plmn = %s", (char *)data);
}

static void on_prop_cellid (TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	int *cell_id = data;

	msg ("");
	msgp ("property(%s) receive !!", TAPI_PROP_NETWORK_CELLID);

	msg (" - cell_id = %d", *cell_id);
}

static void on_prop_service_type (TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	int *service_type = data;

	msg ("");
	msgp ("property(%s) receive !!", TAPI_PROP_NETWORK_SERVICE_TYPE);

	msg (" - service_type = %d", *service_type);
}

static void on_prop_act (TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	int *act = data;

	msg ("");
	msgp ("property(%s) receive !!", TAPI_PROP_NETWORK_ACT);

	msg (" - access technology = %d", *act);
}

static void on_prop_ps_type (TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	int *ps_type = data;

	msg ("");
	msgp ("property(%s) receive !!", TAPI_PROP_NETWORK_PS_TYPE);

	msg (" - ps_type = %d", *ps_type);
}

static void on_prop_circuit_status (TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	int *circuit_status = data;

	msg ("");
	msgp ("property(%s) receive !!", TAPI_PROP_NETWORK_CIRCUIT_STATUS);

	msg (" - circuit_status = %d", *circuit_status);
}

static void on_prop_packet_status (TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	int *packet_status = data;

	msg ("");
	msgp ("property(%s) receive !!", TAPI_PROP_NETWORK_PACKET_STATUS);

	msg (" - packet_status = %d", *packet_status);
}

static void on_prop_roaming_status (TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	guchar *roaming_status = data;

	msg ("");
	msgp ("property(%s) receive !!", TAPI_PROP_NETWORK_ROAMING_STATUS);

	msg (" - roaming_status = %d", *roaming_status);
}

static void on_prop_name_option (TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	char *option = data;

	msg ("");
	msgp ("property(%s) receive !!", TAPI_PROP_NETWORK_NAME_OPTION);

	msg (" - name_option = %s", option);
}

static void on_prop_network_name (TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	msg ("");
	msgp ("property(%s) receive !!", TAPI_PROP_NETWORK_NETWORK_NAME);

	msg (" - network_name = %s", (char *)data);
}

static void on_prop_spn_name (TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	msg ("");
	msgp ("property(%s) receive !!", TAPI_PROP_NETWORK_SPN_NAME);

	msg (" - spn_name = %s", (char *)data);
}

static void on_noti_registration_status(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	struct tel_noti_network_registration_status *noti = data;

	msg ("");
	msgb ("event(%s) receive !!", TAPI_NOTI_NETWORK_REGISTRATION_STATUS);

	msg (" - circuit status = %d", noti->cs);
	msg (" - packet status = %d", noti->ps);
	msg (" - service type = %d", noti->type);
	msg (" - is roaming = %d", noti->is_roaming);
}

static void on_noti_cell_info(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	struct tel_noti_network_cell_info *noti = data;

	msg ("");
	msgb ("event(%s) receive !!", TAPI_NOTI_NETWORK_CELLINFO);

	msg (" - lac = %d", noti->lac);
	msg (" - cell_id = %d", noti->cell_id);
}

static void on_noti_change(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	struct tel_noti_network_change *noti = data;

	msg ("");
	msgb ("event(%s) receive !!", TAPI_NOTI_NETWORK_CHANGE);

	msg (" - plmn = %s", noti->plmn);
	msg (" - act = %d", noti->act);
	msg (" - lac = %d", noti->lac);
}

static void on_noti_time_info(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	struct tel_noti_network_time_info *noti = data;

	msg ("");
	msgb ("event(%s) receive !!", TAPI_NOTI_NETWORK_TIMEINFO);

	msg (" - plmn = %s", noti->plmn);
	msg (" - year = %d", noti->year);
	msg (" - month = %d", noti->month);
	msg (" - day = %d", noti->day);
	msg (" - hour = %d", noti->hour);
	msg (" - minute = %d", noti->minute);
	msg (" - second = %d", noti->second);
	msg (" - wday = %d", noti->wday);
	msg (" - gmtoff = %d", noti->gmtoff);
	msg (" - dstoff = %d", noti->dstoff);
	msg (" - isdst = %d", noti->isdst);
}

static void on_noti_identity(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	struct tel_noti_network_identity *noti = data;

	msg ("");
	msgb ("event(%s) receive !!", TAPI_NOTI_NETWORK_IDENTITY);

	msg (" - plmn = %s", noti->plmn);
	msg (" - short_name = %s", noti->short_name);
	msg (" - full_name = %s", noti->full_name);
}

static void on_noti_signal_strength(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	struct tel_noti_network_signal_strength *noti = data;

	msg ("");
	msgb ("event(%s) receive !!", TAPI_NOTI_NETWORK_SIGNALSTRENGTH);

	msg (" - dbm = %d", noti->dbm);
}

static void on_net_search(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelNetworkPlmnList_t *list = data;
	int i =0;

	msg ("");
	msgb ("tel_search_network() response receive");
	msg (" - result = 0x%x", result);

	if (!list) {
		msg (" - failed");
		return;
	}

	msg (" - count = %d", list->networks_count);

	for (i = 0; i < list->networks_count; i++) {
		msg (" - [%d] plmn=%s, act=%d, type=%d, name=%s",
				i,
				list->network_list[i].plmn,
				list->network_list[i].access_technology,
				list->network_list[i].type_of_plmn,
				list->network_list[i].network_name);
	}
}

static void on_net_set_plmn_mode_automatic(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg ("");
	msgb ("tel_select_network_automatic() response receive");
	msg (" - result = 0x%x", result);
}

static void on_net_set_plmn_mode_manual(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg ("");
	msgb ("tel_select_network_manual() response receive");
	msg (" - result = 0x%x", result);
}

static void on_net_get_plmn_mode(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *mode = data;

	msg ("");
	msgb ("tel_get_network_selection_mode() response receive");
	msg (" - result = 0x%x", result);

	if (data)
		msg (" - mode = %d", *mode);
}

static void on_net_set_service_domain(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg ("");
	msgb ("tel_set_network_service_domain() response receive");
	msg (" - result = 0x%x", result);
}

static void on_net_get_service_domain(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *domain = data;

	msg ("");
	msgb ("tel_get_network_service_domain() response receive");
	msg (" - result = 0x%x", result);

	if (data)
		msg (" - domain = %d", *domain);
}

static void on_net_set_band(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg ("");
	msgb ("tel_set_network_band() response receive");
	msg (" - result = 0x%x", result);
}

static void on_net_get_band(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *band = data;

	msg ("");
	msgb ("tel_get_network_band() response receive");
	msg (" - result = 0x%x", result);

	if (data)
		msg (" - band = %d", *band);
}

static void on_net_set_preferred_plmn(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg ("");
	msgb ("tel_set_preferred_plmn() response receive");
	msg (" - result = 0x%x", result);
}

static void on_net_get_preferred_plmn(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelNetworkPreferredPlmnList_t *info = data;
	unsigned int i = 0;

	msg ("");
	msgb ("tel_get_preferred_plmn() response receive");
	msg (" - result = 0x%x", result);

	if (!info) {
		msg (" - failed");
		return;
	}

	msg (" - count = %d", info->NumOfPrefPlmns);

	for (i = 0; i < info->NumOfPrefPlmns; i++) {
		msg (" - [%d] plmn=%s, type=%d, ef_index=%d, name=%s",
				i,
				info->PrefPlmnRecord[i].Plmn,
				info->PrefPlmnRecord[i].SystemType,
				info->PrefPlmnRecord[i].Index,
				info->PrefPlmnRecord[i].network_name);
	}
}

static void on_net_set_cancel_manual_search(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg ("");
	msgb ("tel_cancel_network_manual_search() response receive");
	msg (" - result = 0x%x", result);
}

static void on_net_get_serving_network(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelNetworkServing_t *info = data;

	msg ("");
	msgb ("tel_get_network_serving() response receive");
	msg (" - result = 0x%x", result);

	if (!info) {
		msg (" - failed");
		return;
	}

	msg (" - plmn = %s", info->plmn);
	msg (" - access technology = %d", info->act);
	msg (" - lac = %d", info->lac);
}

static void on_net_set_mode(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg ("");
	msgb ("tel_set_network_mode() response receive");
	msg (" - result = 0x%x", result);
}

static void on_net_get_mode(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *mode = data;

	msg ("");
	msgb ("tel_get_network_mode() response receive");
	msg (" - result = 0x%x", result);

	if (data)
		msg (" - mode = %d", *mode);
}

static void on_net_get_neighboring_cell_info(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelNetworkNeighboringCellInfo_t *info = data;
	int i, j;

	msg ("");
	msgb ("tel_get_neighboring_cell_info() response receive");
	msg (" - result = 0x%x", result);

	if (!data)
		return;

	msg ("info=%p",info);

	msg ("act=%d",info->serving.act);
	msg ("mcc=%d",info->serving.mcc);
	msg ("mnc=%d\n",info->serving.mnc);

	if(info->serving.act <= TAPI_NETWORK_SYSTEM_EGPRS) {
		msg ("geran.cell_id=%d",info->serving.cell.geran.cell_id);
		msg ("geran.lac=%d",info->serving.cell.geran.lac);
		msg ("geran.bcch=%d",info->serving.cell.geran.bcch);
		msg ("geran.bsic=%d",info->serving.cell.geran.bsic);
		msg ("geran.rxlev=%d\n",info->serving.cell.geran.rxlev);
	}
	else if(info->serving.act <= TAPI_NETWORK_SYSTEM_GSM_AND_UMTS) {
		msg ("umts.cell_id=%d",info->serving.cell.umts.cell_id);
		msg ("umts.lac=%d",info->serving.cell.umts.lac);
		msg ("umts.arfcn=%d",info->serving.cell.umts.arfcn);
		msg ("umts.psc=%d",info->serving.cell.umts.psc);
		msg ("umts.rscp=%d\n",info->serving.cell.umts.rscp);
	}
	else if(info->serving.act == TAPI_NETWORK_SYSTEM_LTE) {
		msg ("lte.cell_id=%d",info->serving.cell.lte.cell_id);
		msg ("lte.lac=%d",info->serving.cell.lte.lac);
		msg ("lte.earfcn=%d",info->serving.cell.lte.earfcn);
		msg ("lte.tac=%d",info->serving.cell.lte.tac);
		msg ("lte.rssi=%d\n",info->serving.cell.lte.rssi);
	}
	msg ("geran_list_count=%d",info->geran_list_count);
	for(i=0; i<info->geran_list_count; i++) {
		msg ("[%d] cell_id=%d, lac=%d, bcch=%d, bsic=%d, rxlev=%d,",i,
			info->geran_list[i].cell_id, info->geran_list[i].lac, info->geran_list[i].bcch,
			info->geran_list[i].bsic, info->geran_list[i].rxlev);
	}

	msg ("umts_list_count=%d",info->umts_list_count);
	for(j=0; j<info->umts_list_count; j++) {
		msg ("[%d] cell_id=%d, lac=%d, arfcn=%d, psc=%d, rscp=%d,",j,
			info->umts_list[j].cell_id, info->umts_list[j].lac, info->umts_list[j].arfcn,
			info->umts_list[j].psc, info->umts_list[j].rscp);
	}
}

static int run_net_search (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;

	msg ("call tel_search_network()");

	result = tel_search_network (handle, on_net_search, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg ("failed. (result = %d)", result);
	}

	return 0;
}

static int run_net_set_plmn_mode_automatic (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;

	msg ("call tel_select_network_automatic()");

	result = tel_select_network_automatic (handle, on_net_set_plmn_mode_automatic, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg ("failed. (result = %d)", result);
	}

	return 0;
}

static int run_net_set_plmn_mode_manual (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;
	const char *plmn;
	int act;

	msg ("call tel_select_network_manual()");

	plmn = data_net_set_plmn_mode_manual_plmn;
	act = atoi(data_net_set_plmn_mode_manual_act);

	result = tel_select_network_manual (handle, plmn, act, on_net_set_plmn_mode_manual, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg ("failed. (result = %d)", result);
	}

	return 0;
}

static int run_net_get_plmn_mode (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;

	msg ("call tel_get_network_selection_mode()");

	result = tel_get_network_selection_mode (handle, on_net_get_plmn_mode, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg ("failed. (result = %d)", result);
	}

	return 0;
}

static int run_net_set_service_domain (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;
	int domain;

	msg ("call tel_set_network_service_domain()");

	domain = atoi(data_net_set_service_domain_domain);

	result = tel_set_network_service_domain (handle, domain, on_net_set_service_domain, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg ("failed. (result = %d)", result);
	}

	return 0;
}

static int run_net_get_service_domain (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;

	msg ("call tel_get_network_service_domain()");

	result = tel_get_network_service_domain (handle, on_net_get_service_domain, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg ("failed. (result = %d)", result);
	}

	return 0;
}

static int run_net_set_band (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;
	int mode;
	int band;

	msg ("call tel_set_network_band()");

	mode = atoi(data_net_set_band_mode);
	band = atoi(data_net_set_band_band);

	result = tel_set_network_band (handle, mode, band, on_net_set_band, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg ("failed. (result = %d)", result);
	}

	return 0;
}

static int run_net_get_band (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;

	msg ("call tel_get_network_band()");

	result = tel_get_network_band (handle, on_net_get_band, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg ("failed. (result = %d)", result);
	}

	return 0;
}

static int run_net_set_preferred_plmn (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;
	int operation;
	TelNetworkPreferredPlmnInfo_t info;

	msg ("call tel_set_network_preferred_plmn()");

	memset(&info, 0, sizeof(TelNetworkPreferredPlmnInfo_t));

	operation = atoi(data_net_set_preferred_plmn_mode);
	info.Index = atoi(data_net_set_preferred_plmn_ef_index);
	info.SystemType = atoi(data_net_set_preferred_plmn_type);
	strncpy(info.Plmn, data_net_set_preferred_plmn_plmn, 6);

	result = tel_set_network_preferred_plmn (handle, operation, &info, on_net_set_preferred_plmn, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg ("failed. (result = %d)", result);
	}

	return 0;
}

static int run_net_get_preferred_plmn (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;

	msg ("call tel_get_network_preferred_plmn()");

	result = tel_get_network_preferred_plmn (handle, on_net_get_preferred_plmn, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg ("failed. (result = %d)", result);
	}

	return 0;
}

static int run_net_set_cancel_manual_search (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;

	msg ("call tel_cancel_network_manual_search()");

	result = tel_cancel_network_manual_search (handle, on_net_set_cancel_manual_search, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg ("failed. (result = %d)", result);
	}

	return 0;
}

static int run_net_get_serving_network (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;

	msg ("call tel_get_network_serving()");

	result = tel_get_network_serving (handle, on_net_get_serving_network, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg ("failed. (result = %d)", result);
	}

	return 0;
}

static int run_net_set_mode (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;
	int mode;

	msg ("call tel_set_network_mode()");

	mode = atoi(data_net_set_mode_mode);

	result = tel_set_network_mode (handle, mode, on_net_set_mode, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg ("failed. (result = %d)", result);
	}

	return 0;
}

static int run_net_get_mode (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;

	msg ("call tel_get_network_mode()");

	result = tel_get_network_mode (handle, on_net_get_mode, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg ("failed. (result = %d)", result);
	}

	return 0;
}

static int run_net_get_neighboring_cell_info (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;

	msg ("call tel_get_network_neighboring_cell_info()");

	result = tel_get_network_neighboring_cell_info (handle, on_net_get_neighboring_cell_info, NULL);
	if (result != TAPI_API_SUCCESS) {
		msg ("failed. (result = %d)", result);
	}

	return 0;
}

static int show_properties (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int lac = -1,
		cellid = -1,
		svc_type = -1,
		act = -1,
		ps_type = -1,
		cs = -1,
		ps = -1,
		roam = -1,
		sig_dbm = -1,
		sig_level = -1;
	char *plmn = NULL,
		 *option = NULL,
		 *n_name = NULL,
		 *s_name = NULL;

	tel_get_property_int (handle, TAPI_PROP_NETWORK_LAC	, &lac);
	tel_get_property_int (handle, TAPI_PROP_NETWORK_CELLID, &cellid);
	tel_get_property_int (handle, TAPI_PROP_NETWORK_SERVICE_TYPE, &svc_type);
	tel_get_property_int (handle, TAPI_PROP_NETWORK_ACT, &act);
	tel_get_property_string (handle, TAPI_PROP_NETWORK_PLMN, &plmn);
	tel_get_property_int (handle, TAPI_PROP_NETWORK_PS_TYPE, &ps_type);
	tel_get_property_int (handle, TAPI_PROP_NETWORK_CIRCUIT_STATUS, &cs);
	tel_get_property_int (handle, TAPI_PROP_NETWORK_PACKET_STATUS, &ps);
	tel_get_property_int (handle, TAPI_PROP_NETWORK_SIGNALSTRENGTH_DBM, &sig_dbm);
	tel_get_property_int (handle, TAPI_PROP_NETWORK_SIGNALSTRENGTH_LEVEL, &sig_level);
	tel_get_property_int (handle, TAPI_PROP_NETWORK_ROAMING_STATUS, &roam);
	tel_get_property_string (handle, TAPI_PROP_NETWORK_NAME_OPTION, &option);
	tel_get_property_string (handle, TAPI_PROP_NETWORK_NETWORK_NAME, &n_name);
	tel_get_property_string (handle, TAPI_PROP_NETWORK_SPN_NAME, &s_name);

	msg (
			"  [lac]: 0x%08X   [cellid]: 0x%08X\n"
			"  [service_type]: %d    [act]: %d            [plmn]: \"%s\"\n"
			"  [ps_type]: %d         [cs_status]: %d      [ps_status]: %d\n"
			"  [sig_dbm]: %d         [sig_level]: %d      [roaming_status]: %d\n"
			"  [option]: \"%s\"  [network_name]: \"%s\"    [spn_name]: \"%s\"",
			lac, cellid,
			svc_type, act, plmn,
			ps_type, cs, ps,
			sig_dbm, sig_level, roam,
			option,	n_name, s_name);

	g_free (plmn);
	g_free (option);
	g_free (n_name);
	g_free (s_name);

	return 0;
}

static struct menu_data menu_net_search[] = {
	{ "1", "run", NULL, run_net_search, NULL},
	{ NULL, NULL, },
};

static struct menu_data menu_net_set_plmn_mode_automatic[] = {
	{ "1", "run", NULL, run_net_set_plmn_mode_automatic, NULL},
	{ NULL, NULL, },
};

static struct menu_data menu_net_set_plmn_mode_manual[] = {
	{ "1", "act", NULL, NULL, data_net_set_plmn_mode_manual_act},
	{ "2", "plmn (45001)", NULL, NULL, data_net_set_plmn_mode_manual_plmn},
	{ "3", "run", NULL, run_net_set_plmn_mode_manual, NULL},
	{ NULL, NULL, },
};

static struct menu_data menu_net_get_plmn_mode[] = {
	{ "1", "run", NULL, run_net_get_plmn_mode, NULL},
	{ NULL, NULL, },
};


static struct menu_data menu_net_set_service_domain[] = {
	{ "1", "domain (1=combined, 2=cs, 3=ps)", NULL, NULL, data_net_set_service_domain_domain},
	{ "2", "run", NULL, run_net_set_service_domain, NULL},
	{ NULL, NULL, },
};

static struct menu_data menu_net_get_service_domain[] = {
	{ "1", "run", NULL, run_net_get_service_domain, NULL},
	{ NULL, NULL, },
};


static struct menu_data menu_net_set_band[] = {
	{ "1", "mode (1=preferred, 2=only)", NULL, NULL, data_net_set_band_mode},
	{ "2", "band (1=GSM850, 2=GSM900_1800, 3=GSM1900, 4=GSM, 5=WCDMA, 6=WCDMA850, ...)", NULL, NULL, data_net_set_band_band},
	{ "3", "run", NULL, run_net_set_band, NULL},
	{ NULL, NULL, },
};

static struct menu_data menu_net_get_band[] = {
	{ "1", "run", NULL, run_net_get_band, NULL},
	{ NULL, NULL, },
};


static struct menu_data menu_net_set_preferred_plmn[] = {
	{ "1", "mode (1=add, 2=edit, 3=delete)", NULL, NULL, data_net_set_preferred_plmn_mode},
	{ "2", "plmn (45001)", NULL, NULL, data_net_set_preferred_plmn_plmn},
	{ "3", "type (1=GSM, 2=GPRS, 3=EGPRS, 4=UMTS, ...)", NULL, NULL, data_net_set_preferred_plmn_type},
	{ "4", "ef_index (0,...)", NULL, NULL, data_net_set_preferred_plmn_ef_index},
	{ "5", "run", NULL, run_net_set_preferred_plmn, NULL},
	{ NULL, NULL, },
};

static struct menu_data menu_net_get_preferred_plmn[] = {
	{ "1", "run", NULL, run_net_get_preferred_plmn, NULL},
	{ NULL, NULL, },
};


static struct menu_data menu_net_set_cancel_manual_search[] = {
	{ "1", "run", NULL, run_net_set_cancel_manual_search, NULL},
	{ NULL, NULL, },
};


static struct menu_data menu_net_get_serving_network[] = {
	{ "1", "run", NULL, run_net_get_serving_network, NULL},
	{ NULL, NULL, },
};

static struct menu_data menu_net_set_mode[] = {
	{ "1", "mode (1=GSM, 2=WCDMA, 4=CDMA, 8=LTE)", NULL, NULL, data_net_set_mode_mode},
	{ "3", "run", NULL, run_net_set_mode, NULL},
	{ NULL, NULL, },
};

static struct menu_data menu_net_get_mode[] = {
	{ "1", "run", NULL, run_net_get_mode, NULL},
	{ NULL, NULL, },
};

static struct menu_data menu_net_get_neighboring_cell_info[] = {
	{ "1", "run", NULL, run_net_get_neighboring_cell_info, NULL},
	{ NULL, NULL, },
};

struct menu_data menu_net[] = {
	{ "1", "Search", menu_net_search, NULL, NULL},
	{ "2a", "SET PLMN Selection mode (Automatic)", menu_net_set_plmn_mode_automatic, NULL, NULL},
	{ "2s", "SET PLMN Selection mode (Manual)", menu_net_set_plmn_mode_manual, NULL, NULL},
	{ "2g", "GET PLMN Selection mode", menu_net_get_plmn_mode, NULL, NULL},
	{ "3s", "SET Service Domain", menu_net_set_service_domain, NULL, NULL},
	{ "3g", "GET Service Domain", menu_net_get_service_domain, NULL, NULL},
	{ "4s", "SET Band", menu_net_set_band, NULL, NULL},
	{ "4g", "GET Band", menu_net_get_band, NULL, NULL},
	{ "5s", "SET Preferred PLMN", menu_net_set_preferred_plmn, NULL, NULL},
	{ "5g", "GET Preferred PLMN", menu_net_get_preferred_plmn, NULL, NULL},
	{ "6", "SET Cancel manual search", menu_net_set_cancel_manual_search, NULL, NULL},
	{ "7", "GET Serving network", menu_net_get_serving_network, NULL, NULL},
	{ "8s", "SET Mode", menu_net_set_mode, NULL, NULL},
	{ "8g", "GET Mode", menu_net_get_mode, NULL, NULL},
	{ "9g", "GET Neighboring Cell Info", menu_net_get_neighboring_cell_info, NULL, NULL},
	{ "*", "<Properties>", NULL, show_properties, NULL },
	{ NULL, NULL, },
};

void register_network_event (TapiHandle *handle)
{
	int ret;

	/* Signal */
	ret = tel_register_noti_event (handle,
			TAPI_NOTI_NETWORK_REGISTRATION_STATUS,
			on_noti_registration_status, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_NOTI_NETWORK_CELLINFO, on_noti_cell_info, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_NOTI_NETWORK_CHANGE, on_noti_change, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_NOTI_NETWORK_TIMEINFO, on_noti_time_info, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_NOTI_NETWORK_IDENTITY, on_noti_identity, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_NOTI_NETWORK_SIGNALSTRENGTH, on_noti_signal_strength, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	/* Property */
	ret = tel_register_noti_event (handle,
			TAPI_PROP_NETWORK_SIGNALSTRENGTH_DBM, on_prop_signal_dbm, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_PROP_NETWORK_SIGNALSTRENGTH_LEVEL, on_prop_signal_level, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_PROP_NETWORK_LAC, on_prop_lac, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_PROP_NETWORK_PLMN, on_prop_plmn, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_PROP_NETWORK_CELLID, on_prop_cellid, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_PROP_NETWORK_SERVICE_TYPE, on_prop_service_type, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_PROP_NETWORK_ACT, on_prop_act, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_PROP_NETWORK_PS_TYPE, on_prop_ps_type, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_PROP_NETWORK_CIRCUIT_STATUS, on_prop_circuit_status, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_PROP_NETWORK_PACKET_STATUS, on_prop_packet_status, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_PROP_NETWORK_ROAMING_STATUS, on_prop_roaming_status, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_PROP_NETWORK_NAME_OPTION, on_prop_name_option, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_PROP_NETWORK_NETWORK_NAME, on_prop_network_name, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle,
			TAPI_PROP_NETWORK_SPN_NAME, on_prop_spn_name, NULL);
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}
}
