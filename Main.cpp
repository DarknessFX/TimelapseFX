#pragma region Base references
#include <windows.h>
#include <string>
#include "gcroot.h"
#include "dwmapi.h"
#include <msclr\marshal_cppstd.h>
#include "MainForm.h"
#include "TimelapseFX_Helper.h"

using namespace System::Collections::Generic;
using namespace System::Diagnostics;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::IO;
using namespace System::Resources;
using namespace System::Reflection;
using namespace System::Threading;
using namespace System::Threading::Tasks;
using namespace System::Timers;
using namespace System::Windows::Forms;
using namespace TimelapseFX;
#pragma endregion


std::string VERSION = "1.2";


#pragma region Helpers functions
/// 
/// Helpers functions
/// 
String^ Append(String^ str0, String^ str1) { return str0->Insert(str0->Length, str1); }
String^ ToNString(std::string str0) { return gcnew String(str0.c_str()); }
String^ ToNString(std::wstring str0) { return gcnew String(str0.c_str()); }
std::string ToCString(String^ str0) { msclr::interop::marshal_context m_context; return m_context.marshal_as<std::string>(str0); ; }
double ToSeconds(double Seconds) { return Seconds * 1000; };
double ToMinutes(double Minutes) { return Minutes * 60 * 1000; };
static void CaptureTask( System::Object^ sender, Timers::ElapsedEventArgs^ e );
void BlinkNotify();
gcroot<ResourceManager^> _oRM;
ResourceManager^ GetRM () { 
    return (static_cast<ResourceManager^>(_oRM) == nullptr) ? 
        gcnew ResourceManager( "TimelapseFX.Main", Assembly::GetExecutingAssembly() ) : 
        _oRM;
}
Icon^  GetIcon ( String^ ico ) { return ( cli::safe_cast< Icon^  >( GetRM()->GetObject( ico ) ) ); }
Image^ GetImage( String^ img ) { return ( cli::safe_cast< Image^ >( GetRM()->GetObject( img ) ) ); }
String^ GetDisplayName(String^ DeviceName) {
    DISPLAY_DEVICE dd; memset(&dd, 0, sizeof(DISPLAY_DEVICE)); dd.cb = sizeof(dd); int i = 0;
    while(EnumDisplayDevices(NULL, i, &dd, 0)) {
        if (ToNString(dd.DeviceName) == DeviceName) { return ToNString(dd.DeviceString); }
        i++;
    }
    return DeviceName;
}
array<String^>^ Split(String^ str0, String^ delim = " - ") {
    array<String^>^ sRes = gcnew array< String^ >(5); int iArr = 0;
    while (str0->Length > 0)
    {
        int iPos = str0->IndexOf(delim);
        if (iPos != -1)
        { sRes[iArr] = str0->Substring(0 , iPos); str0 = str0->Substring(iPos + delim->Length); }
        else
        { sRes[iArr] = str0; sRes[4] = str0->Substring(str0->IndexOf(":") + 1, str0->IndexOf(")") - (str0->IndexOf(":") + 1));  str0 = ""; }
        iArr++;
    }
    return sRes;
}
String^ ToTimecode(float iFR) {
    TimeSpan^ oTS = gcnew TimeSpan((int)(iFR * 10000));
    String^ sRes = "";
    sRes = Append(sRes, oTS->Hours.ToString("D2"));
    sRes = Append(sRes, ":");
    sRes = Append(sRes, oTS->Minutes.ToString("D2"));
    sRes = Append(sRes, ":");
    sRes = Append(sRes, oTS->Seconds.ToString("D2"));
    sRes = Append(sRes, ",");
    sRes = Append(sRes, oTS->Milliseconds.ToString("D3"));
    return sRes;
}
String^ ToSRTTimecode(int iFC, float iFR) {
    String^ sRes = ToTimecode((iFC - 1) * iFR);
    sRes = Append(sRes, " --> ");
    sRes = Append(sRes, ToTimecode(iFC * iFR - 1));
    return sRes;
}
String^ GetWindowTitle(HWND hWnd) { TCHAR szText[256]; GetWindowText(hWnd, szText, 256); return ToNString(szText); }
bool IsAltTabWindow(HWND hWnd) {
    if (hWnd == GetShellWindow()) { return false; }
    if (!IsWindowVisible(hWnd)) { return false; }
    if (GetAncestor(hWnd, GA_ROOT) != hWnd) { return false; }
    if (GetWindowTitle(hWnd) == "") { return false; }
    LONG style = GetWindowLong(hWnd, GWL_STYLE);
    if (!((style & WS_DISABLED) != WS_DISABLED)) { return false; }
    DWORD cloaked = FALSE;
    HRESULT hrTemp = DwmGetWindowAttribute(hWnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked));
    if (SUCCEEDED(hrTemp) && cloaked == DWM_CLOAKED_SHELL) { return false; }
    return true;
}
gcroot<List<Int64>^> _oWindowsList;
BOOL CALLBACK OnEnumWindow(HWND hwnd, LPARAM lParam) { if ( IsAltTabWindow(hwnd) ) { _oWindowsList->Add((Int64)hwnd); } return true; }
List<Int64>^ EnumerateWindows() {
    _oWindowsList = (static_cast<List<Int64>^>(_oWindowsList) == nullptr) ? gcnew List<Int64>() : _oWindowsList;
    _oWindowsList->Clear();
    EnumWindows(OnEnumWindow, 0);
    return _oWindowsList;
}
#pragma endregion


#pragma region Main Application Functions And Settings
/// 
/// Main Application Functions And Settings
/// 
struct MainApplication
{
    MainApplication(void) {}
    ~MainApplication(void) {}


private:
    std::string _OutputFolder = ToCString(Append(Application::StartupPath, "\\Screenshots\\"));
    gcroot<NotifyIcon^> _oNtfSystray;
    gcroot<Timers::Timer^> _oLapseTimer;
    Timers::Timer^ _GetTimer()
    {
        Timers::Timer^ oLapseTimer = (static_cast<Timers::Timer^>(_oLapseTimer) == nullptr) ? 
            gcnew Timers::Timer(GetPeriod()) : 
            _oLapseTimer;
        return oLapseTimer;
    }


public:
    HWND        hMainForm               = NULL;

    bool        bIsStarting             = true;
    bool        bIs1stShot              = true;
    bool        bIsExporting            = false;
    bool        bIsPaused               = false;

