namespace NJS
{

	VAR::VAR()
	{
		type = NJS::Enum::Type::Undefined;
		_ptr = new NJS::Class::Undefined();
	}

	VAR::~VAR()
	{
		((NJS::Class::Base*)_ptr)->Delete();
	}

	/**/
	VAR::VAR(VAR const &_v)
	{
		
		type = _v.type;

		if (_v.type == NJS::Enum::Type::Object)
		{
			_ptr = _v._ptr;
			((NJS::Class::Object*)_ptr)->counter++;
		}
		else if (_v.type == NJS::Enum::Type::String)
		{
			_ptr = new NJS::Class::String(((NJS::Class::String*)_v._ptr)->value);
		}
		else if (_v.type == NJS::Enum::Type::Number)
		{
			if(((NJS::Class::Number*)_v._ptr)->isInt)
			{
				_ptr = new NJS::Class::Number(((NJS::Class::Number*)_v._ptr)->getInt());
			}
			else 
			{
				_ptr = new NJS::Class::Number(((NJS::Class::Number*)_v._ptr)->getDouble());
			}
		}
		else if (_v.type == NJS::Enum::Type::Function)
		{
			_ptr = _v._ptr;
			((NJS::Class::Function*)_ptr)->counter++;
		}
		else if (_v.type == NJS::Enum::Type::Array)
		{
			_ptr = _v._ptr;
			((NJS::Class::Array*)_ptr)->counter++;
		}
		else if (_v.type == NJS::Enum::Type::Native)
		{
			_ptr = _v._ptr;
			((NJS::Class::Native*)_ptr)->counter++;
		}
		else if (_v.type == NJS::Enum::Type::Boolean)
		{
			_ptr = _v._ptr;
			((NJS::Class::Boolean*)_ptr)->counter++;
		}
		else if (_v.type == NJS::Enum::Type::Undefined)
		{
			_ptr = _v._ptr;
			((NJS::Class::Undefined*)_ptr)->counter++;
		}
		else
		{
			_ptr = _v._ptr;
		}
	}
	/**/
	
	/*** CONSTRUCTOR ***/

	VAR::VAR(NJS::Enum::Type _type, int _value)
	{
		this->type = _type;
		_ptr = new NJS::Class::Number(_value);
	}

	VAR::VAR(int _value)
	{
		this->type = NJS::Enum::Type::Number;
		_ptr = new NJS::Class::Number(_value);
	}

	VAR::VAR(double _value)
	{
		this->type = NJS::Enum::Type::Number;
		_ptr = new NJS::Class::Number(_value);
	}
	
	VAR::VAR(long long _value)
	{
		this->type = NJS::Enum::Type::Number;
		_ptr = new NJS::Class::Number(_value);
	}

	VAR::VAR(char *_value)
	{
		type = NJS::Enum::Type::String;
		_ptr = new NJS::Class::String(_value);
	}

	VAR::VAR(std::string _value)
	{
		type = NJS::Enum::Type::String;
		_ptr = new NJS::Class::String(_value);
	}

	VAR::VAR(const char *_value)
	{
		type = NJS::Enum::Type::String;
		_ptr = new NJS::Class::String(_value);
	}

	VAR::VAR(NJS::Class::Array *_value)
	{
		type = NJS::Enum::Type::Array;
		_value->counter++;
		_ptr = _value;
	}
	
	VAR::VAR(const NJS::Class::Array *_value)
	{
		type = NJS::Enum::Type::Array;
		_ptr = (NJS::Class::Array *)_value;
		((NJS::Class::Array*)_ptr)->counter++;
	}
	
	VAR::VAR(NJS::Class::Boolean *_value)
	{
		type = NJS::Enum::Type::Boolean;
		_value->counter++;
		_ptr = _value;
	}
	
	VAR::VAR(NJS::Class::Function *_value)
	{
		type = NJS::Enum::Type::Function;
		_value->counter++;
		_ptr = _value;
	}
	
	VAR::VAR(NJS::Class::Object *_value)
	{
		type = NJS::Enum::Type::Object;
		_value->counter++;
		_ptr = _value;
	}
	
	VAR::VAR(NJS::Class::String *_value)
	{
		type = NJS::Enum::Type::String;
		_value->counter++;
		_ptr = new NJS::Class::String(_value->value);
	}
	
