/*
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
 */
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <stdio.h> // TODO: REMOVE

#include "irc/connection.h"

/*
 * Connect to the server stored in the connection struct. Authenticate using the
 * stored authentication details in the connection struct.
 */
void ci_connect(struct ci_connection *con)
{
        int sock;
        struct sockaddr_in server;
        char recvbfr[1024];
        char sendbfr[1024];

        sock = socket(AF_INET, SOCK_STREAM, 0);
        bzero(&server, sizeof(server));

        server.sin_addr.s_addr = inet_addr(con->server);
        server.sin_port = con->port;
        server.sin_family = AF_INET;

        int con_res = connect(sock, &server, sizeof(server));
        if (!con_res)
        {
                puts("Could not connect to server.");
                exit(-1);
        }

        sendto(sock, "NICK cbot\n", 10, 0, &server, sizeof(server));

        while (1)
        {
                int n = recvfrom(sock, recvbfr, 1024, 0, NULL, NULL);
                recvbfr[n] = 0;
                puts(recvbfr);
        }
}