    int         lapseCaptureMode        = 0;        // Modes: All Displays, Single Display, Application, Region.
    std::string lapseCaptureModeDesc    = "";       // Description of the capture mode.
    std::string lapseCaptureModeApp     = "";       // Application name to capture.
    RECT        lapseCaptureModeRegion  = {0,0,0,0};// Rectangle screen region to capture.
    bool        lapseRemoveTaskbar      = true;     // Remove windows taskbar from screenshot.
    int         lapseDelay              = 60;       // in Seconds, after load the app seconds to wait before 1st screenshot.
    double      lapsePeriod             = 15;       // in Minutes
    bool        lapseNotify             = true;     // Pop-up informing when lapsePeriod is about to hit.
    int         lapseNotifyRush         = 10;       // in Seconds, how long before lapsePeriod should the notify happen.
    bool        lapseCountdown          = true;     // Pop-up counting down when lapsePeriod is about to hit.
    int         lapseCountdownRush      = 3;        // in Seconds, how long before lapsePeriod should the count down happen.
    int         countShoots             = 0;        // Control counter for screenshot filenames.
    float       videoFramerate          = 1.0;      // in Images per Second, how many screenshots per second will display on exported video.
    bool        videoAspectRatio        = false;    // Force aspect ratio to 16:9
    std::string videoFFMpegPath         = "";       // Path to FFMpeg.exe    

    String^ GetVersion() { return ToNString(VERSION); }
    String^ GetOutputFolder() { return ToNString(_OutputFolder); }
    void SetOutputFolder( String^ sPath ) { _OutputFolder = _OutputFolder = ToCString(sPath); }
    NotifyIcon^ GetNotifyIcon() { return _oNtfSystray; }
    void SetNotifyIcon( NotifyIcon^ ntfSystray ) { _oNtfSystray = ntfSystray; }

    String^ GetFFMpegPath() { return ToNString(videoFFMpegPath); }
    void SetFFMpegPath(String^ sPath ) { videoFFMpegPath = ToCString(sPath); }
    String^ GetFFMpegArgs() {
        /// Default FFMpeg arguments
        // -f image2                : input format image2
        // -vcodec png              : input video codec PNG
        // -y                       : Overwrite output
        // -an                      : Disable audio
        // -loglevel quiet          : silent log
        return " -f image2 -vcodec png -y -an -loglevel quiet ";
    }

    Timers::Timer^ GetTimer() { return _GetTimer(); }
    void StopTimer() { _GetTimer()->Stop(); }
    void RestartTimer()  { _GetTimer()->Start(); }
    void CloseTimer()  { _GetTimer()->Close(); }
    double GetPeriod() {
        double dPeriod = 0;
        if ( bIs1stShot ) {
            dPeriod = ToSeconds(mApp.lapseDelay);
        } else {
            dPeriod = ToMinutes(lapsePeriod);
        }
        if ( lapseNotify )      { dPeriod -= ToSeconds(lapseNotifyRush); }
        if ( !lapseNotify && lapseCountdown )   { dPeriod -= ToSeconds(lapseCountdownRush); }
        return dPeriod;
    }
    Timers::Timer^ StartTimer() {
        Timers::Timer^ oLapseTimer = _GetTimer();
        oLapseTimer->Stop();
        oLapseTimer->Enabled = false;
        oLapseTimer->BeginInit();
        oLapseTimer->Interval = GetPeriod();
        oLapseTimer->AutoReset = true;
        if ( mApp.bIs1stShot ) {
            oLapseTimer->AutoReset = false;
            mApp.bIs1stShot = false;
        }
        oLapseTimer->Elapsed += gcnew ElapsedEventHandler(CaptureTask);
        oLapseTimer->EndInit();
        oLapseTimer->Enabled = true;
        oLapseTimer->Start();
        return oLapseTimer;
    }

    Drawing::Rectangle^ GetCaptureSize() {
        if (ToNString(lapseCaptureModeDesc) == "All Displays") {
            if ( !lapseRemoveTaskbar ) { return SystemInformation::VirtualScreen; }
            Drawing::Rectangle^ oCaptureSize = SystemInformation::VirtualScreen;
            if ( !lapseRemoveTaskbar ) { return oCaptureSize; }
            oCaptureSize->Height -= oCaptureSize->Height - SystemInformation::WorkingArea.Height;
            return oCaptureSize;
        }
        if (ToNString(lapseCaptureModeDesc)->Substring(0, 7) == "Display") {
            Screen^ oScreen = Screen::AllScreens[lapseCaptureMode - 1]; //int::Parse(ToNString(lapseCaptureModeDesc)->Substring(8, 1)) - 1
            Drawing::Rectangle^ oCaptureSize = oScreen->Bounds;
            if ( !lapseRemoveTaskbar ) { return oCaptureSize; }
            oCaptureSize->Height -= oCaptureSize->Height - oScreen->WorkingArea.Height;
            return oCaptureSize;
        }
        if (ToNString(lapseCaptureModeDesc) == "Application") { return SystemInformation::VirtualScreen; }
        if (ToNString(lapseCaptureModeDesc) == "Region") { return SystemInformation::VirtualScreen; }

        // If nothing is recognized, return full screen region
        return SystemInformation::VirtualScreen;
    }

    void LoadCaptureModes(Windows::Forms::ComboBox^ cmbCM)
    {
        cmbCM->Items->Clear();
        if (Screen::AllScreens->Length > 0) { cmbCM->Items->Add("All Displays"); }
        for (int i = 0; i < Screen::AllScreens->Length; i++) {
            String^ sDisplay = "Display ";
            sDisplay = Append(sDisplay, (i + 1).ToString());
            sDisplay = Append(sDisplay, " - ");
            sDisplay = Append(sDisplay, GetDisplayName(Screen::AllScreens[i]->DeviceName));
            cmbCM->Items->Add(sDisplay);
        }
        cmbCM->Items->Add("Application");
        //TODO: Capture By Region cmbCM->Items->Add("Region");
        //TODO: Capture By Application Region cmbCM->Items->Add("Application Region");
        cmbCM->SelectedIndex = lapseCaptureMode;
        lapseCaptureModeDesc = ToCString(cmbCM->SelectedItem->ToString());
    }

    void CheckIni()
    {
        // If is the 1st time running TimelapseFX, create an default .INI 
        if (!File::Exists(Append(Application::StartupPath, "\\TimelapseFX.ini"))) {
            FileStream^ oFS = gcnew FileStream( Append(Application::StartupPath, "\\TimelapseFX.ini"), FileMode::CreateNew);
            StreamWriter^ oSW = gcnew StreamWriter(oFS);
            oSW->WriteLine(Append("txtScreenshots=", GetOutputFolder()));
            oSW->WriteLine("cmbCaptureMode=0");
            oSW->WriteLine("cmbCaptureModeDesc=");
            oSW->WriteLine("chkCaptureModeApp=");
            oSW->WriteLine("chkCaptureModeAppDesc=");
            oSW->WriteLine("txtCaptureRegionX=0");
            oSW->WriteLine("txtCaptureRegionY=0");
            oSW->WriteLine("txtCaptureRegionWidth=0");
            oSW->WriteLine("txtCaptureRegionHeight=0");
            oSW->WriteLine("chkTimelapseTaskbar=true");
            oSW->WriteLine("txtTimelapseDelay=60");
            oSW->WriteLine("txtTimelapsePeriod=15");
            oSW->WriteLine("chkTimelapseNotify=true");
            oSW->WriteLine("txtTimelapseNotify=10");
            oSW->WriteLine("chkTimelapseCountdown=true");
            oSW->WriteLine("txtTimelapseCountdown=3");
            oSW->WriteLine("txtFFMpeg=C:\\Program Files\\FFMpeg\\bin\\FFMpeg.exe");
            oSW->WriteLine("txtExpFramerate=1");
            oSW->WriteLine("chkExpAspect=false");
            oSW->Close();
            oFS->Close();
            if (!Directory::Exists(GetOutputFolder())) { Directory::CreateDirectory(GetOutputFolder()); }
        }
    }

