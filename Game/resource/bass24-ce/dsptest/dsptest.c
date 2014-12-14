/*
	BASS simple DSP test
	Copyright (c) 2000-2010 Un4seen Developments Ltd.
*/

#include <windows.h>
#include <aygshell.h>
#include <commdlg.h>
#include "bass.h"

#ifndef M_PI
#define M_PI 3.14159265359
#endif

HWND win=NULL;

DWORD chan;	// the channel... HMUSIC or HSTREAM

OPENFILENAME ofn;

// display error messages
void Error(const wchar_t *es)
{
	wchar_t mes[200];
	wsprintf(mes,L"%s\n(error code: %d)",es,BASS_ErrorGetCode());
	MessageBox(win,mes,0,0);
}

#define MulShr(a,b,s) Int64ShraMod32(Int32x32To64(a,b),s)

// "rotate"
HDSP rotdsp=0;	// DSP handle
int rotpos[2];	// sin/cos pos (2.30 fixed-point)

void CALLBACK Rotate(HDSP handle, DWORD channel, void *buffer, DWORD length, void *user)
{
	int *d=(int*)buffer;
	DWORD a;

	for (a=0;a<length/4;a+=2) {
		d[a]=MulShr(d[a],abs(rotpos[0]),30);
		d[a+1]=MulShr(d[a+1],abs(rotpos[1]),30);
		rotpos[0]-=rotpos[1]>>16;
		rotpos[1]+=rotpos[0]>>16;
	}
}

// "echo"
HDSP echdsp=0;	// DSP handle
#define ECHBUFLEN 1200	// buffer length
int echbuf[ECHBUFLEN][2];	// buffer
int echpos;	// cur.pos
void CALLBACK Echo(HDSP handle, DWORD channel, void *buffer, DWORD length, void *user)
{
	int *d=(int*)buffer;
	DWORD a;

	for (a=0;a<length/4;a+=2) {
		int l=d[a]+(echbuf[echpos][1]/2);
		int r=d[a+1]+(echbuf[echpos][0]/2);
#if 1 // 0=echo, 1=basic "bathroom" reverb
		echbuf[echpos][0]=d[a]=l;
		echbuf[echpos][1]=d[a+1]=r;
#else
		echbuf[echpos][0]=d[a];
		echbuf[echpos][1]=d[a+1];
		d[a]=l;
		d[a+1]=r;
#endif
		echpos++;
		if (echpos==ECHBUFLEN) echpos=0;
	}
}

// "flanger"
HDSP fladsp=0;	// DSP handle
#define FLABUFLEN 350	// buffer length
int flabuf[FLABUFLEN][2];	// buffer
int flapos;	// cur.pos
int flas,flasinc;	// sweep pos/increment (23.9 fixed-point)
void CALLBACK Flange(HDSP handle, DWORD channel, void *buffer, DWORD length, void *user)
{
	int *d=(int*)buffer;
	DWORD a;

	for (a=0;a<length/4;a+=2) {
		int p1=(flapos+(flas>>9))%FLABUFLEN;
		int p2=(p1+1)%FLABUFLEN;
		int f=flas&511;
		int s;

		s=(d[a]+flabuf[p1][0]+MulShr(flabuf[p2][0]-flabuf[p1][0],f,9))*7/10;
		flabuf[flapos][0]=d[a];
		d[a]=s;

		s=(d[a+1]+flabuf[p1][1]+MulShr(flabuf[p2][1]-flabuf[p1][1],f,9))*7/10;
		flabuf[flapos][1]=d[a+1];
		d[a+1]=s;

		flapos++;
		if (flapos==FLABUFLEN) flapos=0;
		flas+=flasinc;
		if (flas<0 || flas>(FLABUFLEN<<9)-1) {
			flasinc=-flasinc;
			flas+=flasinc;
		}
	}
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
						BASS_CHANNELINFO info;
						wchar_t file[MAX_PATH]=L"";
						ofn.lpstrFilter=L"playable files\0*.mo3;*.xm;*.mod;*.s3m;*.it;*.mtm;*.umx;*.mp3;*.mp2;*.mp1;*.ogg;*.wav;*.aif\0All files\0*.*\0\0";
						ofn.lpstrFile=file;
						if (GetOpenFileName(&ofn)) {
							// free both MOD and stream, it must be one of them! :)
							BASS_MusicFree(chan);
							BASS_StreamFree(chan);
							if (!(chan=BASS_StreamCreateFile(FALSE,file,0,0,BASS_SAMPLE_LOOP|BASS_UNICODE))
								&& !(chan=BASS_MusicLoad(FALSE,file,0,0,BASS_SAMPLE_LOOP|BASS_MUSIC_RAMPS|BASS_UNICODE,0))) {
								// whatever it is, it ain't playable
								MESS(10,WM_SETTEXT,0,L"click here to open a file...");
								Error(L"Can't play the file");
								break;
							}
							BASS_ChannelGetInfo(chan,&info);
							if (info.chans!=2) { // only stereo is allowed
								MESS(10,WM_SETTEXT,0,L"click here to open a file...");
								BASS_MusicFree(chan);
								BASS_StreamFree(chan);
								Error(L"only stereo sources are supported");
								break;
							}
							MESS(10,WM_SETTEXT,0,file);
							// setup DSPs on new channel and play it
							SendMessage(win,WM_COMMAND,11,0);
							SendMessage(win,WM_COMMAND,12,0);
							SendMessage(win,WM_COMMAND,13,0);
							BASS_ChannelPlay(chan,FALSE);
						}
					}
					break;
				case 11: // toggle "rotate"
					if (MESS(11,BM_GETCHECK,0,0)) {
						rotpos[0]=rotpos[1]=759250125; // sin(PI/4)
						rotdsp=BASS_ChannelSetDSP(chan,&Rotate,0,2);
					} else
						BASS_ChannelRemoveDSP(chan,rotdsp);
					break;
				case 12: // toggle "echo"
					if (MESS(12,BM_GETCHECK,0,0)) {
						memset(echbuf,0,sizeof(echbuf));
						echpos=0;
						echdsp=BASS_ChannelSetDSP(chan,&Echo,0,1);
					} else
						BASS_ChannelRemoveDSP(chan,echdsp);
					break;
				case 13: // toggle "flanger"
					if (MESS(13,BM_GETCHECK,0,0)) {
						memset(flabuf,0,sizeof(flabuf));
						flapos=0;
					    flas=(FLABUFLEN/2)<<9;
					    flasinc=1;
						fladsp=BASS_ChannelSetDSP(chan,&Flange,0,0);
					} else
						BASS_ChannelRemoveDSP(chan,fladsp);
					break;
			}
			break;

		case WM_INITDIALOG:
			win=h;
			memset(&ofn,0,sizeof(ofn));
			ofn.lStructSize=sizeof(ofn);
			ofn.hwndOwner=h;
			ofn.nMaxFile=MAX_PATH;
			ofn.Flags=OFN_HIDEREADONLY|OFN_EXPLORER;
			// enable floating-point DSP (actually 8.24 fixed-point on CE)
			BASS_SetConfig(BASS_CONFIG_FLOATDSP,TRUE);
			// initialize - default device
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
			return 1;

		case WM_DESTROY:
			BASS_Free();
			break;
	}
	return 0;
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// check the correct BASS was loaded
	if (HIWORD(BASS_GetVersion())!=BASSVERSION) {
		MessageBox(0,L"An incorrect version of BASS.DLL was loaded",0,MB_ICONERROR);
		return 0;
	}

	DialogBox(hInstance,MAKEINTRESOURCE(1000),0,&dialogproc);

	return 0;
}
