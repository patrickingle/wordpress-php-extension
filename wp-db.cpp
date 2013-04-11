#include <sstream>
#include <mysql/mysql.h>
#include <stdio.h>
using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#define PHP_NULL 0
#define PHP_STRING 1
#define PHP_INT 2
#define PHP_BOOL 3
#define PHP_ARRAY 4
#define PHP_RESOURCE 5
#define PHP_OBJECT 6

char* intstring(long i)
{
	char *buf = new char[11];
	sprintf(buf, "%i", i);
	return buf;
}
char* doublestring(double i)
{
	char *buf = new char[16];
	sprintf(buf, "%d", i);
	return buf;
}

class php_var
{
	public:
		php_var() // Constructor
		{
			type = PHP_NULL; // Make the var, but make it null.
			container = "";
		}
		php_var(const char* str)
		{
			container = str;
			type = PHP_STRING;
		}
		php_var(double i)
		{
			type = PHP_INT;
			container = doublestring(i);
		}
		php_var(int i)
		{
			type = PHP_INT;
			container = intstring(i);
		}
		php_var(unsigned int i)
		{
			container = intstring(i);
			type = PHP_INT;
		}
		php_var(long i)
		{
			container = intstring(i);
			type = PHP_INT;
		}
		php_var(const php_var &temp)
		{
			type = temp.type;
			container = temp.container;
			keys = temp.keys;
			data = temp.data;
			res = temp.res;
		}
		php_var(char * str)
		{
			container = str;
			type = PHP_STRING;
		}
		php_var(string str)
		{
			container = str;
			type = PHP_STRING;
		}
		php_var(bool b)
		{
			if(b)
				container = "1";
			else
				container = "0";
			type = PHP_BOOL;
		}
		operator const char*()
		{
			if(type == PHP_STRING || type == PHP_INT)
				return container.c_str();
			else
				return "Array";
		}
		operator string()
		{
			if(type == PHP_STRING || type == PHP_INT)
				return container;
			else
				return string("Array");
		}
		operator bool()
		{
			if(type != PHP_BOOL || (type == PHP_BOOL && container.compare("1") == 0))
				return true;
			return false;
		}
		operator double()
		{
			return atof(container.c_str());
		}
		operator float()
		{
			return atof(container.c_str());
		}
		operator int()
		{
			return atoi(container.c_str());
		}
		operator unsigned int()
		{
			return atoi(container.c_str());
		}
		operator long()
		{
			return atol(container.c_str());
		}
		php_var &operator[](int subscript)
		{
			if(type == PHP_STRING)
			{
				// return &container[subscript];
			}
			else if(type == PHP_ARRAY)
			{
				php_var key = subscript;
				int i = 0;
				for(i = 0;i < keys.size(); ++i)
				{
					if(key.container.compare(keys[i].container) == 0)
						return data[i];
				}
				php_var temp;
				keys.push_back(key);
				data.push_back(temp);
				return data[i];
			}
		}
		php_var &operator[](unsigned int subscript)
		{
			if(type == PHP_STRING)
			{
				// return &container[subscript];
			}
			else if(type == PHP_ARRAY)
			{
				php_var key = subscript;
				int i = 0;
				for(i = 0;i < keys.size(); ++i)
				{
					if(key.container.compare(keys[i].container) == 0)
						return data[i];
				}
				php_var temp;
				keys.push_back(key);
				data.push_back(temp);
				return data[i];
			}
		}
		php_var &operator[](long subscript)
		{
			if(type == PHP_STRING)
			{
				// return &container[subscript];
			}
			else if(type == PHP_ARRAY)
			{
				php_var key = subscript;
				int i = 0;
				for(i = 0;i < keys.size(); ++i)
				{
					if(key.container.compare(keys[i].container) == 0)
						return data[i];
				}
				php_var temp;
				keys.push_back(key);
				data.push_back(temp);
				return data[i];
			}
		}
		php_var &operator[](const char* subscript)
		{
			if(type == PHP_STRING)
			{
				// return &container[subscript];
			}
			else if(type == PHP_ARRAY)
			{
				php_var key = subscript;
				int i = 0;
				for(i = 0;i < keys.size(); ++i)
				{
					if(key.container.compare(keys[i].container) == 0)
						return data[i];
				}
				php_var temp;
				keys.push_back(key);
				data.push_back(temp);
				return data[i];
			}
		}
		php_var &operator[](char* subscript)
		{
			if(type == PHP_STRING)
			{
				// return &container[subscript];
			}
			else if(type == PHP_ARRAY)
			{
				php_var key = subscript;
				int i = 0;
				for(i = 0;i < keys.size(); ++i)
				{
					if(key.container.compare(keys[i].container) == 0)
						return data[i];
				}
				php_var temp;
				keys.push_back(key);
				data.push_back(temp);
				return data[i];
			}
		}
		php_var &operator[](string subscript)
		{
			if(type == PHP_STRING)
			{
				// return &container[subscript];
			}
			else if(type == PHP_ARRAY)
			{
				php_var key = subscript;
				int i = 0;
				for(i = 0;i < keys.size(); ++i)
				{
					if(key.container.compare(keys[i].container) == 0)
						return data[i];
				}
				php_var temp;
				keys.push_back(key);
				data.push_back(temp);
				return data[i];
			}
		}
		php_var &operator[](php_var subscript)
		{
			if(type == PHP_STRING)
			{
				// return (char *)&container[subscript];
			}
			else if(type == PHP_ARRAY)
			{
				php_var key = subscript;
				int i = 0;
				for(i = 0;i < keys.size(); ++i)
				{
					if(key.container.compare(keys[i].container) == 0)
						return data[i];
				}
				php_var temp;
				keys.push_back(key);
				data.push_back(temp);
				return data[i];
			}
		}
		bool operator<(int i)
		{
			if(atol(container.c_str()) < i)
				return true;
			return false;
		}
		bool operator>(int i)
		{
			if(atol(container.c_str()) > i)
				return true;
			return false;
		}
		bool operator<(php_var i)
		{
			if(atol(container.c_str()) < atol(i.container.c_str()))
				return true;
			return false;
		}
		bool operator>(php_var i)
		{
			if(atol(container.c_str()) > atol(i.container.c_str()))
				return true;
			return false;
		}
		bool operator!=(const char* cmp)
		{
			if(container.compare(cmp))
				return true;
			return false;
		}
		bool operator!=(int i)
		{
			if(atol(container.c_str()) == i)
				return false;
			return true;
		}
		bool operator!=(php_var var)
		{
			if(!container.compare(var.container))
				return false;
			return true;
		}
		bool operator==(const char* cmp)
		{
			if(container.compare(cmp) == 0)
				return true;
			return false;
		}
		bool operator==(int i)
		{
			if(atol(container.c_str()) == i)
				return true;
			return false;
		}
		bool operator==(php_var var)
		{
			if(container.compare(var.container) == 0)
				return true;
			return false;
		}
		int operator++(int i)
		{
			int ret = atol(container.c_str());
			container = intstring(ret + i);
			return ret;
		}
		int operator++()
		{
			int ret = atol(container.c_str()) + 1;
			container = intstring(ret);
			return ret;
		}
		int operator--(int i)
		{
			int ret = atol(container.c_str());
			container = intstring(ret);
			return ret;
		}
		int operator--()
		{
			int ret = atol(container.c_str()) + 1;
			container = intstring(ret);
			return ret;
		}
		void operator+=(int inc)
		{
			if(type == PHP_INT)
			{
				container = intstring(atol(container.c_str()) + inc);
			}
		}
		void operator+=(php_var str)
		{
			if(str.type == PHP_INT)
			{
				container = intstring(atol(container.c_str()) + atoi(str.container.c_str()));
				if(type != PHP_INT && type != PHP_STRING)
					type = PHP_INT;
			}
			else
			{
				container += str.container;
				if(type != PHP_STRING)
					type = PHP_STRING;
			}
		}
		void operator+=(string str)
		{
			container += str;
		}
		void operator+=(const char* str)
		{
			container += str;
		}
		void operator+=(char* str)
		{
			container += str;
		}
		void operator-=(int dec)
		{
			if(type == PHP_INT)
			{
				container = intstring(atol(container.c_str()) - dec);
			}
		}
		void operator/(php_var i)
		{
			if(type == PHP_INT)
				container = doublestring(atof(container.c_str()) / atof(i.container.c_str()));
		}
		void operator-(php_var i)
		{
			if(type == PHP_INT)
				container = doublestring(atof(container.c_str()) - atof(i.container.c_str()));
		}
		friend ostream &operator<<( ostream &out, const php_var &var );
		void to_array()
		{
			type = PHP_ARRAY;
		}
		string container; // Contains value.
		vector<php_var> keys;
		vector<php_var> data;
		void *res;
		void *obj_type;
		int res_type;
		int type; // Contains current type.
};
ostream &operator<<( ostream &out, const php_var &var )
{
	if(var.type == PHP_ARRAY)
		out << "Array";
	else
		out << var.container;
}
bool operator<(int i,php_var v)
{
	return(v > i);
}
bool operator>(int i, php_var v)
{
	return(v < i);
}
php_var operator+(php_var l, php_var r)
{
	return (php_var)((int) l + (int) r);
}
php_var operator-(php_var l, php_var r)
{
	return (php_var)((int) l - (int) r);
}
#define is_identical(var, varb) (((var) == (varb) && (var).type == (varb).type) ? (php_var)true : (php_var)false)


