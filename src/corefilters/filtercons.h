#ifndef _UTM_FILTERCONS_H
#define _UTM_FILTERCONS_H

#pragma once
#include <utm.h>

#include <filtercons_base.h>

namespace utm {

class filtercons :
	public filtercons_base
{
public:
	filtercons();
	~filtercons();

	unsigned int get_id() const { return filter_id; };
	void set_id(unsigned int id) { filter_id = id; };
};

}

#endif // _UTM_FILTERCONS_H