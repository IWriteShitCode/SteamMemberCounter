#include "Connector.h"

Connector::Connector()
{
	memset(m_Buffer, 0, sizeof(m_Buffer));
}

Connector::~Connector() { }

static bool Request(IStream* stream, WCHAR* url)
{
	HRESULT result = URLOpenBlockingStream(0, url, &stream, 0, 0);
	if (result != 0)
	{
		return false;
	}

	return true;
}

static void BuildURL(const wchar_t* start, unsigned int id, const wchar_t* end, wchar_t* buffer, size_t bufferLength)
{
	memset((void*)buffer, 0, bufferLength);

	std::wstring idStr = std::to_wstring(id);

	size_t offset = 0;

	wcscat(buffer, start);
	offset += lstrlenW(end);

	wcscat(buffer, idStr.c_str());
	offset += lstrlenW(idStr.c_str());

	wcscat(buffer, end);
	offset += lstrlenW(end);
}

bool Connector::RequestMembers(unsigned int id)
{
	IStream* stream = nullptr;
	WCHAR url[512] = { 0 };
	BuildURL(L"https://steamcommunity.com/games/", id, L"/members", url, 512);

	if (!Request(stream, url))
	{
		printf("Request for ID: %u failed.\n", id);
		return false;
	}

	//Also works with https URL's - unsure about the extent of SSL support though.
	HRESULT result = URLOpenBlockingStream(0, url, &stream, 0, 0);
	if (result != 0)
	{
		printf("Could not open stream: %u failed.\n", id);
		return false;
	}

	char buffer[60000];
	unsigned long bytesRead;
	std::stringstream ss;
	stream->Read(buffer, 60000, &bytesRead);
	while (bytesRead > 0U)
	{
		ss.write(buffer, (long long)bytesRead);
		stream->Read(buffer, 60000, &bytesRead);
	}
	stream->Release();
	std::string resultString = ss.str();
	strncpy_s(m_Buffer, ss.str().c_str(), sizeof(m_Buffer));

	return true;
}