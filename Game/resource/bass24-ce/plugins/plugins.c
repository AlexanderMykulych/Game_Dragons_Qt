/*
	BASS plugin test
	Copyright (c) 2005-2009 Un4seen Developments Ltd.
*/

#include <windows.h>
#include <aygshell.h>
#include <commdlg.h>
#include <commctrl.h>
#include "bass.h"

HWND win=NULL;

DWORD chan;	// the channel

OPENFILENAME ofn;
wchar_t filter[1000];

// display error messages
void Error(const wchar_t *es)
{
	wchar_t mes[200];
	wsprintf(mes,L"%s\n(error code: %d)",es,BASS_ErrorGetCode());
	MessageBox(win,mes,0,0);
}

// translate a CTYPE value to text
const wchar_t *GetCTypeString(DWORD ctype, HPLUGIN plugin)
{
	if (plugin) { // using a plugin
		const BASS_PLUGININFO *pinfo=BASS_PluginGetInfo(plugin); // get plugin info
		int a;
		for (a=0;a<pinfo->formatc;a++) {
			if (pinfo->formats[a].ctype==ctype) // found a "ctype" match...
				return pinfo->formats[a].name; // return it's name
		}
	}
	// check built-in stream formats...
	if (ctype==BASS_CTYPE_STREAM_OGG) return L"Ogg Vorbis";
	if (ctype==BASS_CTYPE_STREAM_MP1) return L"MPEG layer 1";
	if (ctype==BASS_CTYPE_STREAM_MP2) return L"MPEG layer 2";
	if (ctype==BASS_CTYPE_STREAM_MP3) return L"MPEG layer 3";
	if (ctype==BASS_CTYPE_STREAM_AIFF) return L"Audio IFF";
	if (ctype==BASS_CTYPE_STREAM_WAV_PCM) return L"PCM WAVE";
	if (ctype==BASS_CTYPE_STREAM_WAV_FLOAT) return L"Floating-point WAVE";
	if (ctype&BASS_CTYPE_STREAM_WAV) // other WAVE codec, could use acmFormatTagDetails to get its name, but...
		return L"WAVE";
	return L"?";
}

#define MESS(id,m,w,l) SendDlgItemMessage(win,id,m,(WPARAM)(w),(LPARAM)(l))

