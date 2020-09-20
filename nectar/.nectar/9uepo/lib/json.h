/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
#define JSMN_STRICT
#ifndef __NJS_ARDUINO
  #define JSMN_PARENT_LINK
#endif

#include "jsmn.h"

__NJS_VAR to_int(char const *s)
{
	bool _float = false;
	if(strchr(s, '.'))
	{
		return __NJS_VAR(stod(s));
	}
	else 
	{
		return __NJS_VAR(stoi(s));
	}
} 

static inline void *realloc_it(void *ptrmem, size_t size) {
  void *p = realloc(ptrmem, size);
  if (!p) {
    free(ptrmem);
    fprintf(stderr, "realloc(): errno=%d\n", errno);
  }
  return p;
}



char* substr(const char* arr, int begin, int len)
{
    char* res = new char[len];
    for (int i = 0; i < len; i++) res[i] = *(arr + begin + i);
    res[len] = 0;
    return res;
}



int dump(const char *js, jsmntok_t *t, size_t count, int indent, var& _res) 
{
  int i, j, k;
  jsmntok_t *key;
  if (count == 0) 
  {
    return 0;
  }
  if (t->type == JSMN_PRIMITIVE) 
  {
	  string _s = substr(js, t->start, t->end - t->start);
	if(_s[0] == 't') _res = true;
	else if(_s[0] == 'f') _res = false;
	else if(_s[0] == 'n') _res = var();
	else _res = to_int(_s.c_str());

    return 1;
  } 
  else if (t->type == JSMN_STRING) 
  {
	_res = substr(js, t->start, t->end - t->start);

    return 1;
  } 
  else if (t->type == JSMN_OBJECT) 
  {
    j = 0;
    _res = __NJS_Create_Object();
    for (i = 0; i < t->size; i++) 
    {
      key = t + 1 + j;
      var _key;
      j += dump(js, key, count - j, indent + 1, _key);
      var _value;
      if (key->size > 0) 
      {
        j += dump(js, t + 1 + j, count - j, indent + 1, _value);
      }
      __NJS_Object_Set(_key, _value, _res);
    }
    return j+1;
  } 
  else if (t->type == JSMN_ARRAY) 
  {
    j = 0;
    _res = __NJS_Create_Array();
    vector<var> _arr;

    
    for (i = 0; i < t->size; i++) 
    {
      var _value;  
      j += dump(js, t + 1 + j, count - j, indent + 1, _value);
      __NJS_Object_Set(i, _value, _res);
    }
    return j+1;
  }
  return 0;
}

__NJS_DECL_Function<NJS::VAR (var, vector<var>)>* __NJS_FN___5po78g = new __NJS_DECL_Function<NJS::VAR (var, vector<var>)>([](var __INJECTED_THIS, vector<var> __NJS_VARARGS ) -> NJS::VAR{var __json; if(__NJS_VARARGS.size() > 0) __json = __NJS_VARARGS[0];
	if(!__json) return NJS::Value::undefined;
	size_t tokcount = 32;
	int r;
	int j = 0;
	var __RESULT;
	const char* JSON_STRING = ((NJS::Class::String*)__json._ptr)->value.c_str();
	jsmn_parser p;
	jsmntok_t *tok = (jsmntok_t*)malloc(sizeof(*tok) * tokcount);

	jsmn_init(&p);
	
	int _again = 1;
	while(_again)
	{
		r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), tok, tokcount);
		if (r < 0) 
		{
			if (r == JSMN_ERROR_NOMEM) 
			{
				tokcount = tokcount * 2;
				tok = (jsmntok_t *)realloc_it(tok, sizeof(*tok) * tokcount);
			}
			else
			{
				printf("Failed to parse JSON: %d\n", r);
				return __RESULT;
			}
		}
		else 
		{
			dump(JSON_STRING, tok, p.toknext, 0, __RESULT);
			_again = 0;
		}
	}
	free(tok);
	return __RESULT;
;return __NJS_Create_Undefined();});var __NJS_JSON_PARSE=NJS::VAR(NJS::Enum::Type::Function, __NJS_FN___5po78g);;


__NJS_DECL_Function<NJS::VAR (var, vector<var>)>* __NJS_FN___ylc1k6 = new __NJS_DECL_Function<NJS::VAR (var, vector<var>)>([](var __INJECTED_THIS, vector<var> __NJS_VARARGS ) -> NJS::VAR{var __object; if(__NJS_VARARGS.size() > 0) __object = __NJS_VARARGS[0];
	return __NJS_Object_Stringify(__object);
;return __NJS_Create_Undefined();});var __NJS_JSON_STRINGIFY=NJS::VAR(NJS::Enum::Type::Function, __NJS_FN___ylc1k6);;