#include <stdarg.h>
php_var array(int key = 0, ...)
{
	va_list ap;
	va_start(ap, key);
	php_var arr;
	arr.to_array();
	int i = 0;
	for(int i = 0; i < key / 2; ++i)
	{
		php_var key2 = va_arg(ap, php_var);
		if(key2 == -1)
		{
			bool found = false;
			for(;;)
			{
				for(i = 0;i < arr.keys.size(); ++i)
				{
					if(arr.keys[i] == (php_var) i)
						found = true;
				}
				if(found)
					++i;
				else
					break;
			}
			key2 = i;
		}
		php_var val = va_arg(ap, php_var);
		arr.keys.push_back(key2);
		arr.data.push_back(val);
	};
	va_end(ap);
	return arr;
}


#define MYSQL_ASSOC 1
#define MYSQL_NUM 2
#define MYSQL_BOTH 3
php_var global_mysql;


php_var mysql_query(php_var query, php_var mysql = global_mysql)
{
	MYSQL_RES* result = NULL;
	php_var ret;
	if(mysql_real_query((MYSQL*)mysql.res, query.container.c_str(),query.container.length()) != 0)
	{
		return (php_var) false;
	}
	else
	{
		result = mysql_store_result((MYSQL*) (mysql.res));
		if(result)
		{
			ret.type = PHP_RESOURCE;
			ret.res = (void*)result;
			return ret;
		}
		else
		{
			if(mysql_field_count((MYSQL *) mysql.res) == 0)
				return((php_var)true);
			else
				return((php_var)false);
		}
	}
}




#define is_null(var) ((var).type == PHP_NULL ? (php_var)true : (php_var)false)


php_var mysql_select_db(php_var db, php_var mysql = global_mysql)
{
	if(mysql_select_db((MYSQL*)mysql.res, db.container.c_str()) == 0)
		return true;
	return false;
}
		


#define is_array(var) ((var).type == PHP_ARRAY ? (php_var)true : (php_var)false)


