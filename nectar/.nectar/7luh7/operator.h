NJS::VAR __NJS_Boolean_Result(NJS::VAR _v)
{
	if (_v.type == NJS::Enum::Type::Number)
		return ((NJS::Class::Number*)_v._ptr);
	else if (_v.type == NJS::Enum::Type::Boolean)
		return ((NJS::Class::Boolean*)_v._ptr);
	else if (_v.type == NJS::Enum::Type::String)
	{
		if (strlen(((NJS::Class::String*)_v._ptr)->value.c_str()) > 0)
			return true;
		else
			return false;
	}
	else if (_v.type == NJS::Enum::Type::Array)
		return true;
	else
		return false;
}

ostream &operator<<(ostream &os, const NJS::VAR &_v)
{
	switch (_v.type)
	{
	case NJS::Enum::Type::Undefined:
		os << (std::string)(*(NJS::Class::Undefined*)_v._ptr);
		break;
	case NJS::Enum::Type::Boolean:
		os << (std::string)(*(NJS::Class::Boolean*)_v._ptr);
		break;
	case NJS::Enum::Type::Number:
		os << (std::string)(*(NJS::Class::Number*)_v._ptr);
		break;
	case NJS::Enum::Type::String:
		os << (std::string)(*(NJS::Class::String*)_v._ptr);
		break;
	case NJS::Enum::Type::Object:
		os << __NJS_Object_Stringify(_v);
		break;
	case NJS::Enum::Type::Array:
		os << __NJS_Object_Stringify(_v);
		break;
	case NJS::Enum::Type::Native:
		os << "[Native]";
		break;
	case NJS::Enum::Type::ISNAN:
		os << "NaN";
		break;
	case NJS::Enum::Type::Function:
		os << (std::string)(*(NJS::Class::Function*)_v._ptr);
		break;
	case NJS::Enum::Type::ISINFINITY:
		os << "Infinity";
		break;
	case NJS::Enum::Type::ISNULL:
		os << "null";
		break;
	default:
		os << "undefined";
		break;
	}
	return os;
}

NJS::VAR parseInt(NJS::VAR _str)
{
	if (_str.type == NJS::Enum::Type::String)
	{
#ifdef __NJS_ARDUINO
		return NJS::VAR();
#else
		return __NJS_Create_Number(stoi(((NJS::Class::String*)_str._ptr)->value));
#endif
	}
	else
		return __NJS_Create_Undefined();
}

NJS::VAR __NJS_Log_Console(NJS::VAR _var)
{
#ifdef __NJS_ARDUINO

#else
	cout << _var;
	cout << endl;
#endif

	return NJS::VAR();
}

NJS::VAR __NJS_Object_Keys(NJS::VAR _var)
{
	if (_var.type != NJS::Enum::Type::Object)
		return 0;
	var _res = __NJS_Create_Array();

	vector<pair<const char *, NJS::VAR>> *_obj = &((NJS::Class::Object*)_var._ptr)->object;
	int _j = (*_obj).size();
	for (int _i = 0; _i < _j; _i++)
	{
		__NJS_Object_Set(_i, (*_obj)[_i].first, _res);
	}
	return _res;
}

NJS::VAR __NJS_Object_Stringify(NJS::VAR _var)
{
	return __NJS_Object_Stringify(_var, true);
}
NJS::VAR __NJS_Object_Stringify(NJS::VAR _var, bool _bracket)
{

	NJS::Enum::Type _t = _var.type;

	if (_t == NJS::Enum::Type::Undefined)
		return "undefined";
	else if (_t == NJS::Enum::Type::ISNAN)
		return "NaN";
	else if (_t == NJS::Enum::Type::Number)
		return var("") + _var;
	else if (_t == NJS::Enum::Type::String)
		return var("\"") + _var + "\"";
	else if (_t == NJS::Enum::Type::Function)
		return var("\"") + (std::string)(*(NJS::Class::Function*)_var._ptr) + "\"";
	else if (_t == NJS::Enum::Type::Array)
	{
		var _res = "";
		std::vector<NJS::VAR> *_arr = &((NJS::Class::Array*)_var._ptr)->value;
		if(_bracket) _res += "[";
		int j = (*_arr).size();
		for (int i = 0; i < j; i++)
		{
			if (i > 0)
				_res += ",";
			_res += __NJS_Object_Stringify((*_arr)[i], _bracket);
		}
		if(_bracket) _res += "]";

		return _res;
	}
	else if (_t == NJS::Enum::Type::Object)
	{
		var _res = "";
		vector<pair<const char *, NJS::VAR>> *_obj = &((NJS::Class::Object*)_var._ptr)->object;
		_res = "{";
		int j = (*_obj).size();
		for (int _i = 0; _i < j; _i++)
		{
			if (_i > 0)
				_res += ", ";
			_res += var("\"") + (*_obj)[_i].first + "\"";
			_res += ":";
			_res += __NJS_Object_Stringify((*_obj)[_i].second);
		}
		_res += "}";
		return _res;
	}
	else
		return "";
}

