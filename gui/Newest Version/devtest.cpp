//#include "Window.h"
//#include "Cursor.h"
//#include "ComboBox.h"
//#include "Checkbutton.h"
//#include "Button.h"
//#include "Menu.h"
//#include "ContextMenu.h"
//#include "TextEntry.h"
//#include "Icon.h"
//#include "Label.h"
//#include "RichEdit.h"
//#include "Fonts.h"
//#include "Paint.h"
//#include "ListBox.h"
//#include "Screen.h"
//#include "SubDialog.h"
//#include "gui_resource.h"
//#include "TreeView.h"
//#include "LoadingBar.h"
//#include "ListView.h"
//#include "StatusBar.h"
//#include "TabController.h"
//#include "FileDialogs.h"
//#include "DatePicker.h"
//
//using namespace gui;
//
////set this to 0 and type text and stuff into the rich edit
////when set to 1 it makes the window use a WM_PAINT that doesnt return the BasecCass::ElementProc
////and this breaks the rich edit.
//#define BROKEN_RICHEDIT_EXAMPLE 0
//
//class CTestSubDialog : public SubDialog
//{
//	DECLARE_ELEMENT_DIALOG(CTestSubDialog, SubDialog)
//
//	void OnCreate(ELEMENT_PROC_ITEMS)
//	{
//		HICON icon = LoadIconFromFile("icon1.ico");
//		if (icon)
//			SetIcon(icon, true);
//
//		SetBounds(100, 100, 400, 600);
//		SetDeleteOnClose(true);
//
//		Button* button = new Button(this, "Hello World", 1001);
//		button->SetBounds(100, 100, 200, 25);
//	}
//
//	void OnCommand(ELEMENT_PROC_ITEMS)
//	{
//		if (LOWORD(wp) == 1001)
//		{
//			ShowMessageBox(0, "Test", "Hello World (:");
//		}
//	}
//	
//	void OnEraseBk(ELEMENT_PROC_ITEMS)
//	{
//		PAINT_BACKGROUND_START(hwnd, 255, 100, 0);
//		PAINT_SET_CLIENT_RECT(hwnd);
//		PAINT_FILL(hwnd);
//		PAINT_BACKGROUND_END(hwnd)
//	}
//
//	DECLARE_ELEMENT_DLGPROC()
//};
//
//START_ELEMENT_DLGPROC(CTestSubDialog)
//DEFINE_ELEMENT_PROC(WM_INITDIALOG, OnCreate)
//DEFINE_ELEMENT_PROC(WM_ERASEBKGND, OnEraseBk)
//DEFINE_ELEMENT_PROC(WM_COMMAND, OnCommand)
//END_ELEMENT_PROC(BaseClass::ElementDialogProc(ELEMENT_ITEMS))
//
//class CMainWindow : public Window
//{
//	DECLARE_ELEMENT_NOSUBPROC(CMainWindow, Window);
//
//	CMainWindow();
//
//	void OnCreate(ELEMENT_PROC_ITEMS);
//	void OnLButtonClick(ELEMENT_PROC_ITEMS);
//	void OnLButtonDown(ELEMENT_PROC_ITEMS);
//	void OnLButtonUp(ELEMENT_PROC_ITEMS);
//	void OnMouseMove(ELEMENT_PROC_ITEMS);
//	void OnRButtonDblClick(ELEMENT_PROC_ITEMS);
//	void OnSize(ELEMENT_PROC_ITEMS);
//	void RedrawBkground(ELEMENT_PROC_ITEMS);
//	int OnCommand(int id, int lp);
//	void OnPaint(ELEMENT_PROC_ITEMS);
//	virtual void OnFileSelected(int id, const char* file, FileDialogType type) override;
//
//	DECLARE_ELEMENT_PROC();
//	ComboBox* cb;
//	CheckButton* cb2;
//	Menu* cmenu, *file;
//	TextEntry* te;
//	POINT pt;
//	ListBox* lb;
//
//	bool bInPaint;
//	LoadingBar* lb2;
//	StatusBar* sb;
//
//	DatePicker* dp;
//};
//
//START_ELEMENT_PROC(CMainWindow)
//DEFINE_ELEMENT_PROC_RETURN(WM_CREATE, OnCreate, 0);
//DEFINE_ELEMENT_PROC_RETURN(WM_CLOSE, OnClose, 0);
//
////DEFINE_ELEMENT_PROC_RETURN(WM_RBUTTONDBLCLK, OnRButtonDblClick, 0);
////DEFINE_ELEMENT_PROC_RETURN(WM_LBUTTONDOWN, OnRButtonDblClick, 0);
//DEFINE_ELEMENT_PROC_RETURN(WM_COMMAND, NO_PROC, OnCommand(LOWORD(wp), 0));
//#if BROKEN_RICHEDIT_EXAMPLE
//DEFINE_ELEMENT_PROC_RETURN(WM_PAINT, OnPaint, 0);
//#else
//DEFINE_ELEMENT_PROC(WM_PAINT, OnPaint);
//#endif
//DEFINE_ELEMENT_PROC_RETURN(WM_LBUTTONDOWN, OnLButtonDown, 0);
//DEFINE_ELEMENT_PROC_RETURN(WM_LBUTTONUP, OnLButtonUp, 0);
//DEFINE_ELEMENT_PROC_RETURN(WM_MOUSEMOVE, OnMouseMove, 0);
//DEFINE_ELEMENT_PROC_RETURN(WM_ERASEBKGND, RedrawBkground, 0);
//DEFINE_ELEMENT_PROC_RETURN(WM_SIZE, OnSize, 0);
//END_ELEMENT_PROC(BaseClass::ElementProc(ELEMENT_ITEMS))
//
//CMainWindow::CMainWindow() : BaseClass()
//{
//	bInPaint = false;
//
//	int swide, stall, width = 1200, tall = 1000;
//	GetScreenSize(&swide, &stall);
//	MakeWindow("CMainWindow", "Title", DEF_FLAGS_WINDOW, (swide - width) / 2, (stall - tall) / 2, width, tall, false/*, 255, 0, 0*/);
//	WindowLoop();
//}
//
//void CMainWindow::OnLButtonClick(ELEMENT_PROC_ITEMS)
//{
//	POINT pt = GetCursorPosition();
//	int id = ShowMessageBox(MB_ICONERROR | MB_OKCANCEL, "Got Point", "%d", cb2->IsChecked());
//	if (id == IDCANCEL)
//		OnClose(ELEMENT_ITEMS);
//}
//
//void CMainWindow::OnLButtonDown(ELEMENT_PROC_ITEMS)
//{
//	bInPaint = true;
//	pt = GetCursorPosition();
//	pt = ClientFromScreen(pt);
//}
//
//void CMainWindow::OnLButtonUp(ELEMENT_PROC_ITEMS)
//{
//	bInPaint = false;
//}
//
//void CMainWindow::OnMouseMove(ELEMENT_PROC_ITEMS)
//{
//	if (!bInPaint)
//		return;
//
//
//	Redraw(false);
//}
//
//void CMainWindow::RedrawBkground(ELEMENT_PROC_ITEMS)
//{
//	PAINT_BACKGROUND_START(hwnd, 0, 100, 0);
//	PAINT_SET_CLIENT_RECT(hwnd);
//	PAINT_FILL(hwnd);
//	PAINT_BACKGROUND_END(hwnd)
//}
//
//void CMainWindow::OnRButtonDblClick(ELEMENT_PROC_ITEMS)
//{
//	POINT pt = GetCursorPosition();
//	pt = ClientFromScreen(pt);
//	//file->EnableMenuItem(!file->IsMenuEnabled(0, MF_BYPOSITION), false, MF_BYPOSITION, 0);
//	/*if (gui::GetElementFocus() == this)
//		ShowMessageBox(0, 0, "");*/
//}
//
//void CMainWindow::OnPaint(ELEMENT_PROC_ITEMS)
//{
//	if (!bInPaint)
//		return;
//
//	PAINT_START(hwnd, 255, 100, 0);
//	POINT pt2 = GetCursorPosition();
//	pt2 = ClientFromScreen(pt2);
//	PAINT_DRAW_LINE(hwnd, pt.x, pt.y, pt2.x, pt2.y, 255, 100, 0, 20);
//	PAINT_END(hwnd);
//}
//
//void CMainWindow::OnCreate(ELEMENT_PROC_ITEMS)
//{
//	//SetSizable(false);
//
//	//this use to be a context menu and this function used to be a right click function
//	cmenu = new Menu();
//
//	file = cmenu->CreateNewMenu();
//	file->AddItem("Hello World", MF_STRING, 1000);
//	file->AddItem("Hello World2", MF_STRING , 1001);
//	file->AddVerticleSeperator("Hello World2", 1002);
//	file->AddItem("Hello World", 0, 1000);
//
//	lb2 = new LoadingBar(this, 0, 100, 0);
//	lb2->SetBounds(0, 0, 200, 20);
//	lb2->SetVisible(false);
//
//	cmenu->AddMenu(file, "File", MF_POPUP);
//
//	SetThisMenu(cmenu);
//
//	HICON icon = LoadIconFromFile("icon1.ico", 16, 16);
//
//	//cb = new ComboBox(this, 0);
//	//cb->SetBounds(450, 100, 300, 200);
//	//cb->SetElementHeight(100);
//	//cb->AddItem("Hello World");
//	//cb->AddItem("Hello Bob");
//	//cb->SelectItem(0);
//
//	//cb2 = new CheckButton(this, "Press Me", 0);
//	//cb2->SetBounds(450, 250, 200, 25);
//
//	//te = new TextEntry(this, "Hello World", 0);
//	//te->SetBounds(450, 500, 200, 20);
//
//
//	//HFONT TestFont = CreateFontFromFile(
//	//	"font.ttf",
//	//	"Cabal",
//	//	30, 0,
//	//	0, 0,
//	//	FW_NORMAL,
//	//	FALSE,
//	//	FALSE,
//	//	FALSE,
//	//	DEFAULT_CHARSET,
//	//	OUT_DEFAULT_PRECIS,
//	//	CLIP_DEFAULT_PRECIS,
//	//	DEFAULT_QUALITY,
//	//	DEFAULT_PITCH | FF_SWISS
//	//);
//	//Label* test = new Label(this, "Hello World", 0);
//	//test->SetBounds(500, 400, 200, 40);
//	//test->SetFont(TestFont);
//
//	////test->SetFont(TestFont);
//	//RichEdit::Init();
//
//	//RichEdit* re = new RichEdit(this, "", 0);
//	//re->SetBounds(10, 10, 300, 300);
//
//	//int len = re->GetTextLength();
//	//re->SetFont(TestFont);
//	//re->SetTextColor(RGB(0, 0, 255));
//
//	//re->AppendText("Hello World\r\n");
//	//re->SetFont(re->GetDefaultFont());
//	//re->SetTextColor(RGB(255, 100, 0));
//	//re->SetTextBackgroundColor(RGB(0, 255, 0));
//	//re->AppendText("Hello World\r\n");
//
//	//re->SetTextSize(30);
//	//re->AppendText("How To Use:\r\n");
//	//re->SetTextSize(14);
//	//re->AppendText("Go To: moddb.com/mods/half-life-2-alone-mod and play the mod\r\nplease");
//	//re->SetBackgroundColor(RGB(255, 100, 0));
//	//DestroyFontMadeFromFile(TestFont, "font.ttf");
//
//	//lb = new ListBox(this, 1010);
//	//lb->SetBounds(700, 500, 200, 300);
//	//lb->AddItem("Test");
//	//lb->AddItem("Hello World");
//	//lb->SetSelectedIndex(lb->GetIndexFromString("Hello World"));
//
//	//lb->SetFocusToThis();
//
//	//HTREEITEM root = nullptr;
//	//TreeView* tv = new TreeView(this, "Hello World", 0,&root);
//
////	ImageList* il = new ImageList(16, 16);
////	il->AddIcon(icon);
////	
//	//tv->SetImageList(il);
//	
//	//tv->SetTreeviewBgColor(RGB(200, 200, 255));
//	//if (root)
//	//	tv->AddNode("Hello Wor2ld", root, TVI_LAST, 1, 0, 0);
//	
//	//tv->SetBounds(10, 600, 200, 400);
//	
////	ListView* listView = new ListView(this, 0);
////	listView->SetBounds(100, 100, 700, 200);
////	listView->SetImageList(il);
////	
////	listView->AddColumn("ID", 50);
////	listView->AddColumn("Name", 150);
////	listView->AddColumn("Description", 300);
////	
////	listView->AddItem("sd", 0, 0);
////	listView->AddItem("Seb", 0, 1);
////	listView->AddItem("Name Is Seb (:", 0, 2);
////	
////	listView->AddItem("2", 1, 0);
////	listView->AddItem("Bob", 1, 1);
////	listView->AddItem("Name Is Bob", 1, 2);
////
////sb = new StatusBar(this, "Status: Ok", 0);
//	//TabController* tc = new TabController(this, 0);
//	//tc->SetBounds(50, 50, 800, 600);
//	//tc->AddTab("HelloWorld", 0);
//	//tc->AddTab("HelloWorlds", 1);
//
//	SYSTEMTIME minDate = { 2020, 1, 0, 1 }, maxDate = { 2030, 12, 0, 31 };
//
//	dp = new DatePicker(this, 0);
//	dp->SetBounds(200, 200, 300, 25);
//	dp->SetRange(&maxDate, &minDate);
//
//}
//
//int CMainWindow::OnCommand(int id, int lp)
//{	
//	//ShowMessageBox(0, 0, "%d", lb->GetSelectedIndex());
//	if (id == 1000)
//	{
//		CTestSubDialog* dlg = new CTestSubDialog();
//		dlg->MakeDialog(this);
//		dlg->SetText("Hello World");
//	}
//	if (id == 1002)
//	{
//		SYSTEMTIME time;
//		dp->GetDate(&time);
//		ShowMessageBox(0, 0, "%d:%d:%d", time.wDay, time.wMonth, time.wYear);
//	}
//	else if (id == 1001)
//	{
//		FileDialog* fd = new FileDialog(this, 100, FileDialogType::FILE_OPEN_SHELL);
//		fd->Show("Title Test", 0, "All Files\'*.*\0", nullptr, nullptr);
//	}
//
//	return 0;
//}
//
//void CMainWindow::OnSize(ELEMENT_PROC_ITEMS)
//{	
//	if (sb)
//		sb->OnSize(lp);
//}
//
//void CMainWindow::OnFileSelected(int id, const char* file, FileDialogType type)
//{
//	ShowMessageBox(0, 0, "Id: %d, File %s, Type %d", id, file, (int)type);
//}
//
//ENTRY_POINT()
//{
//	CMainWindow* window = new CMainWindow();
//}