	VAR::VAR(NJS::Class::Number _value)
	{
		type = NJS::Enum::Type::Number;
		_ptr = new NJS::Class::Number(_value);
	}
	
	VAR::VAR(NJS::Class::Number *_value)
	{
		type = NJS::Enum::Type::Number;
		_value->counter++;
		_ptr = _value;
	}
	
	VAR::VAR(NJS::Class::Native *_value)
	{
		type = NJS::Enum::Type::Native;
		_value->counter++;
		_ptr = _value;
	}
	
	VAR::VAR(NJS::Class::Undefined *_value)
	{
		type = NJS::Enum::Type::Undefined;
		_value->counter++;
		_ptr = _value;
	}
	
	VAR::VAR(NJS::Enum::Type _type, void *_value)
	{
		type = _type;
		_ptr = new NJS::Class::Function(_value);
	}
	
	VAR::VAR(NJS::Enum::Type _type, void *_value, var _this)
	{
		type = _type;
		_ptr = new NJS::Class::Function(_value);
		((NJS::Class::Function*)_ptr)->This = _this;
	}

	VAR::VAR(function<VAR(vector<var>)> &_value)
	{
		type = NJS::Enum::Type::Function;
		_ptr = new NJS::Class::Function(&_value);
	}

	template <class... Args>
	VAR VAR::operator() (Args... args)
	{
		if (this->type != NJS::Enum::Type::Function)
		{
	#ifndef __NJS_ARDUINO
			throw NJS::VAR("TypeError: object is not a function");
	#endif
			exit(1);
		}
		else return (*(NJS::Class::Function*)_ptr)((VAR)(args)...);
	}
	
	/* END CALL OVERLOAD */

	VAR & VAR::operator[] (VAR _index)
	{
		return (*(NJS::Class::Base*)_ptr)[_index];
	}
	
	VAR & VAR::operator[] (VAR _index) const
	{
		return (*(NJS::Class::Base*)_ptr)[_index];
	}
	
	/* END ACCESS OVERLOAD */

	/*** END CONSTRUCTOR ***/

	/*** OPERATOR ***/
	VAR VAR::operator=(const VAR &_v)
	{
		((NJS::Class::Base*)_ptr)->Delete();

		type = _v.type;

		if (_v.type == NJS::Enum::Type::Object)
		{
			_ptr = _v._ptr;
			((NJS::Class::Object*)_ptr)->counter++;
		}
		else if (_v.type == NJS::Enum::Type::String)
		{
			_ptr = new NJS::Class::String((string)_v);
		}
		else if (_v.type == NJS::Enum::Type::Number)
		{
			if(((NJS::Class::Number*)_v._ptr)->isInt)
			{
				_ptr = new NJS::Class::Number(((NJS::Class::Number*)_v._ptr)->getInt());
			}
			else 
			{
				_ptr = new NJS::Class::Number(((NJS::Class::Number*)_v._ptr)->getDouble());
			}
		}
		else if (_v.type == NJS::Enum::Type::Function)
		{
			_ptr = _v._ptr;
			((NJS::Class::Function*)_ptr)->counter++;
		}
		else if (_v.type == NJS::Enum::Type::Array)
		{
			_ptr = _v._ptr;
			((NJS::Class::Array*)_ptr)->counter++;
		}
		else if (_v.type == NJS::Enum::Type::Native)
		{
			_ptr = _v._ptr;
			((NJS::Class::Native*)_ptr)->counter++;
		}
		else if (_v.type == NJS::Enum::Type::Boolean)
		{
			_ptr = _v._ptr;
			((NJS::Class::Boolean*)_ptr)->counter++;
		}
		else if (_v.type == NJS::Enum::Type::Undefined)
		{
			_ptr = _v._ptr;
			((NJS::Class::Undefined*)_ptr)->counter++;
		}
		else
		{
			_ptr = _v._ptr;
		}

		return *this;
	}

	/// Unary VAR::operators
	VAR VAR::operator+()
	{
		if (type == NJS::Enum::Type::Number)
			return *this;
		else
			return (double)*this;
	}
	
