#pragma once

#include <string>
#include "HttpCurl.h"
#include "JsonFun.h"

class CGooglePayAccessToken : public CHttpCurl
{
	public:
		CGooglePayAccessToken()
		{
			m_expiresTime = 0;
		}
		~CGooglePayAccessToken(){}
	public:
		void Response(std::string& response)
		{
			std::string key_access_token = "access_token";
			std::string key_expires_in = "expires_in";
			std::string access_token,expires_in;
			get_json_value(response,key_access_token,access_token);
			get_json_value(response,key_expires_in,expires_in);
			m_accessToken = access_token;
			m_expiresTime = time(NULL) + atoi(expires_in.c_str()) - 10;
		}
		CURLcode RefreshToken(std::string& client_id,std::string& client_secret,std::string& refresh_token)
		{
			std::string url = "https://accounts.google.com/o/oauth2/token";
			std::string fileds = "grant_type=refresh_token&client_id=" + client_id + "&client_secret=" + client_secret + "&refresh_token=" + refresh_token;
			return this->Post(url,fileds);
		}
		std::string GetAccessToken()
		{
			return m_accessToken;
		}
		unsigned int GetExpiresTime()
		{
			return m_expiresTime;
		}
	private:
		std::string m_accessToken;	
		unsigned int m_expiresTime;
};
class CGooglePay : public CHttpCurl
{
	public:
		CGooglePay(){}
		~CGooglePay(){}
	public:
		void Response(std::string& response)
		{
			std::string key_purchaseState = "purchaseState";
			std::string key_developerPayload = "developerPayload";
			std::string purchaseState,developerPayload;
			get_json_value(response,key_purchaseState,purchaseState);
			get_json_value(response,key_developerPayload,developerPayload);
			if(purchaseState == "0" && developerPayload == m_billNo) m_bPayResult = true;
		}
		bool PayCheck(std::string& packageName,std::string& productId,std::string& token,std::string& billNo)
		{
			m_bPayResult = false;
			m_billNo = billNo;
			if(time(NULL) >= m_payToken.GetExpiresTime())
			{
				if(CURLE_OK != m_payToken.RefreshToken(m_clientId,m_clientSecret,m_refreshToken)) return false;
			}
			if(time(NULL) >= m_payToken.GetExpiresTime()) return false;
			std::string url = "https://www.googleapis.com/androidpublisher/v2/applications/" +
				packageName + "/purchases/products/" + productId + 
				"/tokens/" + token + "?access_token=" + m_payToken.GetAccessToken();
			if(CURLE_OK != this->Get(url)) return false;
			return m_bPayResult;
		}
		void InitCGooglePay(std::string& client_id,std::string& client_secret,std::string& refresh_token)
		{
			m_clientId = client_id;
			m_clientSecret = client_secret;
			m_refreshToken = refresh_token;
		}
	private:
		CGooglePayAccessToken m_payToken;
		std::string m_clientId;
		std::string m_clientSecret;
		std::string m_refreshToken;
		bool m_bPayResult;
		std::string m_billNo;
};
