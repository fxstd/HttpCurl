
#pragma once

#include <curl/curl.h>

size_t rev_data(void *ptr, size_t size, size_t nmemb, void *stream);

class CHttpCurl
{
	public:
		CHttpCurl()
		{
			m_curlCode = CURLE_OK;
		}
		virtual ~CHttpCurl()
		{
		}
	public:
		//初始化 curl环境 只能调用1次
		static CURLcode CurlGlobalInit()
		{
			CURLcode m_curlCode = curl_global_init(CURL_GLOBAL_ALL);
			return m_curlCode;
		}
		//清理 curl环境 只能调用1次
		static void CurlGlobalCleanUp()
		{
			curl_global_cleanup();
		}
		//提交POST请求
		//url post请求的url地址
		//fileds post请求的表单数据
		//return CURLcode 
		CURLcode Post(std::string& url,std::string& fileds)
		{
			m_curl = curl_easy_init();
			curl_easy_setopt(m_curl, CURLOPT_URL,url.c_str());
			curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS,fileds.c_str());
			if(url.find("https://") != std::string::npos)
			{
				curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L);
				curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0L);
			}
			curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 3L);
			curl_easy_setopt(m_curl, CURLOPT_CONNECTTIMEOUT, 3L);
			curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, rev_data);
			curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);
			m_curlCode = curl_easy_perform(m_curl);
			curl_easy_cleanup(m_curl);
			return m_curlCode;
		}
		//提交GET请求
		//url get请求的url地址
		//return CURLcode
		CURLcode Get(std::string& url)
		{
			m_curl = curl_easy_init();
			curl_easy_setopt(m_curl, CURLOPT_URL,url.c_str());
			if(url.find("https://") != std::string::npos)
			{
				curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L);
				curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0L);
			}
			curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 3L);
			curl_easy_setopt(m_curl, CURLOPT_CONNECTTIMEOUT, 3L);
			curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, rev_data);
			curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);
			m_curlCode = curl_easy_perform(m_curl);
			curl_easy_cleanup(m_curl);
			return m_curlCode;
		}
		//return CURLcode 
		CURLcode GetCURLcode()
		{
			return m_curlCode;
		}
		//post/get 请求的相应函数
		//response 收到的相应数据
		virtual void Response(std::string& response) = 0;
	private:
		CURLcode m_curlCode;
		CURL* m_curl;
};
size_t rev_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	CHttpCurl* pHttp = (CHttpCurl*)stream;
	size_t len = size * nmemb;
	std::string response;
	if(ptr && len)
	{
		response.assign((char*)ptr,len);
	}
	pHttp->Response(response);
	return size * nmemb;
}