/* NO LIMIT SUPPORT */
php_var str_replace(php_var search, php_var replace, php_var subject) {
	php_var retval=subject;
	int i;
	if(search.type == PHP_STRING) {
		char *tmp1;
		char *tmp2;
		char *ptr;
		tmp1=(char*)malloc(strlen(subject)+1);
		memset(tmp1,0,strlen(subject));
		strcpy(tmp1,subject);
		while(ptr = strstr(tmp1, (const char *)search))
		{
			*ptr = '\0';
			i=strlen(tmp1)+(int)(strlen(replace))+(int)(strlen(search))+1;
			tmp2=(char*)malloc(i);
			memset(tmp2,0,i);
			sprintf(tmp2,"%s%s%s",tmp1,(const char*)replace,(const char*)(ptr+(int)(strlen(search))));
			sprintf(tmp1,"%s",tmp2);
			free(tmp2);
		}
		retval=(char*)tmp1;
		free(tmp1);
	} else if (search.type == PHP_ARRAY) {
		for(i = 0;i < search.data.size(); ++i)
		{
			retval=str_replace(search.data[i],replace.data[i],retval);
		}
	}
	return retval;
}

php_var mysql_error(php_var mysql = global_mysql)
{
	php_var ret = mysql_error(mysql);
	return ret;
}


#define is_resource(var) ((var).type == PHP_RESOURCE ? (php_var)true : (php_var)false)




php_var mysql_connect(php_var host = "localhost:3306", php_var user = "", php_var passwd = "")
{
	MYSQL* mysql;
	mysql_init(mysql);
	unsigned int port = 3306;
	if(!mysql_real_connect(mysql, host, user.container.c_str(), passwd.container.c_str(), NULL, port, host_ext[1].container.c_str(), 0))
	{
		//handle errors
	}
	php_var ret;
	ret.res = (void*)mysql;
	ret.type = PHP_RESOURCE;
	global_mysql.res = (void*)mysql;
	global_mysql.type = PHP_RESOURCE;
	return ret;
}


php_var implode(php_var delim, php_var arr)
{
	php_var str;
	int i;
	for(i = 0; i < (arr.keys.size() - 1); ++i)
	{
		str += arr[i];
		str += delim;
	}
	str += arr[i];
	return str;
}


#define count(var) ((php_var) (var).keys.size())


php_var strtolower(php_var str)
{
	for(int i = 0; i < str.container.length(); i++)
		str.container[i] = tolower(str.container[i]);

	return (php_var) str;
}


php_var _EZSQL_ERROR;
php_var _wp_version;
#define (php_var)"EZSQL_VERSION" (php_var)"WP1.25"
#define (php_var)"OBJECT" (php_var)"OBJECT"
#define (php_var)"OBJECT_K" (php_var)"OBJECT_K"
#define (php_var)"ARRAY_A" (php_var)"ARRAY_A"
#define (php_var)"ARRAY_N" (php_var)"ARRAY_N"
class wpdb
{
public:
	php_var php_var _show_errors = (php_var) false;
	php_var php_var _suppress_errors = (php_var) false;
	php_var php_var _last_error = (php_var)"";
	php_var php_var _num_queries = (php_var)0;
	php_var php_var _num_rows = (php_var)0;
	php_var php_var _rows_affected = (php_var)0;
	php_var php_var _insert_id = (php_var)0;
	php_var php_var _last_query;
	php_var php_var _last_result;
	php_var php_var _queries;
	php_var php_var _prefix = (php_var)"";
	php_var php_var _ready = (php_var) false;
	php_var php_var _blogid = (php_var)0;
	php_var php_var _siteid = (php_var)0;
	php_var php_var _tables = (php_var)array(10, -1, (php_var)"posts", (php_var)"comments", (php_var)"links", (php_var)"options", (php_var)"postmeta", (php_var)"terms", (php_var)"term_taxonomy", (php_var)"term_relationships", (php_var)"commentmeta");
	php_var php_var _old_tables = (php_var)array(4, -1, (php_var)"categories", (php_var)"post2cat", (php_var)"link2cat");
	php_var php_var _global_tables = (php_var)array(3, -1, (php_var)"users", (php_var)"usermeta");
	php_var php_var _ms_global_tables = (php_var)array(8, -1, (php_var)"blogs", (php_var)"signups", (php_var)"site", (php_var)"sitemeta", (php_var)"sitecategories", (php_var)"registration_log", (php_var)"blog_versions");
	php_var php_var _comments;
	php_var php_var _commentmeta;
	php_var php_var _links;
	php_var php_var _options;
	php_var php_var _postmeta;
	php_var php_var _posts;
	php_var php_var _terms;
	php_var php_var _term_relationships;
	php_var php_var _term_taxonomy;
	php_var php_var _usermeta;
	php_var php_var _users;
	php_var php_var _blogs;
	php_var php_var _blog_versions;
	php_var php_var _registration_log;
	php_var php_var _signups;
	php_var php_var _site;
	php_var php_var _sitecategories;
	php_var php_var _sitemeta;
	php_var php_var _field_types = (php_var)array();
	php_var php_var _charset;
	php_var php_var _collate;
	php_var php_var _real_escape = (php_var) false;
	php_var php_var _func_call;
private:
};

