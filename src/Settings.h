#ifndef TVTEST_SETTINGS_H
#define TVTEST_SETTINGS_H


#include <vector>
#include "IniFile.h"


class CSettings
{
public:
	enum class OpenFlag : unsigned int {
		None          = 0x0000U,
		Read          = 0x0001U,
		Write         = 0x0002U,
		WriteVolatile = 0x0004U,
	};

	typedef TVTest::CIniFile::CEntry CEntry;
	typedef TVTest::CIniFile::EntryArray EntryList;

	CSettings();
	~CSettings();
	bool Open(LPCTSTR pszFileName, OpenFlag Flags);
	void Close();
	bool IsOpened() const;
	bool Clear();
	bool SetSection(LPCTSTR pszSection);
	bool IsSectionExists(LPCTSTR pszSection);
	bool GetEntries(EntryList *pEntries);
	bool IsValueExists(LPCTSTR pszValueName);
	bool DeleteValue(LPCTSTR pszValueName);
	bool Read(LPCTSTR pszValueName, int *pData);
	bool Write(LPCTSTR pszValueName, int Data);
	bool Read(LPCTSTR pszValueName, unsigned int *pData);
	bool Write(LPCTSTR pszValueName, unsigned int Data);
	bool Read(LPCTSTR pszValueName, LPTSTR pszData, unsigned int Max);
	bool Write(LPCTSTR pszValueName, LPCTSTR pszData);
	bool Read(LPCTSTR pszValueName, TVTest::String *pValue);
	bool Write(LPCTSTR pszValueName, const TVTest::String &Value);
	bool Read(LPCTSTR pszValueName, bool *pfData);
	bool Write(LPCTSTR pszValueName, bool fData);
	bool Read(LPCTSTR pszValueName, double *pData);
	bool Write(LPCTSTR pszValueName, double Data, int Digits);
	bool Read(LPCTSTR pszValueName, float *pData);
	bool ReadColor(LPCTSTR pszValueName, COLORREF *pcrData);
	bool WriteColor(LPCTSTR pszValueName, COLORREF crData);
	bool Read(LPCTSTR pszValueName, LOGFONT *pFont);
	bool Write(LPCTSTR pszValueName, const LOGFONT *pFont);

private:
	TVTest::CIniFile m_IniFile;
	OpenFlag m_OpenFlags;
};

TVTEST_ENUM_FLAGS(CSettings::OpenFlag)

class ABSTRACT_CLASS(CSettingsBase)
{
public:
	CSettingsBase();
	CSettingsBase(LPCTSTR pszSection);
	virtual ~CSettingsBase() = default;
	virtual bool ReadSettings(CSettings &Settings) { return false; }
	virtual bool WriteSettings(CSettings &Settings) { return false; }
	virtual bool LoadSettings(CSettings &Settings);
	virtual bool SaveSettings(CSettings &Settings);
	bool LoadSettings(LPCTSTR pszFileName);
	bool SaveSettings(LPCTSTR pszFileName);
	bool IsChanged() const { return m_fChanged; }
	void SetChanged() { m_fChanged = true; }
	void ClearChanged() { m_fChanged = false; }

protected:
	LPCTSTR m_pszSection;
	bool m_fChanged;
};


#endif
