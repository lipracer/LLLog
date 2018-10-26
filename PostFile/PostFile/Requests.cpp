#include "Requests.h"

using boost::asio::ip::tcp;

Requests::Requests()
{
    
}

Requests::~Requests()
{
    
}

int Requests::post(string url, const char* buf, size_t len)
{
    return 0;
}

int Requests::post(string url, string file)
{
    tcp::resolver resolver = tcp::resolver(Requests::get_context());
    tcp::socket _socket(Requests::get_context());

    tcp::resolver::results_type endpoints = resolver.resolve("host", "port");
    
    boost::asio::async_connect(_socket, endpoints,
                               [this](boost::system::error_code ec, tcp::endpoint)
                               {
                                   if (!ec)
                                   {
                                       //do_read_header();
                                   }
                               });
    return 0;
}
