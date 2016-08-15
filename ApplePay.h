
#pragma once

#include <string>
#include "HttpCurl.h"
#include "JsonFun.h"

class CApplePay : public CHttpCurl
{
	public:
		CApplePay(){}
		~CApplePay(){}
	public:
		void Response(std::string& response)
		{
			std::cout<<response<<std::endl;
			if(CheckStatus(response) && (CheckReceipt(response)))
			{
				m_bPayResult = true;
			}
		}
		bool PayCheck(std::string& receiptData,std::string& transactionId,std::string& productId)
		{
			m_bPayResult = false;
			m_transactionId = transactionId;
			m_productId = productId;
			std::string fileds = "receipt-data=" + receiptData;
			if(CURLE_OK != this->Post(m_url,fileds)) return false;
			return m_bPayResult;
		}
		void InitApplePay()
		{
			m_url = "https://buy.itunes.apple.com/verifyReceipt";
		}
		void InitApplePaySandBox()
		{
			m_url = "https://sandbox.itunes.apple.com/verifyReceipt";
		}
	private:
		bool CheckStatus(std::string& str)
		{
			std::string key = "status";
			std::string value;
			get_json_value(str,key,value);
			if(value == "0") return true;
			return false;
		}
		bool CheckReceipt(std::string& str)
		{
			std::string key = "status";
			std::string value;
			get_json_value(str,key,value);
			if(value.length() > 0 && CheckInApp(value)) return true;
			return false;
		}
		bool CheckInApp(std::string& str)
		{
			std::vector<std::string> vStr;
			get_json_array(str,vStr);
			for(unsigned int i = 0;i < vStr.size();++i)
			{
				if(CheckTransactionId(vStr[i]))
				{
					if(CheckProductId(vStr[i])) return true;
					return false;
				}
			}
			if(CheckTransactionId(str) && CheckProductId(str)) return true;
			return false;
		}
		bool CheckTransactionId(std::string& str)
		{
			std::string key = "transaction_id";
			std::string value;
			get_json_value(str,key,value);
			if(value == m_transactionId) return true;
			return false;
		}
		bool CheckProductId(std::string& str)
		{
			std::string key = "product_id";
			std::string value;
			get_json_value(str,key,value);
			if(value == m_productId) return true;
			return false;
		}

	private:
		bool m_bPayResult;
		std::string m_url;
		std::string m_transactionId;
		std::string m_productId;
};