    bool IgnoreApplications ( Process^ oProc) 
    {
        if ( oProc->ProcessName->ToLower()->Contains("svchost") ) { return true; } 
        if ( oProc->ProcessName->ToLower()->Contains("scriptedsandbox64") )  { return true; }
        //if ( oProc->ProcessName->ToLower()->Contains("applicationframehost") )  { return true; }
        if ( oProc->ProcessName->ToLower()->Contains("textinputhost") )  { return true; }

        ///DEBUG:
        /*
        String^ sProcess = "";
        sProcess = Append(sProcess, oProc->ProcessName->ToString());
        sProcess = Append(sProcess, " - ");
        sProcess = Append(sProcess, oProc->MainWindowTitle->ToString());
        sProcess = Append(sProcess, " - (ID:");
        sProcess = Append(sProcess, oProc->Id.ToString());
        sProcess = Append(sProcess, ") - ");
        try {
            sProcess = Append(sProcess, oProc->MainModule->ModuleName);
            sProcess = Append(sProcess, " - ");
            sProcess = Append(sProcess, oProc->MainModule->FileName);
            sProcess = Append(sProcess, " - ");
            sProcess = Append(sProcess, oProc->MainModule->FileVersionInfo->FileDescription);
        } catch (Exception^ e) {
            (void)e;
        }
        OutputDebugStringA(ToCString(Append(sProcess, "\n")).c_str());
        */

        return false;
    }

    bool CompareApplications(String^ chkCMA, String^ lpsCMA)
    {
        array<String^>^ achk = Split(chkCMA);
        array<String^>^ alps = Split(lpsCMA);
        if ( achk[0] == alps[0] && achk[1] == alps[1]) {
            return true;
        } else {
            return false;
        }
    }

    void LoadApplications( Windows::Forms::CheckedListBox^ chkCMA )
    {
        List<String^> oApps = gcnew List<String^>();        
        chkCMA->Enabled = false;
        chkCMA->Items->Clear();
        for each (auto hWnd in EnumerateWindows())
        {
            DWORD processID;
            if ( GetWindowThreadProcessId((HWND)hWnd, &processID) ) 
            {
                Process^ oProc = Process::GetProcessById(processID);
                if ( IgnoreApplications( oProc ) ) { continue; } 
                String^ sProcess = "";
                try {
                    sProcess = Append(sProcess, oProc->MainModule->FileVersionInfo->FileDescription);
                } catch (Exception^ e) {
                    sProcess = Append(sProcess, oProc->ProcessName->ToString());
                    (void)e;
                }
                sProcess = Append(sProcess, " - ");
                // *** Replaced by GetWindowTitle function ***
                //sProcess = Append(sProcess, oProc->MainWindowTitle->ToString()->Replace(" - ", ""));
                sProcess = Append(sProcess, GetWindowTitle((HWND)hWnd)->Replace(" - ", ""));
                if ( !oApps.Contains(sProcess) ) 
                {
                    oApps.Add(sProcess);
                    sProcess = Append(sProcess, " - (ID:");
                    sProcess = Append(sProcess, hWnd.ToString());
                    // *** Replaced by Window Handle function ***
                    //sProcess = Append(sProcess, oProc->Id.ToString());
                    sProcess = Append(sProcess, ")");
                    chkCMA->Items->Add(sProcess, CompareApplications(sProcess, ToNString(lapseCaptureModeApp)));
                }
            }
        }
        oApps.Clear();
        chkCMA->Enabled = true;
    }

} mApp;
#pragma endregion


#pragma region WinAPI EXE Entry Point
/// 
/// WinAPI EXE Entry Point
/// 
[STAThreadAttribute]
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, INT nCmdShow)
{
    // Pre-Initialize Main Settings
    mApp.CheckIni();

    // Load MainForm in systray
    Application::Run(gcnew MainForm());

    // Closing
    mApp.CloseTimer();
    return 0;
}
#pragma endregion 


#pragma region Capture Screenshot Functions
/// 
/// Capture Screenshot Functions
/// 
static void CaptureScreenshot()
{
    if ( mApp.bIsPaused ) { return; }

    BlinkNotify();

    // Don't capture if: screensaver is active, screen is sleeping, capture is paused.
    BOOL bIsScreensaverRunning = false;
    SystemParametersInfo( SPI_GETSCREENSAVERRUNNING, 0, &bIsScreensaverRunning, 0 ); if ( bIsScreensaverRunning )  { return; }
    SystemParametersInfo( SPI_GETPOWEROFFACTIVE, 0, &bIsScreensaverRunning, 0 );     if ( bIsScreensaverRunning )  { return; }

    // Wait until finish exporting.
    while (mApp.bIsExporting) { Application::DoEvents(); Sleep(250); }

    String^ oFileName = Append(mApp.GetOutputFolder(), 
                        Append(mApp.countShoots.ToString("D5"), "_Screenshot.png"));

    Icon^ ico_cam = GetIcon("ico_cam");
    mApp.GetNotifyIcon()->Icon = ico_cam;
    if (ToNString(mApp.lapseCaptureModeDesc) != "Application" && 
        ToNString(mApp.lapseCaptureModeDesc) != "Region" ) 
    {
        Drawing::Rectangle^ oCaptureSize = mApp.GetCaptureSize();
        Bitmap^ oBmp = gcnew Bitmap( oCaptureSize->Width, oCaptureSize->Height, PixelFormat::Format32bppArgb );
        Graphics^ oGfx = Graphics::FromImage(oBmp);
        oGfx->CopyFromScreen( oCaptureSize->X, oCaptureSize->Y, 0, 0, oCaptureSize->Size, CopyPixelOperation::SourceCopy);
        oBmp->Save(oFileName, ImageFormat::Png);
    }
    else if (ToNString(mApp.lapseCaptureModeDesc) == "Application")
    {
        //Process^ oProc = Process::GetProcessById(int::Parse(Split(ToNString(mApp.lapseCaptureModeApp))[4]));
        HWND hWnd = (HWND)Int64::Parse(Split(ToNString(mApp.lapseCaptureModeApp))[4]);
        if (GetWindowLong(hWnd, GWL_STYLE) < 50000000) 
        {
            // Common Windows32, use BitBlt capture
            RECT wRect = {0,0,0,0}; RECT wCltRect = {0,0,0,0};
            GetWindowRect(hWnd, &wRect);
            MapWindowPoints(HWND_DESKTOP, GetParent(hWnd), (LPPOINT) &wRect, 2);
            GetClientRect(hWnd, &wCltRect);
            int iBorderX = ((wRect.right - wRect.left) - (wCltRect.right - wCltRect.left)) / 2;
            int iBorderY = ((wRect.bottom - wRect.top) - (wCltRect.bottom - wCltRect.top)) - iBorderX;
            HDC hSrcDC = GetWindowDC(hWnd);
            HDC hCptDC = CreateCompatibleDC(hSrcDC);
            HBITMAP hBitmap = CreateCompatibleBitmap(hSrcDC, wCltRect.right - wCltRect.left, wCltRect.bottom - wCltRect.top);
            SelectObject(hCptDC, hBitmap);
            BitBlt(hCptDC, 0, 0, wRect.right - wRect.left, wRect.bottom - wRect.top, 
                   hSrcDC, iBorderX, iBorderY, SRCCOPY|CAPTUREBLT);

            Bitmap^ oBmp = Bitmap::FromHbitmap((IntPtr)hBitmap);
            oBmp->Save(oFileName, ImageFormat::Png);
            ReleaseDC(hWnd, hSrcDC);
            DeleteDC(hCptDC);
            DeleteObject(hBitmap);
        }
        else
        {
            // Custom render (DirectX/WinUI/Qt/Other), use DLL to capture.
            String^ oFileBmp = oFileName->Replace("png","bmp");
            CaptureFromDLL(hWnd, ToCString(oFileBmp));
            Application::DoEvents();
            bool bCopyDone = false;
            while (!bCopyDone)
            {
                try {
                    if (File::Exists(oFileBmp)) 
                    {
                        Bitmap^ oBmp = gcnew Bitmap(oFileBmp);
                        oBmp->Save(oFileName, ImageFormat::Png);
                        Application::DoEvents();
                        oBmp->~Bitmap();
                        File::Delete(oFileBmp);
                        bCopyDone = true;
                    }
                    Application::DoEvents();
                } catch (Exception^ e) {
                    (void)e;
                    bCopyDone = false;
                    Sleep(1000);
                    Application::DoEvents();
                }
            }
        }
    }

    if ( mApp.bIs1stShot ) { mApp.StartTimer(); }
    mApp.countShoots++;

    //Force a garbage collection to keep low memory profile
    GC::Collect(0, GCCollectionMode::Default, false);
    mApp.GetNotifyIcon()->Icon = GetIcon("ico_app");
}

