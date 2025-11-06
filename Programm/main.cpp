#include <vector>
#include <queue>
#include <binapi/websocket.hpp>
#include <boost/asio/io_context.hpp>
#include <iostream>

#include "binapi/types.hpp"

using namespace std;

int main() {
    boost::asio::io_context io;

    // SPOT WS endpoint (TLS)
    binapi::ws::websockets ws{
        io,
        "stream.binance.com", // host
        "9443"                // port (Binance spot WS)
    };

    // 1) Single-symbol BBO
    ws.book("BTCUSDT", [](const char* fl, int ec, std::string emsg, binapi::ws::book_ticker_t tick) {
        if (ec) {
            std::cerr << "bookTicker error: fl=" << fl << " ec=" << ec << " emsg=" << emsg << '\n';
            return false;
        }
        // tick contains best bid/ask & qty. If unsure of field names in your binapi version, dump it:
        std::cout << "BTCUSDT bookTicker: " << tick << '\n';
        return true;
    });

    io.run();
    return 0;
}
