#include "stdafx.h"
#include "enumhelper.h"

#include <boost/test/unit_test.hpp>

namespace utm {

const char enumhelper::this_class_name[] = "enumhelper";

#ifdef UTM_DEBUG
const char* enumhelper::teststates_str[] = {
	"error",
	"info",
	"debug"
};

const int enumhelper::teststates_int[] = { 
	(int)error, 
	(int)info, 
	(int)debug 
};
#endif

enumhelper::enumhelper(void)
{
}


enumhelper::~enumhelper(void)
{
}

const char* enumhelper::to_str(int cat, const char** enum_str, const int* enum_int, int maxitems)
{
	for (int i = 0; i < maxitems; ++i)
	{
		if (*enum_int == cat)
			return *enum_str;

		enum_int++;
		enum_str++;
	}

	return NULL;
}

int enumhelper::from_str(const char* str, const char** enum_str, const int* enum_int, int maxitems, int default_item)
{
	int retval = default_item;
	for (int i = 0; i < maxitems; ++i)
	{
		if (strcmp(*enum_str, str) == 0)
		{
			retval = *enum_int;
			break;
		}

		enum_int++;
		enum_str++;
	}
	return retval;
}

int enumhelper::from_str_ci(const char* str, const char** enum_str, const int* enum_int, int maxitems, int default_item)
{
	int retval = default_item;
	for (int i = 0; i < maxitems; ++i)
	{
		if (_stricmp(*enum_str, str) == 0)
		{
			retval = *enum_int;
			break;
		}

		enum_int++;
		enum_str++;
	}
	return retval;
}

#ifdef UTM_DEBUG
BOOST_AUTO_TEST_CASE(enumhelper_test_all)
{
	const char* c1 = enumhelper::to_str((int)enumhelper::info, &enumhelper::teststates_str[0], &enumhelper::teststates_int[0], MAX_TESTSTATES_ITEMS);
	BOOST_REQUIRE_EQUAL(c1, "info");

	const char* c2 = enumhelper::to_str((int)enumhelper::debug, &enumhelper::teststates_str[0], &enumhelper::teststates_int[0], MAX_TESTSTATES_ITEMS);
	BOOST_REQUIRE_EQUAL(c2, "debug");

	const char* c3 = enumhelper::to_str(-1, &enumhelper::teststates_str[0], &enumhelper::teststates_int[0], MAX_TESTSTATES_ITEMS);
	const char* nptr = NULL;
	BOOST_REQUIRE_EQUAL(c3, nptr);

	int k1 = enumhelper::from_str("info", &enumhelper::teststates_str[0], &enumhelper::teststates_int[0], MAX_TESTSTATES_ITEMS, (int)enumhelper::error);
	BOOST_REQUIRE_EQUAL(k1, (int)enumhelper::info);

	int k2 = enumhelper::from_str("debug", &enumhelper::teststates_str[0], &enumhelper::teststates_int[0], MAX_TESTSTATES_ITEMS, (int)enumhelper::error);
	BOOST_REQUIRE_EQUAL(k2, (int)enumhelper::debug);

	int k3 = enumhelper::from_str("debug2", &enumhelper::teststates_str[0], &enumhelper::teststates_int[0], MAX_TESTSTATES_ITEMS, (int)enumhelper::error);
	BOOST_REQUIRE_EQUAL(k3, (int)enumhelper::error);
}
#endif

}
