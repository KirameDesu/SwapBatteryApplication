#include "RegisterData.h"

RegisterData::RegisterData(const qint16 regStart, const Setting& set)
	: _title(set.title), _type(set.dataType), _registerGroupStart(regStart)
{
}

RegisterData::~RegisterData()
{
}