//new devtest
#include "WaddelzGui.h"
#include "ToolBar.h"

class CPropertyPage1 : public gui::PropertyPage
{
public:
	CPropertyPage1(gui::Element* parent) : gui::PropertyPage(parent)
	{
		gui::Button* button = new gui::Button(parent, "Test1", 1002);
		button->SetBounds(200, 200, 200, 20);
		AddElement(button);

		gui::ToolTip* tt = new gui::ToolTip(parent);
		tt->AddTool(button, "This Is A Test\nTool Tip");
		tt->SetDelayTime(100);
		tt->Activate(true);
	}
};

class CPropertyPage2 : public gui::PropertyPage
{
public:
	CPropertyPage2(gui::Element* parent) : gui::PropertyPage(parent)
	{
		gui::Button* button2 = new gui::Button(parent, "Test2", 1001);
		button2->SetBounds(100, 400, 100, 25);
		AddElement(button2);
	}
};

class CMainWindow : public gui::Window
{
	DECLARE_ELEMENT_NOSUBPROC(CMainWindow, gui::Window)

	CMainWindow() : BaseClass()
	{
		m_TabController = nullptr;
		m_iPrevSelected = 0;

		MakeWindow("CMainWindow", "Test Window");
		WindowLoop();
	}

	void OnCreate(ELEMENT_PROC_ITEMS)
	{
		gui::ImageList* il = new gui::ImageList(16, 16);
		il->AddIcon(LoadIcon(nullptr, IDI_APPLICATION));
		il->AddIcon(LoadIcon(nullptr, IDI_WARNING));

		gui::ToolBar* tb = new gui::ToolBar(this, il);
		tb->AddButton(1003);

		//m_TabController = new gui::TabController(this, 1000);
		//m_TabController->SetBounds(0, 0, GetWide(), GetTall() - 58);
		//m_TabController->AddTab("Test Tab 1", 0);
		//m_TabController->AddTab("Test Tab 2", 1);
		//m_TabController->SelectTab(0);

		//m_StatusBar = new gui::StatusBar(this, "Size = Normal");

		//m_Menu = new gui::Menu();

		//gui::Menu* FileMenu = new gui::Menu();
		//FileMenu->AddItem("Open File", MF_STRING, 1001);

		//m_Menu->AddMenu(FileMenu, "File", MF_POPUP);

		//CPropertyPage1* pp1 = new CPropertyPage1(this);
		//CPropertyPage2* pp2 = new CPropertyPage2(this);

		//m_PPageManager = new gui::PropertyPageManager();
		//m_PPageManager->AddPage(pp1);
		//m_PPageManager->AddPage(pp2);
		//m_PPageManager->SelectPage(0);

		//gui::ScrollWheel* sw = new gui::ScrollWheel(this, 0);
		//sw->SetBounds(100, 100, 20, 200);

		//SetThisMenu(m_Menu);
	}