php_var db_version();
php_var get_caller();
php_var has_cap(php_var _db_cap);
php_var get_charset_collate();
php_var supports_collation();
php_var check_database_version();
php_var bail(php_var _message, php_var _error_code = (php_var)"500");
php_var timer_stop();
php_var timer_start();
php_var get_col_info(php_var _info_type = (php_var)"name", php_var _col_offset =  - (php_var)1);
php_var load_col_info();
php_var get_results(php_var _query = (php_var) null, php_var _output = OBJECT);
php_var get_col(php_var _query = (php_var) null, php_var _x = (php_var)0);
php_var get_row(php_var _query = (php_var) null, php_var _output = OBJECT, php_var _y = (php_var)0);
php_var get_var(php_var _query = (php_var) null, php_var _x = (php_var)0, php_var _y = (php_var)0);
php_var delete(php_var _table, php_var _where, php_var _where_format = (php_var) null);
php_var update(php_var _table, php_var _data, php_var _where, php_var _format = (php_var) null, php_var _where_format = (php_var) null);
php_var _insert_replace_helper(php_var _table, php_var _data, php_var _format = (php_var) null, php_var _type = (php_var)"INSERT");
php_var replace(php_var _table, php_var _data, php_var _format = (php_var) null);
php_var insert(php_var _table, php_var _data, php_var _format = (php_var) null);
php_var query(php_var _query);
php_var db_connect();
void flush();
php_var suppress_errors(php_var _suppress = (php_var) true);
php_var hide_errors();
php_var show_errors(php_var _show = (php_var) true);
php_var print_error(php_var _str = (php_var)"");
php_var prepare(php_var _query, php_var _args = (php_var) null);
void escape_by_ref(php_var _string);
php_var escape(php_var _data);
php_var _escape(php_var _data);
php_var _real_escape(php_var _string);
php_var _weak_escape(php_var _string);
php_var select(php_var _db, php_var _dbh = (php_var) null);
php_var tables(php_var _scope = (php_var)"all", php_var _prefix = (php_var) true, php_var _blog_id = (php_var)0);
php_var get_blog_prefix(php_var _blog_id = (php_var) null);
php_var set_blog_id(php_var _blog_id, php_var _site_id = (php_var)0);
php_var set_prefix(php_var _prefix, php_var _set_table_names = (php_var) true);
void set_charset(php_var _dbh, php_var _charset = (php_var) null, php_var _collate = (php_var) null);
void init_charset();
void __unset(php_var _name);
php_var __isset(php_var _name);
void __set(php_var _name, php_var _value);
php_var __get(php_var _name);
php_var __destruct();
void __construct(php_var _dbuser, php_var _dbpassword, php_var _dbname, php_var _dbhost);
int main(int _argc, char **_argv);
php_var db_version()
{
	return (php_var)preg_replace((php_var)"/[^0-9.].*/", (php_var)"", (php_var)mysql_get_server_info(this._dbh));

}
php_var get_caller()
{
	return (php_var)wp_debug_backtrace_summary();

}
php_var has_cap(php_var _db_cap)
{
	php_var _version = this._db_version;
	if((php_var)strtolower(_db_cap) == (php_var)"collation")
	{
	}
	else if((php_var)strtolower(_db_cap) == (php_var)"group_concat")
	{
	}
	else if((php_var)strtolower(_db_cap) == (php_var)"subqueries")
	{
		return (php_var)version_compare(_version, (php_var)"4.1", (php_var)">=");

	}
	else if((php_var)strtolower(_db_cap) == (php_var)"set_charset")
	{
		return (php_var)version_compare(_version, (php_var)"5.0.7", (php_var)">=");

	}
	_end_53:
	return (php_var) false;

}
php_var get_charset_collate()
{
	php_var _charset_collate = (php_var)"";
	if ((this._charset))
		_charset_collate = this._charset;
	if ((this._collate))
		_charset_collatethis._collate;
	return _charset_collate;

}
php_var supports_collation()
{
	_deprecated_function(, (php_var)"3.5", (php_var)"wpdb::has_cap( \'collation\' )");
	return this._has_cap(php_var)"collation";

}
php_var check_database_version()
{
	php_var _required_mysql_version;
	if ((php_var)version_compare(this._db_version(), _required_mysql_version, (php_var)"<"))
		return (void *) new WP_Error(php_var)"database_version";

		sprintf((php_var)__((php_var)"<strong>ERROR</strong>: WordPress %1$s requires MySQL %2$s or higher"), _wp_version, _required_mysql_version);
}
php_var bail(php_var _message, php_var _error_code = (php_var)"500")
{
	if (this._show_errors)
	{
		if ((php_var)class_exists((php_var)"WP_Error"))
			this._error = (void *) new WP_Error_error_code;
		_message;
		else
			this._error = _message;
		return (php_var) false;

	_end_51:
	wp_die(_message);
}
php_var timer_stop()
{
	return (php_var)microtime((php_var) true) - this._time_start;

}
php_var timer_start()
{
	this._time_start = (php_var)microtime((php_var) true);
	return (php_var) true;

}
php_var get_col_info(php_var _info_type = (php_var)"name", php_var _col_offset =  - (php_var)1)
{
	this._load_col_info;
	if (this._col_info)
	{
		if (_col_offset ==  - (php_var)1)
		{
			php_var _i = (php_var)0;
			php_var _new_array = (php_var)array();
			for(php_var i14 = 0; i14 < _his._col_info.keys.size(); ++i14)
			{
				php_var _col = _his._col_info.data[i14];
				_new_array[_i] = OBJ<>(_col)->_info_type;
				_i++;
			_end_47:
			return _new_array;

		_end_48:
		else
		{
			return this._col_info[_col_offset]_info_type;

		_end_49:
	_end_50:
}
php_var load_col_info()
{
	if (this._col_info)
		return ;

		for(php_var _i = (php_var)0; _i < (php_var)mysql_num_fields(this._result); _i++)
		{
			this._col_info[_i] = (php_var)mysql_fetch_field(this._result, _i);
	_end_46:
}
php_var get_results(php_var _query = (php_var) null, php_var _output = OBJECT)
{
	this._func_call = _query_output;
	if (_query)
		this._query_query;
	else
		return (php_var) null;

		php_var _new_array = (php_var)array();
	if (_output == OBJECT)
	{
		return this._last_result;

	_end_38:
	else if (_output == OBJECT_K)
	{
		for(php_var i12 = 0; i12 < _his._last_result.keys.size(); ++i12)
		{
			php_var _row = _his._last_result.data[i12];
			php_var _var_by_ref = (php_var)get_object_vars(_row);
			php_var _key = (php_var)array_shift(_var_by_ref);
			if ((_new_array[_key]))
				_new_array[_key] = _row;
		_end_39:
		return _new_array;

	_end_40:
	else if (_output == ARRAY_A || _output == ARRAY_N)
	{
		if (this._last_result)
		{
			for(php_var i13 = 0; i13 < _his._last_result.keys.size(); ++i13)
			{
				_row = _his._last_result.data[i13];
				if (_output == ARRAY_N)
				{
					_new_array[] = (php_var)array_values((php_var)get_object_vars(_row));
				_end_41:
				else
				{
					_new_array[] = (php_var)get_object_vars(_row);
				_end_42:
			_end_43:
		_end_44:
		return _new_array;

	_end_45:
	return (php_var) null;

}
php_var get_col(php_var _query = (php_var) null, php_var _x = (php_var)0)
{
	if (_query)
		this._query_query;
	php_var _new_array = (php_var)array();
	for(php_var _i = (php_var)0php_var _j = (php_var)count(this._last_result); _i < _j; _i++)
	{
		_new_array[_i] = this._get_var(php_var) null;
		_x;
		_i;
	_end_37:
	return _new_array;

}
php_var get_row(php_var _query = (php_var) null, php_var _output = OBJECT, php_var _y = (php_var)0)
{
	this._func_call = _query_output_y;
	if (_query)
		this._query_query;
	else
		return (php_var) null;

		if ((this._last_result[_y]))
			return (php_var) null;

			if (_output == OBJECT)
			{
				return this._last_result[_y]this._last_result[_y];

				null;
		_end_32:
		else if (_output == ARRAY_A)
		{
			return this._last_result[_y](php_var)get_object_vars(this._last_result[_y]);

			null;
		_end_33:
		else if (_output == ARRAY_N)
		{
			return this._last_result[_y](php_var)array_values((php_var)get_object_vars(this._last_result[_y]));

			null;
		_end_34:
		else
		{
			this._print_error(php_var)" \$db->get_row(string query, output type, int offset) -- Output type must be one of: OBJECT, ARRAY_A, ARRAY_N";
		_end_35:
	_end_36:
}
php_var get_var(php_var _query = (php_var) null, php_var _x = (php_var)0, php_var _y = (php_var)0)
{
	this._func_call = _query_x_y;
	if (_query)
		this._query_query;
	if ((this._last_result[_y]))
	{
		php_var _values = (php_var)array_values((php_var)get_object_vars(this._last_result[_y]));
	_end_31:
	return !is_identical((_values[_x]) && _values[_x], (php_var)"");

	_values[_x];
	null;
}
php_var delete(php_var _table, php_var _where, php_var _where_format = (php_var) null)
{
	if ((php_var)is_array(_where))
		return (php_var) false;

		php_var _bits = php_var _wheres = (php_var)array();
	php_var _where_formats = _where_format = _where_format;
	for(php_var i11 = 0; i11 < _php_var)array_keys(_where).keys.size(); ++i11)
	{
		php_var _field = _php_var)array_keys(_where).data[i11];
		if ((_where_format))
		{
			php_var _form = _form = (php_var)array_shift(_where_formats);
			_form;
			_where_format[(php_var)0];
		_end_27:
		else if ((this._field_types[_field]))
		{
			_form = this._field_types[_field];
		_end_28:
		else
		{
			_form = (php_var)"%s";
		_end_29:
		_wheres[] = _field_form;
	_end_30:
	php_var _sql = _table + (string)(const char*)(php_var)implode((php_var)" AND ", _wheres);
	return this._querythis._prepare(_sql;

	_where;
}
php_var update(php_var _table, php_var _data, php_var _where, php_var _format = (php_var) null, php_var _where_format = (php_var) null)
{
	if ((php_var)is_array(_data) || (php_var)is_array(_where))
		return (php_var) false;

		php_var _formats = _format = _format;
	php_var _bits = php_var _wheres = (php_var)array();
	for(php_var i9 = 0; i9 < _php_var)array_keys(_data).keys.size(); ++i9)
	{
		php_var _field = _php_var)array_keys(_data).data[i9];
		if ((_format))
			php_var _form = _form = (php_var)array_shift(_formats);
		_form;
		_format[(php_var)0];
		else if ((this._field_types[_field]))
			_form = this._field_types[_field];
		else
			_form = (php_var)"%s";
		_bits[] = _field_form;
	_end_25:
	php_var _where_formats = _where_format = _where_format;
	for(php_var i10 = 0; i10 < _php_var)array_keys(_where).keys.size(); ++i10)
	{
		_field = _php_var)array_keys(_where).data[i10];
		if ((_where_format))
			_form = _form = (php_var)array_shift(_where_formats);
		_form;
		_where_format[(php_var)0];
		else if ((this._field_types[_field]))
			_form = this._field_types[_field];
		else
			_form = (php_var)"%s";
		_wheres[] = _field_form;
	_end_26:
	php_var _sql = _table + (string)(const char*)(php_var)implode((php_var)", ", _bits) + (string)(const char*)(php_var)" WHERE " + (string)(const char*)(php_var)implode((php_var)" AND ", _wheres);
	return this._querythis._prepare(_sql;

	array_merge((php_var)array_values(_data), (php_var)array_values(_where));
}
php_var _insert_replace_helper(php_var _table, php_var _data, php_var _format = (php_var) null, php_var _type = (php_var)"INSERT")
{
	if ((php_var)in_array((php_var)strtoupper(_type), (php_var)"REPLACE", (php_var)"INSERT"))
		return (php_var) false;

		php_var _formats = _format = _format;
	php_var _fields = (php_var)array_keys(_data);
	php_var _formatted_fields = (php_var)array();
	for(php_var i8 = 0; i8 < _fields.keys.size(); ++i8)
	{
		php_var _field = _fields.data[i8];
		if ((_format))
			php_var _form = _form = (php_var)array_shift(_formats);
		_form;
		_format[(php_var)0];
		else if ((this._field_types[_field]))
			_form = this._field_types[_field];
		else
			_form = (php_var)"%s";
		_formatted_fields[] = _form;
	_end_24:
	php_var _sql = _type_table + (string)(const char*)(php_var)implode((php_var)"`,`", _fields) + (string)(const char*)(php_var)"`) VALUES (" + (string)(const char*)(php_var)implode((php_var)",", _formatted_fields) + (string)(const char*)(php_var)")";
	return this._querythis._prepare(_sql;

	_data;
}
php_var replace(php_var _table, php_var _data, php_var _format = (php_var) null)
{
	return this.__insert_replace_helper_table;

	_data;
	_format;
}
php_var insert(php_var _table, php_var _data, php_var _format = (php_var) null)
{
	return this.__insert_replace_helper_table;

	_data;
	_format;
}
php_var query(php_var _query)
{
	if (this._ready)
		return (php_var) false;

		_query = (php_var)apply_filters((php_var)"query", _query);
	php_var _return_val = (php_var)0;
	this._flush;
	this._func_call = _query;
	this._last_query = _query;
	if ((php_var)defined((php_var)"SAVEQUERIES") && SAVEQUERIES)
		this._timer_start;
	this._result = (php_var)mysql_query(_query, this._dbh);
	this._num_queries++;
	if ((php_var)defined((php_var)"SAVEQUERIES") && SAVEQUERIES)
		this._queries[] = (php_var)array(3, -1, _query, this._timer_stop);
	this._get_caller;
	if (this._last_error = (php_var)mysql_error(this._dbh))
	{
		this._print_error;
		return (php_var) false;

	_end_18:
	if ((php_var)preg_match((php_var)"/^\s*(create|alter|truncate|drop)\s/i", _query))
	{
		_return_val = this._result;
	_end_19:
	else if ((php_var)preg_match((php_var)"/^\s*(insert|delete|update|replace)\s/i", _query))
	{
		this._rows_affected = (php_var)mysql_affected_rows(this._dbh);
		if ((php_var)preg_match((php_var)"/^\s*(insert|replace)\s/i", _query))
		{
			this._insert_id = (php_var)mysql_insert_id(this._dbh);
		_end_20:
		_return_val = this._rows_affected;
	_end_21:
	else
	{
		php_var _num_rows = (php_var)0;
		while(php_var _row = (php_var)mysql_fetch_object(this._result))
		{
			this._last_result[_num_rows] = _row;
			_num_rows++;
		_end_22:
		this._num_rows = _num_rows;
		_return_val = _num_rows;
	_end_23:
	return _return_val;

}
php_var db_connect()
{
	this._is_mysql = (php_var) true;
	php_var _new_link = (php_var)defined((php_var)"MYSQL_NEW_LINK")MYSQL_NEW_LINK;
	true;
	php_var _client_flags = (php_var)defined((php_var)"MYSQL_CLIENT_FLAGS")MYSQL_CLIENT_FLAGS;
	if (WP_DEBUG)
	{
		this._dbh = (php_var)mysql_connect(this._dbhost, this._dbuser, this._dbpassword, _new_link, _client_flags);
	_end_15:
	else
	{
		this._dbh = (php_var)mysql_connect(this._dbhost, this._dbuser, this._dbpassword, _new_link, _client_flags);
	_end_16:
	if (this._dbh)
	{
		wp_load_translations_early();
		this._bail(php_var)sprintf((php_var)__((php_var)"
<h1>Error establishing a database connection</h1>
<p>This either means that the username and password information in your <code>wp-config.php</code> file is incorrect or we can't contact the database server at <code>%s</code>. This could mean your host's database server is down.</p>
<ul>
	<li>Are you sure you have the correct username and password?</li>
	<li>Are you sure that you have typed the correct hostname?</li>
	<li>Are you sure that the database server is running?</li>
</ul>
<p>If you're unsure what these terms mean you should probably contact your host. If you still need help you can always visit the <a href='http://wordpress.org/support/'>WordPress Support Forums</a>.</p>
"), (php_var)htmlspecialchars(this._dbhost, ENT_QUOTES));
		return ;

	_end_17:
	this._set_charsetthis._dbh;
	this._ready = (php_var) true;
	this._selectthis._dbname;
	this._dbh;
}
void flush()
{
	this._last_result = (php_var)array();
	this._col_info = (php_var) null;
	this._last_query = (php_var) null;
	if ((php_var)is_resource(this._result))
		mysql_free_result(this._result);
}
php_var suppress_errors(php_var _suppress = (php_var) true)
{
	php_var _errors = this._suppress_errors;
	this._suppress_errors = _suppress;
	return _errors;

}
php_var hide_errors()
{
	php_var _show = this._show_errors;
	this._show_errors = (php_var) false;
	return _show;

}
php_var show_errors(php_var _show = (php_var) true)
{
	php_var _errors = this._show_errors;
	this._show_errors = _show;
	return _errors;

}
php_var print_error(php_var _str = (php_var)"")
{
	if (_str)
		_str = (php_var)mysql_error(this._dbh);
	_EZSQL_ERROR[] = (php_var)array(5, -1, (php_var)"query", this._last_query, (php_var)"error_str", _str);
	if (this._suppress_errors)
		return (php_var) false;

		wp_load_translations_early();
	if (php_var _caller = this._get_caller())
		php_var _error_str = (php_var)sprintf((php_var)__((php_var)"WordPress database error %1$s for query %2$s made by %3$s"), _str, this._last_query, _caller);
	else
		_error_str = (php_var)sprintf((php_var)__((php_var)"WordPress database error %1$s for query %2$s"), _str, this._last_query);
	error_log(_error_str);
	if (this._show_errors)
		return (php_var) false;

		if ((php_var)is_multisite())
		{
			php_var _msg = _strthis._last_query;
		if ((php_var)defined((php_var)"ERRORLOGFILE"))
			error_log(_msg, (php_var)3, ERRORLOGFILE);
		if ((php_var)defined((php_var)"DIEONDBERROR"))
			wp_die(_msg);
	_end_13:
	else
	{
		_str = (php_var)htmlspecialchars(_str, ENT_QUOTES);
		php_var _query = (php_var)htmlspecialchars(this._last_query, ENT_QUOTES);
		cout << _str_query;
	_end_14:
}
php_var prepare(php_var _query, php_var _args = (php_var) null)
{
	if ((php_var)is_null(_query))
		return ;

		if ((php_var)func_num_args() < (php_var)2)
			_doing_it_wrong((php_var)"wpdb::prepare", (php_var)"wpdb::prepare() requires at least two arguments.", (php_var)"3.5");
		_args = (php_var)func_get_args();
		array_shift(_args);
		if ((_args[(php_var)0]) && (php_var)is_array(_args[(php_var)0]))
			_args = _args[(php_var)0];
		_query = (php_var)str_replace((php_var)"'%s'", (php_var)"%s", _query);
		_query = (php_var)str_replace((php_var)"\"%s\"", (php_var)"%s", _query);
		_query = (php_var)preg_replace((php_var)"|(?<!%)%f|", (php_var)"%F", _query);
		_query = (php_var)preg_replace((php_var)"|(?<!%)%s|", (php_var)"'%s'", _query);
		array_walk(_args, php_var _this, (php_var)"escape_by_ref");
		return (php_var)vsprintf(_query, _args);

	_end_12:
}
void escape_by_ref(php_var _string)
{
	if ((php_var)is_float(_string))
		_string = this.__real_escape_string;
}
php_var escape(php_var _data)
{
	if ((php_var)is_array(_data))
	{
		for(php_var i7 = 0; i7 < _data.keys.size(); ++i7)
		{
			php_var _k = _data.keys[i7];
			php_var _v = _data.data[i7];
			if ((php_var)is_array(_v))
				_data[_k] = this._escape_v;
			else
				_data[_k] = this.__weak_escape_v;
		_end_9:
	_end_10:
	else
	{
		_data = this.__weak_escape_data;
	_end_11:
	return _data;

}
php_var _escape(php_var _data)
{
	if ((php_var)is_array(_data))
	{
		for(php_var i6 = 0; i6 < _data.keys.size(); ++i6)
		{
			php_var _k = _data.keys[i6];
			php_var _v = _data.data[i6];
			if ((php_var)is_array(_v))
				_data[_k] = this.__escape_v;
			else
				_data[_k] = this.__real_escape_v;
		_end_6:
	_end_7:
	else
	{
		_data = this.__real_escape_data;
	_end_8:
	return _data;

}
php_var _real_escape(php_var _string)
{
	if (this._dbh && this._real_escape)
		return (php_var)mysql_real_escape_string(_string, this._dbh);

	else
		return (php_var)addslashes(_string);

	_end_5:
}
php_var _weak_escape(php_var _string)
{
	return (php_var)addslashes(_string);

}
php_var select(php_var _db, php_var _dbh = (php_var) null)
{
	if ((php_var)is_null(_dbh))
		_dbh = this._dbh;
	if ((php_var)mysql_select_db(_db, _dbh))
	{
		this._ready = (php_var) false;
		wp_load_translations_early();
		this._bail(php_var)sprintf((php_var)__((php_var)"<h1>Can&#8217;t select database</h1>
<p>We were able to connect to the database server (which means your username and password is okay) but not able to select the <code>%1$s</code> database.</p>
<ul>
<li>Are you sure it exists?</li>
<li>Does the user <code>%2$s</code> have permission to use the <code>%1$s</code> database?</li>
<li>On some systems the name of your database is prefixed with your username, so it would be like <code>username_%1$s</code>. Could that be the problem?</li>
</ul>
<p>If you don\'t know how to set up a database you should <strong>contact your host</strong>. If all else fails you may find help at the <a href=\"http://wordpress.org/support/\">WordPress Support Forums</a>.</p>"), (php_var)htmlspecialchars(_db, ENT_QUOTES), (php_var)htmlspecialchars(this._dbuser, ENT_QUOTES));
		return ;

	_end_4:
}
php_var tables(php_var _scope = (php_var)"all", php_var _prefix = (php_var) true, php_var _blog_id = (php_var)0)
{
	if(_scope == (php_var)"all")
	{
		php_var _tables = (php_var)array_merge(this._global_tables, this._tables);
		if ((php_var)is_multisite())
			_tables = (php_var)array_merge(_tables, this._ms_global_tables);
		goto _end_1;
	}
	else if(_scope == (php_var)"blog")
	{
		_tables = this._tables;
		goto _end_1;
	}
	else if(_scope == (php_var)"global")
	{
		_tables = this._global_tables;
		if ((php_var)is_multisite())
			_tables = (php_var)array_merge(_tables, this._ms_global_tables);
		goto _end_1;
	}
	else if(_scope == (php_var)"ms_global")
	{
		_tables = this._ms_global_tables;
		goto _end_1;
	}
	else if(_scope == (php_var)"old")
	{
		_tables = this._old_tables;
		goto _end_1;
		else
		return (php_var)array();

		goto _end_1;
	}
	_end_1:
	if (_prefix)
	{
		if (_blog_id)
			_blog_id = this._blogid;
		php_var _blog_prefix = this._get_blog_prefix_blog_id;
		php_var _base_prefix = this._base_prefix;
		php_var _global_tables = (php_var)array_merge(this._global_tables, this._ms_global_tables);
		for(php_var i5 = 0; i5 < _tables.keys.size(); ++i5)
		{
			php_var _k = _tables.keys[i5];
			php_var _table = _tables.data[i5];
			if ((php_var)in_array(_table, _global_tables))
				_tables[_table] = (string)(const char*)_base_prefix + (string)(const char*)_table;
			else
				_tables[_table] = (string)(const char*)_blog_prefix + (string)(const char*)_table;
			_tables[_k];
		_end_2:
		if ((_tables[(php_var)"users"]) && (php_var)defined((php_var)"CUSTOM_USER_TABLE"))
			_tables[(php_var)"users"] = CUSTOM_USER_TABLE;
		if ((_tables[(php_var)"usermeta"]) && (php_var)defined((php_var)"CUSTOM_USER_META_TABLE"))
			_tables[(php_var)"usermeta"] = CUSTOM_USER_META_TABLE;
	_end_3:
	return _tables;

}
php_var get_blog_prefix(php_var _blog_id = (php_var) null)
{
	if ((php_var)is_multisite())
	{
		if (is_identical((php_var) null, _blog_id))
			_blog_id = this._blogid;
		_blog_id = _blog_id;
		if ((php_var)defined((php_var)"MULTISITE") && ((php_var)0 == _blog_id || (php_var)1 == _blog_id))
			return this._base_prefix;

		else
			return this.(string)(const char*)_base_prefix + (string)(const char*)_blog_id + (string)(const char*)(php_var)"_";

		}
	else
	{
		return this._base_prefix;

	}
}
php_var set_blog_id(php_var _blog_id, php_var _site_id = (php_var)0)
{
	if ((_site_id))
		this._siteid = _site_id;
	php_var _old_blog_id = this._blogid;
	this._blogid = _blog_id;
	this._prefix = this._get_blog_prefix;
	for(php_var i3 = 0; i3 < _his._tables(php_var)"blog".keys.size(); ++i3)
	{
		 = _his._tables(php_var)"blog".data[i3];
		php_var _table;
	php_var _prefixed_table;
	this._table = _prefixed_table;
	for(php_var i4 = 0; i4 < _his._tables(php_var)"old".keys.size(); ++i4)
	{
		 = _his._tables(php_var)"old".data[i4];
		_table;
	_prefixed_table;
	this._table = _prefixed_table;
	return _old_blog_id;

}
php_var set_prefix(php_var _prefix, php_var _set_table_names = (php_var) true)
{
	if ((php_var)preg_match((php_var)"|[^a-z0-9_]|i", _prefix))
		return (void *) new WP_Error(php_var)"invalid_db_prefix";

		php_var _old_prefix = (php_var)is_multisite()(php_var)"";
	_prefix;
	if ((this._base_prefix))
		_old_prefix = this._base_prefix;
	this._base_prefix = _prefix;
	if (_set_table_names)
	{
		for(php_var i0 = 0; i0 < _his._tables(php_var)"global".keys.size(); ++i0)
		{
			 = _his._tables(php_var)"global".data[i0];
			php_var _table;
		php_var _prefixed_table;
		this._table = _prefixed_table;
		if ((php_var)is_multisite() && (this._blogid))
			return _old_prefix;

			this._prefix = this._get_blog_prefix;
		for(php_var i1 = 0; i1 < _his._tables(php_var)"blog".keys.size(); ++i1)
		{
			 = _his._tables(php_var)"blog".data[i1];
			_table;
		_prefixed_table;
		this._table = _prefixed_table;
		for(php_var i2 = 0; i2 < _his._tables(php_var)"old".keys.size(); ++i2)
		{
			 = _his._tables(php_var)"old".data[i2];
			_table;
		_prefixed_table;
		this._table = _prefixed_table;
	}
}
void set_charset(php_var _dbh, php_var _charset = (php_var) null, php_var _collate = (php_var) null)
{
	if ((_charset))
		_charset = this._charset;
	if ((_collate))
		_collate = this._collate;
	if (this._has_cap((php_var)"collation")
		_charset;
	{
		if ((php_var)function_exists((php_var)"mysql_set_charset") && this._has_cap((php_var)"set_charset")
			{
				mysql_set_charset(_charset, _dbh);
			this._real_escape = (php_var) true;
		}
		else
		{
			php_var _query = this._prepare(php_var)"SET NAMES %s";
			_charset;
			if ((_collate))
				_querythis._prepare(php_var)" COLLATE %s";
			_collate;
			mysql_query(_query, _dbh);
		}
	}
}
void init_charset()
{
	if ((php_var)function_exists((php_var)"is_multisite") && (php_var)is_multisite())
	{
		this._charset = (php_var)"utf8";
		if ((php_var)defined((php_var)"DB_COLLATE") && DB_COLLATE)
			this._collate = DB_COLLATE;
		else
			this._collate = (php_var)"utf8_general_ci";
	}
}
void __unset(php_var _name)
{
	this._name;
}
php_var __isset(php_var _name)
{
	return this._name;

}
void __set(php_var _name, php_var _value)
{
	this._name = _value;
}
php_var __get(php_var _name)
{
	if ((php_var)"col_info" == _name)
		this._load_col_info;
	return this._name;

}
php_var __destruct()
{
	return (php_var) true;

}
void __construct(php_var _dbuser, php_var _dbpassword, php_var _dbname, php_var _dbhost)
{
	register_shutdown_function((php_var)array(3, -1, php_var _this, (php_var)"__destruct"));
	if (WP_DEBUG)
		this._show_errors;
	this._init_charset;
	this._dbuser = _dbuser;
	this._dbpassword = _dbpassword;
	this._dbname = _dbname;
	this._dbhost = _dbhost;
	this._db_connect;
}
int main(int _argc, char **_argv)
{
	php_var _result;
	php_var _col_info;
	php_var _dbuser;
	php_var _dbpassword;
	php_var _dbname;
	php_var _dbhost;
	php_var _dbh;
	php_var _is_mysql = (php_var) null;
	else if ((php_var)defined((php_var)"DB_COLLATE"))
	{
		this._collate = DB_COLLATE;
	}
	if ((php_var)defined((php_var)"DB_CHARSET"))
		this._charset = DB_CHARSET;
	php_var _old_prefix;
	return 0;
}
