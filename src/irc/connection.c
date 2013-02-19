/**
 * @file    connection.c
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
#include <netinet/in.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "irc/connection.h"
#include "error.h"

static error_t send_nickline(int sock, struct sockaddr* server, char* nickname,
                             size_t s_nicklen)
{
        size_t nicklen;
        char* nickline;

        nicklen = strlen(nickname) + 6;
        if (nicklen > (s_nicklen + 6))
                return E_NICK_MAXLEN;

        nickline = malloc(nicklen*sizeof(char));
        sprintf(nickline, "NICK %s\n", nickname);
        sendto(sock, nickline, nicklen, 0, server, sizeof(*server));
        free(nickline);

        return E_SUCCESS;
}


static error_t send_userline(int sock, struct sockaddr* server, char* ident,
                             char* name)
{
        size_t userlen;
        char* userline;

        /* TODO: Check maxlen of ident, server and name. */
        userlen = strlen(ident) + strlen(name) + 13;

        userline = malloc(userlen*sizeof(char));
        sprintf(userline, "USER %s x x :%s\n", ident, name);
        sendto(sock, userline, userlen, 0, server, sizeof(*server));
        free(userline);

        return (E_SUCCESS);
}



static error_t authenticate(int sock, struct sockaddr* server,
                            struct ci_connection con)
{
        error_t err;
        err =  send_nickline(sock, server, con.user.nick, 9);
        if (err != E_SUCCESS)
                return err;

        err = send_userline(sock, server, con.user.ident, con.user.name);
        if (err != E_SUCCESS)
                return err;

        return E_SUCCESS;
}



void ci_connect(struct ci_connection *con)
{
        int sock;
        int con_res;
        error_t err;
        struct sockaddr_in* server = calloc(1, sizeof(*server));
        char recvbfr[1024];

        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
                perror("Creating socket");

        server->sin_addr.s_addr = inet_addr(con->server.host);
        server->sin_port = htons(con->server.port);
        server->sin_family = AF_INET;

        con_res = connect(sock, (struct sockaddr*)server, sizeof(*server));
        if (con_res == -1)
                perror("Connecting to server");

        err = authenticate(sock, (struct sockaddr*)server, *con);
        if (err != E_SUCCESS)
        {
                fprintf(stderr, "%s: %s\n", "Error connecting to IRC server",
                        err_desc[err].message);
                exit(1);
        }

        while(1)
        {
                int n;
                n = recvfrom(sock, recvbfr, 1024, 0, NULL, NULL);
                recvbfr[n] = 0;
                fputs(recvbfr, stdout);
        }
}
