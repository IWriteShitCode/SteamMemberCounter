#ifndef CONNECTOR_H
#define CONNECTOR_H

#pragma comment(lib, "urlmon.lib")

#include <urlmon.h>
#include <sstream>

class Connector
{
public:
	Connector();
	~Connector();

	bool RequestMembers(unsigned int id);

	const char* GetBuffer() const { return m_Buffer; }

private:
	char m_Buffer[512 * 512];
};

#endif // !CONNECTOR_H