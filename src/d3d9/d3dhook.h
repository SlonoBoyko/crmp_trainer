/*
		AUTHOR: SlonoBoyko
		LiteHack.Ru
		21.05.2018
*/

#pragma once

#define GAME_DIRECT3DDEVICE9			0xC97C28
#define GAME_PRESENT_PARAMETERS			0xC9C040
#define GAME_DEVICE_WINDOW				0xC97C1C

class CD3DHook
{
public:
								CD3DHook(void);
	void						InstallHook(void);
	void						InitRender(IDirect3DDevice9 *pDevice);
	void						UnInitRender(void);
	
	void						Render(void);

	class CD3DRender			*pRender;
	class CD3DFont				*pD3DFont;
	class CD3DFont				*pD3DFontFix;
	class CD3DFont				*pD3DFontNick;
	class CD3DFont				*pD3DFontBig;

	D3DPRESENT_PARAMETERS		*pPresentParam;
	IDirect3DDevice9			*pD3DDevice;

private:
	using tReset				= HRESULT(CALLBACK *)(IDirect3DDevice9 *, D3DPRESENT_PARAMETERS *);
	using tPresent				= HRESULT(CALLBACK *)(IDirect3DDevice9 *, const RECT *, const RECT *, HWND, const RGNDATA *);

	static HRESULT CALLBACK		Reset(IDirect3DDevice9 *, D3DPRESENT_PARAMETERS *);
	static HRESULT CALLBACK		Present(IDirect3DDevice9 *, const RECT *, const RECT *, HWND, const RGNDATA *);

	tReset						orig_Reset;
	tPresent					orig_Present;

	bool						bD3DRenderInit	= false;
	bool						bDrawingAllowed = false;
};

enum eDirectXVtable
{
	VTABLE_QueryInterface = 0,
	VTABLE_AddRef,
	VTABLE_Release,
	VTABLE_TestCooperativeLevel,
	VTABLE_GetAvaibleTextureMem,
	VTABLE_EvictManagedResources,
	VTABLE_GetDirect3D,
	VTABLE_GetDeviceCaps,
	VTABLE_GetDisplayMode,
	VTABLE_GetCreationParameters,
	VTABLE_SetCursorProperties,
	VTABLE_SetCursorPosition,
	VTABLE_ShowCursor,
	VTABLE_CreateAdditionalSwapChain,
	VTABLE_GetSwapChain,
	VTABLE_GetNumberOfSwapChains,
	VTABLE_Reset,
	VTABLE_Present,
	VTABLE_GetBackBuffer,
	VTABLE_GetRasterStatus,
	VTABLE_SetDialogBoxMode,
	VTABLE_SetGammaRamp,
	VTABLE_GetGammaRamp,
	VTABLE_CreateTexture,
	VTABLE_CreateVolumeTexture,
	VTABLE_CreateCubeTexture,
	VTABLE_CreateVertexBuffer,
	VTABLE_CreateIndexBuffer,
	VTABLE_CreateRenderTarget,
	VTABLE_CreateDepthStencilSurface,
	VTABLE_UpdateSurface,
	VTABLE_UpdateTexture,
	VTABLE_GetRenderTargetData,
	VTABLE_GetFronBufferData,
	VTABLE_StrechRect,
	VTABLE_ColorFill,
	VTABLE_CreateOffscreenPlainSurface,
	VTABLE_SetRenderTarget,
	VTABLE_GetRenderTarget,
	VTABLE_SetDepthStencilSurface,
	VTABLE_GetDepthStencilSurface,
	VTABLE_BeginScene,
	VTABLE_EndScene,
	VTABLE_Clear,
	VTABLE_SetTransforM,
	VTABLE_GetTransform,
	VTABLE_MultiplyTransform,
	VTABLE_SetViewport,
	VTABLE_GetViewport,
	VTABLE_SetMaterial,
	VTABLE_GetMaterial,
	VTABLE_SetLight,
	VTABLE_GetLight,
	VTABLE_LightEnable,
	VTABLE_GetLightEnable,
	VTABLE_SetClipPlane,
	VTABLE_GetClipPlane,
	VTABLE_SetRenderState,
	VTABLE_GetRenderState,
	VTABLE_CreateStateBlock,
	VTABLE_BeginStateBlock,
	VTABLE_EndStateBlock,
	VTABLE_SetClipStatus,
	VTABLE_GetClipStatus,
	VTABLE_GetTexture,
	VTABLE_SetTexture,
	VTABLE_GetTextureStageState,
	VTABLE_SetTextureStageState,
	VTABLE_GetSamplerState,
	VTABLE_SetSamplerState,
	VTABLE_ValidateDevice,
	VTABLE_SetPaletteEntries,
	VTABLE_GetPaletteEntries,
	VTABLE_SetCurrentTexturePalette,
	VTABLE_GetCurrentTexturePalette,
	VTABLE_SetScissorRect,
	VTABLE_GetScissorRect,
	VTABLE_SetSoftwareVertexProcessing,
	VTABLE_GetSoftwareVertexProcessing,
	VTABLE_SetNPatchMode,
	VTABLE_GetNPatchMode,
	VTABLE_DrawPrimitive,
	VTABLE_DrawIndexPrimitive,
	VTABLE_DrawPrimitiveUP,
	VTABLE_DrawIndexPrimitiveUP,
	VTABLE_ProcessVertices,
	VTABLE_CreateVertexDeclaration,
	VTABLE_SetVertexDeclaration,
	VTABLE_GetVertexDeclaration,
	VTABLE_SetFVF,
	VTABLE_GetFVF,
	VTABLE_CreateVertexShader,
	VTABLE_SetVertexShader,
	VTABLE_GetVertexShader,
	VTABLE_SetVertexShaderConstantF,
	VTABLE_GetVertexShaderConstantF,
	VTABLE_SetVertexShaderConstantI,
	VTABLE_GetVertexShaderConstantI,
	VTABLE_SetVertexShaderConstantB,
	VTABLE_GetVertexShaderConstantB,
	VTABLE_SetStreamSource,
	VTABLE_GetStreamSource,
	VTABLE_SetStreamSourceFreq,
	VTABLE_GetStreamSourceFreq,
	VTABLE_SetIndices,
	VTABLE_GetIndices,
	VTABLE_CreatePixelShader,
	VTABLE_SetPixelShader,
	VTABLE_GetPixelShader,
	VTABLE_SetPixelShaderConstantF,
	VTABLE_GetPixelShaderConstantF,
	VTABLE_SetPixelShaderConstantI,
	VTABLE_GetPixelShaderConstantI,
	VTABLE_SetPixelShaderConstantB,
	VTABLE_GetPixelShaderConstantB,
	VTABLE_DrawRectPatch,
	VTABLE_DrawTriPatch,
	VTABLE_DeletePatch,
	VTABLE_CreateQuery,
};

extern CD3DHook					*pD3DHook;