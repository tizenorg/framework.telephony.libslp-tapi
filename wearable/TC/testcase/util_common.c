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

#include <glib.h>
#include "util_common.h"

static GMainLoop *g_loop = NULL;
static GMainContext *g_ctx = NULL;

void util_init_loop ()
{
	g_ctx = g_main_context_new ();
	g_main_context_push_thread_default (g_ctx);
	g_loop = g_main_loop_new (g_ctx, FALSE);
}

void util_free_loop ()
{
	g_main_context_pop_thread_default (g_ctx);
	g_main_loop_unref (g_loop);
	g_main_context_unref (g_ctx);

	g_ctx = NULL;
	g_loop = NULL;

}

void util_start_loop ()
{
	g_main_loop_run (g_loop);
}

void util_stop_loop ()
{
	g_main_loop_quit (g_loop);
}
