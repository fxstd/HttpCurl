#include "HttpCurl.h"
		//提交POST请求
		//url post请求的url地址
		//fileds post请求的表单数据
		//return CURLcode 
		CURLcode CHttpCurl::Post(std::string& url,std::string& fileds)
		{
			m_curl = curl_easy_init();
			curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1L);
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
		CURLcode CHttpCurl::Get(std::string& url)
		{
			m_curl = curl_easy_init();
			curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1L);
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
		CURLcode CHttpCurl::GetCURLcode()
		{
			return m_curlCode;
		}
		//设置附带数据
		void CHttpCurl::SetExtra(void* extra)
		{
			m_extra = extra;
		}
		//获取附带数据
		void* CHttpCurl::GetExtra()
		{
			return m_extra;
		}
