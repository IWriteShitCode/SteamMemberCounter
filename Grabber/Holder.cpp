#include "Holder.h"

Holder::Holder() { }

Holder::~Holder() 
{
	Flush();
}

void Holder::Flush()
{
	m_Entries.clear();
}

const SteamGameInfo* Holder::AddEntry(const SteamGameInfo& entry)
{
	std::string idStr = std::to_string(entry.ID);

	if (DoesExist(entry.Name))
	{
		printf("The entry: %s already exists in the entries.\n", entry.Name);
		return false;
	}

	m_Entries.insert({ entry.Name, entry });

	return &m_Entries.at(entry.Name);
}

const SteamGameInfo* Holder::GetSteamInfo(unsigned int id)
{
	std::string idStr = std::to_string(id);

	return DoesExist(idStr) ? &m_Entries.at(idStr) : nullptr;
}

const SteamGameInfo* Holder::GetSteamInfo(const std::string& id)
{
	return DoesExist(id) ? &m_Entries.at(id) : nullptr;
}

bool Holder::DoesExist(const std::string& id) const
{
	return (m_Entries.find(id) != m_Entries.end());
}