static void CaptureTask( System::Object^ sender, Timers::ElapsedEventArgs^ e )
{
    CaptureScreenshot();
}

void BlinkLoop(double dSeconds, String^ icon1, String^ icon2, double OffsetSeconds = 0)
{
    NotifyIcon^ ntfSystray = mApp.GetNotifyIcon();
    Icon^ ic1 = GetIcon(icon1); Icon^ ic2 = GetIcon(icon2);
    int iStep = 250; bool bFlip = false;
    dSeconds -= OffsetSeconds;
    while (dSeconds > 0) {
        if (bFlip) { ntfSystray->Icon = ic1; } else { ntfSystray->Icon = ic2; }
        Application::DoEvents(); bFlip = !bFlip;
        Sleep(iStep); dSeconds -= iStep;
        ntfSystray->Text = Append(((dSeconds + OffsetSeconds) / 1000).ToString(), " seconds to screenshot.");
        if ( mApp.bIsPaused ) { return; }
    }
}

void BlinkNotify()
{
    if ( mApp.lapseNotify )    { BlinkLoop( ToSeconds(mApp.lapseNotifyRush), "ico_alr", "ico_alt", ToSeconds(mApp.lapseCountdownRush)); }
    if ( mApp.lapseCountdown ) { BlinkLoop( ToSeconds(mApp.lapseCountdownRush), "ico_alr", "ico_wrn"); }
    NotifyIcon^ ntfSystray = mApp.GetNotifyIcon();
    ntfSystray->Text = "TimelapseFX - Click to capture screenshot.";
    ntfSystray->Icon = GetIcon("ico_app");
}
#pragma endregion


