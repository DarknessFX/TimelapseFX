#pragma once

namespace TimelapseFX {

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Summary for MainForm
/// </summary>
public ref class MainForm : public System::Windows::Forms::Form
{
public:
	MainForm(void)
	{
		InitializeComponent();
		//
		// Add the constructor code here
		//
	}

protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~MainForm()
	{
		if (components)
		{
			delete components;
		}
	}
private: System::Windows::Forms::NotifyIcon^ ntfSystray;
private: System::Windows::Forms::ContextMenuStrip^ ctxMenu;
private: System::Windows::Forms::ToolStripMenuItem^ mnuOpenFolder;
private: System::Windows::Forms::ToolStripSeparator^ mnuSeparator1;
private: System::Windows::Forms::ToolStripMenuItem^ mnuQuit;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp480;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp480MP4;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp480AVI;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp480GIF;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp720;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp720MP4;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp720AVI;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp720GIF;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp1080;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp1080MP4;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp1080AVI;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp1080GIF;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp2160;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp2160MP4;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp2160AVI;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExp2160GIF;
private: System::Windows::Forms::ToolStripMenuItem^ mnuReorder;
private: System::Windows::Forms::ToolStripSeparator^ mnuSeparator2;

private: System::Windows::Forms::ToolStripMenuItem^ mnuAbout;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExpOrig;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExpOrigMP4;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExpOrigAVI;
private: System::Windows::Forms::ToolStripMenuItem^ mnuExpOrigGIF;
private: System::Windows::Forms::ToolStripMenuItem^ mnuSettings;
private: System::Windows::Forms::FlowLayoutPanel^ flwSettings;
private: System::Windows::Forms::FolderBrowserDialog^ dlgFolderBrowse;


private: System::Windows::Forms::GroupBox^ grpScreenshots;
private: System::Windows::Forms::Button^ btnScreenshots;
private: System::Windows::Forms::TextBox^ txtScreenshots;
private: System::Windows::Forms::GroupBox^ grpCaptureMode;
private: System::Windows::Forms::CheckedListBox^ chkCaptureModeApp;
private: System::Windows::Forms::ComboBox^ cmbCaptureMode;
private: System::Windows::Forms::GroupBox^ grpTimelapse;
private: System::Windows::Forms::CheckBox^ chkTimelapseCountdown;
private: System::Windows::Forms::NumericUpDown^ txtTimelapseCountdown;
private: System::Windows::Forms::Label^ lblTimelapseCountdown;
private: System::Windows::Forms::CheckBox^ chkTimelapseNotify;
private: System::Windows::Forms::NumericUpDown^ txtTimelapseNotify;
private: System::Windows::Forms::Label^ lblTimelapseNotify;
private: System::Windows::Forms::NumericUpDown^ txtTimelapsePeriod;
private: System::Windows::Forms::Label^ lblTimelapsePeriod;
private: System::Windows::Forms::GroupBox^ grpFFMpeg;
private: System::Windows::Forms::Button^ btnFFMpegBrowse;
private: System::Windows::Forms::Button^ btnFFMpegDownload;
private: System::Windows::Forms::Label^ lblFFMpeg;
private: System::Windows::Forms::TextBox^ txtFFMpeg;
private: System::Windows::Forms::GroupBox^ grpExp;
private: System::Windows::Forms::CheckBox^ chkExpAspect;
private: System::Windows::Forms::NumericUpDown^ txtExpFramerate;
private: System::Windows::Forms::Label^ lblExpFramerate;
private: System::Windows::Forms::CheckBox^ chkTimelapseTaskbar;
private: System::Windows::Forms::ToolStripMenuItem^ mnuPause;
private: System::Windows::Forms::ToolTip^ tipMain;
private: System::Windows::Forms::NumericUpDown^ txtTimelapseDelay;
private: System::Windows::Forms::Label^ lblTimelapseDelay;
private: System::Windows::Forms::OpenFileDialog^ dlgFileBrowse;
private: System::Windows::Forms::ToolStripSeparator^ mnuSeparator3;
private: System::Windows::Forms::ToolStripMenuItem^ mnuCaption;



private: System::ComponentModel::IContainer^ components;

private:
	/// <summary>
	/// Required designer variable.
	/// </summary>


#pragma region Windows Form Designer generated code
	/// <summary>
	/// Required method for Designer support - do not modify
	/// the contents of this method with the code editor.
	/// </summary>
	void InitializeComponent(void)
	{
        this->components = ( gcnew System::ComponentModel::Container () );
        this->ntfSystray = ( gcnew System::Windows::Forms::NotifyIcon ( this->components ) );
        this->ctxMenu = ( gcnew System::Windows::Forms::ContextMenuStrip ( this->components ) );
        this->mnuOpenFolder = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuReorder = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuSeparator2 = ( gcnew System::Windows::Forms::ToolStripSeparator () );
        this->mnuExp = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExpOrig = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExpOrigMP4 = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExpOrigAVI = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExpOrigGIF = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExp480 = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExp480MP4 = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExp480AVI = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExp480GIF = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExp720 = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExp720MP4 = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExp720AVI = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExp720GIF = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExp1080 = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExp1080MP4 = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExp1080AVI = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExp1080GIF = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExp2160 = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExp2160MP4 = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExp2160AVI = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuExp2160GIF = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuSeparator3 = ( gcnew System::Windows::Forms::ToolStripSeparator () );
        this->mnuCaption = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuSeparator1 = ( gcnew System::Windows::Forms::ToolStripSeparator () );
        this->mnuPause = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuSettings = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuAbout = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->mnuQuit = ( gcnew System::Windows::Forms::ToolStripMenuItem () );
        this->flwSettings = ( gcnew System::Windows::Forms::FlowLayoutPanel () );
        this->grpScreenshots = ( gcnew System::Windows::Forms::GroupBox () );
        this->btnScreenshots = ( gcnew System::Windows::Forms::Button () );
        this->txtScreenshots = ( gcnew System::Windows::Forms::TextBox () );
        this->grpCaptureMode = ( gcnew System::Windows::Forms::GroupBox () );
        this->chkCaptureModeApp = ( gcnew System::Windows::Forms::CheckedListBox () );
        this->cmbCaptureMode = ( gcnew System::Windows::Forms::ComboBox () );
        this->grpTimelapse = ( gcnew System::Windows::Forms::GroupBox () );
        this->txtTimelapseDelay = ( gcnew System::Windows::Forms::NumericUpDown () );
        this->lblTimelapseDelay = ( gcnew System::Windows::Forms::Label () );
        this->chkTimelapseTaskbar = ( gcnew System::Windows::Forms::CheckBox () );
        this->chkTimelapseCountdown = ( gcnew System::Windows::Forms::CheckBox () );
        this->txtTimelapseCountdown = ( gcnew System::Windows::Forms::NumericUpDown () );
        this->lblTimelapseCountdown = ( gcnew System::Windows::Forms::Label () );
        this->chkTimelapseNotify = ( gcnew System::Windows::Forms::CheckBox () );
        this->txtTimelapseNotify = ( gcnew System::Windows::Forms::NumericUpDown () );
        this->lblTimelapseNotify = ( gcnew System::Windows::Forms::Label () );
        this->txtTimelapsePeriod = ( gcnew System::Windows::Forms::NumericUpDown () );
        this->lblTimelapsePeriod = ( gcnew System::Windows::Forms::Label () );
        this->grpFFMpeg = ( gcnew System::Windows::Forms::GroupBox () );
        this->btnFFMpegBrowse = ( gcnew System::Windows::Forms::Button () );
        this->btnFFMpegDownload = ( gcnew System::Windows::Forms::Button () );
        this->lblFFMpeg = ( gcnew System::Windows::Forms::Label () );
        this->txtFFMpeg = ( gcnew System::Windows::Forms::TextBox () );
        this->grpExp = ( gcnew System::Windows::Forms::GroupBox () );
        this->chkExpAspect = ( gcnew System::Windows::Forms::CheckBox () );
        this->txtExpFramerate = ( gcnew System::Windows::Forms::NumericUpDown () );
        this->lblExpFramerate = ( gcnew System::Windows::Forms::Label () );
        this->dlgFolderBrowse = ( gcnew System::Windows::Forms::FolderBrowserDialog () );
        this->tipMain = ( gcnew System::Windows::Forms::ToolTip ( this->components ) );
        this->dlgFileBrowse = ( gcnew System::Windows::Forms::OpenFileDialog () );
        this->ctxMenu->SuspendLayout ();
        this->flwSettings->SuspendLayout ();
        this->grpScreenshots->SuspendLayout ();
        this->grpCaptureMode->SuspendLayout ();
        this->grpTimelapse->SuspendLayout ();
        ( cli::safe_cast< System::ComponentModel::ISupportInitialize^ >( this->txtTimelapseDelay ) )->BeginInit ();
        ( cli::safe_cast< System::ComponentModel::ISupportInitialize^ >( this->txtTimelapseCountdown ) )->BeginInit ();
        ( cli::safe_cast< System::ComponentModel::ISupportInitialize^ >( this->txtTimelapseNotify ) )->BeginInit ();
        ( cli::safe_cast< System::ComponentModel::ISupportInitialize^ >( this->txtTimelapsePeriod ) )->BeginInit ();
        this->grpFFMpeg->SuspendLayout ();
        this->grpExp->SuspendLayout ();
        ( cli::safe_cast< System::ComponentModel::ISupportInitialize^ >( this->txtExpFramerate ) )->BeginInit ();
        this->SuspendLayout ();
        // 
        // ntfSystray
        // 
        this->ntfSystray->ContextMenuStrip = this->ctxMenu;
        this->ntfSystray->Text = L"TimelapseFX - Click to capture screenshot.";
        this->ntfSystray->Visible = true;
        this->ntfSystray->Click += gcnew System::EventHandler ( this, &MainForm::ntfSystray_Click );
        // 
        // ctxMenu
        // 
        this->ctxMenu->Items->AddRange ( gcnew cli::array< System::Windows::Forms::ToolStripItem^  > ( 9 )
        {
            this->mnuOpenFolder, this->mnuReorder,
                this->mnuSeparator2, this->mnuExp, this->mnuSeparator1, this->mnuPause, this->mnuSettings, this->mnuAbout, this->mnuQuit
        } );
        this->ctxMenu->Name = L"ctxMenu";
        this->ctxMenu->Size = System::Drawing::Size ( 203, 170 );
        // 
        // mnuOpenFolder
        // 
        this->mnuOpenFolder->Name = L"mnuOpenFolder";
        this->mnuOpenFolder->Size = System::Drawing::Size ( 202, 22 );
        this->mnuOpenFolder->Text = L"Open screenshots folder";
        this->mnuOpenFolder->ToolTipText = L"Open Windows Explorer on the screenshots folder.";
        this->mnuOpenFolder->Click += gcnew System::EventHandler ( this, &MainForm::mnuOpenFolder_Click );
        // 
        // mnuReorder
        // 
        this->mnuReorder->Name = L"mnuReorder";
        this->mnuReorder->Size = System::Drawing::Size ( 202, 22 );
        this->mnuReorder->Text = L"Reorder filenames";
        this->mnuReorder->ToolTipText = L"If you manually deleted screenshots, use this option to reorder the filenames num"
            L"bers.";
        this->mnuReorder->Click += gcnew System::EventHandler ( this, &MainForm::mnuReorder_Click );
        // 
        // mnuSeparator2
        // 
        this->mnuSeparator2->Name = L"mnuSeparator2";
        this->mnuSeparator2->Size = System::Drawing::Size ( 199, 6 );
        // 
        // mnuExp
        // 
        this->mnuExp->DropDownItems->AddRange ( gcnew cli::array< System::Windows::Forms::ToolStripItem^  > ( 7 )
        {
            this->mnuExpOrig, this->mnuExp480,
                this->mnuExp720, this->mnuExp1080, this->mnuExp2160, this->mnuSeparator3, this->mnuCaption
        } );
        this->mnuExp->Name = L"mnuExp";
        this->mnuExp->Size = System::Drawing::Size ( 202, 22 );
        this->mnuExp->Tag = L"Export screenshots in different formats.";
        this->mnuExp->Text = L"Export Timelapse";
        // 
        // mnuExpOrig
        // 
        this->mnuExpOrig->DropDownItems->AddRange ( gcnew cli::array< System::Windows::Forms::ToolStripItem^  > ( 3 )
        {
            this->mnuExpOrigMP4,
                this->mnuExpOrigAVI, this->mnuExpOrigGIF
        } );
        this->mnuExpOrig->Name = L"mnuExpOrig";
        this->mnuExpOrig->Size = System::Drawing::Size ( 151, 22 );
        this->mnuExpOrig->Text = L"Original Res.";
        this->mnuExpOrig->ToolTipText = L"Keep the original screenshot resolutionwhen exporting to video.";
        // 
        // mnuExpOrigMP4
        // 
        this->mnuExpOrigMP4->Name = L"mnuExpOrigMP4";
        this->mnuExpOrigMP4->Size = System::Drawing::Size ( 98, 22 );
        this->mnuExpOrigMP4->Text = L"MP4";
        this->mnuExpOrigMP4->Click += gcnew System::EventHandler ( this, &MainForm::mnuExpOrigMP4_Click );
        // 
        // mnuExpOrigAVI
        // 
        this->mnuExpOrigAVI->Name = L"mnuExpOrigAVI";
        this->mnuExpOrigAVI->Size = System::Drawing::Size ( 98, 22 );
        this->mnuExpOrigAVI->Text = L"AVI";
        this->mnuExpOrigAVI->Click += gcnew System::EventHandler ( this, &MainForm::mnuExpOrigAVI_Click );
        // 
        // mnuExpOrigGIF
        // 
        this->mnuExpOrigGIF->Name = L"mnuExpOrigGIF";
        this->mnuExpOrigGIF->Size = System::Drawing::Size ( 98, 22 );
        this->mnuExpOrigGIF->Text = L"GIF";
        this->mnuExpOrigGIF->Click += gcnew System::EventHandler ( this, &MainForm::mnuExpOrigGIF_Click );
        // 
        // mnuExp480
        // 
        this->mnuExp480->DropDownItems->AddRange ( gcnew cli::array< System::Windows::Forms::ToolStripItem^  > ( 3 )
        {
            this->mnuExp480MP4,
                this->mnuExp480AVI, this->mnuExp480GIF
        } );
        this->mnuExp480->Name = L"mnuExp480";
        this->mnuExp480->Size = System::Drawing::Size ( 151, 22 );
        this->mnuExp480->Text = L"480p";
        this->mnuExp480->ToolTipText = L"VGA";
        // 
        // mnuExp480MP4
        // 
        this->mnuExp480MP4->Name = L"mnuExp480MP4";
        this->mnuExp480MP4->Size = System::Drawing::Size ( 98, 22 );
        this->mnuExp480MP4->Text = L"MP4";
        this->mnuExp480MP4->ToolTipText = L"Export timelapse as AVI video.";
        this->mnuExp480MP4->Click += gcnew System::EventHandler ( this, &MainForm::mnuExp480MP4_Click );
        // 
        // mnuExp480AVI
        // 
        this->mnuExp480AVI->Name = L"mnuExp480AVI";
        this->mnuExp480AVI->Size = System::Drawing::Size ( 98, 22 );
        this->mnuExp480AVI->Text = L"AVI";
        this->mnuExp480AVI->ToolTipText = L"Export timelapse as MP4 video.";
        this->mnuExp480AVI->Click += gcnew System::EventHandler ( this, &MainForm::mnuExp480AVI_Click );
        // 
        // mnuExp480GIF
        // 
        this->mnuExp480GIF->Name = L"mnuExp480GIF";
        this->mnuExp480GIF->Size = System::Drawing::Size ( 98, 22 );
        this->mnuExp480GIF->Text = L"GIF";
        this->mnuExp480GIF->ToolTipText = L"Export timelapse as animated GIF.";
        this->mnuExp480GIF->Click += gcnew System::EventHandler ( this, &MainForm::mnuExp480GIF_Click );
        // 
        // mnuExp720
        // 
        this->mnuExp720->DropDownItems->AddRange ( gcnew cli::array< System::Windows::Forms::ToolStripItem^  > ( 3 )
        {
            this->mnuExp720MP4,
                this->mnuExp720AVI, this->mnuExp720GIF
        } );
        this->mnuExp720->Name = L"mnuExp720";
        this->mnuExp720->Size = System::Drawing::Size ( 151, 22 );
        this->mnuExp720->Text = L"720p";
        this->mnuExp720->ToolTipText = L"Standard HD";
        // 
        // mnuExp720MP4
        // 
        this->mnuExp720MP4->Name = L"mnuExp720MP4";
        this->mnuExp720MP4->Size = System::Drawing::Size ( 98, 22 );
        this->mnuExp720MP4->Text = L"MP4";
        this->mnuExp720MP4->ToolTipText = L"Export timelapse as MP4 video.";
        this->mnuExp720MP4->Click += gcnew System::EventHandler ( this, &MainForm::mnuExp720MP4_Click );
        // 
        // mnuExp720AVI
        // 
        this->mnuExp720AVI->Name = L"mnuExp720AVI";
        this->mnuExp720AVI->Size = System::Drawing::Size ( 98, 22 );
        this->mnuExp720AVI->Text = L"AVI";
        this->mnuExp720AVI->ToolTipText = L"Export timelapse as AVI video.";
        this->mnuExp720AVI->Click += gcnew System::EventHandler ( this, &MainForm::mnuExp720AVI_Click );
        // 
        // mnuExp720GIF
        // 
        this->mnuExp720GIF->Name = L"mnuExp720GIF";
        this->mnuExp720GIF->Size = System::Drawing::Size ( 98, 22 );
        this->mnuExp720GIF->Text = L"GIF";
        this->mnuExp720GIF->ToolTipText = L"Export timelapse as animated GIF.";
        this->mnuExp720GIF->Click += gcnew System::EventHandler ( this, &MainForm::mnuExp720GIF_Click );
        // 
        // mnuExp1080
        // 
        this->mnuExp1080->DropDownItems->AddRange ( gcnew cli::array< System::Windows::Forms::ToolStripItem^  > ( 3 )
        {
            this->mnuExp1080MP4,
                this->mnuExp1080AVI, this->mnuExp1080GIF
        } );
        this->mnuExp1080->Name = L"mnuExp1080";
        this->mnuExp1080->Size = System::Drawing::Size ( 151, 22 );
        this->mnuExp1080->Text = L"1080p";
        this->mnuExp1080->ToolTipText = L"Full HD";
        // 
        // mnuExp1080MP4
        // 
        this->mnuExp1080MP4->Name = L"mnuExp1080MP4";
        this->mnuExp1080MP4->Size = System::Drawing::Size ( 98, 22 );
        this->mnuExp1080MP4->Text = L"MP4";
        this->mnuExp1080MP4->ToolTipText = L"Export timelapse as MP4 video.";
        this->mnuExp1080MP4->Click += gcnew System::EventHandler ( this, &MainForm::mnuExp1080MP4_Click );
        // 
        // mnuExp1080AVI
        // 
        this->mnuExp1080AVI->Name = L"mnuExp1080AVI";
        this->mnuExp1080AVI->Size = System::Drawing::Size ( 98, 22 );
        this->mnuExp1080AVI->Text = L"AVI";
        this->mnuExp1080AVI->ToolTipText = L"Export timelapse as AVI video.";
        this->mnuExp1080AVI->Click += gcnew System::EventHandler ( this, &MainForm::mnuExp1080AVI_Click );
        // 
        // mnuExp1080GIF
        // 
        this->mnuExp1080GIF->Name = L"mnuExp1080GIF";
        this->mnuExp1080GIF->Size = System::Drawing::Size ( 98, 22 );
        this->mnuExp1080GIF->Text = L"GIF";
        this->mnuExp1080GIF->ToolTipText = L"Export timelapse as animated GIF.";
        this->mnuExp1080GIF->Click += gcnew System::EventHandler ( this, &MainForm::mnuExp1080GIF_Click );
        // 
        // mnuExp2160
        // 
        this->mnuExp2160->DropDownItems->AddRange ( gcnew cli::array< System::Windows::Forms::ToolStripItem^  > ( 3 )
        {
            this->mnuExp2160MP4,
                this->mnuExp2160AVI, this->mnuExp2160GIF
        } );
        this->mnuExp2160->Name = L"mnuExp2160";
        this->mnuExp2160->Size = System::Drawing::Size ( 151, 22 );
        this->mnuExp2160->Text = L"2160p";
        this->mnuExp2160->ToolTipText = L"4K UHD";
        // 
        // mnuExp2160MP4
        // 
        this->mnuExp2160MP4->Name = L"mnuExp2160MP4";
        this->mnuExp2160MP4->Size = System::Drawing::Size ( 98, 22 );
        this->mnuExp2160MP4->Text = L"MP4";
        this->mnuExp2160MP4->ToolTipText = L"Export timelapse as MP4 video.";
        this->mnuExp2160MP4->Click += gcnew System::EventHandler ( this, &MainForm::mnuExp2160MP4_Click );
        // 
        // mnuExp2160AVI
        // 
        this->mnuExp2160AVI->Name = L"mnuExp2160AVI";
        this->mnuExp2160AVI->Size = System::Drawing::Size ( 98, 22 );
        this->mnuExp2160AVI->Text = L"AVI";
        this->mnuExp2160AVI->ToolTipText = L"Export timelapse as AVI video.";
        this->mnuExp2160AVI->Click += gcnew System::EventHandler ( this, &MainForm::mnuExp2160AVI_Click );
        // 
        // mnuExp2160GIF
        // 
        this->mnuExp2160GIF->Name = L"mnuExp2160GIF";
        this->mnuExp2160GIF->Size = System::Drawing::Size ( 98, 22 );
        this->mnuExp2160GIF->Text = L"GIF";
        this->mnuExp2160GIF->ToolTipText = L"Export timelapse as animated GIF.";
        this->mnuExp2160GIF->Click += gcnew System::EventHandler ( this, &MainForm::mnuExp2160GIF_Click );
        // 
        // mnuSeparator3
        // 
        this->mnuSeparator3->Name = L"mnuSeparator3";
        this->mnuSeparator3->Size = System::Drawing::Size ( 148, 6 );
        // 
        // mnuCaption
        // 
        this->mnuCaption->Name = L"mnuCaption";
        this->mnuCaption->Size = System::Drawing::Size ( 151, 22 );
        this->mnuCaption->Text = L"Create caption";
        this->mnuCaption->ToolTipText = L"Option to insert caption text for each screenshot when exporting to video.";
        this->mnuCaption->Click += gcnew System::EventHandler ( this, &MainForm::mnuCaption_Click );
        // 
        // mnuSeparator1
        // 
        this->mnuSeparator1->Name = L"mnuSeparator1";
        this->mnuSeparator1->Size = System::Drawing::Size ( 199, 6 );
        // 
        // mnuPause
        // 
        this->mnuPause->Name = L"mnuPause";
        this->mnuPause->Size = System::Drawing::Size ( 202, 22 );
        this->mnuPause->Text = L"Pause";
        this->mnuPause->Click += gcnew System::EventHandler ( this, &MainForm::mnuPause_Click );
        // 
        // mnuSettings
        // 
        this->mnuSettings->Name = L"mnuSettings";
        this->mnuSettings->Size = System::Drawing::Size ( 202, 22 );
        this->mnuSettings->Text = L"Settings";
        this->mnuSettings->Click += gcnew System::EventHandler ( this, &MainForm::mnuSettings_Click );
        // 
        // mnuAbout
        // 
        this->mnuAbout->Name = L"mnuAbout";
        this->mnuAbout->Size = System::Drawing::Size ( 202, 22 );
        this->mnuAbout->Text = L"About";
        this->mnuAbout->Click += gcnew System::EventHandler ( this, &MainForm::mnuAbout_Click );
        // 
        // mnuQuit
        // 
        this->mnuQuit->Name = L"mnuQuit";
        this->mnuQuit->Size = System::Drawing::Size ( 202, 22 );
        this->mnuQuit->Text = L"Quit";
        this->mnuQuit->ToolTipText = L"Quit TimelapseFX program.";
        this->mnuQuit->Click += gcnew System::EventHandler ( this, &MainForm::mnuQuit_Click );
        // 
        // flwSettings
        // 
        this->flwSettings->AutoScroll = true;
        this->flwSettings->AutoSize = true;
        this->flwSettings->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
        this->flwSettings->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
        this->flwSettings->CausesValidation = false;
        this->flwSettings->Controls->Add ( this->grpScreenshots );
        this->flwSettings->Controls->Add ( this->grpCaptureMode );
        this->flwSettings->Controls->Add ( this->grpTimelapse );
        this->flwSettings->Controls->Add ( this->grpFFMpeg );
        this->flwSettings->Controls->Add ( this->grpExp );
        this->flwSettings->Dock = System::Windows::Forms::DockStyle::Fill;
        this->flwSettings->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
        this->flwSettings->Location = System::Drawing::Point ( 0, 0 );
        this->flwSettings->Name = L"flwSettings";
        this->flwSettings->Padding = System::Windows::Forms::Padding ( 6 );
        this->flwSettings->Size = System::Drawing::Size ( 268, 724 );
        this->flwSettings->TabIndex = 3;
        this->flwSettings->WrapContents = false;
        // 
        // grpScreenshots
        // 
        this->grpScreenshots->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
        this->grpScreenshots->BackColor = System::Drawing::Color::Transparent;
        this->grpScreenshots->Controls->Add ( this->btnScreenshots );
        this->grpScreenshots->Controls->Add ( this->txtScreenshots );
        this->grpScreenshots->Dock = System::Windows::Forms::DockStyle::Left;
        this->flwSettings->SetFlowBreak ( this->grpScreenshots, true );
        this->grpScreenshots->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                                       static_cast< System::Byte >( 0 ) ) );
        this->grpScreenshots->ForeColor = System::Drawing::Color::Gainsboro;
        this->grpScreenshots->Location = System::Drawing::Point ( 6, 6 );
        this->grpScreenshots->Margin = System::Windows::Forms::Padding ( 0 );
        this->grpScreenshots->Name = L"grpScreenshots";
        this->grpScreenshots->Padding = System::Windows::Forms::Padding ( 6 );
        this->grpScreenshots->Size = System::Drawing::Size ( 250, 88 );
        this->grpScreenshots->TabIndex = 16;
        this->grpScreenshots->TabStop = false;
        this->grpScreenshots->Text = L"Screenshots Folder";
        // 
        // btnScreenshots
        // 
        this->btnScreenshots->BackColor = System::Drawing::Color::FromArgb ( static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ), static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ),
                                                                             static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ) );
        this->btnScreenshots->CausesValidation = false;
        this->btnScreenshots->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
        this->btnScreenshots->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                       static_cast< System::Byte >( 0 ) ) );
        this->btnScreenshots->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
        this->btnScreenshots->Location = System::Drawing::Point ( 134, 56 );
        this->btnScreenshots->Name = L"btnScreenshots";
        this->btnScreenshots->Size = System::Drawing::Size ( 107, 24 );
        this->btnScreenshots->TabIndex = 1;
        this->btnScreenshots->Text = L" Browse";
        this->btnScreenshots->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
        this->tipMain->SetToolTip ( this->btnScreenshots, L"Browse to change the screenshots folder." );
        this->btnScreenshots->UseVisualStyleBackColor = false;
        this->btnScreenshots->Click += gcnew System::EventHandler ( this, &MainForm::btnScreenshots_Click );
        // 
        // txtScreenshots
        // 
        this->txtScreenshots->BackColor = System::Drawing::Color::FromArgb ( static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ), static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ),
                                                                             static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ) );
        this->txtScreenshots->Font = ( gcnew System::Drawing::Font ( L"Calibri", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                       static_cast< System::Byte >( 0 ) ) );
        this->txtScreenshots->ForeColor = System::Drawing::Color::Gainsboro;
        this->txtScreenshots->Location = System::Drawing::Point ( 6, 28 );
        this->txtScreenshots->Name = L"txtScreenshots";
        this->txtScreenshots->Size = System::Drawing::Size ( 235, 22 );
        this->txtScreenshots->TabIndex = 0;
        this->tipMain->SetToolTip ( this->txtScreenshots, L"Path to screenshots folder." );
        this->txtScreenshots->Leave += gcnew System::EventHandler ( this, &MainForm::txtScreenshots_Leave );
        // 
        // grpCaptureMode
        // 
        this->grpCaptureMode->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
        this->grpCaptureMode->BackColor = System::Drawing::Color::Transparent;
        this->grpCaptureMode->Controls->Add ( this->chkCaptureModeApp );
        this->grpCaptureMode->Controls->Add ( this->cmbCaptureMode );
        this->grpCaptureMode->Dock = System::Windows::Forms::DockStyle::Left;
        this->grpCaptureMode->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                                       static_cast< System::Byte >( 0 ) ) );
        this->grpCaptureMode->ForeColor = System::Drawing::Color::Gainsboro;
        this->grpCaptureMode->Location = System::Drawing::Point ( 6, 94 );
        this->grpCaptureMode->Margin = System::Windows::Forms::Padding ( 0 );
        this->grpCaptureMode->Name = L"grpCaptureMode";
        this->grpCaptureMode->Padding = System::Windows::Forms::Padding ( 6 );
        this->grpCaptureMode->Size = System::Drawing::Size ( 250, 145 );
        this->grpCaptureMode->TabIndex = 17;
        this->grpCaptureMode->TabStop = false;
        this->grpCaptureMode->Text = L"Capture Mode";
        // 
        // chkCaptureModeApp
        // 
        this->chkCaptureModeApp->BackColor = System::Drawing::Color::FromArgb ( static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ),
                                                                                static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ), static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ) );
        this->chkCaptureModeApp->BorderStyle = System::Windows::Forms::BorderStyle::None;
        this->chkCaptureModeApp->CheckOnClick = true;
        this->chkCaptureModeApp->Dock = System::Windows::Forms::DockStyle::Top;
        this->chkCaptureModeApp->Enabled = false;
        this->chkCaptureModeApp->Font = ( gcnew System::Drawing::Font ( L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                          static_cast< System::Byte >( 0 ) ) );
        this->chkCaptureModeApp->ForeColor = System::Drawing::Color::Gainsboro;
        this->chkCaptureModeApp->HorizontalScrollbar = true;
        this->chkCaptureModeApp->IntegralHeight = false;
        this->chkCaptureModeApp->Items->AddRange ( gcnew cli::array< System::Object^  > ( 1 ) { L"- Application List -" } );
        this->chkCaptureModeApp->Location = System::Drawing::Point ( 6, 51 );
        this->chkCaptureModeApp->Name = L"chkCaptureModeApp";
        this->chkCaptureModeApp->Size = System::Drawing::Size ( 238, 88 );
        this->chkCaptureModeApp->Sorted = true;
        this->chkCaptureModeApp->TabIndex = 3;
        this->tipMain->SetToolTip ( this->chkCaptureModeApp, L"Select the application to be captured." );
        this->chkCaptureModeApp->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler ( this, &MainForm::chkCaptureModeApp_ItemCheck );
        this->chkCaptureModeApp->SelectedIndexChanged += gcnew System::EventHandler ( this, &MainForm::chkCaptureModeApp_SelectedIndexChanged );
        // 
        // cmbCaptureMode
        // 
        this->cmbCaptureMode->BackColor = System::Drawing::Color::FromArgb ( static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ), static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ),
                                                                             static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ) );
        this->cmbCaptureMode->Dock = System::Windows::Forms::DockStyle::Top;
        this->cmbCaptureMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
        this->cmbCaptureMode->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                       static_cast< System::Byte >( 0 ) ) );
        this->cmbCaptureMode->ForeColor = System::Drawing::Color::Gainsboro;
        this->cmbCaptureMode->Location = System::Drawing::Point ( 6, 25 );
        this->cmbCaptureMode->Name = L"cmbCaptureMode";
        this->cmbCaptureMode->Size = System::Drawing::Size ( 238, 26 );
        this->cmbCaptureMode->TabIndex = 2;
        this->tipMain->SetToolTip ( this->cmbCaptureMode, L"Select your desired capture mode. (All monitores, Single Monitor, Single Applicat"
                                    L"ion, Screen Region)" );
        this->cmbCaptureMode->SelectedIndexChanged += gcnew System::EventHandler ( this, &MainForm::cmbCaptureMode_SelectedIndexChanged );
        // 
        // grpTimelapse
        // 
        this->grpTimelapse->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
        this->grpTimelapse->BackColor = System::Drawing::Color::Transparent;
        this->grpTimelapse->Controls->Add ( this->txtTimelapseDelay );
        this->grpTimelapse->Controls->Add ( this->lblTimelapseDelay );
        this->grpTimelapse->Controls->Add ( this->chkTimelapseTaskbar );
        this->grpTimelapse->Controls->Add ( this->chkTimelapseCountdown );
        this->grpTimelapse->Controls->Add ( this->txtTimelapseCountdown );
        this->grpTimelapse->Controls->Add ( this->lblTimelapseCountdown );
        this->grpTimelapse->Controls->Add ( this->chkTimelapseNotify );
        this->grpTimelapse->Controls->Add ( this->txtTimelapseNotify );
        this->grpTimelapse->Controls->Add ( this->lblTimelapseNotify );
        this->grpTimelapse->Controls->Add ( this->txtTimelapsePeriod );
        this->grpTimelapse->Controls->Add ( this->lblTimelapsePeriod );
        this->grpTimelapse->Dock = System::Windows::Forms::DockStyle::Left;
        this->flwSettings->SetFlowBreak ( this->grpTimelapse, true );
        this->grpTimelapse->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                                     static_cast< System::Byte >( 0 ) ) );
        this->grpTimelapse->ForeColor = System::Drawing::Color::Gainsboro;
        this->grpTimelapse->Location = System::Drawing::Point ( 6, 239 );
        this->grpTimelapse->Margin = System::Windows::Forms::Padding ( 0 );
        this->grpTimelapse->Name = L"grpTimelapse";
        this->grpTimelapse->Padding = System::Windows::Forms::Padding ( 6 );
        this->grpTimelapse->Size = System::Drawing::Size ( 250, 238 );
        this->grpTimelapse->TabIndex = 12;
        this->grpTimelapse->TabStop = false;
        this->grpTimelapse->Text = L"Timelapse";
        // 
        // txtTimelapseDelay
        // 
        this->txtTimelapseDelay->BackColor = System::Drawing::Color::FromArgb ( static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ),
                                                                                static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ), static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ) );
        this->txtTimelapseDelay->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                          static_cast< System::Byte >( 0 ) ) );
        this->txtTimelapseDelay->ForeColor = System::Drawing::Color::Gainsboro;
        this->txtTimelapseDelay->Location = System::Drawing::Point ( 177, 54 );
        this->txtTimelapseDelay->Maximum = System::Decimal ( gcnew cli::array< System::Int32 > ( 4 ) { 300, 0, 0, 0 } );
        this->txtTimelapseDelay->Minimum = System::Decimal ( gcnew cli::array< System::Int32 > ( 4 ) { 1, 0, 0, 0 } );
        this->txtTimelapseDelay->Name = L"txtTimelapseDelay";
        this->txtTimelapseDelay->Size = System::Drawing::Size ( 64, 26 );
        this->txtTimelapseDelay->TabIndex = 5;
        this->txtTimelapseDelay->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
        this->tipMain->SetToolTip ( this->txtTimelapseDelay, L"When you open TimelapseFX, the 1st screen shot wait for this delay before start t"
                                    L"he interval period." );
        this->txtTimelapseDelay->Value = System::Decimal ( gcnew cli::array< System::Int32 > ( 4 ) { 30, 0, 0, 0 } );
        this->txtTimelapseDelay->Leave += gcnew System::EventHandler ( this, &MainForm::txtTimelapseDelay_Leave );
        // 
        // lblTimelapseDelay
        // 
        this->lblTimelapseDelay->AutoSize = true;
        this->lblTimelapseDelay->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                          static_cast< System::Byte >( 0 ) ) );
        this->lblTimelapseDelay->Location = System::Drawing::Point ( 6, 56 );
        this->lblTimelapseDelay->Name = L"lblTimelapseDelay";
        this->lblTimelapseDelay->Size = System::Drawing::Size ( 152, 18 );
        this->lblTimelapseDelay->TabIndex = 18;
        this->lblTimelapseDelay->Text = L"Delay start (in seconds)";
        this->tipMain->SetToolTip ( this->lblTimelapseDelay, L"When you open TimelapseFX, the 1st screen shot wait for this delay before start t"
                                    L"he interval period." );
                                    // 
                                    // chkTimelapseTaskbar
                                    // 
        this->chkTimelapseTaskbar->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
        this->chkTimelapseTaskbar->Checked = true;
        this->chkTimelapseTaskbar->CheckState = System::Windows::Forms::CheckState::Checked;
        this->chkTimelapseTaskbar->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                            static_cast< System::Byte >( 0 ) ) );
        this->chkTimelapseTaskbar->Location = System::Drawing::Point ( 6, 22 );
        this->chkTimelapseTaskbar->Name = L"chkTimelapseTaskbar";
        this->chkTimelapseTaskbar->Size = System::Drawing::Size ( 235, 25 );
        this->chkTimelapseTaskbar->TabIndex = 4;
        this->chkTimelapseTaskbar->Text = L"Screenshot without Taskbar";
        this->tipMain->SetToolTip ( this->chkTimelapseTaskbar, L"Auto-remove the taskbar from the screenshots." );
        this->chkTimelapseTaskbar->UseVisualStyleBackColor = true;
        this->chkTimelapseTaskbar->CheckedChanged += gcnew System::EventHandler ( this, &MainForm::chkTimelapseTaskbar_CheckedChanged );
        // 
        // chkTimelapseCountdown
        // 
        this->chkTimelapseCountdown->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
        this->chkTimelapseCountdown->Checked = true;
        this->chkTimelapseCountdown->CheckState = System::Windows::Forms::CheckState::Checked;
        this->chkTimelapseCountdown->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                              static_cast< System::Byte >( 0 ) ) );
        this->chkTimelapseCountdown->Location = System::Drawing::Point ( 6, 171 );
        this->chkTimelapseCountdown->Name = L"chkTimelapseCountdown";
        this->chkTimelapseCountdown->Size = System::Drawing::Size ( 235, 25 );
        this->chkTimelapseCountdown->TabIndex = 9;
        this->chkTimelapseCountdown->Text = L"Countdown before screenshot";
        this->tipMain->SetToolTip ( this->chkTimelapseCountdown, L"Icon blinks RED/BLUE in the system tray." );
        this->chkTimelapseCountdown->UseVisualStyleBackColor = true;
        this->chkTimelapseCountdown->CheckedChanged += gcnew System::EventHandler ( this, &MainForm::chkTimelapseCountdown_CheckedChanged );
        // 
        // txtTimelapseCountdown
        // 
        this->txtTimelapseCountdown->BackColor = System::Drawing::Color::FromArgb ( static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ),
                                                                                    static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ), static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ) );
        this->txtTimelapseCountdown->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                              static_cast< System::Byte >( 0 ) ) );
        this->txtTimelapseCountdown->ForeColor = System::Drawing::Color::Gainsboro;
        this->txtTimelapseCountdown->Location = System::Drawing::Point ( 177, 203 );
        this->txtTimelapseCountdown->Maximum = System::Decimal ( gcnew cli::array< System::Int32 > ( 4 ) { 60, 0, 0, 0 } );
        this->txtTimelapseCountdown->Minimum = System::Decimal ( gcnew cli::array< System::Int32 > ( 4 ) { 1, 0, 0, 0 } );
        this->txtTimelapseCountdown->Name = L"txtTimelapseCountdown";
        this->txtTimelapseCountdown->Size = System::Drawing::Size ( 64, 26 );
        this->txtTimelapseCountdown->TabIndex = 10;
        this->txtTimelapseCountdown->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
        this->tipMain->SetToolTip ( this->txtTimelapseCountdown, L"Seconds the icon will blink to warn before the screenshot." );
        this->txtTimelapseCountdown->Value = System::Decimal ( gcnew cli::array< System::Int32 > ( 4 ) { 3, 0, 0, 0 } );
        this->txtTimelapseCountdown->Leave += gcnew System::EventHandler ( this, &MainForm::txtTimelapseCountdown_Leave );
        // 
        // lblTimelapseCountdown
        // 
        this->lblTimelapseCountdown->AutoSize = true;
        this->lblTimelapseCountdown->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                              static_cast< System::Byte >( 0 ) ) );
        this->lblTimelapseCountdown->Location = System::Drawing::Point ( 6, 205 );
        this->lblTimelapseCountdown->Name = L"lblTimelapseCountdown";
        this->lblTimelapseCountdown->Size = System::Drawing::Size ( 158, 18 );
        this->lblTimelapseCountdown->TabIndex = 21;
        this->lblTimelapseCountdown->Text = L"Countdown (in seconds)";
        this->tipMain->SetToolTip ( this->lblTimelapseCountdown, L"Seconds the icon will blink to warn before the screenshot." );
        // 
        // chkTimelapseNotify
        // 
        this->chkTimelapseNotify->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
        this->chkTimelapseNotify->Checked = true;
        this->chkTimelapseNotify->CheckState = System::Windows::Forms::CheckState::Checked;
        this->chkTimelapseNotify->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                           static_cast< System::Byte >( 0 ) ) );
        this->chkTimelapseNotify->Location = System::Drawing::Point ( 6, 110 );
        this->chkTimelapseNotify->Name = L"chkTimelapseNotify";
        this->chkTimelapseNotify->Size = System::Drawing::Size ( 235, 25 );
        this->chkTimelapseNotify->TabIndex = 7;
        this->chkTimelapseNotify->Text = L"Notify before screenshot";
        this->tipMain->SetToolTip ( this->chkTimelapseNotify, L"Icon blinks YELLOW/BLUE in the system tray." );
        this->chkTimelapseNotify->UseVisualStyleBackColor = true;
        this->chkTimelapseNotify->CheckedChanged += gcnew System::EventHandler ( this, &MainForm::chkTimelapseNotify_CheckedChanged );
        // 
        // txtTimelapseNotify
        // 
        this->txtTimelapseNotify->BackColor = System::Drawing::Color::FromArgb ( static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ),
                                                                                 static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ), static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ) );
        this->txtTimelapseNotify->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                           static_cast< System::Byte >( 0 ) ) );
        this->txtTimelapseNotify->ForeColor = System::Drawing::Color::Gainsboro;
        this->txtTimelapseNotify->Location = System::Drawing::Point ( 177, 142 );
        this->txtTimelapseNotify->Maximum = System::Decimal ( gcnew cli::array< System::Int32 > ( 4 ) { 300, 0, 0, 0 } );
        this->txtTimelapseNotify->Minimum = System::Decimal ( gcnew cli::array< System::Int32 > ( 4 ) { 1, 0, 0, 0 } );
        this->txtTimelapseNotify->Name = L"txtTimelapseNotify";
        this->txtTimelapseNotify->Size = System::Drawing::Size ( 64, 26 );
        this->txtTimelapseNotify->TabIndex = 8;
        this->txtTimelapseNotify->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
        this->tipMain->SetToolTip ( this->txtTimelapseNotify, L"Seconds the icon will blink to notify before the screenshot." );
        this->txtTimelapseNotify->Value = System::Decimal ( gcnew cli::array< System::Int32 > ( 4 ) { 10, 0, 0, 0 } );
        this->txtTimelapseNotify->Leave += gcnew System::EventHandler ( this, &MainForm::txtTimelapseNotify_Leave );
        // 
        // lblTimelapseNotify
        // 
        this->lblTimelapseNotify->AutoSize = true;
        this->lblTimelapseNotify->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                           static_cast< System::Byte >( 0 ) ) );
        this->lblTimelapseNotify->Location = System::Drawing::Point ( 6, 144 );
        this->lblTimelapseNotify->Name = L"lblTimelapseNotify";
        this->lblTimelapseNotify->Size = System::Drawing::Size ( 124, 18 );
        this->lblTimelapseNotify->TabIndex = 20;
        this->lblTimelapseNotify->Text = L"Notify (in seconds)";
        this->tipMain->SetToolTip ( this->lblTimelapseNotify, L"Seconds the icon will blink to notify before the screenshot." );
        // 
        // txtTimelapsePeriod
        // 
        this->txtTimelapsePeriod->BackColor = System::Drawing::Color::FromArgb ( static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ),
                                                                                 static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ), static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ) );
        this->txtTimelapsePeriod->DecimalPlaces = 1;
        this->txtTimelapsePeriod->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                           static_cast< System::Byte >( 0 ) ) );
        this->txtTimelapsePeriod->ForeColor = System::Drawing::Color::Gainsboro;
        this->txtTimelapsePeriod->Location = System::Drawing::Point ( 177, 81 );
        this->txtTimelapsePeriod->Maximum = System::Decimal ( gcnew cli::array< System::Int32 > ( 4 ) { 2880, 0, 0, 0 } );
        this->txtTimelapsePeriod->Minimum = System::Decimal ( gcnew cli::array< System::Int32 > ( 4 ) { 1, 0, 0, 65536 } );
        this->txtTimelapsePeriod->Name = L"txtTimelapsePeriod";
        this->txtTimelapsePeriod->Size = System::Drawing::Size ( 64, 26 );
        this->txtTimelapsePeriod->TabIndex = 6;
        this->txtTimelapsePeriod->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
        this->tipMain->SetToolTip ( this->txtTimelapsePeriod, L"Define the amount of minutes to wait between each screenshot." );
        this->txtTimelapsePeriod->Value = System::Decimal ( gcnew cli::array< System::Int32 > ( 4 ) { 10, 0, 0, 0 } );
        this->txtTimelapsePeriod->Leave += gcnew System::EventHandler ( this, &MainForm::txtTimelapsePeriod_Leave );
        // 
        // lblTimelapsePeriod
        // 
        this->lblTimelapsePeriod->AutoSize = true;
        this->lblTimelapsePeriod->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                           static_cast< System::Byte >( 0 ) ) );
        this->lblTimelapsePeriod->Location = System::Drawing::Point ( 6, 83 );
        this->lblTimelapsePeriod->Name = L"lblTimelapsePeriod";
        this->lblTimelapsePeriod->Size = System::Drawing::Size ( 135, 18 );
        this->lblTimelapsePeriod->TabIndex = 19;
        this->lblTimelapsePeriod->Text = L"Interval (in minutes)";
        this->tipMain->SetToolTip ( this->lblTimelapsePeriod, L"Define the amount of minutes to wait between each screenshot." );
        // 
        // grpFFMpeg
        // 
        this->grpFFMpeg->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
        this->grpFFMpeg->BackColor = System::Drawing::Color::Transparent;
        this->grpFFMpeg->Controls->Add ( this->btnFFMpegBrowse );
        this->grpFFMpeg->Controls->Add ( this->btnFFMpegDownload );
        this->grpFFMpeg->Controls->Add ( this->lblFFMpeg );
        this->grpFFMpeg->Controls->Add ( this->txtFFMpeg );
        this->grpFFMpeg->Dock = System::Windows::Forms::DockStyle::Left;
        this->flwSettings->SetFlowBreak ( this->grpFFMpeg, true );
        this->grpFFMpeg->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                                  static_cast< System::Byte >( 0 ) ) );
        this->grpFFMpeg->ForeColor = System::Drawing::Color::Gainsboro;
        this->grpFFMpeg->Location = System::Drawing::Point ( 6, 477 );
        this->grpFFMpeg->Margin = System::Windows::Forms::Padding ( 0 );
        this->grpFFMpeg->Name = L"grpFFMpeg";
        this->grpFFMpeg->Padding = System::Windows::Forms::Padding ( 6 );
        this->grpFFMpeg->Size = System::Drawing::Size ( 250, 146 );
        this->grpFFMpeg->TabIndex = 22;
        this->grpFFMpeg->TabStop = false;
        this->grpFFMpeg->Text = L"FFMPEG.exe Location";
        // 
        // btnFFMpegBrowse
        // 
        this->btnFFMpegBrowse->BackColor = System::Drawing::Color::FromArgb ( static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ), static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ),
                                                                              static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ) );
        this->btnFFMpegBrowse->CausesValidation = false;
        this->btnFFMpegBrowse->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
        this->btnFFMpegBrowse->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                        static_cast< System::Byte >( 0 ) ) );
        this->btnFFMpegBrowse->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
        this->btnFFMpegBrowse->Location = System::Drawing::Point ( 6, 113 );
        this->btnFFMpegBrowse->Name = L"btnFFMpegBrowse";
        this->btnFFMpegBrowse->Size = System::Drawing::Size ( 107, 24 );
        this->btnFFMpegBrowse->TabIndex = 12;
        this->btnFFMpegBrowse->Text = L" Browse";
        this->btnFFMpegBrowse->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
        this->tipMain->SetToolTip ( this->btnFFMpegBrowse, L"Browse FFMpeg.exe file path." );
        this->btnFFMpegBrowse->UseVisualStyleBackColor = false;
        this->btnFFMpegBrowse->Click += gcnew System::EventHandler ( this, &MainForm::btnFFMpegBrowse_Click );
        // 
        // btnFFMpegDownload
        // 
        this->btnFFMpegDownload->BackColor = System::Drawing::Color::FromArgb ( static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ),
                                                                                static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ), static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ) );
        this->btnFFMpegDownload->CausesValidation = false;
        this->btnFFMpegDownload->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
        this->btnFFMpegDownload->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                          static_cast< System::Byte >( 0 ) ) );
        this->btnFFMpegDownload->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
        this->btnFFMpegDownload->Location = System::Drawing::Point ( 134, 113 );
        this->btnFFMpegDownload->Name = L"btnFFMpegDownload";
        this->btnFFMpegDownload->Size = System::Drawing::Size ( 107, 24 );
        this->btnFFMpegDownload->TabIndex = 13;
        this->btnFFMpegDownload->Text = L" Download";
        this->btnFFMpegDownload->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
        this->tipMain->SetToolTip ( this->btnFFMpegDownload, L"Open 2 links. 1st is FFMpeg page with information and source code, 2nd is an inst"
                                    L"aller ready to download." );
        this->btnFFMpegDownload->UseVisualStyleBackColor = false;
        this->btnFFMpegDownload->Click += gcnew System::EventHandler ( this, &MainForm::btnFFMpegDownload_Click );
        // 
        // lblFFMpeg
        // 
        this->lblFFMpeg->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                  static_cast< System::Byte >( 0 ) ) );
        this->lblFFMpeg->Location = System::Drawing::Point ( 3, 25 );
        this->lblFFMpeg->Name = L"lblFFMpeg";
        this->lblFFMpeg->Size = System::Drawing::Size ( 241, 55 );
        this->lblFFMpeg->TabIndex = 23;
        this->lblFFMpeg->Text = L"FFMpeg is used to convert the timelapse screenshots to video. Inform the FFMPEG i"
            L"nstall location:";
            // 
            // txtFFMpeg
            // 
        this->txtFFMpeg->BackColor = System::Drawing::Color::FromArgb ( static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ), static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ),
                                                                        static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ) );
        this->txtFFMpeg->Font = ( gcnew System::Drawing::Font ( L"Calibri", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                  static_cast< System::Byte >( 0 ) ) );
        this->txtFFMpeg->ForeColor = System::Drawing::Color::Gainsboro;
        this->txtFFMpeg->Location = System::Drawing::Point ( 6, 83 );
        this->txtFFMpeg->Name = L"txtFFMpeg";
        this->txtFFMpeg->Size = System::Drawing::Size ( 235, 22 );
        this->txtFFMpeg->TabIndex = 11;
        this->txtFFMpeg->Text = L"C:\\Program Files\\FFMpeg\\bin\\FFMpeg.exe";
        this->tipMain->SetToolTip ( this->txtFFMpeg, L"Path to FFMPEG.EXE" );
        this->txtFFMpeg->Leave += gcnew System::EventHandler ( this, &MainForm::txtFFMpeg_Leave );
        // 
        // grpExp
        // 
        this->grpExp->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
        this->grpExp->BackColor = System::Drawing::Color::Transparent;
        this->grpExp->Controls->Add ( this->chkExpAspect );
        this->grpExp->Controls->Add ( this->txtExpFramerate );
        this->grpExp->Controls->Add ( this->lblExpFramerate );
        this->grpExp->Dock = System::Windows::Forms::DockStyle::Left;
        this->flwSettings->SetFlowBreak ( this->grpExp, true );
        this->grpExp->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                               static_cast< System::Byte >( 0 ) ) );
        this->grpExp->ForeColor = System::Drawing::Color::Gainsboro;
        this->grpExp->Location = System::Drawing::Point ( 6, 623 );
        this->grpExp->Margin = System::Windows::Forms::Padding ( 0 );
        this->grpExp->Name = L"grpExp";
        this->grpExp->Padding = System::Windows::Forms::Padding ( 6 );
        this->grpExp->Size = System::Drawing::Size ( 250, 92 );
        this->grpExp->TabIndex = 24;
        this->grpExp->TabStop = false;
        this->grpExp->Text = L"Export Video";
        // 
        // chkExpAspect
        // 
        this->chkExpAspect->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
        this->chkExpAspect->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                     static_cast< System::Byte >( 0 ) ) );
        this->chkExpAspect->Location = System::Drawing::Point ( 6, 58 );
        this->chkExpAspect->Name = L"chkExpAspect";
        this->chkExpAspect->Size = System::Drawing::Size ( 235, 25 );
        this->chkExpAspect->TabIndex = 15;
        this->chkExpAspect->Text = L"Force Aspect Ratio 16:9";
        this->chkExpAspect->UseVisualStyleBackColor = true;
        this->chkExpAspect->CheckedChanged += gcnew System::EventHandler ( this, &MainForm::chkExpAspect_CheckedChanged );
        // 
        // txtExpFramerate
        // 
        this->txtExpFramerate->BackColor = System::Drawing::Color::FromArgb ( static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ), static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ),
                                                                              static_cast< System::Int32 >( static_cast< System::Byte >( 45 ) ) );
        this->txtExpFramerate->DecimalPlaces = 2;
        this->txtExpFramerate->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                        static_cast< System::Byte >( 0 ) ) );
        this->txtExpFramerate->ForeColor = System::Drawing::Color::Gainsboro;
        this->txtExpFramerate->Increment = System::Decimal ( gcnew cli::array< System::Int32 > ( 4 ) { 250, 0, 0, 196608 } );
        this->txtExpFramerate->Location = System::Drawing::Point ( 177, 27 );
        this->txtExpFramerate->Name = L"txtExpFramerate";
        this->txtExpFramerate->Size = System::Drawing::Size ( 64, 26 );
        this->txtExpFramerate->TabIndex = 14;
        this->txtExpFramerate->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
        this->tipMain->SetToolTip ( this->txtExpFramerate, L"Default is 1 screenshot per second. Change to 2 if you want faster timelapse vide"
                                    L"o, or 0.5 if you want slower." );
        this->txtExpFramerate->Value = System::Decimal ( gcnew cli::array< System::Int32 > ( 4 ) { 1, 0, 0, 0 } );
        this->txtExpFramerate->Leave += gcnew System::EventHandler ( this, &MainForm::txtExpFramerate_Leave );
        // 
        // lblExpFramerate
        // 
        this->lblExpFramerate->AutoSize = true;
        this->lblExpFramerate->Font = ( gcnew System::Drawing::Font ( L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                        static_cast< System::Byte >( 0 ) ) );
        this->lblExpFramerate->Location = System::Drawing::Point ( 6, 29 );
        this->lblExpFramerate->Name = L"lblExpFramerate";
        this->lblExpFramerate->Size = System::Drawing::Size ( 124, 18 );
        this->lblExpFramerate->TabIndex = 0;
        this->lblExpFramerate->Text = L"Images Per Second";
        this->tipMain->SetToolTip ( this->lblExpFramerate, L"Default is 1 screenshot per second. Change to 2 if you want faster timelapse vide"
                                    L"o, or 0.5 if you want slower." );
                                    // 
                                    // dlgFolderBrowse
                                    // 
        this->dlgFolderBrowse->RootFolder = System::Environment::SpecialFolder::MyComputer;
        this->dlgFolderBrowse->ShowNewFolderButton = false;
        // 
        // MainForm
        // 
        this->AutoScaleDimensions = System::Drawing::SizeF ( 6, 13 );
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
        this->BackColor = System::Drawing::Color::FromArgb ( static_cast< System::Int32 >( static_cast< System::Byte >( 28 ) ), static_cast< System::Int32 >( static_cast< System::Byte >( 28 ) ),
                                                             static_cast< System::Int32 >( static_cast< System::Byte >( 28 ) ) );
        this->ClientSize = System::Drawing::Size ( 268, 724 );
        this->ControlBox = false;
        this->Controls->Add ( this->flwSettings );
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
        this->Location = System::Drawing::Point ( 0, 2160 );
        this->MaximizeBox = false;
        this->MinimizeBox = false;
        this->Name = L"MainForm";
        this->ShowInTaskbar = false;
        this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
        this->Text = L"TimelapseFX Settings";
        this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
        this->Deactivate += gcnew System::EventHandler ( this, &MainForm::MainForm_Deactivate );
        this->Load += gcnew System::EventHandler ( this, &MainForm::MainForm_Load );
        this->ctxMenu->ResumeLayout ( false );
        this->flwSettings->ResumeLayout ( false );
        this->grpScreenshots->ResumeLayout ( false );
        this->grpScreenshots->PerformLayout ();
        this->grpCaptureMode->ResumeLayout ( false );
        this->grpTimelapse->ResumeLayout ( false );
        this->grpTimelapse->PerformLayout ();
        ( cli::safe_cast< System::ComponentModel::ISupportInitialize^ >( this->txtTimelapseDelay ) )->EndInit ();
        ( cli::safe_cast< System::ComponentModel::ISupportInitialize^ >( this->txtTimelapseCountdown ) )->EndInit ();
        ( cli::safe_cast< System::ComponentModel::ISupportInitialize^ >( this->txtTimelapseNotify ) )->EndInit ();
        ( cli::safe_cast< System::ComponentModel::ISupportInitialize^ >( this->txtTimelapsePeriod ) )->EndInit ();
        this->grpFFMpeg->ResumeLayout ( false );
        this->grpFFMpeg->PerformLayout ();
        this->grpExp->ResumeLayout ( false );
        this->grpExp->PerformLayout ();
        ( cli::safe_cast< System::ComponentModel::ISupportInitialize^ >( this->txtExpFramerate ) )->EndInit ();
        this->ResumeLayout ( false );
        this->PerformLayout ();

    }
