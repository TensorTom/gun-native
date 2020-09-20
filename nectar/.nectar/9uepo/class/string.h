#pragma once
#include "string_header.h"
#include <string>
#include <limits>
#define __NJS_Class_String_Init()\
counter++; \
__NJS_CreateMethodToClass("toString", toString); \
__NJS_CreateMethodToClass("split", split); \
__NJS_CreateMethodToClass("indexOf", indexOf); \
__NJS_CreateMethodToClass("lastIndexOf", lastIndexOf); \
__NJS_CreateMethodToClass("search", search); \
__NJS_CreateMethodToClass("slice", slice); \
__NJS_CreateMethodToClass("substr", substr); \
__NJS_CreateMethodToClass("replace", replace);

namespace NJS::Class
{
	// Constructors
	String::String()
	{ 
		__NJS_Class_String_Init();
		__NJS_Object_Set("length", NJS::VAR((int)value.size()), &object);
	}
	String::String(std::string val)
	{
		__NJS_Class_String_Init();
		value = val;
		__NJS_Object_Set("length", NJS::VAR((int)value.size()), &object);
	}
	String::String(const char* val)
	{
		__NJS_Class_String_Init();
		value = val;
		__NJS_Object_Set("length", NJS::VAR((int)value.size()), &object);
	}
	// Methods
	void String::Delete() noexcept
	{
		if (--counter < 1)
		{
			delete this;
		}
	}
	// Native cast
	String::operator bool() const noexcept { return value.size() > 0; }
	String::operator double() const noexcept
	{
		std::string::size_type end;
		auto res = std::stod(value, &end);
		return end == value.size() ? res : std::numeric_limits<double>::quiet_NaN();
	}
	String::operator int() const noexcept
	{
		std::string::size_type end;
		auto res = std::stoi(value, &end, 10);
		return end == value.size() ? res : std::numeric_limits<int>::quiet_NaN();
	}
	String::operator long long() const noexcept
	{
		std::string::size_type end;
		auto res = std::stoll(value, &end, 10);
		return end == value.size() ? res : std::numeric_limits<long long>::quiet_NaN();
	}
	String::operator std::string() const noexcept { return value; }
	// Main operators
	NJS::VAR const String::operator[](NJS::VAR key) const
	{
		if (key.type == NJS::Enum::Type::Number)
		{
			auto i = (int)key;
			if (i >= 0 && i <= value.size())
			{
				return value.at(i);
			}
		}
		auto &obj = this->object;
		auto index = (std::string)key;
		int _j = obj.size();
		for (int _i = 0; _i < _j; _i++)
		{
			if (index.compare(obj[_i].first) == 0)
			{
				return obj[_i].second;
			}
		}
		return NJS::VAR();
	}
	NJS::VAR &String::operator[](NJS::VAR key)
	{
		static NJS::VAR _char;
		if (key.type == NJS::Enum::Type::Number)
		{
			auto i = (int)key;
			if (i >= 0)
			{
				if (i >= value.size())
				{
					value.resize(i + 1);
					__NJS_Object_Set("length", (int)value.size(), &this->object);
				}
				_char = value.at(i);
			}
			return _char;
		}
		
		for (auto & search : object)
		{
			if (((NJS::Class::String*)key._ptr)->value.compare(search.first) == 0)
			{
				return search.second;
			}
		}

		((NJS::Class::String*)key._ptr)->counter++;
		object.push_back(pair_t(((NJS::Class::String*)key._ptr)->value.c_str(), __NJS_VAR()));
		return object[object.size() - 1].second;
	}
	template <class... Args>
	NJS::VAR String::operator()(Args... args) const { throw InvalidTypeException(); }
	// Comparation operators
	String String::operator!() const { throw InvalidTypeException(); }
	bool String::operator==(const String &_v1) const { return value.compare(_v1.value) == 0; }
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	bool String::operator!=(const String &_v1) const { return value.compare(_v1.value) != 0; }
	bool String::operator<(const String &_v1) const { return value.at(0) < _v1.value.at(0); }
	bool String::operator<=(const String &_v1) const { return value.at(0) <= _v1.value.at(0); }
	bool String::operator>(const String &_v1) const { return value.at(0) > _v1.value.at(0); }
	bool String::operator>=(const String &_v1) const { return value.at(0) >= _v1.value.at(0); }
	// Numeric operators
	String String::operator+() const { throw InvalidTypeException(); }
	String String::operator-() const { throw InvalidTypeException(); }
	String String::operator++(const int _v1) { throw InvalidTypeException(); }
	String String::operator--(const int _v1) { throw InvalidTypeException(); }
	String String::operator+(const String &_v1) const { return value + _v1.value; }
	String String::operator+=(const String &_v1) { value += _v1.value; return *this; }
	String String::operator-(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator-=(const String &_v1) { throw InvalidTypeException(); }
	String String::operator*(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator*=(const String &_v1) { throw InvalidTypeException(); }
	// TODO: "**" and "**=" operators
	String String::operator/(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator/=(const String &_v1) { throw InvalidTypeException(); }
	String String::operator%(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator%=(const String &_v1) { throw InvalidTypeException(); }
	String String::operator&(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator|(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator^(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator~() const { throw InvalidTypeException(); }
	String String::operator>>(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator<<(const String &_v1) const { throw InvalidTypeException(); }
	String String::operator&=(const String &_v1) { throw InvalidTypeException(); }
	String String::operator|=(const String &_v1) { throw InvalidTypeException(); }
	String String::operator^=(const String &_v1) { throw InvalidTypeException(); }
	String String::operator>>=(const String &_v1) { throw InvalidTypeException(); }
	String String::operator<<=(const String &_v1) { throw InvalidTypeException(); }
	// TODO: ">>>" and ">>>=" operators
	/*** STRING METHODS ***/
	NJS::VAR String::toString(std::vector<NJS::VAR> _args) const
	{
		return value;
	}
	
	NJS::VAR String::split(std::vector<NJS::VAR> _args) const
	{
		var _needle;
		if (_args.size() > 0)
			_needle = _args[0];
		else
			return NJS::VAR(this->value);

		NJS::VAR _arr = __NJS_Create_Array();
		char *_v = (char *)malloc(strlen(this->value.c_str()) + 1);
		strcpy(_v, this->value.c_str());
		char *delim = (char *)malloc(strlen(((std::string)_needle).c_str()) + 1);
		strcpy(delim, ((std::string)_needle).c_str());

		char *ptr = strtok(_v, delim);
		int i = 0;
		char *_new;
		while (ptr != NULL)
		{
			_new = (char *)malloc(strlen(ptr) + 1);
			strcpy(_new, ptr);
			__NJS_Object_Set(i, _new, _arr);
			free(_new);
			ptr = strtok(NULL, delim);
			i++;
		}

		free(delim);
		return _arr;
	}
	
	NJS::VAR String::indexOf(std::vector<NJS::VAR> _args) const
	{
		var _needle;
		if (_args.size() > 0)
			_needle = _args[0];
		else
			return NJS::VAR(-1);

		string::size_type loc = this->value.find((std::string)_needle, 0);
		if (loc != string::npos)
		{
			return NJS::VAR((int)loc);
		}
		return NJS::VAR(-1);
	}
	
	NJS::VAR String::lastIndexOf(std::vector<NJS::VAR> _args) const
	{
		var _needle;
		if (_args.size() > 0)
			_needle = _args[0];
		else
			return NJS::VAR(-1);

		string::size_type loc = this->value.find_last_of((std::string)_needle, 0);
		if (loc != string::npos)
		{
			return NJS::VAR((int)loc);
		}
		return NJS::VAR(-1);
	}
	
	NJS::VAR String::search(std::vector<NJS::VAR> _args) const
	{
		var _needle;
		if (_args.size() > 0)
			_needle = _args[0];
		else
			return NJS::VAR(-1);

		string::size_type loc = this->value.find((std::string)_needle, 0);
		if (loc != string::npos)
		{
			return NJS::VAR((int)loc);
		}
		return NJS::VAR(-1);
	}
	
	NJS::VAR String::slice(std::vector<NJS::VAR> _args) const
	{
		var _start;
		var _end;
		if (_args.size() > 0)
			_start = _args[0];
		else
			return NJS::VAR(this->value);
		if (_args.size() > 1)
			_end = _args[1];

		if (_end.type == NJS::Enum::Type::Undefined)
			return NJS::VAR(this->value.substr((int)_start, string::npos));
		int _endIndex = (int)_end - (int)_start;
		return NJS::VAR(this->value.substr((int)_start, _endIndex));
	}
	
	NJS::VAR String::substr(std::vector<NJS::VAR> _args) const
	{
		var _start;
		var _end;
		if (_args.size() > 0)
			_start = _args[0];
		else
			return NJS::VAR(this->value);
		if (_args.size() > 1)
			_end = _args[1];

		if (_end.type == NJS::Enum::Type::Undefined)
			return NJS::VAR(this->value.substr((int)_start, string::npos));
		return NJS::VAR(this->value.substr((int)_start, (int)_end));
	}
		
	NJS::VAR String::replace(std::vector<NJS::VAR> _args) const
	{
		var _search;
		var _replace;
		if (_args.size() > 0)
			_search = _args[0];
		else
			return NJS::VAR(this->value);
		if (_args.size() > 1)
			_replace = _args[1];

		size_t start_pos = this->value.find((std::string)_search);
		if (start_pos == std::string::npos)
		{
			return var(value);
		}
		
		std::string _new = value;
		return var(_new.replace(start_pos, ((std::string)_search).length(), (std::string)_replace));
	}
	/* END STRING METHODS */
} // namespace NJS::Class
