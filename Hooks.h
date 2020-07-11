#pragma once

using ResetFn = long(__stdcall*)(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pp);
extern ResetFn oReset;

using PresentFn = long(__stdcall*)(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);
extern PresentFn oPresent;

using CreateMoveFn = bool(__stdcall*)(float, CUserCmd*);
extern CreateMoveFn oCreateMove;

using PaintTraverseFn = void(__stdcall*)(unsigned int, bool, bool);
extern PaintTraverseFn oPaintTraverse;

typedef void(__thiscall* LockCursorFn)(void*);
extern LockCursorFn oLockCursor;


namespace Hooks {
	extern long __stdcall Present(IDirect3DDevice9* device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion); // probably better if you go with EndScene.
	extern long __stdcall Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
	extern bool __stdcall CreateMove(float flInputSampleTime, CUserCmd * cmd);
	extern void __stdcall PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce);
	extern void __stdcall LockCursor();

	extern WNDPROC oldWindowProc;
	extern LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

}