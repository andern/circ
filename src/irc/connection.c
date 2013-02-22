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

#define BFRSIZE 1024

static error_t send_nickline(const int sock, const struct sockaddr* server,
                             const char nickname[], const size_t s_nicklen)
{
        size_t nicklen;
        char* nickline;

        nicklen = strlen(nickname);
        if (nicklen > s_nicklen) /* Servers have different nicklen config */
                return E_NICK_MAXLEN;

        nicklen += 6; /* Count for "NICK " and \n */
        nickline = malloc(nicklen*sizeof(char));
        if (nickline == NULL)
                return E_OOM;

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
        if (userline == NULL)
                return E_OOM;

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



static void parse(int sock, char recvbfr[], size_t len, char sendbfr[],
                 const struct sockaddr* server)
{
        if (strncmp(recvbfr, "PING", 4) == 0)
        {
                strncpy(sendbfr, recvbfr, len);
                sendbfr[1] = 'O';
                sendto(sock, sendbfr, len, 0,  server, sizeof(server));
        }
}



static void communicate(int sock, struct sockaddr* server)
{
        ssize_t n;
        char recvbfr[BFRSIZE];
        char sendbfr[BFRSIZE];

        while(1)
        {
                n = recvfrom(sock, recvbfr, BFRSIZE, 0, NULL, NULL);
                if (n == -1)
                {
                        fprintf(stderr, "%s: %s\n", "WARNING",
                               "Failed to receive a message from the server.");
                }
                else 
                {
                        recvbfr[n] = '\0';
                        fputs(recvbfr, stdout);
                        parse(sock, recvbfr, (size_t)n, sendbfr, server);
                }
        }
}



void ci_connect(struct ci_connection *con)
{
        int sock;
        int con_res;
        error_t err;
        struct sockaddr_in* server = calloc(1, sizeof(*server));

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
        communicate(sock, (struct sockaddr*)server);
}



