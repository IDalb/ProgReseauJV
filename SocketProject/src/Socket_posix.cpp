#ifdef unix

#include "socket.h"
#include <string.h>
#include <stdio.h>

namespace tpSocket
{
    int socketInit() {
        return 0; // No initialization required on Unix
    }

    void socketClean() {
        // No cleanup required on Unix
    }

    void socketClose(SocketHandle sock) {
        close(sock);
    }
}
#endif // unix