#pragma region Form, Systray and Menu Events
/// 
/// Form, Systray and Menu Events
/// 
void MainForm::MainForm_Load ( System::Object^ sender, System::EventArgs^ e )
{
    // Save global references
    mApp.hMainForm = (HWND)this->Handle.ToInt64();
    mApp.SetNotifyIcon(ntfSystray);

    // Load form icons and menu images from custom Main.RESX
    // to avoid FormDesigner mishaps and duplications
    mnuOpenFolder->Image  = GetImage("img_fld");
    mnuReorder->Image     = GetImage("img_ord");
    mnuExp->Image         = GetImage("img_exp");
    mnuCaption->Image     = GetImage("img_cpt");
    mnuPause->Image       = GetImage("img_pau");
    mnuSettings->Image    = GetImage("img_set");
    mnuAbout->Image       = GetImage("img_abt");
    mnuQuit->Image        = GetImage("img_quit");

    mnuExpOrigMP4->Image  = GetImage("img_mp4");
    mnuExpOrigAVI->Image  = GetImage("img_avi");
    mnuExpOrigGIF->Image  = GetImage("img_gif");
    mnuExp480MP4->Image   = GetImage("img_mp4");
    mnuExp480AVI->Image   = GetImage("img_avi");
    mnuExp480GIF->Image   = GetImage("img_gif");
    mnuExp720MP4->Image   = GetImage("img_mp4");
    mnuExp720AVI->Image   = GetImage("img_avi");
    mnuExp720GIF->Image   = GetImage("img_gif");
    mnuExp1080MP4->Image  = GetImage("img_mp4");
    mnuExp1080AVI->Image  = GetImage("img_avi");
    mnuExp1080GIF->Image  = GetImage("img_gif");
    mnuExp2160MP4->Image  = GetImage("img_mp4");
    mnuExp2160AVI->Image  = GetImage("img_avi");
    mnuExp2160GIF->Image  = GetImage("img_gif");

    btnScreenshots->Image       = GetImage("img_brw");
    btnFFMpegBrowse->Image      = GetImage("img_brw");
    btnFFMpegDownload->Image    = GetImage("img_dwn");

    mnuAbout->Text = Append("About TimelapseFX v", mApp.GetVersion());

    // Turn the Settings form visible offscreen once to avod form size misreadings
    this->Visible = true;
    this->WindowState = FormWindowState::Normal;
    this->Visible = false;

    // Load CaptureModes
    mApp.LoadCaptureModes(cmbCaptureMode);

    // Initialize default Settings
    txtScreenshots->Text = mApp.GetOutputFolder();
    chkCaptureModeApp->Items->Clear();
    chkTimelapseTaskbar->Checked = mApp.lapseRemoveTaskbar;
    txtTimelapsePeriod->Text = mApp.lapsePeriod.ToString();
    chkTimelapseNotify->Checked = mApp.lapseNotify;
    txtTimelapseNotify->Text = mApp.lapseNotifyRush.ToString();
    chkTimelapseCountdown->Checked = mApp.lapseCountdown;
    txtTimelapseCountdown->Text = mApp.lapseCountdownRush.ToString();
    txtFFMpeg->Text = mApp.GetFFMpegPath();
    txtExpFramerate->Text = mApp.videoFramerate.ToString();
    chkExpAspect->Checked = mApp.videoAspectRatio;

    // Load .Ini saved settings
    FileStream^ oFS = gcnew FileStream(Append(Application::StartupPath, "\\TimelapseFX.ini"), FileMode::Open);
    StreamReader^ oSR = gcnew StreamReader(oFS);
    while (!oSR->EndOfStream)
    {
        String^ sLine = oSR->ReadLine();
        String^ sControl = sLine->Substring(0, sLine->IndexOf("="));
        String^ sValue = sLine->Substring(sLine->IndexOf("=") + 1);
        if (sControl == "txtScreenshots") { 
            if (Directory::Exists(sValue))
            {
                txtScreenshots->Text = sValue; 
                mApp.SetOutputFolder(sValue);
                mApp.countShoots = Directory::GetFiles(sValue, "?????_Screenshot.png")->Length;    
            }
        }
        if (sControl == "cmbCaptureMode") { cmbCaptureMode->SelectedIndex = int::Parse(sValue); }
        if ((sControl == "chkCaptureModeApp" || sControl == "chkCaptureModeAppDesc") &&
             sValue != "") { 
            chkCaptureModeApp->Items->Add(sValue, true);
            mApp.lapseCaptureModeApp = ToCString(sValue); 
        }
        if (sControl == "txtCaptureRegionX") { mApp.lapseCaptureModeRegion.left = int::Parse(sValue); }
        if (sControl == "txtCaptureRegionY") { mApp.lapseCaptureModeRegion.top = int::Parse(sValue); }
        if (sControl == "txtCaptureRegionWidth") { mApp.lapseCaptureModeRegion.right = int::Parse(sValue); }
        if (sControl == "txtCaptureRegionHeight") { mApp.lapseCaptureModeRegion.bottom = int::Parse(sValue); }
        if (sControl == "txtTimelapseDelay") { txtTimelapseDelay->Text = sValue; }
        if (sControl == "txtTimelapsePeriod") { txtTimelapsePeriod->Text = sValue; }
        if (sControl == "chkTimelapseNotify") { chkTimelapseNotify->Checked = bool::Parse(sValue); }
        if (sControl == "txtTimelapseNotify") { txtTimelapseNotify->Text = sValue; }
        if (sControl == "chkTimelapseCountdown") { chkTimelapseCountdown->Checked = bool::Parse(sValue); }
        if (sControl == "txtTimelapseCountdown") { txtTimelapseCountdown->Text = sValue; }
        if (sControl == "txtFFMpeg") { txtFFMpeg->Text = sValue; }
        if (sControl == "txtExpFramerate") { txtExpFramerate->Text = sValue; }
        if (sControl == "chkExpAspect") { chkExpAspect->Checked = bool::Parse(sValue); }
    }
    oSR->Close();
    oFS->Close();

    if (cmbCaptureMode->SelectedItem->ToString() == "Application" &&
        mApp.lapseCaptureModeDesc != "Application") { mApp.LoadApplications(chkCaptureModeApp); }

    ExportSettings();

    mApp.bIsStarting = false;
    this->Icon            = GetIcon("ico_app");
    ntfSystray->Icon      = GetIcon("ico_app");

    // Start Timelapse Timer
    mApp.StartTimer();
}

void MainForm::MainForm_Deactivate ( System::Object^ sender, System::EventArgs^ e )
{
    if (this->Visible) {
        txtScreenshots->Select(); // Leave Focus from other controls
        this->Visible = false;

        FileStream^ oFS = gcnew FileStream(Append(Application::StartupPath, "\\TimelapseFX.ini"), FileMode::Create);
        StreamWriter^ oSW = gcnew StreamWriter(oFS);
        oSW->WriteLine(Append("txtScreenshots=", txtScreenshots->Text));
        oSW->WriteLine(Append("cmbCaptureMode=", cmbCaptureMode->SelectedIndex.ToString()));
        oSW->WriteLine(Append("cmbCaptureModeDesc=", cmbCaptureMode->SelectedItem->ToString()));
        oSW->WriteLine(Append("chkCaptureModeApp=", chkCaptureModeApp->CheckedIndices->Count != 0 ? chkCaptureModeApp->CheckedItems[0]->ToString() : ""));
        oSW->WriteLine(Append("chkCaptureModeAppDesc=", chkCaptureModeApp->CheckedIndices->Count != 0 ? chkCaptureModeApp->CheckedItems[0]->ToString() : ""));
        oSW->WriteLine(Append("txtCaptureRegionX=", mApp.lapseCaptureModeRegion.left.ToString()));
        oSW->WriteLine(Append("txtCaptureRegionY=", mApp.lapseCaptureModeRegion.top.ToString()));
        oSW->WriteLine(Append("txtCaptureRegionWidth=", mApp.lapseCaptureModeRegion.right.ToString()));
        oSW->WriteLine(Append("txtCaptureRegionHeight=", mApp.lapseCaptureModeRegion.bottom.ToString()));
        oSW->WriteLine(Append("chkTimelapseTaskbar=",chkTimelapseTaskbar->Checked.ToString()));
        oSW->WriteLine(Append("txtTimelapseDelay=", txtTimelapseDelay->Text));
        oSW->WriteLine(Append("txtTimelapsePeriod=", txtTimelapsePeriod->Text));
        oSW->WriteLine(Append("chkTimelapseNotify=", chkTimelapseNotify->Checked.ToString()));
        oSW->WriteLine(Append("txtTimelapseNotify=", txtTimelapseNotify->Text));
        oSW->WriteLine(Append("chkTimelapseCountdown=", chkTimelapseCountdown->Checked.ToString()));
        oSW->WriteLine(Append("txtTimelapseCountdown=", txtTimelapseCountdown->Text));
        oSW->WriteLine(Append("txtFFMpeg=", txtFFMpeg->Text));
        oSW->WriteLine(Append("txtExpFramerate=", txtExpFramerate->Text));
        oSW->WriteLine(Append("chkExpAspect=", chkExpAspect->Checked.ToString()));
        oSW->Close();
        oFS->Close();

        ExportSettings();

        // Update timer
        mApp.StartTimer();
    }
}

void MainForm::ExportSettings()
{
    mApp.SetOutputFolder(txtScreenshots->Text);
    mApp.lapseCaptureMode       = cmbCaptureMode->SelectedIndex;
    mApp.lapseCaptureModeDesc   = ToCString(cmbCaptureMode->SelectedItem->ToString());
    mApp.lapseCaptureModeApp    = ToCString(chkCaptureModeApp->CheckedIndices->Count != 0 ? chkCaptureModeApp->CheckedItems[0]->ToString() : "");
    mApp.lapseRemoveTaskbar     = chkTimelapseTaskbar->Checked;
    mApp.lapseDelay             = int::Parse(txtTimelapseDelay->Text);
    mApp.lapsePeriod            = double::Parse(txtTimelapsePeriod->Text);
    mApp.lapseNotify            = chkTimelapseNotify->Checked;
    mApp.lapseNotifyRush        = int::Parse(txtTimelapseNotify->Text);
    mApp.lapseCountdown         = chkTimelapseCountdown->Checked;
    mApp.lapseCountdownRush     = int::Parse(txtTimelapseCountdown->Text);
    mApp.videoFFMpegPath        = ToCString(txtFFMpeg->Text);
    mApp.videoFramerate         = float::Parse(txtExpFramerate->Text);
    mApp.videoAspectRatio       = chkExpAspect->Checked;
}

