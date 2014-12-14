/*
	BASS recording example
	Copyright (c) 2002-2009 Un4seen Developments Ltd.
*/

#include <windows.h>
#include <aygshell.h>
#include <commdlg.h>
#include <stdio.h>
#include "bass.h"

HWND win=NULL;

HRECORD rchan=0;		// recording channel
HSTREAM chan=0;			// playback channel

FILE *rfp;				// recording file

// display error messages
void Error(const wchar_t *es)
{
	wchar_t mes[200];
	wsprintf(mes,L"%s\n(error code: %d)",es,BASS_ErrorGetCode());
	MessageBox(win,mes,0,0);
}

// messaging macros
#define MESS(id,m,w,l) SendDlgItemMessage(win,id,m,(WPARAM)(w),(LPARAM)(l))
#define DLGITEM(id) GetDlgItem(win,id)

// buffer the recorded data
BOOL CALLBACK RecordingCallback(HRECORD handle, const void *buffer, DWORD length, void *user)
{
	return fwrite(buffer,length,1,rfp)==1; // continue recording if file write is successful
}

void StartRecording()
{
	WAVEFORMATEX wf;
	if (chan) { // free old recording
		BASS_StreamFree(chan);
		chan=0;
		EnableWindow(DLGITEM(11),FALSE);
		// close output device before recording incase of half-duplex device
		BASS_Free();
	}
	// open the output file
	if (!(rfp=_wfopen(L"bass.wav",L"wb"))) {
		Error(L"Can't create the file");
		return;
	}
	// write the WAVE header
	fwrite("RIFF\0\0\0\0WAVEfmt \20\0\0\0",1,20,rfp);
	wf.wFormatTag=WAVE_FORMAT_PCM;
	wf.nChannels=1;
	wf.wBitsPerSample=16;
	wf.nSamplesPerSec=44100;
	wf.nBlockAlign=wf.nChannels*wf.wBitsPerSample/8;
	wf.nAvgBytesPerSec=wf.nSamplesPerSec*wf.nBlockAlign;
	fwrite(&wf,1,16,rfp);
	fwrite("data\0\0\0\0",1,8,rfp);
	// start recording @ 44100hz 16-bit mono
	if (!(rchan=BASS_RecordStart(44100,1,0,&RecordingCallback,0))) {
		Error(L"Couldn't start recording");
		fclose(rfp);
		return;
	}
	MESS(10,WM_SETTEXT,0,L"Stop");
}

void StopRecording()
{
	BASS_ChannelStop(rchan);
	rchan=0;
	{ // complete the WAVE header
		DWORD len=ftell(rfp),v;
		fseek(rfp,4,SEEK_SET);
		v=len-8;
		fwrite(&v,1,4,rfp);
		fseek(rfp,40,SEEK_SET);
		v=len-44;
		fwrite(&v,1,4,rfp);
		fclose(rfp);
	}
	MESS(10,WM_SETTEXT,0,L"Record");
	// setup output device (using default device)
	if (!BASS_Init(-1,44100,0,NULL,NULL)) {
		Error(L"Can't initialize output device");
		return;
	}
	// create a stream from the recording
	if (chan=BASS_StreamCreateFile(FALSE,L"bass.wav",0,0,BASS_UNICODE))
		EnableWindow(DLGITEM(11),TRUE); // enable "play" button
	else 
		BASS_Free();
}

BOOL CALLBACK dialogproc(HWND h,UINT m,WPARAM w,LPARAM l)
{
	switch (m) {
		case WM_TIMER:
			{ // update the recording/playback counter
				wchar_t text[30]=L"";
				if (rchan) // recording
					wsprintf(text,L"%I64d",BASS_ChannelGetPosition(rchan,BASS_POS_BYTE));
				else if (chan) {
					if (BASS_ChannelIsActive(chan)) // playing
						wsprintf(text,L"%I64d / %I64d",BASS_ChannelGetPosition(chan,BASS_POS_BYTE),BASS_ChannelGetLength(chan,BASS_POS_BYTE));
					else
						wsprintf(text,L"%I64d",BASS_ChannelGetLength(chan,BASS_POS_BYTE));
				}
				MESS(20,WM_SETTEXT,0,text);
				{ // display free disk space
					ULARGE_INTEGER space;
					if (GetDiskFreeSpaceEx(NULL,&space,NULL,NULL)) {
						wsprintf(text,L"%I64d",space.QuadPart);
						MESS(21,WM_SETTEXT,0,text);
					}
				}
			}
			break;

		case WM_COMMAND:
			switch (LOWORD(w)) {
				case IDOK:
				case IDCANCEL:
					EndDialog(h,LOWORD(w));
					break;
				case 10:
					if (!rchan)
						StartRecording();
					else
						StopRecording();
					break;
				case 11:
					BASS_ChannelPlay(chan,TRUE); // play the recorded data
					break;
			}
			break;

		case WM_INITDIALOG:
			win=h;
			// setup recording device (using default device)
			if (!BASS_RecordInit(-1)) {
				Error(L"Can't initialize recording device");
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
			SetTimer(h,1,200,0); // timer to update the position display
			return 1;

		case WM_DESTROY:
			// release all BASS stuff
			BASS_RecordFree();
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

	DialogBox(hInstance,MAKEINTRESOURCE(1000),0,&dialogproc);

	return 0;
}
