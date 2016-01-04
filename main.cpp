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
    std::string postfileds = "grant_type=refresh_token&client_id=client_id&client_secret=client_secret&refresh_tok=refresh_token";
    CHttpCurl::CurlGlobalInit();
    CHttpTest ht;
    ht.Post(posturl,postfileds);
    std::string geturl = "https://www.googleapis.com/androidpublisher/v2/applications/packageName/purchases/products/productId/tokens/token";
    ht.Get(geturl);
    CHttpCurl::CurlGlobalCleanUp();
    return 0;
}