void MainForm::ntfSystray_Click ( System::Object^ sender, System::EventArgs^ e ) 
{
    if ((cli::safe_cast< MouseEventArgs^ >(e))->Button == Windows::Forms::MouseButtons::Left)
    {
        bool _lapseNotify = mApp.lapseNotify;
        bool _lapseCountdown = mApp.lapseCountdown;
        bool _bIsPaused = mApp.bIsPaused;
        mApp.lapseNotify = false;
        mApp.lapseCountdown = false;
        mApp.bIsPaused = false;

        CaptureScreenshot();

        mApp.lapseNotify = _lapseNotify;
        mApp.lapseCountdown = _lapseCountdown;
        mApp.bIsPaused = _bIsPaused;
    }
}

void MainForm::mnuOpenFolder_Click ( System::Object^ sender, System::EventArgs^ e )
{
    Process::Start("explorer.exe", mApp.GetOutputFolder());
}

void MainForm::mnuReorder_Click ( System::Object^ sender, System::EventArgs^ e )
{
    String^ sPath = mApp.GetOutputFolder();
    int iOrder = 0;
    int iFileIdx = 0; 
    for each (String^ oFile in Directory::EnumerateFiles(sPath, "?????_Screenshot.png"))
    {
        oFile = oFile->Substring(sPath->Length);
        if (int::TryParse(oFile->Substring(0, 5), iFileIdx))    // Ignore png files without 00000 filename format.
        {
            if (iFileIdx != iOrder)
            {
                File::Move(
                    Append(sPath, oFile), 
                    Append(sPath, Append(iOrder.ToString("D5"), "_Screenshot.png")));
            }
            iOrder++;
        }
    }
    mApp.countShoots = Directory::GetFiles(sPath, "?????_Screenshot.png")->Length;
}

void MainForm::mnuCaption_Click ( System::Object^ sender, System::EventArgs^ e )
{
    FileStream^ oFS = File::OpenWrite(Append(mApp.GetOutputFolder(), "TimelapseFX_caption.srt"));
    StreamWriter^ oSW = gcnew StreamWriter(oFS);

    // SRT Format
    //   Sequence number
    //   Timecode 00:00:00:00 --> 00:00:00:00
    //   Caption text
    //   Blank line separator

    float iFramerate = 1000 / mApp.videoFramerate ;
    int iFramecount = 0;
    for each (String^ oFile in Directory::EnumerateFiles(mApp.GetOutputFolder(), "?????_Screenshot.png"))
    {
        iFramecount++;
        oSW->WriteLine(iFramecount.ToString());
        oSW->WriteLine(ToSRTTimecode(iFramecount, iFramerate));
        oSW->WriteLine("");
        oSW->WriteLine("");
    }
    oSW->Close();
    oFS->Close();
}

void MainForm::mnuPause_Click ( System::Object^ sender, System::EventArgs^ e )
{
    Timers::Timer^ oLapseTimer = mApp.GetTimer();
    if (mnuPause->Text == "Pause")
    {
        mApp.bIsPaused = true;
        oLapseTimer->Stop();
        oLapseTimer->Enabled = false;
        mnuPause->Image = GetImage("img_res");
        mnuPause->Text = "Resume";
    } else {
        mApp.bIsPaused = false;
        oLapseTimer->Enabled = true;
        oLapseTimer->Start();
        mnuPause->Image = GetImage("img_pau");
        mnuPause->Text = "Pause";
    }
}

void MainForm::mnuSettings_Click ( System::Object^ sender, System::EventArgs^ e )
{
    if (mApp.lapseCaptureModeDesc == "Application") { mApp.LoadApplications(chkCaptureModeApp); }

    // Add scrollbar space if Settings form height is bigger than monitor height
    if ( this->Height > SystemInformation::WorkingArea.Height )
    {
        this->Width = this->Width + 20;
        this->Height = SystemInformation::WorkingArea.Height - 24;
    }

    this->ShowInTaskbar = true;
    this->Location = Point(
        SystemInformation::WorkingArea.Width - this->Width, 
        SystemInformation::WorkingArea.Height - this->Height);
    this->Visible = true;
    this->WindowState = FormWindowState::Normal;
    this->Focus();
}

void MainForm::mnuAbout_Click ( System::Object^ sender, System::EventArgs^ e )
{
    Process::Start("https://github.com/DarknessFX/TimelapseFX");
}

void MainForm::mnuQuit_Click ( System::Object^ sender, System::EventArgs^ e )
{
    MainForm::Close();
}

void MainForm::AllControlsEnabled(bool bEnabled)
{
    txtScreenshots->Enabled          = bEnabled;
    btnScreenshots->Enabled          = bEnabled;
    cmbCaptureMode->Enabled          = bEnabled;
    chkCaptureModeApp->Enabled       = bEnabled;
    txtTimelapsePeriod->Enabled      = bEnabled;
    chkTimelapseNotify->Enabled      = bEnabled;
    txtTimelapseNotify->Enabled      = bEnabled;
    chkTimelapseCountdown->Enabled   = bEnabled;
    txtTimelapseCountdown->Enabled   = bEnabled;
    txtFFMpeg->Enabled               = bEnabled;
    btnFFMpegBrowse->Enabled         = bEnabled;
    btnFFMpegDownload->Enabled       = bEnabled;
    txtExpFramerate->Enabled         = bEnabled;
    chkExpAspect->Enabled            = bEnabled;
}
#pragma endregion


#pragma region Settings Form Events
void MainForm::txtScreenshots_Leave ( System::Object^ sender, System::EventArgs^ e )
{
    if (!Directory::Exists(txtScreenshots->Text)) { txtScreenshots->Text = mApp.GetOutputFolder(); }
    if (txtScreenshots->Text->Substring(txtScreenshots->Text->Length - 1) != "\\") { txtScreenshots->Text = Append(txtScreenshots->Text, "\\"); }
    
}

void MainForm::btnScreenshots_Click ( System::Object^ sender, System::EventArgs^ e )
{
    dlgFolderBrowse->Description = "Folder to save screenshots:";
    dlgFolderBrowse->RootFolder = Environment::SpecialFolder::MyComputer;
    dlgFolderBrowse->SelectedPath = mApp.GetOutputFolder();
    dlgFolderBrowse->ShowNewFolderButton = true;
    if (dlgFolderBrowse->ShowDialog() == Windows::Forms::DialogResult::OK) {
        txtScreenshots->Text = Append(dlgFolderBrowse->SelectedPath, "\\");
        mApp.SetOutputFolder(Append(dlgFolderBrowse->SelectedPath, "\\"));
    }
    mnuSettings_Click(sender, e);
}

