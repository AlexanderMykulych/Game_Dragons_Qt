/*
	BASS internet radio example
	Copyright (c) 2002-2009 Un4seen Developments Ltd.
*/

#include <windows.h>
#include <aygshell.h>
#include <stdio.h>
#include "bass.h"

HWND win=NULL;
HANDLE cthread=0;
HSTREAM chan;

const wchar_t *urls[10]={ // preset stream URLs
	L"http://www.radioparadise.com/musiclinks/rp_128-9.m3u",L"http://www.radioparadise.com/musiclinks/rp_32.m3u",
	L"http://www.sky.fm/mp3/classical.pls",L"http://www.sky.fm/mp3/classical_low.pls",
	L"http://www.sky.fm/mp3/the80s.pls",L"http://www.sky.fm/mp3/the80s_low.pls",
	L"http://somafm.com/tags.pls",L"http://somafm.com/tags32.pls",
	L"http://somafm.com/secretagent.pls",L"http://somafm.com/secretagent24.pls"
};

// display error messages
void Error(const wchar_t *es)
{
	wchar_t mes[200];
	wsprintf(mes,L"%s\n(error code: %d)",es,BASS_ErrorGetCode());
	MessageBox(win,mes,0,0);
}

#define ITEM(id) GetDlgItem(win,id)
#define MESS(id,m,w,l) SendDlgItemMessage(win,id,m,(WPARAM)(w),(LPARAM)(l))

// set control text with 8-bit text (ANSI/UTF-8)
void SetWindowText8(HWND hwnd, const char *text, DWORD cp)
{
	wchar_t *wtext;
	int n=MultiByteToWideChar(cp,0,text,-1,0,0);
	wtext=alloca(n*2);
	MultiByteToWideChar(cp,0,text,-1,wtext,n);
	SetWindowText(hwnd,wtext);
}

// update stream title from metadata
void DoMeta()
{
	const char *meta=BASS_ChannelGetTags(chan,BASS_TAG_META);
	if (meta) { // got Shoutcast metadata
		char *p=strstr(meta,"StreamTitle='");
		if (p) {
			p=_strdup(p+13);
			strchr(p,';')[-1]=0;
			SetWindowText8(ITEM(30),p,CP_ACP);
			free(p);
		}
	} else {
		meta=BASS_ChannelGetTags(chan,BASS_TAG_OGG);
		if (meta) { // got Icecast/OGG tags
			const char *artist=NULL,*title=NULL,*p=meta;
			for (;*p;p+=strlen(p)+1) {
				if (!_strnicmp(p,"artist=",7)) // found the artist
					artist=p+7;
				if (!_strnicmp(p,"title=",6)) // found the title
					title=p+6;
			}
			if (artist) {
				char text[100];
				_snprintf(text,sizeof(text),"%s - %s",artist,title);
				SetWindowText8(ITEM(30),text,CP_UTF8);
			} else if (title)
				SetWindowText8(ITEM(30),title,CP_UTF8);
		}
    }
}

void CALLBACK MetaSync(HSYNC handle, DWORD channel, DWORD data, void *user)
{
	DoMeta();
}

void CALLBACK EndSync(HSYNC handle, DWORD channel, DWORD data, void *user)
{
	MESS(31,WM_SETTEXT,0,L"not playing");
	MESS(30,WM_SETTEXT,0,L"");
	MESS(32,WM_SETTEXT,0,L"");
}

void CALLBACK StatusProc(const void *buffer, DWORD length, void *user)
{
	if (buffer && !length)
		SetWindowText8(ITEM(32),buffer,CP_ACP); // display connection status
}

DWORD OpenURL(wchar_t *url)
{
	KillTimer(win,1); // stop prebuffer monitoring
	BASS_StreamFree(chan); // close old stream
	MESS(31,WM_SETTEXT,0,L"connecting...");
	MESS(30,WM_SETTEXT,0,L"");
	MESS(32,WM_SETTEXT,0,L"");
	chan=BASS_StreamCreateURL((char*)url,0,BASS_STREAM_BLOCK|BASS_STREAM_STATUS|BASS_STREAM_AUTOFREE|BASS_UNICODE,StatusProc,0); // open URL
	free(url); // free temp URL buffer
	if (!chan) { // failed to open
		MESS(31,WM_SETTEXT,0,L"not playing");
		Error(L"Can't play the stream");
	} else
		SetTimer(win,1,50,0); // start prebuffer monitoring
	cthread=0;
	return 0;
}