NJS::VAR __NJS_Object_Clone(NJS::VAR _var)
{
	NJS::Enum::Type _t = _var.type;
	switch(_t)
	{
		case NJS::Enum::Type::Undefined:
		case NJS::Enum::Type::ISNAN:
		case NJS::Enum::Type::Number:
		case NJS::Enum::Type::String:
		case NJS::Enum::Type::Function:
			return _var;
		case NJS::Enum::Type::Array:
		{
			var _res = __NJS_Create_Array();
			std::vector<NJS::VAR> *_arr = &((NJS::Class::Array*)_var._ptr)->value;

			int j = (*_arr).size();
			for (int i = 0; i < j; i++)
			{
				__NJS_Object_Set(i, __NJS_Object_Clone((*_arr)[i]), _res);
			}
			return _res;
		}
		case NJS::Enum::Type::Object:
		{
			var _res = __NJS_Create_Object();
			vector<pair<const char *, NJS::VAR>> *_obj = &((NJS::Class::Object*)_var._ptr)->object;
			int j = (*_obj).size();
			for (int _i = 0; _i < j; _i++)
			{
				__NJS_Object_Set((*_obj)[_i].first, __NJS_Object_Clone((*_obj)[_i].second), _res);
			}
			return _res;
		}
		default:
			return NJS::VAR();
	}
}

void __NJS_Object_Construct(NJS::VAR _this, NJS::VAR _prototype)
{
	if(_this.type == NJS::Enum::Type::Object && _prototype.type == NJS::Enum::Type::Object)
	{
		vector<pair<const char *, NJS::VAR>> *_obj = &((NJS::Class::Object*)_prototype._ptr)->object;
		int j = (*_obj).size();
		for (int _i = 0; _i < j; _i++)
		{
			NJS::VAR _tmp =  __NJS_Object_Get((*_obj)[_i].first, _this);
			if(_tmp.type == NJS::Enum::Type::Undefined)
			{
				__NJS_Object_Set((*_obj)[_i].first, (*_obj)[_i].second, _this);
			}
		}
	}
	
}


NJS::VAR __NJS_Create_Object()
{
	NJS::Class::Object *_obj = new NJS::Class::Object();
	return NJS::VAR(_obj);
}

NJS::VAR __NJS_CREATE_Function(void *_fn)
{
	return NJS::VAR(NJS::Enum::Type::Function, _fn);
}

NJS::VAR __NJS_Create_Native(void *_native)
{
	return NJS::VAR(NJS::Enum::Type::Undefined, _native);
}

/*
void* __NJS_Get_Function(NJS::VAR _fn)
{
  return _fn.get().f;
}
*/

function<var(vector<var>)> *__NJS_Get_Function(NJS::VAR _v)
{
	return (function<var(vector<var>)> *)((NJS::Class::Function*)_v._ptr)->value;
}

void *__NJS_Get_Native(NJS::VAR _native)
{
	return ((NJS::Class::Function*)_native._ptr);
}

/*** REDIFINING STD OPERATORS ***/

template <typename t>
t operator+(t _left, const NJS::VAR &_right)
{
	return _left + (t)_right;
}

std::string operator+(const char* _left, const NJS::VAR &_right)
{
	return std::string(_left) + (std::string)_right;
}

template <typename t>
t operator-(t _left, const NJS::VAR &_right)
{
	return _left - (t)_right;
}

template <typename t>
t operator*(t _left, const NJS::VAR &_right)
{
	return _left * (t)_right;
}

template <typename t>
t operator/(t _left, const NJS::VAR &_right)
{
	return _left / (t)_right;
}

template <typename t, typename u>
t operator<(t _left, const u &_right)
{
	return _left < (t)_right;
}

template <typename t, typename u>
t operator<=(t _left, const u &_right)
{
	return _left <= (t)_right;
}


template <typename t>
t operator>(t _left, const NJS::VAR &_right)
{
	return _left > (t)_right;
}

template <typename t>
t operator>=(t _left, const NJS::VAR &_right)
{
	return _left >= (t)_right;
}

/*** END REDIFINING STD OPERATORS ***/

__NJS_Create_Lambda(__IMPL_EVAL)
{
	__NJS_Log_Console("eval not implemented, return undefined");
	return var();
});
var eval = __NJS_Create_Function(__IMPL_EVAL);

function<NJS::VAR(vector<var>)> *__NJS_IS_NAN = new function<NJS::VAR(vector<var>)>([](vector<var> _NJS_VARARGS) {
	var _test;
	if (_NJS_VARARGS.size() > 0)
		_test = _NJS_VARARGS[0];
	else
		return __NJS_Create_Boolean(0);

	if (_test.type == NJS::Enum::Type::Number)
	{
		return __NJS_Create_Boolean(1);
	}

	return __NJS_Create_Boolean(0);
});

NJS::VAR isNaN = NJS::VAR(NJS::Enum::Type::Function, __NJS_IS_NAN);

NJS::VAR __NJS_EQUAL_VALUE_AND_TYPE(NJS::VAR _left, NJS::VAR _right)
{
	if (_left.type == _right.type && _left == _right)
	{
		return __NJS_Create_Boolean(1);
	}

	return __NJS_Create_Boolean(0);
}

NJS::VAR __NJS_NOT_EQUAL_VALUE_AND_TYPE(NJS::VAR _left, NJS::VAR _right)
{
	if (_left.type != _right.type || _left != _right)
	{
		return __NJS_Create_Boolean(1);
	}

	return __NJS_Create_Boolean(0);
}