void MainForm::cmbCaptureMode_SelectedIndexChanged ( System::Object^ sender, System::EventArgs^ e )
{
    if ( mApp.bIsStarting ) { return; }
    if (cmbCaptureMode->SelectedItem->ToString() == "Application")
    {
        mApp.LoadApplications(chkCaptureModeApp);
    } else {
        chkCaptureModeApp->Enabled = false;
        chkCaptureModeApp->Items->Clear();
    }
}

void MainForm::chkCaptureModeApp_SelectedIndexChanged ( System::Object^ sender, System::EventArgs^ e )
{
    if ( mApp.bIsStarting ) { return; }
}

void MainForm::chkCaptureModeApp_ItemCheck ( System::Object^ sender, System::Windows::Forms::ItemCheckEventArgs^ e )
{
    // Single App selection
    for (int i = 0; i < chkCaptureModeApp->Items->Count; i++) {
        if ( i != e->Index ) { chkCaptureModeApp->SetItemChecked(i, false); }
    }
}

void MainForm::chkTimelapseTaskbar_CheckedChanged ( System::Object^ sender, System::EventArgs^ e )
{
    if ( mApp.bIsStarting ) { return; }
    mApp.lapseRemoveTaskbar = chkTimelapseTaskbar->Checked;
}

void MainForm::txtTimelapseDelay_Leave ( System::Object^ sender, System::EventArgs^ e )
{
}

void MainForm::txtTimelapsePeriod_Leave ( System::Object^ sender, System::EventArgs^ e )
{
    mApp.lapsePeriod = double::Parse(txtTimelapsePeriod->Text);
}

void MainForm::chkTimelapseNotify_CheckedChanged ( System::Object^ sender, System::EventArgs^ e )
{
    if ( mApp.bIsStarting ) { return; }
}

void MainForm::txtTimelapseNotify_Leave ( System::Object^ sender, System::EventArgs^ e )
{
}

void MainForm::chkTimelapseCountdown_CheckedChanged ( System::Object^ sender, System::EventArgs^ e )
{
    if ( mApp.bIsStarting ) { return; }
}

void MainForm::txtTimelapseCountdown_Leave ( System::Object^ sender, System::EventArgs^ e )
{
}

void MainForm::txtFFMpeg_Leave ( System::Object^ sender, System::EventArgs^ e )
{
    if (!File::Exists(txtFFMpeg->Text) || !txtFFMpeg->Text->ToLower()->Contains("ffmpeg.exe")) { txtFFMpeg->Text = mApp.GetFFMpegPath(); }
}

void MainForm::btnFFMpegBrowse_Click ( System::Object^ sender, System::EventArgs^ e )
{
    dlgFileBrowse->Filter = "FFMpeg Executable (.exe)|FFMpeg.exe";
    dlgFileBrowse->FilterIndex = 1;
    dlgFileBrowse->RestoreDirectory = true;
    dlgFileBrowse->Multiselect = false;
    dlgFileBrowse->CheckFileExists = true;
    dlgFileBrowse->CheckPathExists = true;
    dlgFileBrowse->DefaultExt = "exe";
    dlgFileBrowse->InitialDirectory = mApp.GetFFMpegPath();
    if (dlgFileBrowse->ShowDialog() == Windows::Forms::DialogResult::OK) {
        txtFFMpeg->Text = dlgFileBrowse->FileName;
        mApp.SetFFMpegPath(dlgFileBrowse->FileName);
    }
    mnuSettings_Click(sender, e);
}

void MainForm::btnFFMpegDownload_Click ( System::Object^ sender, System::EventArgs^ e )
{
    Process::Start("https://ffmpeg.org/download.html#build-windows");
    Sleep(500);
    Process::Start("https://m.majorgeeks.com/files/details/ffmpeg.html");    
}

void MainForm::txtExpFramerate_Leave ( System::Object^ sender, System::EventArgs^ e )
{
}

void MainForm::chkExpAspect_CheckedChanged ( System::Object^ sender, System::EventArgs^ e )
{
    if ( mApp.bIsStarting ) { return; }
}
#pragma endregion


#pragma region Export To Video
/// 
/// Export To Video
/// 
struct ExportType {
    enum Size {
        pOrig = 5,
        p480 = 1,
        p720 = 2,
        p1080 = 3,
        p2160 = 4
    };
    enum Format {
        MP4 = 0,
        AVI = 1,
        GIF = 2
    };
};

