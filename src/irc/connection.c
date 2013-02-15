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
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <stdio.h>

#include "irc/connection.h"
/*
static void authenticate(int sock, struct sockaddr* server)
{
        size_t sent;
        char* nick = "NICK cbot\n";
        puts("hmm.");
        sendto(sock, "NICK cbot\n", 10, 0, server, 10);
        sent = send(sock, nick, sizeof(nick), 0);
        printf("%d\n", (int)sent);
}
*/




void ci_connect(struct ci_connection *con)
{
        int sock;
        int con_res;
        struct sockaddr_in* server = calloc(1, sizeof(struct sockaddr_in));
        char recvbfr[1024];
        char sendbfr[1024];

        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
                perror("Creating socket");
        else
                puts("Successfully created socket.");

        server->sin_addr.s_addr = inet_addr(con->server);
        server->sin_port = con->port;
        server->sin_family = AF_INET;
        printf("%d\n", server->sin_addr.s_addr);

        con_res = connect(sock, (struct sockaddr*)server, sizeof(*server));
        puts("Con?");
        if (con_res == -1)
                perror("Connecting to server");
        else
                puts("Successfully connected to server.");

        /* authenticate(sock, (struct sockaddr*)server); */

        while (fgets(sendbfr, 10000, stdin) != NULL)
            {
                int n;
                sendto(sock, sendbfr, strlen(sendbfr), 0, (struct sockaddr *)server, sizeof(server));
                puts("Hey");
                n = recvfrom(sock, recvbfr, 10000, 0, NULL, NULL);
                recvbfr[n] = 0;
                fputs(recvbfr,stdout);
            }
}
