#ifndef _REQUESTS_H_
#define _REQUESTS_H_

#include <string>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;



class Requests
{
public:
    Requests();
    virtual ~Requests();
    
    constexpr static const char* get_general_get_head = R"(GET 1.0 HTTP/1.1)";
    constexpr static const char* get_general_post_head = R"(POST 1.0 HTTP/1.1)";
    
    virtual int post(string url, const char* buf, size_t len);
    virtual int post(string url, string file);
    
private:    
    static io_context& get_context()
    {
        static io_context _context;
        return _context;
    }
public:
private:

};

#endif
