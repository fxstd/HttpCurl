# HttpCurl
封装了简单的http/https post/get方法 基于libcurl实现

# Example
例子：main.cpp
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <iostream>
#include "HttpCurl.h"

class CHttpTest : public CHttpCurl
{
    public:
        CHttpTest(){}
        ~CHttpTest(){}
        void Response(std::string& response)
        {   
            std::cout<<response<<std::endl;
        }   
};

int main()
{
    std::string posturl = "https://accounts.google.com/o/oauth2/token";
    std::string postfileds = "grant_type=refresh_token&client_id=client_id&client_secret=client_secret&refresh_token=refresh_token";
    CHttpCurl::CurlGlobalInit();
    CHttpTest ht;
    ht.Post(posturl,postfileds);
    std::string geturl = "https://www.googleapis.com/androidpublisher/v2/applications/packageName/purchases/products/productId/tokens/token";
    ht.Get(geturl);
    CHttpCurl::CurlGlobalCleanUp();
    return 0;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
编译命令：g++ main.cpp -o test -lcurl -g

./test
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

{
  "error" : "invalid_request",
  "error_description" : "Missing required parameter: refresh_token"
}
{
 "error": {
  "errors": [
   {
    "domain": "global",
    "reason": "required",
    "message": "Login Required",
    "locationType": "header",
    "location": "Authorization"
   }
  ],
  "code": 401,
  "message": "Login Required"
 }
}

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