	void OnSize(ELEMENT_PROC_ITEMS)
	{
		if (m_TabController)
			m_TabController->SetBounds(0, 0, LOWORD(lp), HIWORD(lp) - 20);

		if (m_StatusBar)
		{
			if (wp == SIZE_MAXIMIZED)
				m_StatusBar->SetText("Size = Maximized");
			else
				m_StatusBar->SetText("Size = Normal");

			m_StatusBar->OnSize(lp);
		}
	}

	void OnNotify(ELEMENT_PROC_ITEMS)
	{
		GUI_NOTIFICATION_GET()
		//if (noticode->hwndFrom == m_TabController->GetHandle() && noticode->code == TCN_SELCHANGE)
		//{
		//	int currselected = m_TabController->GetCurrentSelected();
		//	if (m_iPrevSelected == currselected)
		//		return;

		//	m_PPageManager->SelectPage(currselected);
		//	m_iPrevSelected = currselected;
		//}
	}

	int OnCommand(int id)
	{
		if (id == 1001)
		{
			gui::FileDialog dialog(this, 0, gui::FileDialogType::FILE_OPEN_DIALOG);
			dialog.Show("Choose A File", DEF_FLAGS_OPENFILE);
		}
		else if (id == 1002)
		{
			gui::ColorPicker cp;
			if (cp.ShowDialog(DEF_FLAGS_COLORPICKER))
			{
				ShowMessageBox(0, "Got Color", "Got Color %d %d %d", GetRValue(cp.GetColor()), GetGValue(cp.GetColor()), GetBValue(cp.GetColor()));
			}
		}
		else if (id == 1003)
		{
			bool bIsChecked = m_ToolBar->IsButtonChecked(id);
			m_ToolBar->SetButtonChecked(id, !bIsChecked);
		}

		return 0;
	}