#pragma endregion

void MainForm_Load ( System::Object^ sender, System::EventArgs^ e );
void MainForm_Deactivate ( System::Object^ sender, System::EventArgs^ e );

void ntfSystray_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuOpenFolder_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuReorder_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuCaption_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuPause_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuSettings_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuAbout_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuQuit_Click ( System::Object^ sender, System::EventArgs^ e );

void mnuExpOrigMP4_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuExpOrigAVI_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuExpOrigGIF_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuExp480MP4_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuExp480AVI_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuExp480GIF_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuExp720MP4_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuExp720AVI_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuExp720GIF_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuExp1080MP4_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuExp1080AVI_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuExp1080GIF_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuExp2160MP4_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuExp2160AVI_Click ( System::Object^ sender, System::EventArgs^ e );
void mnuExp2160GIF_Click ( System::Object^ sender, System::EventArgs^ e );

void txtScreenshots_Leave ( System::Object^ sender, System::EventArgs^ e );
void btnScreenshots_Click ( System::Object^ sender, System::EventArgs^ e );
void cmbCaptureMode_SelectedIndexChanged ( System::Object^ sender, System::EventArgs^ e );
void chkCaptureModeApp_SelectedIndexChanged ( System::Object^ sender, System::EventArgs^ e );
void chkCaptureModeApp_ItemCheck ( System::Object^ sender, System::Windows::Forms::ItemCheckEventArgs^ e );
void chkTimelapseTaskbar_CheckedChanged ( System::Object^ sender, System::EventArgs^ e );
void txtTimelapseDelay_Leave ( System::Object^ sender, System::EventArgs^ e );
void txtTimelapsePeriod_Leave ( System::Object^ sender, System::EventArgs^ e );
void chkTimelapseNotify_CheckedChanged ( System::Object^ sender, System::EventArgs^ e );
void txtTimelapseNotify_Leave ( System::Object^ sender, System::EventArgs^ e );
void chkTimelapseCountdown_CheckedChanged ( System::Object^ sender, System::EventArgs^ e );
void txtTimelapseCountdown_Leave ( System::Object^ sender, System::EventArgs^ e );
void txtFFMpeg_Leave ( System::Object^ sender, System::EventArgs^ e );
void btnFFMpegBrowse_Click ( System::Object^ sender, System::EventArgs^ e );
void btnFFMpegDownload_Click ( System::Object^ sender, System::EventArgs^ e );
void txtExpFramerate_Leave ( System::Object^ sender, System::EventArgs^ e );
void chkExpAspect_CheckedChanged ( System::Object^ sender, System::EventArgs^ e );

void AllControlsEnabled(bool bEnabled);
void ExportSettings();

};
}