void ExportTimelapse( ExportType::Size expSize, ExportType::Format expFormat) {
    NotifyIcon^ ntfSystray = mApp.GetNotifyIcon();

    if ( !File::Exists(mApp.GetFFMpegPath()) )
    {
        ntfSystray->BalloonTipIcon = ToolTipIcon::Error;
        ntfSystray->BalloonTipTitle = "TimelapseFX - FFMpeg not found.";
        ntfSystray->BalloonTipText = "Go to Settings and inform FFMpeg.exe location.";
        ntfSystray->ShowBalloonTip(1000);
        return;
    }
    
    Application::UseWaitCursor = true;
    mApp.bIsExporting = true;

    ntfSystray->Icon = GetIcon("ico_ffm");
    ntfSystray->Text = "Exporting video...";

    String^ expFile = Append(mApp.GetOutputFolder(), "TimelapseFX");
    expFile = Append("\"", expFile);

    String^ expProc = " -framerate ";
    expProc = Append(expProc, mApp.videoFramerate.ToString()->Replace(",","."));
    expProc = Append(expProc, mApp.GetFFMpegArgs());
    expProc = Append(expProc, " -i \"");
    expProc = Append(expProc, mApp.GetOutputFolder());
    expProc = Append(expProc, "%05d_Screenshot.png\" ");

    if ( mApp.videoAspectRatio && 
         expSize != ExportType::Size::pOrig ) 
    {
        expProc = Append(expProc, " -aspect 16/9 ");
    }

    switch ( expSize ) {
        case ExportType::Size::pOrig:
            expProc = Append(expProc, " -vf scale=force_original_aspect_ratio=decrease");
            expFile = Append(expFile, "_Orig");
            break;
        case ExportType::Size::p480:
            expProc = Append(expProc, " -vf scale=w=854:h=480");
            expFile = Append(expFile, "_480p");
            break;
        case ExportType::Size::p720:
            expProc = Append(expProc, " -vf scale=w=1280:h=720");
            expFile = Append(expFile, "_720p");
            break;
        case ExportType::Size::p1080:
            expProc = Append(expProc, " -vf scale=w=1920:h=1080");
            expFile = Append(expFile, "_1080p");
            break;
        case ExportType::Size::p2160:
            expProc = Append(expProc, " -vf scale=w=3840:h=2160");
            expFile = Append(expFile, "_2160p");
            break;
    }
    switch ( expFormat ) {
        case ExportType::Format::MP4:
            expFile = Append(expFile, ".mp4");
            break;
        case ExportType::Format::AVI:
            expFile = Append(expFile, ".avi");
            break;
        case ExportType::Format::GIF:
            expFile = Append(expFile, "_.mp4"); // new improved GIF, use MP4 temp for 1st pass
            break;
    }
    if ( File::Exists(Append(mApp.GetOutputFolder(), "TimelapseFX_caption.srt") ) )
    {
        expProc = Append(expProc, ",subtitles=\"");
        expProc = Append(expProc, Append(mApp.GetOutputFolder()->Replace("\\", "\\\\\\\\")->Replace(":", "\\\\\\:"), "TimelapseFX_caption.srt"));
        expProc = Append(expProc, "\"");
    }
    expProc = Append(expProc, ",format=yuv420p -movflags +faststart -preset veryslow -tune stillimage -crf 0 ");

    expFile = Append(expFile, "\" ");
    expProc = Append(expProc, expFile);

    Process^ oProc = gcnew Process;
    oProc->StartInfo->FileName = mApp.GetFFMpegPath();
    oProc->StartInfo->Arguments = expProc;
    oProc->StartInfo->WindowStyle = ProcessWindowStyle::Hidden;
    oProc->StartInfo->CreateNoWindow = true;
    oProc->Start();
    oProc->WaitForExit();
    oProc->Close();

    //DEBUG: 
    OutputDebugStringA(ToCString(Append(mApp.GetFFMpegPath(), expProc)).c_str());
    OutputDebugStringA("\n");

    if (expFormat == ExportType::Format::GIF)
    {
        // new improved GIF
        // Credits to http://blog.pkh.me/p/21-high-quality-gif-with-ffmpeg.html
        // GIF 2nd Pass, from MP4 to Palette PNG

        String^ expPal = "\"";
        expPal = Append(expPal, mApp.GetOutputFolder());
        expPal = Append(expPal, "TimelapseFX_gif_palette.png");
        expPal = Append(expPal, "\"");

        oProc->StartInfo->FileName = mApp.GetFFMpegPath();
        oProc->StartInfo->Arguments = Append(Append(Append(" -i ", expFile), " -vf \"scale=-1:-1:flags=lanczos,palettegen=stats_mode=full\" -y "), expPal);
        oProc->StartInfo->WindowStyle = ProcessWindowStyle::Hidden;
        oProc->StartInfo->CreateNoWindow = true;
        oProc->Start();
        oProc->WaitForExit();
        oProc->Close();

        //DEBUG: 
        OutputDebugStringA(ToCString(Append(mApp.GetFFMpegPath(), oProc->StartInfo->Arguments)).c_str());
        OutputDebugStringA("\n");

        expProc = Append(" -i ", expFile);
        expProc = Append(expProc, " -i ");
        expProc = Append(expProc, expPal);

        // GIF 3nd Pass, MP4 + Palette PNG to GIF
        oProc->StartInfo->FileName = mApp.GetFFMpegPath();
        oProc->StartInfo->Arguments = Append(Append(expProc, " -lavfi \"scale=-1:-1:flags=lanczos [x]; [x][1:v] paletteuse=dither=sierra2\" -y "), expFile->Replace("_.mp4", ".gif"));
        oProc->StartInfo->WindowStyle = ProcessWindowStyle::Hidden;
        oProc->StartInfo->CreateNoWindow = true;
        oProc->Start();
        oProc->WaitForExit();
        oProc->Close();

        //DEBUG: 
        OutputDebugStringA(ToCString(Append(mApp.GetFFMpegPath(), oProc->StartInfo->Arguments)).c_str());
        OutputDebugStringA("\n");

        File::Delete(expPal->Replace("\"", "")->Trim());
        File::Delete(expFile->Replace("\"", "")->Trim());
    }

    ntfSystray->Text = "TimelapseFX - Click to capture screenshot.";
    ntfSystray->Icon = GetIcon("ico_app");

    mApp.bIsExporting = false;
    Application::UseWaitCursor = false;
}

void MainForm::mnuExpOrigMP4_Click ( System::Object^ sender, System::EventArgs^ e ) { ExportTimelapse( ExportType::Size::pOrig, ExportType::Format::MP4 );  };
void MainForm::mnuExpOrigAVI_Click ( System::Object^ sender, System::EventArgs^ e ) { ExportTimelapse( ExportType::Size::pOrig, ExportType::Format::AVI );  };
void MainForm::mnuExpOrigGIF_Click ( System::Object^ sender, System::EventArgs^ e ) { ExportTimelapse( ExportType::Size::pOrig, ExportType::Format::GIF );  };
void MainForm::mnuExp480MP4_Click ( System::Object^ sender, System::EventArgs^ e )  { ExportTimelapse( ExportType::Size::p480, ExportType::Format::MP4 );  };
void MainForm::mnuExp480AVI_Click ( System::Object^ sender, System::EventArgs^ e )  { ExportTimelapse( ExportType::Size::p480, ExportType::Format::AVI );  };
void MainForm::mnuExp480GIF_Click ( System::Object^ sender, System::EventArgs^ e )  { ExportTimelapse( ExportType::Size::p480, ExportType::Format::GIF );  };
void MainForm::mnuExp720MP4_Click ( System::Object^ sender, System::EventArgs^ e )  { ExportTimelapse( ExportType::Size::p720, ExportType::Format::MP4 );  };
void MainForm::mnuExp720AVI_Click ( System::Object^ sender, System::EventArgs^ e )  { ExportTimelapse( ExportType::Size::p720, ExportType::Format::AVI );  };
void MainForm::mnuExp720GIF_Click ( System::Object^ sender, System::EventArgs^ e )  { ExportTimelapse( ExportType::Size::p720, ExportType::Format::GIF );  };
void MainForm::mnuExp1080MP4_Click ( System::Object^ sender, System::EventArgs^ e ) { ExportTimelapse( ExportType::Size::p1080, ExportType::Format::MP4 ); };
void MainForm::mnuExp1080AVI_Click ( System::Object^ sender, System::EventArgs^ e ) { ExportTimelapse( ExportType::Size::p1080, ExportType::Format::AVI ); };
void MainForm::mnuExp1080GIF_Click ( System::Object^ sender, System::EventArgs^ e ) { ExportTimelapse( ExportType::Size::p1080, ExportType::Format::GIF ); };
void MainForm::mnuExp2160MP4_Click ( System::Object^ sender, System::EventArgs^ e ) { ExportTimelapse( ExportType::Size::p2160, ExportType::Format::MP4 ); };
void MainForm::mnuExp2160AVI_Click ( System::Object^ sender, System::EventArgs^ e ) { ExportTimelapse( ExportType::Size::p2160, ExportType::Format::AVI ); };
void MainForm::mnuExp2160GIF_Click ( System::Object^ sender, System::EventArgs^ e ) { ExportTimelapse( ExportType::Size::p2160, ExportType::Format::GIF ); };
#pragma endregion