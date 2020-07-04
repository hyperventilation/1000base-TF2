#include "Main.h"
#include "Panels.h"

PaintTraverseFn oPaintTraverse;

void __stdcall Hooks::PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	oPaintTraverse(vguiPanel, forceRepaint, allowForce);
}
