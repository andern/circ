/**
 * @file    server.c
 * @author  Andreas Halle <andern@gmail.com>
 * @version 0.1.0
 *
 * @section LICENSE
 *
 * This file is part of circ.
 *
 * circ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * circ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with circ.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 * See header file for description.
 */
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "irc/server.h"

struct ci_server* ci_server_new(char* host, int port)
{
        struct ci_server* server = calloc(1, sizeof(*server));
        if (server == NULL)
                return NULL;

        server->host = host;
        server->port = port;

        /* TODO: Implement IP resolve from hostname. */
        server->ip = host;

        return server;
}



void ci_server_free(struct ci_server* server)
{
        free(server->host);
        free(server->ip);
        free(server->chantypes);
        free(server->chanmodes);
        free(server->network);
}
