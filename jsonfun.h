
#pragma once

#include <jansson.h>
#include <sstream>
#include <vector>
#include <string>

static void get_json_array(std::string& source, std::vector<std::string>& vValue)
{
	json_error_t error;
	json_t* jsonbase = json_loads(source.c_str(),JSON_ENCODE_ANY,&error);
	if(jsonbase == NULL) return;
	if(json_is_array(jsonbase))
	{
		int array_size = (int)json_array_size(jsonbase);
		for(int i = 0;i < array_size;++i)
		{
			json_t* jsonvale = json_array_get(jsonbase,i);
			if(jsonvale)
			{
				std::string value;
				const char* pDump = json_dumps(jsonvale,JSON_ENCODE_ANY);
				if(pDump)
				{
					value = pDump;
					free((void*)pDump);
				}
				vValue.push_back(value);
			}		
		}
	}
	json_decref(jsonbase);
}

static void get_json_value(std::string& source, std::string& key,std::string& value)
{
	json_error_t error;
	json_t* jsonbase = json_loads(source.c_str(),JSON_ENCODE_ANY,&error);
	if(jsonbase == NULL) return;
	json_t* jsonvale = json_object_get(jsonbase,key.c_str());
	if(jsonvale)
	{
		if(json_is_string(jsonvale))
		{
			value = json_string_value(jsonvale);
		}else if(json_is_number(jsonvale))
		{
			int num = (int)json_number_value(jsonvale);
			std::stringstream ss;
			ss<<num;
			ss>>value;
		}else
		{
			const char* pDump = json_dumps(jsonvale,JSON_ENCODE_ANY);
			if(pDump)
			{
				value = pDump;
				free((void*)pDump);
			}
		}
	}
	json_decref(jsonbase);
}
