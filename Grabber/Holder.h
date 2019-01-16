#ifndef HOLDER_H
#define HOLDER_H

#include <unordered_map>
#include <string>

struct SteamGameInfo
{
	unsigned int ID;
	unsigned int Members;
	unsigned int InGame;
	unsigned int Online;
	unsigned int InGroupChat;
	char Name[512];
};

class Holder
{
public:
	Holder();
	~Holder();

	void Flush();
	const SteamGameInfo* AddEntry(const SteamGameInfo& entry);
	
	const SteamGameInfo* GetSteamInfo(unsigned int id);
	const SteamGameInfo* GetSteamInfo(const std::string& id);

private:

	bool DoesExist(const std::string& id) const;

	std::unordered_map<std::string, SteamGameInfo> m_Entries;
};


#endif // !HOLDER_H