	VAR VAR::operator-()
	{
		if (type == NJS::Enum::Type::Number)
			return -(int)*this;
		else
			return -(double)*this;
	}
	VAR VAR::operator!() { return !(bool)*this; };

	/// Logical VAR::operators
	VAR VAR::operator&&(const VAR &_v1) { return (bool)*this && (bool)_v1; }
	VAR VAR::operator||(const VAR &_v1) { return (bool)*this || (bool)_v1; }

	/// Arithmetic VAR::operators
	VAR VAR::operator+(const VAR &_v1)
	{
		if (type == NJS::Enum::Type::String || type == NJS::Enum::Type::Array || type == NJS::Enum::Type::Object || _v1.type == NJS::Enum::Type::String)
			return __NJS_Concat_To_Str((string) * this, (string)_v1);
		else if (type == NJS::Enum::Type::Number)
		{
			return ((*(NJS::Class::Number*)_ptr)) + _v1;
		}
		else return VAR();
		
	}
	VAR VAR::operator+(const char _v1[])
	{
		return __NJS_Concat_To_Str((string)*this, _v1);
	}
	VAR VAR::operator+=(const VAR &_v1)
	{
		if(type == NJS::Enum::Type::Number) 
			(*((NJS::Class::Number*)_ptr)) += _v1;
		else if(type == NJS::Enum::Type::String) 
			((NJS::Class::String*)_ptr)->value += (string)_v1;
		else 
		{
			string _s = (string)*this;
			type = NJS::Enum::Type::String;
			_ptr = new NJS::Class::String("");
			((NJS::Class::String*)_ptr)->value += _s + (string)_v1;
		}
		return *this;
	}
	VAR VAR::operator-(const VAR &_v1)
	{
		if (type == NJS::Enum::Type::Number )
			return ((*(NJS::Class::Number*)_ptr)) - _v1;
		else return "NaN";
	}
	VAR VAR::operator-=(const VAR &_v1)
	{
		if(type == NJS::Enum::Type::Number && _v1.type == NJS::Enum::Type::Number) 
			(*((NJS::Class::Number*)_ptr)) -= _v1;
		else 
		{
			type = NJS::Enum::Type::ISNAN;
			_ptr = new NJS::Class::String("NaN");
		}
		return *this;
	}
	VAR VAR::operator*(const VAR &_v1)
	{
		if(type == NJS::Enum::Type::Number) 
			return (*((NJS::Class::Number*)_ptr)) * _v1;
		return VAR();
	}
	VAR VAR::operator*=(const VAR &_v1)
	{
		if(type == NJS::Enum::Type::Number) 
			(*((NJS::Class::Number*)_ptr)) *= _v1;
		return VAR();
	}
	VAR VAR::operator/(const VAR &_v1)
	{
		if (type == NJS::Enum::Type::Number)
			return (*((NJS::Class::Number*)_ptr)) / _v1;
		return VAR();
	}
	VAR VAR::operator/=(const VAR &_v1)
	{
		if(type == NJS::Enum::Type::Number) 
			(*((NJS::Class::Number*)_ptr)) /= _v1;
		return VAR();
	}
	VAR VAR::operator%(const VAR &_v1)
	{
		if (type == NJS::Enum::Type::Number && _v1.type == NJS::Enum::Type::Number)
			return (*((NJS::Class::Number*)_ptr)) % _v1;
		else
		{
			return remainder((int)(*((NJS::Class::Number*)_ptr)), (int)_v1);
		}
	}
	VAR VAR::operator%=(const VAR &_v1)
	{
		if (type == NJS::Enum::Type::Number && _v1.type == NJS::Enum::Type::Number)
		{
			(*((NJS::Class::Number*)_ptr)) %= _v1;
		}
		else
		{
			_ptr = new NJS::Class::Number(remainder((int)*this, (int)_v1));
		}
		return *this;
	}
	// TODO: "**" and "**=" VAR::operators
	VAR VAR::operator++(const int _v1)
	{
		if (type == NJS::Enum::Type::Number)
		{
			(*((NJS::Class::Number*)_ptr))++;
		}
		return *this;
	}
	VAR VAR::operator--(const int _v1)
	{
		if (type == NJS::Enum::Type::Number)
			(*((NJS::Class::Number*)_ptr))--;
		return *this;
	}