BOOL CALLBACK dialogproc(HWND h,UINT m,WPARAM w,LPARAM l)
{
	switch (m) {
		case WM_TIMER:
			{ // monitor prebuffering progress
				DWORD progress=BASS_StreamGetFilePosition(chan,BASS_FILEPOS_BUFFER)
					*100/BASS_StreamGetFilePosition(chan,BASS_FILEPOS_END); // percentage of buffer filled
				if (progress>75 || !BASS_StreamGetFilePosition(chan,BASS_FILEPOS_CONNECTED)) { // over 75% full (or end of download)
					KillTimer(win,1); // finished prebuffering, stop monitoring
					{ // get the broadcast name and URL
						const char *icy=BASS_ChannelGetTags(chan,BASS_TAG_ICY);
						if (!icy) icy=BASS_ChannelGetTags(chan,BASS_TAG_HTTP); // no ICY tags, try HTTP
						if (icy) {
							for (;*icy;icy+=strlen(icy)+1) {
								if (!_strnicmp(icy,"icy-name:",9))
									SetWindowText8(ITEM(31),icy+9,CP_ACP);
								if (!_strnicmp(icy,"icy-url:",8))
									SetWindowText8(ITEM(32),icy+8,CP_ACP);
							}
						} else
							MESS(31,WM_SETTEXT,0,L"");
					}
					// get the stream title and set sync for subsequent titles
					DoMeta();
					BASS_ChannelSetSync(chan,BASS_SYNC_META,0,&MetaSync,0); // Shoutcast
					BASS_ChannelSetSync(chan,BASS_SYNC_OGG_CHANGE,0,&MetaSync,0); // Icecast/OGG
					// set sync for end of stream
					BASS_ChannelSetSync(chan,BASS_SYNC_END,0,&EndSync,0);
					// play it!
					BASS_ChannelPlay(chan,FALSE);
				} else {
					wchar_t text[20];
					wsprintf(text,L"buffering... %d%%",progress);
					MESS(31,WM_SETTEXT,0,text);
				}
			}
			break;

		case WM_COMMAND:
			switch (LOWORD(w)) {
				case IDCANCEL:
				case IDOK:
					EndDialog(h,LOWORD(w));
					break;
				default:
					if ((LOWORD(w)>=10 && LOWORD(w)<20) || LOWORD(w)==21) {
						wchar_t *url;
						if (cthread) { // already connecting
							MessageBeep(0);
							break;
						}
						if (LOWORD(w)==21) { // custom stream URL
							wchar_t temp[200];
							MESS(20,WM_GETTEXT,200,temp);
							url=wcsdup(temp);
						} else // preset
							url=wcsdup(urls[LOWORD(w)-10]);
						// open URL in a new thread (so that main thread is free)
						cthread=CreateThread(NULL,0,OpenURL,url,0,NULL);
						CloseHandle(cthread);
					}
			}
			break;

		case WM_INITDIALOG:
			win=h;
			// initialize output device
			if (!BASS_Init(-1,44100,0,NULL,NULL)) {
				Error(L"Can't initialize device");
				EndDialog(h,0);
				return 0;
			}
			{ // go full screen
				SHINITDLGINFO shidi;
				shidi.dwMask = SHIDIM_FLAGS;
				shidi.dwFlags = SHIDIF_DONEBUTTON|SHIDIF_SIZEDLGFULLSCREEN|SHIDIF_EMPTYMENU|SHIDIF_SIPDOWN;
				shidi.hDlg = h;
				SHInitDialog(&shidi);
			}
			BASS_SetConfig(BASS_CONFIG_NET_PLAYLIST,1); // enable playlist processing
			BASS_SetConfig(BASS_CONFIG_NET_PREBUF,0); // minimize automatic pre-buffering, so we can do it (and display it) instead
			return 1;

		case WM_DESTROY:
			BASS_Free();
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

	// display the window
	DialogBox(hInstance,MAKEINTRESOURCE(1000),0,&dialogproc);

	return 0;
}
