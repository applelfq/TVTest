#ifndef TVTEST_TASK_TRAY_H
#define TVTEST_TASK_TRAY_H


namespace TVTest
{

	class CTaskTrayManager
	{
	public:
		enum class StatusFlag : unsigned int {
			None      = 0x0000U,
			Recording = 0x0001U,
			Minimized = 0x0002U,
			Standby   = 0x0004U,
		};

		enum {
			MESSAGE_ICON_NONE,
			MESSAGE_ICON_INFO,
			MESSAGE_ICON_WARNING,
			MESSAGE_ICON_ERROR
		};

		CTaskTrayManager();
		~CTaskTrayManager();
		bool Initialize(HWND hwnd, UINT Message);
		void Finalize();
		bool SetResident(bool fResident);
		bool GetResident() const { return m_fResident; }
		bool SetMinimizeToTray(bool fMinimizeToTray);
		bool GetMinimizeToTray() const { return m_fMinimizeToTray; }
		bool SetStatus(StatusFlag Status, StatusFlag Mask = EnumNot(StatusFlag::None));
		StatusFlag GetStatus() const { return m_Status; }
		bool SetTipText(LPCTSTR pszText);
		bool ShowMessage(LPCTSTR pszText, LPCTSTR pszTitle, int Icon = 0, DWORD TimeOut = 5000);
		bool HandleMessage(UINT Message, WPARAM wParam, LPARAM lParam);

	private:
		HWND m_hwnd;
		UINT m_TrayIconMessage;
		bool m_fResident;
		bool m_fMinimizeToTray;
		StatusFlag m_Status;
		UINT m_TaskbarCreatedMessage;
		String m_TipText;

		bool AddTrayIcon();
		bool RemoveTrayIcon();
		bool ChangeTrayIcon();
		HICON LoadTrayIcon() const;
		bool UpdateTipText();
		bool NeedTrayIcon() const;
	};

	TVTEST_ENUM_FLAGS(CTaskTrayManager::StatusFlag)

}	// namespace TVTest


#endif
