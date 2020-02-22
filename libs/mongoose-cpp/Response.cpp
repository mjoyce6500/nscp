#include "Response.h"

#include <boost/foreach.hpp>

#include <sstream>

using namespace std;

namespace Mongoose
{
    Response::Response() : code(HTTP_OK), reason(REASON_OK), headers()
    {
    }
            
    Response::~Response()
    {
    }
            
    void Response::setHeader(string key, string value)
    {
        headers[key] = value;
    }

    bool Response::hasHeader(string key)
    {
        return headers.find(key) != headers.end();
    }

    string Response::getData()
    {
        string body = getBody();
        ostringstream data;

        data << "HTTP/1.1 " << code << " " << reason << "\r\n";

        if (!hasHeader("Content-Length")) {
            ostringstream length;
            length << body.size();
            setHeader("Content-Length", length.str());
        }

        map<string, string>::iterator it;
        BOOST_FOREACH(const header_type::value_type &v, headers) {
            data << v.first << ": " << v.second << "\r\n";
        }
		BOOST_FOREACH(const header_type::value_type &v, cookies) {
			data << "Set-cookie: " << v.first << "=" << v.second << "; path=/\r\n";
		}

        data << "\r\n";

        data << body;

        return data.str();
    }

    void Response::setCookie(string key, string value)
    {
		cookies[key] = value;
    }

    void Response::setCode(int code_, std::string reason_)
    {
        code = code_;
		reason = reason_;
    }

	void Response::setCodeOk()
	{
		code = HTTP_OK;
		reason = REASON_OK;
	}

	std::string Response::getCookie(std::string key) const {
		header_type::const_iterator cit = cookies.find(key);
		if (cit == cookies.end()) {
			return "";
		}
		return cit->second;
	}

}