	void OnFileSelected(int id, const char* filename, gui::FileDialogType type) override
	{
		if (id == 0)
		{
			FILE* file = fopen(filename, "wb");
			if (!file)
			{
				ShowMessageBox(MB_OK | MB_ICONERROR, "Error", "Failed To Open File %s", filename);
			}
			else
			{
				ShowMessageBox(MB_OK | MB_ICONINFORMATION, "Sucsess", "Opened File %s", filename);
				fclose(file);
			}

		}
	}

	void OnRightClick(ELEMENT_PROC_ITEMS)
	{
		if (m_TabController->GetTabCount() % 2 == 1)
		{
			m_TabController->AddTab("TabController 1", m_TabController->GetTabCount() + 1);
			CPropertyPage1* pp = new CPropertyPage1(this);
			m_PPageManager->AddPage(pp);
			m_TabController->SelectTab(m_TabController->GetTabCount() - 1);
		}
		else
		{
			m_TabController->AddTab("TabController 2", m_TabController->GetTabCount() + 1);
			CPropertyPage2* pp = new CPropertyPage2(this);
			m_PPageManager->AddPage(pp);
			m_TabController->SelectTab(m_TabController->GetTabCount() - 1);
		}

	}

	DECLARE_ELEMENT_PROC()

private:
	int m_iPrevSelected;

	gui::PropertyPageManager* m_PPageManager;
	gui::TabController* m_TabController;
	gui::StatusBar* m_StatusBar;
	gui::Menu* m_Menu;
};

START_ELEMENT_PROC(CMainWindow)
DEFINE_ELEMENT_PROC(WM_CREATE, OnCreate)
DEFINE_ELEMENT_PROC(WM_SIZE, OnSize)
DEFINE_ELEMENT_PROC_RETURN(WM_COMMAND, NO_PROC, OnCommand(LOWORD(wp)))
DEFINE_ELEMENT_PROC(WM_NOTIFY, OnNotify)
DEFINE_ELEMENT_PROC(WM_CLOSE, OnClose)
DEFINE_ELEMENT_PROC(WM_RBUTTONDOWN, OnRightClick)
END_ELEMENT_PROC(BaseClass::ElementProc(ELEMENT_ITEMS));

MAKE_CRASH_HANDLER(CrashHandler)
{
	gui::Element::EmptyMessageBox(0, "Hello World", "What");
	return 0;
}

ENTRY_POINT()
{
	SET_CRASH_HANDLER(CrashHandler);
	CMainWindow g_Window;
}