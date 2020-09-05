/*
 * SPDX-License-Identifier: MIT
 *
 * The MIT License (MIT)
 *
 * Copyright (c) <2020> <Stephan Gatzka>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef SCRAMJET_PEER_H
#define SCRAMJET_PEER_H

#include <stddef.h>
#include <stdint.h>

#include "cio/error_code.h"
#include "cio/write_buffer.h"

struct jet_peer;

typedef void (*peer_communication_complete_t)(struct jet_peer *, enum cio_error err);
typedef void (*peer_message_received_t)(struct jet_peer *, enum cio_error err, uint8_t *msg, size_t msg_len);

struct jet_peer {
	struct cio_write_buffer wb;
	struct cio_write_buffer wbh;
	void (*shutdown_peer)(struct jet_peer *peer);
	enum cio_error (*receive_message)(struct jet_peer *peer, peer_message_received_t handler);
	enum cio_error (*send_message)(struct jet_peer *peer, peer_communication_complete_t handler);

	peer_communication_complete_t sent_handler;
	peer_message_received_t recvd_hander;
};

void close_jet_peer(struct jet_peer *peer);

#endif