	/// Comparison VAR::operators
	VAR VAR::operator==(const VAR &_v1)
	{
		if (type == _v1.type)
		{
			switch (type)
			{
			case NJS::Enum::Type::Number:
				return (bool)((*((NJS::Class::Number*)_ptr)) == _v1);
			case NJS::Enum::Type::Boolean:
				return __NJS_Create_Boolean((bool)((NJS::Class::Boolean*)_ptr) == (bool)_v1);
			case NJS::Enum::Type::String:
				return __NJS_Create_Boolean((((NJS::Class::String*)_ptr)->value).compare((string)_v1) == 0);
			case NJS::Enum::Type::ISINFINITY:
			case NJS::Enum::Type::ISNULL:
			case NJS::Enum::Type::Undefined:
				return __NJS_Create_Boolean(true);
			case NJS::Enum::Type::Array:
			case NJS::Enum::Type::Native:
			case NJS::Enum::Type::Function:
			case NJS::Enum::Type::Object:
			case NJS::Enum::Type::ISNAN:
			default:
				return __NJS_Create_Boolean(false);
			}
		}
		else
		{
			if (type == NJS::Enum::Type::String || _v1.type == NJS::Enum::Type::String)
			{
				return __NJS_Create_Boolean((string) * this == (string)_v1);
			}
			else
				return __NJS_Create_Boolean((double)*this == (double)_v1);
		}
	}
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	VAR VAR::operator!=(const VAR &_v1)
	{
		return !(*this == _v1);
	}
	
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	VAR VAR::operator<(const VAR &_v1)
	{
		return (int)*this < (int)_v1;
	}
	VAR VAR::operator<=(const VAR &_v1)
	{
		return (int)*this <= (int)_v1;
	}
	VAR VAR::operator>(const VAR &_v1)
	{
		return (int)*this > (int)_v1;
	}
	VAR VAR::operator>=(const VAR &_v1)
	{
		return (int)*this >= (int)_v1;
	}

	/// Bitwise VAR::operators
	VAR VAR::operator&(const VAR &_v1) { return (int)*this & (int)_v1; }
	VAR VAR::operator&=(const VAR &_v1)
	{
		type = NJS::Enum::Type::Number;
		_ptr = new NJS::Class::Number((int)*this & (int)_v1);
		return *this;
	}
	VAR VAR::operator|(const VAR &_v1) { return (int)*this | (int)_v1; }
	VAR VAR::operator|=(const VAR &_v1)
	{
		type = NJS::Enum::Type::Number;
		_ptr = new NJS::Class::Number((int)*this | (int)_v1);
		return *this;
	}
	VAR VAR::operator^(const VAR &_v1) { return (int)*this ^ (int)_v1; }
	VAR VAR::operator^=(const VAR &_v1)
	{
		type = NJS::Enum::Type::Number;
		_ptr = new NJS::Class::Number((int)*this ^ (int)_v1);
		return *this;
	}
	VAR VAR::operator~() { return ~(int)*this; }
	VAR VAR::operator>>(const VAR &_v1) { return (int)*this >> (int)_v1; }
	VAR VAR::operator>>=(const VAR &_v1)
	{
		type = NJS::Enum::Type::Number;
		_ptr = new NJS::Class::Number((int)*this >> (int)_v1);
		return *this;
	}
	VAR VAR::operator<<(const VAR &_v1) 
	{ 
		return (int)*this << (int)_v1; 
	}
	VAR VAR::operator<<=(const VAR &_v1)
	{
		type = NJS::Enum::Type::Number;
		_ptr = new NJS::Class::Number((int)*this << (int)_v1);
		return *this;
	}

	VAR::operator int() const
	{
		return (int)(*(NJS::Class::Base*)_ptr);
	}

	VAR::operator double() const
	{
		return (double)(*(NJS::Class::Base*)_ptr);
	}

	VAR::operator bool() const
	{
		return (bool)(*(NJS::Class::Base*)_ptr);
	}

	VAR::operator string() const
	{
		return (string)(*(NJS::Class::Base*)_ptr);
	}
	
	VAR::operator const char*() const
	{
		return ((string)*this).c_str();
	}
	
	VAR::operator const long long() const
	{
		return (long long)((double)*this);
	}

		
} // namespace NJS