/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <asm/unistd.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>

#include <glib.h>
#include <glib-object.h>

#include <dlog.h>
#include <tapi_common.h>
#include <ITapiModem.h>

#include "log.h"


static pid_t get_tid ()
{
	return syscall (__NR_gettid);
}

struct meta_data {
	pid_t tid;
	GMainLoop *loop;
	GMainContext *context;
};

static void on_cb (TapiHandle *h, int result, void *data, void *user_data)
{
	struct meta_data *m = user_data;
	int *status = data;

	g_assert (m != NULL);
	g_assert (m->tid == get_tid());

	dbg ("response: %d", *status);
	g_main_loop_quit (m->loop);
}

static gboolean on_timeout (gpointer user_data)
{
	g_assert_not_reached ();
	return FALSE;
}

static void *do_blocking_request_response (gpointer user_data)
{
	struct meta_data m;
	TapiHandle *h = user_data;
	GSource *timer;
	int ret;

	m.tid = get_tid();
	m.context = g_main_context_new();
	m.loop = g_main_loop_new (m.context, FALSE);

	g_main_context_push_thread_default (m.context);

	if (!user_data) {
		h = tel_init (NULL);
		g_assert (h != NULL);
	}

	ret = tel_get_flight_mode (h, on_cb, &m);
	g_assert (ret == TAPI_API_SUCCESS);

	timer = g_timeout_source_new_seconds (60);
	g_source_set_callback (timer, on_timeout, &m, NULL);
	g_source_attach (timer, m.context);
	g_source_unref (timer);

	g_main_loop_run (m.loop);

	g_main_context_pop_thread_default (m.context);
	g_main_context_unref (m.context);
	g_main_loop_unref (m.loop);

	if (!user_data)
		tel_deinit (h);

	return NULL;
}

static void test_each_request (void)
{
	GThread *th1;
	GThread *th2;

	/* Request from A thread */
	th1 = g_thread_new ("test1-A", do_blocking_request_response, NULL);
	g_assert (th1 != NULL);

	/* Request from B thread */
	th2 = g_thread_new ("test1-B", do_blocking_request_response, NULL);
	g_assert (th2 != NULL);

	g_thread_join (th1);
	g_thread_join (th2);
}

static void test_cross_request (void)
{
	GThread *th1;
	GThread *th2;
	GThread *th3;
	TapiHandle *h;

	h = tel_init (NULL);
	g_assert (h != NULL);

	/* Request from A thread with shared handle */
	th1 = g_thread_new ("test2-A", do_blocking_request_response, h);
	g_assert (th1 != NULL);

	/* Sync Request from Default context */
	g_assert (tel_get_misc_me_imei_sync (h) != NULL);

	/* Request from B thread with custom handle */
	th2 = g_thread_new ("test2-B", do_blocking_request_response, NULL);
	g_assert (th2 != NULL);

	/* Request from C thread with shared handle */
	th3 = g_thread_new ("test3-C", do_blocking_request_response, h);
	g_assert (th3 != NULL);

	g_thread_join (th1);
	g_thread_join (th2);
	g_thread_join (th3);

	tel_deinit (h);
}

int main (int argc, char **argv)
{
	g_test_init (&argc, &argv, NULL);
	g_type_init ();

	g_test_add_func ("/thread/each_request", test_each_request);
	g_test_add_func ("/thread/cross_request", test_cross_request);

	return g_test_run();
}
