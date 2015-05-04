#include "stdafx.h"

#include "adapterinfo.h"
#include "addrip_v4.h"
#include "stringtools.h"

namespace utm {

const char adapterinfo::this_class_name[] = "adapterinfo";
const char adapterinfo::promiscuous_on[] = "Promiscous mode=on";
const char adapterinfo::promiscuous_off[] = "Promiscous mode=off";

adapterinfo::adapterinfo()
{
	clear();
}

adapterinfo::~adapterinfo()
{
}

std::string adapterinfo::getstr_adapterinfo(const char *text) const
{
	const char *pmode = is_promiscuous ? promiscuous_on : promiscuous_off;

	std::ostringstream oss;
	oss << text << " " << descr.getmb() << ", IP=" << addrip_v4(ipaddr_v4).to_string() << ", " << pmode;
	return oss.str();
}

#ifdef UTM_DEBUG
void adapterinfo::test_fillparams(int num)
{
	name = "{012345679}";
	descr = "Realtek 8139A";
	ipaddr_v4 = 3221225473;
	mask_v4 = 4294901760;
	medium = ADAPTER_MEDIUM_ETHERNET;
	mac_current.from_string("818283848586");
	mac_permanent.from_string("cacbcccdcecf");
	is_promiscuous = true;
	is_selected = true;

	std::string s = getstr_adapterinfo("test");
	TEST_CASE_CHECK(s, std::string("test Realtek 8139A, IP=192.0.0.1, Promiscous mode=on"));
}

void adapterinfo::test_all()
{
	adapterinfo ai;
	ai.test_fillparams(1);

	std::string s;
	ai.xml_create();
	ai.xml_get_string(s, true);

	return;
}

#endif

}