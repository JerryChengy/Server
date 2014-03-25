#ifndef CW_TESTDATA_H
#define CW_TESTDATA_H


struct HumanData 
{
	int		m_ID;	
	int		m_Level;
	void    CleanUp()
	{
		m_ID = 0;
		m_Level = 0;
	}
	HumanData(){ CleanUp(); }
};
//static int MaxHumanDataVersion = 0;
//void UpgradeHumanData(int fromVer, int toVer, void* fromData, void* toData)
//{
//
//}
struct PacketHumanData 
{
	int		m_Size;
	HumanData	m_Data;
	void	CleanUp()
	{
		m_Size = sizeof(HumanData);
	}
	PacketHumanData(){ CleanUp(); }
};
#endif