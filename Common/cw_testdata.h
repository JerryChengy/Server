#ifndef CW_TESTDATA_H
#define CW_TESTDATA_H


struct HumanData 
{
	int		m_ID;
	short	m_Sex;
	char	m_Name[16];
	int		m_QuestData[30*1024];
	void    CleanUp()
	{
		m_ID = -1;
		m_Sex = 0;
		memset(m_Name, 0, sizeof(m_Name));
		memset(m_QuestData, 0, sizeof(m_QuestData));
	}
	HumanData(){ CleanUp(); }
};
#endif