BOOL CALLBACK dialogproc(HWND h,UINT m,WPARAM w,LPARAM l)
{
	switch (m) {
		case WM_COMMAND:
			switch (LOWORD(w)) {
				case IDCANCEL:
				case IDOK:
					EndDialog(h,LOWORD(w));
					break;
				case 10:
					{
						wchar_t file[MAX_PATH]=L"";
						ofn.lpstrFile=file;
						ofn.nMaxFile=MAX_PATH;
						if (GetOpenFileName(&ofn)) {
							BASS_StreamFree(chan); // free the old stream
							if (!(chan=BASS_StreamCreateFile(FALSE,file,0,0,BASS_UNICODE|BASS_SAMPLE_LOOP))) {
								// it ain't playable
								MESS(10,WM_SETTEXT,0,L"click here to open a file...");
								MESS(11,WM_SETTEXT,0,L"");
								Error(L"Can't play the file");
								break;
							}
							MESS(10,WM_SETTEXT,0,file);
							{ // display the file type and length
								QWORD bytes=BASS_ChannelGetLength(chan,BASS_POS_BYTE);
								DWORD time=BASS_ChannelBytes2Seconds(chan,bytes);
								BASS_CHANNELINFO info;
								BASS_ChannelGetInfo(chan,&info);
								wsprintf(file,L"channel type = %x (%s)\nlength = %I64u (%u:%02u)",
									info.ctype,GetCTypeString(info.ctype,info.plugin),bytes,time/60,time%60);
								MESS(11,WM_SETTEXT,0,file);
								MESS(12,TBM_SETRANGE,1,MAKELONG(0,time)); // update scroller range
							}
							BASS_ChannelPlay(chan,FALSE);
						}
					}
					break;
			}
			break;

		case WM_HSCROLL:
			if (l && LOWORD(w)!=SB_THUMBPOSITION && LOWORD(w)!=SB_ENDSCROLL) { // set the position
				int pos=SendMessage((HWND)l,TBM_GETPOS,0,0);
				BASS_ChannelSetPosition(chan,BASS_ChannelSeconds2Bytes(chan,pos),BASS_POS_BYTE);
			}
			break;

		case WM_TIMER:
			MESS(12,TBM_SETPOS,1,(DWORD)BASS_ChannelBytes2Seconds(chan,BASS_ChannelGetPosition(chan,BASS_POS_BYTE))); // update position
			break;

		case WM_INITDIALOG:
			win=h;
			// initialize default output device
			if (!BASS_Init(-1,44100,0,NULL,NULL)) {
				Error(L"Can't initialize device");
				DestroyWindow(win);
				break;
			}
			{ // go full screen
				SHINITDLGINFO shidi;
				shidi.dwMask = SHIDIM_FLAGS;
				shidi.dwFlags = SHIDIF_DONEBUTTON|SHIDIF_SIZEDLGFULLSCREEN|SHIDIF_EMPTYMENU|SHIDIF_SIPDOWN;
				shidi.hDlg = h;
				SHInitDialog(&shidi);
			}
			// initialize file selector
			memset(&ofn,0,sizeof(ofn));
			ofn.lStructSize=sizeof(ofn);
			ofn.hwndOwner=h;
			ofn.Flags=OFN_HIDEREADONLY|OFN_EXPLORER;
			ofn.lpstrFilter=filter;
			memcpy(filter,L"BASS built-in (*.mp3;*.mp2;*.mp1;*.ogg;*.wav;*.aif)\0*.mp3;*.mp2;*.mp1;*.ogg;*.wav;*.aif\0",88*2);
			{ // look for plugins (in the executable's directory)
				WIN32_FIND_DATA fd;
				HANDLE fh;
				wchar_t path[MAX_PATH],*fp=filter+88;
				GetModuleFileName(0,path,sizeof(path));
				wcscpy(wcsrchr(path,'\\')+1,L"bass*.dll");
				fh=FindFirstFile(path,&fd);
				if (fh!=INVALID_HANDLE_VALUE) {
					do {
						HPLUGIN plug;
						if (plug=BASS_PluginLoad((char*)fd.cFileName,BASS_UNICODE)) { // plugin loaded...
							const BASS_PLUGININFO *pinfo=BASS_PluginGetInfo(plug); // get plugin info to add to the file selector filter...
							int a;
							for (a=0;a<pinfo->formatc;a++) {
								fp+=wsprintf(fp,L"%s (%s) - %s",pinfo->formats[a].name,pinfo->formats[a].exts,fd.cFileName)+1; // format description
								fp+=wsprintf(fp,L"%s",pinfo->formats[a].exts)+1; // extension filter
							}
							// add plugin to the list
							MESS(20,LB_ADDSTRING,0,fd.cFileName);
						}
					} while (FindNextFile(fh,&fd));
					FindClose(fh);
				}
				if (!MESS(20,LB_GETCOUNT,0,0)) // no plugins...
					MESS(20,LB_ADDSTRING,0,L"no plugins - visit the BASS webpage to get some");
				memcpy(fp,L"All files\0*.*\0\0",15*2);
			}
			SetTimer(h,1,500,0); // timer to update the position
			return 1;

		case WM_DESTROY:
			// "free" the output device and all plugins
			BASS_Free();
			BASS_PluginFree(0);
			break;
	}
	return 0;
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPWSTR lpCmdLine, int nCmdShow)
{
	// check the correct BASS was loaded
	if (HIWORD(BASS_GetVersion())!=BASSVERSION) {
		MessageBox(0,L"An incorrect version of BASS.DLL was loaded",0,MB_ICONERROR);
		return 0;
	}

	DialogBox(hInstance,MAKEINTRESOURCE(1000),0,dialogproc);

	return 0;
}
